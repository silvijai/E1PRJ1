#include <avr/io.h>
#include "light.h"

#define LIGHT_OFF  0
#define LIGHT_HALF 127
#define LIGHT_FULL 255

void initLight(void)
{
    DDRH |= (1 << PH3) | (1 << PH4);

    TCCR4A = (1 << COM4A1) | (1 << COM4B1) | (1 << WGM40);
    TCCR4B = (1 << WGM42) | (1 << CS41);

    lightOff();
}

void lightStart(void)
{
    OCR4A = LIGHT_FULL;
    OCR4B = LIGHT_HALF;
}

void lightForward(void)
{
    OCR4A = LIGHT_FULL;
    OCR4B = LIGHT_HALF;
}

void lightReverse(void)
{
    OCR4A = LIGHT_FULL;
    OCR4B = LIGHT_FULL;
}

void lightOff(void)
{
    OCR4A = LIGHT_OFF;
    OCR4B = LIGHT_OFF;
}
