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
#ifndef FRKGEOMDISPLAYLIST_H
#define FRKGEOMDISPLAYLIST_H


#include "frksdk.h"
#include "frkmath.h"
#include "frkptuner.h"
#include "FrkDataServer.h"
#include "FrkParticleSystem.h"
#include "FrkParticleEmitter.h"


class FrkVertex 
{
public:
	t_frkVector3	Pos;
	t_frkVector4	Color;
	_t_frkvector2	UV;
};

class FrkNonTexVertex 
{
public:
	t_frkVector3 Pos;
	t_frkVector4 Color;
};

#define INDEX_BUFFER_IS_NOTSET 0
#define INDEX_BUFFER_IS_STRING 1
#define INDEX_BUFFER_IS_POINT 1		//same as above, because both use same index buffer values
#define INDEX_BUFFER_IS_TRIANGLE 2
#define INDEX_BUFFER_IS_DIAMOND 3
#define INDEX_BUFFER_IS_RECTANGLE 3		//same as above, because both use same index buffer values
#define INDEX_BUFFER_IS_MODEL 4	

struct  ParticleEmitterRenderInfo
{
	float fRotMin;
	float fRot;
    float fScale; 
	
	t_frkVector4*  pColorTint;
	t_frkVector4*  pColor; 
	
	_t_frkvector2* pScale;
	_t_frkvector2* pTextCoord1;
	_t_frkvector2* pTextCoord2;
	
	t_frkVector4* pPos;

	ParticleEmitterRenderInfo()
	{	
		fRotMin = fRot = fScale = 0.0f; 

		pColorTint	= NULL;
		pColor		= NULL;
		pScale		= NULL;
		pTextCoord1 = NULL;
		pTextCoord2 = NULL;
		pPos		= NULL;
	}
};
/************************************************************************/
//	Class:			FrkGeomDisplayList
//	Description:	Holds the Event Track Related common functions.
/************************************************************************/
class FrkGeomDisplayList
{

public:
		static FrkGeomDisplayList *s_Instance; 

		static FrkGeomDisplayList* GetInstance()
		{
			if (!s_Instance)
			{
				s_Instance = new FrkGeomDisplayList;
				return s_Instance;
			}
			return s_Instance;
		}

		static void DestroyInstance()
		{
			if (s_Instance)
			{
				delete s_Instance;
				s_Instance = NULL;
			}
		}
private:

		FrkGeomDisplayList();
	   ~FrkGeomDisplayList();
public:	   //BufferData
	   void* m_pVertexBuffer;
	   void *m_pIndexBuffer;

	   int m_nNumVertices;
	   bool m_bVertexBufferIsLocked;
	   int m_nIndexBufferState;
	
		FrkVertex *m_pVertices;

		const int GetNumVertices() const { return m_nNumVertices; }

		void SetNumVertices(const int& NumVertices) { m_nNumVertices = NumVertices; }

		const bool VertexBufferIsLocked() const { return m_bVertexBufferIsLocked; }

		void LockVertexBuffer();
		void UnlockVertexBuffer();

		const int GetIndexBufferState() const { return m_nIndexBufferState; }
		void SetIndexBufferState(const int& nIndexBufferState) { m_nIndexBufferState = nIndexBufferState; }
};


#endif
