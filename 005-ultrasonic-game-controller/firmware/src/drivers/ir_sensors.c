#include "gpio.h"
#include "ir_sensors.h"

bool previous_state_top_left = true;
bool previous_state_top_right = true;
bool previous_state_bottom_left = true;
bool previous_state_bottom_right = true;

int8_t events_mask = 0;

void ir_sensors_poll(void)
{
    // TOP LEFT SENSOR CHECK
    bool current_state_top_left = _gpio_get_input(IR_SENSOR_TOP_LEFT);

	if (!current_state_top_left && previous_state_top_left)
	{
		previous_state_top_left = false;
		events_mask |= TOP_LEFT_SENSOR_ONCOMING_EVENT_MASK;
	}

	if (current_state_top_left && !previous_state_top_left)
	{
		previous_state_top_left = true;
		events_mask |= TOP_LEFT_SENSOR_DISTANCING_EVENT_MASK;
	}

    // TOP RIGHT SENSOR CHECK
    bool current_state_top_right = _gpio_get_input(IR_SENSOR_TOP_RIGHT);

	if (!current_state_top_right && previous_state_top_right)
	{
		previous_state_top_right = false;
		events_mask |= TOP_RIGHT_SENSOR_ONCOMING_EVENT_MASK;
	}

	if (current_state_top_right && !previous_state_top_right)
	{
		previous_state_top_right = true;
		events_mask |= TOP_RIGHT_SENSOR_DISTANCING_EVENT_MASK;
	}


    // BOTTOM LEFT SENSOR CHECK
    bool current_state_bottom_left = _gpio_get_input(IR_SENSOR_BOTTOM_LEFT);

	if (!current_state_bottom_left && previous_state_bottom_left)
	{
		previous_state_bottom_left = false;
		events_mask |= BOTTOM_LEFT_SENSOR_ONCOMING_EVENT_MASK;
	}

	if (current_state_bottom_left && !previous_state_bottom_left)
	{
		previous_state_bottom_left = true;
		events_mask |= BOTTOM_LEFT_SENSOR_DISTANCING_EVENT_MASK;
	}


    // BOTTOM RIGHT SENSOR CHECK
    bool current_state_bottom_right = _gpio_get_input(IR_SENSOR_BOTTOM_RIGHT);

	if (!current_state_bottom_right && previous_state_bottom_right)
	{
		previous_state_bottom_right = false;
		events_mask |= BOTTOM_RIGHT_SENSOR_ONCOMING_EVENT_MASK;
	}

	if (current_state_bottom_right && !previous_state_bottom_right)
	{
		previous_state_bottom_right = true;
		events_mask |= BOTTOM_RIGHT_SENSOR_DISTANCING_EVENT_MASK;
	}
}
