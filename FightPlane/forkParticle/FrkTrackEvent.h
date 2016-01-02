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
#ifndef FRKTRACKEVENT_H
#define FRKTRACKEVENT_H

//#include <d3dx9.h>
#include "frksdk.h"
#include "frkmath.h"
#include "frkptuner.h"
#include "FrkDataServer.h"
#include "FrkParticleSystem.h"
#include "FrkParticleEmitter.h"


/************************************************************************/
//	Class:			FrkTrackEvent
//	Description:	Holds the Event Track Related common functions.
/************************************************************************/
class FrkTrackEvent
{
	
	public:
		static int EventNoteCB (_t_frkAnmInst*, _t_frkPNote*);
		int Create(char *, void *);
		void Destroy();
		void Process();

	_t_frkAnmInst* m_pEventsAnmInst;
	_t_frkAnmTrk*  m_pEventsAnmTrk;

	 FrkTrackEvent();
	~FrkTrackEvent();
	
};

#endif
