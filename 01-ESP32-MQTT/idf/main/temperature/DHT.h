/* 

	DHT22 temperature sensor driver

*/

#ifndef DHT_H_
#define DHT_H_

#define DHT_OK 0
#define DHT_CHECKSUM_ERROR -1
#define DHT_TIMEOUT_ERROR -2

#include <stdio.h>
#include <stdbool.h>

// == function prototypes =======================================

void setDHTgpio(int gpio);
void errorHandler(int response);
int readDHT();
float getHumidity();
float getTemperature();
int getSignalLevel(int usTimeOut, bool state);

#endif