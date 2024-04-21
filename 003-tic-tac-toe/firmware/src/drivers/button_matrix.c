/**
 * @author Maksym Palii
 * @brief Button matrix keyboard 3X3
 * @version 1.0
*/
#define F_CPU (8000000UL)
#define COLUMN_SIZE (3U)
#define ROW_SIZE (3U)

#include <stdbool.h>
#include "button_matrix.h"
#include "gpio.h"

bool button_1_was_pressed = false;
bool button_2_was_pressed = false;
bool button_3_was_pressed = false;
bool button_4_was_pressed = false;
bool button_5_was_pressed = false;
bool button_6_was_pressed = false;
bool button_7_was_pressed = false;
bool button_8_was_pressed = false;
bool button_9_was_pressed = false;

uint8_t columns[] = { COLUMN1, COLUMN2, COLUMN3 };
uint8_t rows[] = { ROW1, ROW2, ROW3 };

bool *button_flags[ROW_SIZE][COLUMN_SIZE] = 
{
    { &button_1_was_pressed, &button_4_was_pressed, &button_7_was_pressed },
    { &button_2_was_pressed, &button_5_was_pressed, &button_8_was_pressed },
    { &button_3_was_pressed, &button_6_was_pressed, &button_9_was_pressed }
};

sign *sign_matrix[ROW_SIZE][COLUMN_SIZE] =
{
    { &element1.sign, &element2.sign, &element3.sign },
    { &element4.sign, &element5.sign, &element6.sign },
    { &element7.sign, &element8.sign, &element9.sign }
};

void handle_input_in_evaluation_mode(void)
{
    for (uint8_t i = 0; i < COLUMN_SIZE; i++)
    {
        GPIO_HIGH(columns[i]);

        for (uint8_t j = 0; j < ROW_SIZE; j++)
        {
            bool row_high = GPIO_GET_INPUT(rows[j]);
            bool *button_flag = button_flags[i][j];

            // check whether button was pressed
            if (row_high && !*button_flag)
            {
                *button_flag= true;
                
                sign *current_sign = sign_matrix[j][i];
                if (*current_sign == CROSS)
                {
                    *current_sign = NOUGHT;
                }
                else
                {
                    *current_sign = CROSS;
                }
            }

            // check whether button was released
            if (!row_high && *button_flag)
            {
                *button_flag = false;
            }
        }

        GPIO_LOW(columns[i]);
    }
}

void handle_input(sign *user_sign)
{
    for (uint8_t i = 0; i < COLUMN_SIZE; i++)
    {
        GPIO_HIGH(columns[i]);

        for (uint8_t j = 0; j < ROW_SIZE; j++)
        {
            bool row_high = GPIO_GET_INPUT(rows[j]);
            bool *button_flag = button_flags[i][j];

            // check whether button was pressed
            if (row_high && !*button_flag)
            {
                *button_flag= true;
                
                sign *current_sign = sign_matrix[j][i];
                if (*current_sign == EMPTY)
                {
                    *current_sign = *user_sign;
                    *user_sign = (*user_sign == CROSS) ? NOUGHT : CROSS;
                }
            }

            // check whether button was released
            if (!row_high && *button_flag)
            {
                *button_flag = false;
            }
        }

        GPIO_LOW(columns[i]);
    }
}

bool handle_pvm_input(sign *user_sign)
{
    bool input_occured = false;

    for (uint8_t i = 0; i < COLUMN_SIZE; i++)
    {
        if (input_occured)
        {
            continue;
        }
        
        GPIO_HIGH(columns[i]);

        for (uint8_t j = 0; j < ROW_SIZE; j++)
        {
            bool row_high = GPIO_GET_INPUT(rows[j]);
            bool *button_flag = button_flags[i][j];

            // check whether button was pressed
            if (row_high && !*button_flag && !input_occured)
            {
                *button_flag= true;
                
                sign *current_sign = sign_matrix[j][i];
                if (*current_sign == EMPTY)
                {
                    *current_sign = *user_sign;
                    input_occured = true;
                    GPIO_LOW(columns[i]);
                    continue;
                }
            }

            // check whether button was released
            if (!row_high && *button_flag)
            {
                *button_flag = false;
            }
        }

        GPIO_LOW(columns[i]);
    }

    return input_occured;
}