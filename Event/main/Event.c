#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#define NUM0_BIT BIT0
#define NUM1_BIT BIT1

static EventGroupHandle_t test_event;
static TaskHandle_t taskC_Handle;
static TaskHandle_t taskD_Handle;
void taskA(void *param)
{
    while(1)
    {
        xEventGroupSetBits(test_event,NUM0_BIT);
        vTaskDelay(pdMS_TO_TICKS(1000));
        xEventGroupSetBits(test_event,NUM1_BIT);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void taskB(void* param)
{
    EventBits_t ev;
    while(1)
    {
        ev= xEventGroupWaitBits(test_event,NUM0_BIT|NUM1_BIT,pdTRUE,pdFALSE, pdMS_TO_TICKS(5000));
        if(ev&NUM0_BIT)
        {
            ESP_LOGI("ev","get BIT0 event");
        }
        if(ev&NUM1_BIT)
        {
            ESP_LOGI("ev","get BIT1 event");
        }
    }
}

void taskC(void* param)
{
    uint32_t value=0;
    vTaskDelay(pdMS_TO_TICKS(200));
    while(1)
    {
        xTaskNotify(taskD_Handle,value,eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(1000));
        value++;
    }
}

void taskD(void* param)
{
    uint32_t value;
    while(1)
    {
        xTaskNotifyWait(0x00,ULONG_MAX,&value,portMAX_DELAY);
        ESP_LOGI("ev","notify wait value:%lu",value);
    }

}

void app_main(void)
{
    test_event=xEventGroupCreate();
    xTaskCreatePinnedToCore(taskA,"taskA",2048,NULL,3,NULL,1);
    xTaskCreatePinnedToCore(taskB,"taskB",2048,NULL,3,NULL,1);
    xTaskCreatePinnedToCore(taskC,"taskC",2048,NULL,3,&taskC_Handle,1);
    xTaskCreatePinnedToCore(taskD,"taskD",2048,NULL,3,&taskD_Handle,1);
}
