#include "main.h"

const char TAG[] = "EPAPER";


void app_main(void) {
  for(;;){
    ESP_LOGI(TAG,"In main...");
    vTaskDelay(100);

  }
}