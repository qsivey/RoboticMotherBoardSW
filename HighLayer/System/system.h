/** ____________________________________________________________________
 *
 *	@file		system.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_SYSTEM_H_
#define		_SYSTEM_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"projectConfig.h"

#include	"gfx.h"
#include	"mixes.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											 Objects
 */
typedef enum
{
	BS_RELEASED						= 0,
	BS_PRESSED						= 1,

	BS_LOCKED						= 2

}	ButtonState_t;


typedef enum
{
	ND_CENTER						= 0,			// No action

	ND_UP							= 0x01,
	ND_DOWN							= 0x02,
	ND_RIGHT						= 0x04,
	ND_LEFT							= 0x08,

	ND_UP_RIGHT						= (ND_UP | ND_RIGHT),
	ND_DOWN_RIGHT					= (ND_DOWN | ND_RIGHT),
	ND_DOWN_LEFT					= (ND_DOWN | ND_LEFT),
	ND_UP_LEFT						= (ND_UP | ND_LEFT),

	ND_CONTINUOUS					= 0x40,
	ND_LOCKED						= 0x80,

	ND_COMPLEX_MASK					= (ND_CONTINUOUS | ND_LOCKED)

}	NavigationDirection_t;


typedef struct
{
	font_t	smallFont,
			mediumFont,
			largeFont;

	ui16	brightness;

}	SystemGUI_t;


typedef enum
{

}	RMB_State_t;


class RoboticMotherBoardDevice
{
	private :

		/* System */
		NavigationDirection_t
							navDirection;

		/* GUI */
		SystemGUI_t			GUI;

		/* State machine */
		RMB_State_t			currentState;

	public :

		/* Mixes */
		ui8					mixChannelsNumber;
		MixChannel_t		*mixChannel;

		/* Outputs */
		ui8					outputFunctionsNumber;
		SystemFunction_t	*outputFunction;

		/* State machine */
		xSemaphoreHandle	xSemaphoreCurrentState;

		xSemaphoreHandle	xSemaphoreInputProcess;


		RoboticMotherBoardDevice(
							font_t smallFont,
							font_t mediumFont,
							font_t largeFont,
							ui8 mixChannelsNumber,
							ui8 outputFunctionsNumber)
							{
								GUI.smallFont				= smallFont;
								GUI.mediumFont				= mediumFont;
								GUI.largeFont				= largeFont;

								this->mixChannelsNumber		= mixChannelsNumber;
								this->outputFunctionsNumber	= outputFunctionsNumber;

								this->mixChannel			= (MixChannel_t*)osMalloc(sizeof(MixChannel_t) * mixChannelsNumber);
								this->outputFunction		= (SystemFunction_t*)osMalloc(sizeof(SystemFunction_t) * outputFunctionsNumber);
							}

		void				Init (void);

		void				SetCurrentState (RMB_State_t newState);
		RMB_State_t			GetCurrentState (void);

		MixChannel_t		*FindMixFromInput (InputID_t ID);
		void				SetMixInput (MixChannel_t *mix, InputID_t ID);

		MixChannel_t		*FindMixFromOutput (SystemFunctionID_t ID);
		void				SetMixOutput (MixChannel_t *mix, SystemFunctionID_t ID);

		ui16				GetFunctionValue (SystemFunctionID_t ID);
		void				ProcessFunction (SystemFunctionID_t ID, void *res);

		void				ProcessNavigationDirection (void);

		/* Getters */
		NavigationDirection_t
							GetNavigationDirection (void) { return navDirection; }

		font_t				GetSmallFont (void) { return GUI.smallFont; }
		font_t				GetMediumFont (void) { return GUI.mediumFont; }
		font_t				GetLargeFont (void) { return GUI.largeFont; }
		ui16				GetBrightness (void) { return GUI.brightness; }
		ui16				*GetAddressBrightness (void) { return &GUI.brightness; }

		/* Setters */
		void				SetBrightness (ui16 brightness) { GUI.brightness = brightness; }

};

extern RoboticMotherBoardDevice RMB_Pro;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Functions Prototypes
 */
/* Free functions prototypes */
void ProcessButton (ui16 bValue, ButtonState_t *buttonState);

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _SYSTEM_H_ */
