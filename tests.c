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


void initLightTest() {
	// DDRB (Data Direction Register B) - Set PB5 (Pin 11) as OUTPUT
	DDRB |= (1 << PB5);
  DDRB |= (1 << PB4);
  
  // TCCR1A (Timer/Counter Control Register 1 A)
	// Fast PWM, 8-bit (Mode 5), Clear OC1A on Compare Match
	TCCR1A = (1 << COM1A1) | (1 << WGM10);
	TCCR1B = (1 << WGM12) | (1 << CS11); // Mode 5 (Part 2) + Prescaler 8

  TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
  TCCR2B = (1 << CS21);
  // OCR1A (Output Compare Register 1 A) - Initializing duty cycle to 0
	OCR1A = 0;
  OCR2A = 0;
}

void lightTest() {
  initLightTest();
  // Setup Input Buttons (PA2, PA3)
  DDRA &= ~((1 << PA2) | (1 << PA3) | (1 << PA4) | (1 << PA5)); // Set as Inputs
  PORTA |= (1 << PA2) | (1 << PA3);   // Enable internal Pull-ups


  while (1) {
    // BUTTON Turn on
    if (!(PINA & (1 << PA2))) {
      // Button 1: Full Power
      _delay_ms(50);
      TCCR1A |= (1 << COM1A1); // Ensure pin is connected to PWM
      OCR1A = 120;
      while (!(PINA & (1 << PA2)));
    }

    if (!(PINA & (1 << PA3)))
    { // Button 2: Turn OFF
      _delay_ms(50);
      OCR1A = 0;
      TCCR1A &= ~(1 << COM1A1); // Disconnect PWM to be safe
      while (!(PINA & (1 << PA3)));
    }
  }
  
  if (!(PINA & (1 << PA4))) {
    // Button 1: Full Power
    _delay_ms(50);
    TCCR2A |= (1 << COM2A1); // Ensure pin is connected to PWM
    OCR2A = 120;
    while (!(PINA & (1 << PA4)));
  }

  if (!(PINA & (1 << PA5))) { // Button 2: Turn OFF
    _delay_ms(50);
    OCR2A = 0;
    TCCR2A &= ~(1 << COM2A1); // Disconnect PWM to be safe
    while (!(PINA & (1 << PA5)));
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
