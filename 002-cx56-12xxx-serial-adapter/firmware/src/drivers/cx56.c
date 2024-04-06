/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 1.0
*/

#include "cx56.h"

#if (!defined(NO_LEADING_ZEROS_MODE) && !defined(WITH_LEADING_ZEROS_MODE))
# error "Leading mode for CX56 is not specified!"
#endif

#ifndef RADIX
#error "Radix is not specified!"
#endif

#define DIGIT_1 0
#define DIGIT_2 1
#define DIGIT_3 2
#define DIGIT_4 3

// Digits placed from lower to higher
const uint8_t DIGIT_MASKS[] = 
{   
    ~_BV(DIGIT_1), 
    ~_BV(DIGIT_2), 
    ~_BV(DIGIT_3), 
    ~_BV(DIGIT_4)
};

const uint8_t NUMBERS[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101, 0b01111101, 0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111, 0b01110111, 0b01111100,	// 8, 9, A, B
    0b00111001, 0b01011110, 0b01111001, 0b01110001	// C, D, E, F
};

uint8_t current_digit = 0;

void render(uint16_t number) 
{

    if (current_digit >= sizeof(DIGIT_MASKS)) 
    {
        current_digit = 0;
    }

    for (int i = 0; i < current_digit; i++)
    {
        number /= RADIX;
    }

    #ifdef NO_LEADING_ZEROS_MODE
        #ifdef DP_DIGIT
        if (current_digit > DP_DIGIT && number == 0)
        {
            current_digit++;
            return;
        }
        #else
        if (current_digit > 0 && number == 0)
        {
            current_digit++;
            return;
        }
        #endif
    #endif
	
    number %= RADIX;

    // Shift digit related byte
    uint8_t digit_byte = DIGIT_MASKS[current_digit];
    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (digit_byte & (1 << i))
        {
            _DIGIT_DISABLE(SER);
        }
        else
        {
            _DIGIT_ENABLE(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    // Shift number related byte
    uint8_t mapped_number = NUMBERS[number];

    #ifdef DP_DIGIT
    // Adjust digit with dp segment if needed
    if (current_digit == DP_DIGIT) 
    {
        mapped_number |= 1 << 7;
    }
    #endif

    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (mapped_number & (1 << i))
        {
            _SEGMENT_ENABLE(SER);
        }
        else
        {
            _SEGMENT_DISABLE(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    GPIO_LOW(SRCLK);

    GPIO_HIGH(RCLK);
    GPIO_LOW(RCLK);

    current_digit++;
}
