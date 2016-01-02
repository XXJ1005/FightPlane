/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef frkpsystem_h
#define frkpsystem_h

#include "frkpoffsets.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef struct _t_frkpeffectinfo			_t_frkPEffectInfo;
typedef struct _t_frkpeffect				_t_frkPEffect;
typedef struct _t_frkpxrefinfo				_t_frkPXrefInfo;
typedef struct _t_frkpemitter				_t_frkPEmitter;
typedef struct _t_frkpemitterinfo			_t_frkPEmitterInfo;
typedef struct _t_frkpsystem				_t_frkPSystem;
typedef struct _t_frkparticle				_t_frkParticle;
typedef struct _t_frkassetinfo				_t_frkAssetInfo;
typedef struct _t_frkchunkinterface			_t_frkPChunk;
typedef struct _t_frkanminst				_t_frkAnmInst;
typedef struct _t_frkanmtrk					_t_frkAnmTrk;
typedef struct _t_frkanmchan				_t_frkAnmChan;
typedef struct _t_frkanm					_t_frkAnm;
typedef struct _t_frkpbuffer				_t_frkPBuffer;
typedef struct _t_frksdk					_t_frkSDK;
typedef struct _t_frkpnote					_t_frkPNote;
typedef struct _t_frkldrchunk				_t_frkLdrChunk;
typedef struct _t_frkparticleassetinfo		_t_frkParticleAssetInfo;
/*****************************************************************************/
typedef void* (*_t_frkPEffectLoadAssetCB) (_t_frkAssetInfo* pAsset, void* pCBUserData);
typedef void (*_t_PEffectDestroyCB) (_t_frkPEffect* pEffect);
typedef void (*_t_PSystemProcessCB) (_t_frkPSystem* pPSystem, float fTDelta);
typedef void (*_t_ParticleSubmitCB) (_t_frkPEmitter* pEmit, _t_frkParticle* pParticle);
typedef void (*_t_ParticleBirthCB)	(_t_frkPEmitter* pEmit, t_frkVector3* pOutPos, t_frkVector3* pOutVelDir);
typedef void (*_t_PEmitterPhysicsCB)(_t_frkPEmitter* pEmit, float fTDelta);
typedef void (*_t_PEmitterProcessCB)(_t_frkPEmitter* pEmit, float fTDelta);
typedef void (*_t_PEmitterEmitCB) (_t_frkPEmitter* pEmit);
typedef void (*_t_ParticleProcessCB) (_t_frkPEmitter* pEmitter, float fTDelta);
typedef void (*_t_ParticleDeathCB) (_t_frkPEmitter* pEmitter);
typedef void (*_t_PEmitterAuxDeathCB) (_t_frkPEmitter* pEmit);
typedef void (*_t_PEmitterDestroyCB) (_t_frkPEmitter* pEmit);
typedef int	 (*_t_SEmitterEEmitCB) (_t_frkPEmitter** pEmitter, void** pAnmTrack, _t_frkPSystem** pPSystem, 
				char* sRefEmitterName, t_frkMatrix4* pLcsWcs, _t_frkPEmitterInfo* pInfo, _t_frkPEmitter* pSEmitter);
typedef void (*_t_PEmitterSetRStateCB) (_t_frkPEmitter* pEmitter, int bEnd);
typedef int (*_t_PEmitterEmitRateCB) (_t_frkPEmitter* pEmitter, float fTDelta);
typedef float (*_t_PEmitterLODCB) (_t_frkPEmitter* pEmitter);
typedef void (*_t_PEmitterDeathCB) (_t_frkPEmitter* pEmitter);
/*****************************************************************************/
enum e_frkCallback
{
	ePSYSTEM_CB_EPROCESS,				// Emitter Process
	ePSYSTEM_CB_PHYSICS,				// Particle Physcis
	ePSYSTEM_CB_EMIT,					// Particle emission
	ePSYSTEM_CB_SUBMIT,					// Submit particle for render
	ePSYSTEM_CB_BIRTH,					// Particle birth
	ePSYSTEM_CB_PPROCESS,				// Particle Process
	ePSYSTEM_CB_SUPEREMITCB,			// Reference particle emission
	ePSYSTEM_CB_ERSTATE,				// Emitter render state
	ePSYSTEM_CB_EDESTROY,				// Emitter destroy
	ePSYSTEM_CB_EEMITRATE,				// Emitter emission rate
	ePSYSTEM_CB_DEATH,					// Particle death
	ePSYSTEM_CB_LOD,					// Level of detail
	ePSYSTEM_CB_EDEATH,					// Emitter death
	ePSYSTEM_CB_EFFECTDESTROY,			// Effect Destroy
	ePSYSTEM_CB_MAX,

	//additonal for Effects api 
	ePSYSTEM_CB_EREFPROCESS,
	ePSYSTEM_CB_EREFDESTROY
};

enum e_frkSort
{
	ePSYSTEM_SORT_NONE,					// No sort
	ePSYSTEM_SORT_EMITTERS,				// Emitter sort
	ePSYSTEM_SORT_EPARTICLE,			// Emitter particle sort
	ePSYSTEM_SORT_EMITTERSEPARTICLE,	// Emitters and emitter particle sort
	ePSYSTEM_SORT_SPARTICLE,			// System particle sort

	ePSYSTEM_SORT_MAX
};

