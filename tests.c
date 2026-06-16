#include "motor.h"
#include "sensor.h"
#include "uart.h"
#include "light.h"
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

void lightTest() {
    initLight();
    
    while(1) {
        // Button 1: Gennemkører alle lysstadier
        if (!(PINA & (1 << PA2))) {
            _delay_ms(50);
            lightStart();
            _delay_ms(4000);
            lightReverse();
            _delay_ms(4000);
            lightForward();
            _delay_ms(4000);
            lightOff();
            _delay_ms(4000);
            while (!(PINA & (1 << PA2)));
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
	}
}

void soundTest() {
  // Venter på SOMO startup
	_delay_ms(3000);
  
	// Volume = 20
	sendCommand(0x06, 0x00, 0x00, 50);
	_delay_ms(500);

	// SINGLE PLAY MODE
	sendCommand(0x19, 0x00, 0x00, 0x01);
	_delay_ms(1000);

	// PLAY 001.mp3
	sendCommand(0x03, 0x00, 0x00, 0x01);
	_delay_ms(1000);

	// PLAY 003.mp3
	sendCommand(0x03, 0x00, 0x00, 0x02);

	_delay_ms(1000);
	// PLAY 005.mp3
	sendCommand(0x03, 0x00, 0x00, 0x03);

	while (1)
	{

	}
}
