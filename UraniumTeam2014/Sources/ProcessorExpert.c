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

/* Liberdado de Servo e outros */
#define CENTRO_SERVO 18518
#define LIDERDADE_SERVO 320
#define ESQUERDA_SERVO (CENTRO_SERVO-LIDERDADE_SERVO)
#define DIREITO_SERVO (CENTRO_SERVO+LIDERDADE_SERVO)
#define ERR_MAX_CENTER 6 // valor do erro para o centro da pista


/* Boost */
int FIRST_PULSE = 0; //pulso inicial                                  200
int NORMAL_PULSE = 0; //pulso normal                                   70
#define PWM_PULSE 1 // tamanho do pulso em PWM (controla velocidade no pulso)
int SAMPLES_IN_CURVE = 50; //total de detecção de amostras de curvas 50
#define SAMPLES_IN_STRAIGHT 10 //total de deteccão de amostras de retas 10

/* PWM Speed */
int RETA_PWM = 450; //velocidade em reta sem pulso                    450
int MIN_TRACAO = 900; //tracao em curva da roda de dentro             700
#define MAX_TRACAO 100 //tracao em reta da roda de fora 400

/* Parada do Carro */
int velociParada = 700;
#define TIME_BREAK 100000 //1000000


int maiorAmostra;
int menorAmostra;
int dadosCamera[128];
int linha[100];
uint8 limiar = 100;
uint8 cameraFinished;
uint8 contTrack = 0;
uint8 widthTrack = 100;
uint8 widthTrackMin = 95;
uint8 widthTrackMax = 100;
bool paradaAtiva = FALSE;
byte switchDIP = 0;

int8 l;
int8 bordaL;
int8 bordaR;
int8 totalParada = 0;
int8 ladoL;
int8 ladoR;

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

int maxTracao = MAX_TRACAO;
int rangeTracao;

//Boost
bool saiuDeCurva = TRUE;
int contCurva = 0;
bool estaEmReta  = TRUE;
int contReta = 0;
int timeMachine = 0;
int widthPulse = 0;

int8 pretos[6];

