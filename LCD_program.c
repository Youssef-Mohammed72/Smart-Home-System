/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: LCD 	  			   		   ****************/
/***************** File: 	  LCD_program.c 			   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Dio_interface.h"
#include "Dio_private.h"
#include "LCD_interface.h"
#include "LCD_config.h"

static u8 cursor = 1;

void LCD_voidInitialization4(void){
	_delay_ms(45); 				//Wait for more than 40 ms after VDD rises to 4.5 V
	LCD_voidSendCMD4(0x32);		//send for 4-bit initialization of LCD_Command
	LCD_voidSendCMD4(0x28);		//2-line 5x7 matrix in 4-bit mode
	LCD_voidSendCMD4(0x0c);		//Display on Cursor OFF
	LCD_voidSendCMD4(0x06);		//Increment cursor (shift cursor to right)
	LCD_voidSendCMD4(0x01);		//clear display screen
}

void LCD_voidWritecChar4 (u8 Data){
	if(cursor == 17){
		LCD_voidGOTOXY(1, 0);
	}
	else if(cursor == 33){
		LCD_voidGOTOXY(0, 0);
		cursor = 1;
	}
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RS ,HIGH);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);
	u8 Dummy0 = 0b00001100;
	_delay_ms(5);

	u8 Dummy = (Data & 0xf0) | Dummy0;
	DIO_voidSetPortValue(DATA_PORT ,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);
	_delay_ms(5);

	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);
	_delay_ms(5);

	Dummy = ((Data & 0x0f) << 4) | Dummy0;
	DIO_voidSetPortValue(DATA_PORT ,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);
	_delay_ms(5);
	cursor++;
}

void LCD_voidSendCMD4(u8 CMD){
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RS ,LOW);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);
	u8 Dummy0 = 0b00001000;
	_delay_ms(5);

	u8 Dummy = (CMD & 0xf0) | Dummy0;
	DIO_voidSetPortValue(DATA_PORT ,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);
	_delay_ms(5);

	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);
	_delay_ms(5);

	Dummy = ((CMD & 0x0f) << 4) | Dummy0;
	DIO_voidSetPortValue(DATA_PORT ,Dummy);
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);
	_delay_ms(5);
}

void LCD_voidGOTOXY(u8 Line_num ,u8 Posittion){
	if((Line_num == 0) && (Posittion < 16)){
		LCD_voidSendCMD4((0x80 + Posittion));
		cursor = Posittion;
	}
	else if((Line_num == 1) && (Posittion < 16)){
		LCD_voidSendCMD4((0xC0 + Posittion));
		cursor = 17 + Posittion;
	}
}

void LCD_voidWriteString(u8* ptr){
	u8 i = 0;
	while(ptr[i] != '\0'){
		LCD_voidWritecChar4(ptr[i]);
		i++;
	}
}

void LCD_voidClearDisplay(void){
	LCD_voidSendCMD4(0x01);		//clear display screen
	cursor = 1;
}

void LCD_voidWriteSpecialChar4(u8 *arr ,u8 BlockNumber ,u8 LineNumber ,u8 Position){
	if(BlockNumber < 8 && BlockNumber >= 0 && LineNumber < 2 && LineNumber >= 0 && Position < 16 && Position >= 0){
		/* WRITE INSIDE CGRAM */
		u8 CGRAM_Address = BlockNumber * 8;
		LCD_voidSendCMD4(CGRAM_Address | 0b01000000);
		for(int i = 0 ;i<8 ;i++){
			LCD_voidWritecChar4(arr[i]);
		}

		/* RETURN TO DDRAM TO PRINT */
		LCD_voidGOTOXY(LineNumber, Position);
		LCD_voidWritecChar4(BlockNumber);
	}
}

