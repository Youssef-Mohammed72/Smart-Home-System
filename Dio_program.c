/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: DIO 	  					   ****************/
/***************** File: 	  Dio_program.c 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Dio_private.h"
#include "Dio_interface.h"

void DIO_voidSetPinDirection(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Direction){
	if((Copy_u8Port < 4) && (Copy_u8Pin < 8)){
		if(Copy_u8Direction == OUTPUT){
			switch(Copy_u8Port){
				case PORTA : SET_BIT(DDRA_REG,Copy_u8Pin);		break;
				case PORTB : SET_BIT(DDRB_REG,Copy_u8Pin);		break;
				case PORTC : SET_BIT(DDRC_REG,Copy_u8Pin);		break;
				case PORTD : SET_BIT(DDRD_REG,Copy_u8Pin);		break;
			}
			
		}
		else if(Copy_u8Direction == INPUT){
			switch(Copy_u8Port){
				case PORTA : CLR_BIT(DDRA_REG,Copy_u8Pin);		break;
				case PORTB : CLR_BIT(DDRB_REG,Copy_u8Pin);		break;
				case PORTC : CLR_BIT(DDRC_REG,Copy_u8Pin);		break;
				case PORTD : CLR_BIT(DDRD_REG,Copy_u8Pin);		break;
			}
			
		}
	}
}

void DIO_voidSetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin ,u8 Copy_u8Value){
	if((Copy_u8Port < 4) && (Copy_u8Pin < 8)){
		if(Copy_u8Value == HIGH){
			switch(Copy_u8Port){
				case PORTA : SET_BIT(PORTA_REG,Copy_u8Pin);		break;
				case PORTB : SET_BIT(PORTB_REG,Copy_u8Pin);		break;
				case PORTC : SET_BIT(PORTC_REG,Copy_u8Pin);		break;
				case PORTD : SET_BIT(PORTD_REG,Copy_u8Pin);		break;
			}
			
		}
		else if(Copy_u8Value == LOW){
			switch(Copy_u8Port){
				case PORTA : CLR_BIT(PORTA_REG,Copy_u8Pin);		break;
				case PORTB : CLR_BIT(PORTB_REG,Copy_u8Pin);		break;
				case PORTC : CLR_BIT(PORTC_REG,Copy_u8Pin);		break;
				case PORTD : CLR_BIT(PORTD_REG,Copy_u8Pin);		break;
			}
			
		}
	}
	
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port ,u8 Copy_u8Pin){
	u8 Local_u8Value = 0xFF;
	if((Copy_u8Port < 4) && (Copy_u8Pin < 8)){
			switch(Copy_u8Port){
				case PORTA : Local_u8Value = GET_BIT(PINA_REG,Copy_u8Pin);		break;
				case PORTB : Local_u8Value = GET_BIT(PINB_REG,Copy_u8Pin);		break;
				case PORTC : Local_u8Value = GET_BIT(PINC_REG,Copy_u8Pin);		break;
				case PORTD : Local_u8Value = GET_BIT(PIND_REG,Copy_u8Pin);		break;
			}
	}
	return Local_u8Value;
}

void DIO_voidSetPortDirection(u8 Copy_u8Port ,u8 Copy_u8Direction){
	if(Copy_u8Port < 4 ){
		switch(Copy_u8Port){
			case PORTA : DDRA_REG = Copy_u8Direction;		break;
			case PORTB : DDRB_REG = Copy_u8Direction;		break;
			case PORTC : DDRC_REG = Copy_u8Direction;		break;
			case PORTD : DDRD_REG = Copy_u8Direction;		break;
		}
	}
}

void DIO_voidSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value){
	if(Copy_u8Port < 4 ){
		switch(Copy_u8Port){
			case PORTA : PORTA_REG = Copy_u8Value;		break;
			case PORTB : PORTB_REG = Copy_u8Value;		break;
			case PORTC : PORTC_REG = Copy_u8Value;		break;
			case PORTD : PORTD_REG = Copy_u8Value;		break;
		}
	}
}

u8 DIO_u8GetPortValue(u8 Copy_u8Port){
	u8 Local_u8Value = 0xFF;
	if(Copy_u8Port < 4){
			switch(Copy_u8Port){
				case PORTA : Local_u8Value = PINA_REG;		break;
				case PORTB : Local_u8Value = PINB_REG;		break;
				case PORTC : Local_u8Value = PINC_REG;		break;
				case PORTD : Local_u8Value = PIND_REG;		break;
			}
	}
	return Local_u8Value;
}
