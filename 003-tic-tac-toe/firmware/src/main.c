/**
 * @author Maksym Palii
 * @brief Tic Tac Toe
 * @version 1.0
 * @date 2024 April 14
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include "drivers/gpio.h"
#include "drivers/led_matrix.h"
#include "drivers/button_matrix.h"

void init_tasks(void);
void init_timer_0(void);

// Task 1
#define T1 1
void task_1(void);
volatile uint8_t time1;

// Task 2
#define T2 20
void task_2(void);
volatile uint8_t time2;

ISR (TIMER0_COMPA_vect)
{    
    // Adjust task's timers
    if (time1 > 0) --time1;
    if (time2 > 0) --time2;
}

int main(void)
{
    gpio_init();
    init_tasks();
    init_timer_0();
    sei();
	
    while (true)
    {
        if (time1 == 0) task_1();
        if (time2 == 0) task_2();
    }
}

void init_tasks(void)
{
    time1 = T1;
    time2 = T2;
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

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
    // re-initialize task 1 timer
    time1 = T1;

    // Render let matrix element
    render();
}

void task_2(void)
{
    // re-initialize task 2 timer
    time2 = T2;

    // Handle user input
    handle_input();
}
