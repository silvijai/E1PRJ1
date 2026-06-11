#include <avr/io.h>
#include "light.h"

#define LIGHT_OFF  0
#define LIGHT_HALF 40
#define LIGHT_FULL_FRONT 110
#define LIGHT_FULL_BACK 110

//A is front, B is back

void initLight(void)
{
  DDRH |= (1 << PH3) | (1 << PH4);

  TCCR4A = (1 << COM4A1) | (1 << COM4B1) | (1 << WGM40);
  TCCR4B = (1 << WGM42) | (1 << CS41);

  lightOff();
}

void lightStart(void)
{
  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_HALF;

  TCCR4A |= (1 << COM4A1);
  // TCCR4B |= (1 << COM4A1);
  TCCR4B &= ~(1 << COM4A1);
}

void lightForward(void)
{
  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_HALF;

  TCCR4A |= (1 << COM4A1);
  TCCR4B |= (1 << COM4B1);
}

void lightReverse(void)
{
  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_FULL_BACK;

  TCCR4A |= (1 << COM4A1);
  TCCR4B |= (1 << COM4B1);
}

void lightOff(void)
{
  OCR4A = LIGHT_OFF;
  OCR4B = LIGHT_OFF;

  TCCR4A &= ~(1 << COM4A1); // Disconnect PWM to be safe
  TCCR4B &= ~(1 << COM4B1); // Disconnect PWM to be safe
}
