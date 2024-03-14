/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: LCD 	  			   		   ****************/
/***************** File: 	  LCD_config.h 			       ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#define 	CONTROL_PORT 	PORTC
#define 	DATA_PORT 		PORTC
#define 	LCD_RS 			PIN2
#define 	LCD_EN 			PIN3

/*
 	{0x00 ,0x0A ,0x15 ,0x11 ,0x11 ,0x0A ,0x04 ,0x00}, 		// LOVE PATTERN
	{0x04 ,0x0E ,0x0E ,0x0E ,0x0E ,0x1F ,0x00 ,0x04},		// ALARM PATTERN
	{0x0E ,0x11 ,0x1F ,0x1F ,0x1B ,0x1B ,0x1F ,0x1F},		// LOCK PATTERN
	{0x01 ,0x03 ,0x05 ,0x09 ,0x09 ,0x09 ,0x1B ,0x1B},		// MUSIC PATTERN
 	{0x00 ,0x02 ,0x06 ,0x1E ,0x1E ,0x1E ,0x06 ,0x02},		// SOUND PATTERN
	{0x00 ,0x00 ,0x01 ,0x03 ,0x16 ,0x1C ,0x08 ,0x00},		// CORRECT PATTERN
	{0x00 ,0x00 ,0x00 ,0x0A ,0x11 ,0x0E ,0x00 ,0x00},		// EMOJI PATTERN
	{0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00}
*/

#endif
