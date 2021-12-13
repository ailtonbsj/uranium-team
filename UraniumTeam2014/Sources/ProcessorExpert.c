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
#include "Relogio1.h"
#include "TimerIntLdd1.h"
#include "TU3.h"
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

int maiorAmostra[2];
int menorAmostra[2];
int dadosCamera[2][128];
int linha[2][100];
uint8 limiar[2];
uint8 cameraFinished;
uint8 contTrack = 0;
uint8 widthTrack = 100;
uint8 widthTrackMin = 95;
uint8 widthTrackMax = 100;

int8 l;
int8 bordaL[2];
int8 bordaR[2];
int8 totalParada = 0;
int8 ladoL;
int8 ladoR;

int output = 44;
int input;
int err = 0;
int errAbs = 0;
int previousErr = 0;
int previousErrAbs = 0;
int8 diffBorda[2];
int servo;
int tracao1;
int tracao2;

#define CENTRO_SERVO 18500
#define LIDERDADE_SERVO 300
#define ESQUERDA_SERVO (CENTRO_SERVO-LIDERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIDERDADE_SERVO)

int maxTracao = 400;
int rangeTracao;

int8 pretos[6];

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
	
	Relogio1_Enable();

	TracaoEnable_PutVal(1);
	TracaoA2_SetDutyUS(999);
	TracaoB2_SetDutyUS(999);

	cameraFinished = 0;
	CameraAnalog_Enable();
	CameraAnalog_Start();
	maxTracao = 350;//-(captaValueSwitch()*10);
	#define MIN_TRACAO 750 //999
	int reta_pwm = 400;
	rangeTracao = MIN_TRACAO-maxTracao;
	
	linha[0][0] = 0;
	linha[0][99] = 0;
	while (TRUE) {
//		if(!SensorParada_GetVal()){
//			acenderLeds(0b1111);
//		}
		if (cameraFinished) {
			int cont;
			cameraFinished = 0;
			menorAmostra[0] = 255;
			maiorAmostra[0] = 0;
			menorAmostra[1] = 255;
			maiorAmostra[1] = 0;
			
			for(cont=0; cont < 128; cont++){
				if (dadosCamera[0][cont] > maiorAmostra[0]) maiorAmostra[0] = dadosCamera[0][cont];
				if (dadosCamera[0][cont] < menorAmostra[0])	menorAmostra[0] = dadosCamera[0][cont];
				
				if (dadosCamera[1][cont] > maiorAmostra[1]) maiorAmostra[1] = dadosCamera[1][cont];
				if (dadosCamera[1][cont] < menorAmostra[1])	menorAmostra[1] = dadosCamera[1][cont];
			}
			
			limiar[0] = ((float) (maiorAmostra[0] - menorAmostra[0])/2)+menorAmostra[0];
			limiar[1] = ((float) (maiorAmostra[1] - menorAmostra[1])/2)+menorAmostra[1];
			totalParada = 0;
			for (l = 15; l <= 112; l++) {
				linha[0][l-14] = dadosCamera[0][l] > limiar[0];
				linha[1][l-14] = dadosCamera[1][l] > limiar[1];
				if((contTrack >= 15) && ((l-14) > 34) && ((l-14) < 68)){
					totalParada = totalParada + !linha[0][l-14];
				}
			}
			
//			totalParada = 0;
//			for (l = 32; l <= 70; l++) {
//				if(linha[l] == 0) totalParada++;
//			}
			

			for (l = 49; l >= 0; l--) {
				if (!linha[0][l]) {
					bordaL[0] = l;
					break;
				}
			}
			for (l = 50; l < 100; l++) {
				if (!linha[0][l]) {
					bordaR[0] = l;
					break;
				}
			}
			
			for (l = 49; l >= 0; l--) {
				if (!linha[1][l]) {
					bordaL[1] = l;
					break;
				}
			}
			for (l = 50; l < 100; l++) {
				if (!linha[1][l]) {
					bordaR[1] = l;
					break;
				}
			}
			
			if(contTrack < 15){
				contTrack++;
				if(contTrack == 15){
					widthTrack = (bordaR[0] - bordaL[0]);
				}
			}
			
			diffBorda[0] = bordaR[0] - bordaL[0];
			diffBorda[1] = bordaR[1] - bordaL[1];
			
//			if(diffBorda < 30){
//				acenderLeds(0b1111);
//			}
//			else {
//				acenderLeds(0);
//			}
			
//			if(diffBorda < 16) {
//				TracaoEnable_PutVal(0);
//			}
			
			if(bordaL[0] == 0){
				ladoL = bordaR[0] - widthTrack;
				ladoR = bordaR[0];
			}
			else if(bordaR[0] == 99){
				ladoL = bordaL[0];
				ladoR = bordaL[0] + widthTrack;
			}
			else {
				ladoR = bordaR[0];
				ladoL = bordaL[0];
			}
			
			output = (ladoR + ladoL) / 2;
			err = 52 - output;
			errAbs = abs(err);
			
			if(previousErrAbs > 19){
				if(diffBorda[0] > 48 && diffBorda[0] < 75 && ((previousErr > 0 && err > 0) || (previousErr < 0 && err < 0))){ //bordaL[0] != 0 && bordaR[0] != 99 &&
				}
				else {
					err = previousErr;
					errAbs = previousErrAbs;
				}
			}
			
			if(diffBorda[0] > 75 && previousErrAbs < 19){
				err = previousErr;
				errAbs = previousErrAbs;
				setServo(CENTRO_SERVO);
			}
			else {
				servo = (ESQUERDA_SERVO + (DIREITO_SERVO-ESQUERDA_SERVO)*((float)(22+err)/44));
				setServo(servo);	
			}
			
			if(errAbs > 6){
				if(err < 0){
					tracao1 = maxTracao + rangeTracao * ((float)errAbs/21);
					tracao2 = maxTracao;
				}
				else {
					tracao1 = maxTracao;
					tracao2 = maxTracao + rangeTracao * ((float)errAbs/21);
				}
				
				setTracao(tracao1,tracao2);
			}
			else {
				#define TAMANHO 45
				#define TAMANHO_MIN TAMANHO-9
				#define TAMANHO_MAX TAMANHO+9
				if(diffBorda[1] > TAMANHO_MIN && diffBorda[1] < TAMANHO_MAX){
					acenderLeds(0b1111);
					reta_pwm = 300;
				}
				else {
					acenderLeds(0);
					reta_pwm = 650;
				}
				setTracao(reta_pwm,reta_pwm);
			}
			
//			if(totalParada > 0 && previousErrAbs < 10){
//				TracaoEnable_PutVal(0);
//			}
			
			previousErr = err;
			previousErrAbs = errAbs;

			CameraSI_PutVal(1);
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
