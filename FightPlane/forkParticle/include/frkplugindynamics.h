/******************************************************************************
	Module		: Particle Stuio Plugin: Particle Dynamics
	Version		: 1.0
	Overview	: The particle dynamics plugin provides the API to over ride 
				  particle dynamics properties of an emitter in particle studio.

  (c) Copyright 2004-2007 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "frkpsinterface.h"

class frkPluginDynamics
{
public:
/******************************************************************************
Function	:	frkPluginDynamics::Init
Description	:	Called right after the plugin has been loaded to pass required data
Arguments	:	> pD3DDevice: Pointer to the Direct3D device used by studio
				> pEditFocus: Pointer to the studio keyboard accelerator enable/disable varaible
				> pfSimulationSpeedMult: Pointer to the simulation speed multiple
Return		:	None
*/
/****************************************************************************/
	virtual void Init (void* pD3dDevice, bool* pEditFocusvirtual, float *pfSimulationSpeedMult, frkPSInterface *pInterface)= 0;
/******************************************************************************
Function	:	frkPluginDynamics::ReadInput
Description	:	Gets data for the plugin from the dyn file whose path is passed to it
Arguments	:	> filepath	: Path to the dyn file attached to this plugin 
Return		:	None
*/
/*****************************************************************************/
    virtual void ReadInput(CString filepath)		            = 0;	
/******************************************************************************
Function	:	frkPluginDynamics::ParticlePhysics
Description	:	Processes data of a live particle, main callback to perform physics on the particle
Arguments	:	> fTDelta	: Time slice since last call
				> Pos	: Pointer to three floats to return the position of the particle
				> Vel	: Pointer to three floats to return the velocity of the particle
				> Color	: Pointer to three floats to return the color of the particle
				> fLife	: Maximum life of the particle
				> fScale: Size of the particle
				> fRot	: Rotiation of particle
				> fTime	: Current age of particle
				> fRotRate	: Rotation rate of particle
				> pData	: User data pointer so that the plugin can attached its data to the particle
Return		:	None
*/
/*****************************************************************************/
	 virtual void ParticlePhysics(_t_frkPEmitter *pEmitter, void *pCustomData, float fTDelta) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::ParticleBirth
Description	:	Processes data of a particle just created 
Arguments	:	> fTDelta	: Time slice since last call
				> Pos	: Pointer to three floats to return the position of the particle
				> Vel	: Pointer to three floats to return the velocity of the particle
				> Color	: Pointer to three floats to return the color of the particle
				> fLife	: Maximum life of the particle
				> fScale: Size of the particle
				> fRot	: Rotiation of particle
				> fTime	: Current age of particle
				> fRotRate	: Rotation rate of particle
				> pData	: User data pointer so that the plugin can attached its data to the particle
