/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef		_GDISP_LLD_BOARD_H
#define		_GDISP_LLD_BOARD_H

#include	"ST7735.h"
#include	<stdbool.h>
#include	"hardware.h"

#define		DELAY					0x80

#define		__CustomDelay(x)		for (ui32 i = 0; i < x; i++) __NOP();

/* Processor delay for slowly ST7735 drivers */
#define		__CustomDelayDisplayTiming		/* __CustomDelay(5) */


#pragma		GCC diagnostic ignored	"-Wmisleading-indentation"


volatile bool SPI_TxDMA_TC_Flag = true;

static DMA_HandleTypeDef LCD_SPI_TX_DMA_NAME;
SPI_HandleTypeDef LCD_SPI_NAME;
TIM_HandleTypeDef LCD_TIM_NAME;


void LCD_SPI_TX_DMA_IRQ_HANDLER (void)
{
	HAL_DMA_IRQHandler(&LCD_SPI_TX_DMA_NAME);
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SPI_TxDMA_TC_Flag = 1;
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	HardwareErrorHandler();
}


// call before initializing any SPI devices
void ST7735_Unselect();
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);


static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      ST7735_ROTATION,        //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

#if (defined(ST7735_IS_128X128) || defined(ST7735_IS_160X128))
  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127
#endif // ST7735_IS_128X128

#ifdef ST7735_IS_160X80
  init_cmds2[] = {            // Init for 7735S, part 2 (160x80 display)
    3,                        //  3 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x4F,             //     XEND = 79
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F ,            //     XEND = 159
    ST7735_INVON, 0 },        //  3: Invert colors
#endif

  init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Gamma Adjustments (pos. polarity), 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Gamma Adjustments (neg. polarity), 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay



static void __SPI_Transmit (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	HAL_SPI_Transmit(hspi, pData, Size, 100);
}


static void __SPI_Transmit_DMA (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	/* Required condition for some controllers */
	ATOMIC_SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCL);

	SPI_TxDMA_TC_Flag = false;
	HAL_SPI_Transmit_DMA(hspi, pData, Size);

	while (!SPI_TxDMA_TC_Flag);

	/* Return to 8-bit */
	ATOMIC_CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_CRCL);
}


static void ST7735_Select (void)
{
	HAL_GPIO_WritePin(SD_SPI_CS_GPIO_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);

    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

    __CustomDelayDisplayTiming;
}

void ST7735_Unselect (void)
{
    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);

    __CustomDelayDisplayTiming;
}


static void ST7735_Reset (void)
{
    HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET);
    __DelayMs(5);
    HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_SET);
    __DelayMs(5);
}

static void ST7735_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);
    __CustomDelayDisplayTiming;

    __SPI_Transmit(&LCD_SPI_NAME, &cmd, 1);
    __CustomDelayDisplayTiming;
}

static void ST7735_WriteData(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
    __CustomDelayDisplayTiming;

    __SPI_Transmit(&LCD_SPI_NAME, buff, buff_size);
    __CustomDelayDisplayTiming;
}

static void ST7735_ExecuteCommandList(const uint8_t *addr) {
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        ST7735_WriteCommand(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            ST7735_WriteData((uint8_t*)addr, numArgs);
            addr += numArgs;
        }

        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            __DelayMs(ms);
        }
    }
}

static void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    // column address set
    ST7735_WriteCommand(ST7735_CASET);
    uint8_t data[] = { 0x00, x0 + ST7735_XSTART, 0x00, x1 + ST7735_XSTART };
    ST7735_WriteData(data, sizeof(data));

    // row address set
    ST7735_WriteCommand(ST7735_RASET);
    data[1] = y0 + ST7735_YSTART;
    data[3] = y1 + ST7735_YSTART;
    ST7735_WriteData(data, sizeof(data));

    // write to RAM
    ST7735_WriteCommand(ST7735_RAMWR);
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;

    ST7735_Select();

    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7735_WriteData(data, sizeof(data));

    ST7735_Unselect();
}


void ST7735_FillRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	ST7735_Select();
	ST7735_SetAddressWindow(x, y, x + w-1, y + h - 1);

	uint8_t data [] = { color >> 8, color & 0xFF };

	HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET);
	__CustomDelayDisplayTiming;

	__SPI_Transmit_DMA(&LCD_SPI_NAME, data, w * h * 2);

	ST7735_Unselect();
}


void ST7735_BlitRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data)
{
    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x + w - 1, y + h - 1);

    HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET);
    __CustomDelayDisplayTiming;

    /* Reverting halfwords */
    uint16_t *pDataTemp = (uint16_t*)data;

    for (uint16_t i = 0; i < h * w; i++)
    	pDataTemp[i] = __REV16((uint16_t)pDataTemp[i]);


    /* SPI Boost */
    ATOMIC_CLEAR_BIT(LCD_SPI_NAME.Instance->CR1, SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2);
    LCD_SPI_TX_DMA_NAME.Init.MemInc = DMA_MINC_ENABLE;
    if (HAL_DMA_Init(&LCD_SPI_TX_DMA_NAME) != HAL_OK)
		HardwareErrorHandler();

	__SPI_Transmit_DMA(&LCD_SPI_NAME, (ui8*)pDataTemp, w * h * 2);

	/* Return to normal speed */
	ATOMIC_SET_BIT(LCD_SPI_NAME.Instance->CR1, SPI_CR1_BR_0);
    LCD_SPI_TX_DMA_NAME.Init.MemInc = DMA_MINC_DISABLE;
    if (HAL_DMA_Init(&LCD_SPI_TX_DMA_NAME) != HAL_OK)
		HardwareErrorHandler();

    ST7735_Unselect();
}

