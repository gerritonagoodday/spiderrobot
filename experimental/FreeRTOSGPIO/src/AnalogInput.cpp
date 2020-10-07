#include "AnalogInput.h"

// Static members initialization
const char AnalogInput::TAG[] = "ADC";
int AnalogInput::gpio_input_total_count=0;
std::map<adc_channel_t, AnalogInput*> AnalogInput::instances;
TaskHandle_t AnalogInput::xSupervisorTaskHandle=0;

// Constructors:
// Channel:  ADC_CHANNEL_0...ADC_CHANNEL_7, ADC_CHANNEL_8, ADC_CHANNEL_9
// ADC Unit: ADC_UNIT_1, ADC_UNIT_2
// Bitwith: adc_bit_width_BIT_9, adc_bit_width_BIT_10, adc_bit_width_BIT_11, adc_bit_width_BIT_12 for 9,10,11,12. 
// Affects all ADCs on this unit. Default 12 bits
// Name, Description, defaults to autogenerate strings
AnalogInput::AnalogInput(adc_channel_t _adc_channel,
  adc_unit_t _adc_unit = ADC_UNIT_1,
  adc_bits_width_t _adc_bit_width = ADC_WIDTH_BIT_12, 
  const char * _name = NULL, 
  const char * _desc = NULL):
    adc_channel(_adc_channel), adc_unit(_adc_unit), adc_bit_width(_adc_bit_width)
{
  // Set up logging tag, e.g. ADC!_!
  sprintf(tag,"%s%d_%d",TAG,adc_unit,adc_channel);
 
  // Self registration to a map of all other class instances like this
  instances[adc_channel] = this;
  // state controll
  smoothed_value = 0.0;
  now_time   = -1;
  prev_time  = -1;  

  if(adc_unit==ADC_UNIT_1){
    // 12-bit ADC Converter, ADC_UNIT_1 (GPIO 32-39) or ADC_UNIT_2 (GPIO 0,2,4,12,13,14,15,25,26,27)    
    // ADC1_CHANNEL_0...ADC1_CHANNEL_7, ADC2_CHANNEL_0...ADC2_CHANNEL_9
    if(adc_channel >= static_cast<adc_channel_t>(ADC1_CHANNEL_0) && 
       adc_channel <= static_cast<adc_channel_t>(ADC1_CHANNEL_7))
    {
      // Determine GPIO
      gpio_num = static_cast<gpio_num_t>(adc_channel + 32);  // 32...39
      if(adc1_config_width(adc_bit_width)!=ESP_OK){
        ESP_LOGE(tag,"Could not set bit width for %d on ADC unit 1 to %d bits",adc_channel, adc_bit_width+9);
        //throw("Could not set bitwidth on ADC unit 1");
      }
    }else{
      ESP_LOGE(tag,"Invalid channel %d selected for ADC unit 1",adc_channel);
      //throw("Invalid channel selected for ADC unit 1");
    }
  } else {
    if(adc_unit==ADC_UNIT_2){      
      ESP_LOGW(tag,"Using this ADC unit %d will interfere with the WiFi!", adc_unit);
      // Determine GPIO
      switch(static_cast<int>(adc_unit)){
        case ADC2_CHANNEL_0: gpio_num=GPIO_NUM_0; break;
        case ADC2_CHANNEL_1: gpio_num=GPIO_NUM_2; break;
        case ADC2_CHANNEL_2: gpio_num=GPIO_NUM_4; break;
        case ADC2_CHANNEL_3: 
        case ADC2_CHANNEL_4: 
        case ADC2_CHANNEL_5: 
        case ADC2_CHANNEL_6: gpio_num=static_cast<gpio_num_t>(adc_unit+9); break; //12,13,14,15
        case ADC2_CHANNEL_7: 
        case ADC2_CHANNEL_8: 
        case ADC2_CHANNEL_9: gpio_num=static_cast<gpio_num_t>(adc_unit+18); break; //25,26,27
        default: 
          ESP_LOGE(tag,"Invalid channel %d selected for ADC unit 2",adc_channel);          
          //throw("Invalid channel selected for ADC unit 2");
      }
      if(adc1_config_width(adc_bit_width)!=ESP_OK){
        ESP_LOGE(tag,"Could not set bit width for %d on ADC unit 2 to %d bits.",adc_channel, adc_bit_width+9);
        //throw("Could not set bitwidth on ADC unit 2");
      }

    } else {
      ESP_LOGE(tag,"Invalid ADC unit %d specified",adc_unit);
      //throw("Invalid ADC unit specified");
    }
  }


  // update count
  AnalogInput::gpio_input_total_count++;

  // Set up text strings
  if(_name != NULL){ 
    name.append(_name);
  }else{
    name.append("ADCChannel_");
    name.append(std::to_string(adc_channel));
  }
  if(_desc!=NULL){
    desc.append(_desc);
  }else{
    std::stringstream ss;
    ss << "Connected to GPIO Pin " << std::to_string(gpio_num) << ", bit width: " << std::to_string(adc_bit_width+9);
    desc=ss.str();
  }

  // Launch single reading task for averaging all ADC readings
  if(AnalogInput::xSupervisorTaskHandle==0){
    xTaskCreate(AnalogInput::SupervisorTask,"AnalogInput::SupervisorTask",2048,NULL,10,&AnalogInput::xSupervisorTaskHandle);
  }
  
  ESP_LOGI(tag,"Created %s %s", name.c_str(), desc.c_str());
}

