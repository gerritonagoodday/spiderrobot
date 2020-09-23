#include "main.h"


//#include "SmartLeds.h"
//#include "Color.h"

//#include "SPI.h"

// #include "U8g2_for_Adafruit_GFX.h"
// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
// #include <GFX.h>

//#define ENABLE_GxEPD2_GFX 0
//#include <GxEPD2_BW.h>
#include "Fonts/FreeMonoBold9pt7b.h"
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#define MAX_DISPLAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));


#include "GxEPD2_290.h"

const char TAG[] = "EPAPER";

const char HelloWorld[] = "Hello World!";
void helloWorld();

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


void app_main(void) {
  display.init();
  helloWorld();
  display.hibernate();

  for(;;){
    ESP_LOGI(TAG,"In main...");
    vTaskDelay(100);

  }
}








