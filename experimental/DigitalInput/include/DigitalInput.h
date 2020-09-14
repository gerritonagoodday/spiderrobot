#ifndef _DIGITAL_INPUT_H_
#define _DIGITAL_INPUT_H_

#include <map>
#include <assert.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/projdefs.h"


#define ESP_INTR_FLAG_DEFAULT 0

#define GPIO_INPUT_DEBOUNCE_DEPRESS_TIME     20000   // 20ms depress
#define GPIO_INPUT_DEBOUNCE_RELEASE_TIME     200000  // 200ms release
#define GPIO_INPUT_DEBOUNCE_SETTLE_TIME      400000  // 400ms settle


class DigitalInput {
  public:
    DigitalInput(gpio_num_t _gpio_num, const char * _name, const char * _desc);        
    DigitalInput(const DigitalInput &c);
    ~DigitalInput();

    // Configuration    
    gpio_num_t gpio_num;
    std::string name;
    std::string desc;
    DigitalInput * self;

    // Interrupt payload:
    int     now_state;
    int64_t now_time;
    int     prev_state;
    int64_t prev_time;
    bool    settled;

    // These statics would normally be declared as inline for C++17, but for now we declare them 
    // in the cpp file until the ESP compiler supports this standard. Then add this to file
    // platformio.ini: build_flags = -std=c++17
    static int64_t gpio_input_mask;
    static xQueueHandle gpio_input_queue;
    static int64_t gpio_input_isr_counter;
    static int gpio_input_high_count;
    static int gpio_input_total_count; // number of input classes defined
    //static std::map<gpio_num_t, DigitalInput*> instances;

    // Logging for all classes
    std::string s_tag;
    static const char * TAG;
    // Logging for each class instance    
    const char * tag;
    
    // Interrupt Service Routine - Passed in as argument is "this" class,
    // which is accessed as follows: DigitalInput * p = reinterpret_cast<DigitalInput*>(arg);
    static void ISR(void* arg);

    void CheckOnSettleTime();
};

#endif // _DIGITAL_INPUT_H_