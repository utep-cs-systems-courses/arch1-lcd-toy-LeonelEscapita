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

  /*if (++secCount2 == 50) {
    state_advance();
    secCount2 = 0;
  }
  
  if (++secCount3 == 80) {
    state_advance_sl();
    secCount3 = 0;
  }
  
  if (++buzzerCount == 100) {
    state_advance_buzzer();
    buzzerCount = 0;
    }*/
}

int switch_selection(int s)
{
  switch(s){
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      return 3;
  }
}

void shape_selection(char* str)
{
  int shape_case;
  for (int i = 0; i < 4; i++) {
    if(str[i] != '-') {
      int s = str[i];
      shape_case = switch_selection(s);
      //shape_case = s;
    }
  }
  switch(shape_case) {
     default:
        if (redrawScreen) {
             redrawScreen = 0;
             drawString11x16(helloCol,helloCol, "hello", COLOR_BLUE, COLOR_BLUE);
             drawString11x16(nextHelloCol,nextHelloCol, "hello", fontFgColor, COLOR_BLUE);
             helloCol = nextHelloCol;
           }
        break;
     case 0:
        break;
  }
  
}
  
void main()
{
  P1DIR |= LED_RED;
  P1OUT |= LED_RED;
  configureClocks();
  lcd_init();
  //led_init();
  buzzer_init();
  //switch_init();

  p2sw_init(15);
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
   while (1) { /* forever */
     u_int switches = p2sw_read(), i;
     char str[5];
     for (i = 0; i < 4; i++)
       str[i] = (switches & (1<<i)) ? '-' : '0'+i;
     str[4] = 0;

     //switch_selection(str);
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

    
    



