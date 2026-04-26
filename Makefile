# Configuration
MCU    = atmega2560
F_CPU  = 16000000UL
PORT   = /dev/cu.usbmodem*
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# Rules
all: main.hex

main.elf: $(wildcard *.c)
	avr-gcc $(CFLAGS) -o $@ $^

main.hex: main.elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: main.hex
	avrdude -v -p $(MCU) -c wiring -P $(PORT) -b 115200 -D -U flash:w:$<:i

clean:
	rm -f *.elf *.hex

.PHONY: all flash clean
