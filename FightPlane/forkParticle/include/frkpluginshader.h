/******************************************************************************
	Module		: Particle Stuio Plugin: Shader
	Version		: 2.0
	Overview	: The shader plugin provides pixel shader processing API for shaders loaded 
				  by particle studio

  (c) Copyright 2004-2006 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#include "frkpsinterface.h"

class frkPluginShader
{
public:
/******************************************************************************
Function	:	frkPluginShader::Init
Description	:	Called right after the plugin has been loaded to pass required data
Arguments	:	> pD3DDevice: Pointer to the Direct3D device used by studio
				> pEditFocus: Pointer to the studio keyboard accelerator enable/diable varaible
Return		:	None.
*/
/*****************************************************************************/
	virtual void Init (void* pD3dDevice, bool* pEditFocus, frkPSInterface* pPSInterface)= 0;

/******************************************************************************
Function	:	frkPluginShader::RegisterCustomDataCallback
Description	:	Registers the type of callback, Custom data chunks of the type registered will be provided to this plugin
Arguments	:	> pCBType	: Pointer to the registered callback integer
Return		:	1 if a callback was registered, 0 if not
*/
/*****************************************************************************/
    virtual int RegisterCustomDataCallback(int* pCBType) = 0;
/******************************************************************************
Function	:	frkPluginShader::SetCurrentTexture
Description	:	Passes the pointer to the current texture attached to the resource that is about to be rendered
Arguments	:	> pTexture	: Pointer to the texture 
Return		:	None
*/
/*****************************************************************************/
    virtual void SetCurrentTexture(void* pTexture)= 0;
/******************************************************************************
Function	:	frkPluginShader::GetShaderGUI
Description	:	Returns the custom GUI of the shader whose name is passed to the function
Arguments	:	> sShaderName	: Name of the shader whose GUI is to be returned 
				> pCustomData	: The custom data to be displayed by the GUI
				> pDialog		: The pointer to return to GUI pointer
Return		:	1 if a GUI was returned 0 if not
*/
/*****************************************************************************/
    virtual int GetShaderGUI(char* sShaderName, void* pCustomData, CWnd** pDialog) = 0;
/******************************************************************************
Function	:	frkPluginShader::SetCurrentShader
Description	:	Sets the current shader which is about to be rendered 
Arguments	:	> sShaderName	: Name of the shader that is attached to the object being rendered
				> pCustomData	: The custom data attached to the object being rendered
Return		:	None
*/
/*****************************************************************************/
    virtual void SetCurrentShader(char* sShaderName, void* pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginShader::PreRenderProcess
Description	:	Function to perform the pre render tasks (setting shader constants) for the currently set shader
Arguments	:	None
Return		:	None
*/
/*****************************************************************************/
	virtual void PreRenderProcess () = 0;
/******************************************************************************
Function	:	frkPluginShader::PreRenderParticleProcess
Description	:	Function to perform the pre render tasks (setting shader constants) for the currently set shader
Arguments	:	None
Return		:	None
*/
/*****************************************************************************/
//	virtual void PreRenderParticleProcess (float* pos, float size, float* fRot, float* uv) = 0;
/******************************************************************************
Function	:	frkPluginShader::SetTransform
Description	:	Function to perform view transformation setup for the active shader. This callback is made before PreRenderProcess().
Arguments	:	> pViewTransform : Pointer to view transformation matrix.
				> pProjectionTransform : Pointer to projection matrix.
Return		:	None
*/
/*****************************************************************************/
	virtual void SetTransform (void* pViewTransform, void* pProjectionTransform) = 0;
/******************************************************************************
Function	:	frkPluginShader::PostRenderProcess
Description	:	Function to perform the post render tasks (resetting shader constants) for the currently set shader
Arguments	:	None
Return		:	None
*/
/*****************************************************************************/
	virtual void PostRenderProcess () = 0;
/******************************************************************************
Function	:	frkPluginShader::ShaderApplied
Description	:	Called when a shader is assigned to an object to return the custom data to be attached to the new object
Arguments	:	> sShaderName	: Name of the shader that is assigned to the new object
				> pType			: Pointer to the type of returned chunk
				> pVersion		: Pointer to the version of returned chunk
				> pDataSize		: Pointer to the size of custom data returned
				> pCustomData	: Pointer to the custom data to the attached 
Return		:	1 if custom data was attached 0 if not
*/
/*****************************************************************************/
    virtual int ShaderApplied(char* sShaderName, int* pType, int* pVersion, int* pDataSize, void** pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginShader::ShaderSaved
Description	:	Called when an object with shader data is about to be saved so that the plugin can add/remove/modify data to be saved
Arguments	:	> sShaderName	: Name of the shader that is assigned to the new object
				> pType			: Type of custom data chunk
				> pVersion		: Version of custom data chunk
				> pDataSize		: Size of custom data 
				> pCustomData	: Pointer to custom data
Return		:	None
*/
/*****************************************************************************/
	virtual void ShaderSaved(char* sShaderName,int nType, int nVersion, int nDataSize, void* pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginShader::ReleaseObjects
Description	:	Releases the objects in the scene on directx device loss.
Arguments	:	None                
Return		:	None
*/
/*****************************************************************************/
    virtual void ReleaseObjects() = 0;
/******************************************************************************
Function	:	frkPluginShader::RestoreObjects
Description	:	Restores the objects in the scene on directx deviced captured after loss.
Arguments	:	None                
Return		:	None
*/
/*****************************************************************************/
    virtual void RestoreObjects() = 0;
/************************************************************************/
	virtual void ApplyShader() = 0;
	virtual void RemoveShader() = 0;
	virtual void Submit(D3DXVECTOR4* pPos, 
						float fRotMin, float& fRot, 
						D3DXVECTOR2* pScale, float fScale, 
						D3DXVECTOR4* pTint, D3DXVECTOR4* pColor,
						D3DXVECTOR4* pUVs, D3DXVECTOR3 AxisUpV, D3DXVECTOR3 AxisRightV, D3DXVECTOR3 AxisRot) = 0;
	virtual void Process() = 0;
	virtual void SetWorldViewProjMatrix(void* matrix) = 0;
	virtual void SetTextureLibraryPath(char *sPath) = 0;
};

/*****************************************************************************/
