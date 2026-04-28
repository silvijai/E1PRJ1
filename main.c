#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

// drivers
#include "tests.h"
#include "motor.h"
#include "track.h"

int main(void) {
  // Inits
  motorInit();

  // Test scripts (Comment out when not in use)
  // motorTest();

  runTrack();

  // Done
  while(1) {
    // finish here please :3
  }
}
