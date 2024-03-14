/**************************************************************************/
/**************************************************************************/
/***************** Author: 	  Youssef Mohammed AbdelFattah ****************/
/***************** Component: TIMER1 	  				   ****************/
/***************** File: 	  TIMER1_config.h 			   ****************/
/***************** Layer: 	  MCAL 						   ****************/
/***************** Version:   1.0 						   ****************/
/**************************************************************************/
/**************************************************************************/

#ifndef TIMER1_CONFIG_H
#define TIMER1_CONFIG_H

/* OPTIONS FOR TIMER1 WAVEFORM GENERATION MODE: 
																						TOP		UPDATE OF OCR1x		TOV1 FLAG SET ON
																						_________________________________________________
										* NORMAL_MODE									0xFFFF		   Immediate			  MAX
										* PWM_PHASE_CORRECT_8_BIT_MODE					0x00FF 			  TOP 				 BOTTOM
										* PWM_PHASE_CORRECT_9_BIT_MODE					0x01FF 		  	  TOP 				 BOTTOM
										* PWM_PHASE_CORRECT_10_BIT_MODE					0x03FF 			  TOP 				 BOTTOM
										* CTC_OCR1A_MODE								OCR1A 		   Immediate 			  MAX
										* FAST_PWM_8_BIT_MODE							0x00FF 		     BOTTOM 			  TOP
										* FAST_PWM_9_BIT_MODE							0x01FF 			 BOTTOM 			  TOP
										* FAST_PWM_10_BIT_MODE							0x03FF 			 BOTTOM 			  TOP
										* PWM_ICR1_PHASE_AND_FREQUENCY_CORRECT_MODE		ICR1 			 BOTTOM 			 BOTTOM
										* PWM_OCR1A_PHASE_AND_FREQUENCY_CORRECT_MODE 	OCR1A 			 BOTTOM 			 BOTTOM
										* PWM_ICR1_PHASE_CORRECT_MODE					ICR1 			  TOP 				 BOTTOM
										* PWM_OCR1A_PHASE_CORRECT_MODE					OCR1A 			  TOP 				 BOTTOM
										* CTC_ICR1_MODE									ICR1 		   Immediate 			  MAX
										* FAST_PWM_ICR1_MODE							ICR1 			 BOTTOM 			  TOP
										* FAST_PWM_OCR1A_MODE							OCR1A 			 BOTTOM 			  TOP
*/
#define TIMER1_WAVEFORM_GENERATION_MODE		FAST_PWM_ICR1_MODE


/* OPTIONS FOR TIMER1 COMPARE OUTPUT MODE, NON PWM (NORMAL && CTC) MODE: 
																* OC1A_OC1B_DISCONNECTED
																* TOGGLE_OC1A_OC1B_ON_COMPARE_MATCH
																* CLEAR_OC1A_OC1B_ON_COMPARE_MATCH
																* SET_OC1A_OC1B_ON_COMPARE_MATCH
 * OPTIONS FOR TIMER1 COMPARE OUTPUT MODE, PHASE CORRECT AND FREQUENCY CORRECT PWM MODE:
																* OC1A_OC1B_DISCONNECTED
																* TOGGLE_OC1A_ON_COMPARE_MATCH_OC1B_DISCONNECTED	// WHEN WAVEFPRM GENERATION MODE IS:
																																	* PWM_OCR1A_PHASE_AND_FREQUENCY_CORRECT_MODE
																																	* FAST_PWM_ICR1_MODE
																																	* OTHERS OC1A OC1B DISCONNECTED
																* NON_INVERTING_MODE
																* INVERTING_MODE
 * OPTIONS FOR TIMER1 COMPARE OUTPUT MODE, FAST PWM MODE:
																* OC1A_OC1B_DISCONNECTED
																* TOGGLE_OC1A_ON_COMPARE_MATCH_OC1B_DISCONNECTED	// WHEN WAVEFPRM GENERATION MODE IS:
																																	* FAST_PWM_OCR1A_MODE
																																	* OTHERS OC1A OC1B DISCONNECTED
																* NON_INVERTING_MODE
																* INVERTING_MODE
*/
#define TIMER1_COMPARE_OUTPUT_MODE		NON_INVERTING_MODE


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
#define TIMER0_Prescaller		CLKIO64_FROM_PRESCALLER

#endif	/* TIMER1_CONFIG_H */