Return		:	None
*/
/*****************************************************************************/
	 virtual void ParticleBirth(_t_frkPEmitter *pEmitter, _t_frkParticle **aParticles, int nParticles, 
								 float fTDelta, void* pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::ParticleDeath
Description	:	Processes data of a particle that is about to die, mainly used to release the resources attached to the particle
Arguments	:	> fTDelta	: Time slice since last call
				> Pos	: Pointer to three floats to return the position of the particle
				> Vel	: Pointer to three floats to return the velocity of the particle
				> Color	: Pointer to three floats to return the color of the particle
				> fLife	: Maximum life of the particle
				> fScale: Size of the particle
				> fRot	: Rotiation of particle
				> fTime	: Current age of particle
				> fRotRate	: Rotation rate of particle
				> pData	: User data pointer so that the plugin can attached its data to the particle
Return		:	None
*/
/*****************************************************************************/
	 virtual void ParticleDeath(_t_frkPEmitter *pEmitter, _t_frkParticle **aParticles, int nParticles, 
								float fTDelta, void* pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::ParticlePreProcess
Description	:	Performs any required processing before any particles have been processed
Arguments	:	> fTDelta	: Time slice since last call
Return		:	None
*/
/*****************************************************************************/
	virtual void ParticlePreProcess (float fTDelta) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::ParticlePostProcess
Description	:	Performs any required processing after all particles have been processed
Arguments	:	> fTDelta	: Time slice since last call
Return		:	None
*/
/*****************************************************************************/
	virtual void ParticlePostProcess (float fTDelta) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::RegisterGUI
Description	:	Registers the custom data GUI with particle studio
Arguments	:	> pDialog	: Pointer to the returned GUI dialog
Return		:	1 if a GUI was registered, 0 if not
*/
/*****************************************************************************/
	virtual int RegisterGUI(CWnd** pDialog, void* pCustomData, _t_frkPEmitter *pEmitter) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::RegisterCustomDataCallback
Description	:	Registers the type of callback, Custom data chunks of the type registered will be provided to this plugin
Arguments	:	> pCBType	: Pointer to the registered callback integer
				> pCustomData : Pointer to the custom data attached to the currently active emmiter
Return		:	1 if a callback was registered, 0 if not
*/
/*****************************************************************************/
	virtual int RegisterCustomDataCallback(int* pCBType) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::EmitterCreated
Description	:	Returns custom chunk header and data to be attached to a newly created emitter 
Arguments	:	> pType	: Pointer to the type of returned chunk
				> pVersion	: Pointer to the version of returned chunk
				> pDataSize	: Pointer to the size of custom data returned
				> pCustomData	: Pointer to the custom data to the attached 
Return		:	1 if any data was returned, 0 if not
*/
/*****************************************************************************/
	virtual int EmitterCreated(_t_frkPEmitter *pEmitter, int* pType,int* pVersion,int* pDataSize,void** pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::EmitterLoaded
Description	:	Provides custom data from a loaded emitter to the plugin, Custom data of only the type registered by this plugin will be provided
Arguments	:	> pType	: Type of custom data chunk
				> pVersion	: Version of custom data chunk
				> pDataSize	: Size of custom data 
				> pCustomData	: Pointer to custom data
Return		:	None
*/
/*****************************************************************************/
	virtual int EmitterLoaded(_t_frkPEmitter *pEmitter, int nType,int nVersion, int* pDataSize, void** pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::EmitterSaved
Description	:	Provides custom data that is about to be saved with the emitter, this function allows the plugin to synchronize custom data
Arguments	:	> pType	: Type of custom data chunk
				> pVersion	: Version of custom data chunk
				> pDataSize	: Size of custom data 
				> pCustomData	: Pointer to custom data
Return		:	None
*/
/*****************************************************************************/
	virtual int EmitterSaved(int nType,int nVersion, int *pDataSize, void** pCustomData) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::SetCoordsConversion
Description	:	Assign switch for plugin to perform coordinates system conversion. 
Arguments	:	> bSwitch: true = perform conversion.                
Return		:	None.
*/
/*****************************************************************************/
    virtual void SetCoordsConversion (bool bSwitch)             = 0;
/******************************************************************************
Function	:	frkPluginDynamics::LoadCollisionModel
Description	:	Loads Collision Model for Physics. 
Arguments	:	> pModelName: Name of Model
                > fMatrix: Pointer to 16x16 Matrix for transfromation               
Return		:	None.
*/
/*****************************************************************************/
	//virtual int LoadCollisionModel(char* pModelName, float* fMatrix )             = 0;
	virtual int LoadCollisionModel(char* pModelName, char *sFilePath, float* fMatrix )  = 0;
/******************************************************************************
Function	:	frkPluginDynamics::UnloadCollisionModel
Description	:	Unloads Collision Model for Physics. 
Arguments	:	> pModelName:  Name of Model             
Return		:	None.
*/
/*****************************************************************************/
	virtual int UnloadCollisionModel(char* pModelName )             = 0;
/******************************************************************************
Function	:	frkPluginDynamics::RemoveAllCollisionModels
Description	:	Removes All Collision Models.              
Arguments	:	None.             
Return		:	None.
*/
/*****************************************************************************/
	virtual int RemoveAllCollisionModels()             = 0;
/******************************************************************************
Function	:	frkPluginDynamics::UpdateActorPos
Description	:	Updates position and orientation of a collision model.              
Arguments	:	> pModelName:  Name of Model             
				> fMatrix: Pointer to 16x16 Matrix for transfromation               
Return		:	None.
*/
/*****************************************************************************/
	virtual int UpdateActorPos(char *pModelName, float *fMatrix) = 0;
/******************************************************************************
Function	:	frkPluginDynamics::UpdateActorMesh
Description	:	Update position and orientation of a display model.              
Arguments	:	> pModelName:  Name of Model             
				> fMatrix: Pointer to 16x16 Matrix for transfromation               
Return		:	None.
*/
/*****************************************************************************/
	virtual int UpdateActorMesh(char *pModelName, float *fMatrix) = 0;

	virtual void EmitterPropertyUpdated(_t_frkPEmitter *pEmitter, void* pCustomData, bool bForceUpdate = false) = 0;
	virtual void Unload() = 0;
	virtual void RemoveEmitter(_t_frkPEmitter *pEmitter, void *pCustomData) = 0;
	virtual void Update(float fTDelta) = 0;
	virtual void DisplayGlobalsUI() = 0;
	virtual bool IsPluginInitialized() = 0;
};