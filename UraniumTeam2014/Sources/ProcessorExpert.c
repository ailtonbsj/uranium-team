/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-09-10, 14:22, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file ProcessorExpert.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
 **  @{
 */
/* MODULE ProcessorExpert */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CameraAnalog.h"
#include "AdcLdd1.h"
#include "CameraClock.h"
#include "BitIoLdd1.h"
#include "CameraSI.h"
#include "BitIoLdd2.h"
#include "LED1.h"
#include "BitIoLdd3.h"
#include "LED2.h"
#include "BitIoLdd4.h"
#include "LED3.h"
#include "BitIoLdd5.h"
#include "LED4.h"
#include "BitIoLdd6.h"
#include "Servo.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "SW1.h"
#include "BitIoLdd7.h"
#include "SW2.h"
#include "BitIoLdd8.h"
#include "SW3.h"
#include "BitIoLdd9.h"
#include "SW4.h"
#include "BitIoLdd10.h"
#include "TracaoEnable.h"
#include "BitIoLdd11.h"
#include "TracaoB2.h"
#include "BitIoLdd12.h"
#include "TracaoA2.h"
#include "BitIoLdd13.h"
#include "TracaoA1.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "TracaoB1.h"
#include "PwmLdd3.h"
#include "Serial.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <extras/extras_stdlib.h>
#include <math.h>

int maiorAmostra;
int menorAmostra;
int dadosCamera[88];
int linha[88];
uint8 cameraFinished;

#define CENTRO_SERVO 18500
#define LIDERDADE_SERVO 300
#define ESQUERDA_SERVO (CENTRO_SERVO-LIDERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIDERDADE_SERVO)

void wait(long a) {
	while (a > 0) {
		a--;
	}
}

void putSerial(int valor, char charFinal) {
	char result[15];
	int i = 0;
	itoa(valor, result, 10);
	while (result[i] != '\0') {
		wait(4000);
		Serial_SendChar(result[i]);
		i++;
	}
	wait(4000);
	Serial_SendChar(charFinal);
	wait(4000);
}

int acenderLeds(uint8 num) {
	if (num & 1)
		LED1_PutVal(TRUE);
	else
		LED1_PutVal(FALSE);
	if (num & 2)
		LED2_PutVal(TRUE);
	else
		LED2_PutVal(FALSE);
	if (num & 4)
		LED3_PutVal(TRUE);
	else
		LED3_PutVal(FALSE);
	if (num & 8)
		LED4_PutVal(TRUE);
	else
		LED4_PutVal(FALSE);
	return 0;
}

void setServo(int16 giro) {
	if (giro < ESQUERDA_SERVO) {
		giro = ESQUERDA_SERVO;
	}
	if (giro > DIREITO_SERVO) {
		giro = DIREITO_SERVO;
	}
	Servo_SetDutyUS(giro);
}

void setTracao(int16 motor1, int16 motor2) {
	if (motor1 <= 0)
		motor1 = 1;
	if (motor1 >= 1000)
		motor1 = 999;
	if (motor2 <= 0)
		motor2 = 1;
	if (motor2 >= 1000)
		motor2 = 999;
	TracaoA1_SetDutyUS(motor1);
	TracaoB1_SetDutyUS(motor2);
}

int captaValueSwitch() {
	int saida = 0;
	if (SW1_GetVal()) {
		saida = saida | 1;
	}
	if (SW2_GetVal()) {
		saida = saida | 2;
	}
	if (SW3_GetVal()) {
		saida = saida | 4;
	}
	if (SW4_GetVal()) {
		saida = saida | 8;
	}
	return saida;
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */
	
	int8 l;
	int8 bordaL;
	int8 bordaR;
	int output = 44;
	int input;
	int previos_err = 0;
	int err = 0;
	int8 diffBorda;
	int servo;
	int tracao1;
	int tracao2;
	
	cameraFinished = 0;

	TracaoEnable_PutVal(1);
	TracaoB2_PutVal(0);
	TracaoA2_PutVal(0);

	CameraAnalog_Enable();
	CameraAnalog_Start();
	int swDip;
	swDip = captaValueSwitch();

	while (TRUE) {
		if (cameraFinished == 1) {
			cameraFinished = 0;

			if (maiorAmostra <= 50) {
				//PRETO
				//acenderLeds(0);
			} else if (menorAmostra >= 130) {
				//BRANCO
				//acenderLeds(0b1111);
			} else {
				//LINES
				for (l = 0; l < 88; l++) {
					linha[l] = ((255 / (maiorAmostra - menorAmostra)) * (dadosCamera[l] - menorAmostra));// > 115;
					putSerial(dadosCamera[l],',');
					putSerial(dadosCamera[l],'\r');
					Serial_SendChar('\n');
				}
				
				bordaL = 0;
				bordaR = 88;
				for (l = 43; l >= 0; l--) {
					if (!linha[l]) {
						bordaL = l;
						break;
					}
				}
				for (l = 44; l < 88; l++) {
					if (!linha[l]) {
						bordaR = l;
						break;
					}
				}

				#define WIDTH_TRACK 60
				#define WIDTH_TRACK_MIN WIDTH_TRACK - 3
				#define WIDTH_TRACK_MAX WIDTH_TRACK + 3

				diffBorda = bordaR - bordaL;
				if (!((diffBorda >= WIDTH_TRACK_MIN)
						&& (diffBorda <= WIDTH_TRACK_MAX))) {
					if ((43 - bordaL) < (bordaR - 44))
						bordaR = bordaL + WIDTH_TRACK;
					else
						bordaL = bordaR - WIDTH_TRACK;
				}

				output = (bordaR + bordaL) / 2;
				err = 44 - output;
				
				if(((previos_err > 0 && err < 0) || (previos_err < 0 && err > 0)) && (abs(previos_err) > 17)){
					err = previos_err;
					acenderLeds(0b1111);
				}
				else {
					acenderLeds(0b0000);
				}
				
				input = (1 + (7-1)*((float)abs(err)/44))*err;

				servo = ESQUERDA_SERVO + (DIREITO_SERVO-ESQUERDA_SERVO)*((float)(44+input)/88);

				#define MAX_TRACAO 900
				#define MIN_TRACAO 999
				#define RANGE_TRACAO MAX_TRACAO-MIN_TRACAO

				tracao1 = MAX_TRACAO + (MIN_TRACAO - MAX_TRACAO) * ((float)-input/44);
				tracao2 = MAX_TRACAO + (MIN_TRACAO - MAX_TRACAO) * ((float)+input/44);
				if (tracao1 < MAX_TRACAO)	tracao1 = MAX_TRACAO;
				if (tracao2 < MAX_TRACAO)	tracao2 = MAX_TRACAO;
				if (tracao1 > MIN_TRACAO)	tracao1 = MIN_TRACAO;
				if (tracao2 > MIN_TRACAO)	tracao2 = MIN_TRACAO;

				setServo(servo);
				setTracao(tracao1, tracao2);
				
				previos_err = err;
			}

			maiorAmostra = 0;
			menorAmostra = 255;
			CameraAnalog_Enable();
			CameraAnalog_Start();
		}

	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.2 [05.06]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
