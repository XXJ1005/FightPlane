/******************************************************************************
Module		: FrkTrackEvent Class
Overview	: THolds the Event Track Related common functions.

Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#include "FrkGeomDisplayList.h"

FrkGeomDisplayList* FrkGeomDisplayList::s_Instance = NULL;
/******************************************************************************
_Function	:	FrkGeomDisplayList Constructor
_Description:	Initializes and creates the Track & Instance

_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkGeomDisplayList::FrkGeomDisplayList()
{
	m_nNumVertices = 0;
	m_bVertexBufferIsLocked = false;
	m_nIndexBufferState = INDEX_BUFFER_IS_NOTSET;
	m_pVertices = NULL;

	m_pIndexBuffer  = malloc(MAX_PS_PARTICLES * 6 * sizeof(size_t));
	m_pVertexBuffer = malloc(MAX_PS_PARTICLES * 4 * sizeof(FrkVertex));
}
/*****************************************************************************/
FrkGeomDisplayList::~FrkGeomDisplayList()
{
	if(m_pIndexBuffer)
		free(m_pIndexBuffer);

	if(m_pVertexBuffer)
		free(m_pVertexBuffer);
}
/*****************************************************************************/

void FrkGeomDisplayList::LockVertexBuffer()
{
	m_pVertices = (FrkVertex *)m_pVertexBuffer;
	m_bVertexBufferIsLocked = true;
}
/*****************************************************************************/
void FrkGeomDisplayList::UnlockVertexBuffer()
{
	//if(VertexBufferIsLocked())
	//{
		//m_pVertexBuffer->Unlock();
	//}
	m_bVertexBufferIsLocked = false;
}
/*****************************************************************************/

