/******************************************************************************
Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#pragma once
#ifndef FRKPARTICLESYSTEM_H
#define FRKPARTICLESYSTEM_H

#include "frksdk.h"
#include "FrkGeomDisplayList.h"

#define MAX_PARTICLE_SYS	1
#define MAX_PS_EMITTERS		256
#define	MAX_PS_PARTICLES	8*1024
#define	MAX_TUNER_PACKETS	64

#define FrkFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FrkNonTexFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)

/************************************************************************/
//	Class:			FrkParticleSystem
//	Description:	Holds the Particle System.
/************************************************************************/
class FrkParticleSystem
{
public:
	_t_frkPSystem* m_pSystem;

	// Class constructor and destructor
	FrkParticleSystem();
	~FrkParticleSystem();

	// virtual Interface fucntions
	virtual void EnableASync();
	virtual void Update(float fTDelta);
	virtual void UpdateASync(float fTDelta);
	virtual void ASyncReady(float fTDelta);

	// creation/destruction functions
	int Create(char *sName, int nMaxParticles);
	int	Destroy();
 };

#endif