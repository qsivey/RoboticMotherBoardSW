/** ____________________________________________________________________
 *
 * 	@file		hardware.h
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#ifndef		_HARDWARE_H_
#define		_HARDWARE_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"initialConfig.h"


/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*			### Peripheral Inclusion ###		  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#define		HW_USE_DISPLAY			SET_ON

/*  - - - - - User Defined Parameters - - - - - - */
#define		HW_USE_DIGITAL_JOYSTICK			SET_OFF
	#define	HW_NUM_DIGITAL_JOYSTICKS		1

#define		HW_USE_ANALOG_JOYSTICK	SET_OFF
	#define	HW_NUM_ANALOG_JOYSTICKS	0

#define		HW_USE_ABS_ENCODER		SET_OFF
	#define	HW_NUM_ABS_ENCODERS		1

#define		HW_USE_INC_ENCODER		SET_OFF
	#define	HW_NUM_INC_ENCODERS		2

#define		HW_USE_ANALOG_CHANNELS	SET_ON
	#define	HW_NUM_ANALOG_CHANNELS	1

#define		HW_USE_DIGITAL_CHANNELS	SET_ON
	#define	HW_NUM_DIGITAL_CHANNELS	3


/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*			### Low Layer Peripheral ###		  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Common Settings
 */
#define		MCU_HCLK_FREQUENCY		216000000

/*	Note: UART ---> SBGC32 hardware link produce
 *	in the <SBGC32_Driver/driver_STM32.h> file
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   DRV8313 Constants
 */
extern		TIM_HandleTypeDef		htim1;
extern		TIM_HandleTypeDef		htim2;
extern		TIM_HandleTypeDef		htim3;
extern		TIM_HandleTypeDef		htim4;
extern		TIM_HandleTypeDef		htim5;
extern		TIM_HandleTypeDef		htim8;

extern		TIM_HandleTypeDef		htim9;

extern		TIM_HandleTypeDef		htim7;

extern		SPI_HandleTypeDef		qspi6;

#define		__TIMER_STRUCT			TIM_HandleTypeDef *tim

#define		__GPIO_STRUCT			GPIO_TypeDef *gpio

#define		__SPI_STRUCT			SPI_HandleTypeDef *spi

/* - - - - - - - - - - - U5 - - - - - - - - - - - */
#define		MOTOR_1_TIMER			(&htim5)

#define		MOTOR_1_CH_1			TIM_CHANNEL_1
#define		MOTOR_1_CH_2			TIM_CHANNEL_2
#define		MOTOR_1_CH_3			TIM_CHANNEL_3

#define		MOTOR_1_EN_PORT			DRV1_EN_GPIO_Port
#define		MOTOR_1_EN_PIN			DRV1_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - U6 - - - - - - - - - - - */
#define		MOTOR_2_TIMER			(&htim2)

#define		MOTOR_2_CH_1			TIM_CHANNEL_1
#define		MOTOR_2_CH_2			TIM_CHANNEL_3
#define		MOTOR_2_CH_3			TIM_CHANNEL_4

#define		MOTOR_2_EN_PORT			DRV2_EN_GPIO_Port
#define		MOTOR_2_EN_PIN			DRV2_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - U7 - - - - - - - - - - - */
#define		MOTOR_3_TIMER			(&htim3)

#define		MOTOR_3_CH_1			TIM_CHANNEL_1
#define		MOTOR_3_CH_2			TIM_CHANNEL_2
#define		MOTOR_3_CH_3			TIM_CHANNEL_3

#define		MOTOR_3_EN_PORT			DRV3_EN_GPIO_Port
#define		MOTOR_3_EN_PIN			DRV3_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - U8 - - - - - - - - - - - */
#define		MOTOR_4_TIMER			(&htim1)

#define		MOTOR_4_CH_1			TIM_CHANNEL_2
#define		MOTOR_4_CH_2			TIM_CHANNEL_3
#define		MOTOR_4_CH_3			TIM_CHANNEL_4

#define		MOTOR_4_EN_PORT			DRV4_EN_GPIO_Port
#define		MOTOR_4_EN_PIN			DRV4_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - U9 - - - - - - - - - - - */
#define		MOTOR_5_TIMER			(&htim4)

#define		MOTOR_5_CH_1			TIM_CHANNEL_1
#define		MOTOR_5_CH_2			TIM_CHANNEL_2
#define		MOTOR_5_CH_3			TIM_CHANNEL_3

#define		MOTOR_5_EN_PORT			DRV5_EN_GPIO_Port
#define		MOTOR_5_EN_PIN			DRV5_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/*  - - - - - - - - - - U10 - - - - - - - - - - - */
#define		MOTOR_6_TIMER			(&htim8)

#define		MOTOR_6_CH_1			TIM_CHANNEL_1
#define		MOTOR_6_CH_2			TIM_CHANNEL_2
#define		MOTOR_6_CH_3			TIM_CHANNEL_3

#define		MOTOR_6_EN_PORT			DRV6_EN_GPIO_Port
#define		MOTOR_6_EN_PIN			DRV6_EN_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							ST7735 Display Constants
 */
