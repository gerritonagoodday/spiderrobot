#ifndef _DIGITAL_OUTPUT_H_
#define _DIGITAL_OUTPUT_H_

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


class DigitalOutput {
  public:
    DigitalOutput(gpio_num_t _gpio_num, const char * _name, const char * _desc);        
    DigitalOutput(const DigitalOutput &c);
    ~DigitalOutput();

    // Configuration    
    gpio_num_t gpio_num;
    std::string name;
    std::string desc;    

    // State history
    int     now_state;
    int64_t now_time;
    int     prev_state;
    int64_t prev_time;

    void setState(bool state);
    bool getState();
    uint getGPIONum(){return gpio_num;}

    // These statics would normally be declared as inline for C++17, but for now we declare them 
    // in the cpp file until the ESP compiler supports this standard. Then add this to file
    // platformio.ini: build_flags = -std=c++17
    static int64_t gpio_output_mask;
    
    static int gpio_output_high_count;
    static int gpio_output_total_count; // number of input classes defined
    static std::map<gpio_num_t, DigitalOutput*> instances;

    // Logging for all classes
    std::string s_tag;
    static const char * TAG;
    // Logging for each class instance    
    const char * tag;
};

#endif // _DIGITAL_OUTPUT_H_
