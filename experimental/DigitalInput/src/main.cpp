#include "main.h"
#include "DigitalInput.h"
#include <ostream>



// Dummy routine to explain what to do with your queue
// Task to display running status from queue
void inputRead(void* arg){
  DigitalInput * p = NULL;
  for(;;) {
    
    vTaskDelay(1000/portTICK_PERIOD_MS);
    // int i;    
    // if(xQueueReceive(DigitalInput::gpio_input_queue,&i, portMAX_DELAY)) {
    if(xQueueReceive(DigitalInput::gpio_input_queue,(void *)&p, portMAX_DELAY)) {
      // ESP_LOGI(DigitalInput::TAG,"GPIO Pin#: %d", p->gpio_num);
      int i = (int)p->gpio_num;
     /// std::cout << i << std::endl;
    //  ESP_LOGI(DigitalInput::TAG,"In task... GPIO %d", i);
      
    }


    // Receive into data struct
    //if(xQueueReceive(DigitalInput::gpio_input_queue,p, portMAX_DELAY)) {                      
    //  ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu] GPIO Pin: [%u] Pin State: [%d]", DigitalInput::gpio_input_isr_counter, p->gpio_num, p->now_state);
    //}
  }
}


// Bizarre pin assignment for GPIO on ESP32:
#define DigitalInput_IO_0     35
#define DigitalInput_IO_1     34
#define DigitalInput_IO_2     39
#define DigitalInput_IO_3     36

void app_main(void){  
  
  // Create digital inputs
  DigitalInput foot_0(static_cast<gpio_num_t>(DigitalInput_IO_0),"foot 0 down","first front left");
  DigitalInput foot_1(static_cast<gpio_num_t>(DigitalInput_IO_1),"foot 1 down","second front left");
  DigitalInput foot_2(static_cast<gpio_num_t>(DigitalInput_IO_2),"foot 2 down","first front right");
  DigitalInput foot_3(static_cast<gpio_num_t>(DigitalInput_IO_3),"foot 3 down","second front right");
  

  // start gpio demo task to read digital inputs off queue
  xTaskCreate(inputRead, "inputRead", 2048, NULL, 10, NULL);
  

  ESP_LOGW(DigitalInput::TAG, "Minimum free heap size: %d bytes", esp_get_minimum_free_heap_size());

  // idle loop
  while(1){
    ESP_LOGI(DigitalInput::TAG,"Number of digital inputs high: %d", DigitalInput::gpio_input_high_count);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu]", DigitalInput::gpio_input_isr_counter);
    //std::cout << "TEST" << std::endl; 
    /*
    put::TAG,"ISRCalls: [%llu]", DigitalInput::gpio_input_isr_counter);
      if(p != NULL){
        ESP_LOGW(DigitalInput::TAG,"Payload arrived!");
        p = NULL;
        // ESP_LOGI(DigitalInput::TAG,"ISRCalls: [%llu] GPIO Pin: [%u] Pin State: [%d]", DigitalInput::gpio_input_isr_counter, p->gpio_num, p->now_state);
      }         
    }
    */
  }

}
