/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER0 	  				   ****************/
/***************** File: 	  TIMER0_interface.h 		   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

/******************** INITIALZE TIMER0 ********************/
void TIMER0_voidInitialization();

/******************** ENABLE TIMER0 OVERFLOW INTERRUPT *************/
void TIMER0_voidOverFlowInterruptEnable(void);

/******************** DISABLE TIMER0 OVERFLOW INTERRUPT ************/
void TIMER0_voidOverFlowInterruptDisable(void);

/******************** ENABLE TIMER0 COMPARE MATCH INTERRUPT *************/
void TIMER0_voidCompareMatchInterruptEnable(void);

/******************** DISABLE TIMER0 COMPARE MATCH INTERRUPT *************/
void TIMER0_voidCompareMatchInterruptDisable(void);

/******************** SET TCNT0 REGISTER  ********************/
void TIMER0_voidSetTCNT0(u8 val);

/******************** SET OCR0 REGISTER  ********************/
void TIMER0_voidSetOCR0(u8 val);

/********* CALL BACK FUNCTION FOR TIMER0 OVERFLOW INTERRUPT *********/
void TIMER0_voidSetCallBackOverFlow(void (*Copy_PF)(void));

/******* CALL BACK FUNCTION FOR TIMER0 COMPARE MATCH INTERRUPT ******/
void TIMER0_voidSetCallBackCompareMatch(void (*Copy_PF)(void));

#endif 	/* TIMER0_INTERFACE_H */
