#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  static int secCount2 = 0;
  static int secCount3 = 0;
  static int buzzerCount = 0;
  
  /* secCount ++;
  if (secCount == 250) {		// once/sec 
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    }*/

  if (++secCount2 == 50) {
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
  }
  
}
  

void main()
{
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  //or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  /* while (1) {			/* forever */
  /*  if (redrawScreen) {
      redrawScreen = 0;
      drawString11x16(20,20, "hello", fontFgColor, COLOR_BLUE);
    }
    or_sr(0x10);		/**< CPU OFF */
  //}
  or_sr(0x18);
}

    
    



