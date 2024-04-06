#ifndef LCD1602_RENDERING_TASK_H_
#define LCD1602_RENDERING_TASK_H_

#include <stdint-gcc.h>

#define LCD1602_RENDERING_TASK_TIME 1

void init_lcd1602_rendering_task(void);
void lcd1602_rendering_task(void);

extern volatile uint8_t lcd1602_rendering_task_time;

#endif /* LCD1602_RENDERING_TASK_H_ */