#include "launcher.h"
#include "../drivers/gpio.h"
#include "../drivers/button.h"
#include "../drivers/buzzer.h"
#include "../drivers/lcd1602.h"
#include "../drivers/led.h"
#include "../drivers/score_reset.h"
#include "../drivers/uart.h"
#include "../finite_automaton/state_machine.h"
#include "../task_manager/scheduler.h"
#include <avr/interrupt.h>

static inline void init_drivers(void);

void launch_app(void)
{
    init_drivers();
    score_reset();
    init_state_machine();
    init_scheduler();
    sei();
	
    // DON'T USE <util/delay.h> after scheduler launch
    launch_scheduler();
}

static inline void init_drivers(void)
{
    init_gpio();
    init_button();
    init_buzzer();
    init_lcd1602();
    init_led();
    init_score_reset();
    init_uart(F_CPU, 9600, false);
}
