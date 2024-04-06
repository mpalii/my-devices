#ifndef EEPROM_SCORE_SAVING_TASK_H_
#define EEPROM_SCORE_SAVING_TASK_H_

#include <stdint-gcc.h>

#define EEPROM_SCORE_SAVING_TASK_TIME 5

void init_eeprom_score_saving_task(void);
void eeprom_score_saving_task(void);
void eeprom_save_score(uint16_t score);

extern volatile uint8_t eeprom_score_saving_task_time;

#endif /* EEPROM_SCORE_SAVING_TASK_H_ */