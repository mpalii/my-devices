#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
    PRE_READY,
    READY,
    BEFORE_FAST_MODE,
    PRE_WAIT,
    WAIT,
    MEASURING,
    AFTER_FAST_MODE
} e_state;

void handle_device_state(void);
e_state get_device_state(void);

#endif /* STATE_MACHINE_H_ */