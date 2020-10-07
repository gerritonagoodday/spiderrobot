#ifndef _ANALOG_OUTPUT_H_
#define _ANALOG_OUTPUT_H_

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
#include "driver/dac.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/projdefs.h"


class AnalogOutput {
  public:
    AnalogOutput(dac_channel_t _channel_num, const char * _name, const char * _desc);        
    AnalogOutput(const AnalogOutput &c);
    ~AnalogOutput();

    // Configuration    
    dac_channel_t dac_num;
    std::string name;
    std::string desc;    

    // Interrupt payload:
    int     now_value;
    int64_t now_time;
    int     prev_value;
    int64_t prev_time;
    
    void setValue(int value);
    dac_channel_t getGPIONum(){return dac_num;}

    // These statics would normally be declared as inline for C++17, but for now we declare them 
    // in the cpp file until the ESP compiler supports this standard. Then add this to file
    // platformio.ini: build_flags = -std=c++17    
    static int gpio_output_total_count; // number of input classes defined
    static std::map<dac_channel_t, AnalogOutput*> instances;

    // Logging for all classes
    std::string s_tag;
    static const char * TAG;
    // Logging for each class instance    
    const char * tag;   
};

#endif // _ANALOG_OUTPUT_H_
