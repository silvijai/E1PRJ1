#include <avr/io.h>
#include <stdint.h>
#include "sound.h"
#include "uart.h"

void soundInit() {
  // Delay for somo to wake
  _delay_ms(2000);

  initUART();

  // single play mode
  sendCommand(0x19, 0x00, 0x00, 0x01);

  setVolume(30);
}

// max volume 30 (default on startup 20)
void setVolume(uint8_t volume) {
  sendCommand(0x06, 0x00, 0x00, volume);
}

void playSound(uint8_t index) {
  sendCommand(0x03, 0x00, 0x00, index);
}
