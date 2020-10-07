// Based on the exampole code  in 
// https://github.com/espressif/esp-idf/blob/8bc19ba893e5544d571a753d82b44a84799b94b1/examples/peripherals/gpio/main/gpio_example_main.c

#include "DigitalInput.h"

// Static members initialization
int64_t DigitalInput::gpio_input_mask = 0;
xQueueHandle DigitalInput::gpio_input_queue = NULL;
int64_t DigitalInput::gpio_input_isr_counter = 0;
const char * DigitalInput::TAG = "DIN";
int DigitalInput::gpio_input_high_count=0;
int DigitalInput::gpio_input_total_count=0;
TaskHandle_t DigitalInput::xSupervisorTaskHandle=0;
std::map<gpio_num_t, DigitalInput*> DigitalInput::instances;

// Constructor
DigitalInput::DigitalInput(gpio_num_t _gpio_num, const char * _name, const char * _desc):  
  gpio_num(_gpio_num)  // instrumentation
{
  // Create queue if it does not exist yet & set up interrupt service for the first time
  if(DigitalInput::gpio_input_queue == NULL ){
    ESP_LOGW(DigitalInput::TAG,"Creating input queue");
    DigitalInput::gpio_input_queue = xQueueCreate(10, sizeof(void *));
    // install gpio isr service    
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    // Create settling task to supervise all digital inputs
    xTaskCreate(DigitalInput::SupervisorTask,"DigitalInput::SupervisorTask",2048,NULL,10,&DigitalInput::xSupervisorTaskHandle);
  }

  // Self registration to a map of all other class instances like this
  instances[_gpio_num] = this;

  name.append(_name);
  desc.append(_desc);

  // state controll
  now_state  = 0;
  prev_state = 0;
  now_time   = -1;
  prev_time  = -1;  
  settled    = false;  

  // First remove any old handlers for this gpio
  gpio_isr_handler_remove(gpio_num);

  // Set INPUT Pins:
  // ~~~~~~~~~~~~~~~
  gpio_config_t io_conf;
  //interrupt on rising edge  and on falling edge
  io_conf.intr_type = GPIO_INTR_ANYEDGE; // GPIO_INTR_POSEDGE;
  // Add to Input mask
  DigitalInput::gpio_input_mask |= (1ULL<<gpio_num);
  // bit mask of the pins
  io_conf.pin_bit_mask = DigitalInput::gpio_input_mask;
  // set as input mode    
  io_conf.mode = GPIO_MODE_INPUT;
  // enable pull-up mode
  io_conf.pull_up_en   = GPIO_PULLUP_ENABLE;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  // OK to call this for every new GPIO that is called as long as 
  // gpio_input_mask contains all previously-defined input
  gpio_config(&io_conf); 

  // Change interrupt type for this gpio  
  gpio_set_intr_type(gpio_num, GPIO_INTR_ANYEDGE);
  // Add new ISR handler
  gpio_isr_handler_add(gpio_num, DigitalInput::ISR, static_cast<void*>(this));


  // update count
  DigitalInput::gpio_input_total_count++;
  
  // Set up logging tag, e.g. DIN_36
  s_tag.append(DigitalInput::TAG);
  s_tag.append("_");
  s_tag.append(std::to_string(gpio_num));
  tag=s_tag.c_str();
  ESP_LOGI(tag,"Created %s %s on Pin %u", name.c_str(), desc.c_str(), gpio_num);
}

// Copy constructor
DigitalInput::DigitalInput(const DigitalInput &c){    
    gpio_num   = c.gpio_num;
    now_state  = 0;
    prev_state = 0;
    now_time   = -1;    
    prev_time  = -1;
    name       = name;
    desc       = desc;
    s_tag      = s_tag;
    tag        = s_tag.c_str();    
    settled    = false;
    //self       = nullptr;
    DigitalInput::gpio_input_total_count++;
}

// Destructor removes ISR
// Can't add logging and serial printing to ISR
DigitalInput::~DigitalInput(){
  gpio_isr_handler_remove(gpio_num);
}

