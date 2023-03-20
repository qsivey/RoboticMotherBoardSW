/** ____________________________________________________________________
 *
 *	@file		projectConfig.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PROJECT_CONFIG_H_
#define		_PROJECT_CONFIG_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"initialConfig.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   System Config
 */
#define		NAVIGATION_FILTER		4U				// 3 Min --> 10 Max

#define		NAVIGATION_CONTINUOUS_PASS_TIME	500		// Units: ms


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Mixers Config
 */
#define		TASK_MIXES_POLLING		SET_ON			// SET_OFF: manual calling | SET_ON: task manager handle
	#define	MIX_POLLING_TIME		20				// Units: ms
	#define	omDelayMs(ms)			__DelayMs(ms)	// Mixers processing delay function

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PROJECT_CONFIG_H_ */
