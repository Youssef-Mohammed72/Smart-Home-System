/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER1 	  				   ****************/
/***************** File: 	  TIMER1_interface.h 		   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER1_INTERFACE_H
#define TIMER1_INTERFACE_H

/******************** INITIALZE TIMER1 ********************/
void TIMER1_voidInitialization();

/******************** ENABLE TIMER1 OVERFLOW INTERRUPT *************/
void TIMER1_voidOverFlowInterruptEnable(void);

/******************** DISABLE TIMER1 OVERFLOW INTERRUPT ************/
void TIMER1_voidOverFlowInterruptDisable(void);

/******************** ENABLE TIMER1 COMPARE B MATCH INTERRUPT *************/
void TIMER1_voidCompare_B_MatchInterruptEnable(void);

/******************** DISABLE TIMER1 COMPARE B MATCH INTERRUPT *************/
void TIMER1_voidCompare_B_MatchInterruptDisable(void);

/******************** ENABLE TIMER1 COMPARE A MATCH INTERRUPT *************/
void TIMER1_voidCompare_A_MatchInterruptEnable(void);

/******************** DISABLE TIMER1 COMPARE A MATCH INTERRUPT *************/
void TIMER1_voidCompare_A_MatchInterruptDisable(void);

/******************** ENABLE TIMER1 INPUT CAPTURE UNIT *************/
void TIMER1_void_ICU_InterruptEnable(void);

/******************** DISABLE TIMER1 INPUT CAPTURE UNIT *************/
void TIMER1_void_ICU_InterruptDisable(void);

/******************** SET TCNT1 REGISTER  ********************/
void TIMER1_voidSetTCNT1(u16 val);

/******************** SET OCR1A REGISTER  ********************/
void TIMER1_voidSetOCR1A(u16 val);

/******************** SET OCR1B REGISTER  ********************/
void TIMER1_voidSetOCR1B(u16 val);

/******************** SET ICR1 REGISTER *************/
void TIMER1_u16SetICR1(u16 val);

/******************** READ ICR1 REGISTER *************/
u16 TIMER1_u16ReadICR1(void);

/********* CALL BACK FUNCTION FOR TIMER1 OVERFLOW INTERRUPT *********/
void TIMER1_voidSetCallBackTCNT1(void (*Copy_PF)(void));

/******* CALL BACK FUNCTION FOR TIMER1 COMPARE MATCH A INTERRUPT ******/
void TIMER1_voidSetCallBackOCR1A(void (*Copy_PF)(void));

/******* CALL BACK FUNCTION FOR TIMER1 COMPARE MATCH B INTERRUPT ******/
void TIMER1_voidSetCallBackOCR1B(void (*Copy_PF)(void));

/********* CALL BACK FUNCTION FOR TIMER1 INPUT CAPTURE INTERRUPT *********/
void TIMER1_voidSetCallBackICR1(void (*Copy_PF)(void));

#endif	/* TIMER1_INTERFACE_H */