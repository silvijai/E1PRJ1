# --- Project Configuration ---
MCU          = atmega2560
F_CPU        = 16000000UL
BAUD         = 115200

# --- Toolchain ---
CC           = avr-gcc
OBJCOPY      = avr-objcopy
AVRDUDE      = avrdude

# --- Hardware/Flashing ---
PROGRAMMER   = wiring
PORT         = /dev/cu.usbmodem* 

# --- Files ---
TARGET       = main
# Automatically finds all .c files in the directory so you don't 
# have to manually update this when your group adds files.
SRCS         = $(wildcard *.c)
OBJS         = $(SRCS:.c=.o)

# --- Flags ---
CFLAGS       = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
LDFLAGS      = -mmcu=$(MCU)

# --- Rules ---

# 'build' and 'all' now do the same thing
all: $(TARGET).hex
build: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i

clean:
	rm -f *.o *.elf *.hex

.PHONY: all build flash clean