void wait(long a) {
	while (a > 0) {
		a--;
	}
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
	switchDIP = captaValueSwitch();
	
	/*ALGORITMO */
	//1 - Centralizar a Mecanica (forçar com alicate) V
	//2 - Corrigir camera com Osciloscopio (na deixar bater) V
	//3 - Diminuir diferencial e veficar Trava! Flag (Guardar valor encontrado)
	//MIN_TRACAO = 900 - switchDIP*25;
	MIN_TRACAO = 825;
	//4 - Aumentar tracao em reta (Guardar valor encontrado)
	//RETA_PWM = 450 - switchDIP*25;
	RETA_PWM = 300;
	//5 - Primeiro Pulso (Guardar)
	//FIRST_PULSE = switchDIP*25;
	//6 - Pulso Normal
	NORMAL_PULSE = switchDIP*10;
	FIRST_PULSE = switchDIP*10;
	//7 - Pulso Normal deteccao de curva
	//SAMPLES_IN_CURVE = 50-switchDIP*5;
	SAMPLES_IN_CURVE = 10;
	//8 - Velocidade depois do Timer
	//velociParada = 700-switchDIP*25;
	//9 - Valor do Timer (Verificar LEDs)
	//10 - Valor do Freio
	
	

	
	// DESATIVAR PARADA!!!
//	if(switchDIP & 0b1000)
//		Relogio1_Enable();
//	else
//		Relogio1_Disable();
	
	//
	
	widthPulse = FIRST_PULSE;

	TracaoEnable_PutVal(1);
	TracaoA2_SetDutyUS(999);
	TracaoB2_SetDutyUS(999);

	cameraFinished = 0;
	CameraAnalog_Enable();
	CameraAnalog_Start();
	maxTracao = MAX_TRACAO;//-(captaValueSwitch()*10);
	rangeTracao = MIN_TRACAO-maxTracao;
	
	linha[0] = 0;
	linha[99] = 0;
	while (TRUE) {
		if (cameraFinished) {
			cameraFinished = 0;
			
			limiar = ((float) (maiorAmostra - menorAmostra)/2)+menorAmostra;
			totalParada = 0;
			
			
//#define MMI 64-25
//#define MMX 64+25
//			int kkk = 0;
////			//TESTE
//			for(kkk=0;kkk<128;kkk++){
//				if(kkk > MMI && kkk < MMX) dadosCamera[kkk] = 255;
//				else dadosCamera[kkk] = 1;
//			}
//			maiorAmostra = 255;
//			menorAmostra = 1;
			
			for (l = 15; l <= 112; l++) {
				linha[l-14] = dadosCamera[l] > limiar;
				if((contTrack >= 15) && ((l-14) > 34) && ((l-14) < 68)){
					totalParada = totalParada + !linha[l-14];
				}
			}
			

			for (l = 49; l >= 0; l--) {
				if (!linha[l]) {
					bordaL = l;
					break;
				}
			}
			for (l = 50; l < 100; l++) {
				if (!linha[l]) {
					bordaR = l;
					break;
				}
			}
			
			if(contTrack < 15){
				contTrack++;
				if(contTrack == 15){
					widthTrack = (bordaR - bordaL);
				}
			}
			
			diffBorda = bordaR - bordaL;
			
			if(bordaL == 0){
				ladoL = bordaR - widthTrack;
				ladoR = bordaR;
			}
			else if(bordaR == 99){
				ladoL = bordaL;
				ladoR = bordaL + widthTrack;
			}
			else {
				ladoR = bordaR;
				ladoL = bordaL;
			}
			
			output = (ladoR + ladoL) / 2;
			err = 52 - output;
			errAbs = abs(err);
			
			if(previousErrAbs > 19){ //Trava o carro para caso perder pista, voltar
				if(diffBorda > 48 && diffBorda < 75 && ((previousErr > 0 && err > 0) || (previousErr < 0 && err < 0))){ //bordaL != 0 && bordaR != 99 &&
				}
				else {
					err = previousErr;
					errAbs = previousErrAbs;
				}
			}
			
			if(diffBorda > 75 && previousErrAbs < 19){
				err = previousErr;
				errAbs = previousErrAbs;
				setServo(CENTRO_SERVO);
			}
			else {
				servo = (ESQUERDA_SERVO + (DIREITO_SERVO-ESQUERDA_SERVO)*((float)(22+err)/44));
				setServo(servo);	
			}
			
			if(errAbs > ERR_MAX_CENTER){ //Estah em curva
				/* proporcial de tracao em curva */
				if(err < 0){
					tracao1 = maxTracao + rangeTracao * ((float)errAbs/21);
					tracao2 = maxTracao;
				}
				else {
					tracao1 = maxTracao;
					tracao2 = maxTracao + rangeTracao * ((float)errAbs/21);
				}
				setTracao(tracao1,tracao2);
				
				/* deteccao de curva */
				contReta = 0;
				contCurva++;
				if(contCurva > SAMPLES_IN_CURVE){
					saiuDeCurva = TRUE;
				}

			}
			else { // Estah em reta
				/* deteccao de reta */
				contCurva = 0;
				contReta++;
				if(contReta > SAMPLES_IN_STRAIGHT){
					estaEmReta = TRUE;
				}
				/* gerador de pulsos */
				if(saiuDeCurva && estaEmReta && !paradaAtiva){
					setTracao(PWM_PULSE,PWM_PULSE);		
					timeMachine++;
					if(timeMachine > widthPulse){
						saiuDeCurva = FALSE;
						estaEmReta = FALSE;
						timeMachine = 0;
						widthPulse = NORMAL_PULSE;
					}
				}
				else {
					setTracao(RETA_PWM,RETA_PWM);
				}
			}
			
			if(paradaAtiva) acenderLeds(0b1111);
			
			/* Para o carrinho */
			if(totalParada > 3 && (previousErrAbs < 10) && paradaAtiva){
				Servo_SetDutyUS(CENTRO_SERVO);
				TracaoA1_SetDutyUS(999);
				TracaoB1_SetDutyUS(999);
				TracaoA2_SetDutyUS(1);
				TracaoB2_SetDutyUS(1);
				wait(TIME_BREAK);
				TracaoEnable_PutVal(0);
			}
			
			previousErr = err;
			previousErrAbs = errAbs;

			
			menorAmostra = 255;
			maiorAmostra = 0;
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
