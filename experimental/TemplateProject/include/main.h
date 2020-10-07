#ifndef _MAIN_H_
#define _MAIN_H_


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