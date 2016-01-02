/******************************************************************************
	Module		: Particle Studio Interface API
	Version		: 1.0
	Overview	: The Particle Studio Interface API provides for external plugins
				  to interface with Particle Studio and access data information.

  (c) Copyright 2004-2008 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#pragma once

class frkPSInterface
{
public:
	frkPSInterface(){};
	~frkPSInterface() {};
/******************************************************************************
Function	:	frkPSInterface::GetAssetFilePath
Description	:	Retrieves file path for an asset.
Arguments	:	> sAsset : Pointer to asset file name string.
				> sFilepath : Pointer to output string.
Return		:	0 if successful, otherwise -1.
*/
/*****************************************************************************/
	virtual int GetAssetFilePath(char* sAsset, char* sFilepath);
/******************************************************************************
Function	:	frkPSInterface::LogMessage
Description	:	Outputs a string message to Particle Studio log window, status bar, or displays a message box.
Arguments	:	> sMsg : Pointer to input message string.
				> bLogWindow : Switch to display message in log window.
				> bLogStatusBar : Switch to display message on status bar.
				> bShowMessageBox : Switch to display message in pop up window.
Return		:	None.
*/
/*****************************************************************************/
	virtual void frkPSInterface::LogMessage(char* sMsg, bool bLogWindow = true,
				bool bLogStatusBar = false, bool bShowMessageBox = false);
/******************************************************************************
Function	:	frkPSInterface::GetWorkspaceRootDirectory
Description	:	Retrieves the assets library workspace directory path.
Arguments	:	None.
Return		:	Assets library workspace directory path string pointer.
*/
/*****************************************************************************/
	virtual char* frkPSInterface::GetWorkspaceRootDirectory();
	virtual char* frkPSInterface::GetTextureDirectory();

	virtual int frkPSInterface::LoadWorkspace(char* pFileName);
	virtual void frkPSInterface::Reset();
	virtual void frkPSInterface::SetBackgroundColor(COLORREF color);
	virtual void frkPSInterface::SetBackgroundImage(char* sFilePath);
	virtual void frkPSInterface::RestartSimulation();
	virtual void frkPSInterface::SetCameraMode(int nMode);
	virtual void frkPSInterface::GetAssetPath(char *sEmitterName, char *sAssetName, 
									int nAssetType, int nSlotNumber, char *sOutPath );
	virtual void* frkPSInterface::GetDirectxD3DPointer ();
	virtual int frkPSInterface :: GetActiveEmitterPropertyValue ( int eProperty, void* pProperty);
	virtual const char* GetAppRootDirectory();
	virtual void SetEmitterPropertyUIStatus(const char *sProperty, bool bEnable);

};
/******************************************************************************/






