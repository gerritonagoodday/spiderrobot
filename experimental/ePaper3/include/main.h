#ifndef _MAIN_H_
#define _MAIN_H_



/// For u8g_MicroDelay in u8g_delay.cpp since usleep is not defined here
// #define usleep  delayMicroseconds


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

extern "C" {
  void app_main(void);
}

#endif // _MAIN_H_