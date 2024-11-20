#ifndef GPIO_H_
#define GPIO_H_

/*
 * General purpose IO pins assignment and handling
 * ATmega328P has 22 general purpose IO lines
 * Two 8bit ports (B, and D), and 7bit port C
 */

#include <avr/io.h>

/*
 * Generic pin map table
 */
#define _PB0                    (0U)
#define _PB1                    (1U)
#define _PB2                    (2U)
#define _PB3                    (3U)
#define _PB4                    (4U)
#define _PB5                    (5U)
#define _PB6                    (6U)
#define _PB7                    (7U)

#define _PC0                    (8U)
#define _PC1                    (9U)
#define _PC2                    (10U)
#define _PC3                    (11U)
#define _PC4                    (12U)
#define _PC5                    (13U)
#define _PC6                    (14U)
// PC7 pin doesn't exist physically - skip 15U value 

#define _PD0                    (16U)
#define _PD1                    (17U)
#define _PD2                    (18U)
#define _PD3                    (19U)
#define _PD4                    (20U)
#define _PD5                    (21U)
#define _PD6                    (22U)
#define _PD7                    (23U)

/*
 * Hardware pin mapping
 */
#define DEADLINE_IND            (_PB0)
#define BUTTON                  (_PB1)
#define LED                     (_PB2)
#define BUZZER                  (_PB3)
#define SCORE_RESET             (_PB4)
#define _GPIO_UNUSED_06         (_PB5)
#define XTAL1                   (_PB6)
#define XTAL2                   (_PB7)

#define LCD_EN                  (_PC0)
#define LCD_RW                  (_PC1)
#define LCD_RS                  (_PC2)
#define _GPIO_UNUSED_12         (_PC3)
#define LCD_PD0                 (_PC4)
#define LCD_PD1                 (_PC5)
#define RESET                   (_PC6)

#define UART_RX                 (_PD0)
#define UART_TX                 (_PD1)
#define LCD_PD2                 (_PD2)
#define LCD_PD3                 (_PD3)
#define LCD_PD4                 (_PD4)
#define LCD_PD5                 (_PD5)
#define LCD_PD6                 (_PD6)
#define LCD_PD7                 (_PD7)

/**
 * Addresses of DDRx, PORTx and PINx registers have the same offset and equals to 3.
 * It is useful for determining a real register address during a bit manipulation
 * 
 * DDRB:0x04;  DDRC:0x07;  DDRD:0x0a     -> offset = 3U
 * PORTB:0x05; PORTC:0x08; PORTD:0x0b    -> offset = 3U
 * PINB:Ox03;  PINC:0x06;  PIND:0x09     -> offset = 3U
 * 
 * Port B will be a starting point for determining adresses of direction, port, and pin registers for other ports (C, and D)
 */
#define _SFR_OFFSET             (3U)
#define _INIT_DDR_ADDRESS       (&DDRB)
#define _INIT_PORT_ADDRESS      (&PORTB)
#define _INIT_PIN_ADDRESS       (&PINB)

/*
 * The main idea is that every value from generic pin map table represents two values: 
 * - pin number (0b00000111 a.k.a 7U mask); 
 * - port number (0b00011000 a.k.a. 3U << 3U, or 3U << GPIO_PORT_OFFSET).
 * 
 * Port number * SFR_OFFSET gives offset for determining the real register address. 
 * It depends on initial DDR, PORT, and PIN addresses.
 */
#define _GPIO_PORT_OFFSET       (3U)
#define _GPIO_PORT_MASK         (3U << _GPIO_PORT_OFFSET)
#define _GPIO_PIN_MASK          (7U)

/*
 * Macro for extracting the physical (hardware) bit value from generic pin value
 */
#define _GPIO_PIN_BIT(GPIO)     (1 << (GPIO & _GPIO_PIN_MASK))

/*
 * Macro for extracting the port number from the generic pin value
 */
#define _GPIO_PORT(GPIO)        ((GPIO & _GPIO_PORT_MASK) >> _GPIO_PORT_OFFSET)

#define _DDR_ADDRESS(GPIO)      (_INIT_DDR_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PORT_ADDRESS(GPIO)     (_INIT_PORT_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PIN_ADDRESS(GPIO)      (_INIT_PIN_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))

// GPIO state manipulation macroses
#define _gpio_set_output(GPIO)  (*_DDR_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_set_input(GPIO)   (*_DDR_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_high(GPIO)        (*_PORT_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_low(GPIO)         (*_PORT_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_toggle(GPIO)      (*_PORT_ADDRESS(GPIO) ^= _GPIO_PIN_BIT(GPIO))
#define _gpio_get_input(GPIO)   (*_PIN_ADDRESS(GPIO) & _GPIO_PIN_BIT(GPIO))

#endif /* GPIO_H_ */



/*

    #define LED                     _PA0
    #define RESET                   _PA1
    #define _GPIO_UNUSED_03         _PA2
    #define _GPIO_UNUSED_04         _PA3
    #define _GPIO_UNUSED_05         _PA4
    #define _GPIO_UNUSED_06         _PA5
    #define _GPIO_UNUSED_07         _PA6
    #define DEADLINE_IND            _PA7

    #define _GPIO_UNUSED_09         _PB0
    #define _GPIO_UNUSED_10         _PB1
    #define _GPIO_UNUSED_11         _PB2
    #define _GPIO_UNUSED_12         _PB3
    #define _GPIO_UNUSED_13         _PB4
    #define _GPIO_UNUSED_14         _PB5
    #define _GPIO_UNUSED_15         _PB6
    #define _GPIO_UNUSED_16         _PB7

    #define LCD_PD0                 _PC0
    #define LCD_PD1                 _PC1
    #define LCD_PD2                 _PC2
    #define LCD_PD3                 _PC3
    #define LCD_PD4                 _PC4
    #define LCD_PD5                 _PC5
    #define LCD_PD6                 _PC6
    #define LCD_PD7                 _PC7

    #define RX                      _PD0
    #define TX                      _PD1
    #define BUTTON                  _PD2    // AKA INT0
    #define _GPIO_UNUSED_28         _PD3
    #define LCD_EN                  _PD4
    #define LCD_RW                  _PD5
    #define LCD_RS                  _PD6
    #define BUZZER                  _PD7    // AKA OC2A



*/