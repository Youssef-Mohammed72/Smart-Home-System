/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: External Interrupt	 	   ****************/
/***************** File: 	  EXTI_program.c  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_interface.h"
#include "Exti_private.h"
#include "EXTI_config.h"


#ifndef 	NULL  
#define 	NULL (void *)0				  // NULL Equal 0 as pointer to void
#endif


void (*(EXTI0_PfCallBack))(void) = NULL;  //Global Variable Pointer To Function Follow Interrupt 0
void (*(EXTI1_PfCallBack))(void) = NULL;  //Global Variable Pointer To Function Follow Interrupt 1
void (*(EXTI2_PfCallBack))(void) = NULL;  //Global Variable Pointer To Function Follow Interrupt 2

/************************************************* INTERRUPT 0 ************************************************************/
void EXTI0_voidInitialization(void){
	#if 	EXTI0_SENSE_MODE == EXTI_LOW_LEVEL
		CLR_BIT(MCUCR ,ISC00);
		CLR_BIT(MCUCR ,ISC01);
	#elif 	EXTI0_SENSE_MODE == EXTI_IOC
		SET_BIT(MCUCR ,ISC00);
		CLR_BIT(MCUCR ,ISC01);
	#elif 	EXTI0_SENSE_MODE == EXTI_FALLING
		CLR_BIT(MCUCR ,ISC00);
		SET_BIT(MCUCR ,ISC01);
	#elif 	EXTI0_SENSE_MODE == EXTI_RISING
		SET_BIT(MCUCR ,ISC00);
		SET_BIT(MCUCR ,ISC01);
	#else
		#error 	"Wrong Choice of External interrupt 0 Sense Mode!"
	#endif
	CLR_BIT(GICR ,INT0); 	//Disable Interrupt 0
	SET_BIT(GIFR ,INTF0); 	//Clear External interrupt 0 Flag
}

void EXTI0_voidEnable(void){
	SET_BIT(GICR ,INT0); 	//Enable Interrupt 0
}
void EXTI0_voidDisable(void){
	CLR_BIT(GICR ,INT0); 	//Disable Interrupt 0
}

void EXTIO_voidSetCallBack(void (*pf)(void)) { /* pf = EXTI0_Func */
	EXTI0_PfCallBack = pf;
}

/* takeCare : This Prototype To convince the compiler that it is being called by the processor and make him use it and doesn't ignore it */
void __vector_1 (void) __attribute__((signal ,used));

/*This Function Called Only By Processor (hardware)*/
/* ISR Function For External Interrupt 0*/
void __vector_1(void){
	EXTI0_PfCallBack();		/* => EXTI0_Func(); */
}

/************************************************* INTERRUPT 1 ************************************************************/

void EXTI1_voidInitialization(void){
	#if 	EXTI1_SENSE_MODE == EXTI_LOW_LEVEL
		CLR_BIT(MCUCR ,ISC10);
		CLR_BIT(MCUCR ,ISC11);
	#elif 	EXTI1_SENSE_MODE == EXTI_IOC
		SET_BIT(MCUCR ,ISC10);
		CLR_BIT(MCUCR ,ISC11);
	#elif 	EXTI1_SENSE_MODE == EXTI_FALLING
		CLR_BIT(MCUCR ,ISC10);
		SET_BIT(MCUCR ,ISC11);
	#elif 	EXTI1_SENSE_MODE == EXTI_RISING
		SET_BIT(MCUCR ,ISC10);
		SET_BIT(MCUCR ,ISC11);
	#else
		#error 	"Wrong Choice of External interrupt 1 Sense Mode!"
	#endif

	CLR_BIT(GICR ,INT1); 	//Disable Interrupt 1
	SET_BIT(GIFR ,INTF1); 	//Clear External interrupt 1 Flag
}

void EXTI1_voidEnable(void){
	SET_BIT(GICR ,INT1); 	//Enable Interrupt 1
}

void EXTI1_voidDisable(void){
	CLR_BIT(GICR ,INT1); 	//Disable Interrupt 1
}

void EXTI1_voidSetCallBack(void (*pf)(void)){
	EXTI1_PfCallBack = pf;
}

void __vector_2 (void) __attribute__((signal ,used));

void __vector_2(void){
	EXTI1_PfCallBack();		/* => EXTI1_Func(); */
}


/************************************************* INTERRUPT 2 ************************************************************/
void EXTI2_voidInitialization(void){
	#if 	EXTI2_SENSE_MODE == EXTI_FALLING
		CLR_BIT(MCUCSR ,ISC2);
	#elif 	EXTI2_SENSE_MODE == EXTI_RISING
		SET_BIT(MCUCSR ,ISC2);
	#else
		#error 	"Wrong Choice of External interrupt 2 Sense Mode!"
	#endif

	CLR_BIT(GICR ,INT2); 	//Disable Interrupt 2
	SET_BIT(GIFR ,INTF2); 	//Clear External interrupt 2 Flag
}

void EXTI2_voidEnable(void){
	SET_BIT(GICR ,INT2); 	//Enable Interrupt 2
}

void EXTI2_voidDisable(void){
	CLR_BIT(GICR ,INT2); 	//Disable Interrupt 2
}

void EXTI2_voidSetCallBack(void (*pf)(void)){
	EXTI2_PfCallBack = pf;
}

void __vector_3 (void) __attribute__((signal ,used));

void __vector_3(void){
	EXTI2_PfCallBack();		/* => EXTI2_Func(); */
}


















