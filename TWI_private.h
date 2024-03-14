/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TWI	 	  		   		   ****************/
/***************** File: 	  TWI_private.h  		   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TWI_PRIVATE_H
#define TWI_PRIVATE_H

/**************************************************************************/
#define 	TWBR 	*((volatile u8*)20) 	// TWI Bit Rate Register – TWBR
/**************************************************************************/

/**************************************************************************/
#define 	TWCR 	*((volatile u8*)0x56) 	// TWI Control Register
/**************************************************************************/

#define 	TWCR_TWIE  			0 			// TWI Interrupt Enable 
#define 	TWCR_Reserved 		1 			// Reserved Bit 
#define 	TWCR_TWEN   		2 			// TWI Enable Bit
#define 	TWCR_TWWC   		3 			// TWI Write Collision Flag
#define 	TWCR_TWSTO  		4 			// TWI STOP Condition Bit
#define 	TWCR_TWSTA  		5 			// TWI START Condition Bit
#define 	TWCR_TWEA   		6 			// TWI Enable Acknowledge Bit
#define 	TWCR_TWINT  		7 			// TWI Interrupt Flag

/**************************************************************************/


/**************************************************************************/
#define 	TWDR 	*((volatile u8*)0x23) 	// TWI Data Register
/**************************************************************************/


/**************************************************************************/
#define 	TWAR 	*((volatile u8*)0x22) 	// TWI Address Register
/**************************************************************************/

#define 	TWAR_TWGCE   	0	 // TWI General Call Recognition Enable Bit
	   /*** Bits 7..1 – TWA: TWI (Slave) Address Register ***/

/**************************************************************************/


/**************************************************************************/
#define 	TWSR 	*((volatile u8*)21) 	// TWI Status Register
/**************************************************************************/

#define 	TWSR_TWPS0      0 				// TWI Prescaler Bit0
#define 	TWSR_TWPS1      1 				// TWI Prescaler Bit1
#define 	TWSR_Reserved   2 				// Reserved Bit
				/*** Bits [7:3] – TWS: TWI Status ***/
				
/**************************************************************************/

/***************************************************************************************************************************************/
									/* STATUS CODES FOR MASTER TRANSMITTER MODE */
#define 	SLAVE_ADD_AND_WR_ACK 			0x18 		// Master transmit ( slave address + write request ) ACK has been received
#define 	SLAVE_ADD_AND_WR_NACK 			0x20 		// Master transmit ( slave address + write request ) NOT ACK has been received
#define 	MSTR_WR_BYTE_ACK 				0x28 		// Master transmit data - ACK has been received
#define 	MSTR_WR_BYTE_NACK 				0x30 		// Master transmit data - NOT ACK has been received
/*-------------------------------------------------------------------------------------------------------------------------------------*/
									/* STATUS CODES FOR MASTER RECEIVER MODE */
#define 	START_ACK 						0x08 		// A START condition has been transmitted 
#define 	REP_START_ACK 					0x10 		// A START condition has been transmitted
#define 	SLAVE_ADD_AND_RD_ACK 			0x40 		// Master transmit ( slave address + read request ) ACK has been received
#define 	SLAVE_ADD_AND_RD_NACK 			0x48 		// Master transmit ( slave address + read request ) NOT ACK has been received
#define 	MSTR_RD_BYTE_WITH_ACK 			0x50 		// Master received data - ACK has been returned
#define 	MSTR_RD_BYTE_WITH_NACK 			0x58 		// Master received data - NOT ACK has been returned
/*-------------------------------------------------------------------------------------------------------------------------------------*/
									/* STATUS CODES FOR SLAVE RECEIVER MODE */
#define 	SLAVE_ADD_RCVD_WR_REQ_ACK 		0x60 		// means that slave address is received with write request - ACK has been returned
#define 	SLAVE_RECEIVE_GENERAL_ADD_ACK	0x70		// General call address has been received; ACK has been returned
#define 	SLAVE_DATA_RECEIVED_ACK 		0x80 		// means that a byte is received - ACK has been returned
#define 	SLAVE_DATA_RECEIVED_NACK 		0x88		// means that a byte is received - NOT ACK has been returned
/*-------------------------------------------------------------------------------------------------------------------------------------*/
									/* STATUS CODES FOR SLAVE TRANSMITTER MODE */
#define 	SLAVE_ADD_RCVD_RD_REQ_ACK		0xA8 		// means that slave address is received with read request - ACK has been returned
#define 	SLAVE_BYTE_TRANSMITTED_ACK 		0xB8 		// means that the written byte is transmitted - ACK has been received
#define 	SLAVE_BYTE_TRANSMITTED_NACK 	0xC0 		// means that the written byte is transmitted - NOT ACK has been received
/*-------------------------------------------------------------------------------------------------------------------------------------*/

#endif	/* TWI_PRIVATE_H */