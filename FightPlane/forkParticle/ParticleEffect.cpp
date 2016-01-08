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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ParticleEffect.h"
#include "frkParticleEffect.h"
#include "frkptuner.h"

#ifndef _TIME_H
#define _TIME_H

#endif

/******************************************************************************
Function	:	ParticleEffect::ParticleEffect(char *path, char *fileName)
Description	:	This function initiates the Demo by creating various modules.
Arguments	:	
Return		:	None.
*****************************************************************************/

ParticleEffect::ParticleEffect(char *path, char *fileName){
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_PrevTime);
	m_StartTime = m_CurTime = m_PrevTime;
	m_fFrameTDelta = 0.0f;

	// Initialize Data Server
	FrkDataServer::GetInstance()->Init();
	FrkDataServer::GetInstance()->SetMediaPath(path);

	// Open Fork SDK
	FrkSDKParam sdkParam;
	m_pSDK = new FrkSDK;
	m_pSDK->Create(sdkParam);

	// Create the Fork SDK particle system
	m_pPSystem = new FrkParticleSystem;
	m_pPSystem->Create("ParticleSystem", MAX_PS_PARTICLES);

	// Create particle effect
	m_pEffect = new FrkParticleEffect();

	m_pEffect->Create(fileName, NULL, m_pPSystem);
}

void SetupMatrices()
{
	t_frkVector3 m_vEye;   // Eye Position
	t_frkVector3 m_vLook;  // Look Vector
	t_frkVector3 m_vUp;    // Up Vector
	t_frkVector3 m_vRight; // Right Vector
	t_frkMatrix4 m_view;

	m_vEye.x = 0.0f;
	m_vEye.y = 0.0f;
	m_vEye.z = 0.0f;
	
	m_vLook.x = 0.0f;
	m_vLook.y = 0.0f;
	m_vLook.z = -1.0f;

	m_vUp.x = 0.0f;
	m_vUp.y = 1.0f;
	m_vUp.z = 0.0f;

	m_vRight.x = 1.0f;
	m_vRight.y = 0.0f;
	m_vRight.z = 0.0f;

	MatrixIdentity(&m_view);

	Vec3Normalize(&m_vLook, &m_vLook);

	Vec3Cross(&m_vRight, &m_vLook, &m_vUp);
	Vec3Normalize(&m_vRight, &m_vRight);

	Vec3Cross(&m_vUp, &m_vRight, &m_vLook);
	Vec3Normalize(&m_vUp, &m_vUp);

	m_view.m00 =  m_vRight.x;
	m_view.m01 =  m_vUp.x;
	m_view.m02 = -m_vLook.x;
	m_view.m03 =  0.0f;

	m_view.m10 =  m_vRight.y;
	m_view.m11 =  m_vUp.y;
	m_view.m12 = -m_vLook.y;
	m_view.m13 =  0.0f;

	m_view.m20 =  m_vRight.z;
	m_view.m21 =  m_vUp.z;
	m_view.m22 =  -m_vLook.z;
	m_view.m23 =  0.0f;

	m_view.m30 = -Vec3Dot(&m_vRight, &m_vEye);
	m_view.m31 = -Vec3Dot(&m_vUp, &m_vEye);
	m_view.m32 =  Vec3Dot(&m_vLook, &m_vEye);
	m_view.m33 =  1.0f;

	glMultMatrixf( (GLfloat*)&m_view );
}

/******************************************************************************
Function	:	ParticleEffect::Frame
Description	:	This function is called periodically by the main thread to process
				the particle m_pSystem,	get the particle data and then  render
				the particles on screen
Arguments	:	None.
Return		:	None.
*****************************************************************************/
bool ParticleEffect::Frame(int accurate = 1){

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glMatrixMode(GL_MODELVIEW);

	accurate = accurate > 0 ? accurate : 1;
	double delta = 180.0 / accurate;
	for (int i = 0; i < accurate; i++) {
		glRotatef(delta, 0, 1, 0);

		glPushMatrix();
		SetupMatrices();

		QueryPerformanceCounter(&m_CurTime);

		if (m_pEffect)
		{
			if (m_pEffect->m_nEmitterCount)
			{
				GLuint * pTexture = (GLuint *)frkPAssetGetDataPointer(frkPPropertyGetCurAsset(m_pEffect->m_aParticleEmitter[0]->m_pEmitterInfo));
				if (pTexture)
				{
					glBindTexture(GL_TEXTURE_2D, *pTexture);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				}
			}
		}

		m_pPSystem->Update(m_fFrameTDelta);

		if (m_pEffect && m_pEffect->m_bDestroyed)
		{
			delete m_pEffect;
			m_pEffect = NULL;
		}

		LONGLONG nTCounterDelta = m_CurTime.QuadPart - m_PrevTime.QuadPart;
		m_fFrameTDelta = (float)((double)nTCounterDelta / (double)m_Frequency.QuadPart);

		m_PrevTime = m_CurTime;

		glPopMatrix();
	}
	
	glPopAttrib();

	return true;
}

/******************************************************************************
Function	:	ParticleEffect::ShutDown
Description	:	Clears the Particle System, Graphic Handler and Input Handler
				before closing the Application.
Arguments	:	None.
Return		:	None.
*****************************************************************************/
bool ParticleEffect::ShutDown()
{
	if (m_pEffect)
	{
		m_pEffect->Destroy();
		delete m_pEffect;
		m_pEffect = NULL;
	}

	FrkGeomDisplayList::DestroyInstance();

	m_pPSystem->Destroy();
	m_pSDK->Destroy();
	delete m_pPSystem;
	delete m_pSDK;
	FrkDataServer::DestroyInstance();

	return true;
}


