#ifndef SOUND_H_
#define SOUND_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

void soundInit(void);
void setVolume(uint8_t volume);
void playSound(uint8_t index);

#endif

