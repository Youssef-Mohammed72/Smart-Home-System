/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: External Interrupt	 	   ****************/
/***************** File: 	  EXTI_interface.h  		   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/************************************************* INTERRUPT 0 ************************************************************/
void EXTI0_voidInitialization(void);
void EXTI0_voidEnable(void);
void EXTI0_voidDisable(void);
void EXTIO_voidSetCallBack(void (*pf)(void));  	// This Function For Take An Address f=>From main.c And Pass it to HMCAL (EXTI Destination)

/************************************************* INTERRUPT 1 ************************************************************/
void EXTI1_voidInitialization(void);
void EXTI1_voidEnable(void);
void EXTI1_voidDisable(void);
void EXTI1_voidSetCallBack(void (*pf)(void));  	// This Function For Take An Address f=>From main.c And Pass it to HMCAL (EXTI Destination)

/************************************************* INTERRUPT 2 ************************************************************/
void EXTI2_voidInitialization(void);
void EXTI2_voidEnable(void);
void EXTI2_voidDisable(void);
void EXTI2_voidSetCallBack(void (*pf)(void));  	// This Function For Take An Address f=>From main.c And Pass it to HMCAL (EXTI Destination)

#endif /* EXTI_INTERFACE_H */