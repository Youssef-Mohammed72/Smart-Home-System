/******************************************************************************************************************/
/******************************************************************************************************************/
/********************************** Authors:	  Youssef Mohammed AbdelFattah Ahmed ******************************/
/**********************************												 	 ******************************/
/********************************** Component: 	  SMART HOME SYSTEM			         ******************************/
/**********************************													 ******************************/
/********************************** File: 	  	  main.c 			   		   		 ******************************/
/**********************************												 	 ******************************/
/********************************** Layer: 	  	  App 						   		 ******************************/
/**********************************												 	 ******************************/
/********************************** Version:   	  1.0 						   		 ******************************/
/**********************************												 	 ******************************/
/********************************** Date:   	  7 September 2023 			   		 ******************************/
/******************************************************************************************************************/
/******************************************************************************************************************/

#define F_CPU 16000000UL
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Dio_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "TIMER1_interface.h"
#include "TIMER0_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "TWI_interface.h"
#include "RTC_interface.h"
#include <util/delay.h>

/* STATIC GLOBAL VARIABLE TO CARRY NEW READED TEMPERATURE DIGITAL VALUE FROM ADC */
static u16 TEMPERATURE_u16DigitalVoltage = 0;

/* STATIC GLOBAL VARIABLE TO CARRY OLD READED TEMPERATURE DIGITAL VALUE FROM ADC */
static u16 TEMPERATURE_u16OldDigitalVoltage = 0;

/* STATIC GLOBAL VARIABLE TO CARRY READED TEMPERATURE ANALOG VALUE ENTER TO ADC */
static u16 TEMPERATURE_u16AnalogVoltagemv = 0;

/* STATIC GLOBAL VARIABLE TO CARRY TEMPERATURE VALUE READED FROM ADC IN DEGREE CELISIUS */
static u16 TEMPERATURE_u16Temp = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "FAN IS OFF" ONLY ONE TIME IN THE RANGE OF TEMPERATURE VALUE >= 0 AND <= 20 */
static u8 TEMPERATURE_u8Flag1 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "FAN SPEED IS 1" ONLY ONE TIME IN THE RANGE OF TEMPERATURE VALUE > 20 AND <= 25 */
static u8 TEMPERATURE_u8Flag2 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "FAN SPEED IS 2" ONLY ONE TIME IN THE RANGE OF TEMPERATURE VALUE > 25 AND <= 35 */
static u8 TEMPERATURE_u8Flag3 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "FAN SPEED IS 3" ONLY ONE TIME IN THE RANGE OF TEMPERATURE VALUE > 35 AND <= 45 */
static u8 TEMPERATURE_u8Flag4 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "EMERGENCY LED ON" ONLY ONE TIME IN THE RANGE OF TEMPERATURE VALUE > 45 */
static u8 TEMPERATURE_u8Flag5 = 0;

/* STATIC LOCAL VARIABLE TO UPDATE (WHEN SET TO 1) THE STATE OF MOTOR AND TEMPERATURE SENSOR EMERGENCY LED AT ANY TIME WHILE SYSTEM RUNNING WITHOUT PRINT ON LCD */
static u8 REALTIME_u8TemperatureFlag;

/* STATIC GLOBAL VARIABLE TO CARRY NEW READED LDR DIGITAL VALUE FROM ADC */
static u16 LDR_u16DigitalVoltage = 0;

/* STATIC GLOBAL VARIABLE TO CARRY OLD LDR READED DIGITAL VALUE FROM ADC */
static u16 LDR_u16OldDigitalVoltage = 0;

/* STATIC GLOBAL VARIABLE TO CARRY READED LDR ANALOG VALUE ENTER TO ADC */
static u16 LDR_u16AnalogVoltagemv = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "LOW LIGHT" AND THE STRING "volt =" ONLY ONE TIME AND CHANGE THEIR VALUES ONLY WHEN BE ALREADY IN THEIR RANGE */
static u8 LDR_u8Flag1 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "MEDIUM LIGHT" AND THE STRING "volt =" ONLY ONE TIME AND CHANGE THEIR VALUES ONLY WHEN BE ALREADY IN THEIR RANGE */
static u8 LDR_u8Flag2 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "GOOD LIGHT" AND THE STRING "volt =" ONLY ONE TIME AND CHANGE THEIR VALUES ONLY WHEN BE ALREADY IN THEIR RANGE */
static u8 LDR_u8Flag3 = 0;

/* STATIC GLOBAL VARIABLE TO ALLOW WRITE THE STRING "HIGH LIGHT" AND THE STRING "volt =" ONLY ONE TIME AND CHANGE THEIR VALUES ONLY WHEN BE ALREADY IN THEIR RANGE */
static u8 LDR_u8Flag4 = 0;

/* STATIC LOCAL VARIABLE TO UPDATE (WHEN SET TO 1) THE STATE OF LIGHT SYSTEM AT ANY TIME WHILE SYSTEM RUNNING WITHOUT PRINT ON LCD */
static u8 REALTIME_u8LightSystemFlag;

/* GLOBAL VARIABLE MUST BE SET WITH CHANNEL NUMBER BEFORE ENTER ADC_FUNC (CALL BACK FUNCTION) OF ADC TO DISTINGUISH BETWEEN LDR AND TEMPERATURE SENSOR */
u8 ADC_u8ChannelSelected;

/* GLOBAL FLAG RAISED WHEN ALL MODULE IS UPDATED FOR THE FIRST TIME  */
static u8 END_u8Flag = 0;

/* GLOBAL VARIABLE FROM THE POINT OF SYSTEM VIEW TO MOVE FROM PART TO ANOTHER PART IN THE SYSTEM */
u8 Global_u8Control = 0;

/* FUNCTION TO RETURN THE ENTERD PASSWORD (AS ARRAY) AS A (u32) NUMBER */
u32 ArrayToInt(u32 *ptr ,u8 size);

/* CALL BACK FUNCTION OF ADC INTERRUPT */
void ADC_FUNC(void);

/* CALL BACK FUNCTION OF EXTERNAL INTERRUPT 0 */
void EXTI0_FUNC(void);

/* CALL BACK FUNCTION OF EXTERNAL INTERRUPT 1 */
void EXTI1_FUNC(void);

