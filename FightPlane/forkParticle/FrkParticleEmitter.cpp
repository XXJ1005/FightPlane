/******************************************************************************
Module		: FrkParticleEmitter Class
Overview	: The ParticleEmitter class is an abstract class . 
It provides an interface for a general emitter. Emitters with specific characteristics can be
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

#include <windows.h>
#include "gl/gl.h"
#include "gl/glext.h"
// ForkParticle Header Files
#include "frksdk.h"
#include "frkpsystem.h"

#ifdef LIVE_TUNER
#include "frkptuner.h"
#endif

#include "FrkParticleSystem.h"
#include "FrkGeomDisplayList.h"
#include "FrkEmitterShape.h"
#include "FrkEmitterDiamond.h"
#include "FrkEmitterRectangle.h"
#include "FrkEmitterTriangle.h"
#include "FrkEmitterString.h"
#include "FrkEmitterPoint.h"
#include "FrkDataServer.h"
#include "FrkParticleEmitter.h"
#include "FrkGraphicsHandler.h"
#include "frkParticleEffect.h"

/******************************************************************************
// SECTION: EMITTER CLASS METHODS USED WITH PARTICLE EFFECT
/*****************************************************************************/
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
extern PFNGLBLENDEQUATIONPROC    glBlendEquation;

