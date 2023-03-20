///** ____________________________________________________________________
// *
// * 	@file		motorDriver.h
// *
// *	@author		qsivey
// *
// *	VK / TG:	@qsivey
// *	mail:		qsivey@gmail.com
// *
// *	K-Lab		Laboratory of robotics and mechatronics
// *	____________________________________________________________________
// */
//
//#ifndef		_MOTOR_DRIVER_H_
//#define		_MOTOR_DRIVER_H_
//
//#ifdef 		__cplusplus
//extern 		"C" {
//#endif
///*  = = = = = = = = = = = = = = = = = = = = = = = */
//
//#include	"hardware.h"
//#include	"service.h"
//
//
///* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
// *									Hardware Structs
// */
//typedef struct
//{
//	/* PWM */
//	__TIMER_STRUCT;
//
//	ui32	channel1,
//			channel2,
//			channel3;
//
//	/* EN */
//	__GPIO_STRUCT;
//
//	ui16	enablePin;
//
//}	MotorDriver_t;
//
//
///* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
// *								 Function Prototypes
// */
//void MBSLL_AttachHardwareToMotor ( /* IN: */	MotorDriver_t *motorDriver,
//								   /* REF: */	__TIMER_STRUCT,
//												const ui32 motorChannel1,
//												const ui32 motorChannel2,
//												const ui32 motorChannel3,
//												__GPIO_STRUCT,
//												const ui16 enablePin);
//
//void MBSLL_TurnOnMotor ( /* IN: */	MotorDriver_t *motorDriver);
//
//void MBSLL_TurnOffMotor ( /* IN: */	MotorDriver_t *motorDriver);
//
//void MBSLL_StartChannelPWM ( /* IN: */	MotorDriver_t *motorDriver,
//										ui32 channel);
//
//void MBSLL_StopChannelPWM ( /* IN: */	MotorDriver_t *motorDriver,
//										ui32 channel);
//
//void MBSLL_CalculateTimerPWM ( /* IN: */	MotorDriver_t *motorDriver,
//											Timer_t *timer,
//											double speed);
//
//void MBSLL_MotorSimpleMotion ( /* IN: */	MotorDriver_t *motorDriver,
//											Timer_t *timer,
//											ui16 speed);
//
///*  = = = = = = = = = = = = = = = = = = = = = = = */
//#ifdef 		__cplusplus
//			}
//#endif
//
//#endif		/* _MOTOR_DRIVER_H_ */
