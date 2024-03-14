/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER0 	  				   ****************/
/***************** File: 	  TIMER0_config.h 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER0_CONFIG_H
#define TIMER0_CONFIG_H

/* OPTIONS FOR TIMER0 WAVEFORM GENERATION MODE: 
										* NORMAL_MODE
										* PHASE_CORRECT_MODE
										* CTC_MODE
										* FAST_PWM_MODE
*/
#define TIMER0_WAVEFORM_GENERATION_MODE		FAST_PWM_MODE


/* OPTIONS FOR TIMER0 COMPARE OUTPUT MODE, NON PWM (NORMAL && CTC) MODE: 
																* OC0_DISCONNECTED
																* TOGGLE_OC0_ON_COMPARE_MATCH
																* CLEAR_OCO_ON_COMPARE_MATCH
																* SET_OCO_ON_COMPARE_MATCH
 * OPTIONS FOR TIMER0 COMPARE OUTPUT MODE, PHASE CORRECT PWM MODE:
  															 	 * OC0_DISCONNECTED
  															 	 * RESERVED
  															 	 * INVERTING_MODE
  															 	 * NON_INVERTING_MODE
 * OPTIONS FOR TIMER0 COMPARE OUTPUT MODE, FAST PWM MODE:
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * OC0_DISCONNECTED
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * RESERVED
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * NON_INVERTING_MODE
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 * INVERTING_MODE
*/
#define TIMER0_COMPARE_OUTPUT_MODE		NON_INVERTING_MODE


/* OPTIONS FOR TIMER0 PRESCALLER:
							* TIMER_COUNTER_STOPPED
							* CLKIO_NO_PRESCALLING
							* CLKIO8_FROM_PRESCALLER
							* CLKIO64_FROM_PRESCALLER
							* CLKIO256_FROM_PRESCALLER
							* CLKIO1024_FROM_PRESCALLER
							* EXTERNAL_CLK_F_SOURCE_ON_T0_PIN		//Clock on falling edge
							* EXTERNAL_CLK_R_SOURCE_ON_T0_PIN		//Clock on rising edge
*/
#define TIMER0_Prescaller		CLKIO1024_FROM_PRESCALLER

#endif 	/* TIMER0_CONFIG_H */
