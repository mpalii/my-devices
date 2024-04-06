#ifndef BUTTON_HANDLING_TASK_H_
#define BUTTON_HANDLING_TASK_H_

#include <stdbool.h>
#include <stdint-gcc.h>

#define BUTTON_HANDLING_TASK_TIME 15
#define BUTTON_HANDLING_TASK_TIME_ALTERNATIVE 1

void init_button_handling_task(void);
void button_handling_task(void);

extern volatile uint8_t button_handling_task_time;
extern bool fast_mode_enabled;

#endif /* BUTTON_HANDLING_TASK_H_ */