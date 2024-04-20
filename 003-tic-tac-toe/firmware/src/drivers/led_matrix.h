#ifndef LED_MATRIX_H_
#define LED_MATRIX_H_

#include "gpio.h"

typedef enum 
{ 
    EMPTY, 
    CROSS, 
    NOUGHT 
} sign;

struct matrix_element
{
    sign sign;
    const uint8_t led_source_pin;
    const uint8_t led_drain_cross_pin;
    const uint8_t led_drain_nought_pin;
};

extern struct matrix_element element1;
extern struct matrix_element element2;
extern struct matrix_element element3;
extern struct matrix_element element4;
extern struct matrix_element element5;
extern struct matrix_element element6;
extern struct matrix_element element7;
extern struct matrix_element element8;
extern struct matrix_element element9;

void render(void);

#endif /* LED_MATRIX_H_ */