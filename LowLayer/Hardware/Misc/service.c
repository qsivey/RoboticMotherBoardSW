/** ____________________________________________________________________
 *
 * 	@file		service.c
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#include "service.h"


//void MBSLL_TurnDebugLED_ON (void)
//{
//	HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PIN, GPIO_PIN_SET);
//}
//
//
//void MBSLL_TurnDebugLED_OFF (void)
//{
//	HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PIN, GPIO_PIN_RESET);
//}
//
//
//void MBSLL_TurnDebugLED_Toggle (void)
//{
//	HAL_GPIO_TogglePin(DEBUG_LED_PORT, DEBUG_LED_PIN);
//}
//

void MBSLL_TimerInit ( /* IN */		Timer_t *timer,

					   /* REF */	__TIMER_STRUCT)
{
	timer->tim = tim;
	timer->timCount = 0;

	START_TIMER(timer->tim);
}


ui32 MBSLL_GetTimeOnlyUs ( /* OUT */	Timer_t *timer)
{
	return timer->tim->Instance->CNT;  // 0 --> 999
}


ui32 MBSLL_GetTimeUs ( /* OUT */	Timer_t *timer)
{
	return (timer->timCount * 1000) + timer->tim->Instance->CNT;
}


ui32 MBSLL_GetTimeMs ( /* OUT */	Timer_t *timer)
{
	return timer->timCount;
}


void MBSLL_TimerDRV_CallBack ( /* IN */	Timer_t *timer)
{
	timer->timCount++;

	timer->tim->Instance->CNT = 0;

	if (timer->timCount > 4000000)
		timer->timCount = 0;
}


void MBSLL_DelayUs ( /* IN */	Timer_t *timer,
								ui32 us)
{
	ui32 count = (MBSLL_GetTimeMs(timer) * 1000) + MBSLL_GetTimeOnlyUs(timer);

	while (((MBSLL_GetTimeMs(timer) * 1000) + MBSLL_GetTimeOnlyUs(timer) - count) < us);
}


/* __________________________________________________________________ */
