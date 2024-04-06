#ifndef SERIAL_TRANSMISSION_TASK_H_
#define SERIAL_TRANSMISSION_TASK_H_

#include <stdint-gcc.h>

#define SERIAL_TRANSMISSION_TASK_TIME 1

void init_serial_transmission_task(void);
void serial_transmission_task(void);

extern volatile uint8_t serial_transmission_task_time;


#endif /* SERIAL_TRANSMISSION_TASK_H_ */