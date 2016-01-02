/******************************************************************************
Confidential Property of Fork Particle, Inc.
(c) Copyright 2002-2009 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef __frkpevents_h
#define __frkpevents_h

// Event ID declares
#define frkPEVENT_ID_BASE				(1 << 24)
#define frkPEVENT_EMITTER_TRANSFORM		0 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_CREATE		1 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_DESTROY		2 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_PROPERTY		3 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_FORCE_TYPE	4 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_FORCE_POS		5 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_ANM_LOOP		6 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_ANM_RESET  	7 + frkPEVENT_ID_BASE
#define frkPEVENT_EMITTER_ANM_CURFRAME	8 + frkPEVENT_ID_BASE

// Property Event IDs
#define frkPEVENT_PROPERTY_LIFE_MIN			0
#define frkPEVENT_PROPERTY_LIFE_VAR			1
#define frkPEVENT_PROPERTY_VEL_MIN			2
#define frkPEVENT_PROPERTY_VEL_VAR			3
#define frkPEVENT_PROPERTY_ROT_MIN			4
#define frkPEVENT_PROPERTY_ROT_VAR			5
#define frkPEVENT_PROPERTY_ISCALE_MIN		6
#define frkPEVENT_PROPERTY_ISCALE_VAR		7
#define frkPEVENT_PROPERTY_TSCALE_MIN		8
#define frkPEVENT_PROPERTY_TSCALE_VAR		9
#define frkPEVENT_PROPERTY_FSCALE_MIN		10
#define frkPEVENT_PROPERTY_FSCALE_VAR		11
#define frkPEVENT_PROPERTY_SCALE_RATIO		12
#define frkPEVENT_PROPERTY_DRAG				13
#define frkPEVENT_PROPERTY_GRAVITY			14
#define frkPEVENT_PROPERTY_CONERAD_MIN		15
#define frkPEVENT_PROPERTY_CONERAD_VAR		16
#define frkPEVENT_PROPERTY_ERATE			17
#define frkPEVENT_PROPERTY_IALPHA			18
#define frkPEVENT_PROPERTY_TALPHA1			19
#define frkPEVENT_PROPERTY_TALPHA2			20
#define frkPEVENT_PROPERTY_FALPHA			21
#define frkPEVENT_PROPERTY_COLOR_RATIO1		22
#define frkPEVENT_PROPERTY_COLOR_RATIO2		23

#ifdef __cplusplus
extern "C" {
#endif

typedef void		  (*_t_frkPEventEmitterCreateCB) (char *sEmitterName);
typedef void		  (*_t_frkPEventEmitterDestroyCB)(char *sEmitterName);
typedef _t_frkAnmInst* (*_t_frkPEventEmitterAnmInstCB)(char *pData);

extern  int  frkPEventDefaultCB (_t_frkAnmInst* pNoteCBData, _t_frkPNote* pNoteData);
extern  void frkPEventSetPS (_t_frkPSystem *pSystem);
extern  void frkPEventSetEmitterCreateCB (_t_frkPEventEmitterCreateCB  pCB);
extern  void frkPEventSetEmitterDestroyCB(_t_frkPEventEmitterDestroyCB pCB);
extern  void frkPEventSetEmitterAnmInstCB(_t_frkPEventEmitterAnmInstCB pCB);

#ifdef __cplusplus
}
#endif

#endif