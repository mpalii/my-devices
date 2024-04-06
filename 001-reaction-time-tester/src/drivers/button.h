#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdbool.h>

void init_button(void);
bool is_button_pressed(void);
bool is_button_released(void);
void set_button_pressed(void);
void set_button_released(void);
bool is_button_event_unhandled(void);
void set_button_event_unhandled(void);
void set_button_event_handled(void);

#endif /* BUTTON_H_ */