/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER0	  				   ****************/
/***************** File: 	  TIMER0_program.c 		       ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "TIMER0_config.h"

#ifndef 	NULL
#define 	NULL (void *)0				  // NULL Equal 0 as pointer to void
#endif

void (*(TIMER0_CompareMatchCallBack_PF))(void) = NULL;
void (*(TIMER0_OverFlowCallBack_PF))(void) = NULL;

void TIMER0_voidInitialization(){
	/***************** Waveform Generation Mode ******************/
	#if 	TIMER0_WAVEFORM_GENERATION_MODE == NORMAL_MODE
		CLR_BIT(TCCRO ,TCCR0_WGM00);
		CLR_BIT(TCCRO ,TCCR0_WGM01);
		#if TIMER0_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED
			CLR_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == CLEAR_OCO_ON_COMPARE_MATCH
			CLR_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == SET_OCO_ON_COMPARE_MATCH
			SET_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#else
			#error 	"WRONG CHOICE OF TIMER0 NORMAL COMPARE OUTPUT MODE!"
		#endif
	#elif 	TIMER0_WAVEFORM_GENERATION_MODE == PHASE_CORRECT_MODE
		SET_BIT(TCCRO ,TCCR0_WGM00);
		CLR_BIT(TCCRO ,TCCR0_WGM01);
		#if TIMER0_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED
			CLR_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == RESERVED
			SET_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_MODE
			CLR_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_MODE
			SET_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#else
			#error 	"WRONG CHOICE OF TIMER0 PHASE CORRECT PWM COMPARE OUTPUT MODE!"
		#endif
	#elif 	TIMER0_WAVEFORM_GENERATION_MODE == CTC_MODE
		CLR_BIT(TCCRO ,TCCR0_WGM00);
		SET_BIT(TCCRO ,TCCR0_WGM01);
		#if TIMER0_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED
			CLR_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == TOGGLE_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == CLEAR_OCO_ON_COMPARE_MATCH
			CLR_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == SET_OCO_ON_COMPARE_MATCH
			SET_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#else
			#error 	"WRONG CHOICE OF TIMER0 CTC COMPARE OUTPUT MODE!"
		#endif
	#elif 	TIMER0_WAVEFORM_GENERATION_MODE == FAST_PWM_MODE
		SET_BIT(TCCRO ,TCCR0_WGM00);
		SET_BIT(TCCRO ,TCCR0_WGM01);
		#if TIMER0_COMPARE_OUTPUT_MODE == OC0_DISCONNECTED
			CLR_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == RESERVED
			SET_BIT(TCCRO ,TCCR0_COM00);
			CLR_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == NON_INVERTING_MODE
			CLR_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#elif TIMER0_COMPARE_OUTPUT_MODE == INVERTING_MODE
			SET_BIT(TCCRO ,TCCR0_COM00);
			SET_BIT(TCCRO ,TCCR0_COM01);
		#else
			#error 	"WRONG CHOICE OF TIMER0 FAST PWM COMPARE OUTPUT MODE!"
		#endif
	#else
		#error 	"WRONG CHOICE OF TIMER0 WAVEFORM GENERATION MODE!"
	#endif

	/***************************** Prescaller ******************************/
	#if 	TIMER0_Prescaller == TIMER_COUNTER_STOPPED
		CLR_BIT(TCCRO ,TCCR0_CS00);
		CLR_BIT(TCCRO ,TCCR0_CS01);
		CLR_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == CLKIO_NO_PRESCALLING
		SET_BIT(TCCRO ,TCCR0_CS00);
		CLR_BIT(TCCRO ,TCCR0_CS01);
		CLR_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == CLKIO8_FROM_PRESCALLER
		CLR_BIT(TCCRO ,TCCR0_CS00);
		SET_BIT(TCCRO ,TCCR0_CS01);
		CLR_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == CLKIO64_FROM_PRESCALLER
		SET_BIT(TCCRO ,TCCR0_CS00);
		SET_BIT(TCCRO ,TCCR0_CS01);
		CLR_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == CLKIO256_FROM_PRESCALLER
		CLR_BIT(TCCRO ,TCCR0_CS00);
		CLR_BIT(TCCRO ,TCCR0_CS01);
		SET_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == CLKIO1024_FROM_PRESCALLER
		SET_BIT(TCCRO ,TCCR0_CS00);
		CLR_BIT(TCCRO ,TCCR0_CS01);
		SET_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == EXTERNAL_CLK_F_SOURCE_ON_T0_PIN
		CLR_BIT(TCCRO ,TCCR0_CS00);
		SET_BIT(TCCRO ,TCCR0_CS01);
		SET_BIT(TCCRO ,TCCR0_CS02);
	#elif 	TIMER0_Prescaller == EXTERNAL_CLK_R_SOURCE_ON_T0_PIN
		SET_BIT(TCCRO ,TCCR0_CS00);
		SET_BIT(TCCRO ,TCCR0_CS01);
		SET_BIT(TCCRO ,TCCR0_CS02);
	#else
		#error 	"Wrong Choice of TIMER0 Prescaller!"
	#endif
}

void TIMER0_voidOverFlowInterruptEnable(void){
	SET_BIT(TIMSK ,TIMSK_TOIE0);
}


void TIMER0_voidOverFlowInterruptDisable(void){
	CLR_BIT(TIMSK ,TIMSK_TOIE0);
}

void TIMER0_voidCompareMatchInterruptEnable(void){
	SET_BIT(TIMSK ,TIMSK_OCIE0);
}


void TIMER0_voidCompareMatchInterruptDisable(void){
	CLR_BIT(TIMSK ,TIMSK_OCIE0);
}

void TIMER0_voidSetTCNT0(u8 val){
	TCNTO = val;
}

void TIMER0_voidSetOCR0(u8 val){
	OCR0 = val;
}

void TIMER0_voidSetCallBackCompareMatch(void (*Copy_PF)(void)){
	TIMER0_CompareMatchCallBack_PF = Copy_PF;
}

void __vector_10 (void) __attribute__((signal ,used));       //Timer/Counter0 Compare Match
void __vector_10(void){
	TIMER0_CompareMatchCallBack_PF();
}

void TIMER0_voidSetCallBackOverFlow(void (*Copy_PF)(void)){
	TIMER0_OverFlowCallBack_PF = Copy_PF;
}

void __vector_11 (void) __attribute__((signal ,used));		//Timer/Counter0 Overflow
void __vector_11(void){
	TIMER0_OverFlowCallBack_PF();
}
