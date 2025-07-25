#ifndef GPIO_H_
#define GPIO_H_

/*
 * General purpose IO pins assignment and handling
 * ATmega328P has 23 general purpose IO lines
 * Two 8bit ports (B, D) an one 7bit port (C)
 */

#include <avr/io.h>

// GPIO initialization function prototype
void init_gpio(void);

/*
 * Generic pin map table
 */
#define _PB0    0U
#define _PB1    1U
#define _PB2    2U
#define _PB3    3U
#define _PB4    4U
#define _PB5    5U
#define _PB6    6U
#define _PB7    7U

#define _PC0    8U
#define _PC1    9U
#define _PC2    10U
#define _PC3    11U
#define _PC4    12U
#define _PC5    13U
#define _PC6    14U
// skip 15U value because PC7 pin doesn't exist physically

#define _PD0    16U
#define _PD1    17U
#define _PD2    18U
#define _PD3    19U
#define _PD4    20U
#define _PD5    21U
#define _PD6    22U
#define _PD7    23U

/**
 *          ┌────[●]────┐
 *     PC6  │ 1      28 │  PC5
 *     PD0  │ 2      27 │  PC4
 *     PD1  │ 3      26 │  PC3
 *     PD2  │ 4      25 │  PC2
 *     PD3  │ 5      24 │  PC1
 *     PD4  │ 6      23 │  PC0
 *     VCC  │ 7      22 │  GND
 *     GND  │ 8      21 │  AREF
 *     PB6  │ 9      20 │  AVCC
 *     PB7  │10      19 │  PB5
 *     PD5  │11      18 │  PB4
 *     PD6  │12      17 │  PB3
 *     PD7  │13      16 │  PB2
 *     PB0  │14      15 │  PB1
 *          └───────────┘
 */

/*
 * Hardware pin mapping
 */
#define POWER_CONTROL                   _PB0
#define POWER_BUTTON                    _PB1
#define _GPIO_UNUSED_03                 _PB2
#define _GPIO_UNUSED_04                 _PB3
#define _GPIO_UNUSED_05                 _PB4
#define _GPIO_UNUSED_06                 _PB5
#define XTAL1                           _PB6
#define XTAL2                           _PB7

#define _GPIO_UNUSED_09                 _PC0
#define _GPIO_UNUSED_10                 _PC1
#define IR_SENSOR_BOTTOM_RIGHT          _PC2
#define IR_SENSOR_BOTTOM_LEFT           _PC3
#define IR_SENSOR_TOP_RIGHT             _PC4
#define IR_SENSOR_TOP_LEFT              _PC5
#define RESET                           _PC6

#define UART_RX                         _PD0
#define UART_TX                         _PD1
#define _GPIO_UNUSED_18                 _PD2
#define _GPIO_UNUSED_19                 _PD3
#define _GPIO_UNUSED_20                 _PD4
#define _GPIO_UNUSED_21                 _PD5
#define _GPIO_UNUSED_22                 _PD6
#define _GPIO_UNUSED_23                 _PD7

/*
 * Addresses of DDRx, PORTx and PINx registers have the same offset and equals to 3.
 * It is useful for determining a real register address during a bit manipulation
 * 
 * PINB:Ox03;  PINC:0x06;  PIND:0x09     -> offset = 3U
 * DDRB:0x04;  DDRC:0x07;  DDRD:0x0a     -> offset = 3U
 * PORTB:0x05; PORTC:0x08; PORTD:0x0b    -> offset = 3U
 * 
 * Port B will be a starting point for determining adresses of direction, port, and pin registers for other ports (C, and D)
 */
#define _SFR_OFFSET        (3U)
#define _INIT_DDR_ADDRESS  (&DDRB)
#define _INIT_PORT_ADDRESS (&PORTB)
#define _INIT_PIN_ADDRESS  (&PINB)

/*
 * The main idea is that every value from generic pin map table represents two values: 
 * - pin number (0b00000111 a.k.a 7U mask); 
 * - port number (0b00011000 a.k.a. 3U << 3U, or 3U << GPIO_PORT_OFFSET).
 * 
 * Port number * SFR_OFFSET gives offset for determining the real register address. 
 * It depends on initial DDR, PORT, and PIN addresses.
 */
#define _GPIO_PORT_OFFSET  (3U)
#define _GPIO_PORT_MASK    (3U << _GPIO_PORT_OFFSET)
#define _GPIO_PIN_MASK     (7U)

/*
 * Macro for extracting the physical (hardware) bit value from generic pin value
 */
#define _GPIO_PIN_BIT(GPIO) (1 << (GPIO & _GPIO_PIN_MASK))

/*
 * Macro for extracting the port number from the generic pin value
 */
#define _GPIO_PORT(GPIO) ((GPIO & _GPIO_PORT_MASK) >> _GPIO_PORT_OFFSET)

#define _DDR_ADDRESS(GPIO) (_INIT_DDR_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PORT_ADDRESS(GPIO) (_INIT_PORT_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))
#define _PIN_ADDRESS(GPIO) (_INIT_PIN_ADDRESS + (_GPIO_PORT(GPIO) * _SFR_OFFSET))

// GPIO state manipulation macros
#define _gpio_set_output(GPIO) (*_DDR_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_set_input(GPIO) (*_DDR_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_high(GPIO) (*_PORT_ADDRESS(GPIO) |= _GPIO_PIN_BIT(GPIO))
#define _gpio_low(GPIO) (*_PORT_ADDRESS(GPIO) &= ~_GPIO_PIN_BIT(GPIO))
#define _gpio_toggle(GPIO) (*_PORT_ADDRESS(GPIO) ^= _GPIO_PIN_BIT(GPIO))
#define _gpio_get_input(GPIO) (*_PIN_ADDRESS(GPIO) & _GPIO_PIN_BIT(GPIO))

#endif /* GPIO_H_ */