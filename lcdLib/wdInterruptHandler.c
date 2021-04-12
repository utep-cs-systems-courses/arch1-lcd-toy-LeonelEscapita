#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char blink_count2 = 0;
  static char buzzer_count = 0;

  if (++blink_count == 50) {
    state_advance();
    blink_count = 0;
  }
  if (++blink_count2 == 130) {
    state_advance_sl();
    blink_count2 = 0;
  }
  if (++buzzer_count == 166) { 
    state_advance_buzzer();
    buzzer_count = 0;
  }
  
}