int main(void){
	/*************************************** Configuration ***************************************/

	/* SET PORTC DIRECTION ACCORDING TO HEX NUMBER 0xFC FOR LCD */
	//DIO_voidSetPortDirection(PORTC, 0xfc);
	DIO_voidSetPinDirection(PORTC, PIN2, HIGH);
	DIO_voidSetPinDirection(PORTC, PIN3, HIGH);
	DIO_voidSetPinDirection(PORTC, PIN4, HIGH);
	DIO_voidSetPinDirection(PORTC, PIN5, HIGH);
	DIO_voidSetPinDirection(PORTC, PIN6, HIGH);
	DIO_voidSetPinDirection(PORTC, PIN7, HIGH);


	/* MAKE PIN0 ON PORTB OUTPUT FOR THE RED LED */
	DIO_voidSetPinDirection(PORTB, PIN0, OUTPUT);

	/* MAKE PIN1 ON PORTB OUTPUT FOR THE GREEN LED */
	DIO_voidSetPinDirection(PORTB, PIN1, OUTPUT);

	/* MAKE PIN3 ON PORTB OUTPUT FOR THE OCRO OF TIMER0 */
	DIO_voidSetPinDirection(PORTB, PIN3, OUTPUT);

	/* MAKE PIN5 ON PORTD OUTPUT FOR OCR1A OF TIMER1 WHICH CONTROL SERVO MOTOR ANGLE */
	DIO_voidSetPinDirection(PORTD, PIN5, OUTPUT);

	/* MAKE PIN0 ON PORTA INPUT FOR TEMPERATURE SENSOR */
	DIO_voidSetPinDirection(PORTA, PIN0, INPUT);

	/* MAKE PIN1 ON PORTA INPUT FOR GAS SENSOR */
	DIO_voidSetPinDirection(PORTA, PIN1, INPUT);

	/* MAKE PIN4 ON PORTD AND PIN7 ON PORTA OUTPUT TO IDENTICATE THE DIRECTION OF DC-MOTOR */
	DIO_voidSetPinDirection(PORTD, PIN4, OUTPUT);
	DIO_voidSetPinDirection(PORTA, PIN7, OUTPUT);

	/* MAKE PIN7 ON PORTD OUTPUT FOR EMERGENCY TEMPERATURE SENSOR LED */
	DIO_voidSetPinDirection(PORTD, PIN7, OUTPUT);

	/* MAKE PIN6 ON PORTA OUTPUT FOR EMERGENCY GAS SENSOR LED */
	DIO_voidSetPinDirection(PORTA, PIN6, OUTPUT);

	/* MAKE PIN2 ON PORTA INPUT FOR PIR SENSOR */
	DIO_voidSetPinDirection(PORTA, PIN2, INPUT);

	/* MAKE PIN3 ON PORTA INPUT FOR LDR SENSOR */
	DIO_voidSetPinDirection(PORTA, PIN3, INPUT);

	/* MAKE PIN4 ,5 ON PORTA AND PIN2 ON PORTB OUTPUT FOR LIGHT SYSTEM */
	DIO_voidSetPinDirection(PORTA, PIN4, OUTPUT);
	DIO_voidSetPinDirection(PORTA, PIN5, OUTPUT);
	DIO_voidSetPinDirection(PORTB, PIN2, OUTPUT);

	/* MAKE PIN2 ON PORTD INPUT FOR EXTERNAL INTERRUPT 0 TO GO TO THE TEMPERATURE SENSOR AREA */
	DIO_voidSetPinDirection(PORTD, PIN2, INPUT);

	/* ENABLE PULL-UP RESISTOR FOR PIN2 ON PORTD */
	DIO_voidSetPinValue(PORTD, PIN2, HIGH);

	/* MAKE PIN3 ON PORTD INPUT FOR EXTERNAL INTERRUPT 1 TO GO TO THE LIGHT SYSTEM AREA */
	DIO_voidSetPinDirection(PORTD, PIN3, INPUT);

	/* ENABLE PULL-UP RESISTOR FOR PIN3 ON PORTD */
	DIO_voidSetPinValue(PORTD, PIN3, HIGH);

	/* LOCAL VARIABLE TO HOLD PRESSED KEY FROM KEYPAD */
	u8 Local_u8PressedKey = 0;

	/* DEFAULT PASSWORD FOR SMART HOME */
	u32 const Default_u8Password = 4862;

	/* DEFAULT DELAY BETWEEN TEXTS DISPLAYED ON THE LCD */
	u32 const Default_u8Delay = 500;

	/* ARRAY OF SIZE 4 (THE SIZE OF SYSTEM PASSWORD) TO HOLD THE ENTERED PASSWORD FROM KEYPAD */
	u32 Login_u8Password[4];

	/* VARIABLE USED AS A COUNTER WHILE ENTER THE PASSWORD TO TAKE 4 NUMBERS OF PASSWORD ONLy */
	u8 Password_u8Counter = 0;

	/* VARIABLE USED AS A COUNTER WHILE ENTER THE PASSWORD INCORRECTLY WHICH ALLOW ENTER THE PASSWORD INCORRECTLY 3 TIMES ONLY */
	u8 INCORRECT_u8Password = 1;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE THE STRING "GAS IS NOT DETECTED" ONLY ONE TIME IN THE CASE OF GLOBAL CONTROL = 4 (GAS SENSOR AREA) */
	static u8 GAS_Flag1 = 0;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE THE STRING "GAS IS DETECTED" ONLY ONE TIME IN THE CASE OF GLOBAL CONTROL = 4 (GAS SENSOR AREA) */
	static u8 GAS_Flag2 = 0;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE THE STRING "SOMEONE IS DETECTED" ONLY ONE TIME IN THE CASE OF GLOBAL CONTROL = 6 (LIGHT SYSTEM AREA) */
	static u8 PIR_u8Flag1 = 0;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE THE STRING "NO ONE DETECTED ,SO LEDS TURNED-OFF" ONLY ONE TIME IN THE CASE OF GLOBAL CONTROL = 6 (LIGHT SYSTEM AREA) */
	static u8 PIR_u8Flag2 = 0;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE tHE STRING "TEMPERATURE = " ONLY ONE TIME IN THE CASE OF GLOBAL CONTROL = 3 ACCORDING TO THE INTERRUPT 0 */
	static u8 TEMPERATURE_u8Flag0 = 0;

	/* STATIC LOCAL VARIABLE TO ALLOW WRITE THE INFORMATION OF TIME AND DATE ONLY ONE TIME WHEN GLOBAL CONTROL = 9 (RTC AREA) */
	static u8 RTC_u8Flag = 0;

	/* DEFINE A VARIABLE FROM THE TYPE OF E_RTC STRUCT TO HOLD THE VALUES OF DATE AND TIME */
	E_RTC rtc;

	/* 8-BYTES EXPRESS LOCKED ICON */
	u8 ICON_u8Locked[8] = {0x0E ,0x0A ,0x1F ,0x11 ,0x15 ,0x11 , 0x1F ,0x00};

	/* 8-BYTES EXPRESS WRONG ICON */
	u8 ICON_u8Wrong[8] = {0x1F ,0x0E ,0x15 ,0x1B ,0x15 ,0x0E ,0x1F ,0x00};

	/* 8-BYTES EXPRESS CORRECT ICON */
	u8 ICON_u8Correct[8] = {0x00 ,0x00 ,0x01 ,0x03 ,0x16 ,0x1C ,0x08 ,0x00};

	/* CALL BACK FUNCTION TO IMPLEMENT ADC_FUNC WHEN INTERRUPT FLAG REAISED */
	ADC_voidSetCallBack(ADC_FUNC);

	/* CALL BACK FUNCTION TO IMPLEMENT EXTI0_FUNC WHEN EXTERNAL INTERRUPT 0 TAKE PLACE */
	EXTIO_voidSetCallBack(EXTI0_FUNC);

	/* CALL BACK FUNCTION TO IMPLEMENT EXTI1_FUNC WHEN EXTERNAL INTERRUPT 1 TAKE PLACE */
	EXTI1_voidSetCallBack(EXTI1_FUNC);

	// INITIALIZE ADC
	ADC_voidInitialization();

	// ENABLE GLOBAL INTERRUPT
	GIE_voidEnable();

	/* INITIALIZE KEYPAD */
	KPD_voidInitialization();

	/* INITIALIZE LCD */
	LCD_voidInitialization4();

	/* INITIALIZE TIMER1 FOR PWM OF SERVO MOTOR */
	TIMER1_voidInitialization();

	/* INITIALIZE TIMER0 FOR PWM OF DC-MOTOR */
	TIMER0_voidInitialization();

	/* SET TIMER0 OCR0 VALUE */
	TIMER0_voidSetOCR0(0);

	/* SET OVERFLOW VALUE IN ICR1 REGISTER */
	TIMER1_u16SetICR1(5000);

	/* INITIALIZE EXTERNAL INTERRUPT 0 TO DEAL WITH TEMPERATURE SENSOR AREA */
	EXTI0_voidInitialization();

	/* INITIALIZE EXTERNAL INTERRUPT 1 TO DEAl WITH LIGHT SYSTEM AREA */
	EXTI1_voidInitialization();

	/* ENABLE EXTERNAL INTERRUPT 0 */
	EXTI0_voidEnable();

	/* ENABLE EXTERNAL INTERRUPT 1 */
	EXTI1_voidEnable();

	/* INITIALIZE RTC MODULE */
	RTC_voidInitialization();

	while(1){
		/************************************* Real-time *************************************/


		/* UPDATE THE STATUS OF GAS SENSOR ALL OF THE TIME IF END_u8Flag VARIABLE IS SET TO ONE */
		if(END_u8Flag == 1){

			/***************************************** GAS SENSOR UPDATE VALUE *****************************************/
			/* CHECK IF GAS SENSOR DETECT ANY TYPE OF GAS IN THE ATMOSPHERE */
			if(DIO_u8GetPinValue(PORTA, PIN1) == 1){
				/* TURN-ON GAS EMERGENCY LED ON PORTA PIN6 */
				DIO_voidSetPinValue(PORTA, PIN6, HIGH);
			}
			/* CHECK IF GAS SENSOR NOT DETECT ANY TYPE OF GAS IN THE ATMOSPHERE */
			else if(DIO_u8GetPinValue(PORTA, PIN1) == 0){
				/* TURN-OFF GAS EMERGENCY LED ON PORTA PIN6 */
				DIO_voidSetPinValue(PORTA, PIN6, LOW);
			}
			/*===========================================================================================================*/

			/************************************** TEMPERATURE SENSOR UPDATE VALUE **************************************/
			if(DIO_u8GetPinValue(PORTD, PIN2) == 0){

				/* SET REALTIME_u8TemperatureFlag TO ZERO*/
				REALTIME_u8TemperatureFlag = 0;
			}
			else if(DIO_u8GetPinValue(PORTD, PIN2) == 1){

				/* SET REALTIME_u8TemperatureFlag TO ONE*/
				REALTIME_u8TemperatureFlag = 1;

				/* SET ADC_u8ChannelSelected GLOBAL VARIABLE TO 0 TO GO TO THE TEMPERATURE SENSOR AREA IN THE CALL BACK FUNCTION OF ADC */
				ADC_u8ChannelSelected = 0;

				// READ CHANNEL0 ASYNCHROUNOUSLY (START CONVERSION)
				ADC_voidReadChannelASyn(CHANNEL0);

				/* WAIT 20 MILLISECOND */
				_delay_ms(20);
			}
			/*===========================================================================================================*/

			/***************************************** LIGHT SYSTEM UPDATE VALUE *****************************************/
			if(DIO_u8GetPinValue(PORTD, PIN3) == 0){

				/* SET REALTIME_u8LightSystemFlag TO ZERO*/
				REALTIME_u8LightSystemFlag = 0;
			}
			else if(DIO_u8GetPinValue(PORTD, PIN3) == 1){

				/* SET REALTIME_u8LightSystemFlag TO ONE*/
				REALTIME_u8LightSystemFlag = 1;

				/* CHECK IF PIR SENSOR DETECT SOMEONE */
				if(DIO_u8GetPinValue(PORTA, PIN2) == 1){

					/* SET ADC_u8ChannelSelected GLOBAL VARIABLE TO 3 TO GO TO THE LDR AREA IN THE CALL BACK FUNCTION OF ADC */
					ADC_u8ChannelSelected = 3;

					// READ CHANNEL3 ASYNCHROUNOUSLY (START CONVERSION)
					ADC_voidReadChannelASyn(CHANNEL3);

					/* WAIT 20 MILLISECOND */
					_delay_ms(20);
				}

				/* CHECK IF PIR SENSOR NOT DETECT SOMEONE*/
				else if(DIO_u8GetPinValue(PORTA, PIN2) == 0){

					LDR_u16DigitalVoltage  	 = 0;
					LDR_u16OldDigitalVoltage = 0;
					LDR_u16AnalogVoltagemv 	 = 0;

					/* TURN-OFF LEDS OF LIGHT SYSTEM */
					DIO_voidSetPinValue(PORTA, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN5, LOW);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);
				}
			}
			/*===========================================================================================================*/
		}

		/* WELCOME MESSAGE AREA */
		if(Global_u8Control == 0){

			/* CLEAR THE DISPLAY ,THEN WRITE THE STRING "WELCOME YOU IN OUR SMART HOME" */
			LCD_voidClearDisplay();
			LCD_voidGOTOXY(0, 1);
			LCD_voidWriteString((u8*)"WELCOME YOU IN");
			LCD_voidGOTOXY(1, 1);
			LCD_voidWriteString((u8*)"OUR SMART HOME");

			/* WAIT FOR Default_u8Delay SPECIFIED TIME */
			_delay_ms(Default_u8Delay);

			/* GO TO ENTER SMART HOME PASSWORD AREA */
			Global_u8Control = 1;
		}

		/*SMART HOME PASSWORD AREA */
		else if(Global_u8Control == 1){

			/* TURN-ON RED LED ON PIN0 OF PORTB */
			DIO_voidSetPinValue(PORTB, PIN0, HIGH);

			/* TURN-OFF GREEN LED ON PIN1 OF PORTB */
			DIO_voidSetPinValue(PORTB, PIN1, LOW);

			/* SET COMPARE MATCH VALUE IN OCR1A */
			TIMER1_voidSetOCR1A(0);

			/* CLEAR LCD ,THEN WRITE 8-BYTES WHICH EXPRESSED LOCKED ICON IN ADDRESS 0 IN CGRAM AND PRINT IT IN LINE 0 AT POSITION 0 ON LCD ,then
			   WRITE THE STRING "ENTER HOMES'S PASSWORD AT THE SPECIFIC LOCATION ON THE LCD USING LCD_voidGOTOXY() METHOD"
			*/
			LCD_voidClearDisplay();
			LCD_voidWriteSpecialChar4(ICON_u8Locked, 0, 0, 0);
			LCD_voidWriteString((u8*)" ENTER HOMES'S");
			LCD_voidGOTOXY(1, 2);
			LCD_voidWriteString((u8*)"PASSWORD:");

			/*CHECK IF YOU ENTERED 4 NUMBERS OF PASSWORD OR NOT */
			while(Password_u8Counter < 5){

				/* GET PRESSED KEY FROM KEYPAD AND STORE IT IN THE VARIABLE Local_u8PressedKey */
				Local_u8PressedKey = KPD_u8GETPressedKey();

				/* CHECK IF PRESSED KEY == 0xFF ,IT MEANS YOU DOESN'T PRESSED ANY KEY */
				while(Local_u8PressedKey == 0xff){

					/* IF YOU DOESN'T PRESSED ANY KEY ,REREAD PRESSED KEY */
					Local_u8PressedKey = KPD_u8GETPressedKey();
				}
				/* HERE ,YOU ALREADY PRESSED RECOGNISED KEY ON THE KEYPAD */

				/* CLEAR KEY(%) => MEANS YOU WANT TO CLEAR PRESSED KEY ON THE LCD TO REENTER ANOTHER ONE
				   ,SO YOU CHECK IF YOU ALREADY PRESSED KEYS (Password_u8Counter != 0) AND CURRENT
				   PRESSED KEY IS % SYMBOL SO CLEAR THE LAST ENTERD NUMBER
				*/
				if((Local_u8PressedKey == '%') && (Password_u8Counter > 0)){
					LCD_voidGOTOXY(1, 11 + (Password_u8Counter-1));
					LCD_voidWritecChar4(' ');
					LCD_voidGOTOXY(1, 11 + (Password_u8Counter-1));

					/* DECREMENT Password_u8Counter BY ONE TO CAN ENTER OTHER NUMBER FROM THE 4-NUMBERS PASSWORD */
					Password_u8Counter--;
				}

				/* CHECK IF THE PRESSED KEY == CLEAR KEY(%) AND YOU DIDN'T PRESSED ANY NUMBER BEFORE THIS MOMENT
				   i.e, NO PASSWORD HAS BEEN ENTERD YET ,SO DON'T CLEAR ANY THING AND CONTINUE)
				*/
				else if((Local_u8PressedKey == '%') && (Password_u8Counter == 0)){
					continue;
				}

				/* CHECK IF THE PRESSED KEY IS LESS THAN THE FOURTH ENTERD NUMBER AND ALSO THIS PRESSED KEY IS NOT THE CLEAR KEY(%) OR THE ENTER KEY(=) */
				else if((Password_u8Counter < 4) && (Local_u8PressedKey != '=') && (Local_u8PressedKey != '%')){

					/* STORE PRESSED NUMBER KEY IN THE PASSWORD ARRAY */
					Login_u8Password[Password_u8Counter] = Local_u8PressedKey;

					/* REPLACE PRESSED NUMBER WITH (*) KEY ON THE LCD FOR SECURITY */
					LCD_voidWritecChar4('*');

					/* INCREMENT Password_u8Counter BY ONE TO KEEP ON GET 4 NUMBERS ONLY AS A PASSWORD FOR THE SYSTEM */
					Password_u8Counter++;
				}

				/* CHECK IF THE PRESSED KEY IS ENTER KEY(=) AND Password_u8Counter < 4 ,DOESN'T MAKE ANY THING AND CONTINUE */
				else if((Password_u8Counter < 4) && (Local_u8PressedKey == '=')){
					continue;
				}

				/* CHECK  IF YOU ALREADY ENTER THE 4-NUMBERS PASSWORD ,AND THE FIFTH PRESSED KEY NOT ENTER KEY(=) ,DOESN'T MAKE ANYTHING AND CONTINUE */
				else if((Password_u8Counter = 4) && (Local_u8PressedKey != '=')){
					continue;
				}

				/* CHECK IF YOU ALREADY ENTER THE 4-NUMBERS PASSWORD ,AND THE FIFTH PRESSED KEY IS THE ENTERED KEY(=) */
				else if((Password_u8Counter = 4) && (Local_u8PressedKey == '=')){

					/* INCREMENT Password_u8Counter BY ONE TO EXIT FROM THE PASSWORD LOOP */
					Password_u8Counter++;
				}
			}

			/* ZEROS THE Password_u8Counter */
			Password_u8Counter = 0;

			/* MAKE GLOBAL VARIABLE CONTROL = 1 TO GO TO THE ENTERED PASSWORD CHECKER PART OF THE SYSTEM */
			Global_u8Control = 2;
		}

		/* CHECKER PASSWORD PART OF THE SYSTEM PASSWORD */
		else if(Global_u8Control == 2){

			/* CHECK IF THE ENTERD PASSWORD IS EQUAL TO THE DEFAULT PASSWORD THROUGHOUT ArrayToInt() FUNCTION
			   WHICH RETURN THE ELEMENT OF THE ARRAY AS A u32 NUMBER
			*/
			if((ArrayToInt(Login_u8Password, 4)) == Default_u8Password){

				/* TURN-OFF RED LED ON PORTB PIN0 */
				DIO_voidSetPinValue(PORTB, PIN0, LOW);

				/* TURN-ON GREEN LED ON PORTB PIN1 */
				DIO_voidSetPinValue(PORTB, PIN1, HIGH);

				/* SET COMPARE MATCH VALUE IN OCR1A TO THE SPECIFIED NUMBER TO TURN SERVO MOTOR WITH 90 DEGREE CELISIUS */
				TIMER1_voidSetOCR1A(375);

				/* CLEAR THE LCD ,THEN GO TO LINE 0 AT POSITION 0 AND WRITE CORRECT ICON THEN THE STRING "CORRECT PASSWORD THE DOOR IS OPEN" */
				LCD_voidClearDisplay();
				LCD_voidWriteSpecialChar4(ICON_u8Correct, 2, 0, 0);
				LCD_voidWriteString((u8*)" CORECT PASWORD");
				LCD_voidGOTOXY(1, 0);
				LCD_voidWriteString((u8*)"THE DOOR IS OPEN");

				/* WAIT FOR Default_u8Delay SPECIFIED TIME */
				_delay_ms(Default_u8Delay);

				/* GO TO TEMPERATURE SENSOR AREA */
				Global_u8Control = 3;
			}

			/* CHECK IF THE ENTERD PASSWORD IS EQUAL TO THE DEFAULT PASSWORD */
			else{
				/* CHECK ON THE NUMBER OF TIMES AT WHICH PASSWORD ENTERD WAS INCORRECT */
				while(INCORRECT_u8Password <= 3){

					/* CLEAR DISPLAY ,THEN GO TO LINE 0 AT POSITION 3 AND WRITE THE STRING "INCORRECT PASSWORD...!" */
					LCD_voidClearDisplay();
					LCD_voidWriteSpecialChar4(ICON_u8Wrong ,1 ,0 ,3);
					LCD_voidGOTOXY(0, 4);
					LCD_voidWriteString((u8*)"INCORRECT");
					LCD_voidGOTOXY(1, 2);
					LCD_voidWriteString((u8*)"PASSWORD...!");

					/* WAIT FOR Default_u8Delay SPECIFIED TIME */
					_delay_ms(Default_u8Delay);

					/* MAKE Global_u8Control = 1 TO RENTER THE CORRECT PASSWORD */
					Global_u8Control = 1;

					/* INCREMENT INCORRECT_u8Password VARIABLE BY ONE TO CALCULATE NUMBER OF TIMES PASSWORD ENTERD */
					INCORRECT_u8Password++;

					/* BREAK TO EXIT FROM THIS LOOP */
					break;
				}

				/* CHECK IF YOU ENTERD PASSWORD 3 TIMES INCORRECTLY */
				if(INCORRECT_u8Password == 4){

					/* RESET INCORRECT_u8Password VARIABLE TO ONE AS AN INITIALIZED VALUE */
					INCORRECT_u8Password = 1;

					/* DISPLAY THE STRING "Oops..! PASSWORD ENTERD 3 TIMES.. INCORRECTLY SORRY YOU... CAN'T ENTER THE SMART HOME UNTILL...
					   WAIT 1 MINUTE" ACCORDING TO LCD_voidClearDisplay() , LCD_voidGOTOXY() ,LCD_voidWriteString() ,and _delay_ms() FUNCTIONS
					*/
					LCD_voidClearDisplay();
					LCD_voidWriteString((u8*)"Oops..! PASSWORD");
					LCD_voidGOTOXY(1, 0);
					LCD_voidWriteString((u8*)"ENTERD 3 TIMES..");
					_delay_ms(Default_u8Delay);
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 0);
					LCD_voidWriteString((u8*)"INCORECTLY ,SORY");
					LCD_voidGOTOXY(1, 0);
					LCD_voidWriteString((u8*)"YOU CAN'T ENTER.");
					_delay_ms(Default_u8Delay);
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 1);
					LCD_voidWriteString((u8*)"THE SMART HOME");
					LCD_voidGOTOXY(1, 4);
					LCD_voidWriteString((u8*)"UNTILL...");
					_delay_ms(Default_u8Delay);
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 2);
					LCD_voidWriteString((u8*)"WAIT 1 MINUTE");

					/* FOR LOOP TO COUNT 60 SECOND */
					for(u8 Counter = 1 ;Counter<=60 ;Counter++){

						/* GO TO LINE 1 AT POSITION 8 ON LCD AND WRITE THE CURRENT VALUE OF COUNTER */
						LCD_voidGOTOXY(1, 8);
						LCD_voidWriteNumber(Counter);

						/* WAIT 50 MILLISECOND */
						_delay_ms(50);
					}

					/* GO TO SYSTEM ENTERED PASSWORD AGAIN */
					Global_u8Control = 1;
				}
			}
		}

		/* TEMPERATURE SENSOR AREA */
		else if(Global_u8Control == 3){

			/* CHECK IF YOU ENTERD THIS LOOP FOR THE FIRST TIME OR NOT ,TO PREVENT REPEATATION OF STRING "TEMPERATURE =" */
			if(TEMPERATURE_u8Flag0 == 0){

				// GO TO LINE 0 AT POSITION 0 ON LCD AND WRITE THE STRING "TEMPRATURE = "
				LCD_voidClearDisplay();
				LCD_voidGOTOXY(0, 0);
				LCD_voidWriteString((u8*)"TEMPRATURE = ");

				/* SET TEMPERATURE_u8Flag0 TO PREVENT REPEATATION */
				TEMPERATURE_u8Flag0 = 1;
			}

			/* SET ADC_u8ChannelSelected GLOBAL VARIABLE TO 0 TO GO TO THE TEMPERATURE SENSOR AREA IN THE CALL BACK FUNCTION OF ADC */
			ADC_u8ChannelSelected = 0;

			// READ CHANNEL0 ASYNCHROUNOUSLY (START CONVERSION)
			ADC_voidReadChannelASyn(CHANNEL0);

			/* WAIT THE SPECIFIED VALUE OF TIME IN Default_u8Delay VARIABLE */
			_delay_ms(Default_u8Delay);

			/* CHECK IF THE SYSTEM ENTER THIS AREA FOR THE FIRST TIME BEFORE RISE END_u8Flag FLAG */
			if(END_u8Flag == 0){

				/* GO TO AREA 6 TO ZEROS FLAGS BEFORE GO TO AREA 5 (GAS SENSOR AREA) SAFELY */
				Global_u8Control = 6;
			}

			/* CHECK IF THE SYSTEM ALREADY RISE END_u8Flag AND PIN2 ON PORTD IS LOW (FALLING EDGE OF THE EXTERNAL INTERRUPT 0) */
			if((END_u8Flag == 1) && (DIO_u8GetPinValue(PORTD, PIN2) == 0)){

				/* BE HERE IN THE TEMPERATURE SENSOR AREA */
				Global_u8Control = 3;
			}

			/* CHECK IF THE SYSTEM ALREADY RISE END_u8Flag AND PIN2 ON PORTD IS HIGH (RISSING EDGE OF THE EXTERNAL INTERRUPT 0) */
			else if((END_u8Flag == 1) && (DIO_u8GetPinValue(PORTD, PIN2) == 1)){

				/* GO TO AREA 10 TO ZEROS FLAGS BEFORE GO TO AREA 9 (RTC AREA SAFELY) */
				Global_u8Control = 10;
			}
		}

		/* THIS AREA TO ZEROS FLAGS OF TEMPERATURE SENSOR BEFORE ENTER TEMPERATURE SENSOR AREA */
		else if(Global_u8Control == 4){

			/* ZEROS THE FLAGS OF TEMPERATURE SENSOR FIRSTLY */
			TEMPERATURE_u16DigitalVoltage 		= 0;
			TEMPERATURE_u16OldDigitalVoltage 	= 0;
			TEMPERATURE_u16AnalogVoltagemv 		= 0;
			TEMPERATURE_u16Temp 				= 0;
			TEMPERATURE_u8Flag0					= 0;
			TEMPERATURE_u8Flag1 				= 0;
			TEMPERATURE_u8Flag2 				= 0;
			TEMPERATURE_u8Flag3 				= 0;
			TEMPERATURE_u8Flag4 				= 0;
			TEMPERATURE_u8Flag5 				= 0;

			/* GO TO TEMPERATURE SENSOR AREA SAFELY */
			Global_u8Control = 3;
		}

		/* GAS SENSOR AREA */
		else if(Global_u8Control == 5){

			/* CHECK IF GAS IS NOT DETECTED AND IT'S FLAG IS ZERO */
			if(DIO_u8GetPinValue(PORTA, PIN1) == 0 && GAS_Flag1 == 0){

				/* CLEAR THE LCD ,THEN WRITE THE STRING "GAS IS NOT DETECTED" */
				LCD_voidClearDisplay();
				LCD_voidGOTOXY(0, 3);
				LCD_voidWriteString((u8*)"GAS IS NOT");
				LCD_voidGOTOXY(1, 4);
				LCD_voidWriteString((u8*)"DETECTED");

				/* TURN-OFF EMERGENCY LED */
				DIO_voidSetPinValue(PORTA, PIN6, LOW);

				/* SET GAS_Flag1 TO PREVENT ENTER THIS IF CONDITION AGAIN UNTILL GAS IS DETECTED OR GO TO OTHER AREA SUCH AS TEMPERATURE AREA */
				GAS_Flag1 = 1;

				/* CLEAR THE OTHER FLAG TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
				GAS_Flag2 = 0;
			}

			/* CHECK IF GAS IS DETECTED AND IT'S FLAG IS ZERO */
			else if(DIO_u8GetPinValue(PORTA, PIN1) == 1 && GAS_Flag2 == 0){

				/* CLEAR THE LCD ,THEN WRITE THE STRING "GAS IS DETECTED" */
				LCD_voidClearDisplay();
				LCD_voidWriteString((u8*)"GAS IS DETECTED");

				/* TURN-ON EMERGENCY LED TO IDENTICATE THERE'S A DANGEROUS DUE TO THE PRESSENCE OF GAS */
				DIO_voidSetPinValue(PORTA, PIN6, HIGH);

				/* SET GAS_Flag2 TO PREVENT ENTER THIS IF CONDITION AGAIN UNTILL GAS IS NOT DETECTED OR GO TO OTHER AREA SUCH AS TEMPERATURE AREA */
				GAS_Flag2 = 1;

				/* CLEAR THE OTHER FLAG TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
				GAS_Flag1 = 0;
			}

			/* WAIT THE SPECIFIED VALUE OF TIME IN Default_u8Delay VARIABLE */
			_delay_ms(Default_u8Delay);

			/* GO TO AREA 8 TO ZEROS FLAGS BEFORE GO TO AREA 7 (LIGHT SYSTEM AREA) */
			Global_u8Control = 8;
		}

		/* THIS AREA TO ZEROS FLAGS OF GAS SENSOR BEFORE ENTER GAS SENSOR AREA */
		else if(Global_u8Control == 6){

			/* ZEROS GAS SENSOR FLAGS */
			GAS_Flag1 = 0;
			GAS_Flag2 = 0;

			/* GO TO GAS SENSOR AREA SAFELY */
			Global_u8Control = 5;
		}

		/* LIGHT SYSTEM AREA (LDR & PIR SENSOR) */
		else if(Global_u8Control == 7){

			/* CHECK IF PIR SENSOR DETECT SOMEONE FOR THE FIRST TIME */
			if(DIO_u8GetPinValue(PORTA, PIN2) == 1 && PIR_u8Flag1 == 0){

				/* CLEAR DISPLAY ,THEN WRITE THE STRING "SOMEONE IS DETECTED" */
				LCD_voidClearDisplay();
				LCD_voidGOTOXY(0, 3);
				LCD_voidWriteString((u8*)"SOMEONE IS");
				LCD_voidGOTOXY(1, 4);
				LCD_voidWriteString((u8*)"DETECTED");

				/* WAIT THE SPECIFIED VALUE OF TIME IN Default_u8Delay VARIABLE */
				_delay_ms(Default_u8Delay);

				/* SET ADC_u8ChannelSelected GLOBAL VARIABLE TO 3 TO GO TO THE LDR AREA IN THE CALL BACK FUNCTION OF ADC */
				ADC_u8ChannelSelected = 3;

				// READ CHANNEL3 ASYNCHROUNOUSLY (START CONVERSION)
				ADC_voidReadChannelASyn(CHANNEL3);

				/* WAIT THE SPECIFIED VALUE OF TIME IN Default_u8Delay VARIABLE */
				_delay_ms(Default_u8Delay);

				/* SET PIR_u8Flag1 TO PREVENT ENTER THIS IF CONDITION AGAIN UNTILL SOMEONE IS NOT DETECTED OR GO TO OTHER AREA SUCH AS TEMPERATURE AREA */
				PIR_u8Flag1 = 1;

				/* CLEAR THE OTHER FLAG TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
				PIR_u8Flag2 = 0;
			}

			/* CHECK IF PIR SENSOR DETECT SOMEONE FOR NOT THE FIRST TIME */
			else if(DIO_u8GetPinValue(PORTA, PIN2) == 1 && PIR_u8Flag1 == 1){

				/* SET ADC_u8ChannelSelected GLOBAL VARIABLE TO 3 TO GO TO THE LDR AREA IN THE CALL BACK FUNCTION OF ADC */
				ADC_u8ChannelSelected = 3;

				// READ CHANNEL3 ASYNCHROUNOUSLY (START CONVERSION)
				ADC_voidReadChannelASyn(CHANNEL3);

				/* WAIT BEFORE LEAVE */
				_delay_ms(20);

			}

			/* CHECK IF PIR SENSOR NOT DETECT SOMEONE FOR THE FIRST TIME */
			else if(DIO_u8GetPinValue(PORTA, PIN2) == 0 && PIR_u8Flag2 == 0){

				/* TURN-OFF LEDS OF LIGHT SYSTEM */
				DIO_voidSetPinValue(PORTA, PIN4, LOW);
				DIO_voidSetPinValue(PORTA, PIN5, LOW);
				DIO_voidSetPinValue(PORTB, PIN2, LOW);

				/* CLEAR DISPLAY ,THEN WRITE "NO ONE DETECTED,LEDS TURNED-OFF" */
				LCD_voidClearDisplay();
				LCD_voidGOTOXY(0, 0);
				LCD_voidWriteString((u8*)"NO ONE DETECTED,");
				LCD_voidGOTOXY(1, 0);
				LCD_voidWriteString((u8*)"LEDS TURNED-OFF");

				/* WAIT THE SPECIFIED VALUE OF TIME IN Default_u8Delay VARIABLE */
				_delay_ms(Default_u8Delay);

				/* SET PIR_u8Flag2 TO PREVENT ENTER THIS IF CONDITION AGAIN UNTILL SOMEONE IS DETECTED OR GO TO OTHER AREA SUCH AS TEMPERATURE AREA */
				PIR_u8Flag2 = 1;
			}

			/* CHECK PIR SENSOR DETECT SOME ONE WHEN YOU ARE IN LIGHT SYSTEM AREA AND
			   IN THE PREVIOUS STATE PIR SENSOR WASN'T DETECT ANYONE ,ALSO READED LDR VALUE IS CHANGED.
			*/
			else if(DIO_u8GetPinValue(PORTA, PIN2) == 1 && PIR_u8Flag2 == 1){

				/* CLEAR PIR_u8Flag1 TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
				PIR_u8Flag1 = 0;

				/* ZEROS THE FLAGS OF LDR SENSOR IN ADC CALL BACK FUNCTION */
				LDR_u16DigitalVoltage 	 = 0;
				LDR_u16OldDigitalVoltage = 0;
				LDR_u16AnalogVoltagemv 	 = 0;
				LDR_u8Flag1 			 = 0;
				LDR_u8Flag2 			 = 0;
				LDR_u8Flag3 			 = 0;
				LDR_u8Flag4 			 = 0;
			}

			/* CHECK IF THE SYSTEM ENTER THIS AREA FOR THE FIRST TIME BEFORE RISE END_u8Flag FLAG */
			if(END_u8Flag == 0){

				/* GO TO AREA 10 TO CLEAR FLAGS THEN GO TO RTC AREA SAFELY */
				Global_u8Control = 10;
			}

			/* CHECK IF THE SYSTEM ALREADY RISE END_u8Flag AND PIN3 ON PORTD IS LOW (FALLING EDGE OF THE EXTERNAL INTERRUPT 1) */
			if((END_u8Flag == 1) && (DIO_u8GetPinValue(PORTD, PIN3) == 0)){

				/* BE HERE IN THE LIGHT SYSTEM AREA */
				Global_u8Control = 7;
			}

			/* CHECK IF THE SYSTEM ALREADY RISE END_u8Flag AND PIN3 ON PORTD IS HIGH (RISSING EDGE OF THE EXTERNAL INTERRUPT 1) */
			else if((END_u8Flag == 1) && (DIO_u8GetPinValue(PORTD, PIN3) == 1)){

				/* GO TO AREA 10 TO CLEAR FLAGS THEN GO TO RTC AREA SAFELY */
				Global_u8Control = 10;
			}
		}

		/* THIS AREA TO ZEROS FLAGS OF LIGHT SYSTEM BEFORE ENTER LIGHT SYSTEM AREA */
		else if(Global_u8Control == 8){

			/* ZEROS THE FLAGS OF LIGHT SYSTEM */
			PIR_u8Flag1				 = 0;
			PIR_u8Flag2 			 = 0;
			LDR_u16DigitalVoltage  	 = 0;
			LDR_u16OldDigitalVoltage = 0;
			LDR_u16AnalogVoltagemv 	 = 0;
			LDR_u8Flag1 			 = 0;
			LDR_u8Flag2 			 = 0;
			LDR_u8Flag3 			 = 0;
			LDR_u8Flag4 			 = 0;

			/* GO TO THE LIGHT SYSTEM SAFELY */
			Global_u8Control = 7;
		}

		/* RTC AREA */
		else if(Global_u8Control == 9){

			/* CHECK IF YOU ENTER THIS AREA TO THE FIRST TIME OR NOT */
			if(RTC_u8Flag == 0){

				/* CLEAR THE DISPLAY */
				LCD_voidClearDisplay();

				/* RAISE RTC_u8Flag TO PREVENT REPEATATION */
				RTC_u8Flag = 1;

				/* RAISE END_u8Flag TO IDENTICATE THAT THE SYSTEM SHOW ALL MODULES ON THE LCD FOR THE FIRST TIME */
				END_u8Flag = 1;
			}

			/* GO TO THE SPECIFIED LOCATIONS AND WRITE THE CURRENT DATE AND TIME */
			LCD_voidGOTOXY(0, 0);
			RTC_GetDateTime(&rtc);
			LCD_voidWriteString((u8*)"TIME : ");
			LCD_voidWriteNumber(rtc.RTC_u8Hour);
			LCD_voidWritecChar4(':');
			LCD_voidWriteNumber(rtc.RTC_u8Minute);
			LCD_voidWritecChar4(':');
			LCD_voidWriteNumber(rtc.RTC_u8Second);
			LCD_voidGOTOXY(1, 0);
			LCD_voidWriteString((u8*)"DATE : ");
			LCD_voidWriteNumber(rtc.RTC_u8Year);
			LCD_voidWritecChar4('/');
			LCD_voidWriteNumber(rtc.RTC_u8Month);
			LCD_voidWritecChar4('/');
			LCD_voidWriteNumber(rtc.RTC_u8Date);
		}

		/* THIS AREA TO ZEROS FLAGS OF RTC BEFORE ENTER RTC AREA */
		else if(Global_u8Control == 10){

			/* CLEAR THE FLAGS */
			RTC_u8Flag = 0;

			/* GO TO RTC AREA SAFELY */
			Global_u8Control = 9;
		}
	}
}

/* CALL BACK FUNCTION OF ADC INTERRUPT */
void ADC_FUNC(void){

	/* CECK ON TEMPERATURE SENSOR AREA IN THE CALL BACK FUNCTION OF ADC */
	if(ADC_u8ChannelSelected == 0){

		/* ASSIGN CONVERTED DIGITAL VALUE TO THE THE CORRESPONDING VARIABLE */
		TEMPERATURE_u16DigitalVoltage = ADC_u16ReadASynValue();

		/* CHECK IF OLD READED DIGITAL VALUE EQUAL NEW READED DIGITAL VALUE TO PREVENT REPEATATION */
		if(TEMPERATURE_u16OldDigitalVoltage != TEMPERATURE_u16DigitalVoltage){

			/* CALC ANALOG READED VOLTAGE IN MILISECOND AND ASSIGN IT TO THE CORRESPONDING GLOBAL VARIABLE */
			TEMPERATURE_u16AnalogVoltagemv = (u16)(((u32)TEMPERATURE_u16DigitalVoltage*5000UL)/1024UL);

			/* CALC THE VALUE OF TEMPERATURE IN DEGREE CELISIUS AND ASSIGN IT TO THE CORRESPONDING GLOBAL VATIABLE */
			TEMPERATURE_u16Temp = (TEMPERATURE_u16AnalogVoltagemv / 10);

			/* CHECK IF YOU COME FROM TEMPERATURE SENSOR AREA */
			if(REALTIME_u8TemperatureFlag == 0){

				/* GO TO LINE 0 AT POSITION 13 AND WRITE THE TEMPERATURE VALUE IN CELISIUS */
				LCD_voidGOTOXY(0, 13);
				LCD_voidWriteString((u8*)"   ");
				LCD_voidGOTOXY(0, 13);
				LCD_voidWriteNumber(TEMPERATURE_u16Temp);

				/* CHECK IF THE READED TEMPERATURE VALUE IS LESS THAN OR EQUAL 20 */
				if(TEMPERATURE_u16Temp <= 20){
					/* CLEAR DIRECTION OF THE FAN ,THUS FAN IS STILL STOPPED */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, LOW);

					/* CHECK ON THE FIRST TIME ENTER THE SUPER IF => (Local_u16Temp <= 20) */
					if(TEMPERATURE_u8Flag1 == 0){

						/* TURN-OFF EMERGENCY LED */
						DIO_voidSetPinValue(PORTD, PIN7, LOW);

						/* CLEAR LINE TWO OF THE LCD AND WRITE THE STRING "FAN IS OFF" */
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"                ");
						LCD_voidGOTOXY(1, 3);
						LCD_voidWriteString((u8*)"FAN IS OFF");

						/* SET TEMPERATURE_Flag1 TO PREVENT ENTER THIS IF CONDITION AGAIN UNTILL GO TO OTHER SUPER IF SUCH AS
						   (Local_u16Temp > 20 && Local_u16Temp <= 25) FIRSTLY.
					    */
						TEMPERATURE_u8Flag1 = 1;

						/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
						TEMPERATURE_u8Flag2 = 0;
						TEMPERATURE_u8Flag3 = 0;
						TEMPERATURE_u8Flag4 = 0;
						TEMPERATURE_u8Flag5 = 0;
					}
				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 21 AND 25 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 20 && TEMPERATURE_u16Temp <= 25){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.25 */
					TIMER0_voidSetOCR0(64);

					/* CHECK ON THE FIRST TIME ENTER THE SUPER IF => (ADC_u16Temp > 20 && ADC_u16Temp <= 25) */
					if(TEMPERATURE_u8Flag2 == 0){

						/* TURN-OFF EMERGENCY LED */
						DIO_voidSetPinValue(PORTD, PIN7, LOW);

						/* CLEAR LINE TWO OF THE LCD AND WRITE THE STRING "FAN SPEED IS 1" */
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"                ");
						LCD_voidGOTOXY(1, 1);
						LCD_voidWriteString((u8*)"FAN SPEED IS 1");

						/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
						TEMPERATURE_u8Flag1 = 0;
						TEMPERATURE_u8Flag2 = 1;
						TEMPERATURE_u8Flag3 = 0;
						TEMPERATURE_u8Flag4 = 0;
						TEMPERATURE_u8Flag5 = 0;
					}
				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 26 AND 35 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 25 && TEMPERATURE_u16Temp <= 35){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.5 */
					TIMER0_voidSetOCR0(128);

					/* CHECK ON THE FIRST TIME ENTER THE SUPER IF => (ADC_u16Temp > 25 && ADC_u16Temp <= 35) */
					if(TEMPERATURE_u8Flag3 == 0){

						/* TURN-OFF EMERGENCY LED */
						DIO_voidSetPinValue(PORTD, PIN7, LOW);

						/* CLEAR LINE TWO OF THE LCD AND WRITE THE STRING "FAN SPEED IS 2" */
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"                ");
						LCD_voidGOTOXY(1, 1);
						LCD_voidWriteString((u8*)"FAN SPEED IS 2");

						/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
						TEMPERATURE_u8Flag1 = 0;
						TEMPERATURE_u8Flag2 = 0;
						TEMPERATURE_u8Flag3 = 1;
						TEMPERATURE_u8Flag4 = 0;
						TEMPERATURE_u8Flag5 = 0;
					}

				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 36 AND 45 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 35 && TEMPERATURE_u16Temp <= 45){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.75 */
					TIMER0_voidSetOCR0(192);

					/* CHECK ON THE FIRST TIME ENTER THE SUPER IF => (ADC_u16Temp > 35 && ADC_u16Temp <= 45) */
					if(TEMPERATURE_u8Flag4 == 0){

						/* TURN-OFF EMERGENCY LED */
						DIO_voidSetPinValue(PORTD, PIN7, LOW);

						/* CLEAR LINE TWO OF THE LCD AND WRITE THE STRING "FAN SPEED IS 3" */
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"                ");
						LCD_voidGOTOXY(1, 1);
						LCD_voidWriteString((u8*)"FAN SPEED IS 3");

						/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
						TEMPERATURE_u8Flag1 = 0;
						TEMPERATURE_u8Flag2 = 0;
						TEMPERATURE_u8Flag3 = 0;
						TEMPERATURE_u8Flag4 = 1;
						TEMPERATURE_u8Flag5 = 0;
					}
				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BEGGER THAN 45 */
				else if(TEMPERATURE_u16Temp > 45){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 1 */
					TIMER0_voidSetOCR0(255);

					/* CHECK ON THE FIRST TIME ENTER THE SUPER IF => (ADC_u16Temp > 45) */
					if(TEMPERATURE_u8Flag5 == 0){

						/* TURN-ON EMERGENCY LED TO IDENTICATE THE PRESSENCE OF DANGEROUS DUE TO THE HIGH TEMPERATURE IN THE ATMOSPHERE */
						DIO_voidSetPinValue(PORTD, PIN7, HIGH);

						/* CLEAR LINE TWO OF THE LCD AND WRITE THE STRING "EMERGENCY LED ON" */
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"                ");
						LCD_voidGOTOXY(1, 0);
						LCD_voidWriteString((u8*)"EMERGENCY LED ON");

						/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO THEIR IF CONDITION FOR THE FIRST TIME */
						TEMPERATURE_u8Flag1 = 0;
						TEMPERATURE_u8Flag2 = 0;
						TEMPERATURE_u8Flag3 = 0;
						TEMPERATURE_u8Flag4 = 0;
						TEMPERATURE_u8Flag5 = 1;
					}
				}
			}

			/* CHECK IF YOU COME FROM REAL-TIME SYSTEM */
			else if(REALTIME_u8TemperatureFlag == 1){

				/* CHECK IF THE READED TEMPERATURE VALUE IS LESS THAN OR EQUAL 20 */
				if(TEMPERATURE_u16Temp <= 20){

					/* CLEAR DIRECTION OF THE FAN ,THUS FAN IS STILL STOPPED */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, LOW);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0 (MOTOR STOPPED) */
					TIMER0_voidSetOCR0(0);

					/* TURN-OFF EMERGENCY LED */
					DIO_voidSetPinValue(PORTD, PIN7, LOW);
				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 21 AND 25 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 20 && TEMPERATURE_u16Temp <= 25){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.25 */
					TIMER0_voidSetOCR0(64);

					/* TURN-OFF EMERGENCY LED */
					DIO_voidSetPinValue(PORTD, PIN7, LOW);
				}
				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 26 AND 35 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 25 && TEMPERATURE_u16Temp <= 35){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.5 */
					TIMER0_voidSetOCR0(128);

					/* TURN-OFF EMERGENCY LED */
					DIO_voidSetPinValue(PORTD, PIN7, LOW);
				}

				/* CHECK IF THE READED TEMPERATURE VALUE IS BETWEEN 36 AND 45 INCLUSIVE */
				else if(TEMPERATURE_u16Temp > 35 && TEMPERATURE_u16Temp <= 45){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 0.75 */
					TIMER0_voidSetOCR0(192);

					/* TURN-OFF EMERGENCY LED */
					DIO_voidSetPinValue(PORTD, PIN7, LOW);
				}

				else if(TEMPERATURE_u16Temp > 45){

					/* SET DIRECTION OF THE FAN WITH CLOCK-WISE ,THUS FAN IS TURNED ON */
					DIO_voidSetPinValue(PORTD, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN7, HIGH);

					/* SET THE SPEED OF DC MOTOR (FAN) DUTY CYCLE = 1 */
					TIMER0_voidSetOCR0(255);

					/* TURN-ON EMERGENCY LED TO IDENTICATE THE PRESSENCE OF DANGEROUS DUE TO THE HIGH TEMPERATURE IN THE ATMOSPHERE */
					DIO_voidSetPinValue(PORTD, PIN7, HIGH);
				}
			}
			// ASSIGN NEW READED DIGITAL VALUE TO THE OLD ONE GLOBAL VARIABLE
			TEMPERATURE_u16OldDigitalVoltage = TEMPERATURE_u16DigitalVoltage;
		}
	}

	/* CHECK ON LDR AREA IN CALL BACK FUNCTION OF ADC */
	else if(ADC_u8ChannelSelected == 3){

		/* ASSIGN CONVERTED DIGITAL VALUE TO THE THE CORRESPONDING VARIABLE */
		LDR_u16DigitalVoltage = ADC_u16ReadASynValue();

		/* CHECK IF OLD READED DIGITAL VALUE EQUAL NEW READED DIGITAL VALUE TO PREVENT REPEATATION */
		if(LDR_u16OldDigitalVoltage != LDR_u16DigitalVoltage){

			// CALC ANALOG READED VOLTAGE IN MILIVOLT AND ASSIGN IT TO THE CORRESPONDING GLOBAL VARIABLE
			LDR_u16AnalogVoltagemv = (u16)((((u32)LDR_u16DigitalVoltage*5000UL)/1024UL));

			/* CHECK IF YOU COME FROM LIGHT SYSTEM AREA */
			if(REALTIME_u8LightSystemFlag == 0){

				/* CHECK IF READED DIGITAL VALUE IS LESS THAN OR EQUAL 93 OR NOT AND IF THIS CONDITION TAKE PLACE FOR THE FIRST TIME OR NOT */
				if(LDR_u16DigitalVoltage <= 93 && LDR_u8Flag1 == 0){

					/* TURN-ON SYSTEM LEDS */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, HIGH);
					DIO_voidSetPinValue(PORTB, PIN2, HIGH);

					/* CLEAR THE DISPLAY ,THEN WRITE THE STRING "LOW LIGHT : (value of light) volt = (value of volt)mv" */
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 0);
					LCD_voidWriteString((u8*)"LOW LIGHT : ");
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 1);
					LCD_voidWriteString((u8*)"volt = ");
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");

					/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO
					   THEIR IF CONDITION FOR THE FIRST TIME AND SET LDR_u8Flag1 TO PREVENT REPEATATION
					*/
					LDR_u8Flag1 = 1;
					LDR_u8Flag2 = 0;
					LDR_u8Flag3 = 0;
					LDR_u8Flag4 = 0;
				}

				/* CHECK IF READED DIGITAL VALUE IS LESS THAN OR EQUAL 93 OR NOT AND IF THIS CONDITION TAKE PLACE BEFORE OR NOT */
				else if(LDR_u16DigitalVoltage <= 93 && LDR_u8Flag1 == 1){

					/* UPDATES VALUES OF (LIGHT AND VOLT) ONLY */
					LCD_voidGOTOXY(0, 12);
					LCD_voidWriteString((u8*)"     ");
					LCD_voidGOTOXY(0, 12);
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteString((u8*)"        ");
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 93 AND LESS THAN OR EQUAL 512 OR NOT AND IF THIS CONDITION TAKE PLACE FOR THE FIRST TIME OR NOT */
				else if(LDR_u16DigitalVoltage > 93 && LDR_u16DigitalVoltage <= 512 && LDR_u8Flag2 == 0){

					/* TURN-ON 2 LEDS ONLY OF THE SYSTEM */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, HIGH);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);

					/* CLEAR THE DISPLAY ,THEN WRITE THE STRING "MEDIUM LIGHT:(value of light)   volt = (value of volt)mv" */
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 0);
					LCD_voidWriteString((u8*)"MEDIUM LIGHT:");
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 1);
					LCD_voidWriteString((u8*)"volt = ");
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");

					/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO
					   THEIR IF CONDITION FOR THE FIRST TIME AND SET LDR_u8Flag2 TO PREVENT REPEATATION
					*/
					LDR_u8Flag1 = 0;
					LDR_u8Flag2 = 1;
					LDR_u8Flag3 = 0;
					LDR_u8Flag4 = 0;
				}
				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 93 AND LESS THAN OR EQUAL 512 OR NOT AND IF THIS CONDITION TAKE PLACE BEFORE OR NOT */
				else if(LDR_u16DigitalVoltage > 93 && LDR_u16DigitalVoltage <= 512 && LDR_u8Flag2 == 1){

					/* UPDATES VALUES OF (LIGHT AND VOLT) ONLY */
					LCD_voidGOTOXY(0, 13);
					LCD_voidWriteString((u8*)"    ");
					LCD_voidGOTOXY(0, 13);
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteString((u8*)"        ");
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 512 AND LESS THAN OR EQUAL 682 OR NOT AND IF THIS CONDITION TAKE PLACE FOR THE FIRST TIME OR NOT */
				else if(LDR_u16DigitalVoltage > 512 && LDR_u16DigitalVoltage <= 682 && LDR_u8Flag3 == 0){

					/* TURN-ON 1 LED ONLY OF THE SYSTEM */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, LOW);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);

					/* CLEAR THE DISPLAY ,THEN WRITE THE STRING "GOOD LIGHT:(value of light)   volt = (value of volt)mv" */
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 0);
					LCD_voidWriteString((u8*)"GOOD LIGHT : ");
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 1);
					LCD_voidWriteString((u8*)"volt = ");
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");

					/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO
					   THEIR IF CONDITION FOR THE FIRST TIME AND SET LDR_u8Flag3 TO PREVENT REPEATATION
					*/
					LDR_u8Flag1 = 0;
					LDR_u8Flag2 = 0;
					LDR_u8Flag3 = 1;
					LDR_u8Flag4 = 0;
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 512 AND LESS THAN OR EQUAL 682 OR NOT AND IF THIS CONDITION TAKE PLACE BEFORE OR NOT */
				else if(LDR_u16DigitalVoltage > 512 && LDR_u16DigitalVoltage <= 682 && LDR_u8Flag3 == 1){

					/* UPDATES VALUES OF (LIGHT AND VOLT) ONLY */
					LCD_voidGOTOXY(0, 13);
					LCD_voidWriteString((u8*)"    ");
					LCD_voidGOTOXY(0, 13);
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteString((u8*)"        ");
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 682 OR NOT AND IF THIS CONDITION TAKE PLACE FOR THE FIRST TIME OR NOT */
				else if(LDR_u16DigitalVoltage > 682 && LDR_u8Flag4 == 0){

					/* TURN-OFF 3 LEDS */
					DIO_voidSetPinValue(PORTA, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN5, LOW);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);

					/* CLEAR THE DISPLAY ,THEN WRITE THE STRING "HIGH LIGHT:(value of light)   volt = (value of volt)mv" */
					LCD_voidClearDisplay();
					LCD_voidGOTOXY(0, 0);
					LCD_voidWriteString((u8*)"HIGH LIGHT:");
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 1);
					LCD_voidWriteString((u8*)"volt = ");
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");

					/* CLEAR THE OTHER FLAGS TO ALLOW WRITEING THE SPECIFIED STRING WHEN GO TO
					   THEIR IF CONDITION FOR THE FIRST TIME AND SET LDR_u8Flag4 TO PREVENT REPEATATION
					*/
					LDR_u8Flag1 = 0;
					LDR_u8Flag2 = 0;
					LDR_u8Flag3 = 0;
					LDR_u8Flag4 = 1;
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 682 OR NOT AND IF THIS CONDITION TAKE PLACE BEFORE OR NOT */
				else if(LDR_u16DigitalVoltage > 682 && LDR_u8Flag4 == 1){

					/* UPDATES VALUES OF (LIGHT AND VOLT) ONLY */
					LCD_voidGOTOXY(0, 11);
					LCD_voidWriteString((u8*)"      ");
					LCD_voidGOTOXY(0, 11);
					LCD_voidWriteNumber(LDR_u16DigitalVoltage);
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteString((u8*)"        ");
					LCD_voidGOTOXY(1, 8);
					LCD_voidWriteNumber(LDR_u16AnalogVoltagemv);
					LCD_voidWriteString((u8*)"mv");
				}
			}

			/* CHECK IF YOU COME FROM THE REAL TIME SYSTEM */
			else if(REALTIME_u8LightSystemFlag == 1){

				/* CHECK IF READED DIGITAL VALUE IS LESS THAN OR EQUAL 93 OR NOT */
				if(LDR_u16DigitalVoltage <= 93){

					/* TURN-ON SYSTEM LEDS */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, HIGH);
					DIO_voidSetPinValue(PORTB, PIN2, HIGH);
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 93 AND LESS THAN OR EQUAL 512 OR NOT */
				else if(LDR_u16DigitalVoltage > 93 && LDR_u16DigitalVoltage <= 512){

					/* TURN-ON 2 LEDS ONLY OF THE SYSTEM */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, HIGH);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 512 AND LESS THAN OR EQUAL 682 OR NOT */
				else if(LDR_u16DigitalVoltage > 512 && LDR_u16DigitalVoltage <= 682){

					/* TURN-ON 1 LED ONLY OF THE SYSTEM */
					DIO_voidSetPinValue(PORTA, PIN4, HIGH);
					DIO_voidSetPinValue(PORTA, PIN5, LOW);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);
				}

				/* CHECK IF READED DIGITAL VALUE IS BIGGER THAN 682 OR NOT */
				else if(LDR_u16DigitalVoltage > 682){

					/* TURN-OFF 3 LEDS */
					DIO_voidSetPinValue(PORTA, PIN4, LOW);
					DIO_voidSetPinValue(PORTA, PIN5, LOW);
					DIO_voidSetPinValue(PORTB, PIN2, LOW);
				}
			}

			// ASSIGN NEW READED DIGITAL VALUE TO THE OLD ONE GLOBAL VARIABLE
			LDR_u16OldDigitalVoltage = LDR_u16DigitalVoltage;
		}
	}
}