// Copy constructor
AnalogInput::AnalogInput(const AnalogInput &c){    
    adc_channel     = c.adc_channel;
    adc_unit        = c.adc_unit;
    adc_bit_width   = c.adc_bit_width;
    smoothed_value  = c.smoothed_value;
    now_time        = -1;    
    prev_time       = -1;
    name            = c.name;
    desc            = c.desc;
    strcpy(tag,c.tag);
    AnalogInput::gpio_input_total_count++;
}

// Destructor removes ISR
// Can't add logging and serial printing to ISR
AnalogInput::~AnalogInput(){
  if(AnalogInput::gpio_input_total_count==1){
    // last one - kill task off
    vTaskDelete(AnalogInput::xSupervisorTaskHandle);
  }
  AnalogInput::gpio_input_total_count--;
}


/*  Set attenuation for each channel according to these input voltage ranges
    +----------+------------+--------------------------+-------------------+
    |   SoC    | attenuation|   suggested range (mV)   | Symbol Value      |
    +==========+============+==========================+===================+
    |          |  0         |     100 ~ 950            | ADC_ATTEN_DB_0
    |   ESP32  |  2.5       |     100 ~ 1250           | ADC_ATTEN_DB_2_5
    |          |  6         |     150 ~ 1750           | ADC_ATTEN_DB_6
    |          |  11        |     150 ~ 2450           | ADC_ATTEN_DB_11
    +----------+------------+--------------------------+-------------------+
    |          |  0         |     100 ~ 800            | ADC_ATTEN_DB_0
    | ESP32-S2 |  2.5       |     100 ~ 1100           | ADC_ATTEN_DB_2_5
    |          |  6         |     150 ~ 1350           | ADC_ATTEN_DB_6
    |          |  11        |     150 ~ 2600           | ADC_ATTEN_DB_11
    +----------+------------+--------------------------+*------------------+*/
void AnalogInput::setAttenutation(adc_atten_t _adc_attenuation){
  if(adc_unit == ADC_UNIT_1){
    adc1_config_channel_atten(static_cast<adc1_channel_t>(adc_channel),_adc_attenuation);
  }else{
    adc2_config_channel_atten(static_cast<adc2_channel_t>(adc_channel),_adc_attenuation);
  }
  adc_attenuation = _adc_attenuation;
}

