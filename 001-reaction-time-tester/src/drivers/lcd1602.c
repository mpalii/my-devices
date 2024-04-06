#include "lcd1602.h"
#include "gpio.h"
#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>

static void _lcd1602_send_command(char command);
static void _lcd1602_set_data_bus(char data);

static char *message_pointer;

void init_lcd1602(void)
{
    _delay_ms(100);
    _lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
    _delay_ms(5);
    _lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
    _delay_us(100);
    _lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
	
    _delay_us(100);
    _lcd1602_send_command(0b00111000);	// 'Function Set' - 8bit mode, 2 lines, 5x8 font
    _delay_us(53);
    _lcd1602_send_command(0b00001100);	// 'Display ON/OFF Control' display on, cursor off and not blink
    _delay_us(53);
    _lcd1602_send_command(0b00000001);	// 'Clear Display'
    _delay_ms(3);
    _lcd1602_send_command(0b00000110);	// 'Entry Mode Set' cursor shift to right
    _delay_ms(53);
	
    message_pointer = NULL;
}


static void _lcd1602_send_command(char command)
{
    GPIO_LOW(LCD_1602_RS);
    _lcd1602_set_data_bus(command);
    GPIO_HIGH(LCD_1602_E);
    _delay_us(1000);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);
}

static void _lcd1602_set_data_bus(char data)
{
    if (data & 0b00000001) GPIO_HIGH(LCD_1602_PD0);
    else GPIO_LOW(LCD_1602_PD0);

    if (data & 0b00000010) GPIO_HIGH(LCD_1602_PD1);
    else GPIO_LOW(LCD_1602_PD1);

    if (data & 0b00000100) GPIO_HIGH(LCD_1602_PD2);
    else GPIO_LOW(LCD_1602_PD2);

    if (data & 0b00001000) GPIO_HIGH(LCD_1602_PD3);
    else GPIO_LOW(LCD_1602_PD3);
	
    if (data & 0b00010000) GPIO_HIGH(LCD_1602_PD4);
    else GPIO_LOW(LCD_1602_PD4);

    if (data & 0b00100000) GPIO_HIGH(LCD_1602_PD5);
    else GPIO_LOW(LCD_1602_PD5);

    if (data & 0b01000000) GPIO_HIGH(LCD_1602_PD6);
    else GPIO_LOW(LCD_1602_PD6);

    if (data & 0b10000000) GPIO_HIGH(LCD_1602_PD7);
    else GPIO_LOW(LCD_1602_PD7);
}

void lcd1602_print(char *message)
{
    message_pointer = message;
}

void lcd1602_render(void)
{
    if (message_pointer != NULL)
    {
        GPIO_LOW(LCD_1602_E);
        char data = *message_pointer;
		
        if (data == '\0')
        {
            message_pointer = NULL;
            return;
        }
		
        if (data == '\r')
        {
            GPIO_LOW(LCD_1602_RS);
            _lcd1602_set_data_bus(MOVE_CURSOR_TO_POSITION_0_LINE_1);
        }
        else if (data == '\n')
        {
            GPIO_LOW(LCD_1602_RS);
            _lcd1602_set_data_bus(MOVE_CURSOR_TO_POSITION_0_LINE_2);
        }
        else
        {
            GPIO_HIGH(LCD_1602_RS);
            _lcd1602_set_data_bus(data);
        }
		
        GPIO_HIGH(LCD_1602_E);
        message_pointer++;
    }
}
