// This is an embellishment of pins_arduino.h
// which lives in  /home/gerrit/.platformio/packages/framework-arduinoespressif32/variants/doitESP32devkitV1
// See other directories in /home/gerrit/.platformio/packages/framework-arduinoespressif32/variants
// for pinouts to other boards.
// Ignore this file!


#ifndef _ESP2_PINS_H_
#define _ESP2_PINS_H_

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t LED_BUILTIN = 2;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility


// Serial Comms Stuff
static const uint8_t TX = 1;
static const uint8_t TX0 = 1;
static const uint8_t RX = 3;
static const uint8_t RX0 = 3;
static const uint8_t TX1 = 9;
static const uint8_t RX1 = 10;
static const uint8_t TX2 = 17;
static const uint8_t RX2 = 16;

// I2C Stuff
static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

// SPI Stuff
static const uint8_t SS    = 5; // SPI Slave Select
static const uint8_t CS    = 5;
static const uint8_t MOSI  = 23;
static const uint8_t MISO  = 19;
static const uint8_t SCK   = 18;
static const uint8_t SCLK  = 18;

// Analog to Digital Converters
static const uint8_t A0 = 36;
static const uint8_t A3 = 39;
static const uint8_t A4 = 32;
static const uint8_t A5 = 33;
static const uint8_t A6 = 34;
static const uint8_t A7 = 35;
static const uint8_t A10 = 4;
static const uint8_t A11 = 0;
static const uint8_t A12 = 2;
static const uint8_t A13 = 15;
static const uint8_t A14 = 13;
static const uint8_t A15 = 12;
static const uint8_t A16 = 14;
static const uint8_t A17 = 27;
static const uint8_t A18 = 25;
static const uint8_t A19 = 26;

// Touch Inputs
static const uint8_t T0 = 4;
static const uint8_t T1 = 0;
static const uint8_t T2 = 2;
static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
static const uint8_t T7 = 27;
static const uint8_t T8 = 33;
static const uint8_t T9 = 32;

// Digital to Analog converters
static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

#endif /* _ESP2_PINS_H_ */
