/** ____________________________________________________________________
 *
 *	@file		digitalInput.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "digitalInput.h"


DigitalInput LeftButton(		DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_LEFT_BUTTON,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET],
								DIG_CH_PRPH_PINS_NUM,
								LeftButtonReadValue);

DigitalInput CenterButton(		DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_RIGHT_BUTTON,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 1],
								DIG_CH_PRPH_PINS_NUM,
								CenterButtonReadValue);

DigitalInput RightButton(		DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_CENTER_BUTTON,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 2],
								DIG_CH_PRPH_PINS_NUM,
								RightButtonReadValue);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void DigitalInput::Init (void)
{
	DIG_CH_GPIO_CLOCK_ENABLE;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_PULLUP;
	GPIO_InitStruct.Pin		= GPIO_Channel->pin;
	HAL_GPIO_Init(GPIO_Channel->port, &GPIO_InitStruct);

	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
static ui16 DigitalInputReadValueUni (const GPIO_Channel_t *GPIO_Channel, DigitalInputType_t digitalInputType, DigitalInputLogic_t logic)
{
	if (digitalInputType == DIN_2POS_SWITCH)
		return (HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin) ^ logic);

	else if (digitalInputType == DIN_3POS_SWITCH)
	{
		ui8 val;
		ui32 temp;
		ui16 offset;

		val = HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin);

		offset = (ConvertValueBiniry16_FlagToDecade(GPIO_Channel->pin) * 2);
		temp = GPIO_Channel->port->PUPDR;
		temp &= ~(GPIO_PUPDR_PUPDR0 << offset);
		temp |= ((GPIO_PULLDOWN) << offset);
		GPIO_Channel->port->PUPDR = temp;

		for (ui8 i = 0; i < 200; i++) __NOP();

		if (val == HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin))
			val = ((val ^ logic) ? 2 : 0);

		else  // Middle position
			val = 1;

		temp = GPIO_Channel->port->PUPDR;
		temp &= ~(GPIO_PUPDR_PUPDR0 << offset);
		temp |= ((GPIO_PULLUP) << offset);
		GPIO_Channel->port->PUPDR = temp;

		return val;
	}

	else
		return 0;
}


void LeftButtonReadValue (void)
{
	LeftButton.SetValue(DigitalInputReadValueUni(LeftButton.GPIO_Channel, LeftButton.GetType(), LeftButton.GetLogic()));
}


void CenterButtonReadValue (void)
{
	CenterButton.SetValue(DigitalInputReadValueUni(CenterButton.GPIO_Channel, CenterButton.GetType(), CenterButton.GetLogic()));
}


void RightButtonReadValue (void)
{
	RightButton.SetValue(DigitalInputReadValueUni(RightButton.GPIO_Channel, RightButton.GetType(), RightButton.GetLogic()));
}
