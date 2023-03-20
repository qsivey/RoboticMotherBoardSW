/** ____________________________________________________________________
 *
 * 	@file		service.h
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#ifndef		_SERVICE_H_
#define		_SERVICE_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Timer Constants & Macros
 */
/*  - - - - - User Defined Parameters - - - - - - */
#define		INTERNAL_MAIN_TIMER		&htim7
/*  - - - - - - - - - - - - - - - - - - - - - - - */

#define		START_TIMER(TIM)		HAL_TIM_Base_Start_IT(TIM)

#define		GET_FLAG_TIM_SR_UIF(TIM)		__HAL_TIM_GET_FLAG(TIM, TIM_FLAG_UPDATE)
#define		GET_FLAG_TIM_DIER_UIE(TIM)		__HAL_TIM_GET_IT_SOURCE(TIM, TIM_FLAG_UPDATE)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										Timer Struct
 */
typedef struct Timer_t
{
	ui32	timCount;

	__TIMER_STRUCT;

}	Timer_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void MBSLL_TurnDebugLED_ON (void);

void MBSLL_TurnDebugLED_OFF (void);

void MBSLL_TurnDebugLED_Toggle (void);

void MBSLL_TimerInit ( /* IN */		Timer_t *timer,
					   /* REF */	__TIMER_STRUCT);

ui32 MBSLL_GetTimeOnlyUs ( /* OUT */	Timer_t *timer);

ui32 MBSLL_GetTimeUs ( /* OUT */	Timer_t *timer);

ui32 MBSLL_GetTimeMs ( /* OUT */	Timer_t *timer);

void MBSLL_TimerDRV_CallBack ( /* IN */	Timer_t *timer);

void MBSLL_DelayUs ( /* IN */	Timer_t *timer,
								ui32 us);

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif


#endif		/* _SERVICE_H_ */
