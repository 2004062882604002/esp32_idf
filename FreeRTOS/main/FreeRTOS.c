#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "string.h"

#include "driver/gpio.h"

QueueHandle_t queue_handle =NULL;
SemaphoreHandle_t bin_sem;

typedef struct
{
    int value;
}queue_data_t;

void taskA(void* param)
{
    queue_data_t data;
    while(1)
    {
        if(pdTRUE== xQueueReceive(queue_handle,&data,100))
        {
            ESP_LOGI("queue","receive queue value:%d",data.value);
        }
    }
}

void taskB(void* param)
{
    queue_data_t data;
    memset(&data,0,sizeof (queue_data_t));
    while(1)
    {
        xQueueSend(queue_handle,&data,100);
        vTaskDelay(pdMS_TO_TICKS(1000));
        data.value++;
    }
}

void taskC(void* param)
{
    while (1)
    {
        xSemaphoreGive(bin_sem);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void taskD(void* param)
{
    while(1)
    {
        if(pdTRUE== xSemaphoreTake(bin_sem, portMAX_DELAY))
        {
            ESP_LOGI("bin","task D take binsem success");
        }
    }
}

void app_main(void)
{
    queue_handle= xQueueCreate(10,sizeof (queue_data_t));
    xTaskCreatePinnedToCore(taskA,"taskA",2048,NULL,3,NULL,1);
    xTaskCreatePinnedToCore(taskB,"taskB",2048,NULL,3,NULL,1);

    bin_sem=xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore(taskC,"taskC",2048,NULL,3,NULL,1);
    xTaskCreatePinnedToCore(taskD,"taskD",2048,NULL,3,NULL,1);
}