/******************************************************************************
_Function	:	FrkParticleEmitter Constructor
_Description:	Initializes the class members.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkParticleEmitter::FrkParticleEmitter()
{
	m_pEmitterInfo = NULL;				
	m_pEmitter = NULL;
	m_pAnimationInstance = NULL;
	m_pEmitterShape = NULL;
	//m_pParticleSys = NULL;
	m_pTrk = NULL;
	nForces = 0;
}
/******************************************************************************
_Function	:	FrkParticleEmitter Destructor
_Description:	Destroys the emitter.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkParticleEmitter::~FrkParticleEmitter()
{
 	if(m_pEmitterShape)
 		delete m_pEmitterShape;

	m_pEmitter = NULL;
	m_pEmitterInfo = NULL;	
	m_pAnimationInstance = NULL;
	m_pEmitterShape = NULL;
	m_pTrk = NULL;
	nForces = 0;
}
/******************************************************************************
_Function	:	CreateEmitter
_Description:	Creates emitter for use with Effect.
_Arguments	:	> pEmitter : Emitter pointer
				> pLcsWcs  : Initial local to world emitter matrix or NULL for identity.
				> pPSystem : Parent particle system 
_Return		:	Zero if successful, otherwise -1.
*/
/*****************************************************************************/
int FrkParticleEmitter::Create(_t_frkPEmitter* pEmitter ,  t_frkMatrix4* pLcsWcs, FrkParticleSystem* pPSystem)
{
	m_pEmitter = pEmitter;
	m_pEmitterInfo =   frkPEmitterGetPropertyInfo(pEmitter);
	m_pParticleSys = pPSystem;
	
	// Create EmitterShape type instance to process geometry data.
	_t_frkAssetInfo* pAsset = (_t_frkAssetInfo*)((frkPPropertyCurAssetPtr (m_pEmitterInfo) ) );
	int nType = frkPAssetGetType(pAsset);

	if(nType == ePSYSTEM_ASSETTYPE_MODEL)
	{
		
	}
	else
	{
		// Get Particle Shape from Emitter Info
		int nShape = frkPPropertyGetShape(m_pEmitterInfo);

		if(nShape == ePSYSTEM_PARTICLESHAPE_DIAMOND)
			m_pEmitterShape = new FrkEmitterDiamond();
		else if(nShape == ePSYSTEM_PARTICLESHAPE_RECTANGLE)
			m_pEmitterShape = new FrkEmitterRectangle();
		else if(nShape == ePSYSTEM_PARTICLESHAPE_STRING)
			m_pEmitterShape = new FrkEmitterString();
		else if(nShape == ePSYSTEM_PARTICLESHAPE_TRIANGLE)
			m_pEmitterShape = new FrkEmitterTriangle();
		else 
			m_pEmitterShape = new FrkEmitterPoint();
	}

	if(!m_pEmitterShape){
		Cleanup();
		return -1;
	}
	InitPixelShader();
	int nStatus = SetAlpha(*frkPPropertyBlendPtr(frkPEmitterGetPropertyInfo(m_pEmitter)));
	if(nStatus == -1)
	{
		Cleanup();
		return -1;
	}
	#ifdef LIVE_TUNER
	if( !( *frkPEmitterFlagPtr(m_pEmitter) & frkPSYSTEM_EMITTERSTATE_EMITTED) ) 
		FrkDataServer::GetInstance()->DataServerLoadTunerInfo( frkPEmitterNamePtr(m_pEmitter), m_pEmitterInfo );

	// Register Emitter with Live Tuner for update from Particle Studio.
	frkTunerRegEmitter(frkPEmitterNamePtr(m_pEmitter), m_pEmitter);
	#endif
	frkPEmitterSetUserData(m_pEmitter, (void *)this);
	return 0;
}
/******************************************************************************
_Function	:	FrkParticleEmitter::OnEmitterProcess
_Description:	Callback for processing the emitter simulation on each frame.
_Arguments	:	> pEmitter: Pointer to the particle emitter.
				> fTDelta: The time delta.
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::OnEmitterProcess(_t_frkPEmitter* pEmitter, float fTDelta)
{
	FrkParticleEmitter *pParticleEmitter = NULL, **pTmpParticleEmitter = NULL;
	pTmpParticleEmitter	= (FrkParticleEmitter**)frkPEmitterUserDataPtr(pEmitter);
	pParticleEmitter = *pTmpParticleEmitter;

	if(pParticleEmitter)
	{
		if(pParticleEmitter->m_pAnimationInstance != NULL)
			frkPAnmProcess(pParticleEmitter->m_pAnimationInstance, fTDelta);

		pParticleEmitter->SetFacing(pEmitter);
		frkPEmitterProcess (pEmitter, fTDelta);
		ParticleSubmit(pEmitter);
		pParticleEmitter->Draw();
		FrkGeomDisplayList::GetInstance()->SetNumVertices(0);
	}
}
/*******************************************************************************
_Function	:	FrkParticleEmitter::ParticleSubmit
_Description	:	User defined callback for submitting particle data to the renderer.
_Arguments	:	> pEmitter: Pointer to the particle emitter.
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::ParticleSubmit(_t_frkPEmitter* pEmitter)
{
	FrkParticleEmitter *pParticleEmitter = NULL, **pTmpParticleEmitter = NULL;
	pTmpParticleEmitter	= (FrkParticleEmitter**)frkPEmitterUserDataPtr(pEmitter);
	pParticleEmitter = *pTmpParticleEmitter;
	_t_frkPEmitterInfo* pInfo = (_t_frkPEmitterInfo*)(*(frkPEmitterInfoPtr(pEmitter)));
	_t_frkAssetInfo*  pAsset = NULL;
	_t_frkParticle* pParticle = NULL;

	frkPEmitterParticleResetTracer(pEmitter);
	while ((pParticle = frkPEmitterParticleGetTracerItem (pEmitter)) != NULL)
	{
		frkPEmitterParticleIncTracer(pEmitter);

		pAsset = (_t_frkAssetInfo*)frkParticleAssetPtr(pParticle, pInfo);

		int nType = frkPAssetGetType(pAsset);

		static void* pAssetCache = NULL;
		
		if (*(frkPPropertyNumAssetsPtr (pInfo)) &&
			*(frkPPropertyFlagPtr(pInfo)) & (frkPSYSTEM_PROPERTYBIT_PANIMRANDOM | frkPSYSTEM_PROPERTYBIT_PANIMFLIPBOOK)) {

				pParticleEmitter->m_pEmitterShape->SubmitShape(pEmitter, pParticle);

				if(pAsset != pAssetCache)
				{
					size_t* pTexture = (size_t *) frkPAssetGetDataPointer(pAsset);
					if(pTexture)
					{
						glBindTexture(GL_TEXTURE_2D, *pTexture);
						pParticleEmitter->SetFacing(pEmitter);
						pParticleEmitter->SetAlpha(*(frkPPropertyBlendPtr(pInfo)));
						pParticleEmitter->m_pEmitterShape->RenderParticles();
						FrkGeomDisplayList::GetInstance()->SetNumVertices(0);
					}

					pAssetCache = pAsset;
				}

				continue;
		}
		if(frkPPropertyGetFlagsEx(pInfo) & frkPSYSTEM_PROPERTYBIT_EX_FACINGLOCK)
		{
			t_frkVector3 VUp, VRight, VRot;
			pParticleEmitter->m_pEmitterShape->GetQuadAxis(VUp, VRight, VRot);
			if(!frkParticleSetFacingData(pParticle, (float *) &VUp, (float *) &VRight))
				frkParticleGetFacingData(pParticle, (float *) &VUp, (float *) &VRight);
			pParticleEmitter->m_pEmitterShape->SetQuadAxis (VUp, VRight, VRot);
		}
		else
		{
			// Particle Radial Facing
			if (*(frkPPropertyFlagPtr(pInfo)) & frkPSYSTEM_PROPERTYBIT_FACINGERADIAL) {
				t_frkMatrix4* pLcsWcs = (t_frkMatrix4*)frkPEmitterMatrixPtr (pEmitter);
				t_frkVector3 VUp;
				t_frkVector3* pParticlePos = (t_frkVector3*)frkParticlePosPtr (pParticle);
				t_frkVector3* pEmitterPos = (t_frkVector3*)&pLcsWcs->m30;

				VUp.x = 1.0f;
				VUp.y = 0.0f;
				VUp.z = 0.0f;

				t_frkVector3 vLook, vRight;
				Vec3Sub((t_frkVector3*) &vLook.x, (t_frkVector3*)&pParticlePos->x, (t_frkVector3*)&pEmitterPos->x );

				Vec3Normalize(&vLook, &vLook);

				Vec3Cross(&vRight, &vLook, &VUp);
				Vec3Normalize(&vRight, &vRight);

				Vec3Cross(&VUp, &vRight, &vLook);
				Vec3Normalize(&VUp, &VUp);

				pParticleEmitter->m_pEmitterShape->SetQuadAxis (VUp, vRight, vLook);
			}
			// Particle Radial Axial Velocity
			if(*(frkPPropertyFlagPtr(pInfo)) & frkPSYSTEM_PROPERTYBIT_FACINGAXIALVEL)
			{
				t_frkMatrix4 WcsVcs = FrkGraphicsHandler::GetInstance()->m_view;
				t_frkVector3 vUp, vLook, vRight;
				Vec3Set (&vLook, WcsVcs.m02, WcsVcs.m12, WcsVcs.m22);
				Vec3Set (&vRight, WcsVcs.m00, WcsVcs.m10, WcsVcs.m20);
				Vec3Set (&vUp, frkParticleVelPtr(pParticle)->x, frkParticleVelPtr(pParticle)->y, frkParticleVelPtr(pParticle)->z);
				Vec3Normalize(&vUp, &vUp);
				Vec3Cross(&vRight, &vUp, &vLook);
				pParticleEmitter->m_pEmitterShape->SetQuadAxis (vUp, vRight, vLook);
			}
		}

		pParticleEmitter->m_pEmitterShape->SubmitShape(pEmitter,pParticle);
	}
}

/******************************************************************************
Function	:	FrkParticleEmitter::OnSuperEmitCB
Description	:	Callback for super emitter 
Arguments	:	[Out]pEmitter		:	A pointer that is filled with the loaded emitter
[Out]pAnimationTrack:	Is filled with the animation track.
[Out]pSystem		:	Is filled with the particle system.
[In]pInfo			:	A pointer that is filled with the loaded emitter info
[In]sRefEmitterName	:	Is filled with the sRef emitter name.
[In]pLcsWcs			:	Holds the location/orientation of the emitter.
Return			:	None
/*****************************************************************************/
int FrkParticleEmitter::OnSuperEmitCB (_t_frkPEmitter** pEmitter, void** pAnmTrack, _t_frkPSystem** pSystem,
										 char* sRefEmitterName, t_frkMatrix4* pLcsWcs, 
										 _t_frkPEmitterInfo* pInfo, _t_frkPEmitter* pSEmitter) 
{
	FrkParticleEmitter *pParticleEmitter = NULL, **pTmpParticleEmitter = NULL;
	pTmpParticleEmitter	= (FrkParticleEmitter**)frkPEmitterUserDataPtr(pSEmitter);
	pParticleEmitter = *pTmpParticleEmitter;

	FrkParticleEmitter* pRefEmitter = new FrkParticleEmitter();
	int nStatus = frkPEmitterCreate (&pRefEmitter->m_pEmitter, "SEmitter1", (t_frkMatrix4*)pLcsWcs, pInfo);
	if(nStatus == -1)
	{
		pRefEmitter->m_pEmitter = NULL;
		pRefEmitter->Cleanup();
		return -1;
	}

	// Create emitted emitter's animation track
	_t_frkAnmTrk* pTrk = frkPPropertyGetAnmTrk (pInfo);	
	if (pTrk) {
		if(pRefEmitter->m_pAnimationInstance == NULL){
			pRefEmitter->m_pAnimationInstance = (_t_frkAnmInst*) malloc(frkPAnmGetInstMemSize ());				
			if(!pRefEmitter->m_pAnimationInstance)
			{
				pRefEmitter->m_pEmitter = NULL;
				pRefEmitter->Cleanup();
				return -1;
			}

			frkPAnmInit (pRefEmitter->m_pAnimationInstance, pRefEmitter->m_pEmitter);		
		}

		int nSwitch = frkPAnmTrkIsLoop(pTrk);
		frkPAnmSet (pRefEmitter->m_pAnimationInstance, pTrk);
		frkPAnmSetLoop (pRefEmitter->m_pAnimationInstance, nSwitch); 
	}

	// Setting required callbacks for the Emitted Emitter.
	frkPEmitterSetCallback (pRefEmitter->m_pEmitter, ePSYSTEM_CB_EPROCESS, OnEmitterProcess);
	frkPEmitterSetCallback (pRefEmitter->m_pEmitter, ePSYSTEM_CB_EDESTROY, OnEmitterDestroy);
	*frkPEmitterFlagPtr(pRefEmitter->m_pEmitter) |= frkPSYSTEM_EMITTERSTATE_EMITTED;
	nStatus = pRefEmitter->Create(pRefEmitter->m_pEmitter, pLcsWcs, pParticleEmitter->m_pParticleSys);


	//int nStatus = pRefEmitter->CreateRefEmitter(pInfo, pLcsWcs);

	if(nStatus == 0)
	{
		*pEmitter = pRefEmitter->m_pEmitter;
		*pSystem = pParticleEmitter->m_pParticleSys->m_pSystem;
	}
	else{
		delete pRefEmitter;
		return -1;
	}

	return 0;
}

