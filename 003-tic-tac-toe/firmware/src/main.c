/**
 * @author Maksym Palii
 * @brief Tic Tac Toe
 * @version 1.0
 * @date 2024 April 14
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/led_matrix.h"
#include "drivers/button_matrix.h"

void init_mode(void);
void init_timer_0(void);

volatile uint32_t mcu_operating_time = 0;

ISR (TIMER0_COMPA_vect)
{    
    mcu_operating_time++;
    render();
}

uint8_t game_mode = 0;
sign user_sign = CROSS;
bool input_enabled = true;
bool user_turn = true;

int main(void)
{
    gpio_init();
    init_mode();
    init_timer_0();
    sei();

    if (game_mode == 1) 
    {
        while (true)
        {
            handle_input_in_evaluation_mode();
            _delay_ms(20);
        }
    }

    if (game_mode == 2)
    {
        while (true)
        {
            if (input_enabled)
            { 
                handle_input(&user_sign);
                _delay_ms(20);

                if (line_is_present())
                {
                    input_enabled = false;
                }
            }
        }
        
    }
	
    // add pin error signal

    // while (true)
    // {
    //     // NOP
    // }
}

void init_mode(void)
{
    if (GPIO_GET_INPUT(MODE_SELECT_1) && GPIO_GET_INPUT(MODE_SELECT_2))
    {
        game_mode = 1;  // evaluation mode
    }

    if (!GPIO_GET_INPUT(MODE_SELECT_1))
    {
        game_mode = 2; // PVP mode
    }

    if (!GPIO_GET_INPUT(MODE_SELECT_2))
    {
        game_mode = 3; // PVM mode
    }
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	124;                     //set the compare reg to 125 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}
