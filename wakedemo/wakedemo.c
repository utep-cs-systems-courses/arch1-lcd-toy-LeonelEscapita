#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "p2switches.h"

#define LED_RED BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
u_char helloCol = 10;
u_char nextHelloCol = 10;
signed char helloVelocity = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;
  static int buzzerCount = 0;

  //Create a switch case with assembly where the cases are the switch buttons, discuss first

  
  secCount ++;
  dsecCount ++;
  if (secCount == 250) {		// once/sec 
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    }
  if (dsecCount == 25) {
    dsecCount = 0;
    nextHelloCol += helloVelocity;
    if (nextHelloCol > 30 || nextHelloCol < 10) { //limit
      helloVelocity = -helloVelocity; //go the other way
      nextHelloCol += helloVelocity; //undo last move
    }
    redrawScreen = 1;
    }
}

void shape_state_default()
{
 if (redrawScreen) {
        redrawScreen = 0;
        drawString11x16(helloCol,helloCol, "hello", COLOR_BLUE, COLOR_BLUE);
        drawString11x16(nextHelloCol,nextHelloCol, "hello", fontFgColor, COLOR_BLUE);
        helloCol = nextHelloCol;
     }
}

void shape_state_0()
{
 if (redrawScreen) {
        redrawScreen = 0;
        fillCross(nextHelloCol, nextHelloCol, 20, fontFgColor);
	fillCross(nextHelloCol, nextHelloCol, 20, COLOR_BLUE);
        helloCol = nextHelloCol;
     }
}

void shape_state_1()
{
 if (redrawScreen) {
        redrawScreen = 0;
        fillHouse(nextHelloCol, nextHelloCol, 30, fontFgColor);
	fillHouse(nextHelloCol, nextHelloCol, 30, COLOR_BLUE);
        helloCol = nextHelloCol;
     }
}

void shape_state_2()
{
  if (redrawScreen) {
        redrawScreen = 0;
        fillLowerTriangle(nextHelloCol, nextHelloCol, 30, fontFgColor);
	fillLowerTriangle(nextHelloCol, nextHelloCol, 30, COLOR_BLUE);
        helloCol = nextHelloCol;
     }

}

void shape_state_3()
{
  if (redrawScreen) {
        redrawScreen = 0;
        fillUpperTriangle(nextHelloCol, nextHelloCol, 30, fontFgColor);
	fillUpperTriangle(nextHelloCol, nextHelloCol, 30, COLOR_BLUE);
        helloCol = nextHelloCol;
     }

}

void state_selection2(char state)
{
  if(state != 0 && state != 1 && state != 2 && state != 3) {
    shape_state_default();
  }
  
  switch(state) {
      case 0:
	shape_state_0();
	break;
      case 1:
	shape_state_1();
	break;
      case 2:
	shape_state_2();
	break;
      case 3:
	shape_state_3();
	break;
  }
  
}
  
void main()
{
  P1DIR |= LED_RED;
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();

  p2sw_init(15);
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
   while (1) { /* forever */
     u_int switches = p2sw_read(), i;
     char str[5];
     char state = 5;
     for (i = 0; i < 4; i++) {
       str[i] = (switches & (1<<i)) ? '-' : '0'+i;
        if(str[i] != '-') {
          state = str[i];
        }
       }
     str[4] = 0;

     state = state_selection(state);
     state_selection2(state);
     
     /*if (redrawScreen) {
             redrawScreen = 0;
             drawString11x16(helloCol,helloCol, str, COLOR_BLUE, COLOR_BLUE);
             helloCol = nextHelloCol;
	     }*/

    P1OUT &= ~LED_RED; //red off
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED; //red on
   }
  
}

    
    



