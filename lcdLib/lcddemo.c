/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  //led_init();
  //switch_init();
  //buzzer_init();
  //enableWDTInterrupts();
  lcd_init();
  
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  //fillLowerTriangle(30, 30, 25, COLOR_ORANGE);
  //fillUpperTriangle(30, 55, 25, COLOR_ORANGE);
  fillCross(70, 70, 15, COLOR_ORANGE);
  //fillHouse(40, 40, 35, COLOR_ORANGE);
  //or_sr(0x18);
}

