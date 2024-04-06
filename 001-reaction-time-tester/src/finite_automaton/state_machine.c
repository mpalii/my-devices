#include "state_machine.h"
#include "state_ready.h"
#include "state_wait.h"
#include "state_measuring.h"
#include "state_result.h"
#include "state_false_start.h"
#include "state_timeout.h"
#include "../app/metrics.h"
#include "../drivers/button.h"
#include <avr/eeprom.h>

static e_state device_state;
static bool ready_for_state_transition;

void (*handle_state[])(void) = 
{
    handle_ready_state, 
    handle_wait_state, 
    handle_measuring_state, 
    handle_result_state,
    handle_false_start_state,
    handle_timeout_state
};

void handle_device_state(void)
{
    handle_state[device_state]();
}

void init_state_machine(void)
{
    set_device_state(READY);
    user_reaction_time = 0;
    high_score = eeprom_read_word(SCORE_ADDRESS);
}

void set_device_state(e_state state)
{
    device_state = state;
    ready_for_state_transition = false;
    set_button_event_handled();
}

void allow_state_transition(void)
{
    ready_for_state_transition = true;
}

bool is_ready_for_transition(void)
{
    return ready_for_state_transition;
}