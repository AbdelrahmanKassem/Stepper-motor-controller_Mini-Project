  /******************************************************************************
 *
 * Module: LCD - Configuration
 *
 * File Name: LCD.h
 *
 * Description: LCD..
 *
 * Author: Kassem
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define LCD_MODE 8
#define LCD_LINES 2

#define LCD_DATA_DDR DDRC
#define LCD_DATA_PORT PORTC

#if (LCD_MODE == 4)
#define LCD_SEL_PINS 0xF0   /*UPPER PART*/
#endif

#define LCD_CTRL_DDR DDRD
#define LCD_CTRL_PORT PORTD
#define RS PD0
#define RW PD1
#define E  PD2

#define CURSOR_BEGIN_LINE_1 0X80
#define CURSOR_BEGIN_LINE_2 0XC0
#define SHIFT_CURSOR_RIGHT 0X14
#define CLEAR_DISPLAY_SCREEN 0X01
#define ONE_LINE_EIGHT_BIT_MODE 0X30
#define ONE_LINE_FOUR_BIT_MODE 0X20
#define TWO_LINE_EIGHT_BIT_MODE 0X38
#define TWO_LINE_FOUR_BIT_MODE 0X28
#define CURSOR_OFF 0x0C

void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(uint8* string);
void LCD_goToRowColumn(uint8 row , uint8 col);
void LCD_displayStringRowColumn(uint8* string , uint8 row , uint8 col);
void LCD_clearScreen(void);
void LCD_integerToString(int num);

#endif /* LCD_H_ */
