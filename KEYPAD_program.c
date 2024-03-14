/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: KEYPAD 	  			   	   ****************/
/***************** File: 	  KEYPAD_program.c 			   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"

// cols -> output
// rows -> input

void KPD_voidInitialization(void){
	/* DIRECTIONS OF COLUMNS PORT */
	DIO_voidSetPinDirection(KEYPAD_COLSPORT, KEYPAD_COL1, OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_COLSPORT, KEYPAD_COL2, OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_COLSPORT, KEYPAD_COL3, OUTPUT);
	//DIO_voidSetPinDirection(KEYPAD_COLSPORT, KEYPAD_COL4, OUTPUT);

	/* DIRECTIONS OF ROWS PORT */
	DIO_voidSetPinDirection(KEYPAD_ROWSPORT, KEYPAD_ROW1, INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWSPORT, KEYPAD_ROW2, INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWSPORT, KEYPAD_ROW3, INPUT);
	DIO_voidSetPinDirection(KEYPAD_ROWSPORT, KEYPAD_ROW4, INPUT);

	/* PIN VALUES OF COLUMNS PORT */
	DIO_voidSetPinValue(KEYPAD_COLSPORT, KEYPAD_COL1, HIGH);
	DIO_voidSetPinValue(KEYPAD_COLSPORT, KEYPAD_COL2, HIGH);
	DIO_voidSetPinValue(KEYPAD_COLSPORT, KEYPAD_COL3, HIGH);
	//DIO_voidSetPinValue(KEYPAD_COLSPORT, KEYPAD_COL4, HIGH);

	/* PIN VALUES OF ROWS PORT */
	DIO_voidSetPinValue(KEYPAD_ROWSPORT, KEYPAD_ROW1, HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWSPORT, KEYPAD_ROW2, HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWSPORT, KEYPAD_ROW3, HIGH);
	DIO_voidSetPinValue(KEYPAD_ROWSPORT, KEYPAD_ROW4, HIGH);
}

u8 KPD_u8GETPressedKey(void){
	/* INITIAL VALUE FOR PRESSED KEY */
	u8 Local_u8PressedKey = KEYPAD_NoPressedKey;
	
	/* COUNTERS FOR COLUMNS & ROWS IN TWO DIMENSIONAL ARRAY */
	u8 Local_u8ColCounter ,Local_u8RowCounter;
	
	/* KEYPAD VALUES */
	static u8 Local_u8KeypadArr[KEYPAD_RowSize][KEYPAD_ColSize] = KEYPAD_ArrayValues;
	
	/* KEYPAD COLUMN ARRAY */
	static u8 Local_u8KeypadColArr[KEYPAD_ColSize] = {KEYPAD_COL1 ,KEYPAD_COL2 ,KEYPAD_COL3};
	
	/* KEYPAD ROW ARRAY */
	static u8 Local_u8KeypadRowArr[KEYPAD_RowSize] = {KEYPAD_ROW1 ,KEYPAD_ROW2 ,KEYPAD_ROW3 ,KEYPAD_ROW4};
	
	for(Local_u8ColCounter = 0 ;Local_u8ColCounter < KEYPAD_ColSize ;Local_u8ColCounter++){
		
		/* ACTIVE CURRENT COLUMN */
		DIO_voidSetPinValue(KEYPAD_COLSPORT ,Local_u8KeypadColArr[Local_u8ColCounter] ,LOW);
		
		/* READ CURRENT ROW */
		for(Local_u8RowCounter = 0 ;Local_u8RowCounter < KEYPAD_RowSize ;Local_u8RowCounter++){
			/* CHECK IF KEY IS PRESSED */
			if((DIO_u8GetPinValue(KEYPAD_ROWSPORT, Local_u8KeypadRowArr[Local_u8RowCounter])) == 0){
				while((DIO_u8GetPinValue(KEYPAD_ROWSPORT, Local_u8KeypadRowArr[Local_u8RowCounter])) == 0);
				Local_u8PressedKey = Local_u8KeypadArr[Local_u8RowCounter][Local_u8ColCounter];
			}
		}
		/* DEACTIVE CURRENT COLUMN */
		DIO_voidSetPinValue(KEYPAD_COLSPORT ,Local_u8KeypadColArr[Local_u8ColCounter], HIGH);
	}
	return Local_u8PressedKey;
}
