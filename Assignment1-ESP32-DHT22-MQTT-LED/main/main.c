/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"


#include <string.h>
#include <math.h>

#include "helloworld.h"

#include "mqtt/mqtt.h"

#include "wifi/wifi.h"
#include "time/time.h"
#include "led/led.h"
#include "temperature/temperature.h"

void app_main()
{

    

	// Initialize NVS.
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );


	initialise_wifi();

	initialize_time();

    initialize_mqtt();

    initialize_led(GPIO_NUM_13);

    initialize_DHT(GPIO_NUM_32);

    //xTaskCreate(&DHT_print_task, "DHT_task", 2048, NULL, 5, NULL);
    xTaskCreate(&DHT_MQTT_task, "DHT_task", 2048, NULL, 5, NULL);

}



