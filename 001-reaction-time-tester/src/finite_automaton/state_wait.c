#include "state_wait.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/button_handling_task.h"
#include "../app/metrics.h"
#include "../app/messages.h"
#include <stdio.h>
#include <stdlib.h>

static char serial_text_buffer[36] = { '\0' };
static uint16_t wait_time;

void handle_wait_state(void)
{
    if (!is_ready_for_transition())
    {		
		
        user_reaction_time = 0;
		
        srand((unsigned int) mcu_operating_time);
        wait_time = 999 + (rand() % 9000);
		
        sprintf(serial_text_buffer, WAIT_SERIAL_PATTERN, mcu_operating_time, wait_time);
        uart_transmit_data(serial_text_buffer);
		
        lcd1602_print(WAIT_LCD_MESSAGE);
		
        fast_mode_enabled = true;
        allow_state_transition();
    }
    else
    {
        if (wait_time > 0) wait_time--;
    }
	
    if (is_button_event_unhandled())
    {
        fast_mode_enabled = false;
        set_device_state(FALSE_START);
    }
	
    if (wait_time == 0)
    {
        set_device_state(MEASURING);
    }
}