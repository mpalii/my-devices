#include "score_reset.h"
#include "gpio.h"
#include <avr/eeprom.h>
#include <stdbool.h>

#define DEFAULT_SCORE 999U

void init_score_reset(void)
{
    // NOP
}

void score_reset(void)
{
    bool is_default_score = (eeprom_read_word(SCORE_ADDRESS) == DEFAULT_SCORE);
    bool is_score_reset = (GPIO_GET_INPUT(SCORE_RESET) == 0);
	
    if (is_score_reset && !is_default_score)
    {
        eeprom_write_word(SCORE_ADDRESS, DEFAULT_SCORE);
    }
}
