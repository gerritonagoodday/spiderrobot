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


//#include <Wire.h>

const char TAG[] = "HELLO";

#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2/GxEPD2_BW.h> 
#include <Fonts/FreeMonoBold9pt7b.h>


int a = gpio_get_level();



// copy constructor for your e-paper from GxEPD2_Example.ino, and for AVR needed #defines
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ 5, /*DC=*/ 22, /*RST=*/ 21, /*BUSY=*/ 4));

extern "C" {
  <port.c>;
  void app_main(void);
  void helloWorld();
}


const char HelloWorld[] = "Hello World!";


void app_main(void){
  ESP_LOGI(TAG, "Setting up..");
  display.init();
  helloWorld();
  display.hibernate();
  for(;;){
    ESP_LOGI(TAG, "In loop..");
    vTaskDelay(100);
  }
}


void helloWorld()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }

  while (display.nextPage());
}


