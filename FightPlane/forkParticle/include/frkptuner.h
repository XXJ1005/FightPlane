/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2009 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef _frkptuner_h
#define _frkptuner_h

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef void ( *t_frkTunerCB) (char* sName, _t_frkPEmitterInfo* pPSB, 
								_t_frkPEmitter* pEmitter, int nSize, void* pUserData);

typedef void ( *t_frkTunerEffectCB) (char* sName, void* pPSB, _t_frkPEffect* pEmitter, 
								int nSize, void* pUserData);

/*****************************************************************************/
// System API
extern int	frkTunerOpen (int nServerPort);
extern void frkTunerClose ();
extern void frkTunerProcess ();

// Callback API
extern void frkTunerRegCallBack (t_frkTunerCB pCB, void* pDataCB);
extern void frkTunerUnRegCallBack (void);

extern void frkTunerRegEffectCallBack (t_frkTunerEffectCB pCB, void* pDataCB);
extern void frkTunerUnRegEffectCallBack (void);

// Emitter API
extern int frkTunerRegEmitter (char* sUniqueKey, _t_frkPEmitter* pEmitter);
extern int frkTunerUnRegEmitter (_t_frkPEmitter* pEmitter);

// Effect API
extern int frkTunerRegEffect (char* sUniqueKey, _t_frkPEffect* pEffect);
extern int frkTunerUnRegEffect (_t_frkPEffect* pEffect);

// Update data callback
extern int _frkTunerUpdateData (char* sName, void* pTuneData, int nSize);
extern void frkTunerEnableEffectMode(int bEffectMode);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif

