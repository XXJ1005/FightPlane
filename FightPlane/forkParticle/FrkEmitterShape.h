/*******************************************************************************
Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/*******************************************************************************/
#pragma once
#ifndef FRKEMITTERSHAPE_H
#define FRKEMITTERSHAPE_H

#include "frkmath.h"
class FrkParticleEmitter;
/************************************************************************/
//	Class:			FrkEmitterShape
//	Description:	Emitter Shape class Declaration.
//************************************************************************/
class FrkEmitterShape
{
public:
	FrkEmitterShape(){}
	virtual ~FrkEmitterShape(){}
	virtual const int SubmitShape(_t_frkPEmitter* pEmitter, _t_frkParticle* pParticle){return 0;}
	virtual const int SubmitShape(void* pBufferEmitter, void* pBufferParticle) = 0;
		virtual const int SetQuadAxis(const t_frkVector3& Up, const t_frkVector3& Right, const t_frkVector3& Rot){return 0;}
		virtual void GetQuadAxis(t_frkVector3& Up, t_frkVector3& Right, t_frkVector3& Rot) { };
		virtual void RenderParticles(){}
};

#endif
