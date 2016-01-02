/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef _forksdk_h
#define _forksdk_h

#include <stdlib.h>
#include "frkpmath.h"
#include "frkpsystem.h"
#include "frkpanm.h"
#include "frkpmem.h"

#ifdef __cplusplus
extern "C" {
#endif

#define frkSDK_MEMCB_PEFFECTINFO	0x00000001
#define frkSDK_MEMCB_PEFFECT		0x00000002
#define frkSDK_MEMCB_PEMITTER		0x00000004

/*****************************************************************************/
extern void frkSDKPrepPBuffers(int nMaxBuffers, int nMaxEmitters, int nMaxParticles, int* pHeapSize);
extern void frkSDKPrepTuner(int nMaxTunerPackets, int* pHeapSize);
extern void	frkSDKPrep (int nMaxPSystems, int nMaxEmitters, int nMaxParticles, int nMaxEffects, int nMaxPSBAssets, int* pHeapSize);

extern int	frkSDKOpen (void* pMem, int nMemSize);
extern void frkSDKClose (void);
extern _t_frkSDK* frkSDKGet(void);
extern void frkSDKSet(_t_frkSDK* pSDK);

extern void frkMemSetAlign (int nAlignSize);
//extern void frkMemTest();
extern int frkMemSetCallback(_t_frkMemAllocCB pAllocCB, _t_frkMemFreeCB pFreeCB, int nFlags);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif


