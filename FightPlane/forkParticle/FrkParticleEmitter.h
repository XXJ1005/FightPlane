/******************************************************************************
Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/	
/*****************************************************************************/
#pragma once
#ifndef FRKPARTICLEEMITTER_H
#define FRKPARTICLEEMITTER_H

// Maximum value of integer
#define MAX_INT 65535
#define MAX_EMITTER_PARTICLES 25000

#include "frksdk.h"
#include "frkmath.h"

class FrkEmitterShape;
class FrkParticleEffect;
class FrkChunkEmitters;
class FrkParticleSystem;
/************************************************************************/
//	Class:			FrkParticleEmitter
//	Description:	Represents the particle emitter class used to perform
//					Emitter level operations.
/************************************************************************/
class FrkParticleEmitter
{
public:
	_t_frkPEmitter *		m_pEmitter;	
	_t_frkPEmitterInfo*		m_pEmitterInfo;
	_t_frkAnmInst*			m_pAnimationInstance;
	_t_frkAnmTrk*			m_pTrk;
	FrkEmitterShape*		m_pEmitterShape;
	int						nForces;
	
	// Parent Particle System
	FrkParticleSystem*		m_pParticleSys;
	// Parent Effect
	FrkParticleEffect	   *m_pParticleEffect;
	// Emitter constructor and destructor
	FrkParticleEmitter();
	~FrkParticleEmitter();
	// Emitter Construction/Destruction Functions
	int Create(_t_frkPEmitter* pEmitter ,  t_frkMatrix4* pLcsWcs, FrkParticleSystem	*pPSystem);
	int Destroy();

	// Live Tuner Callback. 
	static void OnTunerCallBack ( char* sName, _t_frkPEmitterInfo* pPSB, _t_frkPEmitter* pEmitter, int nSize, void* pUsrData);
	
	// Emitter Callback functions
	static void OnEmitterProcess(_t_frkPEmitter* pEmit, float fTDelta);
	static void OnEmitterDestroy(_t_frkPEmitter* pEmit);
	static int OnSuperEmitCB(_t_frkPEmitter** pEmitter, void** pAnmTrack, _t_frkPSystem** pSystem,
							char* sRefEmitterName, t_frkMatrix4* pLcsWcs, _t_frkPEmitterInfo* pInfo, _t_frkPEmitter* pSEmitter);
	static void OnEmitShaderCB(_t_frkPEmitter* pEmitter, float fTDelta);

private:

	void LoadEmitterAnimationAssets(_t_frkAnmTrk* animationTrack);
	void LoadEmitterAssets( _t_frkPEmitterInfo* emitterInfo );
	// Geometry/Rendering Support Functions
	static int SetFacing(_t_frkPEmitter* pEmitter);
	static void ParticleSubmit(_t_frkPEmitter* pEmit);
	static int SetAlpha(int nBlendMode);
	void Draw();
	void InitPixelShader();
	// Class Cleanup Function
	int Cleanup();
};

#endif
