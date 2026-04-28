#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define PWM_DDR DDRB
#define PWM_PORT PORTB
#define PWM_PIN PB5

#define DIR_DDR DDRA
#define DIR_PORT PORTA
#define DIR_PIN PA0

void motorInit(void);
void motorSetSpeed(uint8_t level);
void motorSetDirection(bool forward);

#endif
