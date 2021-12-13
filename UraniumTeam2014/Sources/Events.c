/* ###################################################################
 **     Filename    : Events.c
 **     Project     : ProcessorExpert
 **     Processor   : MKL25Z128VLK4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2014-09-12, 13:13, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */
uint16 cameraCont;
uint8 cameraClock;
uint8 amostra;
uint8 amostra1;
extern int dadosCamera[2][128];
extern uint8 cameraFinished;
int contaTempo = 0;

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMIINT (module Events)
 **
 **     Component   :  Cpu [MKL25Z128LK4]
 **     Description :
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the <NMI
 **         interrupt> property is set to 'Enabled'.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Cpu_OnNMIINT(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  CameraAnalog_OnEnd (module Events)
 **
 **     Component   :  CameraAnalog [ADC]
 **     Description :
 **         This event is called after the measurement (which consists
 **         of <1 or more conversions>) is/are finished.
 **         The event is available only when the <Interrupt
 **         service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CameraAnalog_OnEnd(void) {
	/* Write your code here ... */
	if (cameraCont <= 130) {
		if (cameraClock == 1) {
			if (cameraCont <= 1) {
				CameraSI_PutVal(0);

			}
			cameraCont++;
		}
		cameraClock = !cameraClock;
	} else if(cameraCont <= 132){
		CameraSI_PutVal(0);
		cameraClock = 0;
		cameraCont++;
	} else {
		cameraClock = 0;
		cameraCont = 0;
		CameraClock_PutVal(cameraClock);
		CameraAnalog_Stop();
		CameraAnalog_Disable();
		cameraFinished = 1;
	}
	CameraClock_PutVal(cameraClock);

	CameraAnalog_GetChanValue8(0,&amostra);
	CameraAnalog_GetChanValue8(1,&amostra1);
	if (cameraCont >= 0 && cameraCont <= 127) {
		dadosCamera[0][cameraCont] = amostra;
		dadosCamera[1][cameraCont] = amostra1;
	}
}

/*
 ** ===================================================================
 **     Event       :  CameraAnalog_OnCalibrationEnd (module Events)
 **
 **     Component   :  CameraAnalog [ADC]
 **     Description :
 **         This event is called when the calibration has been finished.
 **         User should check if the calibration pass or fail by
 **         Calibration status method./nThis event is enabled only if
 **         the <Interrupt service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CameraAnalog_OnCalibrationEnd(void) {
	/* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Relogio1_OnInterrupt (module Events)
**
**     Component   :  Relogio1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Relogio1_OnInterrupt(void)
{
  /* Write your code here ... */
	if(contaTempo > 44){
		//TracaoEnable_PutVal(0);
	}
	contaTempo++;
}

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
#endif 

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
