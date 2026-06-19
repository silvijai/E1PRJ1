#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <stdbool.h>
#include <util/delay.h>

// drivers
#include "light.h"
#include "motor.h"
#include "sensor.h"
#include "sound.h"
#include "tests.h"
#include "track.h"

int main(void) {
  // Inits
  motorInit();
  sensorInit();
  soundInit();
  initLight();

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

  playSound(1);

  _delay_ms(200);

  runTrack();

  _delay_ms(500);

  playSound(3);

  // Done
  while (1) {
    // Finish here :3
  }
}
