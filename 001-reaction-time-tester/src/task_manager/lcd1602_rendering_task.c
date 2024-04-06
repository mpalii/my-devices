#include "lcd1602_rendering_task.h"
#include "../drivers/lcd1602.h"
#include <stdbool.h>
#include <stddef.h>

char *output_buffer;
unsigned char output_buffer_index;
bool in_progress;

// External variables
volatile uint8_t lcd1602_rendering_task_time;

void init_lcd1602_rendering_task(void)
{
    lcd1602_rendering_task_time = LCD1602_RENDERING_TASK_TIME;
}

void lcd1602_rendering_task(void)
{
    lcd1602_rendering_task_time = LCD1602_RENDERING_TASK_TIME;
 
    lcd1602_render();
}
