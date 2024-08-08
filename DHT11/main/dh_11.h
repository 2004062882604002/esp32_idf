#pragma once

#include <stdint.h>
#include <driver/rmt_rx.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include "esp32s3/rom/ets_sys.h"
#ifdef __cplusplus
extern "C"{
#endif

    void DHT11_Init(uint8_t dht11_pin);
    static int parse_items(rmt_symbol_word_t *item, int item_num, int *humidity, int *temp_x10);
    static int parse_items(rmt_symbol_word_t *item, int item_num, int *humidity, int *temp_x10);
    int DHT11_StartGet(int *temp_x10, int *humidity);

#ifdef __cplusplus
};
#endif