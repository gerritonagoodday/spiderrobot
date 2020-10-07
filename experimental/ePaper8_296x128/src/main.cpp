#include <Arduino.h>

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

#define ENABLE_GxEPD2_GFX 0

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
// Note: if you use this with ENABLE_GxEPD2_GFX 1:
//       uncomment it in GxEPD2_GFX.h too, or add #include <GFX.h> before any #include <GxEPD2_GFX.h>

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ 17, /*DC=*/ 16, /*RST=*/ 5, /*BUSY=*/ 19));

#define MAX_DISPLAY_BUFFER_SIZE 15000ul // ~15k is a good compromise
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))

// comment out unused bitmaps to reduce code space used
#include "bitmaps/Bitmaps200x200.h" // 1.54" b/w
#include "bitmaps/Bitmaps128x250.h" // 2.13" b/w
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps176x264.h" // 2.7"  b/w
#include "bitmaps/Bitmaps400x300.h" // 4.2"  b/w
#include "bitmaps/Bitmaps640x384.h" // 7.5"  b/w


void helloWorldCallback(const void*)
{
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 2;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println("Hello World!");
}

void helloWorld()
{
  //Serial.println("helloWorld");
  //uint16_t x = (display.width() - 160) / 2;
  //uint16_t y = display.height() / 2;
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.drawPaged(helloWorldCallback, 0);
  //Serial.println("helloWorld done");
}

void helloFullScreenPartialModeCallback(const void*)
{
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 2;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println("Hello World!");
  y = display.height() / 4;
  display.setCursor(x, y);
  display.println("full screen");
  y = display.height() * 3 / 4;
  if (display.width() <= 200) x = 0;
  display.setCursor(x, y);
  if (display.epd2.hasFastPartialUpdate)
  {
    display.println("fast partial mode");
  }
  else if (display.epd2.hasPartialUpdate)
  {
    display.println("slow partial mode");
  }
  else
  {
    display.println("no partial mode");
  }
}

void helloFullScreenPartialMode()
{
  //Serial.println("helloFullScreenPartialMode");
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.drawPaged(helloFullScreenPartialModeCallback, 0);
  //Serial.println("helloFullScreenPartialMode done");
}

void helloArduinoCallback(const void*)
{
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 4;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println("Hello Arduino!");
}

void helloArduino()
{
  //Serial.println("helloArduino");
  //uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() / 4;
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.drawPaged(helloArduinoCallback, 0);
  delay(1000);
  //Serial.println("helloArduino done");
}

void helloEpaperCallback(const void*)
{
  uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() * 3 / 4;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println("Hello E-Paper!");
}

void helloEpaper()
{
  //Serial.println("helloEpaper");
  //uint16_t x = (display.width() - 160) / 2;
  uint16_t y = display.height() * 3 / 4;
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.drawPaged(helloEpaperCallback, 0);
  //Serial.println("helloEpaper done");
}

struct DrawFontParameters
{
  const char* name;
  const GFXfont* f;
};

void drawFontCallback(const void* parameters)
{
  const DrawFontParameters* p = reinterpret_cast<const DrawFontParameters*>(parameters);
  //display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(p->f);
  display.setCursor(0, 0);
  display.println();
  display.println(p->name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
  if (display.epd2.hasColor)
  {
    display.setTextColor(GxEPD_RED);
  }
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
}


void showFont(const char name[], const GFXfont* f)
{
  DrawFontParameters fontParameters{name, f};
  display.setFullWindow();
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.drawPaged(drawFontCallback, &fontParameters);
}


struct ShowBoxParameters
{
  uint16_t x, y, w, h;
  uint16_t color;
};

struct ShowValueParameters
{
  uint16_t x, y, w, h, cursor_y;
  float value;
};

void showBoxCallback(const void* parameters)
{
  const ShowBoxParameters* p = reinterpret_cast<const ShowBoxParameters*>(parameters);
  display.fillRect(p->x, p->y, p->w, p->h, p->color);
}

void showValueBoxCallback(const void* parameters)
{
  const ShowValueParameters* p = reinterpret_cast<const ShowValueParameters*>(parameters);
  display.fillRect(p->x, p->y, p->w, p->h, GxEPD_WHITE);
  display.setCursor(p->x, p->cursor_y);
  display.print(p->value);
}

void showPartialUpdate()
{
  // some useful background
  helloWorld();
  // use asymmetric values for test
  ShowBoxParameters boxParameters{10, 15, 70, 20, GxEPD_WHITE};
  ShowValueParameters valueParameters{10, 15, 70, 20, 14}; // 13.95};
  valueParameters.cursor_y = valueParameters.y + valueParameters.h - 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(boxParameters.x, boxParameters.y, boxParameters.w, boxParameters.h);
    boxParameters.color = GxEPD_BLACK;
    display.drawPaged(showBoxCallback, &boxParameters);
    delay(2000);
    boxParameters.color = GxEPD_WHITE;
    display.drawPaged(showBoxCallback, &boxParameters);
    while (display.nextPage());
    delay(1000);
  }
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(boxParameters.x, boxParameters.y, boxParameters.w, boxParameters.h);
    for (uint16_t i = 1; i <= 10; i += incr)
    {
      valueParameters.value = value * i;
      display.drawPaged(showValueBoxCallback, &valueParameters);
      delay(500);
    }
    delay(1000);
    boxParameters.color = GxEPD_WHITE;
    display.drawPaged(showBoxCallback, &boxParameters);
    delay(1000);
  }
}

void showBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial)
{
  //Serial.println("showBox");
  ShowBoxParameters boxParameters{x, y, w, h, GxEPD_BLACK};
  display.setRotation(1);
  if (partial)
  {
    display.setPartialWindow(x, y, w, h);
  }
  else
  {
    display.setFullWindow();
  }
  display.drawPaged(showBoxCallback, &boxParameters);
  //Serial.println("showBox done");
}

void drawCornerTestCallback(const void*)
{
  display.fillScreen(GxEPD_WHITE);
  display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
  display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
  display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
  display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);
  display.setCursor(display.width() / 2, display.height() / 2);
  display.print(display.getRotation());
}

void drawCornerTest()
{
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  for (uint16_t r = 0; r <= 4; r++)
  {
    display.setRotation(r);
    display.drawPaged(drawCornerTestCallback, 0);
    delay(2000);
  }
}

void drawInvertedBitmapCallback(const void* parameter)
{
  const uint8_t* bitmap = reinterpret_cast<const uint8_t*>(parameter);
  display.fillScreen(GxEPD_WHITE);
  display.drawInvertedBitmap(0, 0, bitmap, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
}




#ifdef _GxBitmaps128x250_H_
void drawBitmaps128x250()
{
  const unsigned char* bitmaps[] =
  {
    Bitmap128x250_1, logo128x250, first128x250, second128x250, third128x250
  };
  if (display.epd2.panel == GxEPD2::GDE0213B1)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
    display.mirror(m);
  }
}
#endif

#ifdef _GxBitmaps128x296_H_
void drawBitmaps128x296()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296, first128x296, second128x296, third128x296
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296 //, first128x296, second128x296, third128x296
  };
#endif
  if (display.epd2.panel == GxEPD2::GDEH029A1)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
    display.mirror(m);
  }
}
#endif

#ifdef _GxBitmaps176x264_H_
void drawBitmaps176x264()
{
  const unsigned char* bitmaps[] =
  {
    Bitmap176x264_1, Bitmap176x264_2
  };
  if (display.epd2.panel == GxEPD2::GDEW027W3)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps400x300_H_
void drawBitmaps400x300()
{
  const unsigned char* bitmaps[] =
  {
    Bitmap400x300_1, Bitmap400x300_2
  };
  if (display.epd2.panel == GxEPD2::GDEW042T2)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps640x384_H_
void drawBitmaps640x384()
{
  const unsigned char* bitmaps[] =
  {
    Bitmap640x384_1, Bitmap640x384_2
  };
  if (display.epd2.panel == GxEPD2::GDEW075T8)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
  }
}
#endif

#ifdef _GxBitmaps200x200_H_
void drawBitmaps200x200()
{
#if defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    logo200x200, first200x200 //, second200x200, third200x200, fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200
  };
#else
  const unsigned char* bitmaps[] =
  {
    logo200x200, first200x200, second200x200, third200x200, fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200
  };
#endif
  if ((display.epd2.panel == GxEPD2::GDEP015OC1) || (display.epd2.panel == GxEPD2::GDEH0154D67))
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawPaged(drawInvertedBitmapCallback, bitmaps[i]);
      delay(2000);
    }
    display.mirror(m);
  }
  //else
  {
    bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
    display.clearScreen(); // use default for white
    uint16_t x = (display.epd2.WIDTH - 200) / 2;
    uint16_t y = (display.epd2.HEIGHT - 200) / 2;
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.drawImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      delay(2000);
    }
  }
  bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
  for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
  {
    int16_t x = -60;
    int16_t y = -60;
    for (uint16_t j = 0; j < 10; j++)
    {
      display.writeScreenBuffer(); // use default for white
      display.writeImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      display.refresh(true);
      if (display.epd2.hasFastPartialUpdate)
      {
        // for differential update: set previous buffer equal to current buffer in controller
        display.epd2.writeScreenBufferAgain(); // use default for white
        display.epd2.writeImageAgain(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
      }
      delay(2000);
      x += 40;
      y += 40;
      if ((x >= display.epd2.WIDTH) || (y >= display.epd2.HEIGHT)) break;
    }
    if (!display.epd2.hasFastPartialUpdate) break; // comment out for full show
    break; // comment out for full show
  }
  display.writeScreenBuffer(); // use default for white
  display.writeImage(bitmaps[0], 0, 0, 200, 200, false, mirror_y, true);
  display.writeImage(bitmaps[0], display.epd2.WIDTH - 200, display.epd2.HEIGHT - 200, 200, 200, false, mirror_y, true);
  display.refresh(true);
  delay(2000);
}
#endif


