# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:wakedemo.elf

buzzer.o: buzzer.c buzzer.h
led.o: led.c led.h
toggle_green.o:toggle_green.s stateMachines.h
stateMachines.o: led.h stateMachines.h
switches.o: led.h switches.h
lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h
state_selection.o: state_selection.s wakedemo.h
wakedemo.o: wakedemo.h

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o wdt_handler.o font-11x16.o font-5x7.o lcdutils.o lcddraw.o buzzer.o toggle_green.o stateMachines.o state_selection.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
