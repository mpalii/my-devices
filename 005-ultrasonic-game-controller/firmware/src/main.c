/**
 * @author Maksym Palii
 * @brief Gesture-Based Game Controller for Android
 * @version 1.0.0
 * @date 2025 July 08
 */

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

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

// Task 3
#define T3 20UL
void task_3(void);
volatile uint16_t time3 = T3;

// Task 4
#define T4 60000UL
void task_4(void);
volatile uint16_t time4 = T4;

bool button_was_pressed = false;

//**********************************************************
//timer 0 compare ISR
ISR(TIMER0_COMPA_vect)
{
    if (time1 > 0) --time1;
    if (time2 > 0) --time2;
    if (time3 > 0) --time3;
    if (time4 > (uint16_t) 0) --time4;
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
        if (time3 == 0) task_3();
        if ((uint16_t) 0 == time4) task_4();
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

    if (events_mask == 0)
    {
        return;
    }

    time4 = T4;

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

void task_3(void)
{
    // re-initialize task 4 timer
    time3 = T3;

    // check whether button was pressed
    if (!_gpio_get_input(POWER_BUTTON) && !button_was_pressed)
    {
        button_was_pressed = true;
        // button push handling
        /* NOP */
    }
	
    // check whether button was released
    if (_gpio_get_input(POWER_BUTTON) && button_was_pressed)
    {
        button_was_pressed = false;
        //button release handling
        _gpio_low(POWER_CONTROL);
    }
}

void task_4(void)
{
    _gpio_low(POWER_CONTROL);
}