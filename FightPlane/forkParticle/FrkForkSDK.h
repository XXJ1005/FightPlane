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
#ifndef _FrkSDK_H
#define _FrkSDK_H

#define MAX_PARTICLE_SYS	1
#define MAX_SDK_EMITTERS	256
#define	MAX_SDK_PARTICLES	16*1024
#define	MAX_TUNER_PACKETS	64
#define MAX_SDK_EFFECTS		256
#define MAX_SDK_PSBASSETS	256
#define MAX_SDK_BUFFERS		0

struct FrkSDKParam
{
	int m_nMaxParticleSys;
	int m_nMaxEmitters;
	int m_nMaxParticles;
	int m_nMaxEffects;
	int m_nMaxPSBAssets;
	int m_nMaxTunerPackets;
	int m_nMaxBuffers;

	FrkSDKParam() :
	m_nMaxParticleSys(MAX_PARTICLE_SYS),
	m_nMaxEmitters(MAX_SDK_EMITTERS),
	m_nMaxParticles(MAX_SDK_PARTICLES),
	m_nMaxEffects(MAX_TUNER_PACKETS),
	m_nMaxPSBAssets(MAX_SDK_EFFECTS),
	m_nMaxTunerPackets(MAX_SDK_PSBASSETS),
	m_nMaxBuffers(MAX_SDK_BUFFERS)
	{}
};

class FrkSDK
{
public:
	FrkSDK();
	~FrkSDK();

	int	Create(const FrkSDKParam &param);	
	int	Destroy();

	int			 m_nMemSize;
	void		*m_pSDKHeap;
	_t_frkSDK	*m_pSDK;
};


#endif