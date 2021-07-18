/*
 * LCD.c
 *
 *  Created on: Nov 2, 2020
 *      Author: Kassem
 */

#include "lcd.h"



void LCD_init(void)
{
	LCD_CTRL_DDR |= (1<<RS) | (1<<RW) | (1<<E);
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if(LCD_LINES == 1 && LCD_MODE == 8)
	LCD_DATA_DDR=0XFF;
	LCD_sendCommand(ONE_LINE_EIGHT_BIT_MODE);
	#elif(LCD_LINES == 1 && LCD_MODE == 4)
	LCD_DATA_DDR|= LCD_SEL_PINS;
	LCD_sendCommand(ONE_LINE_FOUR_BIT_MODE);
	#elif(LCD_LINES == 2 && LCD_MODE == 8)
	LCD_DATA_DDR=0XFF;
	LCD_sendCommand(TWO_LINE_EIGHT_BIT_MODE);
	#elif(LCD_LINES == 2 && LCD_MODE == 4)
	LCD_DATA_DDR|= LCD_SEL_PINS;
	LCD_sendCommand(TWO_LINE_FOUR_BIT_MODE);
	#endif
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_DISPLAY_SCREEN);

}
void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if (LCD_MODE == 8)
	LCD_DATA_PORT = command;
	#elif (LCD_MODE == 4)
	LCD_DATA_PORT=(LCD_DATA_PORT & LCD_SEL_PINS ) | (command & LCD_SEL_PINS);
	_delay_ms(1);
	command = (command << 4) | (command >> 4);
	LCD_DATA_PORT=(LCD_DATA_PORT & LCD_SEL_PINS ) | (command & LCD_SEL_PINS);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	#if (LCD_MODE == 8)
	LCD_DATA_PORT = data;
	#elif (LCD_MODE == 4)
	LCD_DATA_PORT=(LCD_DATA_PORT & LCD_SEL_PINS ) | (data & LCD_SEL_PINS);
	_delay_ms(1);
	data = (data << 4) | (data >> 4);
	LCD_DATA_PORT=(LCD_DATA_PORT & LCD_SEL_PINS ) | (data & LCD_SEL_PINS);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}
void LCD_displayString(uint8* string)
{
	uint8 i=0;
	while(string[i] != '\0')
	{
		LCD_displayCharacter(string[i]);
		i++;
		#if (LCD_LINES == 2)
		if (i == 16)
		{
			LCD_sendCommand(CURSOR_BEGIN_LINE_2);
		}
		#endif
	}
}
void LCD_goToRowColumn(uint8 row , uint8 col)
{
	uint8 i=1;
	if (row == 0)
	{
		LCD_sendCommand(CURSOR_BEGIN_LINE_1);
	}
	else if ( row == 1)
	{
		LCD_sendCommand(CURSOR_BEGIN_LINE_2);
	}
	while (i < col)
	{
		LCD_sendCommand(SHIFT_CURSOR_RIGHT);
		i++;
	}
}
void LCD_displayStringRowColumn(uint8* string , uint8 row , uint8 col)
{
	LCD_goToRowColumn(row , col);
	LCD_displayString(string);

}
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_DISPLAY_SCREEN);
}
void LCD_integerToString(int num)
{
	uint8 string [16];
	itoa(num, string, 10);
	LCD_displayString(string);
}

