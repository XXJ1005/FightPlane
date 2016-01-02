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
#ifndef FRKPARTICLEEFFECT_H
#define FRKPARTICLEEFFECT_H

#include "frksdk.h"
/************************************************************************/
//	Class:			FrkParticleEffect
//	Description:	Represents the particle effect class used to perform
//					Effect level operations.
/************************************************************************/
#define frkPEFFECT_EMITTERS_MAX 64
#define frkPEFFECT_XREFS_MAX	16

class FrkParticleEffect
{
public:
	// Effect Emitter members
	FrkParticleEmitter*     m_aParticleEmitter[frkPEFFECT_EMITTERS_MAX];
	_t_frkPEmitter    **	m_aEmitter;	
	int						m_nEmitterCount;

	// Effect instance members
	_t_frkPEffect*          m_pEffect;
	_t_frkPEffectInfo *		m_pEffectInfo;

	// Effect XRef members
	FrkParticleEffect**		m_aXRefEffects;
	int						m_nXRefEffect;	
	bool					m_bDestroyed;
	
	// Effect constructor and destructor
	FrkParticleEffect()
	{
		m_aEmitter		= NULL;	
	    m_nEmitterCount = 0;

		m_pEffect		= NULL;
		m_pEffectInfo	= NULL;

		m_aXRefEffects	= NULL;
		m_nXRefEffect	= 0;

		m_bDestroyed = false;
	}

	~FrkParticleEffect(){}

	// Effect creation/destruction Functions
	int Create(char* sName, t_frkMatrix4* pLcsWcs, FrkParticleSystem *pPSystem);
	int Destroy();

private:
	// Parent particle system
	FrkParticleSystem	*m_pParticleSys;

	// XRef Support Functions
	void CreateXRefEffects();
	void DestroyXRefEffects();

	// Misc. Support Functions
	void* LoadEffectInfo(const char* pFileName);

	// Creation function used to create an XRef effect
	int Create(_t_frkPEffect* pPEffect, FrkParticleSystem *pPSystem);

	//Destroy Callback
	static void OnEffectDestroy(_t_frkPEffect* pEffect);
};
#endif