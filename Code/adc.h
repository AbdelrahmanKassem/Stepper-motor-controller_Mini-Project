 /******************************************************************************
 *
 * Module: ADC - Configuration
 *
 * File Name: ADC.h
 *
 * Description: ADC..
 *
 * Author: Kassem
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

#define MAX_ADC_STEPS 1024

void ADC_init(void);
void ADC_readChannel(uint8 ChannelNum);

extern volatile uint16 g_adcResult;


#endif /* ADC_H_ */
