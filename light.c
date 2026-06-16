#include "light.h"
#include <avr/io.h>

#define LIGHT_OFF 0
#define LIGHT_HALF 55
#define LIGHT_FULL_FRONT 110
#define LIGHT_FULL_BACK 255

// A is front (PH3 / OC4A), B is back (PH4 / OC4B)

void initLight(void) {
  DDRH |= (1 << PH3) | (1 << PH4);

  TCCR4A = (1 << COM4A1) | (1 << COM4B1) | (1 << WGM40);
  TCCR4B = (1 << WGM42) | (1 << CS41);

  lightOff();
}

void lightStart(void) {
  // Re-enable pins as outputs (lightOff set them to input)
  DDRH |= (1 << PH3) | (1 << PH4);

  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_HALF;

  // Enable PWM for both channels — COM4B1 lives in TCCR4A, not TCCR4B
  TCCR4A |= (1 << COM4A1) | (1 << COM4B1);
}

void lightForward(void) {
  DDRH |= (1 << PH3) | (1 << PH4);

  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_HALF;

  TCCR4A |= (1 << COM4A1) | (1 << COM4B1);
}

void lightReverse(void) {
  DDRH |= (1 << PH3) | (1 << PH4);

  OCR4A = LIGHT_FULL_FRONT;
  OCR4B = LIGHT_FULL_BACK;

  TCCR4A |= (1 << COM4A1) | (1 << COM4B1);
}

void lightOff(void) {
  OCR4A = LIGHT_OFF;
  OCR4B = LIGHT_OFF;

  TCCR4A &= ~(1 << COM4A1);
  TCCR4A &= ~(1 << COM4B1);

  DDRH &= ~(1 << PH3);
  DDRH &= ~(1 << PH4);
  PORTH &= ~(1 << PH3);
  PORTH &= ~(1 << PH4);
}
