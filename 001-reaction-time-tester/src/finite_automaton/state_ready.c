#include "state_ready.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/scheduler.h"
#include "../app/metrics.h"
#include "../app/messages.h"
#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char lcd_text_buffer[36] = { '\0' };
static char serial_text_buffer[36] = { '\0' };

void handle_ready_state(void)
{
    if (!is_ready_for_transition())
    {
        sprintf(lcd_text_buffer, READY_SERIAL_PATTERN, mcu_operating_time);
        uart_transmit_data(lcd_text_buffer);
		
        sprintf(serial_text_buffer, READY_LCD_PATTERN, high_score);
        lcd1602_print(serial_text_buffer);
		
        allow_state_transition();
    }
	
    if (is_button_event_unhandled() && is_ready_for_transition())
    {
        set_device_state(WAIT);
    }
}
