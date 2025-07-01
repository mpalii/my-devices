/**
 * @author Maksym Palii
 * @brief Gesture-Based Game Controller for Android
 * @version 1.0.0
 * @date 2025 July 08
 */

#include <avr/interrupt.h>
#include <stdbool.h>

#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "drivers/timer_0.h"
#include "drivers/ir_sensors.h"

//**********************************************************
// Task 1
#define T1 20
void task1(void);
volatile uint8_t time1 = T1;

// Task 2
#define T2 1
void task2(void);
volatile uint8_t time2 = T2;

//**********************************************************
//timer 0 compare ISR
ISR(TIMER0_COMPA_vect)
{
    if (time1 > 0) --time1;
    if (time2 > 0) --time2;
}

int main(void)
{
    // Init drivers
    init_gpio();
    init_uart();
    init_timer_0();
	
	// Start system
    sei();                  // Enable global interrupts
    timer_0_start();   // Start system timer

    while (true)
    {
        if (time1 == 0) task1();
        if (time2 == 0) task2();
    }
    
    return 0;
}



void task1(void)
{    
	// re-initialize task 1 timer
    time1 = T1;

	// check IR sensors
	ir_sensors_poll();
}


void task2(void)
{    
	// re-initialize task 2 timer
    time2 = T2;

	if (events_mask & TOP_LEFT_SENSOR_ONCOMING_EVENT_MASK)
	{
        uart_transmit("<011;");
	}

    if (events_mask & TOP_LEFT_SENSOR_DISTANCING_EVENT_MASK)
	{
        uart_transmit("<015;");
	}

    if (events_mask & TOP_RIGHT_SENSOR_ONCOMING_EVENT_MASK)
	{
        uart_transmit("<013;");
	}

    if (events_mask & TOP_RIGHT_SENSOR_DISTANCING_EVENT_MASK)
	{
        uart_transmit("<017;");
	}

    if (events_mask & BOTTOM_LEFT_SENSOR_ONCOMING_EVENT_MASK)
	{
        uart_transmit("<012;");
	}

    if (events_mask & BOTTOM_LEFT_SENSOR_DISTANCING_EVENT_MASK)
	{
        uart_transmit("<016;");
	}

    if (events_mask & BOTTOM_RIGHT_SENSOR_ONCOMING_EVENT_MASK)
	{
        uart_transmit("<014;");
	}

    if (events_mask & BOTTOM_RIGHT_SENSOR_DISTANCING_EVENT_MASK)
	{
        uart_transmit("<018;");
	}

	// clear events
	events_mask = 0;
}