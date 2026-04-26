#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

// drivers
#include "motor.h"

int main(void) {
  // Inits
  motor_init();

  // Test scripts (Comment out when not in use)
  motor_test();

  while (1) {
    // do cool logic here
  }
}
