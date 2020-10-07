// Based on the example code  in 
// 

#include "AnalogOutput.h"

// Static members initialization
//int64_t AnalogOutput::gpio_output_mask = 0;
const char * AnalogOutput::TAG = "DAC";
int AnalogOutput::gpio_output_total_count=0;
std::map<dac_channel_t, AnalogOutput*> AnalogOutput::instances;

//dac_output_enable(DAC_CHANNEL_1);
//dac_output_voltage(DAC_CHANNEL_1, 200);
//DAC_CHANNEL_1_GPIO_NUM is the GPIO number of channel 1 (GPIO25);

// Constructor
AnalogOutput::AnalogOutput(dac_channel_t _dac_num, const char * _name, const char * _desc):  
  dac_num(_dac_num)  // instrumentation
{
  // Self registration to a map of all other class instances like this
  instances[dac_num] = this;

  name.append(_name);
  desc.append(_desc);

  // state controll
  now_value  = 0;
  prev_value = 0;
  now_time   = -1;
  prev_time  = -1;  
  

  // First remove any old handlers for this gpio
  
  //esp_err_t err = dac_output_enable();

  // Set OUTPUT Pins:
  // ~~~~~~~~~~~~~~~
  //gpio_config_t io_conf;
  //interrupt on rising edge  and on falling edge
  //io_conf.intr_type = GPIO_INTR_ANYEDGE; // GPIO_INTR_POSEDGE;
  // Add to Input mask
  //AnalogOutput::gpio_output_mask |= (1ULL<<gpio_num);
  // bit mask of the pins
  //io_conf.pin_bit_mask = AnalogOutput::gpio_output_mask;
  // set as input mode    
  //io_conf.mode = GPIO_MODE_INPUT;
  // enable pull-up mode
  //io_conf.pull_up_en   = GPIO_PULLUP_ENABLE;
  //io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  // OK to call this for every new GPIO that is called as long as 
  // gpio_input_mask contains all previously-defined input
  //gpio_config(&io_conf); 


  // update count
  AnalogOutput::gpio_output_total_count++;
  
  // Set up logging tag, e.g. DIN_36
  s_tag.append(AnalogOutput::TAG);
  s_tag.append("_");
  s_tag.append(std::to_string(dac_num));
  tag=s_tag.c_str();
  ESP_LOGI(tag,"Created %s %s on Pin %u", name.c_str(), desc.c_str(), dac_num);
}

// Copy constructor
AnalogOutput::AnalogOutput(const AnalogOutput &c){    
    dac_num   = c.dac_num;
    now_value  = 0;
    prev_value = 0;
    now_time   = -1;    
    prev_time  = -1;
    name       = name;
    desc       = desc;
    s_tag      = s_tag;
    tag        = s_tag.c_str();    
    AnalogOutput::gpio_output_total_count++;
}

// Destructor removes ISR
// Can't add logging and serial printing to ISR
AnalogOutput::~AnalogOutput(){
  
}

// Sets a the value between 0 and 255 to the analog output.
// 0 = 0V, 255 = 3.3V (usually)
void AnalogOutput::setValue(int value){
  // Clamp input value to ranges
  if(value > 255){
    ESP_LOGW(tag, "Input value of %d is too high for 0-255 range.", value);
    now_value = 255;
  } else {
    if( value < 0){
      ESP_LOGW(tag, "Input value of %d is too low for 0-255 range.", value);
      now_value = 0;
    }
  }

}
