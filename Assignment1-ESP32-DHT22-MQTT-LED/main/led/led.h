#pragma once
 
#ifndef LED_H_INCLIDE
#define LED_H_INCLIDE


#include "driver/gpio.h"



void initialize_led(gpio_num_t gpio);
void set_led(int value);

 
#endif