#include "scheduler.h"
#include "button_handling_task.h"
#include "state_machine_handling_task.h"
#include "lcd1602_rendering_task.h"
#include "eeprom_score_saving_task.h"
#include "serial_transmission_task.h"
#include "../app/metrics.h"

static void init_timer(void);
static void init_tasks(void);

ISR (TIMER0_COMPA_vect)
{
    mcu_operating_time++;
    if (button_handling_task_time > 0) --button_handling_task_time;
    if (state_machine_handling_task_time > 0) --state_machine_handling_task_time;
    if (lcd1602_rendering_task_time > 0) --lcd1602_rendering_task_time;
    if (eeprom_score_saving_task_time > 0) --eeprom_score_saving_task_time;
    if (serial_transmission_task_time > 0) --serial_transmission_task_time;
}

void init_scheduler(void)
{
    mcu_operating_time = 0;
    init_tasks();
    init_timer();
}

/****************************************************************************/
/* Set up timer 0 for 1 ms timebase                                         */
/* (1024 (prescaler) * 18 (OCR0A + 1)) / 18_432_000 MHz = 0.001s = 1ms      */
/****************************************************************************/
void init_timer(void)
{
    // TCCR0A - Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B - Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02) | _BV(CS00); // clk/1024 (From prescaler)
	
    // OCR0A - Timer/Counter0 Output Compare Register channel A
    OCR0A =	17;                    //set the compare reg to 18 time ticks (zero based)
	
    // TIMSK0 - Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

void init_tasks(void)
{
    init_button_handling_task();
    init_state_machine_handling_task();
    init_lcd1602_rendering_task();
    init_eeprom_score_saving_task();
    init_serial_transmission_task();
}

void launch_scheduler(void)
{
    while (true)
    {
        if (button_handling_task_time == 0) 
        { 
            button_handling_task(); 
        }
		
        if (state_machine_handling_task_time == 0) 
        { 
            state_machine_handling_task(); 
        }
		
        if (lcd1602_rendering_task_time == 0) 
        { 
            lcd1602_rendering_task(); 
        }
		
        if (eeprom_score_saving_task_time == 0)
        {
            eeprom_score_saving_task();
        }
		
        if (serial_transmission_task_time == 0)
        {
            serial_transmission_task();
        }
    }
}