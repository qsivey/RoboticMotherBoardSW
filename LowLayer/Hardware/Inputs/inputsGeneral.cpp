/** ____________________________________________________________________
 *
 *	@file		inputsGeneral.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "inputsGeneral.h"


/*	This array provide hardware driver with low layer inputs mapping
 *	to peripheral layer for correct GPIO initialization
 */
const GPIO_Channel_t GPIO_ReferenceArray [] =
	/*
	||			GPIO PIN		  ||		   GPIO PORT		  ||		 GPIO PIN AF		 ||
	 */
	{ {	POT_ADC_PIN,				POT_ADC_GPIO_PORT,				0
	},{	LEFT_BUT_PIN,				LEFT_BUT_GPIO_PORT,				0
	},{	CENTER_BUT_PIN,				CENTER_BUT_GPIO_PORT,			0
	},{	RIGHT_BUT_PIN,				RIGHT_BUT_GPIO_PORT,			0

	}};


Input *inputClassesArray [] =
{
	&Potentiometer,
	&LeftButton,
	&CenterButton,
	&RightButton,

	/* Total members quantity must be equal HW_NUM_INPUTS */
};


#if (PROJ_USE_FREERTOS)

	void TaskPeripheralManage (void *params)
	{
		for (ui8 i = 0; i < countof_(inputClassesArray); i++)
			if (inputClassesArray[i]->GetState() == IN_NEED_INIT)
				inputClassesArray[i]->Init();

		osTaskDelete(NULL);

		while (1);
	}

#endif
