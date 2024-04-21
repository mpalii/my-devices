/**
 * @author Maksym Palii
 * @brief Led matrix display 3X3
 * @version 1.0
*/

#define COLUMN_SIZE (3U)
#define ROW_SIZE (3U)

#include "led_matrix.h"

uint8_t row_index = 0;
uint8_t column_index = 0;

struct matrix_element element1 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_1, 
    .led_drain_cross_pin = LED_DRAIN_1_X, 
    .led_drain_nought_pin = LED_DRAIN_1_O 
};

struct matrix_element element2 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_2, 
    .led_drain_cross_pin = LED_DRAIN_1_X, 
    .led_drain_nought_pin = LED_DRAIN_1_O 
};

struct matrix_element element3 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_3, 
    .led_drain_cross_pin = LED_DRAIN_1_X, 
    .led_drain_nought_pin = LED_DRAIN_1_O 
};

struct matrix_element element4 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_1, 
    .led_drain_cross_pin = LED_DRAIN_2_X, 
    .led_drain_nought_pin = LED_DRAIN_2_O 
};

struct matrix_element element5 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_2, 
    .led_drain_cross_pin = LED_DRAIN_2_X, 
    .led_drain_nought_pin = LED_DRAIN_2_O 
};

struct matrix_element element6 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_3, 
    .led_drain_cross_pin = LED_DRAIN_2_X, 
    .led_drain_nought_pin = LED_DRAIN_2_O 
};

struct matrix_element element7 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_1, 
    .led_drain_cross_pin = LED_DRAIN_3_X, 
    .led_drain_nought_pin = LED_DRAIN_3_O 
};

struct matrix_element element8 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_2, 
    .led_drain_cross_pin = LED_DRAIN_3_X, 
    .led_drain_nought_pin = LED_DRAIN_3_O 
};

struct matrix_element element9 = 
{ 
    .sign = EMPTY, 
    .led_source_pin = LED_SOURCE_3, 
    .led_drain_cross_pin = LED_DRAIN_3_X, 
    .led_drain_nought_pin = LED_DRAIN_3_O 
};

struct matrix_element *led_matrix[ROW_SIZE][COLUMN_SIZE] = 
{ 
    { &element1, &element2, &element3 },  
    { &element4, &element5, &element6 },  
    { &element7, &element8, &element9 }
};

 void render(void) 
 {
    // reset pins
    GPIO_LOW(LED_SOURCE_1);
    GPIO_LOW(LED_SOURCE_2);
    GPIO_LOW(LED_SOURCE_3);
    GPIO_HIGH(LED_DRAIN_1_X);
    GPIO_HIGH(LED_DRAIN_1_O);
    GPIO_HIGH(LED_DRAIN_2_X);
    GPIO_HIGH(LED_DRAIN_2_O);
    GPIO_HIGH(LED_DRAIN_3_X);
    GPIO_HIGH(LED_DRAIN_3_O);

    struct matrix_element m_element = *led_matrix[row_index][column_index];

    if (m_element.sign != EMPTY)
    {
        GPIO_HIGH(m_element.led_source_pin);
        uint8_t drain_pin = (m_element.sign == CROSS) 
            ? m_element.led_drain_cross_pin 
            : m_element.led_drain_nought_pin;
        GPIO_LOW(drain_pin);
    }

    column_index++;
    if (column_index > (COLUMN_SIZE - 1))
    {
        column_index = 0;
        row_index++;
        if (row_index > (ROW_SIZE - 1))
        {
            row_index = 0;
        }
    }    
 }

 bool line_is_present(void)
 {
    sign sign1, sign2, sign3;

    // Check row 1
    sign1 = led_matrix[0][0]->sign;
    sign2 = led_matrix[0][1]->sign;
    sign3 = led_matrix[0][2]->sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check row 2
    sign1 = led_matrix[1][0] -> sign;
    sign2 = led_matrix[1][1] -> sign;
    sign3 = led_matrix[1][2] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check row 3
    sign1 = led_matrix[2][0] -> sign;
    sign2 = led_matrix[2][1] -> sign;
    sign3 = led_matrix[2][2] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check column 1
    sign1 = led_matrix[0][0] -> sign;
    sign2 = led_matrix[1][0] -> sign;
    sign3 = led_matrix[2][0] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check column 2
    sign1 = led_matrix[0][1] -> sign;
    sign2 = led_matrix[1][1] -> sign;
    sign3 = led_matrix[2][1] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check column 3
    sign1 = led_matrix[0][2] -> sign;
    sign2 = led_matrix[1][2] -> sign;
    sign3 = led_matrix[2][2] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check diagonal 1
    sign1 = led_matrix[0][0] -> sign;
    sign2 = led_matrix[1][1] -> sign;
    sign3 = led_matrix[2][2] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    // Check diagonal 2
    sign1 = led_matrix[0][2] -> sign;
    sign2 = led_matrix[1][1] -> sign;
    sign3 = led_matrix[2][0] -> sign;
    if ((sign1 != EMPTY) && (sign1 == sign2) && (sign1 == sign3))
    return true;

    return false;
 }