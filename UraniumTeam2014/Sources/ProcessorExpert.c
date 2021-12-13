/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-09-12, 13:13, # CodeGen: 0
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
#include "SW1.h"
#include "BitIoLdd7.h"
#include "SW2.h"
#include "BitIoLdd8.h"
#include "SW3.h"
#include "BitIoLdd9.h"
#include "SW4.h"
#include "BitIoLdd10.h"
#include "Servo.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "TracaoA1.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "PwmLdd3.h"
#include "TracaoB1.h"
#include "PwmLdd4.h"
#include "TracaoB2.h"
#include "PwmLdd5.h"
#include "TracaoEnable.h"
#include "BitIoLdd11.h"
#include "TracaoA2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdlib.h>

int maiorAmostra;
int menorAmostra;
int dadosCamera[88];
int linha[88];
uint8 cameraFinished;
int8 sentido = 1;

uint8 contTrack = 0;
uint8 widthTrack = 60;
uint8 widthTrackMin = 57;
uint8 widthTrackMax = 63;

int8 l;
int8 bordaL;
int8 bordaR;
bool twoBorderDetect = FALSE;

int output = 44;
int input;
int err = 0;
int errAbs = 0;
int previousErr = 0;
int previousErrAbs = 0;
int8 diffBorda;
int servo;
int tracao1;
int tracao2;

#define CENTRO_SERVO 18500
#define LIDERDADE_SERVO 300
#define ESQUERDA_SERVO (CENTRO_SERVO-LIDERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIDERDADE_SERVO)

int maxTracao = 400;
#define MIN_TRACAO 750 //999
int rangeTracao;

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

//void setTracaoFull(int a, int b){
//	if(sentido == -1){
//		setTracao(a,b);
//	}
//	else {
//		setTracao(b,a);
//	}
//}

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
	
	#define ESQUERDA 0
	#define DIREITA 1

	TracaoEnable_PutVal(1);
	TracaoA2_SetDutyUS(999);
	TracaoB2_SetDutyUS(999);

	cameraFinished = 0;
	CameraAnalog_Enable();
	CameraAnalog_Start();
	maxTracao = 400-(captaValueSwitch()*5);
	rangeTracao = MIN_TRACAO-maxTracao;
	

	while (TRUE) {
		if (cameraFinished) {
			cameraFinished = 0;

			//Code Here!
			if (maiorAmostra <= 50) {
				//PRETO
				//acenderLeds(0b1001);
			} else if (menorAmostra >= 70) {
				//BRANCO
				setServo(CENTRO_SERVO);
				//acenderLeds(0b1111);
			} else {
				//LINES
				//acenderLeds(0);
				for (l = 0; l < 88; l++) {
					linha[l] = (((float) 255 / (maiorAmostra - menorAmostra))	* (dadosCamera[l] - menorAmostra)) > 115;
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
				
				if(contTrack < 15){
					contTrack++;
					if(contTrack == 15){
						widthTrack = bordaR - bordaL;
						widthTrackMax += 4;
						widthTrackMin -= 4;
					}
				}
				

				diffBorda = bordaR - bordaL;
				if (!((diffBorda >= widthTrackMin)
						&& (diffBorda <= widthTrackMax))) {
					if(!(diffBorda < 30)){
						if ((43 - bordaL) < (bordaR - 44))
							bordaR = bordaL + widthTrack;
						else
							bordaL = bordaR - widthTrack;	
					}

					twoBorderDetect = FALSE;
				}
				else twoBorderDetect = TRUE;

				output = (bordaR + bordaL) / 2;
				err = 43 - output;
				
				if(previousErrAbs > 22 && !twoBorderDetect){
					err = previousErr;
				}
				errAbs = abs(err);
				
				servo = ESQUERDA_SERVO + (DIREITO_SERVO-ESQUERDA_SERVO)*((float)(23+err)/46);
				setServo(servo);
				
				input = err;
				
				if(errAbs > 10){ //14
					tracao1 = maxTracao + rangeTracao * ((float)-input/23);
					tracao2 = maxTracao + rangeTracao * ((float)+input/23);
					if (tracao1 < maxTracao)	tracao1 = maxTracao;
					if (tracao2 < maxTracao)	tracao2 = maxTracao;
					if (tracao1 > MIN_TRACAO)	tracao1 = MIN_TRACAO;
					if (tracao2 > MIN_TRACAO)	tracao2 = MIN_TRACAO;
					setTracao(tracao1,tracao2);
					acenderLeds(0b1111);
				}
				else {
					setTracao(maxTracao,maxTracao);
					acenderLeds(0);
				}
				
				previousErr = err;
				previousErrAbs = errAbs;
			}

			menorAmostra = 255;
			maiorAmostra = 0;
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
