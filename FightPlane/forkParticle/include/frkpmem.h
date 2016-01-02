/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef _frkpmem_h
#define _frkpmem_h

#ifdef __cplusplus
extern "C" {
#endif


typedef void* (*_t_frkMemAllocCB)(unsigned int nSize, unsigned char* pData);
typedef void  (*_t_frkMemFreeCB) (void* pMem);

typedef struct _t_frkmemallocator
{
	_t_frkMemAllocCB	pAllocCB;
	_t_frkMemFreeCB		pFreeCB;
}_t_frkMemAllocator;

enum e_frkMemSlot
{
	eMEMSLOT_PEFFECTINFO = 0,
	eMEMSLOT_PEFFECT,
	eMEMSLOT_PEMITTER,

	eMEMSLOT_MAX
};

#ifdef __cplusplus
}
#endif
#endif

