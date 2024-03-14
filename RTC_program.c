/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: RTC	 	  		   		   ****************/
/***************** File: 	  RTC_program.c  		   	   ****************/
/***************** Layer: 	  HAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TWI_interface.h"
#include "RTC_interface.h"

/* INITIALIZE RTC MODULE */
void RTC_voidInitialization(void)
{
	/* INITIALIZE TWI MODULE AS A MASTER */
    TWI_voidMasterInitialization();

    /* TRANSMIT START COMMUNICATION */
    TWI_SendStartCondition();

    /* CONNECT TO RTC MODULE (WRITE MODE) BY SENDING IT'S ID ON THE BUS */
    TWI_SendSlaveAddressWithWrite(RTC_WriteMode);

    /* SELECT RTC CONTROL REGISTER */
    TWI_MasterWriteDataByte(RTC_ControlRegAddress);

    /* WRITE 0x00 TO CONTROL REGISTER TO DISABLE SQW-Out */
    TWI_MasterWriteDataByte(0x00);

    /* TRANSMIT STOP COMMUNICATION */
	TWI_SendStopCondition();
}

/* SET DATE AND TIME OF RTC MODULE */
void RTC_SetDateTime(E_RTC *rtc){

	/* TRANSMIT START COMMUNICATION */
	TWI_SendStartCondition();

	/* CONNECT TO RTC MODULE (WRITE MODE) BY SENDING IT'S ID ON THE BUS */
    TWI_SendSlaveAddressWithWrite(RTC_WriteMode);

    /* SELECT RTC SECOND ADDRESS REGISTER */
    TWI_MasterWriteDataByte(RTC_SecondRegAddress);

    /* WRITE SECOND IN RAM ADDRESS 00H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Second / 10) << 4) + (rtc->RTC_u8Second % 10));

    /* WRITE MINUTE IN RAM ADDRESS 01H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Minute / 10) << 4) + (rtc->RTC_u8Minute % 10));

    /* WRITE HOUR IN RAM ADDRESS 02H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Hour / 10) << 4) + (rtc->RTC_u8Hour % 10));

    /* WRITE WEEKDAY IN RAM ADDRESS 03H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Weekday / 10) << 4) + (rtc->RTC_u8Weekday % 10));

    /* WRITE DATE IN RAM ADDRESS 04H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Date / 10) << 4) + (rtc->RTC_u8Date % 10));

    /* WRITE MONTH IN RAM ADDRESS 05H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Month / 10) << 4) + (rtc->RTC_u8Month % 10));

    /* WRITE YEAR IN RAM ADDRESS 06H */
    TWI_MasterWriteDataByte(((rtc->RTC_u8Year / 10) << 4) + (rtc->RTC_u8Year % 10));

    /* TRANSMIT STOP COMMUNICATION */
    TWI_SendStopCondition();
}

/* GET DATE AND TIME OF RTC MODULE */
void RTC_GetDateTime(E_RTC *rtc){

	/* TRANSMIT START COMMUNICATION */
	TWI_SendStartCondition();

	/* CONNECT TO RTC MODULE (WRITE MODE) BY SENDING IT'S ID ON THE BUS */
	TWI_SendSlaveAddressWithWrite(RTC_WriteMode);

	/* SELECT RTC SECOND ADDRESS REGISTER */
	TWI_MasterWriteDataByte(RTC_SecondRegAddress);

	/* TRANSMIT STOP COMMUNICATION */
	TWI_SendStopCondition();

	/* TRANSMIT START COMMUNICATION */
	TWI_SendStartCondition();

	/* CONNECT TO RTC MODULE (READ MODE) BY SENDING IT'S ID ON THE BUS */
	TWI_SendSlaveAddressWithRead(RTC_WriteMode);

	/* READ SECOND AND RETURN ACKNOWLEDGE */
    rtc->RTC_u8Second = TWI_MasterReadDataByte_ACK();

    /* READ MINUTE AND RETURN ACKNOWLEDGE */
    rtc->RTC_u8Minute = TWI_MasterReadDataByte_ACK();

    /* READ HOUR AND RETURN NO ACKNOWLEDGE */
    rtc->RTC_u8Hour= TWI_MasterReadDataByte_ACK();

    /* READ WEEKDAY AND RETURN ACKNOWLEDGE */
    rtc->RTC_u8Weekday = TWI_MasterReadDataByte_ACK();

    /* READ DATE AND RETURN ACKNOWLEDGE */
    rtc->RTC_u8Date= TWI_MasterReadDataByte_ACK();

    /* READ MONTH AND RETURN ACKNOWLEDGE */
    rtc->RTC_u8Month=TWI_MasterReadDataByte_ACK();

    /* READ YEAR AND RETURN NO ACKNOWLEDGE */
    rtc->RTC_u8Year =TWI_MasterReadDataByte_NACK();

    /* TRANSMIT STOP COMMUNICATION */
    TWI_SendStopCondition();

    rtc->RTC_u8Second  = ((rtc->RTC_u8Second & 0xF0) >> 4) * 10 + (rtc->RTC_u8Second & 0x0F);
    rtc->RTC_u8Minute  = ((rtc->RTC_u8Minute & 0xF0) >> 4) * 10 + (rtc->RTC_u8Minute & 0x0F);
    rtc->RTC_u8Hour    = ((rtc->RTC_u8Hour & 0xF0) >> 4) * 10 + (rtc->RTC_u8Hour & 0x0F);
    rtc->RTC_u8Weekday = ((rtc->RTC_u8Weekday & 0xF0) >> 4) * 10 + (rtc->RTC_u8Weekday & 0x0F);
    rtc->RTC_u8Date    = ((rtc->RTC_u8Date & 0xF0) >> 4) * 10 + (rtc->RTC_u8Date & 0x0F);
    rtc->RTC_u8Month   = ((rtc->RTC_u8Month & 0xF0) >> 4) * 10 + (rtc->RTC_u8Month & 0x0F);
    rtc->RTC_u8Year    = ((rtc->RTC_u8Year & 0xF0) >> 4) * 10 + (rtc->RTC_u8Year & 0x0F);
}