enum e_frkPState
{
	ePSYSTEM_PSTATE_SORTXFORM,			// Sort tranformation
	ePSYSTEM_PSTATE_SORTDESCEND,		// Sort type descending order
	ePSYSTEM_PSTATE_SORTMODE,			// Sort mode

	ePSYSTEM_PSTATE_MAX
};

enum e_frkProperty
{
	ePSYSTEM_PROPERTY_COLORSTAGE1,		// Color stage 1
	ePSYSTEM_PROPERTY_COLORSTAGE2,		// Color stage 2
	ePSYSTEM_PROPERTY_COLORSTAGE3,		// Color stage 3
	ePSYSTEM_PROPERTY_COLORSTAGE4,		// Color stage 4
	ePSYSTEM_PROPERTY_MINVELOCITY,		// Minimum particle velocity
	ePSYSTEM_PROPERTY_VARVELOCITY,		// Maximum particle velocity
	ePSYSTEM_PROPERTY_DRAG,				// Drag/acceleration
	ePSYSTEM_PROPERTY_COLORTINT,		// Tint color
	ePSYSTEM_PROPERTY_GRAVITY,			// Gravity magnitude
	ePSYSTEM_PROPERTY_EMISSIONPARAM1,	// Emission volume parameter 1
	ePSYSTEM_PROPERTY_EMISSIONPARAM2,	// Emission volume parameter 2
	ePSYSTEM_PROPERTY_EMISSIONPARAM3,	// Emission volume parameter 3
	ePSYSTEM_PROPERTY_VOLUMETYPE,		// Emission volume type
	ePSYSTEM_PROPERTY_BOUNDINGBOX,		// Emitter bounding box
	ePSYSTEM_PROPERTY_BLENDMODE,		// Render blendmode
	ePSYSTEM_PROPERTY_MINSPIN,			// Minimum particle spin speed
	ePSYSTEM_PROPERTY_VARSPIN,			// Maximum particle spin speed	
	ePSYSTEM_PROPERTY_MAXPARTICLES,		// Maximum particles limit
	ePSYSTEM_PROPERTY_SHAPE,			// Particle shape
	ePSYSTEM_PROPERTY_EMISSIONRATE,		// Emission rate
	ePSYSTEM_PROPERTY_SCALE,			// Global scale
	ePSYSTEM_PROPERTY_EMITTERLIFE,		// Emitter life in seconds
	ePSYSTEM_PROPERTY_MINLIFE,			// Minimum particle life
	ePSYSTEM_PROPERTY_VARLIFE,			// Maximum particle life
	ePSYSTEM_PROPERTY_DELTAMULT,		// Emitter speed multiplier
	ePSYSTEM_PROPERTY_MAX
};

enum e_frkEmitterVolume 
{
	ePSYSTEM_VOLUME_PLANE		= 0,		
	ePSYSTEM_VOLUME_SPHERE		= 1,	
	ePSYSTEM_VOLUME_CONE		= 2,			
	ePSYSTEM_VOLUME_CYLINDER	= 3,		
	ePSYSTEM_VOLUME_PLANEVOL	= 4,		
	ePSYSTEM_VOLUME_SPHEREVOL	= 5,	
	ePSYSTEM_VOLUME_CONEVOL		= 6,	
	ePSYSTEM_VOLUME_CYLINDERVOL	= 7,
	ePSYSTEM_VOLUME_POINT		= 8,
	ePSYSTEM_VOLUME_USER		= 9,
	ePSYSTEM_VOLUME_ARC			= 10,
	ePSYSTEM_VOLUME_ARCVOL		= 11
};

enum e_frkAssetType
{
	ePSYSTEM_ASSETTYPE_NONE,
	ePSYSTEM_ASSETTYPE_TEXTURE,
	ePSYSTEM_ASSETTYPE_MODEL,

	ePSYSTEM_ASSETTYPE_MAX
};

enum e_frkParticleShape
{
	ePSYSTEM_PARTICLESHAPE_DIAMOND		= 0,
	ePSYSTEM_PARTICLESHAPE_RECTANGLE	= 1,
	ePSYSTEM_PARTICLESHAPE_STRING		= 2,
	ePSYSTEM_PARTICLESHAPE_TRIANGLE		= 3,
	ePSYSTEM_PARTICLESHAPE_POINT		= 4	
};

enum e_frkPBufferState
{
	ePSYSTEM_BUFFER_RENDERED,
	ePSYSTEM_BUFFER_SIMULATED
};

