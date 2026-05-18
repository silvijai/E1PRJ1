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
#include "sound.h"

int main(void) {
  // Inits
  motorInit();
  sensorInit();
  soundInit();

  // Test scripts (Comment out when not in use)
  // motorTest();
  // sensorTest();
  // lightTest();
  // soundTest();

  // Start on button press
  // Setup SW1 as input
  DDRA &= ~(1 << 1);
  
  // Wait for button press
  while (PINA & (1 << 1)); 

  _delay_ms(200);

  playSound(1);

  // Delay for start sound
  _delay_ms(2000);

  runTrack();

  playSound(3);

  // Done
  while(1) { 
    // Finish here :3
  }
}
