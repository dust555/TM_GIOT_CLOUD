#include "temperature.h"
#include "DHT.h"

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "../mqtt/mqtt.h"

static const char *TAG = "DHT";
static const char *DEVICE_ID = "u0118137";



void initialize_DHT(int pin){
    setDHTgpio(pin);    
}

void DHT_print_task(void *pvParameter)
{
    
    ESP_LOGI(TAG, "Starting DHT print Task\n\n");

    while (1)
    {
        ESP_LOGI(TAG, "=== Reading DHT ===\n");
        int ret = readDHT();

        errorHandler(ret);

        ESP_LOGI(TAG, "Hum: %.1f Tmp: %.1f\n", getHumidity(), getTemperature());

       
        // -- wait at least 2 sec before reading again ------------
        // The interval of whole process must be beyond 2 seconds !!
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}

void DHT_MQTT_task(void *pvParameter){
    ESP_LOGI(TAG, "Starting DHT print Task\n\n");

    while (1)
    {
        ESP_LOGI(TAG, "=== Reading DHT ===\n");
        int ret = readDHT();

        errorHandler(ret);

        char cPayload[150];
        sprintf(cPayload, "0");
        
        sprintf(cPayload, "{\"device_id\": \"%s\",\"temperature\": \"%.1f\",\"humidity\":\"%.1f\"}", DEVICE_ID, getTemperature(), getHumidity());

        //ESP_LOGI(TAG, cPayload);

        mqtt_publish("u0118137/measurement",cPayload);


        // -- wait at least 2 sec before reading again ------------
        // The interval of whole process must be beyond 2 seconds !!
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}