#include "helloworld.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include "esp_log.h"


void print_hello_world(int number, char* text){
	int i = 0;
    static const char *TAG = "HELLOWORLD";
	while(1){

        printf("%s - %d! - %d\n",text,number,i);
        ESP_LOGI(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
		vTaskDelay(1500 / portTICK_PERIOD_MS);
		i++;
	}
}

void print_hello_world_param(void * args){
	
    if(NULL != args){
    
        xHelloWorldArgs * Params = (xHelloWorldArgs *) args;

        int number = Params->number;
        char* text = Params->text;
    
        print_hello_world(number,text);
    }
    else{
        print_hello_world(0,"Hello World");
    }
    
}