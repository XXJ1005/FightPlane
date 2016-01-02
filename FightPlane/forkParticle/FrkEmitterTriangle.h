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
#ifndef FRKEMITTERTRIANGLE_H
#define FRKEMITTERTRIANGLE_H

//#include <d3dx9.h>

#include "FrkEmitterShape.h"

/************************************************************************/
//	Class:			FrkEmitterTriangle
//	Description:	Holds the Triangle Shaped particle emitter object.
/************************************************************************/
class FrkEmitterTriangle : public FrkEmitterShape
{
public:
	FrkEmitterTriangle();

	virtual const int SubmitShape(_t_frkPEmitter* pEmitter, _t_frkParticle* pParticle);
	virtual const int SubmitShape(void* pBufferEmitter, void* pBufferParticle);
	virtual const int SetQuadAxis(const t_frkVector3& Up, const t_frkVector3& Right, const t_frkVector3& Rot);
	virtual void GetQuadAxis(t_frkVector3& Up, t_frkVector3& Right, t_frkVector3& Rot);
	virtual void RenderParticles();
protected:
	int m_nLocalVertStart;
	int m_nLocalVertNum;
	int	m_nNumIndices;
	int m_nLocalNumSpr;

	int m_nIndexBufferLockIndex;
	const bool PrepareAndSetIndexBuffer();

	// For Emitter Facing
	t_frkVector3 m_AxisUpV;
	t_frkVector3 m_AxisRightV;
	t_frkVector3 m_AxisRotV;
};

#endif
