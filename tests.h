#ifndef TESTS_H_
#define TESTS_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "motor.h"


void motorTest(void);
void sensorTest(void);
void countDisplayInit(void);
void countDisplay(void);

#endif
