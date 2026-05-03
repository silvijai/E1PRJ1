#include "motor.h"
#include "sensor.h"
// Test functions, for testing the component seperately from the rest of the loop

void motorTest() {
    // Setup Input Buttons (PA2, PA3)
    DDRA &= ~((1 << PA2) | (1 << PA3)); // Set as Inputs
    PORTA |= (1 << PA2) | (1 << PA3);  // Enable internal Pull-ups
    
    bool direction = true;
    uint8_t testSpeed = 63;

    while (1) {
        // BUTTON 1: Change Direction
        if (!(PINA & (1 << PA2))) {
            _delay_ms(50);
            direction = !direction;
            motorSetDirection(direction);
            while (!(PINA & (1 << PA2))); // Wait for release
            _delay_ms(50);
        }

        // BUTTON 2: Cycle Speed
        if (!(PINA & (1 << PA3))) {
            _delay_ms(50);
            testSpeed += 64;
            motorSetSpeed(testSpeed);
            while (!(PINA & (1 << PA3))); // Wait for release
            _delay_ms(50);
        }
    }
}

void sensorTest() {
	// Inits
	sensorInit();

  // Set all LED ports as outputs
	DDRB = 0xFF;
	// Turn off all LED's
	PORTB = 0x00;

	// Done
	while(1) {
		//test ved at tænde LED
		if (count % 2 == 0) {
			PORTB = 0b00001111;
		}
		else {
			PORTB = 0x00;
		}

		// finish here please :3
	}
}
