#include "eeprom_score_saving_task.h"
#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdint-gcc.h>

uint16_t score_to_save;
unsigned char data_index;
bool in_progress;

// External variables
volatile uint8_t eeprom_score_saving_task_time;

void init_eeprom_score_saving_task(void)
{
    eeprom_score_saving_task_time = EEPROM_SCORE_SAVING_TASK_TIME;
    in_progress = false;
    score_to_save = 0;
    data_index = 0;
}

void eeprom_score_saving_task(void)
{
    eeprom_score_saving_task_time = EEPROM_SCORE_SAVING_TASK_TIME;
	
    if (in_progress && eeprom_is_ready())
    {
        uint8_t *first_byte_address = (uint8_t *) &score_to_save;
		
        if (data_index == 0)
        {
            eeprom_update_byte((uint8_t*) SCORE_ADDRESS, *first_byte_address);
            data_index = 1;
        }
        else if (data_index == 1)
        {
            eeprom_update_byte((uint8_t*) (SCORE_ADDRESS + 1), *(first_byte_address + 1));
            data_index = 0;
            in_progress = false;
        }
    }
}

void eeprom_save_score(uint16_t score)
{
    if (!in_progress)
    {
        score_to_save = score;
        in_progress = true;
    }
}
