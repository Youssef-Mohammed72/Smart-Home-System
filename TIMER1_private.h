/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER1 	  				   ****************/
/***************** File: 	  TIMER1_private.h 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

/************************* Registers Addresses *************************/
	/****** Timer/Counter1 Control Register A – TCCR1A ******/
#define TCCR1A *((volatile u8*)0x4F)

	/****** Timer/Counter1 Control Register B – TCCR1B ******/
#define TCCR1B *((volatile u8*)0x4E)

	/****** Timer/Counter1 – TCNT1H and TCNT1L ******/
//#define TCNT1H *((volatile u8*)0x4D)
//#define TCNT1L *((volatile u8*)0x4C)
#define TCNT1    *((volatile u16*)0x4C)

	/****** Output Compare Register 1 A – OCR1AH and OCR1AL ******/
//#define OCR1AH *((volatile u8*)0x4B)
//#define OCR1AL *((volatile u8*)0x4A)
#define OCR1A    *((volatile u16*)0x4A)

	/****** Output Compare Register 1 B – OCR1BH and OCR1BL ******/
//#define OCR1BH *((volatile u8*)0x49)
//#define OCR1BL *((volatile u8*)0x48)
#define OCR1B    *((volatile u16*)0x48)

	/****** Input Capture Register 1 – ICR1H and ICR1L ******/
//#define ICR1H *((volatile u8*)0x47)
//#define ICR1L *((volatile u8*)0x46)
#define ICR1    *((volatile u16*)0x46)


	/****** Timer/Counter Interrupt Mask Register – TIMSK ******/
#define 	TIMSK	*((volatile u8*)0x59)

	/****** Timer/Counter Interrupt Flag Register – TIFR  ******/
#define 	TIFR	*((volatile u8*)0x58)

/***************************** TCCR1A *****************************/
#define 	TCCR1A_WGM10		0		// Waveform Generation Mode PIN0
#define 	TCCR1A_WGM11		1		// Waveform Generation Mode PIN1
#define 	TCCR1A_FOC1B 		2		// Force Output Compare for Compare unit B
#define 	TCCR1A_FOC1A		3		// Force Output Compare for Compare unit A
#define 	TCCR1A_COM1B0  		4		// Compare Output Mode for Compare unit B PIN0
#define 	TCCR1A_COM1B1		5		// Compare Output Mode for Compare unit B PIN1
#define 	TCCR1A_COM1A0		6		// Compare Output Mode for Compare unit A PIN0
#define 	TCCR1A_COM1A1		7		// Compare Output Mode for Compare unit A PIN1

/***************************** TCCR1B *****************************/
#define 	TCCR1B_CS10 		0		// Clock Select PIN0
#define 	TCCR1B_CS11 		1		// Clock Select PIN1
#define 	TCCR1B_CS12 		2		// Clock Select PIN2
#define 	TCCR1B_WGM12 		3		// Waveform Generation Mode PIN0
#define 	TCCR1B_WGM13		4		// Waveform Generation Mode PIN1
#define 	TCCR1B_PIN5			5		// Reserved Bit
#define 	TCCR1B_ICES1		6		// Input Capture Edge Select
#define 	TCCR1B_ICNC1		7		// Input Capture Noise Canceler

/***************************** TIMSK *****************************/
#define 	TIMSK_TOIE1			2		// Timer/Counter1, Overflow Interrupt Enable
#define 	TIMSK_OCIE1B		3		// Timer/Counter1, Output Compare B Match Interrupt Enable
#define 	TIMSK_OCIE1A		4		// Timer/Counter1, Output Compare A Match Interrupt Enable
#define 	TIMSK_TICIE1		5		// Timer/Counter1, Input Capture Interrupt Enable

/***************************** TIFR *****************************/
#define 	TIFR_TOV1			2		// Timer/Counter1, Overflow Flag
#define 	TIFR_OCF1B 			3		// Timer/Counter1, Output Compare B Match Flag
#define 	TIFR_OCF1A			4		// Timer/Counter1, Output Compare A Match Flag
#define 	TIFR_ICF1			5		// Timer/Counter1, Input Capture Flag

/***************** TIMER1 WAVE FORM GENERATION MODE **************/
#define		NORMAL_MODE										0
#define		PWM_PHASE_CORRECT_8_BIT_MODE					1
#define		PWM_PHASE_CORRECT_9_BIT_MODE					2
#define		PWM_PHASE_CORRECT_10_BIT_MODE					3
#define		CTC_OCR1A_MODE									4
#define		FAST_PWM_8_BIT_MODE								5
#define		FAST_PWM_9_BIT_MODE								6
#define		FAST_PWM_10_BIT_MODE							7
#define		PWM_ICR1_PHASE_AND_FREQUENCY_CORRECT_MODE		8
#define		PWM_OCR1A_PHASE_AND_FREQUENCY_CORRECT_MODE 		9
#define		PWM_ICR1_PHASE_CORRECT_MODE						10
#define		PWM_OCR1A_PHASE_CORRECT_MODE					11
#define		CTC_ICR1_MODE									12
#define		FAST_PWM_ICR1_MODE								14
#define		FAST_PWM_OCR1A_MODE								15

/******************** TIMER1 COMPARE OUTPUT MODE ********************/

	/********* BELONG TO ALL WAVE FORM GENERATION MODE *********/
#define		OC1A_OC1B_DISCONNECTED 									0

	/********* BELONG TO NON-PWM WAVEFORM GENERATION MODE ******/
#define		TOGGLE_OC1A_OC1B_ON_COMPARE_MATCH						1
#define		CLEAR_OC1A_OC1B_ON_COMPARE_MATCH						2
#define		SET_OC1A_OC1B_ON_COMPARE_MATCH							3

	/********* BELONG TO PWM WAVEFORM GENERATION MODE *********/
#define		TOGGLE_OC1A_ON_COMPARE_MATCH_OC1B_DISCONNECTED			4
#define		NON_INVERTING_MODE										5
#define		INVERTING_MODE											6

/********************** PRESCALLER ***********************/
#define		TIMER_COUNTER_STOPPED 					0
#define		CLKIO_NO_PRESCALLING					1
#define		CLKIO8_FROM_PRESCALLER					2
#define		CLKIO64_FROM_PRESCALLER					3
#define		CLKIO256_FROM_PRESCALLER				4
#define		CLKIO1024_FROM_PRESCALLER				5
#define		EXTERNAL_CLK_F_SOURCE_ON_T0_PIN			6	//Clock on falling edge
#define		EXTERNAL_CLK_R_SOURCE_ON_T0_PIN			7	//Clock on rising edge

#endif	/* TIMER1_PRIVATE_H */