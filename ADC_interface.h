/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: ANALOG-TO-DIGITAL CONVERTER  ****************/
/***************** File: 	  ADC_interface.h  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

void ADC_voidInitialization(void);
u16  ADC_u16ReadChannelSyn(u8 Copy_u8Channel);
void  ADC_voidReadChannelASyn(u8 Copy_u8Channel);
void ADC_voidSetCallBack(void (*pf)(void));  	// This Function For Take An Address f=>From main.c And Pass it to HMCAL (EXTI Destination)
u16  ADC_u16ReadASynValue(void);

/************************** Channel Selection **************************/
enum channel{
CHANNEL0,
CHANNEL1,
CHANNEL2,
CHANNEL3,
CHANNEL4,
CHANNEL5,
CHANNEL6,
CHANNEL7
};

#endif /* ADC_INTERFACE_H */
