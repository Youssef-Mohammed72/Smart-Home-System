/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: General Interrupt Enable 	   ****************/
/***************** File: 	  GIE_program.c		 	   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_private.h"
#include "GIE_interface.h"
#include "GIE_config.h"

void GIE_voidEnable(void){
	SET_BIT(SREG ,SREF1); 	//Enable Global Interrupt
}

void GIE_voidDisable(void){
	CLR_BIT(SREG ,SREF1); 	//Disable Global Interrupt
}
