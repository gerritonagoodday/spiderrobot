/*########################   Weather Display  #############################
 * Receives and displays the weather forecast from the Weather Underground and then displays using a 
 * JSON decoder wx data to display on an SPI bus e-Paper 4.2" (Waveshare) 400x300 display.
 * Weather data received via WiFi connection to Weather Underground Servers and using their 'Forecast' and 'Astronomny' API and the resultant data
 * is decoded using the excellent Benoit Blanchon's (c) 2014-2017 JSON library.
 * This source code is protected under the terms of the MIT License and is copyright (c) 2017 by David Bird and permission is hereby granted, free of charge, to
 * any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, but not to sub-license and/or 
 * to sell copies of the Software or to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 *   
 *   In update mode, power consumption = 74mA    for 5-secs
 *   In sleep mode, power consumption  = 0.010mA for ~15-mins
 *   
 *   Therefore mAH consumption = 0.01mA x 4 x 15 + 74mA * 4 * 15*60/3600 = 0.421mAH so a 1500mAH battery would last for ~148-days
 *   
 *   See more at http://dsbird.org.uk */
       
// #include <WiFi.h>
#include <ArduinoJson.h>     // https://github.com/bblanchon/ArduinoJson
#include <WiFiClient.h>
#include <Wire.h>

#include "time.h"
#include <SPI.h>
#include <GxEPD.h>
// #include <GxGDEW042T2/GxGDEW042T2.cpp>
#include <GxGDEW029T5/GxGDEW029T5.cpp>
#include <Fonts/FreeSans9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>


#include "main.h"
#include "WhitepaperDisplay.h"


//################# LIBRARIES ##########################
String version = "1.0";       // Version of this program
//################ VARIABLES ###########################