void ST7735_SetBacklight (uint16_t val)
{
	//LCD_TIM_INSTANCE->CCR1 = 1000 - (pow(val, 3) / 1000);
}

void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) return;
    if((y + h - 1) >= ST7735_HEIGHT) return;

    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    ST7735_WriteData((uint8_t*)data, sizeof(uint16_t)*w*h);
    ST7735_Unselect();
}


static GFXINLINE void init_board ()
{
	LCD_SPI_GPIO_CLOCK_ENABLE;

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* SPI GPIO Initializing */
	GPIO_InitStruct.Pin			= LCD_SPI_MOSI_PIN;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate	= LCD_SPI_MOSI_PIN_AF;
	HAL_GPIO_Init(LCD_SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= SD_SPI_MISO_PIN;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate	= SD_SPI_MISO_PIN_AF;
	HAL_GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= LCD_SPI_SCL_PIN;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate	= LCD_SPI_SCL_PIN_AF;
	HAL_GPIO_Init(LCD_SPI_SCL_GPIO_PORT, &GPIO_InitStruct);


	LCD_SPI_CLOCK_ENABLE;

	/* SPI parameter configuration */
	LCD_SPI_NAME.Instance = LCD_SPI_INSTANCE;

	LCD_SPI_NAME.Init.Mode				= SPI_MODE_MASTER;
	LCD_SPI_NAME.Init.Direction			= SPI_DIRECTION_2LINES;
	LCD_SPI_NAME.Init.DataSize			= SPI_DATASIZE_8BIT;
	LCD_SPI_NAME.Init.CLKPolarity		= SPI_POLARITY_LOW;
	LCD_SPI_NAME.Init.CLKPhase			= SPI_PHASE_1EDGE;
	LCD_SPI_NAME.Init.NSS				= SPI_NSS_SOFT;
	LCD_SPI_NAME.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_4;
	LCD_SPI_NAME.Init.FirstBit			= SPI_FIRSTBIT_MSB;
	LCD_SPI_NAME.Init.TIMode			= SPI_TIMODE_DISABLE;
	LCD_SPI_NAME.Init.CRCCalculation	= SPI_CRCCALCULATION_DISABLE;
	LCD_SPI_NAME.Init.CRCPolynomial		= 7;
	LCD_SPI_NAME.Init.CRCLength			= SPI_CRC_LENGTH_DATASIZE;
	LCD_SPI_NAME.Init.NSSPMode			= SPI_NSS_PULSE_ENABLE;

	if (HAL_SPI_Init(&LCD_SPI_NAME) != HAL_OK)
	{
		HardwareErrorHandler();
	}


	LCD_GPIO_CLOCK_ENABLE;

	GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin			= SD_SPI_CS_PIN;
	HAL_GPIO_Init(SD_SPI_CS_GPIO_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(SD_SPI_CS_GPIO_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);

	GPIO_InitStruct.Pin			= LCD_SPI_CS_PIN;
	HAL_GPIO_Init(LCD_SPI_CS_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= LCD_SPI_DC_PIN;
	HAL_GPIO_Init(LCD_SPI_DC_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= LCD_SPI_RES_PIN;
	HAL_GPIO_Init(LCD_SPI_RES_GPIO_PORT, &GPIO_InitStruct);

    /* Enable DMAx clock */
    LCD_SPI_DMA_CLOCK_ENABLE;

    LCD_SPI_TX_DMA_NAME.Instance = LCD_SPI_TX_DMA_STREAM;

    LCD_SPI_TX_DMA_NAME.Init.Channel				= LCD_SPI_TX_DMA_CHANNEL;
    LCD_SPI_TX_DMA_NAME.Init.Direction				= DMA_MEMORY_TO_PERIPH;
    LCD_SPI_TX_DMA_NAME.Init.PeriphInc				= DMA_PINC_DISABLE;
    LCD_SPI_TX_DMA_NAME.Init.MemInc					= DMA_MINC_DISABLE;
    LCD_SPI_TX_DMA_NAME.Init.PeriphDataAlignment	= DMA_PDATAALIGN_HALFWORD;
    LCD_SPI_TX_DMA_NAME.Init.MemDataAlignment		= DMA_MDATAALIGN_HALFWORD;
    LCD_SPI_TX_DMA_NAME.Init.Mode					= DMA_NORMAL;
    LCD_SPI_TX_DMA_NAME.Init.Priority				= DMA_PRIORITY_HIGH;
    LCD_SPI_TX_DMA_NAME.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;

	if (HAL_DMA_Init(&LCD_SPI_TX_DMA_NAME) != HAL_OK)
	{
		HardwareErrorHandler();
	}

	__HAL_LINKDMA(&LCD_SPI_NAME, hdmatx, LCD_SPI_TX_DMA_NAME);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(LCD_SPI_TX_DMA_CH_IRQN, 2, 0);
    HAL_NVIC_EnableIRQ(LCD_SPI_TX_DMA_CH_IRQN);

	ST7735_Select();
	ST7735_Reset();
	ST7735_ExecuteCommandList(init_cmds1);
	ST7735_ExecuteCommandList(init_cmds2);
	ST7735_ExecuteCommandList(init_cmds3);
	ST7735_Unselect();
}


static GFXINLINE void post_init_board(GDisplay *g) {
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
	(void) state;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void write_cmd(GDisplay *g, gU8 cmd) {
	(void) g;
    ST7735_Select();
    ST7735_WriteCommand(cmd);
    ST7735_Unselect();
}

static GFXINLINE void write_data(GDisplay *g, gU8* data, gU16 length) {
	(void) g;
	(void) data;
	(void) length;
}


#endif /* _GDISP_LLD_BOARD_H */


