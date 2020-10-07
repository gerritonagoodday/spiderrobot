
# Overview

This is a C++ class used for reading noisy digital switch inputs, by using the rising
and falling edge-detect interrupt method.

This is one possible method of dealing with noisy physical switches that are used as 
actuators in control systems. Another method is to just scan the input levels on a 
regular bases, rather than their rising and falling edges. Either way, the input signals
 are debounced and verified and then published on a queue "DigitalInput::gpio_input_queue"
The debouncing is necessary because the many jittery input transcients can 
cause the edge-detection interrupts to not fire, or if the alternative method were used,
for the levels to not correctly be read.

There are 3 parameters used in debouncing that can be set in the class header file:

GPIO_INPUT_DEBOUNCE_DEPRESS_TIME, set to wait for 20ms on depression of the actuator before noting it as a logical 1.
GPIO_INPUT_DEBOUNCE_RELEASE_TIME, set to wait for 200ms on release of the actuator before noting it as a logical 0.
GPIO_INPUT_DEBOUNCE_SETTLE_TIME, set to 400ms to check if the current state actually does correspond to the recorded state. If not, the recorded state is corrected.

# Usage:

Create a class instance for each of the digital interrupts, and indicate the GPIO, name and a description.

In your main application, read the pointer from the DigitalInput instances from queue DigitalInput::gpio_input_queue and process it accordingly. 

# Example:

See main.cpp:

Here we create 4 instances of class DigitalInput, and then a task ReadQueueTask reads the queue DigitalInput::gpio_input_queue
and displays the active results. First e create the digital inputs:

```c++
// Input GPIO assignment on ESP32:
#define DigitalInput_IO_0     35
#define DigitalInput_IO_1     34
#define DigitalInput_IO_2     39
#define DigitalInput_IO_3     36

DigitalInput foot_0(static_cast<gpio_num_t>(DigitalInput_IO_0),"foot 0 down","first front left");  
DigitalInput foot_1(static_cast<gpio_num_t>(DigitalInput_IO_1),"foot 1 down","second front left"); 
DigitalInput foot_2(static_cast<gpio_num_t>(DigitalInput_IO_2),"foot 2 down","first front right"); 
DigitalInput foot_3(static_cast<gpio_num_t>(DigitalInput_IO_3),"foot 3 down","second front right");
```

Then we create a task that gets the latest inputs off the queue, and in this case only displays them in the log:

```c++
xTaskCreate(ReadQueueTask, "ReadQueueTask", 2048, NULL, 10, NULL);
```

This is how the task processes the digital inputs for now:

```c++
void ReadQueueTask(void* arg){
  DigitalInput * p = NULL;
  for(;;) {
    if(xQueueReceive(DigitalInput::gpio_input_queue,(void *)&p, portMAX_DELAY)) { 
      // Process the changed inputs... or here, simply display them in the log.           
      ESP_LOGI(DigitalInput::TAG,"Sensor [%s] GPIO: [%u] State: [%d]", p->name.c_str(), p->gpio_num, p->now_state);
    }
  }
}

```

The main programm displays the recorded states of these 4 classes. They should be the same. 
A background supervisory task correct and glitches if they are not.

```c++
while(1){    
  ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu] Sum of Highs: [%d] States: [%d%d%d%d]", DigitalInput::gpio_input_isr_counter, DigitalInput::gpio_input_high_count, foot_0.now_state, foot_1.now_state,foot_2.now_state,foot_3.now_state);    
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
```

Here is the log output - note the noisy inputs that needed to be corrected:
```
I (3177) DIN: ISRCalls: [0] Sum of Highs: [0] States: [0000]
I (3267) DIN: Sensor [foot 0 down] GPIO: [35] State: [1]
I (3717) DIN: Sensor [foot 0 down] GPIO: [35] State: [0]
I (4177) DIN: ISRCalls: [2] Sum of Highs: [0] States: [0000]
I (5177) DIN: ISRCalls: [2] Sum of Highs: [0] States: [0000]
I (5517) DIN: Sensor [foot 1 down] GPIO: [34] State: [1]
I (5807) DIN: Sensor [foot 1 down] GPIO: [34] State: [0]
I (5837) DIN: Sensor [foot 1 down] GPIO: [34] State: [1]
I (6177) DIN: ISRCalls: [234] Sum of Highs: [1] States: [0100]
W (6347) DIN_34: Noisy input signal. Correcting level on settle of GPIO 34.
I (6347) DIN: Sensor [foot 1 down] GPIO: [34] State: [0]
I (7177) DIN: ISRCalls: [234] Sum of Highs: [0] States: [0000]
I (7947) DIN: Sensor [foot 2 down] GPIO: [39] State: [1]
I (8177) DIN: ISRCalls: [237] Sum of Highs: [1] States: [0010]
W (8547) DIN_39: Noisy input signal. Correcting level on settle of GPIO 39.
I (8547) DIN: Sensor [foot 2 down] GPIO: [39] State: [0]
I (9177) DIN: ISRCalls: [237] Sum of Highs: [0] States: [0000]
I (10177) DIN: ISRCalls: [237] Sum of Highs: [0] States: [0000]
I (10917) DIN: Sensor [foot 3 down] GPIO: [36] State: [1]
I (11177) DIN: ISRCalls: [238] Sum of Highs: [1] States: [0001]
I (11177) DIN: Sensor [foot 3 down] GPIO: [36] State: [0]
I (11217) DIN: Sensor [foot 3 down] GPIO: [36] State: [1]
W (11647) DIN_36: Noisy input signal. Correcting level on settle of GPIO 36.
I (11647) DIN: Sensor [foot 3 down] GPIO: [36] State: [0]
I (12177) DIN: ISRCalls: [333] Sum of Highs: [0] States: [0000]

```
Here is how to set up the test in hardware:

![Breadboard layout](fritzing/DigitalInputTest.png)
