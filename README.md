# Intro

This is my first foray into robotics after a considerable time away from real-time process control systems and embedded development. This is a prototype 8-legged spider with 2 pincers, 2 cameras for eyes, moving vision, and a mandible with pointy teeth to scare the little children, all made mode LEGO Technic. The MCU is an ESP32 Dev module, and software is written in C++ (none of this interpreted Python stuff here!) for the FreeRTOS O/S, using PlatformIO on Visual Code as the development environment, on a Linux machine (because developing it on Windows would just be painfull). 

Initially most of the code will be experimental in nature and not much use to anyone, but the pictures may tempt you to start building or improving your own LEGO Spider Robot. Suggestions welcome. 

# Technical Specifications

* 8 legs with 3 axis or rotation, with a foot-down switch sensor on each leg
* 2 pincers with 2 axis of rotation and pincer movement
* 1 moving mandible
* 1 set of parallel-moving eyes, that move both vertically and horizontally 
* 2 cameras on ESP-CAM boards, one for each eye
* 1 front ultrasonic sensor
* 1 inertial sensor
* 1 white-paper status display
* 1 real-time wall-clock
* 1 miniature speaker, 
* 2 head-mounted LED illuminators
* Bluetooth and WiFi connectivity
* 5300mAH low-profile mobile battery
* USB battery charging circuitry
* I2C-controlled circuitry to control 48 servos

This makes for a total of 33 servo motors and 2 stepper motors. These are combined with LEGO Technic in interesting ways, mostly using a combinations of hot-glue and cable ties. There is a a fair bit of wiring and if you don't keep it in a tidy and controlled state, inevitable unhappiness and frustration will ensue, so bundle cables up in bunches using a spirally-cut straws (still free from Subways) or commercial, spiral cable wrap (a quid a metre).

## Third-Party Libraries

The significant third-party libraries in use here are:
* ArduinoJson - "The best JSON library for embedded C++", https://arduinojson.org 

## Documentation Sources

Some fine technical documentation to accompany all this:
* ESP32 API Reference, https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference
* FreeRTOS Operating System Reference, https://www.freertos.org/Documentation/RTOS_book.html
* ArduinoJson Tutorial "The Ultimate Guide to Master ArduinoJson", https://arduinojson.org/book

# Pictures

All pictures are dumped in assets/images. Here is a selection of a view pertinent ones:

Head Assembly:
![Head Assembly](assets/images/SN31/head%20assembly/IMG_20200820_183156.jpg)

Breadboard layout:
![Breadboard layout](fritzing/spider_bb.png) 

MCU Controller Board:
![MCU Controller Board](assets/images/SN31/circuit%20boards/IMG_20200906_150346.jpg) 

Servo Controller Board:
![Servo Controller Board](assets/images/SN31/circuit%20boards/IMG_20200822_130836.jpg) 

Legs:
![Legs](assets/images/SN31/legs/IMG_20200822_095125.jpg) 

Pincers:
![Pincers](assets/images/SN31/pincers/IMG_20200823_124845.jpg) 

A partially-complete build:
![Partially complete](assets/images/SN30/IMG_20200731_232911.jpg) 