/*****************************************************************************/
#define frkPSYSTEM_PROPERTYBIT_PANIMRANDOM		0x00000001
#define frkPSYSTEM_PROPERTYBIT_PANIMFLIPBOOK	0x00000002
#define frkPSYSTEM_PROPERTYBIT_PANIMRNDFIRST	0x00000004
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISX		0x00000008
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISY		0x00000010
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISZ		0x00000020
#define frkPSYSTEM_PROPERTYBIT_FACINGEMITTER	0x00000040
#define frkPSYSTEM_PROPERTYBIT_LIGHTEMITTER		0x00000080
#define frkPSYSTEM_PROPERTYBIT_PATHPARTICLE		0x00000100
#define frkPSYSTEM_PROPERTYBIT_PATHEMITTER		0x00000200
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRAL		0x00000400
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALA		0x00000800
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALX		0x00001000
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALY		0x00002000
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALZ		0x00004000
#define frkPSYSTEM_PROPERTYBIT_PATHBIRTH		0x00008000
#define frkPSYSTEM_PROPERTYBIT_REFEMITTER		0x00010000
#define frkPSYSTEM_PROPERTYBIT_PARTICLEETRANS	0x00020000
#define frkPSYSTEM_PROPERTYBIT_EMITTERLOCAL     0x00020000
#define frkPSYSTEM_PROPERTYBIT_PANIMNOLOOP		0x00040000
#define frkPSYSTEM_PROPERTYBIT_FACINGERADIAL	0x00080000
#define frkPSYSTEM_PROPERTYBIT_INFINITELOOP		0x00100000
#define frkPSYSTEM_PROPERTYBIT_DIRECTIONAL1		0x00200000
#define frkPSYSTEM_PROPERTYBIT_DIRECTIONAL2		0x00400000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALX		0x00800000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALY		0x01000000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALZ		0x02000000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALVEL	0x04000000
#define frkPSYSTEM_PROPERTYBIT_SHAPERECT		0x08000000
#define frkPSYSTEM_PROPERTYBIT_INFINITEFOR		0x10000000
#define frkPSYSTEM_PROPERTYBIT_INFINITEFROZEN	0x20000000
#define frkPSYSTEM_PROPERTYBIT_SHAPESTRING		0x40000000
#define frkPSYSTEM_PROPERTYBIT_NOLOD			0x80000000

#define frkPSYSTEM_PROPERTYBIT_EX_INTIALSCALELOCK	0x00000001
#define frkPSYSTEM_PROPERTYBIT_EX_INTIALSPINLOCK	0x00000002
#define frkPSYSTEM_PROPERTYBIT_EX_ADVANCETABUV 		0x00000004
#define frkPSYSTEM_PROPERTYBIT_EX_ONESHOT 			0x00000008
#define frkPSYSTEM_PROPERTYBIT_EX_EMITONMOTION		0x00000010
#define frkPSYSTEM_PROPERTYBIT_EX_FACINGLOCK		0x00000020
#define frkPSYSTEM_EMITTERSTATE_FREEZE					0x00000001
#define frkPSYSTEM_EMITTERSTATE_ENABLE					0x00000002
#define frkPSYSTEM_EMITTERSTATE_VISIBLE					0x00000004
#define frkPSYSTEM_EMITTERSTATE_STOP					0x00000008
#define frkPSYSTEM_EMITTERSTATE_ORPHAN					0x00000010
#define frkPSYSTEM_EMITTERSTATE_EMITTED					0x00000020		// reserved read-only
#define frkPSYSTEM_EMITTERSTATE_DELAY					0x00000040		// reserved read-only
#define frkPSYSTEM_EMITTERSTATE_USERBIRTH				0x00000080
#define frkPSYSTEM_EMITTERSTATE_EMISSIONINTERP			0x00000100
#define frkPSYSTEM_EMITTERSTATE_PHYSICS					0x00000200
#define frkPSYSTEM_EMITTERSTATE_DEAD					0x00000400		// reserved read-only	

#define frkPSYSTEM_EFFECTSTATE_XREF						0x1000000		// reserved read-only

#define frkPSYSTEM_EMITTERSTATE_ONESHOTFREEZE			0x00000800
#define frkPSYSTEM_EMITTERSTATE_ONESHOTSTOPPED			0x00001000
#define frkPSYSTEM_EMITTERSTATE_ONESHOTNOPARTICLES		0x00002000
#define frkPSYSTEM_EMITTERSTATE_ONESHOTANMENDED			0x00004000
#define frkPSYSTEM_EMITTERSTATE_ONESHOTDESTROYDEAD		0x00008000

#define frkPSYSTEM_EMITTERSTATE_FRAMEDELAY				0x00010000		// reserved read-only
#define frkPSYSTEM_EMITTERSTATE_FRAMEDELAYPROCESSED		0x00020000		// reserved read-only
#define frkPSYSTEM_EMITTERSTATE_PRESTART				0x00040000		// reserved read-only

#define frkPSYSTEM_EMITTERSTATE_ONESHOTMASK (		frkPSYSTEM_EMITTERSTATE_ONESHOTFREEZE |			\
													frkPSYSTEM_EMITTERSTATE_ONESHOTSTOPPED |		\
													frkPSYSTEM_EMITTERSTATE_ONESHOTNOPARTICLES |	\
													frkPSYSTEM_EMITTERSTATE_ONESHOTANMENDED |		\
													frkPSYSTEM_EMITTERSTATE_ONESHOTDESTROYDEAD			\
											 )


#define frkPSYSTEM_ONESHOTBIT_FREEZE				frkPSYSTEM_EMITTERSTATE_ONESHOTFREEZE
#define frkPSYSTEM_ONESHOTBIT_STOPPED				frkPSYSTEM_EMITTERSTATE_ONESHOTSTOPPED
#define frkPSYSTEM_ONESHOTBIT_NOPARTICLES			frkPSYSTEM_EMITTERSTATE_ONESHOTNOPARTICLES
#define frkPSYSTEM_ONESHOTBIT_ANMENDED				frkPSYSTEM_EMITTERSTATE_ONESHOTANMENDED
#define frkPSYSTEM_ONESHOTBIT_DESTROYDEAD				frkPSYSTEM_EMITTERSTATE_ONESHOTDESTROYDEAD

