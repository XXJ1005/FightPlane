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
#ifndef __DEMOAPP_H__
#define __DEMOAPP_H__

#include "FrkParticleSystem.h"
#include "frksdk.h"
#include "FrkDataServer.h"
#include "FrkGeomDisplayList.h"
#include "FrkParticleSystem.h"
#include "FrkParticleEmitter.h"
#include "frkmath.h"
#include "FrkTrackEvent.h"
#include "FrkForkSDK.h"

class ParticleEffect
{
public:

	ParticleEffect(char *path, char *fileName); // (路径， 文件名)
	~ParticleEffect() {
		ShutDown();
	}
	bool Frame();
	bool ShutDown();

private:

	FrkParticleEffect*   m_pEffect;
	FrkParticleSystem*	m_pPSystem;
	FrkSDK*				m_pSDK;

	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_PrevTime, m_CurTime, m_StartTime;
	float  m_fFrameTDelta ;
};

#endif
