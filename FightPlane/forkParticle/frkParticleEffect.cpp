/******************************************************************************
Module		: FrkParticleEffect Class
Overview	: The ParticleEffect class is an abstract class . 
It provides an interface for a general Effect. Effect with specific characteristics can be
derived from this class.


Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/

// ForkParticle Header Files
#include "frksdk.h"

#ifdef LIVE_TUNER
#include "frkptuner.h"
#endif

#include "FrkParticleSystem.h"
#include "FrkDataServer.h"
#include "FrkTrackEvent.h"
#include "FrkParticleEffect.h"
#include "FrkParticleEmitter.h"

/******************************************************************************
_Function	 :	FrkParticleEffect::Create(
_Description :	Creates and effect from the specified file.
_Arguments	 :	> sName    : Name of the Effect PSB file
			    > pLcsWcs  : Initial local to world emitter matrix or NULL for identity.
				> pPSystem : Parent particle system 
_Return		 :	Status: -1 if not able to fill particle data else 0.
*/
/*****************************************************************************/
int FrkParticleEffect::Create(char* sName, t_frkMatrix4* pLcsWcs, FrkParticleSystem *pPSystem)
{
	if (!pPSystem)
		return -1;

	m_pParticleSys = pPSystem;

	LoadEffectInfo(sName);
	frkPEffectCreate(&m_pEffect, sName, m_pEffectInfo, pLcsWcs);
	frkPEffectGetEmitters(m_pEffect , &m_nEmitterCount, &m_aEmitter);	
	 _t_frkPEmitterInfo* pEmitterInfo = NULL;
	for( int i = 0; i < m_nEmitterCount; i++ )
	{
		m_aParticleEmitter[i] = NULL;
       pEmitterInfo =  frkPEmitterGetPropertyInfo(m_aEmitter[i]);
		if(*frkPPropertyFlagPtr(pEmitterInfo) & frkPSYSTEM_PROPERTYBIT_REFEMITTER )
			continue;
		
		m_aParticleEmitter[i] = new FrkParticleEmitter();
		m_aParticleEmitter[i]->Create( m_aEmitter[i] , pLcsWcs, m_pParticleSys);
		m_aParticleEmitter[i]->m_pParticleEffect = this;
	}	
	
	// Create Effect XRef
	CreateXRefEffects();

	//register created effect with particle system
	frkPEffectReg(m_pEffect , m_pParticleSys->m_pSystem);
	frkPEffectRestart(m_pEffect);

	//set effect callbacks
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EPROCESS   , FrkParticleEmitter::OnEmitterProcess);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EREFPROCESS, FrkParticleEmitter::OnEmitterProcess);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EREFDESTROY, FrkParticleEmitter::OnEmitterDestroy);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_SUPEREMITCB, FrkParticleEmitter::OnSuperEmitCB);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EFFECTDESTROY, FrkParticleEffect::OnEffectDestroy);
	frkPEffectAnmSetNoteCB(m_pEffect, FrkTrackEvent::EventNoteCB);
	frkPEffectSetUserData (m_pEffect, this);
	
	return 0;
}

int FrkParticleEffect::Create(_t_frkPEffect* pPEffect, FrkParticleSystem *pPSystem)
{
	if (!pPSystem || !pPEffect)
		return -1;

	m_pParticleSys = pPSystem;
	m_pEffect = pPEffect;
	m_pEffectInfo = frkPEffectGetEffectInfo(pPEffect);


	frkPEffectGetEmitters(m_pEffect , &m_nEmitterCount, &m_aEmitter);	
	
	_t_frkPEmitterInfo* pEmitterInfo = NULL;
	for( int i = 0; i < m_nEmitterCount; i++ )
	{
		m_aParticleEmitter[i] = NULL;
       pEmitterInfo =  frkPEmitterGetPropertyInfo(m_aEmitter[i]);
		if(*frkPPropertyFlagPtr(pEmitterInfo) & frkPSYSTEM_PROPERTYBIT_REFEMITTER )
			continue;
		
		m_aParticleEmitter[i] = new FrkParticleEmitter();
		m_aParticleEmitter[i]->Create( m_aEmitter[i] , NULL, m_pParticleSys);
		m_aParticleEmitter[i]->m_pParticleEffect = this;
	}	
	
	//set effect callbacks
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EPROCESS   , FrkParticleEmitter::OnEmitterProcess);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EREFPROCESS, FrkParticleEmitter::OnEmitterProcess);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EREFDESTROY, FrkParticleEmitter::OnEmitterDestroy);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_SUPEREMITCB, FrkParticleEmitter::OnSuperEmitCB);
	frkPEffectSetCallback (m_pEffect, ePSYSTEM_CB_EFFECTDESTROY, FrkParticleEffect::OnEffectDestroy);
	frkPEffectAnmSetNoteCB(m_pEffect, FrkTrackEvent::EventNoteCB);
	frkPEffectSetUserData (m_pEffect, this);

	return 0;
}

