/*
 * LCD.c
 *
 *  Created on: Nov 2, 2020
 *      Author: Kassem
 */

#define ADC_C_
#include "adc.h"

volatile uint16 g_adcResult=0;


void ADC_init(void)
{
	ADMUX= 0;
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

void ADC_readChannel(uint8 ChannelNum)
{
	ADMUX = (ADMUX & 0xE0) | (ChannelNum & 0x07) ;
	ADCSRA |= (1<<ADSC);
	while (BIT_IS_CLEAR(ADCSRA,ADIF))
	{

	}
	CLEAR_BIT(ADCSRA,ADIF);
	g_adcResult=ADC;
}
