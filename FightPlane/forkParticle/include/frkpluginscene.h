/******************************************************************************
	Module		: Particle Stuio Plugin: Scene
	Version		: 1.0
	Overview	: The custom data  plugin provides the API to load 3d models
                  in the particle studio and manipulate them (e.g. rotata, translate)
                  from the studio.                  

  (c) Copyright 2004-2005 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "frkpsysemitterdb.cpp"
typedef void (*_t_RenderCB) (void* pWorldXMatrix);

class frkPluginScene  
{
public:
	frkPluginScene(){

	}
	virtual ~frkPluginScene(){

	}
/******************************************************************************
Function	:	frkPluginScene::Init
Description	:	Initialises the direct X device.
Arguments	:	> pD3DDevice: The device that will take care of the loading and displaying.                
Return		:	None.
*/
/*****************************************************************************/
	virtual void Init(void* pD3DDevice, _t_RenderCB)		        = 0;
/******************************************************************************
Function	:	frkPluginScene::Load
Description	:	Loads the 3d model. 
Arguments	:	> pFileName: The filename of the 3d model information file. 
				> pDirpath: Directory path associated with the 3d model information file.     
Return		:	None.
*/
/*****************************************************************************/
	virtual int Load(CString pFilename, CString pDirpath)       = 0;
/******************************************************************************
Function	:	frkPluginScene::Unload
Description	:	Unloads or frees all resources associated with the 3d model.
Arguments	:	> pFilename: The filename of the object to be unloaded.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Unload(CString pFileName)					    = 0;
/******************************************************************************
Function	:	frkPluginScene::Process
Description	:	Draws the objects in the display list on the screen.
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
	virtual void Process()									    = 0;
/******************************************************************************
Function	:	frkPluginScene::SetMatrix
Description	:	Sets the position matrix of the object.
Arguments	:	> sObjname : The objectname 
                > matrix : The new position .           
Return		:	None.
*/
/*****************************************************************************/
    virtual void SetMatrix(CString sFilename,float* matrix)     = 0;
/******************************************************************************
Function	:	frkPluginScene::GetMatrix
Description	:	Gets the position matrix of the object.
Arguments	:	> sObjname : The file name.               
Return		:	A matrix containing the position.
*/
/*****************************************************************************/
    virtual float* GetMatrix(CString sFilename)                 = 0;
/******************************************************************************
Function	:	frkPluginScene::GetExtension
Description	:	Gets the extension of the file.
Arguments	:	None.            
Return		:	The file extension.
*/
/*****************************************************************************/
    //virtual char* GetExtension()                                = 0;
	 virtual void GetExtension(CString **aStr, int &nCount)       = 0;
/******************************************************************************
Function	:	frkPluginScene::Hide
Description	:	Hide the object on the screen
Arguments	:	> sName: The name of the object
Return		:	None.
*/
/*****************************************************************************/
    virtual void Hide(char *sName, bool bIsHidden)              = 0;
/******************************************************************************
Function	:	frkPluginScene::ReleaseObjects
Description	:	Releases the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void ReleaseObjects()                               = 0;
/******************************************************************************
Function	:	frkPluginScene::RestoreObjects
Description	:	Restores the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void RestoreObjects()                               = 0;
/******************************************************************************
Function	:	frkPluginScene::SetCoordsConversion
Description	:	Assign switch for plugin to perform coordinates system conversion. 
Arguments	:	> bSwitch: true = perform conversion.                
Return		:	None.
*/
/*****************************************************************************/
    virtual void SetCoordsConversion (bool bSwitch)             = 0;
};