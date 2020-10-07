#include <Arduino.h>
#include "hammer.h" 
#include <GxEPD2_BW.h>
// Instantiate display and set esp32doit-devkit-v1 GPIOs to signals CS,DC,RST,BUSY
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(17,16,5,19)); 

void setup(){
  display.init(115200);  
  display.setRotation(2);
  display.drawImage(hammer_32x28,20,10,32,28,false,false,true);  
  delay(5000);
  display.mirror(1);
  
  display.drawImage(hammer_32x28,20,10,32,28,false,true,true);  
  display.mirror(1);
  display.drawImagePart(hammer_32x28,20,10,32,28,20,10,16,16,false,false,true);  

  
  // display.refresh(0);
}

void loop(){}