#define frkPSYSTEM_ONESHOTBIT_DEFAULT		(		frkPSYSTEM_EMITTERSTATE_ONESHOTDESTROYDEAD |		\
													frkPSYSTEM_EMITTERSTATE_ONESHOTNOPARTICLES |	\
													frkPSYSTEM_EMITTERSTATE_ONESHOTANMENDED			\
											)




#define frkPSYSTEM_EMITTERBLENDMODE_NORMAL		0
#define frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE	1
#define frkPSYSTEM_EMITTERBLENDMODE_SUBTRACTIVE	2
#define frkPSYSTEM_EMITTERBLENDMODE_DARKMAP		3
#define frkPSYSTEM_EMITTERBLENDMODE_LIGHTMAP	4
#define frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE2	5
#define frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE3	6
#define frkPSYSTEM_EMITTERBLENDMODE_EMISSIVE4	7
#define frkPSYSTEM_EMITTERBLENDMODE_MAXTYPES	8
#define frkPSYSTEM_EMITTERBLENDMODE_USER		0xff

#define frkPSYSTEM_FORCEREPELLANT				0
#define frkPSYSTEM_FORCEATTRACTOR				1
#define frkPSYSTEM_FORCENOISE					2
#define frkPSYSTEM_FORCEDIRECTIONAL				4

#define frkPSYSTEM_SYSTEMBIT_SORTEMITTERS		0x00000001
#define frkPSYSTEM_SYSTEMBIT_SORTXFORM			0x00000002
#define frkPSYSTEM_SYSTEMBIT_SORTDESCEND		0x00000004
#define frkPSYSTEM_SYSTEMBIT_SORTEPARTICLE		0x00000008
#define frkPSYSTEM_SYSTEMBIT_SORTSPARTICLE		0x00000010
#define frkPSYSTEM_SYSTEMBIT_ASYNC				0x00000020		// reserved

#define frkPSYSTEM_CHUNKID_PSB					0
#define frkPSYSTEM_CHUNKID_EVENTTRACK			1
#define frkPSYSTEM_CHUNKID_XREF					2

#define  frkPSYSTEM_PROPERTYCLONECOMPONENT_FORCES		0x00000001
#define  frkPSYSTEM_PROPERTYCLONECOMPONENT_ASSETS	  	0x00000002

/*****************************************************************************/
/* Module API Section */
extern void		frkPGetAuxBuffer (_t_frkParticle** aOutParticles[], int* pOutCount);
extern int		frkPGetNumLive (void);
extern void		frkPSetGravityDir (t_frkVector3* pWorldGravityDir);
extern void		frkPEnableEmitterParticlePools (void);
extern void		frkPSetPhysicsDeltaStep (float fTDeltaStep);

/* Particle System API Section */
extern int		frkPSystemCreate (_t_frkPSystem** pPSystem, char* sName, int nMaxParticles);
extern int		frkPSystemCreateEx (_t_frkPSystem** pPSystem, char* sName, int nMaxParticles, _t_frkSDK* pSDK);
extern void		frkPSystemDestroy (_t_frkPSystem** pSys);
extern void		frkPSystemProcess (_t_frkPSystem* pPSystem, float fTDelta);
extern void		frkPSystemSetState (_t_frkPSystem* pPSystem, int ePState, void* pState);
extern void		frkPSystemGetState (_t_frkPSystem* pPSystem, int ePState, void* pState);
extern void		frkPSystemGetAuxBuffer (_t_frkPSystem* pPSystem, _t_frkParticle** aOutParticles[], int* pOutCount);
extern int		frkPSystemGetNumLive (_t_frkPSystem* pPSystem);
extern void*	frkPSystemGetBufferPos (_t_frkPSystem* pPSystem);
extern int		frkPSystemGetParticleSortBuffer (_t_frkPSystem* pPSystem, _t_frkParticle** aOutParticles[], int* pOutCount);


extern int		frkPSystemASyncEnable(_t_frkPSystem* pPSystem, int bSwitch);
extern void		frkPSystemProcessASync (_t_frkPSystem* pPSystem, float fTDelta);
extern void		frkPSystemProcessASyncReady (_t_frkPSystem* pPSystem, float fTDelta);
extern void		frkPSystemSetMaxParticleCount(_t_frkPSystem* pPSystem, int nMaxPart);
extern int		frkPSystemGetMaxParticleCount(_t_frkPSystem* pPSystem);

extern void		frkPSystemProcessTask (_t_frkPSystem* pPSystem, float fTDelta);
extern void		frkPSystemProcessTaskReady (_t_frkPSystem* pPSystem, float fTDelta);
extern void		frkPSystemProcessSimTask (_t_frkPSystem* pPSystem, int nStart, int nCount);
extern void*	frkPSystemGetContext(_t_frkPSystem* pPSystem);
extern void 	frkPSystemSetContext(_t_frkPSystem* pPSystem, void *pContext);

/* Emitter API Section */
extern int		frkPEmitterCreate (_t_frkPEmitter** pOutEmitter, char* sName,
						t_frkMatrix4* pLcsWcs, _t_frkPEmitterInfo* pEmitterInfo);
extern int		frkPEmitterCreateEx (_t_frkPEmitter** pOutEmitter, char* sName, t_frkMatrix4* pLcsWcs, 
						_t_frkPEmitterInfo* pEmitterInfo, _t_frkSDK* pSDK);
