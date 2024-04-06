#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint-gcc.h>

void init_scheduler(void);
void launch_scheduler(void);

#endif /* SCHEDULER_H_ */