#pragma once
 
#ifndef TEMPERATURE_H_INCLUDE
#define TEMPERATURE_H_INCLUDE

void initialize_DHT(int pin);
void DHT_print_task(void *pvParameter);
void DHT_MQTT_task(void *pvParameter);

#endif