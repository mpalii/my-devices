#include <avr/io.h>
#include "timer_0.h"

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (256 (prescaler) * 72 (OCR0A + 1)) / 18_432_000 MHz = 0.001Sec = 1mSec   */
/****************************************************************************/
void init_timer_0(void)
{
	// TCCR0A – Timer/Counter0 Control Register channel A
	TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
	// OCR0A – Timer/Counter0 Output Compare Register channel A
	OCR0A =	71;                     // Set the compare reg to 72 time ticks (zero based)
	
	// TIMSK0 – Timer/Counter0 Interrupt Mask Register
	TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

void timer_0_start(void)
{
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS02);             // CLK/256 (From prescaler)
}