/* FUNCTION TO RETURN THE ENTERD PASSWORD (AS ARRAY) AS A (u32) NUMBER */
u32 ArrayToInt(u32 *ptr ,u8 size){
	u32 result = 0;
	for(u32 i=0 ;i<size ;i++){
		result = (result * 10) + (*(ptr+i));
	}
	return result;
}

/* CALL BACK FUNCTION OF EXTERNAL INTERRUPT 0 */
void EXTI0_FUNC(void){

	/* CHECK IF THE SYSTEM RAISED END_u8Flag FLAG OR NOT */
	if(END_u8Flag == 1){

		/* GO TO AREA 4 TO CLEAR FLAGS OF TEMPERATURE SENSOR BEFORE GO TO THE TEMPERATURE AREA SENSOR SAFELY */
		Global_u8Control = 4;
	}
	else{
		/* DO NoTHING */
	}
}

/* CALL BACK FUNCTION OF EXTERNAL INTERRUPT 1 */
void EXTI1_FUNC(void){

	/* CHECK IF THE SYSTEM RAISED END_u8Flag FLAG OR NOT */
	if(END_u8Flag == 1){

		/* GO TO AREA 8 TO CLEAR FLAGS OF LIGHT SYSTEM BEFORE GO TO THE LIGHT SYSTEM AREA SAFELY */
		Global_u8Control = 8;
	}
	else{
		/* DO NoTHING */
	}
}
