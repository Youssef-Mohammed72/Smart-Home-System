/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: KEYPAD 	  			   	   ****************/
/***************** File: 	  KEYPAD_config.h 			   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#define 	KEYPAD_ROWSPORT 	PORTB
#define 	KEYPAD_COLSPORT 	PORTD

#define 	KEYPAD_NoPressedKey		0xff

/******************** DEFINE PINS ********************/
#define 	KEYPAD_ROW1		PIN4
#define 	KEYPAD_ROW2		PIN5
#define 	KEYPAD_ROW3		PIN6
#define 	KEYPAD_ROW4		PIN7

#define 	KEYPAD_COL1		PIN0
#define 	KEYPAD_COL2		PIN1
#define 	KEYPAD_COL3		PIN6
//#define 	KEYPAD_COL4		PIN7

/********* ROW AND COLUMNS NUMBERS FOR ARRAY *********/
#define 	KEYPAD_RowSize		4
#define 	KEYPAD_ColSize		3

/************** THE VALUES OF THE ARRAY *************/
#define 	KEYPAD_ArrayValues 	{{7 ,8 ,9},{4 ,5 ,6},{1 ,2 ,3},{'%' ,0 ,'='}}

#endif
