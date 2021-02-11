#pragma once
 
#ifndef MQTT_H_INCLUDE
#define MQTT_H_INCLUDE

void initialize_mqtt();
void mqtt_publish(char *topic, char *data);


#endif