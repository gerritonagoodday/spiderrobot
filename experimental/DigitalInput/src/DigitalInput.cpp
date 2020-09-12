#include "DigitalInput.h"

// Static members initialization
int64_t DigitalInput::gpio_input_mask = 0;
xQueueHandle DigitalInput::gpio_input_queue = NULL;
int64_t DigitalInput::gpio_input_isr_counter = 0;
const char * DigitalInput::TAG = "DigitalInput";
int DigitalInput::gpio_input_high_count=0;
int DigitalInput::gpio_input_total_count=0;


// Constructor
DigitalInput::DigitalInput(gpio_num_t _gpio_num, const char * _name, const char * _desc){
  // Create queue if it does not exist yet & set up interrupt service for the first time
  if(DigitalInput::gpio_input_queue == NULL ){
    DigitalInput::gpio_input_queue = xQueueCreate(10, sizeof(void *));
    // install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  }

  // instrumentation
  gpio_num = _gpio_num;
  name     = _name;
  desc     = _desc;
  self     = nullptr;
  // state controll
  now_state  = -1;
  now_time   = -1;
  last_state = -1;
  last_time  = -1;  
  settled    = false;  
  // Add to mask
  gpio_input_mask |= (1ULL<<gpio_num);
  // Change interrupt type for this gpio
  gpio_set_intr_type(gpio_num, GPIO_INTR_ANYEDGE);
  // First remove any old handlers for this gpio
  gpio_isr_handler_remove(gpio_num);
  // Add new ISR handler
  gpio_isr_handler_add(gpio_num, DigitalInput::ISR, static_cast<void*>(this));


  // Set INPUT Pins:
  // ~~~~~~~~~~~~~~~
  gpio_config_t io_conf;
  //interrupt of rising edge
  io_conf.intr_type = GPIO_INTR_POSEDGE;
  //bit mask of the pins
  io_conf.pin_bit_mask = DigitalInput::gpio_input_mask;
  //set as input mode    
  io_conf.mode = GPIO_MODE_INPUT;
  //enable pull-up mode
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  // OK to call this for every new GPIO that is called as long as 
  // gpio_input_mask contains all previously-defined 
  gpio_config(&io_conf); 

  // update count
  DigitalInput::gpio_input_total_count++;
  
  // Set up logging tag
  s_tag=TAG+'_'+std::to_string(gpio_num);
  tag=s_tag.c_str();
  
  ESP_LOGI(tag,"Created %s %s", name.c_str(), desc.c_str());
}

// Copy constructor
DigitalInput::DigitalInput(const DigitalInput &c){    
    gpio_num   = c.gpio_num;
    now_state  = c.now_state;
    now_time   = c.now_time;
    last_state = last_state;
    last_time  = last_time;
    name       = name;
    desc       = desc;
    s_tag      = s_tag;
    tag        = s_tag.c_str();
    settled    = false;
    self       = nullptr;
}

// Destructor removes ISR
// Can't add logging and serial printing to ISR
DigitalInput::~DigitalInput(){
  gpio_isr_handler_remove(gpio_num);
}

// On settingling time, check if rising or falling edges were correctly detected
void DigitalInput::CheckOnSettleTime(){
  int64_t _now_time = esp_timer_get_time();
  if(settled == false){
    if(_now_time - now_time > GPIO_INPUT_DEBOUNCE_SETTLE_TIME){
      this->settled = true;
      int _now_state = gpio_get_level(gpio_num);
      if( now_state != _now_state){
        now_state =  _now_state;                    
        now_time  =  _now_time;                    
        xQueueSendToBack(DigitalInput::gpio_input_queue, (void*)&self, 0);
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
  DigitalInput * p = reinterpret_cast<DigitalInput*>(arg);
  DigitalInput::gpio_input_isr_counter++;

  p->settled = false;
  // Get current state
  int _now_state = gpio_get_level(p->gpio_num);
  if( _now_state != p->now_state ){
    // We are in a new state, check if debounce timer has expired
    p->now_time = esp_timer_get_time();
    if( ((p->now_state == 0) && // old state is digital LOW, compare to release time
          (p->now_time - p->last_time > GPIO_INPUT_DEBOUNCE_RELEASE_TIME)) 
      ||
        ((p->now_state == 1) && // old state is digital HIGH, compare to depress time
          (p->now_time - p->last_time > GPIO_INPUT_DEBOUNCE_DEPRESS_TIME)) 
      ){
      // Accept state, set state for next time
      p->last_time  = p->now_time;
      p->last_state = _now_state;
      p->now_state  = _now_state;
      // Publish result
      if(xQueueSendToBackFromISR(DigitalInput::gpio_input_queue, &p, 0) != pdTRUE){
        ESP_LOGW(DigitalInput::TAG,"Failed to add item to gpio_input_queue");
      }
      
    }
  }
}



