/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: DIO 	  					   ****************/
/***************** File: 	  Dio_interface.h 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef   DIO_INTERFACE_H
#define   DIO_INTERFACE_H

/**************** SET PIN DIRECTION ***************/
void DIO_voidSetPinDirection(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Direction);

/**************** SET PIN VALUE *******************/
void DIO_voidSetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Value);

/**************** GET PIN VALUE *******************/
u8 DIO_u8GetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin);

/**************** SET PORT DIRECTION **************/
void DIO_voidSetPortDirection(u8 Copy_u8Port ,u8 Copy_u8Direction);

/**************** SET PORT VALUE ******************/
void DIO_voidSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value);

/**************** GET PORT VALUE ******************/
u8 DIO_u8GetPortValue(u8 Copy_u8Port);

/******************* PORT NAMES *******************/
typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}PORT;

/******************* PIN NAMES *******************/
typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}PINS;

/*************** DIRECTION OF PIN ***************/
typedef enum{
	INPUT,
	OUTPUT
}DIRECTIONS;

/**************** STATUS OF PIN ****************/
typedef enum{
	LOW,
	HIGH
}STATUS;

#endif
