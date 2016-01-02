/******************************************************************************
Module		: FrkSDK Class
Overview	: The SDK class represents the Fork SDK, and provides interface 
			  to manage the SDK.

Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#include <frksdk.h>
#include "FrkForkSDK.h"
#include "FrkParticleSystem.h"
#include "FrkParticleEmitter.h"

#ifdef LIVE_TUNER
#include "frkptuner.h"
#endif

FrkSDK::FrkSDK() : m_nMemSize(0), m_pSDKHeap(NULL), m_pSDK(NULL)
{}

FrkSDK::~FrkSDK()
{
	if (!m_pSDK || !m_pSDKHeap)
		Destroy();
}

int	FrkSDK::Create(const FrkSDKParam &param)
{
	//	Open Fork SDK
	int nMemSize = 0;

	frkMemSetAlign(16);
	frkSDKPrep(param.m_nMaxParticleSys, 
			   param.m_nMaxEmitters, 
			   param.m_nMaxParticles, 
			   param.m_nMaxEffects, 
			   param.m_nMaxPSBAssets, 
			   &nMemSize);

	int nMemBuffers = 0;

	frkSDKPrepPBuffers(param.m_nMaxBuffers, param.m_nMaxEmitters, param.m_nMaxParticles, &nMemBuffers);

	nMemSize += nMemBuffers;
	if (!nMemSize)
		return -1;

#ifdef LIVE_TUNER
	int nTunerMemSize = 0;
	frkSDKPrepTuner(param.m_nMaxTunerPackets, &nTunerMemSize);
	nMemSize += nTunerMemSize;
#endif

	//nMemSize += 1024 * 1024;

	m_pSDKHeap = malloc(nMemSize);

	if(frkSDKOpen (m_pSDKHeap, nMemSize) != 0)
		return -1;

	m_pSDK = frkSDKGet();
	m_nMemSize = nMemSize;

	// Open the live tuner 
	// Note - Port number should match that in Particle Studio Prefs
#ifdef LIVE_TUNER
	int status = frkTunerOpen  (12345);
	if (status < 0)
		return -1;
	frkTunerRegCallBack ( FrkParticleEmitter::OnTunerCallBack, NULL );
#endif

	return 0;
}

int	FrkSDK::Destroy()
{
	if (!m_pSDK || !m_pSDKHeap)
		return -1;

#ifdef LIVE_TUNER
	frkTunerClose();
#endif

	frkSDKClose ();
	free(m_pSDKHeap);

	m_pSDK	   = NULL;
	m_pSDKHeap = NULL;
	m_nMemSize = 0;

	return 0;
}