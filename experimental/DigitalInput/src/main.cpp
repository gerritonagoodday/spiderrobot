#include "main.h"
#include "DigitalInput.h"

// Input GPIO assignment on ESP32:
#define DigitalInput_IO_0     35
#define DigitalInput_IO_1     34
#define DigitalInput_IO_2     39
#define DigitalInput_IO_3     36

// Task to display running status from queue
void ReadQueueTask(void* arg){
  DigitalInput * p = NULL;
  for(;;) {
    if(xQueueReceive(DigitalInput::gpio_input_queue,(void *)&p, portMAX_DELAY)) { 
      // Process the changed inputs... or here, simply display them in the log.           
      ESP_LOGI(DigitalInput::TAG,"Sensor [%s] GPIO: [%u] State: [%d]", p->name.c_str(), p->gpio_num, p->now_state);
    }
  }
}

void app_main(void){  
  // Instantiate digital inputs  
  DigitalInput foot_0(static_cast<gpio_num_t>(DigitalInput_IO_0),"foot 0 down","first front left");  
  DigitalInput foot_1(static_cast<gpio_num_t>(DigitalInput_IO_1),"foot 1 down","second front left"); 
  DigitalInput foot_2(static_cast<gpio_num_t>(DigitalInput_IO_2),"foot 2 down","first front right"); 
  DigitalInput foot_3(static_cast<gpio_num_t>(DigitalInput_IO_3),"foot 3 down","second front right");

  // Create a task that gets the latest inputs off the queue, and in this case, only displays them in the log:
  xTaskCreate(ReadQueueTask, "ReadQueueTask", 2048, NULL, 10, NULL);

  // Idle loop: Constantly display the state of all the inputs:
  while(1){    
    ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu] Sum of Highs: [%d] States: [%d%d%d%d]", DigitalInput::gpio_input_isr_counter, DigitalInput::gpio_input_high_count, foot_0.now_state, foot_1.now_state,foot_2.now_state,foot_3.now_state);    
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
