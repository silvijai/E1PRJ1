#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

// drivers
#include "motor.h"
#include "track.h"

// Test function, for testing the component seperately from the rest of the loop
void motor_test() {
    // Setup Input Buttons (PA2, PA3)
    DDRA &= ~((1 << PA2) | (1 << PA3)); // Set as Inputs
    PORTA |= (1 << PA2) | (1 << PA3);  // Enable internal Pull-ups
    
    bool direction = true;
    int test_speed = 0;

    while (1) {
        // BUTTON 1: Change Direction
        if (!(PINA & (1 << PA2))) {
            _delay_ms(50);
            direction = !direction;
            motor_set_direction(direction);
            while (!(PINA & (1 << PA2))); // Wait for release
            _delay_ms(50);
        }

        // BUTTON 2: Cycle Speed
        if (!(PINA & (1 << PA3))) {
            _delay_ms(50);
            test_speed += 64;
            motor_set_speed(test_speed);
            while (!(PINA & (1 << PA3))); // Wait for release
            _delay_ms(50);
        }
    }
}

int main(void) {
  // Inits
  motor_init();

  // Test scripts (Comment out when not in use)
  // motor_test();

  runTrack();

  // Done
  while(1) {
    // finish here please :3
  }
}