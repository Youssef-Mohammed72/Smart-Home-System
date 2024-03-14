/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TWI	 	  		   		   ****************/
/***************** File: 	  TWI_program.c  		   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_private.h"
#include "TWI_config.h"
#include "TWI_interface.h"
#include <util/delay.h>

/* INITIALIZATION OF TWI MASTER MODE */
void TWI_voidMasterInitialization(void){
	
	/* SET CLOCK FREQUENCY TO 400kbps */
	TWBR = TWBR_VALUE;
	
	/* SET TWPS[1:0] PRESCALLER VALUE */ 
	#if	PRESCALLER_VALUE == 1
		CLR_BIT(TWSR ,TWSR_TWPS0);
		CLR_BIT(TWSR ,TWSR_TWPS1);
	#elif PRESCALLER_VALUE == 4
		SET_BIT(TWSR ,TWSR_TWPS0);
		CLR_BIT(TWSR ,TWSR_TWPS1);
	#elif PRESCALLER_VALUE == 16
		CLR_BIT(TWSR ,TWSR_TWPS0);
		SET_BIT(TWSR ,TWSR_TWPS1);
	#elif PRESCALLER_VALUE == 64
		SET_BIT(TWSR ,TWSR_TWPS0);
		SET_BIT(TWSR ,TWSR_TWPS1);
	#else
		#error "WRONG CHOICE OF PRESCALLER VALUE!"
	#endif
	
	/* ENABLE TWI PROTOCOL */
	SET_BIT(TWCR ,TWCR_TWEN);
}

/* INITIALIZATION OF TWI SLAVE MODE */
void TWI_voidSlaveInitialization(u8 Copy_u8SlaveAddress){
	/* Initialize the node address */
	TWAR = (Copy_u8SlaveAddress << 1);
	
	/* ENABLE TWI PROTOCOL */
	SET_BIT(TWCR ,TWCR_TWEN);
}

/* TWI SEND START CONDITION */
void TWI_SendStartCondition(void){
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL ,SET START CONDITION BIT IN TWCR REGISTER */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWSTA);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while((GET_BIT(TWCR ,TWCR_TWINT)) == 0);
}

/* TWI SEND REPEATED START CONDITION */
void TWI_SendRepeatedStartCondition(void){

	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL ,SET START CONDITION BIT IN TWCR REGISTER */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWSTA);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while((GET_BIT(TWCR ,TWCR_TWINT)) == 0);
}

/* TWI SEND SLAVE ADDRESS WITH WRITE ACKNOWLEDGEMENT */
void TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){
	
	/* SET SLAVE ADDRESS IN THE 7 MSB OF DATA REGISTER */
	TWDR = Copy_u8SlaveAddress;
	
	/* FOR WRITE REQUEST */
	CLR_BIT(TWDR ,0);
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while((GET_BIT(TWCR ,TWCR_TWINT)) == 0);
	
}

/* TWI SEND SLAVE ADDRESS WITH READ ACKNOWLEDGEMENT */
void TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress){
	
	/* SET SLAVE ADDRESS IN THE 7 MSB OF DATA REGISTER */
	TWDR = Copy_u8SlaveAddress;
	
	/* FOR READ REQUEST */
	SET_BIT(TWDR ,0);
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while((GET_BIT(TWCR ,TWCR_TWINT)) == 0);
}

/* TWI MASTER WRITE DATA BYTE */
void TWI_MasterWriteDataByte(u8 Copy_u8DataByte){
	
	/* WRITE THE DATA BYTE */
	TWDR = Copy_u8DataByte;
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while(GET_BIT(TWCR ,TWCR_TWINT) == 0);
}

/* TWI MASTER READ DATA BYTE */
u8 TWI_MasterReadDataByte_ACK(void){
	
	/*	 CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL ,ENABLE MASTER GENERATING ACKNOWLEDGE BIT AFTER RECEIVING THE DATA */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWEA);

	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while(GET_BIT(TWCR ,TWCR_TWINT) == 0);
	
	/* RETURN READED VALUE IN TWDR REGISTER */
	return TWDR;
}

/* TWI MASTER READ DATA BYTE WITHOUT ACKNOWLEDGEMENT */
u8 TWI_MasterReadDataByte_NACK(void){
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
	
	/* WAIT UNTIL INTERRUPT FLAG IS RAISED AGAIN AND THE PREVIOUS OPERATION IS COMPLETE */
	while(GET_BIT(TWCR ,TWCR_TWINT) == 0);
	
	/* RETURN READED VALUE IN TWDR REGISTER */
	return TWDR;
}

/* TWI SEND STOP CONDITION */
void TWI_SendStopCondition(void){
	
	/* CLEAR INTERRUPT FLAG TO START THE PREVIOUS OPERATION ,ENABLE TWI PROTOCOL ,GENERATE STOP CONDITION ON THE BUS */
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWSTO);
}
