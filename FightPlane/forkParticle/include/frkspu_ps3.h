/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2009 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef frkspu_ps3_h
#define frkspu_ps3_h

#include "frkpoffsets.h"

typedef struct _t_frkpemitterinfo	_t_frkPEmitterInfo;
typedef struct _t_frkpemitter		_t_frkPEmitter;
typedef struct _t_frkparticle		_t_frkParticle;
typedef struct _t_frkps3spuarg		_t_frkps3SPUArg;
typedef struct _t_frkassetinfo		_t_frkAssetInfo;

/*****************************************************************************/
/* PS3 SPU (LIMITED) API */
/*****************************************************************************/

/* Emitter Info Property Flag Bits */
#define frkPSYSTEM_PROPERTYBIT_PANIMRANDOM		0x00000001
#define frkPSYSTEM_PROPERTYBIT_PANIMFLIPBOOK	0x00000002
#define frkPSYSTEM_PROPERTYBIT_PANIMRNDFIRST	0x00000004
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISX		0x00000008
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISY		0x00000010
#define frkPSYSTEM_PROPERTYBIT_FACINGWAXISZ		0x00000020
#define frkPSYSTEM_PROPERTYBIT_FACINGEMITTER	0x00000040
#define frkPSYSTEM_PROPERTYBIT_LIGHTEMITTER		0x00000080
#ifndef SDK_LITE
#define frkPSYSTEM_PROPERTYBIT_PATHPARTICLE		0x00000100
#define frkPSYSTEM_PROPERTYBIT_PATHEMITTER		0x00000200
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRAL		0x00000400
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALA		0x00000800
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALX		0x00001000
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALY		0x00002000
#define frkPSYSTEM_PROPERTYBIT_PATHSPIRALZ		0x00004000
#define frkPSYSTEM_PROPERTYBIT_PATHBIRTH		0x00008000
#endif
#define frkPSYSTEM_PROPERTYBIT_REFEMITTER		0x00010000
#define frkPSYSTEM_PROPERTYBIT_PARTICLEETRANS	0x00020000
#define frkPSYSTEM_PROPERTYBIT_PANIMNOLOOP		0x00040000
#ifndef SDK_LITE
#define frkPSYSTEM_PROPERTYBIT_FACINGERADIAL	0x00080000
#endif
#define frkPSYSTEM_PROPERTYBIT_INFINITELOOP		0x00100000
#define frkPSYSTEM_PROPERTYBIT_DIRECTIONAL1		0x00200000
#define frkPSYSTEM_PROPERTYBIT_DIRECTIONAL2		0x00400000
#ifndef SDK_LITE
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALX		0x00800000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALY		0x01000000
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALZ		0x02000000
#endif
#define frkPSYSTEM_PROPERTYBIT_FACINGAXIALVEL	0x04000000
#ifndef SDK_LITE
#define frkPSYSTEM_PROPERTYBIT_SHAPERECT		0x08000000
#endif
#define frkPSYSTEM_PROPERTYBIT_INFINITEFOR		0x10000000
#define frkPSYSTEM_PROPERTYBIT_INFINITEFROZEN	0x20000000
#define frkPSYSTEM_PROPERTYBIT_SHAPESTRING		0x40000000
#define frkPSYSTEM_PROPERTYBIT_NOLOD			0x80000000


extern _t_frkps3SPUArg*		frkSPUArgGet(CellSpursJobContext2 *jobContext, CellSpursJob256 *job256);
extern void*				frkSPUArgGetUserData(_t_frkps3SPUArg* pArg);
#define						frkSPUArgPBuffer(jc)((jc)->ioBuffer)
#define						frkSPUArgDMATag(jc)((jc)->dmaTag)

/* Emitter API Section */
#define			frkPEmitterNamePtr(pE)((char*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_SNAME))
#define			frkPEmitterFlagPtr(pE) ((int*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_NFLAGS))
#define			frkPEmitterMatrixPtr(pE) ((t_frkMatrix4*)((unsigned char*)(pE) + OFFSET_T_FRKPEMITTER_LCSWCS))
#define			frkPEmitterInfoPtr(pP) (((void**)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTER_PINFO)))

/* Particle API Section */
extern void		frkParticleProcess(_t_frkps3SPUArg* pArg, void* pParticleBuffer, uint32_t dmaTag);
extern void				frkParticleResetTracer(_t_frkps3SPUArg* pArg, void* pParticleBuffer);
extern void				frkParticleIncTracer();
extern _t_frkParticle*	frkParticleGetTracerItem();
extern int				frkParticleIsAlive(_t_frkParticle* pParticle);

#define			frkParticleTimePtr(pP) (float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FTIME + 16)
#define			frkParticlePosPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_POS + 16))		
#define			frkParticleVelPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_VEL + 16))		
#define			frkParticleColorPtr(pP) ((t_frkRGBA*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_COLOR + 16))		
#define			frkParticleLifePtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FLIFE + 16))		
#define			frkParticleScalePtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FSCALE + 16))		
#define			frkParticleRotPtr(pP) ((float*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_FROT + 16))		
#define			frkParticleAssetIdx(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_NASSETIDX + 16))		
#define			frkParticleEmitterInfoPtr(pP) (*((_t_frkPEmitterInfo**)&(((unsigned char*)(pP))[124 + 16])))
_t_frkPEmitter* frkParticleEmitterPtr(_t_frkParticle* pParticle, unsigned int dmaTag);
#define			frkParticleAssetPtr(pP, pI) ((*(int**)((unsigned char*)(pI) + OFFSET_T_FRKPEMITTERINFO_AASSETS)) + \
					288 * (*((int*)((unsigned char*)(pP) + OFFSET_T_FRKPARTICLE_NASSETIDX + 16))))

/* Property API section */
#define			frkPPropertyFlagPtr(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_NFLAGS))
#define			frkPPropertyScalePtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_SCALE))
#define			frkPPropertyRotPtr(pP) ((t_frkVector4*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_ROT ))
#define			frkPPropertyBlendPtr(pP) ((int*)((unsigned char*)(pP)+ OFFSET_T_FRKPEMITTERINFO_NEBLENDMODE))
#define			frkPPropertyTintPtr(pP) ((t_frkRGBA*)(((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_TINT)))
#define			frkPPropertyNumAssetsPtr(pP) ((int*)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_NASSETS))
#define			frkPPropertyAssetsPtr(pP)   (*(int**)((unsigned char*)(pP) + OFFSET_T_FRKPEMITTERINFO_AASSETS))

/* Asset API section */
#define			frkPAssetKeyPtr(pA)	((char*)((unsigned char*)(pA) + 4))
#define			frkPAssetUVsPtr(pA)	((t_frkRect2d*)((unsigned char*)(pA) + 264))

/*****************************************************************************/
#endif