void LCD_voidWriteNumber(s32 number){
	u32 First_Digit;
	u32 Second_Digit;
	u32 Third_Digit;
	u32 Fourth_Digit;
	u32 Fifth_Digit;
	u32 Six_Digit;

	s32 LocalNumber = number;

	if(LocalNumber < 0){
		LCD_voidWritecChar4('-');
		LocalNumber = (LocalNumber * (-1));
	}
	if(LocalNumber >= 0 && LocalNumber < 10){
		First_Digit = (LocalNumber % 10);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(LocalNumber >= 10 && LocalNumber < 100){
		First_Digit = (LocalNumber % 10);
		Second_Digit = ((LocalNumber % 100) - (LocalNumber % 10)) / 10;
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(LocalNumber >=100 && LocalNumber < 1000){
		First_Digit  = (LocalNumber % 10);
		Second_Digit = ((LocalNumber % 100) - (LocalNumber % 10)) / 10;
		Third_Digit  = ((LocalNumber) - (LocalNumber % 100)) / 100;
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(LocalNumber >=1000 && LocalNumber < 10000){
		First_Digit  = (LocalNumber % 10);
		Second_Digit = ((LocalNumber % 100) - (LocalNumber % 10)) / 10;
		Third_Digit  = ((LocalNumber % 1000) - (LocalNumber % 100)) / 100;
		Fourth_Digit = ((LocalNumber) - (LocalNumber % 1000)) / 1000;
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(LocalNumber >=10000 && LocalNumber < 100000){
		First_Digit  = (LocalNumber % 10);
		Second_Digit = ((LocalNumber % 100) - (LocalNumber % 10)) / 10;
		Third_Digit  = ((LocalNumber % 1000) - (LocalNumber % 100)) / 100;
		Fourth_Digit = ((LocalNumber % 10000) - (LocalNumber % 1000)) / 1000;
		Fifth_Digit  = ((LocalNumber) - (LocalNumber % 10000)) / 10000;
		LCD_voidWritecChar4(Fifth_Digit + 0x30);
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(LocalNumber >=100000 && LocalNumber < 1000000){
		First_Digit  = (LocalNumber % 10);
		Second_Digit = ((LocalNumber % 100) - (LocalNumber % 10)) / 10;
		Third_Digit  = ((LocalNumber % 1000) - (LocalNumber % 100)) / 100;
		Fourth_Digit = ((LocalNumber % 10000) - (LocalNumber % 1000)) / 1000;
		Fifth_Digit  = ((LocalNumber % 100000) - (LocalNumber % 10000)) / 10000;
		Six_Digit    = ((LocalNumber) - (LocalNumber % 100000)) / 100000;
		LCD_voidWritecChar4(Six_Digit + 0x30);
		LCD_voidWritecChar4(Fifth_Digit + 0x30);
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
}

/*
void LCD_voidInitialization8(void){
	//Function Set: RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	_delay_ms(45); 		//Wait for more than 40 ms after VDD rises to 4.5 V
	LCD_SendCMD(0x38); 	//Function Set: 0b00111000 : 2-lines & Font:5x7
	_delay_ms(1);
	LCD_SendCMD(0x0c); 	//Function Set: 0b00111000 : Cursor OFF & Blinking OFF
	_delay_ms(1);
	LCD_SendCMD(0x01); 	//Function Set: 0b00111000 : Clear Display
	_delay_ms(2);
	LCD_SendCMD(0x06); 	//Function Set: 0b00111000 : Display is increased
}

void LCD_voidWriteChar8(u8 Data){
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RS ,HIGH);  	// set RS to high for send data
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RW ,LOW);		// set Rw to low for write
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);	// send enable pulse
	_delay_ms(5);
	DIO_voidSetPortValue(DATA_PORT ,Data);				// set data to data pins
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);		// send disable pulse
	_delay_ms(5);
}

void LCD_voidSendCMD8(u8 CMD){
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RS ,LOW);		// set RS to low for send command
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_RW ,LOW);		// set Rw to low for write
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,HIGH);	// send enable pulse
	_delay_ms(5);
	DIO_voidSetPortValue(DATA_PORT ,CMD);				// set command to data pins
	DIO_voidSetPinValue(CONTROL_PORT ,LCD_EN ,LOW);		// send disable pulse
	_delay_ms(5);
}

void LCD_voidWriteNumber(u32 number){
	u32 First_Digit;
	u32 Second_Digit;
	u32 Third_Digit;
	u32 Fourth_Digit;
	u32 Fifth_Digit;
	u32 Six_Digit;
	if(number >= 0 && number < 10){
		First_Digit = (number % 10);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(number >= 10 && number < 100){
		First_Digit = (number % 10);
		Second_Digit = ((number % 100) - (number % 10)) / 10;
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(number >=100 && number < 1000){
		First_Digit  = (number % 10);
		Second_Digit = ((number % 100) - (number % 10)) / 10;
		Third_Digit  = ((number) - (number % 100)) / 100;
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(number >=1000 && number < 10000){
		First_Digit  = (number % 10);
		Second_Digit = ((number % 100) - (number % 10)) / 10;
		Third_Digit  = ((number % 1000) - (number % 100)) / 100;
		Fourth_Digit = ((number) - (number % 1000)) / 1000;
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(number >=10000 && number < 100000){
		First_Digit  = (number % 10);
		Second_Digit = ((number % 100) - (number % 10)) / 10;
		Third_Digit  = ((number % 1000) - (number % 100)) / 100;
		Fourth_Digit = ((number % 10000) - (number % 1000)) / 1000;
		Fifth_Digit  = ((number) - (number % 10000)) / 10000;
		LCD_voidWritecChar4(Fifth_Digit + 0x30);
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
	else if(number >=100000 && number < 1000000){
		First_Digit  = (number % 10);
		Second_Digit = ((number % 100) - (number % 10)) / 10;
		Third_Digit  = ((number % 1000) - (number % 100)) / 100;
		Fourth_Digit = ((number % 10000) - (number % 1000)) / 1000;
		Fifth_Digit  = ((number % 100000) - (number % 10000)) / 10000;
		Six_Digit    = ((number) - (number % 100000)) / 100000;
		LCD_voidWritecChar4(Six_Digit + 0x30);
		LCD_voidWritecChar4(Fifth_Digit + 0x30);
		LCD_voidWritecChar4(Fourth_Digit + 0x30);
		LCD_voidWritecChar4(Third_Digit + 0x30);
		LCD_voidWritecChar4(Second_Digit + 0x30);
		LCD_voidWritecChar4(First_Digit + 0x30);
	}
}
*/
