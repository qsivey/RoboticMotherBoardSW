///** ____________________________________________________________________
// *
// * 	@file		motorDriver.c
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
//#include "motorDriver.h"
//
//
///* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
// *													Executable Functions
// */
//void MBSLL_AttachHardwareToMotor ( /* IN: */	MotorDriver_t *motorDriver,
//								   /* REF: */	__TIMER_STRUCT,
//												const ui32 motorChannel1,
//												const ui32 motorChannel2,
//												const ui32 motorChannel3,
//												__GPIO_STRUCT,
//												const ui16 enablePin)
//{
//	motorDriver->tim = tim;
//
//	motorDriver->channel1 = motorChannel1;
//	motorDriver->channel2 = motorChannel2;
//	motorDriver->channel3 = motorChannel3;
//
//	motorDriver->gpio = gpio;
//	motorDriver->enablePin = enablePin;
//}
//
//
//void MBSLL_TurnOnMotor ( /* IN: */	MotorDriver_t *motorDriver)
//{
//	HAL_GPIO_WritePin(motorDriver->gpio, motorDriver->enablePin, GPIO_PIN_SET);
//}
//
//
//void MBSLL_TurnOffMotor ( /* IN: */	MotorDriver_t *motorDriver)
//{
//	HAL_GPIO_WritePin(motorDriver->gpio, motorDriver->enablePin, GPIO_PIN_RESET);
//}
//
//
//void MBSLL_StartChannelPWM ( /* IN: */	MotorDriver_t *motorDriver,
//										ui32 channel)
//{
//	HAL_TIM_PWM_Start(motorDriver->tim, channel);
//}
//
//
//void MBSLL_StopChannelPWM ( /* IN: */	MotorDriver_t *motorDriver,
//										ui32 channel)
//{
//	HAL_TIM_PWM_Stop(motorDriver->tim, channel);
//}
//
//
//void MBSLL_CalculateTimerPWM ( /* IN: */	MotorDriver_t *motorDriver,
//											Timer_t *timer,
//											double speed)
//{
//	static double channel1Offset = 0.0;
//	static double channel2Offset = 120.0;
//	static double channel3Offset = 240.0;
//
//	ui16 offsetConst = motorDriver->tim->Init.Period / 2;
//
//	motorDriver->tim->Instance->CCR1 = (sin(ConvertDegreesToRadians(channel1Offset)) + 1.0) * offsetConst;
//	motorDriver->tim->Instance->CCR2 = (sin(ConvertDegreesToRadians(channel2Offset)) + 1.0) * offsetConst;
//	motorDriver->tim->Instance->CCR3 = (sin(ConvertDegreesToRadians(channel3Offset)) + 1.0) * offsetConst;
//
//	channel1Offset += speed;
//	channel2Offset += speed;
//	channel3Offset += speed;
//
//	settozeroif_(channel1Offset, 360);
//	settozeroif_(channel2Offset, 360);
//	settozeroif_(channel3Offset, 360);
//}
//
//
//void MBSLL_MotorSimpleMotion ( /* IN: */	MotorDriver_t *motorDriver,
//											Timer_t *timer,
//											ui16 speed)
//{
////	MBSLL_StopChannelPWM(motorDriver, motorDriver->channel2);
////	MBSLL_DelayUs(timer, speed);
////
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel1);
////	MBSLL_DelayUs(timer, speed);
////
////	MBSLL_StopChannelPWM(motorDriver, motorDriver->channel3);
////	MBSLL_DelayUs(timer, speed);
////
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel2);
////	MBSLL_DelayUs(timer, speed);
////
////	MBSLL_StopChannelPWM(motorDriver, motorDriver->channel1);
////	MBSLL_DelayUs(timer, speed);
////
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel3);
////	MBSLL_DelayUs(timer, speed);
//
//
////	HAL_GPIO_WritePin(TCH1_GPIO_Port, TCH1_Pin, GPIO_PIN_SET);
////	MBSLL_DelayUs(timer, 90000);
////
////	HAL_GPIO_WritePin(TCH2_GPIO_Port, TCH2_Pin, GPIO_PIN_SET);
////	HAL_GPIO_WritePin(TCH1_GPIO_Port, TCH1_Pin, GPIO_PIN_RESET);
////	MBSLL_DelayUs(timer, 90000);
////
////	HAL_GPIO_WritePin(TCH3_GPIO_Port, TCH3_Pin, GPIO_PIN_SET);
////	HAL_GPIO_WritePin(TCH2_GPIO_Port, TCH2_Pin, GPIO_PIN_RESET);
////	MBSLL_DelayUs(timer, 90000);
////
////	HAL_GPIO_WritePin(TCH3_GPIO_Port, TCH3_Pin, GPIO_PIN_RESET);
//
//
//
//
////	HAL_GPIO_WritePin(DCH1_GPIO_Port, DCH1_Pin, GPIO_PIN_SET);
////	MBSLL_DelayUs(timer, 1000);
////
////	HAL_GPIO_WritePin(DCH3_GPIO_Port, DCH3_Pin, GPIO_PIN_RESET);
////	MBSLL_DelayUs(timer, 1000);
////
////	HAL_GPIO_WritePin(DCH2_GPIO_Port, DCH2_Pin, GPIO_PIN_SET);
////	MBSLL_DelayUs(timer, 1000);
////
////	HAL_GPIO_WritePin(DCH1_GPIO_Port, DCH1_Pin, GPIO_PIN_RESET);
////	MBSLL_DelayUs(timer, 1000);
////
////	HAL_GPIO_WritePin(DCH3_GPIO_Port, DCH3_Pin, GPIO_PIN_SET);
////	MBSLL_DelayUs(timer, 1000);
////
////	HAL_GPIO_WritePin(DCH2_GPIO_Port, DCH2_Pin, GPIO_PIN_RESET);
////	MBSLL_DelayUs(timer, 1000);
//
//
//
//
//
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel1);
////	while (motorDriver->tim->Instance->CNT < 33);
////
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel2);
////	while (motorDriver->tim->Instance->CNT < 66);
////
////	MBSLL_StartChannelPWM(motorDriver, motorDriver->channel3);
//}
//
///* __________________________________________________________________ */
