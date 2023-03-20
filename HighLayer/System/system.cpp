/** ____________________________________________________________________
 *
 *	@file		system.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "system.h"


RoboticMotherBoardDevice RMB_Pro(	gdispOpenFont("DejaVuSans12_aa"),
									gdispOpenFont("DejaVuSans12_aa"),
									gdispOpenFont("DejaVuSans16_aa"),
									MIX_CHANNELS_TOTAL_NUMBER,
									SYSTEM_FUNCTIONS_TOTAL_NUMBER);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void RoboticMotherBoardDevice::Init (void)
{
	/* General mixers init */
	ParseMixesInitReference(outputFunctionsNumber, outputFunction, mixChannelsNumber, mixChannel);


	/* State machine init */
	osSemaphoreCreate(xSemaphoreCurrentState);
	osSemaphoreGive(xSemaphoreCurrentState);


	/* OS tasks init */
	osTaskCreate(	TaskPeripheralManage,
					"PeripheralManage",
					configMINIMAL_STACK_SIZE * 2,
					NULL,
					OS_HIGHEST_PRIORITY,
					NULL);


	static ui8 mixChannelsNumberTemp = mixChannelsNumber;
	static MixChannel_t* mixChannelTemp = mixChannel;

	osTaskCreate(	[](void *params) { MixesProcess(mixChannelsNumberTemp, mixChannelTemp); },
					"InputProcess",
					configMINIMAL_STACK_SIZE * 3,
					NULL,
					OS_HIGH_PRIORITY,
					NULL);
}


void RoboticMotherBoardDevice::SetCurrentState (RMB_State_t newState)
{
	currentState = newState;
	osSemaphoreGive(xSemaphoreCurrentState);
}


RMB_State_t RoboticMotherBoardDevice::GetCurrentState (void)
{
	if (osSemaphoreTake(xSemaphoreCurrentState, 0) != pdTRUE)
		osSemaphoreTake(xSemaphoreCurrentState, osMaxDelay);

	return currentState;
}


MixChannel_t *RoboticMotherBoardDevice::FindMixFromInput (InputID_t ID)
{
	if (ID == PRPH_NO_INPUT)
		return NULL;

	for (ui8 i = 0; i < HW_NUM_INPUTS; i++)
		if (mixChannel[i].source->GetID() == ID)
			return &mixChannel[i];

	return NULL;
}


void RoboticMotherBoardDevice::SetMixInput (MixChannel_t *mix, InputID_t ID)
{
	if (ID != PRPH_NO_INPUT)
		mix->source = inputClassesArray[ID];

	else
		mix->source = MIX_HAVENO_INPUT;
}


MixChannel_t *RoboticMotherBoardDevice::FindMixFromOutput (SystemFunctionID_t ID)
{
	if (ID == SF_NO)
		return NULL;

	for (ui8 i = 0; i < SYSTEM_FUNCTIONS_TOTAL_NUMBER; i++)
		if (mixChannel[i].target->ID == ID)
			return &mixChannel[i];

	return NULL;
}


void RoboticMotherBoardDevice::SetMixOutput (MixChannel_t *mix, SystemFunctionID_t ID)
{
	if (ID != SF_NO)
	{
		for (ui8 i = 0; i < outputFunctionsNumber; i++)  // Finding associate
			if (outputFunction[i].ID == ID)
				mix->target = &outputFunction[i];
	}

	else
		mix->target = MIX_HAVENO_OUTPUT;
}


ui16 RoboticMotherBoardDevice::GetFunctionValue (SystemFunctionID_t ID)
{
	for (ui8 i = 0; i < outputFunctionsNumber; i++)
		if (outputFunction[i].ID == ID)
			return outputFunction[i].value;

	/* Function haven't found */
	return 0;
}


void RoboticMotherBoardDevice::ProcessFunction (SystemFunctionID_t ID, void *res)
{
	ui16 valueTemp = GetFunctionValue(ID);

	switch (ID)
	{
		case CSF_NAVIGATION_LEFT :
		case CSF_NAVIGATION_ENTER :
		case CSF_NAVIGATION_RIGHT :
			ProcessButton(valueTemp, (ButtonState_t*)res);
			break;

		case CSF_PARAMETER_CHANGE :
			*(ui16*)res = valueTemp;

		default :
			break;
	}
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void ProcessButton (ui16 bValue, ButtonState_t *buttonState)
{
	ButtonState_t bState;

	if (bValue >= 1)
		bState = BS_PRESSED;

	else
		bState = BS_RELEASED;

	if (*buttonState == BS_RELEASED)
		*buttonState = bState;

	else if (((*buttonState == BS_PRESSED) || (*buttonState == BS_LOCKED)) &&
			(bState == BS_RELEASED))
		*buttonState = BS_RELEASED;

	else if ((*buttonState == BS_PRESSED) && (bState == BS_PRESSED))
		*buttonState = BS_LOCKED;
}
