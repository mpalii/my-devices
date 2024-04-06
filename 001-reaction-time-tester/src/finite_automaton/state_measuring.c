#include "state_measuring.h"
#include "state_machine.h"
#include "../drivers/button.h"
#include "../drivers/buzzer.h"
#include "../drivers/led.h"
#include "../drivers/uart.h"
#include "../task_manager/button_handling_task.h"
#include "../app/metrics.h"
#include "../app/messages.h"
#include <stdio.h>

#define MEASURING_TIMEOUT 1000 // 1000 milliseconds

static char serial_text_buffer[36] = { '\0' };

void handle_measuring_state(void)
{
    if (!is_ready_for_transition())
    {
        sprintf(serial_text_buffer, MEASURING_SERIAL_PATTERN, mcu_operating_time);
        uart_transmit_data(serial_text_buffer);
		
        led_on();
        buzzer_on();
		
        allow_state_transition();
    }
    else
    {
        user_reaction_time++;
    }
	
    if (is_button_event_unhandled()) {
        led_off();
        buzzer_off();
        fast_mode_enabled = false;
        set_device_state(RESULT);
    }
	
    if (user_reaction_time == MEASURING_TIMEOUT)
    {
        led_off();
        buzzer_off();
        fast_mode_enabled = false;
        set_device_state(TIMEOUT);
    }
}
