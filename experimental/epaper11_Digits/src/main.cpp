#include <Arduino.h>

#include <GxEPD2_BW.h>
// Instantiate display and set esp32doit-devkit-v1 GPIOs to signals CS,DC,RST,BUSY
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(17,16,5,19)); 

void setup(){
  display.init(115200);  
  /// display.setFullWindow();
  display.setRotation(1); // landscape mode
}


#include "battery_full.h"
#include "battery_half.h"
#include "battery_empty.h"
#include "battery_quarter.h"
#include "battery_three_quarters.h"
// Display battery level icon and % in text below to fit in 32x32 space
// Top left corner coord of scada element 
// Screen coordinate system:
//
//  (0,0)
//    +---------------> X-axis, 296 pixels
//    |
//    |
//    v
//  Y-axis, 128 pixels
//
// Size: 32x24  Icon: 32x16, text below: 32x8
// Total size: 32x24
void displayBatterylevel(int percent, int x=1, int y=1) {
  // Images
  const unsigned char * batterylevels[] = {battery_empty_32x16, battery_quarter_32x16, battery_half_32x16, battery_three_quarters_32x16, battery_full_32x16};  
  // scale                  0                                 5             25        40         50      60              75            90                  100
  const unsigned char * batterylevel;
  if(percent <= 5){
    batterylevel=batterylevels[0];
  }else{
    if(percent<=40){
      batterylevel=batterylevels[1];
    }else{
      if(percent<=60){
        batterylevel=batterylevels[2];
      }else{
        if(percent<=90){
          batterylevel=batterylevels[3];
        }else{
          batterylevel=batterylevels[4];
        }
      }
    }
  }
  
  // Simple char drawing
  char valueText[10];
  sprintf(valueText, "%d%%",percent);
  int len=strlen(valueText);
  // Set partial update area  
  display.setPartialWindow(x,y,32,24);
  
  // Do drawing
  display.firstPage();
  do { 
    // No lines   
    // Draw display element outline 
    //  display.drawFastHLine(x,y,31,0x0000);
    // display.drawFastHLine(x,y+32,31,0x0000);
    // display.drawFastVLine(x,y,32,0x0000);
    // display.drawFastVLine(x+31,y,32,0x0000); Next Display Element will draw vertical line
    
    // Draw bitmap
    display.drawBitmap(x,y,batterylevel,32,16, 0x0000);
    //display.drawImage(batterylevel,x+1,y+1,32,16,false,false,true);  // somehow assumes rotation(0), can't change
    for(int i=0;i<len;i++){
      // Add leading space if single digit
      if(len==2 ){
        display.drawChar(x+5+((i+1)*6),y+19,valueText[i], 0x0000,0xffff,1);
      } else {
        display.drawChar(x+5+(i*6),y+19,valueText[i], 0x0000,0xffff,1);
      }
    }
  } while (display.nextPage());
}

// Global log line text buffer
char logLines[250][4];
// Text into lower 3/4 of 296x128 display
// Holds 4 lines in display at 40, 60, 80, 100
// Scroll downwards
// Use built-int text of 5x7 pixel chars --> text size=1
void displayLogLine(const char * logLine, int x=0, int y=24){
  display.setTextWrap(false);  
  display.setTextColor(0x0000);
  display.setTextSize(1);
  // shocking method! should use ring buffer!
  int i;
  for(i=3;i<0;i--){ // move all lines down
    strcpy((char*)logLine[i],(char*)logLine[i-1]);
  }
  strncpy((char*)logLine[0],(char*)logLine,250);
  // display new buffer
  display.setPartialWindow(x,y,296,104);    
  display.firstPage();
  do { 
    for(i=0;i<4;i++){
      display.setCursor(x,y+(i*10));
      display.print(logLine);
    }
  } while (display.nextPage());
}

int count = 0;
char logline[250];
void loop() {
  
  Serial.println("Drawing battery level...");
  displayBatterylevel(0);
  delay(500);
  displayBatterylevel(30);
  delay(500);
  displayBatterylevel(50);
  delay(500);
  displayBatterylevel(80);
  delay(500);
  displayBatterylevel(100);
  delay(500);
  sprintf(logline, "this is line %d", count++);
  // displayLogLine(logline);
  
  
}