MCU= atmega328p
CLK= 8000000UL

CFLAGS= -Wall -pedantic
TARGET_FLAGS= -mmcu=${MCU} -Og
CC= avr-gcc
AVRDUDE= avrdude -c usbasp -p m328p -P usb -B 8.0 
__start__: Numbers.h Functions.h main.c
	${CC} ${TARGET_FLAGS} -o build.elf Numbers.h Functions.h main.c

flash: build.elf
	sudo ${AVRDUDE} -e -U flash:w:build.elf

clean: 
	rm *.gch *.o *.elf