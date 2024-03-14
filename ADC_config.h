/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: ANALOG-TO-DIGITAL CONVERTER  ****************/
/***************** File: 	  ADC_config.h  		 	   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/* VOLTAGE_REF OPTIONS:
					* EXT_REF
					* VCC_REF
					* INT_REF
*/
#define 	VOLTAGE_REF 	VCC_REF

/* PRESCALLER OPTIONS:
				* DIV_Factor2
				* DIV_Factor4
				* DIV_Factor8
				* DIV_Factor16
				* DIV_Factor32
				* DIV_Factor64
				* DIV_Factor128
*/
#define 	ADC_Prescaler	DIV_Factor128

/* ALIGNMENT OPTIONS:
				* RIGHT
				* LEFT
*/
#define ALIGNMENT RIGHT

/* MODE OPTIONS:
			* POLLING
			* INTERRUPT
*/
#define MODE 	INTERRUPT

#endif /* ADC_CONFIG_H */
