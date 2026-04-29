#ifndef SENSOR_H_
#define SENSOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
// Reference til lyd i fremtiden
// #include "sound.h"

#define S_DDR DDRD
#define S_PORT PORTD
#define S1_PIN PD0
#define S2_PIN PD1

extern volatile uint8_t count;

void sensorInit(void);

#endif
