/******************************************************************************
Module		: FrkParticleSystem Class
Overview	: The Particle System class holds represents the particle system,
and provides interface to manage the particle system.

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

#include "FrkDataServer.h"
#include "FrkParticleSystem.h"

/******************************************************************************
_Function	:	FrkParticleSystem Constructor
_Description:	Creates an Instance of Particle System
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkParticleSystem::FrkParticleSystem()
{
	m_pSystem = NULL;
}

/******************************************************************************
_Function	:	FrkParticleSystem Destructor
_Description:	Destroys the ParticeSystem Object
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkParticleSystem::~FrkParticleSystem(void)
{
}

/******************************************************************************
Function	:	FrkParticleSystem::EnableASync
Description	:	Enables ASync for the system.
Arguments	:	None.
Return		:	None.
*/
/*****************************************************************************/
void FrkParticleSystem::EnableASync()
{
	frkPSystemASyncEnable(m_pSystem, 1);
}

/******************************************************************************
Function	:	FrkParticleSystem::Update
Description	:	Processes the Particle System for each frame.
Arguments	:	None.
Return		:	None.
*/
/*****************************************************************************/
void FrkParticleSystem::Update(float fTDelta)
{
	frkPSystemProcess (m_pSystem, fTDelta);
#ifdef LIVE_TUNER
	frkTunerProcess();
#endif
	FrkGeomDisplayList::GetInstance()->UnlockVertexBuffer();
	FrkGeomDisplayList::GetInstance()->SetNumVertices(0);
}
/******************************************************************************
Function	:	FrkParticleSystem::UpdateAsnyc
Description	:	Processes the Particle System for each frame.
Arguments	:	None.
Return		:	None.
*/
/*****************************************************************************/
void FrkParticleSystem::UpdateASync(float fTDelta)
{
#ifdef LIVE_TUNER
	frkTunerProcess();
#endif

	frkPSystemProcessASync (m_pSystem, fTDelta);
}
/******************************************************************************
Function	:	FrkParticleSystem::ASyncReady
Description	:	Ensures system processing is finished (from last anync call).
Arguments	:	None.
Return		:	None.
*/
/*****************************************************************************/
void FrkParticleSystem::ASyncReady(float fTDelta)
{
	frkPSystemProcessASyncReady (m_pSystem, fTDelta);
}
/******************************************************************************
Function	:	FrkParticleSystem::CreateParticleSys
Description	:	Creates an Instance of Particle System.
Arguments	:	> sName: Name of the particle system.
				> nMaxParticles: Max particles in the system
Return		:	> Zero if successful, otherwise negative error code.
*/
/*****************************************************************************/
int	FrkParticleSystem::Create(char *sName, int nMaxParticles)
{
	// Create one Fork particle system instance for this sample
	return frkPSystemCreate (&m_pSystem, sName, nMaxParticles);
}

/******************************************************************************
Function	:	FrkParticleSystem::DestroyParticleSys
Description	:	Destroys the Particle System.
Arguments	:	None.
Return		:	> Zero if successful, otherwise negative error code.
*/
/*****************************************************************************/
int	FrkParticleSystem::Destroy()
{
	if (!m_pSystem)
		return -1;

	frkPSystemDestroy (&m_pSystem);
	return 0;
}

