/** ____________________________________________________________________
 *
 *	@file		digitalInput.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_DIGITAL_INPUTS_H_
#define		_DIGITAL_INPUTS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"


typedef enum
{
	DIN_2POS_SWITCH					= 0,
	DIN_3POS_SWITCH

}	DigitalInputType_t;


typedef enum
{
	DINL_DIRECT						= 0,
	DINL_INVERT

}	DigitalInputLogic_t;


class DigitalInput : public Input
{
	private :

		DigitalInputType_t	inType;
		DigitalInputLogic_t	logic;

	public :

		DigitalInput(		DigitalInputType_t	inType,
							DigitalInputLogic_t	logic,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputProcess)
							{
								this->inType		= inType;
								this->logic			= logic;

								this->GPIO_Channel	= GPIO_Channel;
							}

		void				Init (void);

		DigitalInputType_t	GetType (void) { return inType; }
		DigitalInputLogic_t	GetLogic (void) { return logic; }

};


extern DigitalInput LeftButton;
extern DigitalInput CenterButton;
extern DigitalInput RightButton;


void LeftButtonReadValue (void);
void CenterButtonReadValue (void);
void RightButtonReadValue (void);

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _DIGITALINPUTS_H_ */
