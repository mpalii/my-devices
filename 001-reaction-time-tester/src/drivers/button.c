#include "button.h"
#include "gpio.h"

static bool button_was_pressed;
static bool button_event;

void init_button(void)
{
    button_was_pressed = false;
    button_event = false;
}

bool is_button_pressed(void)
{
    return ((GPIO_GET_INPUT(BUTTON) == 0) && !button_was_pressed);
}

bool is_button_released(void)
{
    return ((GPIO_GET_INPUT(BUTTON) != 0) && button_was_pressed);
}

void set_button_pressed(void)
{
    button_was_pressed = true;
}

void set_button_released(void)
{
    button_was_pressed = false;
}


bool is_button_event_unhandled(void)
{
    return button_event;
}

void set_button_event_unhandled(void)
{
    button_event = true;
}

void set_button_event_handled(void)
{
    button_event = false;
}