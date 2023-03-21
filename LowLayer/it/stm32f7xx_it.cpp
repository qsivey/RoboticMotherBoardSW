/** ____________________________________________________________________
 *
 * 	@file		stm32f7xx_it.cpp
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#include "stm32f7xx_it.h"


void NMI_Handler (void)
{
	while (1);
}


void HardFault_Handler (void)
{
	while (1);
}


void MemManage_Handler (void)
{
	while (1);
}


void BusFault_Handler (void)
{
	while (1);
}


void UsageFault_Handler (void)
{
	while (1);
}


void DebugMon_Handler (void)
{
	;
}


#if (PROJ_USE_FREERTOS == SET_OFF)

	void SVC_Handler (void)
	{
		;
	}


	void PendSV_Handler (void)
	{
		;
	}


	void SysTick_Handler (void)
	{
		HAL_IncTick();
	}

#endif
