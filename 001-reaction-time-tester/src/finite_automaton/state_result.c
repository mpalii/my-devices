#include "state_result.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/eeprom_score_saving_task.h"
#include "../app/metrics.h"
#include "../app/messages.h"
#include <stdio.h>

static char lcd_text_buffer[36] = { '\0' };
static char serial_text_buffer[36] = { '\0' };

void handle_result_state(void)
{
    if (!is_ready_for_transition())
    {		
        sprintf(serial_text_buffer, RESULT_SERIAL_PATTERN, mcu_operating_time);
        uart_transmit_data(serial_text_buffer);
		
        sprintf(lcd_text_buffer, RESULT_LCD_PATTERN, user_reaction_time);
        lcd1602_print(lcd_text_buffer);
		
        if (user_reaction_time < high_score)
        {
            high_score = user_reaction_time;
            eeprom_save_score(high_score);
        }
		
        allow_state_transition();
    }
	

    if (is_button_event_unhandled() && is_ready_for_transition())
    {
        set_device_state(READY);
    }
}