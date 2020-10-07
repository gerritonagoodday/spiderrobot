#ifndef _WHITEPAPERDISPLAY_H_
#define _WHITEPAPERDISPLAY_H_

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

class WhitepaperDisplay {
  public:
    WhitepaperDisplay();
    ~WhitepaperDisplay();
  
    std::string s_tag;
    const char * TAG;


};



#endif    // _WHITEPAPERDISPLAY_H_