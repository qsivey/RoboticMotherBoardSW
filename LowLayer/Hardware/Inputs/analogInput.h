/** ____________________________________________________________________
 *
 *	@file		analogInput.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_ANALOGINPUTS_H_
#define		_ANALOGINPUTS_H_

#include	"inputs.h"

/*  = = = = = = = = = = = = = = = = = = = = = = = */


typedef enum
{
	ADC_INIT_FINISHED				= 0,
	ADC_DEINITED

}	ADC_InitState_t;


class AnalogInput : public Input
{
	private :

		ui32				analogChannel;

	public :

		/* Driver */
		static ADC_HandleTypeDef
							hadc;

		static ADC_TypeDef
							*instance;

		static DMA_HandleTypeDef
							hdma;

		static DMA_Stream_TypeDef
							*DMA_Stream;

		static ui32			DMA_Channel;

		static ADC_InitState_t
							initFlag;

		/* Other */
		static ui8			channelsNum;
		static ui16			*anValue;

		AnalogInput(		ui32 analogChannel,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputProcess)
							{
								this->analogChannel	= analogChannel;

								this->GPIO_Channel	= GPIO_Channel;
							}

		void				Init (void);

		ui32				GetAnalogChannel (void) { return analogChannel; }

};

extern AnalogInput Potentiometer;


void Potentiometer_ReadValue (void);


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _ANALOGINPUTS_H_ */
