/** ____________________________________________________________________
 *
 *	@file		mixes.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "mixes.h"


static const MixersInitReference_t MixersInitReferenceArray [] =
	/*
	||		 	   INPUT -->	    	 ||  --> MIXER -->  ||	   		--> OUTPUT			||
	 */
	{ {	PRPH_LEFT_BUTTON,					MIX_CHANNEL_0,		CSF_NAVIGATION_LEFT
	},{	PRPH_CENTER_BUTTON,					MIX_CHANNEL_1,		CSF_NAVIGATION_ENTER
	},{	PRPH_LEFT_BUTTON,					MIX_CHANNEL_2,		CSF_NAVIGATION_RIGHT
	},{	PRPH_POTENTIOMETER,					MIX_CHANNEL_3,		CSF_PARAMETER_CHANGE
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_4,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_5,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_6,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_7,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_8,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_9,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_10,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_11,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_12,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_13,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_14,		SF_NO
	},{	PRPH_NO_INPUT,						MIX_CHANNEL_15,		SF_NO

	}};


static const MixersCoefficientsInitReference_t MixersCoefficientsInitReferenceArray [] =
	/*
	||		MIXER		||	     MIN	  ||	  MAX	  ||		OFFSET		||	  MULTUPLIER  	||		 INVERSION		||		AVERAGE		||
	 */
	{ {	MIX_CHANNEL_0,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_1,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_2,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_3,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_4,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_5,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_6,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_7,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_8,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_9,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_10,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_11,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_12,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_13,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_14,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE
	},{	MIX_CHANNEL_15,		IN_MIN_VALUE,	IN_MAX_VALUE,	DEFAULT_MIX_OFFSET,		DEFAULT_MIX_MPL,	MIX_CHANNEL_DIRECT,		MIN_MIX_AVERAGE

	}};


void ParseMixesInitReference (ui8 outputFunctionsNumber, SystemFunction_t *systemFunction,
							  ui8 mixChannelsNumber, MixChannel_t *mixChannel)
{
	/* Outputs init */
	for (ui8 i = 0; i < outputFunctionsNumber; i++)
	{
		systemFunction[i].value = 0;
		systemFunction[i].ID = (SystemFunctionID_t)i;
	}

	/* Mixers init */
	for (ui8 i = 0; i < mixChannelsNumber; i++)
	{
		mixChannel[i].number = MixersInitReferenceArray[i].mix;

		/* Inputs */
		if (MixersInitReferenceArray[i].in != PRPH_NO_INPUT)
			mixChannel[i].source = inputClassesArray[(ui8)MixersInitReferenceArray[i].in];

		else
			mixChannel[i].source = MIX_HAVENO_INPUT;

		/* Outputs */
		if (MixersInitReferenceArray[i].out != SF_NO)
			mixChannel[i].target = &systemFunction[(ui8)MixersInitReferenceArray[i].out];

		else
			mixChannel[i].target = MIX_HAVENO_OUTPUT;

		mixChannel[i].value = 0;
		mixChannel[i].min = MixersCoefficientsInitReferenceArray[i].min;
		mixChannel[i].max = MixersCoefficientsInitReferenceArray[i].max;

		/* Common */
		mixChannel[MixersInitReferenceArray[i].mix].state = MIX_CHANNEL_ON;

		if (MixersInitReferenceArray[i].in != PRPH_NO_INPUT)
			mixChannel[MixersInitReferenceArray[i].mix].source->SetState(IN_NEED_INIT);

		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].offset = MixersCoefficientsInitReferenceArray[i].offset;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].multiplier = MixersCoefficientsInitReferenceArray[i].multiplier;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].inversion = MixersCoefficientsInitReferenceArray[i].inversion;
		mixChannel[MixersCoefficientsInitReferenceArray[i].mix].average = MixersCoefficientsInitReferenceArray[i].average;
	}
}


void MixesProcess (ui8 mixChannelsNumber, MixChannel_t *mixChannel)
{
	#if (TASK_MIXES_POLLING)

		while (1)
		{

	#endif

			for (ui8 i = 0; i < mixChannelsNumber; i++)
			{
				if ((mixChannel[i].source != MIX_HAVENO_INPUT) && (mixChannel[i].target != MIX_HAVENO_OUTPUT))
				{
					/* Averaging */
					if (mixChannel[i].average > 1)
					{
						ui32 averageTemp = 0;

						for (ui8 k = 1; k < mixChannel[i].average; k++)
						{
							/* Fault defense */
							if (mixChannel[i].source->InputProcess != NO_PROCESS_FUNC)
								mixChannel[i].source->InputProcess();

							averageTemp += mixChannel[i].source->GetValue();
						}

						mixChannel[i].value = averageTemp / mixChannel[i].average;
					}

					else
					{
						if (mixChannel[i].source->InputProcess != NO_PROCESS_FUNC)
							mixChannel[i].source->InputProcess();

						mixChannel[i].value = mixChannel[i].source->GetValue();
					}

					/* Writing */
					if (mixChannel[i].target->ID != SF_NO)
					{
						if (mixChannel[i].inversion == MIX_CHANNEL_DIRECT)
						{
							mixChannel[i].target->value =
							constrain_(((mixChannel[i].value * mixChannel[i].multiplier)
							+ mixChannel[i].offset), mixChannel[i].min, mixChannel[i].max);
						}

						else
						{
							mixChannel[i].target->value =
							mixChannel[i].max - constrain_(((mixChannel[i].value * mixChannel[i].multiplier)
							+ mixChannel[i].offset), mixChannel[i].min, mixChannel[i].max);
						}
					}
				}
			}

	#if (TASK_MIXES_POLLING)

			omDelayMs(MIX_POLLING_TIME);

		}

	#endif
}
