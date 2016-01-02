/******************************************************************************
	Module		: Particle Stuio Plugin: Particle Render
	Version		: 1.0
	Overview	: The particle render plugin provides the API to over ride 
				  particle rendering. the particles can be rendered as objects
                  specified by the plugin.

  (c) Copyright 2004-2005 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class frkPluginPRender  
{
public:
	frkPluginPRender () {}
	virtual ~frkPluginPRender () {}
/******************************************************************************
Function	:	frkPluginPRender::Init
Description	:	Initializes the plugin after it is loaded into particle studio.
Arguments	:	> pD3DDevice : DirectX device pointer.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Init(void* pD3DDevice)		            = 0;
/******************************************************************************
Function	:	frkPluginPRender::Load
Description	:	Loads particle birth information.
Arguments	:	> pFilename	: Name of particle model information file.
				> pDirpath: Directory path associated with particle model information file.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Load(CString pFilename, CString pDirpath)          = 0;
/******************************************************************************
Function	:	frkPluginPRender::Unload
Description	:	Unloads or frees all resources associated to the model information file name.
Arguments	:	> pFileName	: Birth information file name.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Unload(CString pFileName)					        = 0;
/******************************************************************************
Function	:	frkPluginPRender::Render
Description	:	Draws the particles in the shape of the object specified on the viewport.
Arguments	:	> Particle: A pointer to the Particle data.
                > pPos: The position of the particle.
                > fRot: The rotation of the particle.
                > fScale: The scaling of the particle.    
                > pColor: A pointer to the color of the particle. RGBA values.
Return		:	None.
*/
/*****************************************************************************/
	virtual void Render(void *Particle,float* pPos,float Scale,
                        float Rot,float fRotX,float fRotY,float fRotZ,
                        float fScaleX,float fScaleY, float fScaleZ,float *pColor, int nBlend) = 0;
/******************************************************************************
Function	:	frkPluginPRender::GetExtension
Description	:	Gets the file extenion associated with the particle object information file.
Arguments	:	None.
Return		:	A character pointer that contains the extension.
*/
/*****************************************************************************/
    //virtual char* GetExtension()                                    = 0;
    virtual void GetExtension(CString **aStr, int &nCount)       = 0;
/******************************************************************************
Function	:	frkPluginPRender::GetParticleHandle
Description	:	Gets a pointer to the model specified.
Arguments	:	> pParticle: The pointer to the model.
                > sName: The name of the particle. 
Return		:	None.
*/
/*****************************************************************************/
    virtual void* GetParticleHandle(char* sName)                    = 0; 
/******************************************************************************
Function	:	frkPluginPRender::ReleaseObjects
Description	:	Releases the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void ReleaseObjects()                                   = 0;
/******************************************************************************
Function	:	frkPluginPRender::RestoreObjects
Description	:	Restores the objects in the scene
Arguments	:	None                
Return		:	None.
*/
/*****************************************************************************/
    virtual void RestoreObjects()                                   = 0;
 
/******************************************************************************
Function	:	frkPluginPRender::SetCoordsConversion
Description	:	Assign switch for plugin to perform coordinates system conversion. 
Arguments	:	> bSwitch: true = perform conversion.                
Return		:	None.
*/
/*****************************************************************************/
    virtual void SetCoordsConversion (bool bSwitch)             = 0;

/******************************************************************************
Function	:	frkPluginPRender::UpdateInstanceCount
Description	:	Updates the instance count for the particles in an emitter
Arguments	:	None.                
Return		:	None.
*/
/*****************************************************************************/
	virtual void UpdateInstanceCount(char * pFileName) = 0;
};