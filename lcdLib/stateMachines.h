#ifndef stateMachine_included
#define stateMachine_included

static char sw1_state = 0;

void state_advance();

void state_advance_sl();

void state_advance_buzzer();

char toggle_green();

#endif // included
