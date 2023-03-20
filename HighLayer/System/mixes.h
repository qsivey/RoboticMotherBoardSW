/** ____________________________________________________________________
 *
 *	@file		mixes.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_MIXES_H_
#define		_MIXES_H_

/* Low layer glue library */
#include	"inputsGeneral.h"

#include	"projectConfig.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
#define		MIN_MIX_OFFSET			-65535
#define		DEFAULT_MIX_OFFSET		0
#define		MAX_MIX_OFFSET			65535

#define		MIN_MIX_MPL				1
#define		DEFAULT_MIX_MPL			1
#define		MAX_MIX_MPL				65535

#define		MIN_MIX_AVERAGE			1
#define		MAX_MIX_AVERAGE			10

#define		MIX_HAVENO_INPUT		NULL
#define		MIX_HAVENO_OUTPUT		NULL


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											 Objects
 */
typedef enum
{
	CSF_NAVIGATION_ENTER			= 0,
	CSF_NAVIGATION_LEFT,
	CSF_NAVIGATION_RIGHT,
	CSF_PARAMETER_CHANGE,

	/* Always here */
	SYSTEM_FUNCTIONS_TOTAL_NUMBER,

	SF_NO							= 255

}	SystemFunctionID_t;


typedef struct
{
	SystemFunctionID_t	ID;

	ui16				value;

}	SystemFunction_t;


typedef enum
{
	MIX_CHANNEL_0					= 0,
	MIX_CHANNEL_1,
	MIX_CHANNEL_2,
	MIX_CHANNEL_3,
	MIX_CHANNEL_4,
	MIX_CHANNEL_5,
	MIX_CHANNEL_6,
	MIX_CHANNEL_7,
	MIX_CHANNEL_8,
	MIX_CHANNEL_9,
	MIX_CHANNEL_10,
	MIX_CHANNEL_11,
	MIX_CHANNEL_12,
	MIX_CHANNEL_13,
	MIX_CHANNEL_14,
	MIX_CHANNEL_15,

	/* Always last */
	MIX_CHANNELS_TOTAL_NUMBER

}	MixChannelNum_t;


typedef enum
{
	MIX_CHANNEL_ON					= 0,
	MIX_CHANNEL_OFF

}	MixChannelState_t;


typedef enum
{
	MIX_CHANNEL_DIRECT				= 0,
	MIX_CHANNEL_INVERTED

}	MixChannelInvert_t;


typedef struct
{
	MixChannelNum_t		number;
	MixChannelState_t	state;

	Input_t				*source;
	SystemFunction_t	*target;

	ui16				value,
						min,
						max;

	i32					offset;
	float				multiplier;
	MixChannelInvert_t	inversion;
	ui8					average;

}	MixChannel_t;


typedef struct
{
	PeripheralReferenceOrder_t	in;
	MixChannelNum_t				mix;
	SystemFunctionID_t			out;

}	MixersInitReference_t;


typedef struct
{
	MixChannelNum_t		mix;

	ui16				min,
						max;

	i32					offset;
	float				multiplier;
	MixChannelInvert_t	inversion;
	ui8					average;

}	MixersCoefficientsInitReference_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void ParseMixesInitReference (ui8 outputFunctionsNumber, SystemFunction_t *systemFunction,
							  ui8 mixChannelsNumber, MixChannel_t *mixChannel);
void MixesProcess (ui8 mixChannelsNumber, MixChannel_t *mixChannel);

#endif		/* _MIXES_H_ */