/******************************************************************************
_Function	:	FrkParticleEmitter::Destroy
_Description	:	Destroys an effect instance and frees associated resources.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
int FrkParticleEffect::Destroy()
{
	if(m_nXRefEffect > 0)
		DestroyXRefEffects();

	frkPEffectUnReg(m_pEffect , (_t_frkPSystem *)m_pParticleSys->m_pSystem);
	frkPEffectDestroy(&m_pEffect);

	if (FrkDataServer::GetInstance()->DestroyEffectInfo(&m_pEffectInfo))
		frkPEffectInfoDestroy(&m_pEffectInfo);

	for( int i = 0; i < m_nEmitterCount; i++)
	{
		if(m_aParticleEmitter[i])
		{
			m_aParticleEmitter[i]->Destroy();
			delete m_aParticleEmitter[i];
			m_aParticleEmitter[i] = NULL;
		}
	}
	m_aEmitter = NULL;

	return 0;
}
/******************************************************************************/
void FrkParticleEffect::DestroyXRefEffects()
{
	FrkParticleEffect *pEffect = NULL;

	//destroy XRef effects
	for(int i = 0; i < m_nXRefEffect; i++)
	{
		//m_aXRefEffects[i]->Destroy();
		pEffect = m_aXRefEffects[i];
		m_aXRefEffects[i] = NULL;

		for( int j = 0; j < pEffect->m_nEmitterCount; j++)
		{
			if(pEffect->m_aParticleEmitter[j])
			{
				pEffect->m_aParticleEmitter[j]->Destroy();
				delete pEffect->m_aParticleEmitter[j];
				pEffect->m_aParticleEmitter[j] = NULL;
			}
		}

		FrkDataServer::GetInstance()->DestroyEffectInfo(&pEffect->m_pEffectInfo);

		delete pEffect;
	}
	
	if(m_nXRefEffect > 0)
		delete [] m_aXRefEffects;
}

/******************************************************************************
_Function	:	FrkParticleEmitter::LoadEffectInfo
_Description	:	Loads the effect description for the emitter.
_Arguments	:	> pFilename: Filename of PSB file containing the effect description.
_Return		:	None.
*/
/*****************************************************************************/
void* FrkParticleEffect::LoadEffectInfo(const char* pFileName)
{
	// Load emitter description from disc if not found in Data Server Database
	void *pPSB;
	
	bool bStatus = FrkDataServer::GetInstance()->LoadPSBPackage(pFileName, &pPSB, &m_pEffectInfo );

	// Case: Effect found
	if (bStatus == true)
		return m_pEffectInfo;

	// Case: Prepare the effect
	if (pPSB)
	{
		frkPSBPrepare(pPSB);
        frkPSBAssociateAssets(pPSB, FrkDataServer::GetInstance()->UserLoadAssetCB, NULL);	
		frkPEffectInfoCreate(&m_pEffectInfo, pPSB );
		FrkDataServer::GetInstance()->SetEffectInfo(pFileName, m_pEffectInfo);

		int nXRefEffects;
		char **aXRefName = NULL;
		void *pXRefPSB = NULL;
		_t_frkPEffectInfo *pEffectInfo = NULL;	

		frkPEffectInfoGetXRefName(m_pEffectInfo, &nXRefEffects, &aXRefName);

		for (int i=0; i<nXRefEffects; i++)
		{
			bStatus = FrkDataServer::GetInstance()->LoadPSBPackage(aXRefName[i], &pXRefPSB, &pEffectInfo);

			if (!pXRefPSB)
				exit(0);
			
			if (!bStatus) // if not already loaded.. fix psb and create effect info
			{
				frkPSBPrepare(pXRefPSB);
				frkPSBAssociateAssets(pXRefPSB, FrkDataServer::GetInstance()->UserLoadAssetCB, NULL);	
				frkPEffectInfoCreate(&pEffectInfo, pXRefPSB );
				FrkDataServer::GetInstance()->SetEffectInfo(aXRefName[i], pEffectInfo);
			}

			frkPEffectInfoAddXRefInfo(m_pEffectInfo, pEffectInfo);
		}

		return m_pEffectInfo;
	}

	// Case: All failed
	return NULL;
}


void FrkParticleEffect::CreateXRefEffects()
{
	_t_frkPEffect **aXRefEffect = NULL;

	frkPEffectGetXRefEffects(m_pEffect, &m_nXRefEffect, &aXRefEffect);

	if(!m_nXRefEffect)
		return;

	m_aXRefEffects = new FrkParticleEffect*[m_nXRefEffect];

	int nStatus = 0;
	for ( int i = 0 ; i < m_nXRefEffect; i++)
	{
		m_aXRefEffects[i] = new FrkParticleEffect();
		nStatus = m_aXRefEffects[i]->Create(aXRefEffect[i], m_pParticleSys );
		if (nStatus < 0)
		{
			::MessageBox(NULL, "Unable to create XRef assets.", "DemoApp", MB_OK);
			exit(0);
		}
	}
}

void FrkParticleEffect::OnEffectDestroy(_t_frkPEffect* pEffect)
{
	FrkParticleEffect *pParticleEffect = NULL;
	frkPEffectGetUserData(pEffect, (void **) &pParticleEffect);

	if(pParticleEffect)
	{
		pParticleEffect->m_bDestroyed = true;
	}
}
