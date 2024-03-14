/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: DIO 	  					   ****************/
/***************** File: 	  Dio_private.h 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef   DIO_PRIVATE_H
#define   DIO_PRIVATE_H

/*           PORTA_REGISTERS               */
#define 	PORTA_REG 	*((volatile u8*)0x3B)
#define 	DDRA_REG  	*((volatile u8*)0x3A)
#define 	PINA_REG  	*((volatile u8*)0x39)

/*           PORTB_REGISTERS               */
#define 	PORTB_REG 	*((volatile u8*)0x38)
#define 	DDRB_REG  	*((volatile u8*)0x37)
#define 	PINB_REG  	*((volatile u8*)0x36)

/*           PORTC_REGISTERS               */
#define 	PORTC_REG 	*((volatile u8*)0x35)
#define 	DDRC_REG  	*((volatile u8*)0x34)
#define 	PINC_REG  	*((volatile u8*)0x33)

/*           PORTD_REGISTERS               */
#define 	PORTD_REG 	*((volatile u8*)0x32)
#define 	DDRD_REG  	*((volatile u8*)0x31)
#define 	PIND_REG  	*((volatile u8*)0x30)

#endif