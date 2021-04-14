#ifndef switches_included
#define switches_included

#define SW1 BIT0		/* switch1 is moved ot p2 inputs (green board) */
//#define SWITCHES SW1            /* only 1 switch on this board (commented) */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4) /*makes use of four switches*/

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down[4], switch_state_changed; /* effectively boolean */

#endif // included