// Set bit with on the ADC Unit that this ADC Channel is on.
// This will affect all the other ADC Channels on this unit.
// adc_bit_width_BIT_9, adc_bit_width_BIT_10, adc_bit_width_BIT_11, adc_bit_width_BIT_12
void AnalogInput::setBitWidth(adc_bits_width_t _adc_bit_width ){
  if(adc_unit == ADC_UNIT_1 ){
    if(adc1_config_width(_adc_bit_width)!=ESP_OK){
      ESP_LOGE(tag,"Could not set bit width on ADC unit 1 to %d bits", _adc_bit_width+9);
      //throw("Could not set bit width on ADC unit 1");
    }
  }
  /*else{
    if(adc2_config_width(_adc_bit_width)!=ESP_OK){
      ESP_LOGE(tag,"Could not set bit width on ADC unit 2 to %d bits", _adc_bit_width+9);
      throw("Could not set bit  width on ADC unit 2");
    }
  }*/
  adc_bit_width=_adc_bit_width;
}

// Returns a value between 0 and 4096, regardless of the bit width.
// The value has been corrected using the 
// https://github.com/G6EJD/ESP32-ADC-Accuracy-Improvement-function
int AnalogInput::getInstantValue(){  
  int rawReading=0;
  int successful_samples=0;
  // Take 8 quick samples
  for(int sample=0;sample<8;sample++){
    if(adc_unit == ADC_UNIT_1){
      //rawReading=adc1_get_voltage(adc_channel);
      rawReading+=adc1_get_raw(static_cast<adc1_channel_t>(adc_channel));
      successful_samples++;
    }else{
      // rawReading=adc2_get_voltage(adc_channel);
      // Need to set attenuation every time we take a reading off ADC_UNIT_2
      adc2_config_channel_atten(static_cast<adc2_channel_t>(adc_channel), adc_attenuation);
      int sample_reading;
      int err=adc2_get_raw(static_cast<adc2_channel_t>(adc_channel), adc_bit_width, &sample_reading);
      switch(err){
        case ESP_OK:  
          rawReading+=sample_reading;
          successful_samples++;
          break;
        case ESP_ERR_TIMEOUT: 
          ESP_LOGE(tag,"ADC2 is used by WiFi. Defaulting to 0.");
          rawReading=0;
          break;
        default:
          ESP_LOGE(tag,"Read Error code %d. Defaulting to 0.", err);
          rawReading=0;
          break;      
      }    
    }
    vTaskDelay(10/portTICK_PERIOD_MS);  // 10 millisecond delay
  }
  rawReading /= successful_samples;

  // Scale up to 4096
  int shiftlefts=ADC_WIDTH_BIT_12-adc_bit_width;
  rawReading<<=shiftlefts;

  if(rawReading < 1 || rawReading > 4095) {
    ESP_LOGW(tag,"Out-of-range analog input value: %d. Check attenuation setting.", rawReading);
    return 0;
  }

  // Simple cubic spline correction
  // return -0.000000000009824 * pow(rawReading,3) + 0.000000016557283 * pow(rawReading,2) + 0.000854596860691 * rawReading + 0.065440348345433;
  // Complex quintic spline correction
  return static_cast<int>( -0.000000000000016 * std::pow(rawReading,4) + 0.000000000118171 * std::pow(rawReading,3)- 0.000000301211691 * std::pow(rawReading,2)+ 0.001109019271794 * rawReading + 0.034143524634089 );
}

// Task to continuously Sample all ADCs once per 1000 ms
void AnalogInput::SupervisorTask(void * arg) {
  // The Ticker runs at 100 ticks a second, e.g. 100ms = 10 ticks.  
  const TickType_t interval = (1000/portTICK_PERIOD_MS);
  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime = xTaskGetTickCount();  
  for( ;; ){
    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, interval);
    // Run supervisory action on all registered digital inputs
    for(std::map<adc_channel_t, AnalogInput*>::iterator it = instances.begin(); it != instances.end(); it++){
      AnalogInput* p = static_cast<AnalogInput*>(it->second);
      p->prev_time = p->now_time;
      p->now_time  = xLastWakeTime;
      double instant_value = p->getInstantValue();
      if(p->smoothed_value==0.0){
        p->smoothed_value = instant_value; // best starting point
      }else{
        p->smoothed_value += (p->smoothed_value-instant_value)/2.0;
      }
    }    
  }
}