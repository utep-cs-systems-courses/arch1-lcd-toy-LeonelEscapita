all: libLcd.a lcddemo.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

libLcd.a: font-11x16.o font-5x7.o font-8x12.o lcdutils.o lcddraw.o buzzer.o led.o toggle_green.o wdInterruptHandler.o p2_interrupt_handler.o stateMachines.o switches.o
	$(AR) crs $@ $^



buzzer.o: buzzer.c buzzer.h
led.o: led.c led.h
toggle_green.o:toggle_green.s stateMachines.h
wdInterruptHandler.o: stateMachines.h
p2_interrupt_handler.o: switches.h
stateMachines.o: led.h stateMachines.h
switches.o: led.h switches.h

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libLcd.a *.o *.elf

lcddemo.elf: lcddemo.o libLcd.a 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 

lcddemo2.elf: lcddemo2.o libLcd.a 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 

load: lcddemo.elf
	msp430loader.sh $^

load2: lcddemo2.elf
	msp430loader.sh $^
