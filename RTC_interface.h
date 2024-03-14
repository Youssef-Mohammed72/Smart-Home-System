/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: RTC	 	  		   		   ****************/
/***************** File: 	  RTC_interface.h  		   	   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef RTC_INTERFACE_H
#define RTC_INTERFACE_H

/* STRUCT VARIABLE CARRY THE DATA WHICH RTC CAN GENERATE */
typedef struct
{
  u8 RTC_u8Second;
  u8 RTC_u8Minute;
  u8 RTC_u8Hour;
  u8 RTC_u8Weekday;
  u8 RTC_u8Date;
  u8 RTC_u8Month;
  u8 RTC_u8Year;
}E_RTC;

/* INITIALIZE RTC MODULE */
void RTC_voidInitialization(void);

/* SET DATE AND TIME OF RTC MODULE */
void RTC_SetDateTime(E_RTC *rtc);

/* GET DATE AND TIME OF RTC MODULE */
void RTC_GetDateTime(E_RTC *rtc);

#define 	RTC_ReadMode   			0xD1 		// READ MODE ID
#define 	RTC_WriteMode  			0xD0		// WRITE MODE ID
#define 	RTC_SecondRegAddress	0x00  		// ADDRESS TO ACCESS RTC SECOND REGISTER 
#define 	RTC_DayRegAddress		0x03  		// ADDRESS TO ACCESS RTC DAY REGISTER
#define 	RTC_DateRegAddress		0x04  		// ADDRESS TO ACCESS RTC DATE REGISTER 
#define 	RTC_ControlRegAddress	0x07		// ADDRESS TO ACCESS RTC CONTROL REGISTER

#endif /* RTC_INTERFACE_H */
