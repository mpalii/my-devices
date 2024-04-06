#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdbool.h>

typedef enum
{
    READY, 
    WAIT, 
    MEASURING, 
    RESULT,
	FALSE_START,
	TIMEOUT
} e_state;

void init_state_machine(void);
void handle_device_state(void);
void set_device_state(e_state state);
void allow_state_transition(void);
bool is_ready_for_transition(void);

#endif /* STATE_MACHINE_H_ */