extern void		frkPEmitterDestroy (_t_frkPEmitter** pEmit);
extern void		frkPEmitterReg (_t_frkPSystem* pPSystem, _t_frkPEmitter* pEmitter);
extern void		frkPEmitterUnReg (_t_frkPSystem* pPSystem, _t_frkPEmitter* pEmitter);
extern void		frkPEmitterProcess (_t_frkPEmitter* pEmitter, float fTDelta);
extern void		frkPEmitterPhysics (_t_frkPEmitter* pEmitter, float fTDelta);
extern void		frkPEmitterEmit (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterRestart (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetMatrix (_t_frkPEmitter* pEmit, t_frkMatrix4* pLcsWcs);
extern void		frkPEmitterSetState (_t_frkPEmitter* pEmitter, int nStateMask, int bSwitch);
extern int		frkPEmitterGetNumLive (_t_frkPEmitter* pEmitter);
extern int		frkPEmitterSetForce (_t_frkPEmitter* pEmitter, int nIndex, t_frkPtForce* pForce);
extern int		frkPEmitterGetForce (t_frkPtForce** pOutForce, _t_frkPEmitter* pEmitter, int nIndex);
extern void		frkPEmitterSetCallback (_t_frkPEmitter* pEmitter, int eCB, void* pCB);
extern void		frkPEmitterGetCallback (_t_frkPEmitter* pEmitter, int eCB, void** pCB);
extern void		frkPEmitterParticleResetTracer (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterParticleIncTracer (_t_frkPEmitter* pEmitter);
extern _t_frkParticle*		frkPEmitterParticleGetTracerItem (_t_frkPEmitter* pEmitter);
extern _t_frkPEmitterInfo*	frkPEmitterGetPropertyInfo (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetPropertyInfo (_t_frkPEmitter* pEmitter, _t_frkPEmitterInfo* pInfo);
extern void		frkPEmitterKillParticles (_t_frkPEmitter* pEmitter, _t_ParticleDeathCB pCB);
extern void		frkPEmitterUnRegDestroyChildren (_t_frkPSystem* pPSystem, _t_frkPEmitter* pSEmitter);
extern void		frkPEmitterBirth (_t_frkPEmitter* pEmitter, t_frkVector3* pPos, t_frkVector3* pVel);
extern void		frkPEmitterDeath (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetCBData (_t_frkPEmitter* pEmitter, void* pCBData);
extern void		frkPEmitterSetUserData (_t_frkPEmitter* pEmit, void* pUsrData);
extern void		frkPEmitterGetUserData (_t_frkPEmitter* pEmit, void** pUsrData);
extern void		frkPEmitterSetLife (_t_frkPEmitter* pEmitter, float fLife);
extern float	frkPEmitterGetLife (_t_frkPEmitter* pEmitter);
extern float	frkPEmitterGetTime (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetScale (_t_frkPEmitter* pEmitter, float fScale);
extern float	frkPEmitterGetScale (_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetEmissionVolumeScale (_t_frkPEmitter* pEmitter, float fPlaneDScale, float fPlaneHScale, float fPlaneWScale);
extern void		frkPEmitterSetEmissionRateScale (_t_frkPEmitter* pEmitter, float fERateScale);
extern void		frkPEmitterSetEmissionInterpDistanceThreshold (_t_frkPEmitter* pEmitter, float fEmissionInterpDistThreshold);
extern void		frkPEmitterSetEmissionInterpTParamInterval (_t_frkPEmitter* pEmitter, float fEmissionInterpTParamDelta);
extern void		frkPEmitterSimulate(_t_frkPEmitter* pEmitter, float fSimTime, float fTick);
extern _t_frkAnmInst* frkPEmitterGetAnmInst (_t_frkPEmitter* pEmitter);

extern int		frkPEmitterSetSpeed (_t_frkPEmitter* pEmitter, float fSpeed);
extern float	frkPEmitterGetSpeed (_t_frkPEmitter* pEmitter);
extern int		frkPEmitterIsAlive(_t_frkPEmitter* pEmitter);
extern void		frkPEmitterSetSpiralDir(_t_frkPEmitter* pEmitter, float fSpiralDir);
extern float	frkPEmitterGetSpiralDir(_t_frkPEmitter* pEmitter);

#define			frkPEmitterNamePtr(pE)((char*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_SNAME))
#define			frkPEmitterFlagPtr(pE) ((int*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_NFLAGS))
#define			frkPEmitterMatrixPtr(pE) ((t_frkMatrix4*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_LCSWCS))
#define			frkPEmitterInfoPtr(pE) (((void**)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_PINFO)))
#define			frkPEmitterUserDataPtr(pE)((void*)((_t_frkPEmitter*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_PUSRDATA)))

/* Particle API Section */
extern void		frkParticleProcess (_t_frkPEmitter* pEmitter, float fTDelta);
extern void		frkParticleProcessString (_t_frkPEmitter* pEmitter, float fTDelta);
extern _t_frkParticleAssetInfo* frkParticleGetAssetInfo(_t_frkParticle *pParticle);
#define			frkParticleTimePtr(pP) (float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FTIME)
#define			frkParticlePosPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_POS))		
#define			frkParticleVelPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_VEL))		
#define			frkParticleColorPtr(pP) ((t_frkRGBA*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_COLOR))		
#define			frkParticleLifePtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FLIFE))		
#define			frkParticleScalePtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FSCALE))		
#define			frkParticleRotPtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FROT))		
#define			frkParticleAssetIdx(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_NASSETIDX))		
#define			frkParticleDataPtr(pP) (*((void**)&(((unsigned char*)(pP))[OFFSET_T_FRKPARTICLE_PDATA])))
#define			frkParticleEmitterPtr(pP) (*((_t_frkPEmitter**)&(((unsigned char*)(pP))[120])))
#define			frkParticleEmitterInfoPtr(pP) (*((_t_frkPEmitterInfo**)&(((unsigned char*)(pP))[124])))
#define			frkParticleAssetPtr(pP, pI) ((*(unsigned char**)((unsigned char*)(pI) + OFFSET_T_FRKPEMITTERINFO_AASSETS)) + \
					OFFSET_T_FRKASSETINFO_SIZE * (*((int*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_NASSETIDX))))
#define			frkParticleJitterPtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FJITTER))
extern int		frkParticleSetFacingData(_t_frkParticle *pParticle, float *pVUp, float *pVRight);
extern void		frkParticleGetFacingData(_t_frkParticle *pParticle, float *pVUp, float *pVRight);
/* Property API section */
extern void		frkPPropertyGetState (_t_frkPEmitterInfo* pInfo, int eProperty, void* pProperty);
extern void		frkPPropertySetState (_t_frkPEmitterInfo* pInfo, int eProperty, void* pProperty);
extern int 		frkPropertyGetSize (_t_frkPEmitterInfo* pSrcInfo, int nFlags);
extern void		frkPropertyCopy (_t_frkPEmitterInfo* pDstInfo, _t_frkPEmitterInfo* pSrcInfo, int nFlags);
extern void*	frkPPropertyGetCustomData (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetCustomDataSize (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetAsset (_t_frkPEmitterInfo* pInfo, int nIndex, _t_frkAssetInfo** pOutAsset);
extern int		frkPPropertySetAsset (_t_frkPEmitterInfo* pInfo, int nIndex, _t_frkAssetInfo* pAsset);
extern int		frkPPropertyGetRefAsset (_t_frkPEmitterInfo* pInfo, int nIndex, _t_frkAssetInfo** pOutAsset);
extern int		frkPPropertyGetShaderAsset (_t_frkPEmitterInfo* pInfo, int nIndex, _t_frkAssetInfo** pOutAsset);
extern int		frkPPropertyGetEmissionAsset (_t_frkPEmitterInfo* pInfo, int nIndex, _t_frkAssetInfo** pOutAsset);
extern int		frkPPropertyGetForce (_t_frkPEmitterInfo* pInfo, int nIndex, t_frkPtForce* pOutForce);
extern int		frkPPropertySetForce (_t_frkPEmitterInfo* pInfo, int nIndex, t_frkPtForce* pForce);
extern int		frkPPropertyGetNumAssets (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetNumRefAssets (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetNumShaderAssets (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetNumEmissionAssets (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetNumForces (_t_frkPEmitterInfo* pInfo);
extern void		frkPPropertySetCurAsset (_t_frkPEmitterInfo* pInfo, _t_frkAssetInfo* pAsset);
extern _t_frkAssetInfo*	frkPPropertyGetCurAsset (_t_frkPEmitterInfo* pInfo);
extern _t_frkAnmTrk*	frkPPropertyGetAnmTrk (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetGroup (_t_frkPEmitterInfo* pInfo, char* pGroupName, t_frkVector3* pOffsetCoords);
extern int		frkPPropertyGetVolume (_t_frkPEmitterInfo* pInfo);
extern void		frkPPropertySetVolume (_t_frkPEmitterInfo* pInfo, int nVol);
extern int		frkPPropertyGetShape (_t_frkPEmitterInfo* pInfo);
extern void		frkPPropertySetShape (_t_frkPEmitterInfo* pInfo, int nShape);
extern t_frkMatrix4*	frkPPropertyGetMatrix(_t_frkPEmitterInfo* pInfo);
extern float	frkPPropertyGetMaxEmitterLife(_t_frkPEmitterInfo *pInfo);
extern int		frkPPropertyGetOrder (_t_frkPEmitterInfo* pInfo);
extern int		frkPPropertyGetFlagsEx(_t_frkPEmitterInfo* pInfo);

#define			frkPPropertyFlagPtr(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_NFLAGS))
#define			frkPPropertyScalePtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_SCALE))
#define			frkPPropertyRotPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_ROT ))
#define			frkPPropertyBlendPtr(pP) ((int*)((unsigned char*)(pP)+ OFFSET_T_FRKPEMITTERINFO_NEBLENDMODE))
#define			frkPPropertyTintPtr(pP) ((t_frkRGBA*)(((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_TINT)))
#define			frkPPropertyNumAssetsPtr(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_NASSETS))
#define			frkPPropertyCurAssetPtr(pP) (*(int**)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_PASSET))
#define			frkPPropertyAssetsPtr(pP)   (*(int**)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_AASSETS))

/* Asset API section */
extern int		frkPAssetGetType (_t_frkAssetInfo* pAsset);
extern char*	frkPAssetGetKey (_t_frkAssetInfo* pAsset);
extern char*	frkPAssetGetKeyFileName (_t_frkAssetInfo* pAsset);
extern void*	frkPAssetGetDataPointer (_t_frkAssetInfo* pAsset);
extern void		frkPAssetSetDataPointer (_t_frkAssetInfo* pAsset, void* pData);
extern t_frkRect2d* frkPAssetGetUVs (_t_frkAssetInfo* pAsset);

#define			frkPAssetDataPtr(pA) ((int*)((unsigned char*)(pA) + OFFSET_T_FRKASSETINFO_PASSET))
#define			frkPAssetKeyPtr(pA)	((char*)((unsigned char*)(pA) + 4))
#define			frkPAssetUVsPtr(pA)	((t_frkRect2d*)((unsigned char*)(pA) + 264))

#define			frkPAssetInfoUVsPtr(pA) ((t_frkRect2d*)((unsigned char*)(pA) + 4))
#define			frkPAssetInfoAssetPtr(pA, pI) ((*(unsigned char**)((unsigned char*)(pI) + OFFSET_T_FRKPEMITTERINFO_AASSETS)) + \
					OFFSET_T_FRKASSETINFO_SIZE * (*((int*)((unsigned char*)(pA)))))

/* Custom Data Chunk API section */
extern char*	frkPChunkGetKey (_t_frkPChunk* pChunk);
extern int		frkPChunkGetType (_t_frkPChunk* pChunk);
extern int		frkPChunkGetSize (_t_frkPChunk* pChunk);
extern int		frkPChunkGetVersion (_t_frkPChunk* pChunk);
extern void*	frkPChunkGetData (_t_frkPChunk* pChunk);
extern void		frkPCustomDataResetChunkTracer (_t_frkPEmitterInfo* pPropertyInfo);
extern void		frkPCustomDataIncChunkTracer (void);
extern _t_frkPChunk*	frkPCustomDataGetTracerChunk (_t_frkPEmitterInfo* pPropertyInfo);
/* PSB API section */
extern void		frkPSBPrepare(void* pPSBMem);
extern void		frkPSBAssociateAssets( void* pPackageDesc ,_t_frkPEffectLoadAssetCB UserAssetLoader, void* pCBUserData );
extern void		frkPSBPrepareEData(void* pPSBMem);
extern int		frkPSBGetVersion(void* pFileBuff);

extern _t_frkLdrChunk*	frkPSBChunkResetTracer(void *pPSBMem);
extern _t_frkLdrChunk*	frkPSBChunkIncTracer(_t_frkLdrChunk* pTracer);
extern _t_frkLdrChunk*	frkPSBChunkGetTracerItem(_t_frkLdrChunk* pTracer);

extern int			frkPSBChunkGetType(_t_frkLdrChunk* pTracer);
extern void*		frkPSBChunkGetData(_t_frkLdrChunk* pTracer);
extern char*		frkPSBChunkGetName(_t_frkLdrChunk* pTracer);
extern unsigned int	frkPSBChunkGetDataSize(_t_frkLdrChunk* pTracer);

/* Effect API Section */
extern int				 frkPEffectInfoCreate(_t_frkPEffectInfo** pPEffectInfo , void * pPSB);  
extern int				 frkPEffectInfoCreateEx(_t_frkPEffectInfo** pPEffectInfo , void * pPSB, _t_frkSDK* pSDK);
extern void				 frkPEffectInfoDestroy(_t_frkPEffectInfo **pPEffectInfo);
extern int				 frkPEffectCreate(_t_frkPEffect **pPEffectOut, const char* sName, _t_frkPEffectInfo* pPEffectInfo, t_frkMatrix4* pLcsWcs);
extern int				 frkPEffectCreateEx(_t_frkPEffect **pPEffectOut, const char* sName, _t_frkPEffectInfo* pPEffectInfo, t_frkMatrix4* pLcsWcs, _t_frkSDK* pSDK);
extern void				 frkPEffectSetCallback(_t_frkPEffect *pPEffect, int eCB, void* pCB  );
extern void				 frkPEffectReg(_t_frkPEffect *pPEffect , _t_frkPSystem* pPSystem );
extern void				 frkPEffectUnReg(_t_frkPEffect *pPEffect , _t_frkPSystem* pPSystem );
extern void				 frkPEffectRestart(_t_frkPEffect *pPEffect);
extern void				 frkPEffectProcess (_t_frkPEffect *pPEffect, float fTDelta);
extern void				 frkPEffectDestroy(_t_frkPEffect **pPEffect );
extern void				 frkPEffectAnmSetNoteCB(_t_frkPEffect *pPEffect, void* EventNoteCB );
extern void				 frkPEffectGetEmitters(_t_frkPEffect *pPEffect,int *nEmitterCount, _t_frkPEmitter** aEmitter[]);
extern void				 frkPEffectSetMatrix(_t_frkPEffect* pPEffect, t_frkMatrix4* pLcsWcs);
extern void				 frkPEffectInfoGetEmitterInfos(_t_frkPEffectInfo *pPEffectInfo,int *nEmitterInfoCount, _t_frkPEmitterInfo** aEmitterInfo[]);
extern void				 frkPEffectEmitterResetTracer (_t_frkPEffect* pPEffect);
extern void				 frkPEffectEmitterIncTracer (_t_frkPEffect* pPEffect);
extern _t_frkPEmitter*	 frkPEffectEmitterGetTracerItem (_t_frkPEffect* pPEffect);
extern t_frkMatrix4*     frkPEffectMatrixPtr(_t_frkPEffect* pPEffect);
extern _t_frkAnmInst*    frkPEffectGetEventAnmInst(_t_frkPEffect *pPEffect);
extern _t_frkPEffectInfo* frkPEffectGetEffectInfo(_t_frkPEffect *pEffect);
extern char*			 frkPEffectGetNamePtr(_t_frkPEffect *pEffect);
extern void				 frkPEffectSetScale (_t_frkPEffect* pPEffect, float fScale);
extern float			 frkPEffectGetScale (_t_frkPEffect* pEffect);
extern int				 frkPEffectEmitterAdd(_t_frkPEffect* pPEffect, _t_frkPEmitter *pInEmitter);
extern int				 frkPEffectEmitterRemove(_t_frkPEffect* pPEffect, _t_frkPEmitter *pInEmitter);
extern int				 frkPEffectAnmIsEnded(_t_frkPEffect* pPEffect);
extern int				 frkPEffectGetNumLive(_t_frkPEffect *pPEffect);
extern float			 frkPEffectGetMaxLife(_t_frkPEffect *pEffect);
extern int				 frkPEffectAnmIsLoop(_t_frkPEffect *pEffect);
extern void				 frkPEffectSimulate(_t_frkPEffect *pPEffect, float fSimTime, float fTick);

extern void				 frkPEffectInfoGetXRefName(_t_frkPEffectInfo *pPEffectInfo,int *pXRefCount, char** aXRefNames[]);
extern void				 frkPEffectInfoAddXRefInfo(_t_frkPEffectInfo *pPEffectInfo, _t_frkPEffectInfo *pXRefInfo);
extern void				 frkPEffectGetXRefEffects(_t_frkPEffect *pPEffect,int *pXRefCount, _t_frkPEffect** aPEffect[]);

extern int				 frkPEffectSetSpeed(_t_frkPEffect *pPEffect, float fSpeed);
extern void				 frkPEffectSetLife(_t_frkPEffect *pPEffect, float fLife);
extern int				 frkPEffectSetOneShot(_t_frkPEffect *pEffect, int nFlags);
extern int				 frkPEffectIsAlive(_t_frkPEffect *pEffect);
extern void				 frkPEffectSetState(_t_frkPEffect *pEffect, int nStateMask, int bSwitch);
extern void				 frkPEffectSetUserData(_t_frkPEffect *pEffect, void* pUsrData);
extern void				 frkPEffectGetUserData(_t_frkPEffect *pEffect, void** pUsrData);

/* Particle Buffers API section */
extern _t_frkPBuffer*	frkPBufferSet(_t_frkPSystem* pSys, int nBuffers, void* aBuffers, 
									  int nMaxEmittersPerBuffer, int nMaxParticlesPerBuffer);
extern void*	frkPBufferResetTracer (_t_frkPBuffer* pBuffer);
extern void*	frkPBufferEmitterIncTracer (void* pTracer);
extern void*	frkPBufferParticleIncTracer (void* pTracer);
extern int		frkPBufferGetState(_t_frkPBuffer* pBuffer);

#define 		frkPBufferGetNext(pB)(*(_t_frkPBuffer**)(((unsigned char*)(pB)) + 4))
#define 		frkPBufferSetState(pB, eState)(*(int*)(pB) = (eState))

#define 		frkPBufferEmitterFlagsPtr(pB)((int*)((unsigned char*)(pB) + 0))
#define 		frkPBufferEmitterNumParticlesPtr(pB)((int*)((unsigned char*)(pB) + 4))
#define 		frkPBufferEmitterBlendModePtr(pB)((int*)((unsigned char*)(pB) + 8))
#define 		frkPBufferEmitterAssetPtr(pB)((void**)((unsigned char*)(pB) + 12))
#define 		frkPBufferEmitterMatrixPtr(pB)((t_frkMatrix4*)((unsigned char*)(pB) + 16))
#define 		frkPBufferEmitterShapePtr(pB)((int*)((unsigned char*)(pB) + 80))

#define 		frkPBufferStatePtr(pB)((int*)((unsigned char*)(pB) + 0))
#define 		frkPBufferNumEmittersPtr(pB)((int*)((unsigned char*)(pB) + 8))

#define 		frkPBufferParticlePosPtr(pB)((t_frkVector4*)((unsigned char*)(pB) + 0))
#define 		frkPBufferParticleColorPtr(pB)((t_frkRGBA*)((unsigned char*)(pB) + 16))
#define 		frkPBufferParticleUVsPtr(pB)((t_frkRect2d*)((unsigned char*)(pB) + 32))
#define 		frkPBufferParticleScalePtr(pB)((t_frkVector4*)((unsigned char*)(pB) + 48))
#define 		frkPBufferParticleVelPtr(pB)((t_frkVector4*)((unsigned char*)(pB) + 64))
#define 		frkPBufferParticleAssetPtr(pB)((void**)((unsigned char*)(pB) + 80))
#define 		frkPBufferParticleRotPtr(pB)((t_frkVector4*)((unsigned char*)(pB) + 84))
#define			frkPBufferParticleJitterPtr(pB)((float*)((unsigned char*)(pB) + 100))
#define 		frkPBufferParticleUVs2Ptr(pB)((t_frkRect2d*)((unsigned char*)(pB) + 104))
/* Emitter LOD API section */
extern void		frkPLODSetParams(float fInterpRate, float fILOD, float fFLOD, float fLODCoeff);
extern void		frkPLODEnable(int bSwitch);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
