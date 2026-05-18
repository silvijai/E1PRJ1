#include <avr/io.h>
#include <stdint.h>
#include "uart.h"

void initUART() {
	// Baud 9600
	UBRR1H = 0;
	UBRR1L = 103;
	// Enable transmitter
	UCSR1B = (1 << TXEN1);
	// 8 databits
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void sendChar(char character) {
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = character;
}

void sendCommand(uint8_t cmd, uint8_t feedback, uint8_t param1, uint8_t param2) {
	uint16_t checksum;
	checksum = 0xFFFF - (cmd + feedback + param1 + param2) + 1;
	sendChar(0x7E);
	sendChar(cmd);
	sendChar(feedback);
	sendChar(param1);
	sendChar(param2);
	sendChar((checksum >> 8) & 0xFF);
	sendChar(checksum & 0xFF);
	sendChar(0xEF);
}
