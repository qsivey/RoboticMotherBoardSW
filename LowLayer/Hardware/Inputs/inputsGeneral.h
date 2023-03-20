/** ____________________________________________________________________
 *
 *	@file		inputsGeneral.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INPUTS_GENERAL_H_
#define		_INPUTS_GENERAL_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"analogInput.h"
#include	"digitalInput.h"


extern Input *inputClassesArray [];


#if (PROJ_USE_FREERTOS)
	void TaskPeripheralManage (void *params);
#endif

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _INPUTSGENERAL_H_ */
