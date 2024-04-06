#include "button_handling_task.h"
#include "../drivers/button.h"
#include "../finite_automaton/state_machine.h"

volatile uint8_t button_handling_task_time;
bool fast_mode_enabled;

void init_button_handling_task(void)
{
    button_handling_task_time = BUTTON_HANDLING_TASK_TIME;
    fast_mode_enabled = false;
}

void button_handling_task(void)
{
    button_handling_task_time = fast_mode_enabled 
        ? BUTTON_HANDLING_TASK_TIME_ALTERNATIVE 
        : BUTTON_HANDLING_TASK_TIME;

    if (is_button_pressed() && is_ready_for_transition())
    {
        set_button_pressed();
        set_button_event_unhandled();
    }
	
    if (is_button_released())
    {
        set_button_released();
    }
}