/******************************************************************************
_Function	:	FrkParticleEmitter::TunerCallBack
_Description	:	The tuner callback is called when the Live Tuner receives
				update data from Particle Studio.
_Arguments	:	> sName:	Name of the emitter.
				> pPSB:	Emitter properties data.
				> pEmitter:	Pointer to emitter instance to be updated.
				> nSize:	Size of data chunk.
				> pUsrData:	Pointer to user data associated with tuner callback.
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::OnTunerCallBack ( char* sName, _t_frkPEmitterInfo* pPSB, _t_frkPEmitter* pEmitter, int nSize, void* pUsrData  )
{	
	if(!pEmitter)
		return;

	FrkParticleEmitter *pParticleEmitter = NULL, **pTmpParticleEmitter = NULL;
	pTmpParticleEmitter	= (FrkParticleEmitter**)frkPEmitterUserDataPtr(pEmitter);
	pParticleEmitter = *pTmpParticleEmitter;
	frkPEmitterUnReg(pParticleEmitter->m_pParticleSys->m_pSystem, pParticleEmitter->m_pEmitter);
	pParticleEmitter->Destroy();

	int nStatus = frkPEmitterCreate(&pParticleEmitter->m_pEmitter, frkPEmitterNamePtr(pEmitter), frkPEmitterMatrixPtr(pEmitter), pPSB);
	if(nStatus == -1)
	{
		pParticleEmitter->m_pEmitter = NULL;
		pParticleEmitter->Cleanup();
		return;
	}

	frkPEmitterReg(pParticleEmitter->m_pParticleSys->m_pSystem, pParticleEmitter->m_pEmitter);

	_t_frkAnmTrk* pTrk = frkPPropertyGetAnmTrk (pPSB);	
	if (pTrk) {
		if(pParticleEmitter->m_pAnimationInstance == NULL){
			pParticleEmitter->m_pAnimationInstance = (_t_frkAnmInst*) malloc(frkPAnmGetInstMemSize ());				
			if(!pParticleEmitter->m_pAnimationInstance)
			{
				pParticleEmitter->m_pEmitter = NULL;
				pParticleEmitter->Cleanup();
				return;
			}

			frkPAnmInit (pParticleEmitter->m_pAnimationInstance, pParticleEmitter->m_pEmitter);		
		}
		int nSwitch = frkPAnmTrkIsLoop(pTrk);
		frkPAnmSet (pParticleEmitter->m_pAnimationInstance, pTrk);
		frkPAnmSetLoop (pParticleEmitter->m_pAnimationInstance, nSwitch); 
	}

	frkPEmitterSetCallback (pParticleEmitter->m_pEmitter, ePSYSTEM_CB_EPROCESS, OnEmitterProcess);
	frkPEmitterSetCallback (pParticleEmitter->m_pEmitter, ePSYSTEM_CB_EDESTROY, OnEmitterDestroy);

	delete pParticleEmitter->m_pEmitterShape;

	pParticleEmitter->Create(pParticleEmitter->m_pEmitter, frkPEmitterMatrixPtr(pEmitter), pParticleEmitter->m_pParticleSys);

	frkPEffectEmitterRemove(pParticleEmitter->m_pParticleEffect->m_pEffect, pEmitter);
	frkPEffectEmitterAdd(pParticleEmitter->m_pParticleEffect->m_pEffect, pParticleEmitter->m_pEmitter);

 	FrkDataServer* pdataServer = FrkDataServer::GetInstance();
	_t_frkAssetInfo *pAsset;
	int nCount = frkPPropertyGetNumAssets(pParticleEmitter->m_pEmitterInfo);

	for(int i = 0; i < nCount; i++)
	{
		frkPPropertyGetAsset(pParticleEmitter->m_pEmitterInfo, i, &pAsset);

		if(pAsset)
		{
			frkPAssetSetDataPointer(pAsset, pdataServer->UserLoadAssetCB(pAsset, NULL) );
		}
	}
}
/******************************************************************************
_Function	:	FrkParticleEmitter::OnEmitterDestroy
_Description	:	Callback for destroying the emitter and associated data.
_Arguments	:	> pEmitter: Pointer to the particle emitter.
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::OnEmitterDestroy(_t_frkPEmitter* pEmitter)
{
	FrkParticleEmitter *pParticleEmitter = NULL, **pTmpParticleEmitter = NULL;
	pTmpParticleEmitter	= (FrkParticleEmitter**)frkPEmitterUserDataPtr(pEmitter);
	pParticleEmitter = *pTmpParticleEmitter;

	if (pParticleEmitter && pParticleEmitter->m_pAnimationInstance)
	{
		free((void*)pParticleEmitter->m_pAnimationInstance);
		pParticleEmitter->m_pAnimationInstance = NULL;
	}

	if (*frkPEmitterFlagPtr(pEmitter) & frkPSYSTEM_EMITTERSTATE_EMITTED)
		delete pParticleEmitter;
}
/******************************************************************************
_Function	:	FrkParticleEmitter::SetFacing
_Description:	Sets the global state for sprite shape mode.
_Arguments	:	> pEmitter:	Pointer to _t_frkPEmitter instance.
_Return		:	None.
*/
/*****************************************************************************/
int FrkParticleEmitter::SetFacing(_t_frkPEmitter* pEmitter)
{
	_t_frkPEmitterInfo* pInfo = (_t_frkPEmitterInfo*)(*(frkPEmitterInfoPtr(pEmitter)));
	t_frkVector3 VUp, VRight, VRot;
	t_frkMatrix4* pLcsWcs = frkPEmitterMatrixPtr (pEmitter);
	unsigned int nPBits = *(frkPPropertyFlagPtr(pInfo));

	if (nPBits & frkPSYSTEM_PROPERTYBIT_FACINGWAXISX) {
		Vec3Set(&VRot, 1.0f, 0.0f, 0.0f);
		Vec3Set(&VRight, 0.0f, 1.0f, 0.0f);
		Vec3Set(&VUp, 0.0f, 0.0f, 1.0f);
	}
	else if ( nPBits & frkPSYSTEM_PROPERTYBIT_FACINGWAXISY) {
		Vec3Set(&VRot, 0.0f, 1.0f, 0.0f);
		Vec3Set(&VRight, 1.0f, 0.0f, 0.0f);
		Vec3Set(&VUp, 0.0f, 0.0f, 1.0f);
	}
	else if (nPBits & frkPSYSTEM_PROPERTYBIT_FACINGWAXISZ) {
		Vec3Set(&VRot, 0.0f, 0.0f, 1.0f);
		Vec3Set(&VRight, 1.0f, 0.0f, 0.0f);
		Vec3Set(&VUp, 0.0f, 1.0f, 0.0f);
	}
	else if (nPBits & frkPSYSTEM_PROPERTYBIT_FACINGEMITTER) {
		Vec3Set(&VRot, pLcsWcs->m10, pLcsWcs->m11, pLcsWcs->m12);
		Vec3Set(&VRight, pLcsWcs->m20, pLcsWcs->m21, pLcsWcs->m22);
		Vec3Set(&VUp, pLcsWcs->m00, pLcsWcs->m01, pLcsWcs->m02);
	}
	else if ( nPBits & frkPSYSTEM_PROPERTYBIT_FACINGAXIALX) {		

		t_frkMatrix4 WcsVcs = FrkGraphicsHandler::GetInstance()->m_view;
		Vec3Set (&VRot, WcsVcs.m02, WcsVcs.m12, WcsVcs.m22);
		Vec3Set (&VUp, pLcsWcs->m00, pLcsWcs->m01, pLcsWcs->m02);
		Vec3Cross(&VRight, &VUp, &VRot);

	}
	else if ( nPBits & frkPSYSTEM_PROPERTYBIT_FACINGAXIALY) {
		t_frkMatrix4 WcsVcs = FrkGraphicsHandler::GetInstance()->m_view;
		Vec3Set (&VRot, WcsVcs.m02, WcsVcs.m12, WcsVcs.m22);
		Vec3Set (&VUp, pLcsWcs->m10, pLcsWcs->m11, pLcsWcs->m12);
		Vec3Cross(&VRight, &VUp, &VRot);

	}
	else if ( nPBits & frkPSYSTEM_PROPERTYBIT_FACINGAXIALZ) {
		t_frkMatrix4 WcsVcs = FrkGraphicsHandler::GetInstance()->m_view;
		Vec3Set (&VRot, WcsVcs.m02, WcsVcs.m12, WcsVcs.m22);
		Vec3Set (&VUp, pLcsWcs->m20, pLcsWcs->m21, pLcsWcs->m22);
		Vec3Cross(&VRight, &VUp, &VRot);

	}
	else {
		t_frkMatrix4 WcsVcs = FrkGraphicsHandler::GetInstance()->m_view;
		Vec3Set (&VRot, WcsVcs.m02, WcsVcs.m12, WcsVcs.m22);
		Vec3Set (&VRight, WcsVcs.m00, WcsVcs.m10, WcsVcs.m20);
		Vec3Set (&VUp, WcsVcs.m01, WcsVcs.m11, WcsVcs.m21);
	}

	FrkParticleEmitter* pParticleEmitter = NULL;
	pParticleEmitter = *((FrkParticleEmitter **)frkPEmitterUserDataPtr(pEmitter));
	if(pParticleEmitter)
		pParticleEmitter->m_pEmitterShape->SetQuadAxis(VUp, VRight, VRot);

	return 0;
}
/******************************************************************************
_Function	:	FrkParticleEmitter::SetAlpha
_Description:	Sets the emitter blend mode.
_Arguments	:	> nBlendMode: The emitter blend mode.
_Return		:	None.
*/
/*****************************************************************************/
int FrkParticleEmitter::SetAlpha(int nBlendMode)
{
	//nBlendModeCache = nBlendMode;

	switch (nBlendMode) {
		case frkPSYSTEM_EMITTERBLENDMODE_NORMAL:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE:
			glBlendFunc(GL_ONE, GL_ONE);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_SUBTRACTIVE:
			if (glBlendEquation)
			{
				glBlendEquation(GL_FUNC_REVERSE_SUBTRACT_EXT);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			}
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_DARKMAP:
			glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_LIGHTMAP:
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE2:
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			break;

		case frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE3:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
	}

	return 0;
}
/******************************************************************************
_Function	:	FrkParticleEmitter::Cleanup
_Description:	Makes memory deallocations when emitter creation fails.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
int FrkParticleEmitter::Cleanup()
{
	if(m_pEmitter)
	{
		frkPEmitterDestroy (&m_pEmitter);		
		m_pEmitter = NULL;

		if(m_pEmitterShape)
			delete m_pEmitterShape;
		m_pEmitterShape = NULL;
	}	

	return 0;
}

void FrkParticleEmitter::Draw()
{
	//LPDIRECT3DDEVICE9 pDevice = FrkGraphicsHandler::GetInstance()->d3dDevice;

	int nType = frkPAssetGetType((_t_frkAssetInfo *) frkPPropertyCurAssetPtr(m_pEmitterInfo));

	bool bDraw = false;
	if(nType == ePSYSTEM_ASSETTYPE_TEXTURE)
	{
		if (*(frkPPropertyNumAssetsPtr (m_pEmitterInfo)) &&
			*(frkPPropertyFlagPtr(m_pEmitterInfo)) & (frkPSYSTEM_PROPERTYBIT_PANIMRANDOM | frkPSYSTEM_PROPERTYBIT_PANIMFLIPBOOK))
		{
		}
		else
		{
			SetAlpha(*frkPPropertyBlendPtr(frkPEmitterGetPropertyInfo(m_pEmitter)));			
			m_pEmitterShape->RenderParticles();
		}
	}
}
/******************************************************************************
// SECTION: EMITTER CLASS METHODS USED WITH FOR WORKING DIRECTLY AT EMITTER LEVEL
// AND NOT USING THE EFFECT INTERFACE.
/*****************************************************************************/
/******************************************************************************
_Function	:	FrkParticleEmitter::LoadAnimationAssets
_Description	:	Loads the animation assets associated with an emitter.
_Arguments	:	> animationTrack:	A pointer to the animation track associated
				with the emitter. 
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::LoadEmitterAnimationAssets(_t_frkAnmTrk* animationTrack)
{
	_t_frkPEmitterInfo* pInfo = NULL;

	frkPAnmResetTrkKeyTracer ();
	while( (pInfo = frkPAnmGetTrkKeyTracer (animationTrack)))
	{
		LoadEmitterAssets(pInfo);
		frkPAnmIncTrkKeyTracer ();
	}
}
/******************************************************************************
_Function	:	FrkParticleEmitter::LoadEmitterAssets
_Description	:	Loads the Emitter assets associated with an emitter.
_Arguments	:	> emitterInfo: A pointer to the EmitterInfo structure.
_Return		:	None.
*/
/*****************************************************************************/
void FrkParticleEmitter::LoadEmitterAssets(_t_frkPEmitterInfo* emitterInfo)
{
	_t_frkAssetInfo* pAsset = NULL;
	int nType = 0;
	char* sKey = "";

	int nCount = frkPPropertyGetNumAssets(emitterInfo);

	for(int i = 0; i < nCount; i++)
	{
		frkPPropertyGetAsset(emitterInfo, i, &pAsset);
		if(pAsset)
		{
			nType = frkPAssetGetType(pAsset);
			sKey =  frkPAssetGetKeyFileName(pAsset);
			if(nType == ePSYSTEM_ASSETTYPE_TEXTURE)
			{
				frkPAssetSetDataPointer(pAsset, FrkDataServer::GetInstance()->LoadTexture(sKey));
			}
			else if(nType == ePSYSTEM_ASSETTYPE_MODEL)
			{
				frkPAssetSetDataPointer(pAsset, FrkDataServer::GetInstance()->LoadModel(sKey));
			}
		}
	}

	// Load associated animation assets
	_t_frkAnmTrk* pTrk = frkPPropertyGetAnmTrk (emitterInfo);	
	if (pTrk)
	{
		LoadEmitterAnimationAssets(pTrk);
	}
}