// On settingling time, check if rising or falling edges were correctly detected
void DigitalInput::CheckOnSettleTime(){
  //assert(("This class-instance has not been assigned to member 'self'.",self!=NULL));
  int64_t _now_time = esp_timer_get_time();
  if(settled == false){
    if(_now_time - now_time > GPIO_INPUT_DEBOUNCE_SETTLE_TIME){
      this->settled = true;
      int _now_state = gpio_get_level(gpio_num);
      if( now_state != _now_state){
        ESP_LOGW(tag,"Noisy input signal. Correcting level on settle of GPIO %d.",gpio_num);
        now_state =  _now_state;                    
        now_time  =  _now_time;   
        // Update tally
        if(_now_state == 0){
          gpio_input_high_count--;
          if(gpio_input_high_count<0){
            ESP_LOGW(tag,"Very noisy input signal. Had to clamp # of high states from %d to 0.", gpio_input_high_count);
            gpio_input_high_count=0;
          }
        }else{
          gpio_input_high_count++;
          if(gpio_input_high_count>gpio_input_total_count){
            ESP_LOGW(tag,"Very noisy input signal. Had to clamp # of high states from %d to %d.",gpio_input_high_count, gpio_input_total_count);
            gpio_input_high_count=gpio_input_total_count;
          }
        }
        // Publish correction
        DigitalInput * p = this;
        xQueueSendToBack(DigitalInput::gpio_input_queue, (void*)&p, 0);
      }
    }
  }
}
  
// Interrupt Service Routine - Passed in as argument is "this" class,
// which is accessed as follows: DigitalInput * p = reinterpret_cast<DigitalInput*>(arg);
// This ISR is shared by all Digital inputs of ths class
// Does debouncing of inputs before passing the state onto the message queue
// Since we are not using ESP_INTR_FLAG_IRAM, no need for IRAM_ATTR
void DigitalInput::ISR(void* arg){   
  // xQueueSendToBackFromISR(DigitalInput::gpio_input_queue,&arg,0); // simple form with no debouncing
  
  // Get current state ASAP
  DigitalInput * p = static_cast<DigitalInput*>(arg);
  int _now_state = gpio_get_level(p->gpio_num);
  
  DigitalInput::gpio_input_isr_counter++;  
  p->settled = false;

  if( _now_state != p->now_state ){
    // CHANGE OF STATE! Check if debounce timer has expired
    p->now_time = esp_timer_get_time();  
    if( 
        ((p->now_state == 0) && // old state is digital LOW, e.g. we are releasing the switch, compare to depress time
         (p->now_time - p->prev_time > GPIO_INPUT_DEBOUNCE_DEPRESS_TIME)) 
        ||
        ((p->now_state == 1) && // old state is digital HIGH, e.g. we are releasing the switch, compare to release time
         (p->now_time - p->prev_time > GPIO_INPUT_DEBOUNCE_RELEASE_TIME))
      )
    {
      // Accept state, set state for next time
      p->prev_time  = p->now_time;
      p->prev_state = p->now_state;
      p->now_state  = _now_state;
      
      // Update count of high states and clamp 
      if(_now_state == 0){
        gpio_input_high_count--; 
        if(gpio_input_high_count<0){
          gpio_input_high_count=0;
        }
      }else{
        gpio_input_high_count++;
        if(gpio_input_high_count>gpio_input_total_count){
          gpio_input_high_count=gpio_input_total_count;
        }
      }

      // Publish result
      xQueueSendToBackFromISR(DigitalInput::gpio_input_queue, static_cast<void*>(&p), 0);
    }
  }
}

// Supervisor task for digital inputs
// Since the inputs responses are measured at at accuracy of no less than 20ms for close
// transition and 200ms for open transition, and the settling time for a transition is 400ms,
// a sampling interval at 100ms is sufficient to to double-check the state of noisy inputs
void DigitalInput::SupervisorTask(void * arg){  
  // The Ticker runs at 100 ticks a second, e.g. 100ms = 10 ticks.  
  const TickType_t interval = 10;
  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for( ;; )  {
    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, interval);
    // Run supervisory action on all registered digital inputs
    for(std::map<gpio_num_t, DigitalInput*>::iterator it = instances.begin(); it != instances.end(); it++){        
      DigitalInput* p = static_cast<DigitalInput*>(it->second);      
      p->CheckOnSettleTime();
    }
  }
}