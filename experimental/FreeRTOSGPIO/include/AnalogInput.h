#ifndef _ANALOG_INPUT_H_
#define _ANALOG_INPUT_H_

#include <map>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_timer.h"
#include "freertos/projdefs.h"


#define ESP_INTR_FLAG_DEFAULT 0

#define GPIO_INPUT_DEBOUNCE_DEPRESS_TIME     20000   // 20ms depress
#define GPIO_INPUT_DEBOUNCE_RELEASE_TIME     200000  // 200ms release
#define GPIO_INPUT_DEBOUNCE_SETTLE_TIME      400000  // 400ms settle


class AnalogInput {
  public:      
    AnalogInput(adc_channel_t _adc_channel,
      adc_unit_t _adc_unit,
      adc_bits_width_t _adc_bit_width, 
      const char * _name , const char * _desc);
    AnalogInput(const AnalogInput &c);
    ~AnalogInput();

    // Configuration   
    adc_channel_t adc_channel;        // ADC1_CHANNEL_0...ADC1_CHANNEL_7 & ADC2_CHANNEL_0...ADC2_CHANNEL_9
    adc_unit_t adc_unit;              // 12-bit ADC Converter, ADC_UNIT_1 (GPIO 32-39) or ADC_UNIT_2 (GPIO 0,2,4,12,13,14,15,25,26,27)    
    adc_atten_t adc_attenuation;      // Attenuation in DB, ADC_ATTEN_DB_0,ADC_ATTEN_DB_2_5,ADC_ATTEN_DB_6,ADC_ATTEN_DB_11
    adc_bits_width_t adc_bit_width;  // adc_bit_width_BIT_9, adc_bit_width_BIT_10, adc_bit_width_BIT_11, adc_bit_width_BIT_12
    gpio_num_t gpio_num;              // This is for reverse lookup on the hardware design
    std::string name;
    std::string desc;    

    // Interrupt payload:
    double  smoothed_value;    
    int64_t now_time;    
    int64_t prev_time;    

    int getInstantValue();
    double getValue(){return smoothed_value;}
    adc_channel_t getADCChannel(){return adc_channel;} 
    void setBitWidth(adc_bits_width_t _adc_bit_width );
    void setAttenutation(adc_atten_t _adc_attenuation);

    // These statics would normally be declared as inline for C++17, but for now we declare them 
    // in the cpp file until the ESP compiler supports this standard. Then add this to file
    // platformio.ini: build_flags = -std=c++17    
    static int gpio_input_total_count; // number of input classes defined
    static std::map<adc_channel_t, AnalogInput*> instances;
    
    static const char  TAG[4];        // Logging for all classes        
    char tag[8];                      // Logging for each class instance    

    // Supervisor task
    static TaskHandle_t xSupervisorTaskHandle;
    static void SupervisorTask(void * arg);

};

#endif // _ANALOG_INPUT_H_