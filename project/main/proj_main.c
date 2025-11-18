/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include <time.h>

#include "proj_wifi.h"
#include "proj_sntp.h"
#include "proj_mqtt.h"
#include "proj_ds18b20.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 2

static void blink_led(void)
{
    // blink on board LED for a very short period.
    gpio_set_level(BLINK_GPIO, 1);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    gpio_set_level(BLINK_GPIO, 0);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}


void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    wifi_init_sta();
    time_t t = init_sntp();
    ESP_LOGI(TAG,"init_sntp(): %lld", t);
    init_mqtt();
    init_ds18b20();
    esp_log_level_set("*", ESP_LOG_WARN); 
    // ref: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/log.html#dynamic-log-level-control
     
#define payload_len 128
    multi_heap_info_t   heap_info;
    wifi_ap_record_t    ap_info;
    char payload_buf[payload_len];
    time_t start_time = time(0);
    static const time_t publish_interval=60;// publish temperature every 60s
    time_t publish_time = start_time - publish_interval;

    while (1) {
        time_t timestamp = time(0);
        if( timestamp-publish_time >= publish_interval) // time to publish?
        {
            publish_time = timestamp;
            heap_caps_get_info(&heap_info, MALLOC_CAP_8BIT);
            esp_wifi_sta_get_ap_info(&ap_info);
            float temperature=read_ds18b20()*9/5+32.0;
            int len=snprintf(payload_buf, payload_len, "ts:%llu, uptime:%llu, heap total:%u, used:%u, rssi:%d, temp:%5.2f°F",
                timestamp, timestamp-start_time, 
                heap_info.total_free_bytes, heap_info.total_allocated_bytes,
                ap_info.rssi, (float)temperature);
            proj_mqtt_publish("/topic/repeating/C3", payload_buf, len, 0, 0);
        }
        blink_led();
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS); // delay 1s
    }
}
