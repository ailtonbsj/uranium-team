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
uint8 cameraCont;
uint8 cameraClock;
uint8 amostra;
extern int maiorAmostra;
extern int menorAmostra;
extern int dadosCamera[88];
extern uint8 cameraFinished;

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
	if (cameraCont <= 135) {
		if (cameraClock == 1) {
			if (cameraCont <= 1) {
				CameraSI_PutVal(0);

			}
			cameraCont++;
		}
		cameraClock = !cameraClock;
	} else {
		cameraClock = 0;
		cameraCont = 0;
		CameraClock_PutVal(cameraClock);
		CameraAnalog_Stop();
		CameraAnalog_Disable();
		cameraFinished = 1;
	}
	if (cameraCont == 0 && cameraClock == 0) {
		CameraSI_PutVal(1);
	}CameraClock_PutVal(cameraClock);

	CameraAnalog_GetValue8(&amostra);
	if (cameraCont >= 20 && cameraCont <= 107) {
		dadosCamera[cameraCont - 20] = amostra;
		if (amostra > maiorAmostra)
			maiorAmostra = amostra;
		if (amostra < menorAmostra)
			menorAmostra = amostra;
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
