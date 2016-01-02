/******************************************************************************
	Module		: Particle Stuio Plugin: Custom Data
	Version		: 1.0
	Overview	: The custom data  plugin provides the API to attach customized data  
				  to an emitter in particle studio.

  (c) Copyright 2004-2005 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#pragma once
#include "StdAfx.h"
#include "frkpsinterface.h"

class frkPluginCustomData
{	
public:
/******************************************************************************
Function	:	frkPluginCustomData::Init
Description	:	Called right after the plugin has been loaded to pass required data
Arguments	:	> pEditFocus: Pointer to the studio keyboard accelerator enable/diable varaible
				> pPSInterface: Pointer to particle studio API interface
Return		:	None
*/
/****************************************************************************/
	virtual void Init(bool* pEditFocus, frkPSInterface* pPSInterface) = 0;
/******************************************************************************
Function	:	frkPluginCustomData::RegisterGUI
Description	:	Called whenever the custom GUI is to be displayed. Returns the pointer to the custom data dialog.
Arguments	:	> pDialog: Returns the dialog in this pointer.
                > pCustomData: pointer to custom data. 
Return		:	1 if Dialog was registered. 0 otherwise.
*/
/*****************************************************************************/
  	virtual int RegisterGUI(CWnd** pDialog, void *pCustomData, _t_frkpemitter *pEmitter) = 0;

/******************************************************************************
Function	:	frkPluginCustomData::RegisterCustomDataCallback
Description	:	Registers the custom data type for which emitter loaded and smitter saved functions will be called.
Arguments	:	> pCBType: Returns the type of the custom data.
Return		:	1 if a callback type was registered, 0 if not.
*/
/*****************************************************************************/
	virtual int RegisterCustomDataCallback(int* pCBType) = 0;
/******************************************************************************
Function	:	frkPluginCustomData::EmitterCreated
Description	:	Whenever an emitter is created in the studio, this is called so that the plugin can attach data to the emitter.
Arguments	:	> pType: Type of custom data
                > pVersion: Version of custom data
                > pDataSize: Size of data to be attached.
                > pCustomData: pointer to custom data. 
Return		:	1 if data is attached. 0 if no data is attached.
*/
/*****************************************************************************/
	virtual int EmitterCreated(int* pType,int* pVersion,int* pDataSize,void** pCustomData,  _t_frkpemitter *pEmitter) = 0;
/******************************************************************************
Function	:	frkPluginCustomData::EmitterLoaded
Description	:	Funtion to pass custom data to the plugin for which the callback was registered. 
Arguments	:	> pType: Type of custom data
                > pVersion: Version of custom data
                > pDataSize: Size of data to be attached.
                > pCustomData: pointer to custom data. 
Return		:	None.
*/
/*****************************************************************************/
	virtual void EmitterLoaded(int nType,int nVersion,int nDataSize,void* pCustomData,  _t_frkpemitter *pEmitter) = 0;
/******************************************************************************
Function	:	frkPluginCustomData::EmitterSaved
Description	:	Whenever an emitter is about to be saved, this is called to update the custom data.
Arguments	:	> pType: Type of custom data
                > pVersion: Version of custom data
                > pDataSize: Pointer to size of data to be attached.
                > pCustomData: pointer to custom data pointer. 
Return		:	None.
*/
/*****************************************************************************/
	virtual void EmitterSaved(int nType,int nVersion,int* pDataSize,void** pCustomData, _t_frkpemitter *pEmitter) = 0;
/******************************************************************************
Function	:	frkPluginCustomData::ConvertData
Description	:	Converts from an older version of the custom data to the new one.
Arguments	:	> pData: Pointer to the old custom data
				> nVersion: Version of old custom data
				> pNewData: Pointer that is filled with the new converted data.
Return		:	None.
*/
/*****************************************************************************/
	virtual void ConvertData(void *pData, int nVersion, void *pNewData) = 0;

/******************************************************************************
Function	:	frkPluginCustomData::GetCurrentVersionInfo
Description	:	Retrieves the size and version number of current version data structure
Arguments	:	> pDataVersion: Pointer to data version for output.
				> pDataSize: Pointer to custom data size for output.
Return		:	None.
*/
/*****************************************************************************/
	virtual void GetCurrentVersionInfo(int* pDataVersion, int* pDataSize) = 0;

/*****************************************************************************/
};
