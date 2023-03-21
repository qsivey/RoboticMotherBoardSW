/** ____________________________________________________________________
 *
 * 	@file		main.cpp
 *
 *	@author		qsivey
 *
 *	VK / TG:	@qsivey
 *	mail:		qsivey@gmail.com
 *
 *	K-Lab		Laboratory of robotics and mechatronics
 *	____________________________________________________________________
 */

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "string.h"
#include "gfx.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "hardware.h"

char UserPath [4];   /* USER logical drive path */
extern Diskio_drvTypeDef UserDriver [];


void SystemClock_Config(void);
static void MPU_Config(void);


static gdispImage PowerImage [19];

void PictureTest (void *params)
{
	gCoord width, height;

	gfxInit();

	FATFS_LinkDriver(UserDriver, UserPath);
	__DelayMs(500);

	width = gdispGetWidth();
	height = gdispGetHeight();

	char imagePath [20];

	while (1)
	{
		for (ui8 i = 0; i < 19; i++)
		{
			sprintf(imagePath, "power%d.bmp", i + 1);

			gdispImageOpenFile(&PowerImage[i], imagePath);
			gdispImageCache(&PowerImage[i]);
			gdispImageDraw(&PowerImage[i], 0, 0, width, height, 0, 0);
			gdispImageClose(&PowerImage[i]);
		}
	}
}


int main (void)
{
	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
	/*                         Initialization                         */
	/* ______________________________________________________________ */

	MPU_Config();
	HAL_Init();
	SystemClock_Config();

	/* Demo task */
	xTaskCreate(PictureTest, "Test", configMINIMAL_STACK_SIZE * 10, NULL, OS_MEDIUM_PRIORITY, NULL);

	/* FreeRTOS start */
	vTaskStartScheduler();

	while (1);
}


void HAL_MspInit (void)
{
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
//	  HardwareErrorHandler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
//	  HardwareErrorHandler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
//	  HardwareErrorHandler();
  }
}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}


#if (PROJ_USE_FREERTOS)

	HAL_StatusTypeDef HAL_InitTick (ui32 TickPriority)
	{
		unused_(TickPriority);

		return HAL_OK;
	}


	ui32 HAL_GetTick (void)
	{
		return __GetTick;
	}


	void HAL_Delay (__IO ui32 Delay)
	{
		__DelayMs(Delay);
	}

#endif
