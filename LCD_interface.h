/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: LCD 	  			   		   ****************/
/***************** File: 	  LCD_interface.h 			   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef    LCD_INTERFACE_H
#define    LCD_INTERFACE_H

void LCD_voidInitialization4(void);
void LCD_voidWritecChar4(u8 Data);
void LCD_voidSendCMD4(u8 CMD);
void LCD_voidGOTOXY(u8 Line_num ,u8 Posittion);
void LCD_voidWriteString(u8* ptr);
void LCD_voidWriteNumber(s32 number);
void LCD_voidClearDisplay(void);
void LCD_voidWriteSpecialChar4(u8 *arr ,u8 BlockNumber ,u8 LineNumber ,u8 Position);

/*
void LCD_voidInitialization8(void);
void LCD_voidWriteChar8(u8 Data);
void LCD_voidSendCMD8(u8 CMD);
*/

#endif
