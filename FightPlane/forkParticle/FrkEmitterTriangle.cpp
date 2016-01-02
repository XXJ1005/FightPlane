/******************************************************************************
Module		: FrkEmitterTriangle Class
Overview	: The FrkEmitterTriangle class is derived from FrkEmitterShape class. 
It creates emitter with triangle shaped particles.

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

#include "FrkParticleSystem.h"
#include "FrkGeomDisplayList.h"
#include "FrkParticleEmitter.h"
#include "FrkEmitterShape.h"
#include "FrkEmitterTriangle.h"

/******************************************************************************
_Function	:	FrkEmitterTriangle Constructor
_Description:	Initializes and creates the vertex, color and texture 
coordinate arrays.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkEmitterTriangle::FrkEmitterTriangle()
{
	m_nLocalVertStart = -1;
	m_nLocalVertNum = 0;
	m_nNumIndices = 0;
	m_AxisUpV;
	m_AxisRightV;
	m_AxisRotV;
	m_nIndexBufferLockIndex = 0;
	m_nLocalNumSpr = 0;
}
/******************************************************************************
_Function	:	FrkEmitterTriangle::SubmitShape
_Description	:	Submit particle data to the triangle strip buffers.
_Arguments	:	> pEmitter: emitter being processed
pParticle : submitted particle
_Return		:	Status: -1 if not able to fill particle data else 0.
*/
/*****************************************************************************/
const int FrkEmitterTriangle::SubmitShape(_t_frkPEmitter* pEmitter, _t_frkParticle* pParticle)
{
	_t_frkPEmitterInfo* pInfo = (_t_frkPEmitterInfo*)(*(frkPEmitterInfoPtr(pEmitter)));
	_t_frkAssetInfo*  pAsset = NULL;
	pAsset = (_t_frkAssetInfo*)frkParticleAssetPtr(pParticle,pInfo);

	_t_frkvector2 t1, t2;
	t_frkRect2d* pUV = frkPAssetUVsPtr (pAsset);
	t1.x = pUV->x1;
	t1.y = pUV->y1;
	t2.x = pUV->x2;
	t2.y =pUV->y2;

	t_frkVector4* pPos = (t_frkVector4*)frkParticlePosPtr (pParticle);
	float fRotMin = frkDeg2Rad (*((float*)frkPPropertyRotPtr(pInfo)));
	float* fRot = (float*)(frkParticleRotPtr(pParticle));
	_t_frkvector2* pScale = (_t_frkvector2*)frkPPropertyScalePtr(pInfo);
	float* fScale = (float*)frkParticleScalePtr(pParticle);
	t_frkVector4* pColorTint = (t_frkVector4*)frkPPropertyTintPtr(pInfo);
	t_frkVector4* pColor = (t_frkVector4*)frkParticleColorPtr (pParticle);
	_t_frkvector2*  pTextCoord1 = &t1;
	_t_frkvector2*  pTextCoord2  = &t2;

	if(!FrkGeomDisplayList::GetInstance()->VertexBufferIsLocked())
	{
		FrkGeomDisplayList::GetInstance()->LockVertexBuffer();

		if(!FrkGeomDisplayList::GetInstance()->VertexBufferIsLocked())
			return 0;
	}

	if(m_nLocalVertStart == -1)	//need to be set
	{
		m_nLocalVertStart = FrkGeomDisplayList::GetInstance()->GetNumVertices();
		m_nLocalVertNum = 0;
		m_nNumIndices = 0;
	}

	t_frkMatrix4 RotMat;
	MatrixIdentity(&RotMat);
	MatrixRotationAngleAxis(&RotMat, &m_AxisRotV, *fRot + fRotMin);
	t_frkVector3 V0, V1, V2;


	t_frkVector3 VRight, VUp;
	MatrixVec3MulSub (&VRight, &m_AxisRightV, &RotMat);
	MatrixVec3MulSub (&VUp, &m_AxisUpV, &RotMat);
	Vec3Scale(&VRight, &VRight, (*fScale * 0.5f * pScale->x));;
	Vec3Scale(&VUp, &VUp, (*fScale * 0.5f * pScale->y)); 

	float fJitter = *frkParticleJitterPtr(pParticle);
	if(fJitter != 0.0f)
	{
		t_frkVector3 VnegRight;
		t_frkVector3 VnegUp;
		t_frkVector3 JitterVector = {0.0f, 0.0f, 0.0f};
		int nDirection = rand() % 4;
		
		Vec3Scale(&VnegRight, &VRight, -1.0f);
		Vec3Scale(&VnegUp, &VUp, -1.0f);

		Vec3Scale(&JitterVector, &JitterVector, fJitter);
		Vec3Normalize(&JitterVector, &((t_frkVector3) (nDirection < 2 ? ((nDirection == 0) ? VRight : VnegRight /*-VRight*/) : ((nDirection == 2) ? VUp : VnegUp/*-VUp*/))));
		Vec3Scale(&JitterVector, &JitterVector, fJitter);
		Vec3Add((t_frkVector3 *) pPos, (t_frkVector3 *) pPos, &JitterVector);
	}

	t_frkVector4 color;
	color.x = pColor->x * pColorTint->x;
	color.y = pColor->y * pColorTint->y;
	color.z = pColor->z * pColorTint->z;
	color.w = pColor->w * pColorTint->w;

	t_frkVector3 tempUp;
	Vec3Scale(&V0, &VUp, 0.577f);
	Vec3Add(&V0, &V0, pPos);
	Vec3Scale(&V1, &VRight, -0.5f);
	Vec3Scale(&tempUp, &VUp, -0.288f);
	Vec3Add(&V1, &V1, &tempUp);
	Vec3Add(&V1, &V1, pPos);
	Vec3Scale(&V2, &VRight, 0.5f);
	Vec3Scale(&tempUp, &VUp, -0.288f);
	Vec3Add(&V2, &V2, &tempUp);
	Vec3Add(&V2, &V2, pPos);

	FrkVertex *pVertex = (FrkVertex *) FrkGeomDisplayList::GetInstance()->m_pVertices;

	pVertex->Pos = V0;
	pVertex->Color = color;
	pVertex->UV.x = pTextCoord2->x;
	pVertex->UV.y = pTextCoord2->y;
	pVertex++;

	pVertex->Pos =  V1;
	pVertex->Color = color;
	pVertex->UV.x = pTextCoord1->x;
	pVertex->UV.y = pTextCoord2->y;
	pVertex++;

	pVertex->Pos =  V2;
	pVertex->Color = color;
	pVertex->UV.x	= pTextCoord1->x;
	pVertex->UV.y	= pTextCoord1->y;
	pVertex++;

	FrkGeomDisplayList::GetInstance()->m_pVertices = pVertex;
	m_nNumIndices += 3;
	m_nLocalVertNum += 3;
	FrkGeomDisplayList::GetInstance()->SetNumVertices(FrkGeomDisplayList::GetInstance()->GetNumVertices() + 3);
	m_nLocalNumSpr++;

	return 0;
}
/******************************************************************************
_Function	:	FrkEmitterTriangle::SubmitShape
_Description	:	Submit particle data to the triangle strip buffers.
_Arguments	:	> pEmitter: buffer for emitter being processed
pParticle : buffer for submitted particle
_Return		:	Status: -1 if not able to fill particle data else 0.
*/
/*****************************************************************************/
const int FrkEmitterTriangle::SubmitShape(void* pBufferEmitter, void* pBufferParticle)
{
	_t_frkvector2 t1, t2;
	t_frkRect2d* pUV = frkPBufferParticleUVsPtr (pBufferParticle);
	t1.x = pUV->x1;
	t1.y = pUV->y1;
	t2.x = pUV->x2;
	t2.y =pUV->y2;

	t_frkVector4* pPos = (t_frkVector4*)frkPBufferParticlePosPtr (pBufferParticle);

	float* fRot = (float*)(frkPBufferParticleRotPtr(pBufferParticle));

	float* fScale = (float*)frkPBufferParticleScalePtr(pBufferParticle);

	t_frkVector4* pColor = (t_frkVector4*)frkPBufferParticleColorPtr (pBufferParticle);
	_t_frkvector2*  pTextCoord1 = &t1;
	_t_frkvector2*  pTextCoord2  = &t2;
	
	float fRotMin = 0;
	t_frkVector2 Scale;
	Scale.x = 1.0f; 
	Scale.y = 1.0f;

	t_frkVector2* pScale = &Scale;
	t_frkVector4 ColorTint;
	ColorTint.w = 1.0f;
	ColorTint.x = 1.0f;
	ColorTint.y = 1.0f;
	ColorTint.z = 1.0f;
	t_frkVector4* pColorTint = &ColorTint;

	if(!FrkGeomDisplayList::GetInstance()->VertexBufferIsLocked())
	{
		FrkGeomDisplayList::GetInstance()->LockVertexBuffer();

		if(!FrkGeomDisplayList::GetInstance()->VertexBufferIsLocked())
			return 0;
	}

	if(m_nLocalVertStart == -1)	//need to be set
	{
		m_nLocalVertStart = FrkGeomDisplayList::GetInstance()->GetNumVertices();
		m_nLocalVertNum = 0;
		m_nNumIndices = 0;
	}

	t_frkMatrix4 RotMat;
	MatrixIdentity(&RotMat);
	MatrixRotationAngleAxis(&RotMat, &m_AxisRotV, *fRot + fRotMin);
	t_frkVector3 V0, V1, V2;
	
	t_frkVector3 VRight, VUp;
	MatrixVec3MulSub (&VRight, &m_AxisRightV, &RotMat);
	MatrixVec3MulSub (&VUp, &m_AxisUpV, &RotMat);
	Vec3Scale(&VRight, &VRight, (*fScale * 0.5f * pScale->x));;
	Vec3Scale(&VUp, &VUp, (*fScale * 0.5f * pScale->y)); 

	float fJitter = *frkParticleJitterPtr(pBufferParticle);
	if(fJitter != 0.0f)
	{
		t_frkVector3 VnegRight;
		t_frkVector3 VnegUp;
		t_frkVector3 JitterVector = {0.0f, 0.0f, 0.0f};
		int nDirection = rand() % 4;
		
		Vec3Scale(&VnegRight, &VRight, -1.0f);
		Vec3Scale(&VnegUp, &VUp, -1.0f);

		Vec3Scale(&JitterVector, &JitterVector, fJitter);
		Vec3Normalize(&JitterVector, &((t_frkVector3) (nDirection < 2 ? ((nDirection == 0) ? VRight : VnegRight /*-VRight*/) : ((nDirection == 2) ? VUp : VnegUp/*-VUp*/))));
		Vec3Scale(&JitterVector, &JitterVector, fJitter);
		Vec3Add((t_frkVector3 *) pPos, (t_frkVector3 *) pPos, &JitterVector);
	}

	t_frkVector4 color;
	color.x = pColor->x * pColorTint->x;
	color.y = pColor->y * pColorTint->y;
	color.z = pColor->z * pColorTint->z;
	color.w = pColor->w * pColorTint->w;

	t_frkVector3 tempUp;
	Vec3Scale(&V0, &VUp, 0.577f);
	Vec3Add(&V0, &V0, pPos);
	Vec3Scale(&V1, &VRight, -0.5f);
	Vec3Scale(&tempUp, &VUp, -0.288f);
	Vec3Add(&V1, &V1, &tempUp);
	Vec3Add(&V1, &V1, pPos);
	Vec3Scale(&V2, &VRight, 0.5f);
	Vec3Scale(&tempUp, &VUp, -0.288f);
	Vec3Add(&V2, &V2, &tempUp);
	Vec3Add(&V2, &V2, pPos);

	FrkVertex *pVertex = (FrkVertex *) FrkGeomDisplayList::GetInstance()->m_pVertices;

	pVertex->Pos = V0;
	pVertex->Color = color;
	pVertex->UV.x = pTextCoord2->x;

	pVertex->UV.y = pTextCoord2->y;
	pVertex++;

	pVertex->Pos =  V1;
	pVertex->Color = color;
	pVertex->UV.x = pTextCoord1->x;
	pVertex->UV.y = pTextCoord2->y;
	pVertex++;

	pVertex->Pos =  V2;
	pVertex->Color = color;
	pVertex->UV.x	= pTextCoord1->x;
	pVertex->UV.y	= pTextCoord1->y;
	pVertex++;

	FrkGeomDisplayList::GetInstance()->m_pVertices = pVertex;
	m_nNumIndices += 3;
	m_nLocalVertNum += 3;
	FrkGeomDisplayList::GetInstance()->SetNumVertices(FrkGeomDisplayList::GetInstance()->GetNumVertices() + 3);
	m_nLocalNumSpr++;

	return 0;
}
/******************************************************************************
_Function	:	FrkEmitterTriangle::SetQuadAxis
_Description:	Set Facing vectors of Sprite.
_Arguments	:	> Up: Sprite up axis.
> Right: Sprite right Vector.
> Rot: Sprite rotation axis.
_Return		:	None.
*/
/*****************************************************************************/
const int FrkEmitterTriangle::SetQuadAxis(const t_frkVector3& Up, const t_frkVector3& Right, const t_frkVector3& Rot)
{
	m_AxisUpV = Up;
	m_AxisRightV = Right;
	m_AxisRotV = Rot;

	return 0;
}
/******************************************************************************
_Function	:	FrkEmitterDiamond::GetQuadAxis
_Description:	Get Facing vectors of Sprite.
_Arguments	:	> Up: Sprite up axis.
> Right: Sprite right Vector.
> Rot: Sprite rotation axis.
_Return		:	None.
*/
/*****************************************************************************/
void FrkEmitterTriangle::GetQuadAxis(t_frkVector3& Up, t_frkVector3& Right, t_frkVector3& Rot)
{
	Up = m_AxisUpV;
	Right = m_AxisRightV;
	Rot = m_AxisRotV;
}
/******************************************************************************
Function	:	ParticleSprite::RenderParticles
Description	:	Render the Sprite System
Arguments	:	None.
Return		:	None.
/*****************************************************************************/
void FrkEmitterTriangle::RenderParticles()
{
	if(FrkGeomDisplayList::GetInstance()->VertexBufferIsLocked())
		FrkGeomDisplayList::GetInstance()->UnlockVertexBuffer();

	if (m_nLocalVertNum == 0)
		return;

	if(m_nLocalVertStart == -1)
		return;

	if (!glIsEnabled(GL_TEXTURE_2D))
		glEnable(GL_TEXTURE_2D);

	if (!glIsEnabled(GL_TEXTURE_COORD_ARRAY))
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(FrkVertex), &(((FrkVertex*) FrkGeomDisplayList::GetInstance()->m_pVertexBuffer)->Pos));
	glColorPointer (4, GL_FLOAT, sizeof(FrkVertex), &(((FrkVertex*) FrkGeomDisplayList::GetInstance()->m_pVertexBuffer)->Color));
	glTexCoordPointer(2, GL_FLOAT, sizeof(FrkVertex), &(((FrkVertex*) FrkGeomDisplayList::GetInstance()->m_pVertexBuffer)->UV));
	glDrawArrays( GL_TRIANGLES, 0, m_nLocalVertNum );

	m_nLocalVertStart = -1;
	m_nLocalNumSpr = 0;
}
