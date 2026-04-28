#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

// drivers
#include "motor.h"
#include "track.h"

int main(void) {
  // Inits
  motor_init();

  // Test scripts (Comment out when not in use)
  motor_test();

  runTrack();

  // Done
  while(1) {
    // finish here please :3
  }
}
