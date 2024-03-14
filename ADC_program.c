/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: ANALOG-TO-DIGITAL CONVERTER  ****************/
/***************** File: 	  ADC_program.c  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_config.h"

#ifndef 	NULL  
#define 	NULL (void *)0				  // NULL Equal 0 as pointer to void
#endif


void (*(ADC_PfCallBack))(void) = NULL;  //Global Variable Pointer To Function Follow ADC

void ADC_voidInitialization(void){
	
	/********************* VOLTAGE_REF Initialization **********************/
	#if 	VOLTAGE_REF == EXT_REF
		CLR_BIT(ADMUX ,ADMUX_REFS0);
		CLR_BIT(ADMUX ,ADMUX_REFS1);
	#elif 	VOLTAGE_REF == VCC_REF
		SET_BIT(ADMUX ,ADMUX_REFS0);
		CLR_BIT(ADMUX ,ADMUX_REFS1);
	#elif 	VOLTAGE_REF == INT_REF
		SET_BIT(ADMUX ,ADMUX_REFS0);
		SET_BIT(ADMUX ,ADMUX_REFS1);
	#else
		#error 	"WRONG CHOICE OF VOLTAGE REFERENCE!"
	#endif
	
	/***************************** ALIGNMENT *****************************/
	#if 	ALIGNMENT == RIGHT
		CLR_BIT(ADMUX ,ADMUX_ADLAR);
	#elif 	ALIGNMENT == LEFT
		SET_BIT(ADMUX ,ADMUX_ADLAR);
	#else
		#error 	"WRONG CHOICE OF ALIGNMENT!"
	#endif
	
	/***************************** PRESCALLER *****************************/
	#if 	ADC_Prescaler == DIV_Factor2
		SET_BIT(ADCSRA ,ADCSRA_ADPS0);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS1);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor4
		CLR_BIT(ADCSRA ,ADCSRA_ADPS0);
		SET_BIT(ADCSRA ,ADCSRA_ADPS1);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor8
		SET_BIT(ADCSRA ,ADCSRA_ADPS0);
		SET_BIT(ADCSRA ,ADCSRA_ADPS1);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor16
		CLR_BIT(ADCSRA ,ADCSRA_ADPS0);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS1);
		SET_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor32
		SET_BIT(ADCSRA ,ADCSRA_ADPS0);
		CLR_BIT(ADCSRA ,ADCSRA_ADPS1);
		SET_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor64
		CLR_BIT(ADCSRA ,ADCSRA_ADPS0);
		SET_BIT(ADCSRA ,ADCSRA_ADPS1);
		SET_BIT(ADCSRA ,ADCSRA_ADPS2);
	#elif 	ADC_Prescaler == DIV_Factor128
		SET_BIT(ADCSRA ,ADCSRA_ADPS0);
		SET_BIT(ADCSRA ,ADCSRA_ADPS1);
		SET_BIT(ADCSRA ,ADCSRA_ADPS2);
	#else
		#error 	"WRONG CHOICE OF PRESCALLER!"
	#endif
	
	/***************************** ADC ENABLE *****************************/
	SET_BIT(ADCSRA ,ADCSRA_ADEN);
	
	/****************************** ADC MODE ******************************/
	#if 	MODE == POLLING
		SET_BIT(ADCSRA ,ADCSRA_ADIF);		// CLEAR THE FLAG
		CLR_BIT(ADCSRA ,ADCSRA_ADIE);		// DISABLE INTERRUPT
	#elif 	MODE == INTERRUPT
		SET_BIT(ADCSRA ,ADCSRA_ADIF);		// CLEAR THE FLAG
		SET_BIT(ADCSRA ,ADCSRA_ADIE);		// ENABLE INTERRUPT
	#else
		#error 	"WRONG CHOICE OF ADC MODE!"
	#endif
}

u16  ADC_u16ReadChannelSyn(u8 Copy_u8Channel){
	
	u16 Local_u16Value = 0;
	
	/************************** Channel Selection **************************/
	if(Copy_u8Channel < 8){
		switch(Copy_u8Channel){
			case CHANNEL0 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL1 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL2 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL3 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL4 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL5 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL6 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL7 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
		}
	}
	
	/******************* Start Conversion (Sngle Conversion) *********************/
	SET_BIT(ADCSRA ,ADCSRA_ADSC); 
	
	/********************************** Poolling *********************************/	
	while((GET_BIT(ADCSRA ,ADCSRA_ADIF)) == 0);
	
	/******************************* Clear the Flag ******************************/
	SET_BIT(ADCSRA ,ADCSRA_ADIF);
	
	/************************* Read The Converted Value **************************/
	Local_u16Value = ADC;
	
	return Local_u16Value;
}

void  ADC_voidReadChannelASyn(u8 Copy_u8Channel){
	if(Copy_u8Channel < 8){
		switch(Copy_u8Channel){
			case CHANNEL0 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL1 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL2 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL3 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					CLR_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL4 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL5 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					CLR_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL6 :
					CLR_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
			case CHANNEL7 :
					SET_BIT(ADMUX ,ADMUX_MUX0);
					SET_BIT(ADMUX ,ADMUX_MUX1);
					SET_BIT(ADMUX ,ADMUX_MUX2);
					CLR_BIT(ADMUX ,ADMUX_MUX3);
					CLR_BIT(ADMUX ,ADMUX_MUX4);
					break;
		}
	}
	
	/******************* Start Conversion (Sngle Conversion) *********************/
	SET_BIT(ADCSRA ,ADCSRA_ADSC); 
}

u16  ADC_u16ReadASynValue(void){
	u16 Local_u16Value = 0;
	
	/************************* Read The Converted Value **************************/
	Local_u16Value = ADC;
	
	return Local_u16Value;
}

void ADC_voidSetCallBack(void (*pf)(void)) { /* pf = ADC_Func */
	ADC_PfCallBack = pf;
}

/* takeCare : This Prototype To convince the compiler that it is being called by the processor and make him use it and doesn't ignore it */
void __vector_16 (void) __attribute__((signal ,used));

/*This Function Called Only By Processor (hardware)*/
/* ISR Function For External Interrupt 0*/
void __vector_16(void){
	ADC_PfCallBack();		/* => ADC_Func(); */
}
