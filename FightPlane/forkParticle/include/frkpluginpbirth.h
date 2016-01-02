/******************************************************************************
	Module		: Particle Stuio Plugin: Particle Birth
	Version		: 1.0
	Overview	: The particle birth plugin provides the API to over ride 
				  particle birth properties of an emitter in particle studio.

  (c) Copyright 2004-2005 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class frkPluginPBirth
{
public:	

/******************************************************************************
Function	:	frkPluginPBirth::Init
Description	:	Initializes the plugin after it is loaded into particle studio.
Arguments	:	> pD3DDevice	: DirectX device pointer.
Return		:	None.
*/
/*****************************************************************************/
    virtual void Init(void* pD3DDevice)= 0;
/******************************************************************************
Function	:	frkPluginPBirth::Load
Description	:	Loads particle birth information.
Arguments	:	> pFilename	: Name of birth information file.
				> pDirpath: Directory path associated with birth information file.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Load(CString pFilename, CString pDirpath)= 0;
/******************************************************************************
Function	:	frkPluginPBirth::Unload
Description	:	Unloads or frees all resources associated to the birth information file name.
Arguments	:	> pFileName	: Birth information file name.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Unload(CString pFileName) = 0;
/******************************************************************************
Function	:	frkPluginPBirth::GetPoint
Description	:	Gets a random point from the pointlist passed.
Arguments	:	> ListInput: A pointer to the list that contains the vertices.
                > pOutPos: A vector that will contain the coordinates of the randomly selected vertex
                > pOutVel: A vector that will contain the direction of the randomly selected vertex (Normal to the vertex)
Return		:	None.
*/
/*****************************************************************************/
    virtual void GetPoint(void *ListInput, float *Pos, float *Vel) = 0;
/******************************************************************************
Function	:	frkPluginPBirth::GetPointList
Description	:	Gets the Points of the model specified.
Arguments	:	> sFilename: The filename of the object.
Return		:	> A pointer pointing to the Points list of the object.
*/
/*****************************************************************************/
    virtual void* GetPointList(CString pFilename) = 0;
/******************************************************************************
Function	:	frkPluginPBirth::GetExtension
Description	:	Gets the file extenion associated with the birth information file.
Arguments	:	None.
Return		:	A character pointer that contains the extension.
*/
/*****************************************************************************/
    //virtual char* GetExtension() = 0;
    virtual void GetExtension(CString **aStr, int &nCount)       = 0;
/******************************************************************************
Function	:	frkPluginPBirth::ReleaseObjects
Description	:	Releases the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void ReleaseObjects() = 0;
/******************************************************************************
Function	:	frkPluginPBirth::RestoreObjects
Description	:	Restores the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void RestoreObjects() = 0;
/******************************************************************************
Function	:	frkPluginPBirth::SetCoordsConversion
Description	:	Assign switch for plugin to perform coordinates system conversion. 
Arguments	:	> bSwitch: true = perform conversion.                
Return		:	None.
*/
/*****************************************************************************/
    virtual void SetCoordsConversion (bool bSwitch)             = 0;
};