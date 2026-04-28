#include "motor.h"

static int speed = 0;

void motor_init(void) {
  PWM_DDR |= (1 << PWM_PIN);
  DIR_DDR |= (1 << DIR_PIN);

  // Timer 1 configurations (Mode 5) (Based on setup on page 337 (figure 18) of AVR book)
  TCCR1A = (1 << WGM10); 
  TCCR1B = (1 << WGM12) | (1 << CS11); // Prescaler 8
 
  // Start by setting the speed to 0
  OCR1A = 0;
}

void motor_set_speed(uint8_t s) {
  speed = s;

  if (s == 0) {
    // Disconnect pin from timer
    TCCR1A &= ~(1 << COM1A1);
    OCR1A = 0;
    PWM_PORT &= ~(1 << PWM_PIN); // Force LOW (especially important to switch to reverse)
  } else {
    // Connect timer to pin
    TCCR1A |= (1 << COM1A1);

    OCR1A = s;
  }
}

void motor_set_direction(bool forward) {
  int temp_speed = speed;
  motor_set_speed(0);
  _delay_ms(150);

  if (forward) {
    DIR_PORT &= ~(1 << DIR_PIN);
  } else {
    DIR_PORT |= (1 << DIR_PIN);
  }

  _delay_ms(100);

  motor_set_speed(temp_speed);
}


