#ifndef GDHELPERS_H
#define GDHELPERS_H

/*===========================================================================
   Copyright (c) 2013 Qualcomm Technologies, Inc.       
   All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/sse/qsee/SecureDisplay/libgd/include/gdhelpers.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
07/02/13   ts       Initial version.

===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	/* sys/types.h is needed for size_t on Sparc-SunOS-4.1 */
#if !defined(_WIN32) && !defined(__ARMCC)
#include <sys/types.h>
#else
#include <stdlib.h>
#endif /* _WIN32_WCE */


#ifndef SECURE_UI_SUPPORTED

	/* TBB: strtok_r is not universal; provide an implementation of it. */

	char * gd_strtok_r (char *s, char *sep, char **state);

	/* These functions wrap memory management. gdFree is
		in gd.h, where callers can utilize it to correctly
		free memory allocated by these functions with the
		right version of free(). */
	void *gdCalloc (size_t nmemb, size_t size);
	void *gdMalloc (size_t size);
	void *gdRealloc (void *ptr, size_t size);

#endif

	/* Returns nonzero if multiplying the two quantities will
		result in integer overflow. Also returns nonzero if
		either quantity is negative. By Phil Knirsch based on
		netpbm fixes by Alan Cox. */

	int overflow2(int a, int b);

	/* 2.0.16: portable mutex support for thread safety. */

#if defined(_WIN32)
	/* 2.0.18: must include windows.h to get CRITICAL_SECTION. */
# include <windows.h>
# define gdMutexDeclare(x) CRITICAL_SECTION x
# define gdMutexSetup(x) InitializeCriticalSection(&x)
# define gdMutexShutdown(x) DeleteCriticalSection(&x)
# define gdMutexLock(x) EnterCriticalSection(&x)
# define gdMutexUnlock(x) LeaveCriticalSection(&x)
#elif defined(HAVE_PTHREAD)
# include <pthread.h>
# define gdMutexDeclare(x) pthread_mutex_t x
# define gdMutexSetup(x) pthread_mutex_init(&x, 0)
# define gdMutexShutdown(x) pthread_mutex_destroy(&x)
# define gdMutexLock(x) pthread_mutex_lock(&x)
# define gdMutexUnlock(x) pthread_mutex_unlock(&x)
#else
# define gdMutexDeclare(x)
# define gdMutexSetup(x)
# define gdMutexShutdown(x)
# define gdMutexLock(x)
# define gdMutexUnlock(x)
#endif /* _WIN32 || HAVE_PTHREAD */

#define DPCM2DPI(dpcm) (unsigned int)((dpcm)*2.54 + 0.5)
#define DPM2DPI(dpm)   (unsigned int)((dpm)*0.0254 + 0.5)
#define DPI2DPCM(dpi)  (unsigned int)((dpi)/2.54 + 0.5)
#define DPI2DPM(dpi)   (unsigned int)((dpi)/0.0254 + 0.5)

#ifdef __cplusplus
}
#endif 

#endif /* GDHELPERS_H */
