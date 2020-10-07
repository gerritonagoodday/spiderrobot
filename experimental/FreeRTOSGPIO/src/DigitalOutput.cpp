// Based on the example code  in 
// https://github.com/espressif/esp-idf/blob/8bc19ba893e5544d571a753d82b44a84799b94b1/examples/peripherals/gpio/main/gpio_example_main.c

#include "DigitalOutput.h"

// Static members initialization
int64_t DigitalOutput::gpio_output_mask = 0;
const char * DigitalOutput::TAG = "DOUT";
int DigitalOutput::gpio_output_high_count=0;
int DigitalOutput::gpio_output_total_count=0;
std::map<gpio_num_t, DigitalOutput*> DigitalOutput::instances;

// Constructor
DigitalOutput::DigitalOutput(gpio_num_t _gpio_num, const char * _name, const char * _desc):  
  gpio_num(_gpio_num)  // instrumentation
{
  // Self registration to a map of all other class instances like this
  instances[_gpio_num] = this;

  name.append(_name);
  desc.append(_desc);

  // state controll
  now_state  = 0;
  prev_state = 0;
  now_time   = -1;
  prev_time  = -1;  

  // Set OUTPUT Pins:
  // ~~~~~~~~~~~~~~~~
  gpio_config_t io_conf;
  //interrupt on rising edge  and on falling edge
  io_conf.intr_type = GPIO_INTR_DISABLE; // GPIO_INTR_POSEDGE;
  // Add to Input mask
  DigitalOutput::gpio_output_mask |= (1ULL<<gpio_num);
  // bit mask of the pins
  io_conf.pin_bit_mask = DigitalOutput::gpio_output_mask;
  // set as input mode    
  io_conf.mode = GPIO_MODE_OUTPUT;
  // enable pull-up mode
  io_conf.pull_up_en   = GPIO_PULLUP_DISABLE;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  // OK to call this for every new GPIO that is called as long as 
  // gpio_input_mask contains all previously-defined input
  gpio_config(&io_conf); 

  // update count
  DigitalOutput::gpio_output_total_count++;
  
  // Set up logging tag, e.g. DOUT_02
  s_tag.append(DigitalOutput::TAG);
  s_tag.append("_");
  s_tag.append(std::to_string(gpio_num));
  tag=s_tag.c_str();
  ESP_LOGI(tag,"Created %s %s on Pin %02u", name.c_str(), desc.c_str(), gpio_num);
}

// Copy constructor
DigitalOutput::DigitalOutput(const DigitalOutput &c){    
    gpio_num   = c.gpio_num;
    now_state  = 0;
    prev_state = 0;
    now_time   = -1;    
    prev_time  = -1;
    name       = name;
    desc       = desc;
    s_tag      = s_tag;
    tag        = s_tag.c_str();            
    DigitalOutput::gpio_output_total_count++;
}

// Destructor removes ISR
// Can't add logging and serial printing to ISR
DigitalOutput::~DigitalOutput(){
  gpio_isr_handler_remove(gpio_num);
}

void DigitalOutput::setState(bool state){
  gpio_set_level(gpio_num, state);
  prev_state = now_state;
  prev_time = now_time;
  now_state=state;
  now_time = esp_timer_get_time();
}

bool DigitalOutput::getState(){
  return now_state;
}