/* LCD SPI GPIO Config -------------------------
 */
/* LCD SPI MOSI pin */
#define	LCD_SPI_MOSI_GPIO_PORT	GPIOG
#define	LCD_SPI_MOSI_PIN		GPIO_PIN_14
#define	LCD_SPI_MOSI_PIN_AF		GPIO_AF5_SPI6

/* LCD SPI MISO pin */
#define	SD_SPI_MISO_GPIO_PORT	GPIOB
#define	SD_SPI_MISO_PIN			GPIO_PIN_4
#define	SD_SPI_MISO_PIN_AF		GPIO_AF8_SPI6

/* LCD SPI SCL pin */
#define	LCD_SPI_SCL_GPIO_PORT	GPIOG
#define	LCD_SPI_SCL_PIN			GPIO_PIN_13
#define	LCD_SPI_SCL_PIN_AF		GPIO_AF5_SPI6

#define	LCD_SPI_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOG_CLK_ENABLE();\
										__HAL_RCC_GPIOB_CLK_ENABLE()

/* LCD SPI Module Config -----------------------
 */
#define	LCD_SPI_NAME			qspi6
#define	LCD_SPI_INSTANCE		SPI6

#define	LCD_SPI_CLOCK_ENABLE	__HAL_RCC_SPI6_CLK_ENABLE()

/* LCD SPI DMA Module Config -------------------
 */
#define	LCD_SPI_TX_DMA_NAME		qdma5_tx_spi6
#define	LCD_SPI_TX_DMA_STREAM	DMA2_Stream5
#define	LCD_SPI_TX_DMA_CHANNEL	DMA_CHANNEL_1

#define LCD_SPI_TX_DMA_CH_IRQN			DMA2_Stream5_IRQn
#define	LCD_SPI_TX_DMA_IRQ_HANDLER		DMA2_Stream5_IRQHandler

#define	LCD_SPI_DMA_CLOCK_ENABLE		__HAL_RCC_DMA2_CLK_ENABLE()

/* LCD Other Pins Config -----------------------
 */
/* LCD SPI CS pin */
#define	LCD_SPI_CS_GPIO_PORT	GPIOG
#define	LCD_SPI_CS_PIN			GPIO_PIN_12

/* LCD SPI DC pin */
#define	LCD_SPI_DC_GPIO_PORT	GPIOG
#define	LCD_SPI_DC_PIN			GPIO_PIN_11

/* LCD SPI RES pin */
#define	LCD_SPI_RES_GPIO_PORT	GPIOG
#define	LCD_SPI_RES_PIN			GPIO_PIN_10

#define	SD_SPI_CS_GPIO_PORT		GPIOC
#define SD_SPI_CS_PIN			GPIO_PIN_0

#define	LCD_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOC_CLK_ENABLE()


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Analog Channels
 */
#if (HW_USE_ANALOG_CHANNELS)
	/* Potentiometer Analog Pin Config -------------
	 */
	#define	POT_ADC_GPIO_PORT		GPIOC
	#define	POT_ADC_PIN				GPIO_PIN_1

	#define	POT_ADC_CHANNEL			ADC_CHANNEL_11

	#define	ADC_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOC_CLK_ENABLE()

	/* ADC Module Config ---------------------------
	 */
	#define	GENERAL_ADC_INSTANCE	ADC1

	#define	GENERAL_ADC_CLOCK_ENABLE		__HAL_RCC_ADC1_CLK_ENABLE()

	/* ADC DMA Module Config -----------------------
	 */
	#define	GENERAL_ADC_DMA_INSTANCE		DMA2
	#define	GENERAL_ADC_DMA_CHANNEL			DMA_CHANNEL_0
	#define	GENERAL_ADC_DMA_STREAM			DMA2_Stream0

	#define GENERAL_ADC_DMA_CH_IRQN			DMA2_Stream0_IRQn
	#define	GENERAL_ADC_DMA_IRQ_HANDLER		DMA2_Stream0_IRQHandler

	#define	GENERAL_ADC_DMA_CLOCK_ENABLE	__HAL_RCC_DMA2_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Digital Channels
 */
#if (HW_USE_DIGITAL_CHANNELS)
	/* Left Button Pin Config ----------------------
	 */
	#define	LEFT_BUT_GPIO_PORT		GPIOF
	#define	LEFT_BUT_PIN			GPIO_PIN_1

	/* Center Button Pin Config --------------------
	 */
	#define	CENTER_BUT_GPIO_PORT	GPIOF
	#define	CENTER_BUT_PIN			GPIO_PIN_0

	/* Right Button Pin Config ---------------------
	 */
	#define	RIGHT_BUT_GPIO_PORT		GPIOF
	#define	RIGHT_BUT_PIN			GPIO_PIN_2


	#define	DIG_CH_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOF_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Other
 */
#define DEBUG_LED_GPIO_Port		GPIOD
#define DEBUG_LED_Pin			GPIO_PIN_7

#define	OC_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOD_CLK_ENABLE()