/*****************************************************************************/
void FrkParticleEmitter::InitPixelShader()
{
	int nShaderAssets = frkPPropertyGetNumShaderAssets (m_pEmitterInfo);								
	if(nShaderAssets > 0)																			
	{																								
		_t_frkAssetInfo* pShaderAsset;																
		frkPPropertyGetShaderAsset (m_pEmitterInfo, 0, &pShaderAsset);								
		if( pShaderAsset )																			
		{																							
			char* sShaderName = frkPAssetGetKey(pShaderAsset);											
			FrkGraphicsHandler::GetInstance()->LoadPixelShader(sShaderName);
			frkPEmitterSetCallback (m_pEmitter, ePSYSTEM_CB_EPROCESS, OnEmitShaderCB);
		}																							
	}
}
/******************************************************************************
Function	:	ParticleEmitter::OnEmitShaderCB
Description	:	Callback for shader.
Arguments	:	[In]pEmitter:	A pointer to an emitter
[In]fTDelta	:	Time difference from last frame.
Return		:	None.
/*****************************************************************************/
void FrkParticleEmitter::OnEmitShaderCB(_t_frkPEmitter* pEmitter, float fTDelta)
{
	FrkGraphicsHandler::GetInstance()->ShaderPreRender ();
	OnEmitterProcess(pEmitter, fTDelta);
	FrkGraphicsHandler::GetInstance()->ShaderPostRender ();
}
/*****************************************************************************/
int FrkParticleEmitter::Destroy()
{
	
#ifdef LIVE_TUNER
		frkTunerUnRegEmitter(m_pEmitter);
#endif

	return 0;
}