// Define each of the *icons for display
const unsigned char sunny[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xe1, 0xff, 0x9f, 0xff, 0xff, 0xf0, 0x7f, 0xf3, 0xff, 0x0f, 0xff, 
0xff, 0xf8, 0x3f, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xfe, 0x1f, 0x81, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xbc, 0x00, 0x1c, 0x7f, 0xff, 
0xff, 0xff, 0xf0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xc3, 0xff, 0xff, 
0xff, 0xff, 0x81, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x03, 0x87, 0xff, 0xf0, 0xe0, 0x3f, 0xf8, 0x01, 0x87, 0xff, 0xf0, 0xc0, 0x1f, 
0xf8, 0x01, 0x87, 0xff, 0xf0, 0xc0, 0x1f, 0xfc, 0x03, 0x87, 0xff, 0xf0, 0xe0, 0x3f, 0xff, 0xff, 0x87, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xc1, 0xff, 0xff, 
0xff, 0xff, 0xc1, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7f, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x06, 0xff, 0xff, 
0xff, 0xff, 0x3e, 0x00, 0x3c, 0x7f, 0xff, 0xff, 0xfc, 0x1f, 0x81, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xfe, 0x07, 0xff, 
0xff, 0xf8, 0x7f, 0xf3, 0xff, 0x0f, 0xff, 0xff, 0xfc, 0xff, 0xe1, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

const unsigned char mostlysunny[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 
0xff, 0xff, 0xfe, 0xff, 0x87, 0xfe, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0x87, 0xf8, 0x7f, 0xff, 0xff, 0xf8, 0x3f, 0xcf, 0xf0, 0x7f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff, 
0xff, 0xff, 0xfe, 0x0f, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 
0xff, 0xff, 0xc0, 0xf8, 0x78, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x01, 0xfe, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0x0f, 0xff, 
0xff, 0xfc, 0x00, 0x01, 0xff, 0x87, 0xff, 0xff, 0xf0, 0x7f, 0xe1, 0xff, 0xe7, 0xff, 0xff, 0xf0, 0xff, 0xf1, 0xff, 0xe7, 0xff, 0xff, 0xe1, 0xff, 0xf0, 0x7f, 0xe4, 0x07, 
0xff, 0xc3, 0xff, 0xf8, 0x1f, 0xc0, 0x03, 0xff, 0xc7, 0xff, 0xfc, 0x0f, 0x88, 0x03, 0xff, 0xc7, 0xff, 0xfe, 0x07, 0x8c, 0x07, 0xf0, 0x0f, 0xff, 0xff, 0xe3, 0x1f, 0xff, 
0xe0, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 
0xc7, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0x67, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0x67, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0x63, 0xff, 
0x9f, 0xff, 0xff, 0xff, 0xfc, 0x61, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0x60, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0x7f, 0xcf, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0x7f, 
0xcf, 0xff, 0xff, 0xff, 0xf1, 0xfc, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 
0xe0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

const unsigned char rain[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7e, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0x80, 0xff, 0xff, 
0xff, 0xff, 0x81, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xfc, 0x01, 0xff, 
0xff, 0xfc, 0x3f, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0x00, 0x1f, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x0f, 
0xf8, 0x01, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x87, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0x07, 0x03, 0xff, 0x87, 
0xc3, 0xff, 0xff, 0x06, 0x07, 0xff, 0x07, 0xe1, 0xff, 0xfe, 0x0e, 0x07, 0xff, 0x07, 0xe0, 0xff, 0xfe, 0x1e, 0x0f, 0xfc, 0x0f, 0xe0, 0x3f, 0xfe, 0x1e, 0x0f, 0xf0, 0x1f, 
0xe0, 0x00, 0x3c, 0x1c, 0x1c, 0x00, 0x1f, 0xfc, 0x00, 0x78, 0x3c, 0x3c, 0x00, 0xff, 0xff, 0x00, 0x78, 0x78, 0x38, 0x03, 0xff, 0xff, 0xc0, 0x78, 0x78, 0x78, 0x0f, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xe0, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x81, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x83, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x07, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char tstorms[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 
0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0x80, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0x83, 0xff, 0xf0, 0x3f, 0xff, 
0xff, 0xff, 0x07, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0x00, 0x3f, 
0xff, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0x0f, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x0f, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x07, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xc7, 
0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 
0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 
0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc7, 0xff, 0xf0, 0xf8, 0xf8, 0x3f, 0x87, 0xc1, 0xff, 0xf0, 0xf8, 0xf0, 0x3f, 0x07, 0xe0, 0xff, 0xc0, 0xe1, 0xe0, 0x7c, 0x0f, 
0xe0, 0x3f, 0x81, 0xe1, 0xc0, 0xf8, 0x0f, 0xf0, 0x07, 0x83, 0xc1, 0xc0, 0xf8, 0x3f, 0xfc, 0x07, 0x83, 0x83, 0x81, 0xf0, 0xff, 0xfe, 0x0f, 0x87, 0x83, 0x83, 0xf1, 0xff, 
0xff, 0xcf, 0x0f, 0x07, 0x03, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0x0e, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x1f, 0x1e, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x3e, 0x1e, 0x00, 0xff, 0xff, 
0xff, 0xf8, 0x7c, 0x3f, 0xe1, 0xff, 0xff, 0xff, 0xf0, 0x7c, 0x7f, 0xe1, 0xff, 0xff, 0xff, 0xf0, 0x78, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xff, 0xc3, 0xff, 0xff, 
0xff, 0xff, 0xe0, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0x9f, 0xff, 0xff, 
0xff, 0xff, 0x87, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char cloudy[] PROGMEM =  { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3e, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0x80, 0xff, 0xff, 
0xff, 0xff, 0x81, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0x03, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xfc, 0x01, 0xff, 
0xff, 0xfc, 0x3f, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xfc, 0x3f, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0x00, 0x1f, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0x0f, 
0xf8, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x0f, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x87, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 
0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 
0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xf0, 0x0f, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char snow[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xe0, 0x0f, 0xff, 
0xff, 0xff, 0xfc, 0x07, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xe8, 0x1f, 0xfe, 0x07, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0x83, 0xff, 
0xff, 0xf0, 0x00, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xe0, 0x0f, 
0xff, 0xc3, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x03, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe1, 
0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 
0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x81, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xb9, 0xef, 
0xff, 0xc7, 0xff, 0xff, 0xff, 0x09, 0x8f, 0xfc, 0x46, 0x7f, 0xff, 0xff, 0xc0, 0x1f, 0xfc, 0x04, 0x7f, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0x00, 0x7f, 0xf3, 0xfc, 0x00, 0x07, 
0xff, 0x80, 0xff, 0xf1, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x1f, 0x71, 0x1f, 0xe0, 0x3f, 0xf0, 0x00, 0x1f, 0x10, 0x1f, 0xc0, 0x1f, 0xff, 0x00, 0xff, 0x80, 0xff, 0x08, 0x8f, 
0xfe, 0x00, 0x7f, 0xc0, 0xff, 0x98, 0xcf, 0xfc, 0x06, 0x7c, 0x00, 0x07, 0xf8, 0xff, 0xfc, 0xc7, 0x7c, 0x00, 0x07, 0xf9, 0xff, 0xff, 0xc7, 0xff, 0x80, 0xff, 0xff, 0xff, 
0xff, 0xef, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x71, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff};

const unsigned char sleet[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xe0, 0x0f, 0xff, 
0xff, 0xff, 0xfc, 0x07, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xfe, 0x07, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0x83, 0xff, 
0xff, 0xf0, 0x00, 0x7f, 0xff, 0xc3, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xe0, 0x0f, 
0xff, 0x83, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x03, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xc1, 
0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 
0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x81, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0x07, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xfc, 0x07, 0xff, 0xcf, 0xff, 0x80, 0x3f, 
0xf8, 0x07, 0xff, 0x8f, 0xff, 0x80, 0x3f, 0xf0, 0x07, 0xf8, 0x8c, 0xff, 0x80, 0x7f, 0xf0, 0x07, 0xf8, 0x88, 0xff, 0x80, 0x7f, 0xf0, 0x0f, 0xff, 0x01, 0xff, 0xe1, 0xff, 
0xf0, 0x0f, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xe0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x7f, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff};

const unsigned char fog[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xe0, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0x7f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0x8f, 0xff, 
0xff, 0xff, 0x8f, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xc7, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xe7, 0xff, 
0xf8, 0x00, 0x3f, 0xff, 0xff, 0xe7, 0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0x3f, 0xff, 0xff, 0xe0, 0x1f, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 
0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 
0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char nodata[] PROGMEM = { // 56x48
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 
0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0c, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x83, 0xff, 0xff, 
0xff, 0xff, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char thermo[] PROGMEM = { // 64x24
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 
0xf9, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xfb, 0xdf, 0xff, 0xff, 0xf3, 0xff, 0xdf, 0xff, 0xfb, 0x5f, 0xff, 0xff, 0xe9, 0xff, 0x0f, 0xff, 
0xfb, 0x5f, 0xfc, 0x7f, 0xed, 0xbf, 0x0f, 0xff, 0xfa, 0x5e, 0x18, 0x3f, 0xed, 0x7e, 0x07, 0xff, 0xfb, 0x5e, 0xd9, 0x9f, 0xed, 0x7e, 0x07, 0xff, 
0xfb, 0x5e, 0xd3, 0xdf, 0xe3, 0x7c, 0x03, 0xff, 0xfa, 0x5e, 0x13, 0xff, 0xf2, 0xfc, 0x03, 0xdf, 0xfb, 0x5f, 0xf7, 0xff, 0xfe, 0xfc, 0x13, 0xdf, 
0xfb, 0x5f, 0xf7, 0xff, 0xfd, 0x9c, 0x07, 0xdf, 0xfa, 0x5f, 0xf7, 0xff, 0xfd, 0x4e, 0x07, 0x8f, 0xfb, 0x5f, 0xf3, 0xdf, 0xfb, 0x6f, 0x0f, 0x8f, 
0xfb, 0x5f, 0xf1, 0x9f, 0xfb, 0x6f, 0xff, 0x07, 0xfa, 0x5f, 0xf8, 0x3f, 0xfb, 0x6f, 0xff, 0x07, 0xfa, 0x1f, 0xfc, 0x7f, 0xf7, 0x1f, 0xff, 0x03, 
0xf0, 0x0f, 0xff, 0xff, 0xff, 0x9f, 0xfe, 0x03, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x13, 
0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f };

const unsigned char probrain[] PROGMEM = { // 32x24
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xc7, 0xe0, 0x7f, 
0xff, 0xdf, 0xf8, 0x3f, 0xff, 0x1f, 0xff, 0x9f, 0xfc, 0x3f, 0xff, 0xcf, 0xe0, 0x7f, 0xdf, 0xc7, 0xc0, 0xff, 0x9f, 0xc3, 0x9f, 0xff, 0x1f, 0xf9, 
0x3f, 0xff, 0x1f, 0xfc, 0x3f, 0xfe, 0x1f, 0xfc, 0x3f, 0xfb, 0x1f, 0xfc, 0x9f, 0xf3, 0x3b, 0xf9, 0xc0, 0x63, 0xf3, 0x03, 0xe0, 0x63, 0xe3, 0x87, 
0xff, 0xc3, 0xe3, 0xff, 0xff, 0xe7, 0xc3, 0xff, 0xff, 0xe7, 0xe3, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

// pins_arduino.h, e.g. WEMOS Lolin
static const uint8_t GPIO_CS    = 17; // ORANGE
static const uint8_t GPIO_MOSI  = 23; // BLUE
static const uint8_t GPIO_SCK   = 18; // YELLOW
// static const uint8_t GPIO_MISO  = ;
static const uint8_t GPIO_DC    = 16; // GREEN
static const uint8_t GPIO_RST   = 5; // WHITE
static const uint8_t GPIO_BUSY  = 19; // VIOLET

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, GPIO_CS, GPIO_DC); 
//GxIO_Class io(SPI, 17, 16, 14); 
//GxIO_Class io(SPI, 13, 12, 14); 
// GxGDEP015OC1(GxIO& io, uint8_t rst = D4, uint8_t busy = D2);
GxEPD_Class display(io, GPIO_RST, GPIO_BUSY); 
//GxEPD_Class display(io, 14, 22); 

//------ NETWORK VARIABLES---------
// Use your own API key by signing up for a free developer account at http://www.wunderground.com/weather/api/
String apikey     = "b84fec59e3464f2b8fec59e346df2b7e";  // See: http://www.wunderground.com/weather/api/d/docs (change here with your KEY)
String City       = "Chichester";                     // Your home city
String Country    = "UK";                          // Your country   
String Conditions = "conditions";                  // See: http://www.wunderground.com/weather/api/d/docs?d=data/index&MR=1
char   wxserver[] = "api.wunderground.com";        // Address for WeatherUnderGround
unsigned long     lastConnectionTime = 0;          // Last time you connected to the server, in milliseconds
const unsigned long  postingInterval    = 15L*60L*1000L; // Delay between updates, in milliseconds, WU allows 500 requests per-day maximum, set to every 15-mins or 144/day
String Units      =  "M"; // M for Metric, X for Mixed and I for Imperial
String time_str, currCondString; // strings to hold time and received weather data;

//################ PROGRAM VARIABLES and OBJECTS ################
// Conditions
String WDay0, Day0, Icon0, High0, Low0, Conditions0, Pop0, Averagehumidity0,
       WDay1, Day1, Icon1, High1, Low1, Conditions1, Pop1, Averagehumidity1,
       WDay2, Day2, Icon2, High2, Low2, Conditions2, Pop2, Averagehumidity2,
       WDay3, Day3, Icon3, High3, Low3, Conditions3, Pop3, Averagehumidity3;

// Astronomy
String  DphaseofMoon, Sunrise, Sunset, Moonrise, Moonset, Moonlight;

const char* ssid     = "VodafoneConnect97006177";
const char* password = "a93maec6ftpsp3u";
const char* host     = "api.wunderground.com";

WiFiClient client; // wifi client object

void app_main(void){

  ESP_LOGI(WhitepaperDisplay::TAG,"Starting up...");  
  display.init();
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeSans9pt7b);
  display.setRotation(2);
  display.setCursor(0, 12);
  display.println(F("SpiderRobot\n\rStarting...\n\rReading and Decoding Wx Data..."));
  display.update();
  delay(500);
  StartWiFi(ssid,password);
  SetupTime();
  lastConnectionTime = millis();
  obtain_forecast("forecast");
  obtain_forecast("astronomy");
  DisplayForecast();
  ESP.deepSleep(15*60*1000000); // Sleep for 15 minutes

  for(;;){
    if (millis() - lastConnectionTime > postingInterval) {
      obtain_forecast("forecast");
      obtain_forecast("astronomy");
      lastConnectionTime = millis();
      DisplayForecast();
    }
  }
}

void DisplayForecast(){ // Display is 400x300 resolution
  display.fillScreen(GxEPD_WHITE);
  DisplayWXicon(0,0, Icon0);  DisplayWXicon(75,0, "thermo"); DisplayWXicon(155,0, "probrain");
  DisplayText(200,15,WDay0 + " " + Day0);
  DisplayText(195,30,Conditions0);
  DisplayText(60,40,High0 + "/" + Low0);
  DisplayText(115,40,Averagehumidity0 + "%");
  DisplayText(158,40,Pop0 + "%");
  DisplayText(60,55,"--------------------------");
  DisplayWXicon(0,60, Icon1); DisplayWXicon(75,60, "thermo"); DisplayWXicon(155,60, "probrain");
  DisplayText(200,75,WDay1 + " " + Day1);
  DisplayText(195,90,Conditions1);
  DisplayText(60,100,High1 + "/" + Low1);
  DisplayText(115,100,Averagehumidity1 + "%");
  DisplayText(158,100,Pop1 + "%");
  DisplayText(60,115,"-------------------------");
  DisplayWXicon(0,120, Icon2); DisplayWXicon(75,120, "thermo"); DisplayWXicon(155,120, "probrain");
  DisplayText(200,135,WDay2 + " " + Day2);
  DisplayText(195,150,Conditions2);
  DisplayText(60,160,High2 + "/" + Low2);
  DisplayText(115,160,Averagehumidity2 + "%");
  DisplayText(158,160,Pop2 + "%");
  DisplayText(60,175,"--------------------------");
  DisplayWXicon(0,180, Icon3); DisplayWXicon(75,180, "thermo"); DisplayWXicon(155,180, "probrain");
  DisplayText(200,195,WDay3 + " " + Day3);
  DisplayText(195,210,Conditions3);
  DisplayText(60,220,High3 + "/" + Low3);
  DisplayText(115,220,Averagehumidity3 + "%");
  DisplayText(158,220,Pop3 + "%");
  DisplayText(60,235,"--------------------------");
  
  DisplayText(000,245,"Sunrise/Set");
  DisplayText(000,262,Sunrise+"/"+Sunset);
  DisplayText(110,245,"Moonrise/Set");
  DisplayText(110,262,Moonrise+"/"+Moonset);
  DisplayText(225,245,"Moonphase");
  DisplayText(225,262,DphaseofMoon+" "+Moonlight+"%");
  UpdateTime();
  DisplayText(85,292,time_str);
  display.update(); 
}

void DisplayText(int x, int y, String text){
  display.setCursor(x,y);
  display.println(text);
}

void DisplayWXicon(int x, int y, String IconName){
  // int len = 56*48; 
  //char myChar[56*48]={};
  //for (int k = 0; k < len; k++) {
  //  myChar[k] =  IconName[k];
  //}
  ESP_LOGI(WhitepaperDisplay::TAG,"Displaying icon %s",IconName);  
  if      (IconName == "rain"            || IconName == "nt_rain"         ||
           IconName == "chancerain"      || IconName == "nt_chancerain")
           display.drawBitmap(x,y, rain, 56,48, GxEPD_BLACK);
  else if (IconName == "snow"            || IconName == "nt_snow"         ||
           IconName == "flurries"        || IconName == "nt_flurries"     ||
           IconName == "chancesnow"      || IconName == "nt_chancesnow"   ||
           IconName == "chanceflurries"  || IconName == "nt_chanceflurries")
           display.drawBitmap(x,y, snow, 56,48, GxEPD_BLACK);
  else if (IconName == "sleet"           || IconName == "nt_sleet"        ||
           IconName == "chancesleet"     || IconName == "nt_chancesleet")
           display.drawBitmap(x,y, sleet, 56,48, GxEPD_BLACK);
  else if (IconName == "sunny"           || IconName == "nt_sunny"        ||
           IconName == "clear"           || IconName == "nt_clear")
           display.drawBitmap(x,y, sunny, 56,48, GxEPD_BLACK);
  else if (IconName == "partlysunny"     || IconName == "nt_partlysunny"  ||
           IconName == "mostlysunny"     || IconName == "nt_mostlysunny")
           display.drawBitmap(x,y, mostlysunny, 56,48, GxEPD_BLACK);
  else if (IconName == "cloudy"          || IconName == "nt_cloudy"       ||
           IconName == "mostlycloudy"    || IconName == "nt_mostlycloudy" ||
           IconName == "partlycloudy"    || IconName == "nt_partlycloudy")  
           display.drawBitmap(x,y, cloudy, 56,48, GxEPD_BLACK);
  else if (IconName == "tstorms"         || IconName == "nt_tstorms"      ||
           IconName == "chancetstorms"   || IconName == "nt_chancetstorms")
           display.drawBitmap(x,y, tstorms, 56,48, GxEPD_BLACK);
  else if (IconName == "fog"             || IconName == "nt_fog"          ||
           IconName == "hazy"            || IconName == "nt_hazy")
           display.drawBitmap(x,y, fog, 56,48, GxEPD_BLACK);
  else if (IconName == "thermo")
           display.drawBitmap(x,y, thermo,64,24, GxEPD_BLACK);
  else if (IconName == "probrain")
           display.drawBitmap(x,y, probrain,32,24, GxEPD_BLACK);
  else     display.drawBitmap(x,y, nodata, 56,48, GxEPD_BLACK);
}

bool obtain_forecast (String forecast_type) {
  client.stop();  // Clear any current connections
  ESP_LOGI(WhitepaperDisplay::TAG,"Connecting to %s",host); // start a new connection
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
   ESP_LOGE(WhitepaperDisplay::TAG,"Connection failed");
   return false;
  }
  // Weather Underground API address http://api.wunderground.com/api/YOUR_API_KEY/conditions/q/YOUR_STATE/YOUR_CITY.json
  String url = "http://api.wunderground.com/api/"+apikey+"/"+forecast_type+"/q/"+Country+"/"+City+".json";
  ESP_LOGI(WhitepaperDisplay::TAG,"Requesting URL: %s",url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      ESP_LOGW(WhitepaperDisplay::TAG,">>> Client Connection Timeout...Stopping");
      client.stop();
      return false;
    }
  }
  ESP_LOGI(WhitepaperDisplay::TAG,"Receiving API weather data...");
  while(client.available()) {
    currCondString = client.readStringUntil('\r');    
  }
  ESP_LOGI(WhitepaperDisplay::TAG,"Received. Closing connection");
  //Serial.println(*currCondString);
  if (forecast_type == "forecast"){
    if (showWeather_forecast(&currCondString)); else ESP_LOGE(WhitepaperDisplay::TAG,"Failed to get Weather Data");
  }
  if (forecast_type == "astronomy"){
    if (showWeather_astronomy(&currCondString)); else ESP_LOGE(WhitepaperDisplay::TAG,"Failed to get Astronomy Data");
  }
  return true;
}

bool showWeather_astronomy(String* currCondString) {
  ESP_LOGI(WhitepaperDisplay::TAG,"Creating astronomy object...");
  DynamicJsonBuffer jsonBuffer(1*1024);
  // Create root object and parse the json file returned from the api. The API returns errors and these need to be checked to ensure successful decoding
  JsonObject& root = jsonBuffer.parseObject(*(currCondString));
  if (!root.success()) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
  }
  // Extract weather info from parsed JSON
  JsonObject& current = root["moon_phase"];
  String percentIlluminated = current["percentIlluminated"];
  String phaseofMoon = current["phaseofMoon"];
  int SRhour         = current["sunrise"]["hour"];
  int SRminute       = current["sunrise"]["minute"];
  int SShour         = current["sunset"]["hour"];
  int SSminute       = current["sunset"]["minute"];
  int MRhour         = current["moonrise"]["hour"];
  int MRminute       = current["moonrise"]["minute"];
  int MShour         = current["moonset"]["hour"];
  int MSminute       = current["moonset"]["minute"];
  Sunrise   = (SRhour<10?"0":"")+String(SRhour)+":"+(SRminute<10?"0":"")+String(SRminute);
  Sunset    = (SShour<10?"0":"")+String(SShour)+":"+(SSminute<10?"0":"")+String(SSminute);
  Moonrise  = (MRhour<10?"0":"")+String(MRhour)+":"+(MRminute<10?"0":"")+String(MRminute);
  Moonset   = (MShour<10?"0":"")+String(MShour)+":"+(MSminute<10?"0":"")+String(MSminute);
  Moonlight = percentIlluminated;
  DphaseofMoon = phaseofMoon;
  return true;
}

bool showWeather_forecast(String* currCondString) {
  ESP_LOGI(WhitepaperDisplay::TAG,"Creating weather object...");
  DynamicJsonBuffer jsonBuffer(8*1024);
  // Create root object and parse the json file returned from the api. The API returns errors and these need to be checked to ensure successful decoding
  JsonObject& root = jsonBuffer.parseObject(*(currCondString));
  if (!root.success()) {
    ESP_LOGE(WhitepaperDisplay::TAG,"jsonBuffer.parseObject() failed");
  }
  JsonObject& forecast = root["forecast"]["simpleforecast"];
  String wday0  = forecast["forecastday"][0]["date"]["weekday_short"];  WDay0 = wday0;
  int    day0   = forecast["forecastday"][0]["date"]["day"];            day0<10?(Day0="0"+String(day0)):(Day0=String(day0));
  String mon0   = forecast["forecastday"][0]["date"]["monthname_short"];
  String year0  = forecast["forecastday"][0]["date"]["year"];           Day0 += "-" + mon0 + "-" + year0.substring(2); 
  String icon0  = forecast["forecastday"][0]["icon"];                   Icon0 = icon0;
  String high0  = forecast["forecastday"][0]["high"]["celsius"];        High0 = high0;
  String low0   = forecast["forecastday"][0]["low"]["celsius"];         Low0  = low0;
  String conditions0 = forecast["forecastday"][0]["conditions"];        Conditions0  = conditions0;
  String pop0        = forecast["forecastday"][0]["pop"];               Pop0  = pop0;
  String averagehumidity0 = forecast["forecastday"][0]["avehumidity"];  Averagehumidity0 = averagehumidity0;

  String wday1  = forecast["forecastday"][1]["date"]["weekday_short"];  WDay1 = wday1;
  int    day1   = forecast["forecastday"][1]["date"]["day"];            day1<10?(Day1="0"+String(day1)):(Day1=String(day1));
  String mon1   = forecast["forecastday"][1]["date"]["monthname_short"];
  String year1  = forecast["forecastday"][1]["date"]["year"];           Day1 += "-" + mon1 + "-" + year1.substring(2); 
  String icon1  = forecast["forecastday"][1]["icon"];                   Icon1 = icon1;
  String high1  = forecast["forecastday"][1]["high"]["celsius"];        High1 = high1;
  String low1   = forecast["forecastday"][1]["low"]["celsius"];         Low1  = low1;
  String conditions1 = forecast["forecastday"][1]["conditions"];        Conditions1  = conditions1;
  String pop1   = forecast["forecastday"][1]["pop"];                    Pop1  = pop1;
  String averagehumidity1 = forecast["forecastday"][1]["avehumidity"];  Averagehumidity1 = averagehumidity1;
  
  String wday2  = forecast["forecastday"][2]["date"]["weekday_short"];  WDay2 = wday2;
  int    day2   = forecast["forecastday"][2]["date"]["day"];            day2<10?(Day2="0"+String(day2)):(Day2=String(day2));
  String mon2   = forecast["forecastday"][2]["date"]["monthname_short"];
  String year2  = forecast["forecastday"][2]["date"]["year"];           Day2 += "-" + mon2 + "-" + year2.substring(2); 
  String icon2  = forecast["forecastday"][2]["icon"];                   Icon2 = icon2;
  String high2  = forecast["forecastday"][2]["high"]["celsius"];        High2 = high2;
  String low2   = forecast["forecastday"][2]["low"]["celsius"];         Low2  = low2;
  String conditions2 = forecast["forecastday"][2]["conditions"];        Conditions2  = conditions2;
  String pop2   = forecast["forecastday"][2]["pop"];                    Pop2  = pop2;
  String averagehumidity2 = forecast["forecastday"][2]["avehumidity"];  Averagehumidity2 = averagehumidity2;

  String wday3  = forecast["forecastday"][3]["date"]["weekday_short"];  WDay3 = wday3;
  int    day3   = forecast["forecastday"][3]["date"]["day"];            day3<10?(Day3="0"+String(day3)):(Day3=String(day3));
  String mon3   = forecast["forecastday"][3]["date"]["monthname_short"];
  String year3  = forecast["forecastday"][3]["date"]["year"];           Day3 += "-" + mon3 + "-" + year3.substring(2); 
  String icon3  = forecast["forecastday"][3]["icon"];                   Icon3 = icon3;
  String high3  = forecast["forecastday"][3]["high"]["celsius"];        High3 = high3;
  String low3   = forecast["forecastday"][3]["low"]["celsius"];         Low3  = low3;
  String conditions3 = forecast["forecastday"][3]["conditions"];        Conditions3  = conditions3;
  String pop3   = forecast["forecastday"][3]["pop"];                    Pop3  = pop3;
  String averagehumidity3 = forecast["forecastday"][3]["avehumidity"];  Averagehumidity3 = averagehumidity3;

  return true;
}

int StartWiFi(const char* ssid, const char* password){
 int connAttempts = 0;
 ESP_LOGI(WhitepaperDisplay::TAG,"Connecting to: %s"),ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED ) {
   delay(500); 
   if(connAttempts > 20) return -5;
   connAttempts++;
 }
 ESP_LOGI(WhitepaperDisplay::TAG,"WiFi connected at: %s", WiFi.localIP());
 return 1;
}

void clear_screen() {
   display.fillScreen(GxEPD_WHITE);
   display.update();
}  

void SetupTime(){
  configTime(0 * 3600, 3600, "0.uk.pool.ntp.org", "time.nist.gov");
  UpdateTime();
}

void UpdateTime(){
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)){
    ESP_LOGE(WhitepaperDisplay::TAG,"Failed to obtain time from NTP server. Trying again...");
    xTaskDelay(1000/portTICK_PERIOD_MS);    
  }
  //See http://www.cplusplus.com/reference/ctime/strftime/
  char now_time[40];
  strftime(now_time,siezof(now_time),"%a %d %b %Y, %H:%M:%S", &timeinfo); // Displays: Saturday 24 June 24 2020, 14:05:49
  ESP_LOGI(WhitepaperDisplay::TAG,"%", now_time); 
  time_str = asctime(&timeinfo); // Displays: Sat Jun 24 14:05:49 2017
  time_str = time_str.substring(0,24); // Displays: Sat Jun 24 14:05
}