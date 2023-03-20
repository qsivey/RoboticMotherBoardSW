/** ____________________________________________________________________
 *
 *	@file		inputs.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INPUTS_H_
#define		_INPUTS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"

#define		NO_PROCESS_FUNC			NULL

#define		IN_MIN_VALUE			0U
#define		IN_MIDDLE_VALUE			32768U
#define		IN_MAX_VALUE			65535U

#define		VALUE_MP_14B_TO_16B		4U


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Common Input Objects
 */
extern const GPIO_Channel_t GPIO_ReferenceArray [];


typedef enum
{
	IN_ON,
	IN_NEED_INIT,
	IN_NEED_DEINIT,
	IN_OFF

}	InputState_t;


/*	Note:	This is only auxiliary peripheral enumeration
 *			Needs for manual mixers initialization
 *
 *			It must have elements order like an inputClassesArray []
 */
typedef enum
{
	PRPH_LEFT_BUTTON				= 0,
	PRPH_RIGHT_BUTTON,
	PRPH_CENTER_BUTTON,
	PRPH_POTENTIOMETER,

	PRPH_NO_INPUT					= 255

}	PeripheralReferenceOrder_t, InputID_t;


typedef void		(*InputProcess_t)(void);


typedef class Input
{
	private :

		ui16				value;
		InputID_t			ID;
		InputState_t		state;

	public :

		const GPIO_Channel_t
							*GPIO_Channel;

		IRQn_Type			IRQn;

		InputProcess_t		InputProcess;

		Input(				InputID_t ID,
							ui8 pinsNum,
							InputProcess_t InputProcess)
							{
								this->ID		= ID;
								state			= IN_OFF;

								GPIO_Channel	= (GPIO_Channel_t*)__Malloc(sizeof(GPIO_Channel_t) * pinsNum);

								this->InputProcess = InputProcess;
							}

		virtual void		Init (void) { ; }

		void				SetValue (ui16 value) { this->value = value; }
		ui16				GetValue (void) { return value; }

		InputID_t			GetID (void) { return ID; }
		InputID_t			*GetAddressID (void) { return &ID; }

		void				SetState (InputState_t state) { this->state = state; }
		InputState_t		GetState (void) { return state; }

}		Input_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Functions
 */
static inline ui16 ConvertValue14_BitTo16_Bit (ui16 value)
{
	return (value * VALUE_MP_14B_TO_16B);
}


static inline ui16 ConvertValue1_BitTo16_Bit (ui16 value)
{
	return (value ? IN_MAX_VALUE : IN_MIN_VALUE);
}


static inline ui16 ConvertValueBiniry16_FlagToDecade (ui16 flag)
{
	for (ui8 i = 0; i < 16; i++)
	{
		if (flag == 1)
			return i;

		flag >>= 1;
	}

	return 0;
}


static inline i32 SignedCeil (float value)
{
	return (value > 0) ? (ceil(value)) : -(ceil(abs(value)));
}


static inline i32 FilterDeltaValue (ui16 oldValue, ui16 newValue, ui16 revError, ui16 hysteresis, float divider)
{
	i32 delta = newValue - oldValue;

	if ((abs(delta) <= revError) || (abs(delta) > hysteresis))
		return 0;

	else
		return (((abs(delta) / divider) > 1.0F) ? (delta / divider) : ((delta > 0) ? 1 : -1));
}


static inline ui16 CalculateAverage (ui16 *buff, ui16 averagePow, ui16 newValue)
{
	ui32 resTemp;

	for (ui16 i = 0; i < averagePow - 1; i++)
	{
		buff[i] = buff[i + 1];
		resTemp += buff[i];
	}

	buff[averagePow - 1] = newValue;

	return (resTemp + newValue) / averagePow;
}

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _INPUTS_H_ */
