/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TWI	 	  		   		   ****************/
/***************** File: 	  TWI_config.h  		   	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TWI_CONFIG_H
#define TWI_CONFIG_H

/* OPTIONS FOR ACKNOWLEDGE BIT:
							* ACKNOWLEDGE_ENABLE
							* ACKNOWLEDGE_DISABLE
*/
#define 	ACKNOWLEDGE_BIT		ACKNOWLEDGE_ENABLE

/* OPTIONS FOR PRESCALLER VALUE WHICH REPRESENTED BY THE BINARY VALUE IN TWPS[1:0] BINS:
																						* 1
																						* 4
																						* 16
																						* 64
*/
#define 	PRESCALLER_VALUE		1

/*
	*) SET THE VALUE OF TWBR REGISTER ACCORDING TO THE EQUATION:
			SCL FREQUENCY = CPU CLOCK FREQUENCY / (16 + (2x(TWBR)x4^(TWPS[1:0])))
*/
#define 	TWBR_VALUE		12

/* OPTIONS FOR TWI GENERAL CALL RECOGNITION:
										* ENABLE_GENERAL_CALL_RECOGNITION
										* DISABLE_GENERAL_CALL_RECOGNITION
*/
#define 	GENERAL_CALL_RECOGNITION	DISABLE_GENERAL_CALL_RECOGNITION


#endif	/* TWI_CONFIG_H */
