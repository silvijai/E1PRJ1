#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void initUART();
void sendChar(char Tegn);
void sendCommand(uint8_t CMD, uint8_t Feedback, uint8_t Param1, uint8_t Param2);

#endif