void drawBitmaps()
{
  display.setFullWindow();
#ifdef _GxBitmaps128x250_H_
  drawBitmaps128x250();
#endif
#ifdef _GxBitmaps128x296_H_
  drawBitmaps128x296();
#endif
#ifdef _GxBitmaps176x264_H_
  drawBitmaps176x264();
#endif
#ifdef _GxBitmaps400x300_H_
  drawBitmaps400x300();
#endif
#ifdef _GxBitmaps640x384_H_
  drawBitmaps640x384();
#endif
  // show these after the specific bitmaps
#ifdef _GxBitmaps200x200_H_
  drawBitmaps200x200();
#endif
}




struct bitmap_pair
{
  const unsigned char* black;
  const unsigned char* red;
};

void drawBitmapPairCallback(const void* parameters)
{
  const bitmap_pair* bitmaps = reinterpret_cast<const bitmap_pair*>(parameters);
  display.fillScreen(GxEPD_WHITE);
  display.drawBitmap(0, 0, bitmaps->black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
  display.drawBitmap(0, 0, bitmaps->red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
}

void drawInvertedBitmapPairCallback(const void* parameters)
{
  const bitmap_pair* bitmaps = reinterpret_cast<const bitmap_pair*>(parameters);
  display.fillScreen(GxEPD_WHITE);
  display.drawInvertedBitmap(0, 0, bitmaps->black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
  display.drawInvertedBitmap(0, 0, bitmaps->red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
}

void drawSpecialBitmapPairCallback(const void* parameters)
{
  const bitmap_pair* bitmaps = reinterpret_cast<const bitmap_pair*>(parameters);
  display.fillScreen(GxEPD_WHITE);
  // Bitmap3c200x200_black has 2 bits per pixel
  // taken from Adafruit_GFX.cpp, modified
  int16_t byteWidth = (display.epd2.WIDTH + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
  for (int16_t j = 0; j < display.epd2.HEIGHT; j++)
  {
    for (int16_t i = 0; i < display.epd2.WIDTH; i++)
    {
      if (i & 3) byte <<= 2;
      else
      {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
        byte = pgm_read_byte(&bitmaps->black[j * byteWidth * 2 + i / 4]);
#else
        byte = bitmaps->black[j * byteWidth * 2 + i / 4];
#endif
      }
      if (!(byte & 0x80))
      {
        display.drawPixel(i, j, GxEPD_BLACK);
      }
    }
  }
  display.drawInvertedBitmap(0, 0, bitmaps->red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init(115200);
  // first update should be full refresh
  helloWorld();
  delay(1000);
  // partial refresh mode can be used to full screen,
  // effective if display panel hasFastPartialUpdate
  helloFullScreenPartialMode();
  delay(1000);
  helloArduino();
  delay(1000);
  helloEpaper();
  delay(1000);
  showFont("FreeMonoBold9pt7b", &FreeMonoBold9pt7b);
  delay(1000);
  drawBitmaps();
  if (display.epd2.hasPartialUpdate)
  {
    showPartialUpdate();
    delay(1000);
  } // else // on GDEW0154Z04 only full update available, doesn't look nice
  //drawCornerTest();
  //showBox(16, 16, 48, 32, false);
  //showBox(16, 56, 48, 32, true);
  display.powerOff();
  Serial.println("setup done");
}

void loop()
{
}