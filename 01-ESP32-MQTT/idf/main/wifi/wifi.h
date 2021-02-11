#pragma once
 
#ifndef WIFI_H_INCLUDE
#define WIFI_H_INCLUDE

#include <stdio.h>
#include "esp_wifi.h"
#include "freertos/event_groups.h"

#include "esp_event_loop.h"
#include "esp_log.h"


EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT;

void initialise_wifi(void);

#endif