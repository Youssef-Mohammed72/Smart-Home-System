/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: External Interrupt	 	   ****************/
/***************** File: 	  EXTI_private.h  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* MCUCR CONTAINS CONTROL BITS FOR INTERUPPT 0 AND 1 SENSE CONTROL */
#define 	MCUCR 	*((volatile u8 *)0x55)

/* MCUCSR CONTAINS CONTROL BIT FOR INTERUPPT 2 SENSE CONTROL */
#define 	MCUCSR 	*((volatile u8 *)0x54)

/* GICR CONTAINS ENABLE BIT FOR INTERUPPT 0 ,1 ,AND 2 */
#define 	GICR 	*((volatile u8 *)0x5B)

/* GIFR CONTAINS BITs FOR INTERUPPT 0 ,1 ,AND 2 FLAGS */
#define 	GIFR 	*((volatile u8 *)0x5A)

/* SENSE CONTROL OPTIONS FOR INTERRUPT */
#define 	EXTI_FALLING 	0
#define 	EXTI_RISING 	1
#define 	EXTI_LOW_LEVEL	2
#define 	EXTI_IOC	 	3

/* MCUCR PIN NAMES FOR INTERRUPT 1 SENSE CONTROL */
#define ISC10	2
#define ISC11	3

/* MCUCR PIN NAMES FOR INTERRUPT 0 SENSE CONTROL */
#define ISC00	0
#define ISC01	1

/* MCUCSR PIN NAME FOR INTERRUPT 2 SENSE CONTROL */
#define ISC2	6

/* GICR PIN NAMES FOR ENABLE THE 3 EXTERNAL INTERRUPT */
#define INT2	5
#define INT0	6
#define INT1	7

/* GIFR PIN NAMES FOR THE 3 EXTERNAL INTERRUPT FLAGS */
#define INTF2	5
#define INTF0	6
#define INTF1	7

#endif /* EXTI_PRIVATE_H */