#define	SD_SPI_MISO_BLOCK_GPIO_PORT		GPIOD
#define SD_SPI_MISO_BLOCK_PIN			GPIO_PIN_11

#define	OC_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOD_CLK_ENABLE()
/*  - - - - - - - - - - - - - - - - - - - - - - - */


/* Service code ------------------------------------
 */
#if (HW_USE_DIGITAL_JOYSTICK == SET_OFF)
	#undef	HW_NUM_DIGITAL_JOYSTICKS
	#define	HW_NUM_DIGITAL_JOYSTICKS		0
#endif

#if (HW_USE_ANALOG_JOYSTICK == SET_OFF)
	#undef	HW_NUM_ANALOG_JOYSTICKS
	#define	HW_NUM_ANALOG_JOYSTICKS	0
#endif

#if (HW_USE_ABS_ENCODER == SET_OFF)
	#undef	HW_NUM_ABS_ENCODERS
	#define	HW_NUM_ABS_ENCODERS		0
#endif

#if (HW_USE_INC_ENCODER == SET_OFF)
	#undef	HW_NUM_INC_ENCODERS
	#define	HW_NUM_INC_ENCODERS		0
#endif

#if (HW_USE_ANALOG_CHANNELS == SET_OFF)
	#undef	HW_NUM_ANALOG_CHANNELS
	#define	HW_NUM_ANALOG_CHANNELS	0
#endif

#if (HW_USE_DIGITAL_CHANNELS == SET_OFF)
	#undef	HW_NUM_DIGITAL_CHANNELS
	#define	HW_NUM_DIGITAL_CHANNELS	0
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *				Global GPIO-Setting Reference Object
 */
/* Peripheral Order Offsets ------------------------
 */
#define		AJOY_XCH_PRPH_OFFSET	0
#define		AJOY_YCH_PRPH_OFFSET	1
#define		AJOY_CH_PRPH_PINS_NUM	1
#define		AJOY_PRPH_PINS_NUM		2

#define		DJOY_XCH_PRPH_OFFSET	(HW_NUM_ANALOG_JOYSTICKS * AJOY_PRPH_PINS_NUM)
#define		DJOY_YCH_PRPH_OFFSET	AJOY_XCH_PRPH_OFFSET + 1
#define		DJOY_CH_PRPH_PINS_NUM	1
#define		DJOY_PRPH_PINS_NUM		2

#define		ABS_ENC_PRPH_OFFSET		(DJOY_XCH_PRPH_OFFSET + (HW_NUM_DIGITAL_JOYSTICKS * DJOY_PRPH_PINS_NUM))
	#define	ABS_ENC_PRPH_PINS_NUM	2

#define		INC_ENC_PRPH_OFFSET		(ABS_ENC_PRPH_OFFSET + (HW_NUM_ABS_ENCODERS * ABS_ENC_PRPH_PINS_NUM))
	#define	INC_ENC_PRPH_PINS_NUM	2

#define		AN_CH_PRPH_OFFSET		(INC_ENC_PRPH_OFFSET + (HW_NUM_INC_ENCODERS * INC_ENC_PRPH_PINS_NUM))
	#define	AN_CH_PRPH_PINS_NUM		1

#define		DIG_CH_PRPH_OFFSET		(AN_CH_PRPH_OFFSET + HW_NUM_ANALOG_CHANNELS)
	#define	DIG_CH_PRPH_PINS_NUM	1


/* General inputs constant that uses in most higher software layers */
#define		HW_NUM_INPUTS			((HW_NUM_ANALOG_JOYSTICKS * AJOY_PRPH_PINS_NUM) +	\
									 (HW_NUM_DIGITAL_JOYSTICKS * DJOY_PRPH_PINS_NUM) +	\
									 (HW_NUM_ABS_ENCODERS) +	\
									 (HW_NUM_INC_ENCODERS) +	\
									 (HW_NUM_ANALOG_CHANNELS) +	\
									 (HW_NUM_DIGITAL_CHANNELS))


typedef struct
{
	ui16			pin;
	GPIO_TypeDef	*port;
	ui8				pinAF;

}	GPIO_Channel_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Functions
 */
static inline void HardwareErrorHandler (void)
{
	__disable_irq();

	while (1)
	{
		/* - - - - Custom Hardware Error Handler - - - - */
		;
		/* - - - - - - - - - - - - - - - - - - - - - - - */
	}
}


static inline void SoftwareErrorHandler (void)
{
	__disable_irq();

	while (1)
	{
		/* - - - - Custom Software Error Handler - - - - */
		;
		/* - - - - - - - - - - - - - - - - - - - - - - - */
	}
}


static inline void AllGPIO_ClockEnable (void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
}


static inline void AllGPIO_ClockDisable (void)
{
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_GPIOH_CLK_DISABLE();
}


static inline void MISO_Enable (void)
{
	HAL_GPIO_WritePin(SD_SPI_MISO_BLOCK_GPIO_PORT, SD_SPI_MISO_BLOCK_PIN, GPIO_PIN_RESET);
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _HARDWARE_H_ */
