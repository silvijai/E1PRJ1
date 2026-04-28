#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>

#define S_DDR DDRD
#define S_PORT PORTD
#define S1_PIN PD0
#define S2_PIN PD1

volatile uint8_t count = 0;


// Timer interrupt
ISR(TIMER3_COMPA_vect) {
	//Slukker sig selv
	TCCR3B &= ~((1 << CS32) | (1 << CS32) | (1 << CS30));
	EIFR |= (1 << INTF0) | (1 << INTF1);

	//Tænder for sensor
	EIMSK |= (1 << INT0) | (1 << INT1);
}

//Incrementerer count og slukker for sensorne, starter timer til at starte dem igen.
void sensorIncrement() {

	EIMSK &= ~((1 << INT0) | (1 << INT1)); //slukker for sensorne
	count++;

	//starter for Interrupt timer: (COMPA)
	TCNT3 = 0; //sætter timer til 0

	//tænder for timer, sætter prescaler til 1024.
	TCCR3B |= (1 << CS32) | (1 << CS30);
}

// Sensor 1 interrupt
ISR(INT0_vect) {
	sensorIncrement();
}

// Sensor 2 interrupt
ISR(INT1_vect) {
	sensorIncrement();
}


void sensorInit() {
	// set pins as input
	S_DDR &= ~((1 << S1_PIN) | (1 << S2_PIN));

	// enable pull up resistor
	PORTD |= (1 << S1_PIN) | (1 << PD1);

	// Configure the trigger (rising edge)
	// INT0
	EICRA |= (1 << ISC01);
	EICRA &= (1 << ISC00); //ÆNDRET til falling edge for test

	// INT1
	EICRA |= (1 << ISC11);
	EICRA &= (1 << ISC10);  //ÆNDRET til falling edge for test
	
	// Enable specific interrupt mask
	EIMSK |= (1 << INT0) | (1 << INT1);


	//lave en timerInit() måske?
	//Timer 3 setup:
	TCCR3B |= (1 << WGM32); //CTC on
	TIMSK3 |= (1 << OCIE3A); //Timer3 Compare Match A interrupt yuck
	OCR3A = 7812; //Værdi på ca 500ms  ((delay*Fcpu/)prescaler)

	// Global interrupt enable
	sei();


}


//Tænde for LED for at jeg kan se om det virker, slet senere når bil er sat op
void initLEDport()
{
	// Set all LED ports as outputs
	DDRB = 0xFF;
	// Turn off all LED's
	PORTB = 0x00;
	
}


int main(void) {
	// Inits
	sensorInit();
	initLEDport(); //SLET SENERE - Anders' Jank



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
