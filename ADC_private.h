/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: ANALOG-TO-DIGITAL CONVERTER  ****************/
/***************** File: 	  ADC_private.h  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/************************* Registers Addresses *************************/
#define	 	ADMUX 		*((volatile u8 *)0x27)		// ADMUX REFFERENCE SELECTION BIT
#define	 	ADCSRA 		*((volatile u8 *)0x26)		// ADCSRA CONTROL AND STATUS REGISTER
//#define	ADCH 		*((volatile u8 *)0x25)
//#define	ADCL 		*((volatile u8 *)0x24)
#define 	ADC 		*((volatile u16 *)0x24) 	// LITTLE ENDIAN CONCATINATION TO READ CONVERTION VALUE
#define	 	SFIOR 		*((volatile u8 *)0x50)		// Special Function IO Register – SFIOR

/* ADMUX REFFERENCE SELECTION BIT */
#define ADMUX_MUX0		0		// ANALOG CHANNEL AND GAIN SELECTION BIT 0
#define ADMUX_MUX1		1		// ANALOG CHANNEL AND GAIN SELECTION BIT 1
#define ADMUX_MUX2		2		// ANALOG CHANNEL AND GAIN SELECTION BIT 2
#define ADMUX_MUX3		3		// ANALOG CHANNEL AND GAIN SELECTION BIT 3
#define ADMUX_MUX4		4		// ANALOG CHANNEL AND GAIN SELECTION BIT 4
#define ADMUX_ADLAR		5		// ADC LEFT ADJUST RESULT
#define ADMUX_REFS0		6		// REFERENCE SELECTION BIT 0
#define ADMUX_REFS1		7		// REFERENCE SELECTION BIT 1

/* ADCSRA CONTROL AND STATUS REGISTER */
#define ADCSRA_ADPS0	0		// ADC PRESCALER SELECT BIT 0
#define ADCSRA_ADPS1	1		// ADC PRESCALER SELECT BIT 1
#define ADCSRA_ADPS2	2		// ADC PRESCALER SELECT BIT 2
#define ADCSRA_ADIE		3		// ADC INTERRUPT ENABLE
#define ADCSRA_ADIF		4		// ADC INTERRUPT FLAG
#define ADCSRA_ADATE	5		// ADC AUTO TRIGGER ENABLE
#define ADCSRA_ADSC		6		// ADC START CONVERSION
#define ADCSRA_ADEN		7		// ADC ENABLE

/********************* VOLTAGE_REF Initialization **********************/
#define 	EXT_REF 	0
#define 	VCC_REF 	1
#define 	INT_REF 	2

/***************************** PRESCALLER *****************************/
#define 	DIV_Factor2 	0
#define 	DIV_Factor4 	1
#define 	DIV_Factor8 	2
#define 	DIV_Factor16 	3
#define 	DIV_Factor32 	4
#define 	DIV_Factor64	5
#define 	DIV_Factor128	6

/***************************** ALIGNMENT *****************************/
#define  	RIGHT	0
#define 	LEFT	1

/******************************* MODE ********************************/
#define  	POLLING		0
#define 	INTERRUPT	1

#endif /* ADC_PRIVATE_H */
