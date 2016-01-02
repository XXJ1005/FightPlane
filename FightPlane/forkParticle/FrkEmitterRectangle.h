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
#ifndef FRKEMITTERRECTANGLE_H
#define FRKEMITTERRECTANGLE_H

#include "FrkEmitterShape.h"

/************************************************************************/
//	Class:			FrkEmitterRectangle
//	Description:	Holds the Rectangle Shaped particle emitter object.
/************************************************************************/
class FrkEmitterRectangle : public FrkEmitterShape
{
public:
	FrkEmitterRectangle();

	virtual const int SubmitShape(_t_frkPEmitter* pEmitter, _t_frkParticle* pParticle );
	virtual const int SubmitShape(void* pBufferEmitter, void* pBufferParticle);
	virtual const int SetQuadAxis(const t_frkVector3& Up, const t_frkVector3& Right, const t_frkVector3& Rot);
	virtual void GetQuadAxis(t_frkVector3& Up, t_frkVector3& Right, t_frkVector3& Rot);
	virtual void RenderParticles();
protected:
	int m_nLocalVertStart;
	int m_nLocalVertNum;
	int	m_nNumIndices;
	int m_nIndexBufferLockIndex;
	// For Emitter Facing
	t_frkVector3				m_AxisUpV;
	t_frkVector3				m_AxisRightV;
	t_frkVector3				m_AxisRotV;
};

#endif
