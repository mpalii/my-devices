#include "state_machine_handling_task.h"
#include "../finite_automaton/state_machine.h"

volatile uint8_t state_machine_handling_task_time;

void init_state_machine_handling_task(void)
{
    state_machine_handling_task_time = STATE_MACHINE_HANDLING_TASK_TIME;
}

void state_machine_handling_task(void)
{
    state_machine_handling_task_time = STATE_MACHINE_HANDLING_TASK_TIME;

    handle_device_state();
}
