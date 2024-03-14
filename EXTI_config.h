/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: External Interrupt	 	   ****************/
/***************** File: 	  EXTI_config.h  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

/* SENSE CONTROL OPTIONS FOR INTERRUPT:
									* EXTI_LOW_LEVEL
									* EXTI_IOC
									* EXTI_FALLING
									* EXTI_RISING
*/

#define EXTI0_SENSE_MODE 	EXTI_IOC
#define EXTI1_SENSE_MODE 	EXTI_IOC
#define EXTI2_SENSE_MODE 	EXTI_FALLING

#endif /* EXTI_CONFIG_H */
