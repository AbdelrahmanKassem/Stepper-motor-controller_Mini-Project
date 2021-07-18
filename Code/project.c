/*
 * project.c
 *
 *  Created on: Nov 5, 2020
 *      Author: arahm
 */

#include "project.h"

ISR (INT1_vect)
{
	TOGGLE_BIT(MOTOR_PORT,MOTOR_INPUT1);
	TOGGLE_BIT(MOTOR_PORT,MOTOR_INPUT2);
}


void INT1_config (void)
{
	CLEAR_BIT(DDRD,PD3);
	GICR=(1<<INT1);
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}


void TIMER0_config(void)
{
	DDRB = DDRB | (1<<PB3);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS00);  //| (1<<CS02)
	TCNT0 = 0;

}



int main (void)
{
	SREG |= (1<<7);
	INT1_config ();
	TIMER0_config();
	ADC_init();
	LCD_init();
	uint8 ADCchannel = ADC_CHANNEL_NUMBER ;
	SET_BIT(MOTOR_DDR,MOTOR_INPUT1);
	SET_BIT(MOTOR_PORT,MOTOR_INPUT1);
	SET_BIT(MOTOR_DDR,MOTOR_INPUT2);
	CLEAR_BIT(MOTOR_PORT,MOTOR_INPUT2);
	LCD_displayString("ADC Value = ");

	while(1)
	{

		ADC_readChannel(ADCchannel);
		OCR0 = g_adcResult/4 ;
		LCD_goToRowColumn(0 , 12);
		LCD_integerToString((int)g_adcResult);
		uint16 num = g_adcResult; uint8 digits=0; uint8 i=0;
		while(num != 0)
		{
			num=num/10;
			digits++;
		}
		for(i=digits ; i<4 ; i++)
		{
			LCD_displayCharacter(' ');
		}

	}

}
