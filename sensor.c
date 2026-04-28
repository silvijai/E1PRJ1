#include "sensor.h"
#include <avr/interrupt.h>

// Sensor 1 interrupt
ISR(INT0_vect) {
  // Depending on past state, increase count
}

// Sensor 2 interrupt
ISR(INT1_vect) {
  
}

void sensorInit() {
  // set pins as input
  S_DDR &= ~((1 << S1_PIN) | (1 << S2_PIN)); 

  // enable pull up resistor
  PORTD |= (1 << S1_PIN) | (1 << PD1);

  // Configure the trigger (rising edge)
  // INT0
  EICRA |= (1 << ISC01);
  EICRA |= (1 << ISC00);

  // INT1
  EICRA |= (1 << ISC11);
  EICRA |= (1 << ISC10);
  
  // Enable specific interrupt mask
  EIMSK |= (1 << INT0) | (1 << INT1);

  // Global interrupt enable
  sei();
}
