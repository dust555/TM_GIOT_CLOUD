#include "led.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"

static const char *TAG = "LED";

gpio_num_t led_gpio;

void initialize_led(gpio_num_t gpio){
    gpio_pad_select_gpio(gpio);
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio, 0);

    led_gpio = gpio;

    
    ESP_LOGI(TAG, "LED INITIALIZED");
}


void set_led(int value){
    if(value == 1){
        ESP_LOGI(TAG, "TURNING LED ON");
        gpio_set_level(led_gpio, 1);
    }
    else{
        gpio_set_level(led_gpio, 0);
        ESP_LOGI(TAG, "TURNING LED OFF");
    }
}