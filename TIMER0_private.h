/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER0 	  				   ****************/
/***************** File: 	  TIMER0_private.h 		   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H


/************************* Registers Addresses *************************/
			/****** TIMER/COUNTER CONTROL REGISTER ******/
#define 	TCCRO	*((volatile u8 *)0x53)

			/****** Timer/Counter Register – TCNT0 ******/
#define 	TCNTO	*((volatile u8 *)0x52)

			/****** Output Compare Register – OCR0 ******/
#define 	OCR0	*((volatile u8 *)0x5C)

	/****** Timer/Counter Interrupt Mask Register – TIMSK ******/
#define 	TIMSK	*((volatile u8 *)0x59)

	/****** Timer/Counter Interrupt Flag Register – TIFR  ******/
#define 	TIFR	*((volatile u8 *)0x58)


/***************************** TIMSK *****************************/
#define 	TIMSK_TOIE0			0       //Timer/Counter0 Overflow Interrupt Enable
#define 	TIMSK_OCIE0			1       //Timer/Counter0 Output Compare Match Interrupt Enable

/***************************** TCCR0 *****************************/
#define		TCCR0_CS00			0		//Clock Select
#define		TCCR0_CS01			1		//Clock Select
#define		TCCR0_CS02			2		//Clock Select
#define 	TCCR0_WGM01 		3		//Waveform Generation Mode
#define 	TCCR0_COM00 		4		//Compare Output Mode PIN4
#define 	TCCR0_COM01			5		//Compare Output Mode PIN5
#define 	TCCR0_WGM00			6		//Waveform Generation Mode

/***************************** TIFR *****************************/
#define TIFR_TOV0				0
#define TIFR_OCF0				1

/***************** TIMER0 WAVE FORM GENERATION MODE **************/
#define	NORMAL_MODE 			0
#define	PHASE_CORRECT_MODE		1
#define	CTC_MODE				2
#define	FAST_PWM_MODE			3

/***************** TIMER0 COMPARE OUTPUT MODE *****************/
/* BELONG TO ALL WAVE FORM GENERATION MODE */
#define	OC0_DISCONNECTED 					0
/* BELONG TO NON-PWM WAVEFORM GENERATION MODE */
#define	TOGGLE_OC0_ON_COMPARE_MATCH			1
#define	CLEAR_OCO_ON_COMPARE_MATCH			2
#define	SET_OCO_ON_COMPARE_MATCH			3
/* BELONG TO PWM WAVEFORM GENERATION MODE */
#define	RESERVED							4
/* BELONG TO FAST-PWM and PHASE-CORRECT GENERATION MODE */
#define	NON_INVERTING_MODE					5
#define	INVERTING_MODE						6

/********************** PRESCALLER ***********************/
#define	TIMER_COUNTER_STOPPED 				0
#define	CLKIO_NO_PRESCALLING				1
#define	CLKIO8_FROM_PRESCALLER				2
#define	CLKIO64_FROM_PRESCALLER				3
#define	CLKIO256_FROM_PRESCALLER			4
#define	CLKIO1024_FROM_PRESCALLER			5
#define	EXTERNAL_CLK_F_SOURCE_ON_T0_PIN		6	//Clock on falling edge
#define	EXTERNAL_CLK_R_SOURCE_ON_T0_PIN		7	//Clock on rising edge

#endif 	/* TIMER0_PRIVATE_H */
