#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char toggle_red()		/* always toggle! */
{ 
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

/*char toggle_green()  
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
} */

// My Changes

char toggle_red2()	  
{
  green_on = 0;
  
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green2()
{
  static char state = 0;

  red_on = 0;
  
  switch (state) {
    case 0:
      green_on = 1;
      state = 1;
      break;
    case 1:
      green_on = 0;
      red_on = 1;
      state = 0;
      break;
    }
  return 1;
}

void state_advance()
{
  if(switch_state_down[0]) {
     char changed = 0;  
     static char state = 0;
  
     switch(state) {
       case 0: changed = toggle_red(); state = 1; break;
       case 1: changed = toggle_green(); state = 0; break;
  }

   led_changed = changed;
   led_update();
  }
  else if(switch_state_down[1]) {
    char changed = 0;  
    static char state = 0;
  
    switch(state) {
      case 0: changed = toggle_red2(); state = 1; break;
      case 1: changed = toggle_green2(); state = 0; break;
  }

  led_changed = changed;
  led_update();
  }
}

void state_advance_sl()
{
  if(switch_state_down[2]) {
     char changed = 0;  
     static char state = 0;
  
    switch(state) {
      case 0: changed = toggle_red(); state = 1; break;
      case 1: changed = toggle_green(); state = 0; break;
  }

  led_changed = changed;
  led_update();
  }
  else if(switch_state_down[3]) {
    char changed = 0;  
    static char state = 0;
  
    switch(state) {
      case 0: changed = toggle_red2(); state = 1; break;
      case 1: changed = toggle_green2(); state = 0; break;
  }

  led_changed = changed;
  led_update();
  }
}

void state_advance_buzzer()
{
  static char buzz_state = 0;
  if(switch_state_down[0]) { //C MAJOR
   switch(buzz_state) {
    case 0: buzzer_set_period(3822); buzz_state++; break;
    case 1: buzzer_set_period(3405); buzz_state++; break;
    case 2: buzzer_set_period(3033); buzz_state = 0; break;
  default: buzz_state = 0;
   }
  }
  
  else if(switch_state_down[1]) { //F MAJOR
  switch(buzz_state) {
    case 0: buzzer_set_period(5727); buzz_state++; break;
    case 1: buzzer_set_period(4545); buzz_state++; break;
    case 2: buzzer_set_period(3822); buzz_state = 0; break;
  default: buzz_state = 0;
   }
  }

  else if(switch_state_down[2]) { // Bb MAJOR
  switch(buzz_state) {
    case 0: buzzer_set_period(4290); buzz_state++; break;
    case 1: buzzer_set_period(3407); buzz_state++; break;
    case 2: buzzer_set_period(2863); buzz_state = 0; break;
  default: buzz_state = 0;
   }
  }

  else if(switch_state_down[3]) { // F# MAJOR
  switch(buzz_state) {
    case 0: buzzer_set_period(5410); buzz_state++; break;
    case 1: buzzer_set_period(4290); buzz_state++; break;
    case 2: buzzer_set_period(3607); buzz_state = 0; break;
  default: buzz_state = 0;
   }
  }
  
  else {
    buzzer_set_period(0);
  }

}
