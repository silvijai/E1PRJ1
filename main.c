#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

// drivers
#include "tests.h"
#include "motor.h"
#include "track.h"
#include "sensor.h"

int main(void) {
  // Inits
  motorInit();
  sensorInit();

  // Test scripts (Comment out when not in use)
  // motorTest();
  // sensorTest();
  lightTest();

  // Start on button press
  // Setup SW1 as input
  DDRA &= ~(1 << 1);
  
  // Wait for button press
  while (PINA & (1 << 1)); 

  _delay_ms(200);

  runTrack();

  // Done
  while(1) { 
    // Finish here :3
  }
}
