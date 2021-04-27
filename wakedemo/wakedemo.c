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

void shape_state_0()
{
  if (redrawScreen) {
        redrawScreen = 0;
        drawString11x16(helloCol,helloCol, "hello", COLOR_BLUE, COLOR_BLUE);
        drawString11x16(nextHelloCol,nextHelloCol, "hello", fontFgColor, COLOR_BLUE);
        helloCol = nextHelloCol;
     }
}

void state_selection(char state)
{
  switch(state) {
     default:
        shape_state_0();
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
     char state;
     for (i = 0; i < 4; i++) {
       str[i] = (switches & (1<<i)) ? '-' : '0'+i;
        if(str[i] != '-') {
          state = str[i];
        }
       }
     str[4] = 0;

     //state_selection(state);
     if (redrawScreen) {
             redrawScreen = 0;
             drawString11x16(helloCol,helloCol, "hello", COLOR_BLUE, COLOR_BLUE);
             drawString11x16(nextHelloCol,nextHelloCol, "hello", fontFgColor, COLOR_BLUE);
             helloCol = nextHelloCol;
           }
      //fillCross(nextHelloCol, nextHelloCol, 30, fontFgColor);
    P1OUT &= ~LED_RED; //red off
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_RED; //red on
   }
   
  //or_sr(0x18);
}

    
    



