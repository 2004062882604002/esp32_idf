#include <stdio.h>
#include <dh_11.h>
#include <nvs_flash.h>

#define DHT11_GPIO	37		// DHT11引脚定义
const static char *TAG = "DHT11_Demo";
int temp = 0,hum = 0;
void app_main(void)
{

    ESP_ERROR_CHECK(nvs_flash_init());
    vTaskDelay(100 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "[APP] APP Is Start!~\r\n");
    ESP_LOGI(TAG, "[APP] IDF Version is %d.%d.%d",ESP_IDF_VERSION_MAJOR,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH);
    ESP_LOGI(TAG, "[APP] Free memory: %lu bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    DHT11_Init(DHT11_GPIO);
    while (1){
        if (DHT11_StartGet(&temp, &hum)){
            ESP_LOGI(TAG, "temp->%i.%i C     hum->%i%%", temp / 10, temp % 10, hum);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
