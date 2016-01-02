/******************************************************************************
	Module		: Particle Stuio Plugin: Import Export
	Version		: 
	Overview	: The particle dynamics plugin provides the API to import
				  or export data 	

  (c) Copyright 2004-2005 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#pragma once

#include "frkpsinterface.h"

#define IMEXPLUGIN_MAX_MENUITEMS		8
#define IMEXPLUGIN_MAX_MENUSTRING		64
/******************************************************************************
Function	:	MenuCB
Description	:	Exports the data in a file.
Arguments	:	> pEmitters: An array of pointers to selected emitters in the studio
				> nNumEmitters: The number of elements in the pEmitters array..
Return		:	None.
*/
/*****************************************************************************/
typedef void (*MenuCB) (_t_frkpemitter **pEmitters, char **sEmitterNames, int nNumEmitters);

class frkPluginImportExport
{
public:
/******************************************************************************
Function	:	frkPluginImportExport::Init
Description	:	Called right after the plugin has been loaded to pass required data
Arguments	:	> pPSInterface: Pointer to particle studio API interface
Return		:	None
*/
/****************************************************************************/
	virtual void Init(frkPSInterface* pPSInterface) = 0;
/******************************************************************************
Function	:	frkPluginImportExport::RegisterMenus
Description	:	Gets the terminology to use in the studio for the menu option. Maximum string length 256.
Arguments	:	> pOutMenuTexts: Array to be filled with menu items strings
				> pOutCBs:	Array of callback functions for the menu items
				> nMaxItems: Maximum number of items that can be registered
				> pOutItems: Pointer to integer that returns the number of items registered
Return		:	0 if no menu is registered, 1 if menu has been registered
*/
/*****************************************************************************/
	virtual int RegisterMenus (char pOutMenuTexts[IMEXPLUGIN_MAX_MENUITEMS][IMEXPLUGIN_MAX_MENUSTRING], MenuCB pOutCBs[IMEXPLUGIN_MAX_MENUITEMS], int* pOutItems) = 0;
/******************************************************************************
Function	:	frkPluginImportExport::GetTerminology
Description	:	Gets the terminology to use in the studio for the menu option.
Arguments	:	None.
Return		:	A pointer to a string carrying the name of the menu option.
*/
/*****************************************************************************/
    virtual char* GetTerminology() = 0;
};
