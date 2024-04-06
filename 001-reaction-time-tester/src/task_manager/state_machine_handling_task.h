#ifndef STATE_MACHINE_HANDLING_TASK_H_
#define STATE_MACHINE_HANDLING_TASK_H_

#include <stdbool.h>
#include <stdint-gcc.h>

#define STATE_MACHINE_HANDLING_TASK_TIME 1

void init_state_machine_handling_task(void);
void state_machine_handling_task(void);

extern volatile uint8_t state_machine_handling_task_time;

#endif /* STATE_MACHINE_HANDLING_TASK_H_ */