#include "main.h"
#include "DigitalInput.h"
#include <ostream>

// Dummy routine to explain what to do with your queue
// Task to display running status from queue
void ReadQueueTask(void* arg){
  DigitalInput * p = NULL;
  for(;;) {
    if(xQueueReceive(DigitalInput::gpio_input_queue,(void *)&p, portMAX_DELAY)) {            
      ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu] [%s] GPIO Pin: [%u] Pin State: [%d]", DigitalInput::gpio_input_isr_counter, p->name.c_str(), p->gpio_num, p->now_state);
    }
  }
}

// Bizarre pin assignment for GPIO on ESP32:
#define DigitalInput_IO_0     35
#define DigitalInput_IO_1     34
#define DigitalInput_IO_2     39
#define DigitalInput_IO_3     36

void app_main(void){  
  // Create digital inputs
  // and self-register
  DigitalInput foot_0(static_cast<gpio_num_t>(DigitalInput_IO_0),"foot 0 down","first front left");   foot_0.self = &foot_0;
  DigitalInput foot_1(static_cast<gpio_num_t>(DigitalInput_IO_1),"foot 1 down","second front left");  foot_1.self = &foot_1;
  DigitalInput foot_2(static_cast<gpio_num_t>(DigitalInput_IO_2),"foot 2 down","first front right");  foot_2.self = &foot_2;
  DigitalInput foot_3(static_cast<gpio_num_t>(DigitalInput_IO_3),"foot 3 down","second front right"); foot_3.self = &foot_3;

  // start gpio demo task to read digital inputs off queue
  xTaskCreate(ReadQueueTask, "ReadQueueTask", 2048, NULL, 10, NULL);
  ESP_LOGW(DigitalInput::TAG, "Minimum free heap size: %d bytes", esp_get_minimum_free_heap_size());

  // idle loop
  while(1){    
    ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu]", DigitalInput::gpio_input_isr_counter);
    ESP_LOGI(DigitalInput::TAG,"Number of highs: %d", DigitalInput::gpio_input_high_count);
    ESP_LOGI(DigitalInput::TAG,"States: %d%d%d%d", foot_0.now_state, foot_1.now_state,foot_2.now_state,foot_3.now_state);
    
    foot_0.DigitalInput::CheckOnSettleTime();
    foot_1.DigitalInput::CheckOnSettleTime();
    foot_2.DigitalInput::CheckOnSettleTime();
    foot_3.DigitalInput::CheckOnSettleTime();
    
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
