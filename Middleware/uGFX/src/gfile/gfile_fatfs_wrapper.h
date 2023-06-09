/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gfile/gfile_fatfs_wrapper.h
 * @brief   GFILE FATFS wrapper.
 *
 */

#ifndef _FATFS_WRAPPER
#define _FATFS_WRAPPER

// Include the fatfs configuration from the local directory not the original source folder
#include "ffconf.h"

// Prevent preprocessor redefinition warnings
#include "integer.h"
#if defined(_T) && !defined(_INC_TCHAR)
	#define _INC_TCHAR
#endif

// Include the fatfs API
#include "ff.h"

// Include the fatfs diskio API
#include "diskio.h"

#endif //_FATFS_WRAPPER
