/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TWI	 	  		   		   ****************/
/***************** File: 	  TWI_interface.h  		   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

/* ENUM FOR ERROR STATUS IN TWI STATUS REGISTER - TWSR */
typedef enum{
	NoError,
	StartConditionErr,
	RepeatedStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr
}TWI_ErrStatus;

/* INITIALIZATION OF TWI MASTER MODE */
void TWI_voidMasterInitialization(void);

/* INITIALIZATION OF TWI SLAVE MODE */
void TWI_voidSlaveInitialization(u8 Copy_u8SlaveAddress);

/* TWI SEND START CONDITION */
void TWI_SendStartCondition(void);

/* TWI SEND REPEATED START CONDITION */
void TWI_SendRepeatedStartCondition(void);

/* TWI SEND SLAVE ADDRESS WITH WRITE ACKNOWLEDGEMENT */
void TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

/* TWI SEND SLAVE ADDRESS WITH READ ACKNOWLEDGEMENT */
void TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

/* TWI MASTER WRITE DATA BYTE */
void TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

/* TWI MASTER READ DATA BYTE WITH ACKNOWLEDGEMENT*/
u8 TWI_MasterReadDataByte_ACK(void);

/* TWI MASTER READ DATA BYTE WITHOUT ACKNOWLEDGEMENT */
u8 TWI_MasterReadDataByte_NACK(void);

/* TWI SEND STOP CONDITION */
void TWI_SendStopCondition(void);

/*********************** ACKNOWLEDGE BIT ************************/
#define 	ACKNOWLEDGE_DISABLE		0
#define 	ACKNOWLEDGE_ENABLE		1

/******************* GENERAL_CALL_RECOGNITION *******************/
#define 	DISABLE_GENERAL_CALL_RECOGNITION	0
#define 	ENABLE_GENERAL_CALL_RECOGNITION		1



#endif	/* TWI_INTERFACE_H */
