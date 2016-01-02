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

#include "FrkTrackEvent.h"


/******************************************************************************
_Function	:	FrkTrackEvent Constructor
_Description:	Initializes and creates the Track & Instance

_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkTrackEvent::FrkTrackEvent(){
	m_pEventsAnmInst = NULL;
	m_pEventsAnmTrk  = NULL;
}
/******************************************************************************
_Function	:	FrkTrackEvent Destructor
_Description:	Initializes and creates the Track & Instance

_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkTrackEvent::~FrkTrackEvent()
{

}
/*****************************************************************************/
int FrkTrackEvent::Create(char *sFileName,void *pPackage)
{
	_t_frkAnmTrk* pTrk;
	pTrk = FrkDataServer::GetInstance()->LoadNoteTrkFromPackage(sFileName, pPackage);

	if(!pTrk)	//if event track was not in the package file , see if user wanted to load it from a trk file
		pTrk = FrkDataServer::GetInstance()->LoadNoteTrkFile(sFileName);

	if(!pTrk)	//if all else fails
		return -1;

	_t_frkAnmInst* pEventAnmInstTemp;

	pEventAnmInstTemp = (_t_frkAnmInst*)malloc (frkPAnmGetInstMemSize() );
	frkPAnmInit (pEventAnmInstTemp, NULL);

	

	m_pEventsAnmTrk  = pTrk;
	m_pEventsAnmInst = pEventAnmInstTemp;
	
	if (m_pEventsAnmInst == NULL || m_pEventsAnmTrk == NULL)
		return -1;

	frkPAnmSet (m_pEventsAnmInst, m_pEventsAnmTrk);
	frkPAnmSetLoop(m_pEventsAnmInst, 1 );	

	return 0;
}
/******************************************************************************
_Function	:	FrkTrackEvent::Destroy
_Description:	Destroys the event track instance
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
void FrkTrackEvent::Destroy()
{
//	remove event track and anim instance
 	if(m_pEventsAnmInst)
 	{
 		free(m_pEventsAnmInst);
 		m_pEventsAnmInst = NULL;
 	}
 
 	if(m_pEventsAnmTrk)
 	{
 		free(m_pEventsAnmTrk);
 		m_pEventsAnmTrk = NULL;
 	}

}
/******************************************************************************
_Function	:	FrkTrackEvent::EventNoteCB
_Description:	Event note Callback functions
_Arguments	:	pAnmInst	: Animation instance
				pNote		: The fired note
_Return		:	None.
*/
/*****************************************************************************/
int FrkTrackEvent::EventNoteCB (_t_frkAnmInst* pAnmInst, _t_frkPNote* pNote)
{
 	char sBuff[256];
 	strcpy(sBuff, "Printing Note Data: ");
 	strcat(sBuff, frkPAnmNoteGetData(pNote) );
 
 	return 0;
}
/******************************************************************************
_Function	:	FrkTrackEvent::Process
_Description:	Assign event processing data to the event animation isntance.
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/

void FrkTrackEvent::Process()
{
	frkAnmSetNoteCB (m_pEventsAnmInst,EventNoteCB ,NULL ); //Call this in dempoapp
}
