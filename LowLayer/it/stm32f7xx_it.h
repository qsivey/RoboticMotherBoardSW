/** ____________________________________________________________________
 *
 * 	@file		stm32f7xx_it.h
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#ifndef		_STM32F7XX_IT_H_
#define 	_STM32F7XX_IT_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
void NMI_Handler (void);
void HardFault_Handler (void);
void MemManage_Handler (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void DebugMon_Handler (void);
#if (DRV_USE_FREERTOS == 0)
	void SVC_Handler (void);
	void PendSV_Handler (void);
	void SysTick_Handler (void);
#endif

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _STM32F7XX_IT_H_ */
