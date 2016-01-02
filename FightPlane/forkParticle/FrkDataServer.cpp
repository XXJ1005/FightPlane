/******************************************************************************
Module		: FrkDataServer Class
Overview	: The Data Server class holds Emitter Description and Asset Data
and provides interface for managing and accessing the data.

Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
// ForkParticle Header Files
#include "frksdk.h"

#include "FrkDataServer.h"

#include <stdio.h>
#include <string>
#include <atlimage.h>

class ParticleSystem;

FrkDataServer* FrkDataServer::s_Inst = NULL;
char FrkDataServer::m_sMediaPath[frkPARTICLESYSTEM_MAX_PATH_LENGTH];
/******************************************************************************
_Function	:	FrkDataServer Constructor
_Description:	Creates a DataServer instance. 
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkDataServer::FrkDataServer()
{
	m_nNumTextureAssetCount = 0;
	m_nNumModelAssetCount   = 0;
	m_nNumEffectDescCount  = 0;
	m_nNumEmitterDescCount  = 0;

	for(int i = 0; i < frkPARTICLESYSTEM_MAX_ENTRIES; i++)
	{
		m_aTextureAssetDatabase[i].nTextureID = 0;

		m_aModelsAssetDatabase[i].pModel = 0;

		m_aEmitterDescDatabase[i].nSize = 0;
		m_aEmitterDescDatabase[i].pDesc = 0;

		m_aEffectDescDatabase[i].nNumRefs = 0;
		m_aEffectDescDatabase[i].pDesc = 0;
		m_aEffectDescDatabase[i].pPEffectInfo = 0;
	}
}
/******************************************************************************
_Function	:	FrkDataServer Destructor
_Description	:	Destroys a DataServer instance. 
_Arguments	:	None.
_Return		:	None.
*/
/*****************************************************************************/
FrkDataServer::~FrkDataServer()
{
	Unload();

	m_nNumTextureAssetCount = 0;
	m_nNumModelAssetCount   = 0;
	m_nNumEffectDescCount  = 0;
}
/******************************************************************************
_Function	:	FrkDataServer::SetMediaPath
_Description:	Sets Media Path for Assets. 
_Arguments	:	> sPath: Directory Path.
_Return		:	None.
/*****************************************************************************/
void FrkDataServer::SetMediaPath(char* sPath)
{
	strncpy(m_sMediaPath, sPath, frkPARTICLESYSTEM_MAX_PATH_LENGTH);
}
/******************************************************************************
_Function	:	FrkDataServer::GetMediaPath
_Description:	Gets Media Path for Assets. 
_Arguments	:	None.
_Return		:	Media Path.
/*****************************************************************************/
char* FrkDataServer::GetMediaPath()
{
	return m_sMediaPath;
}
/******************************************************************************
_Function	:	FrkDataServer::LoadEmitter
_Description	:	Loads emitter description from a PSB file into the data server.
_Arguments	:	> sName:	PSB File Name.
_Return		:	Returns pointer to Info.
*/
/*****************************************************************************/
void* FrkDataServer::LoadEmitter(const char* sName)
{
	char sBuff[256];
	sprintf(sBuff, "%s%s.psb", m_sMediaPath, sName);

	FILE* InfoFile=fopen(sBuff,"rb");

	fseek(InfoFile, 0L, SEEK_END); 
	int len = ftell(InfoFile); 
	fseek(InfoFile, 0L, SEEK_SET); 

	void* buf = malloc (len);
	fread(buf, len, 1, InfoFile);
	fclose(InfoFile);

	m_nNumEmitterDescCount = SearchEmptySlot((IAssetInfoNode*)m_aEmitterDescDatabase, m_nNumEmitterDescCount, sizeof(EmitterDescNode), frkPARTICLESYSTEM_MAX_ENTRIES);
	if (m_nNumEmitterDescCount != -1)
	{
		m_aEmitterDescDatabase[m_nNumEmitterDescCount].pDesc = buf;
		m_aEmitterDescDatabase[m_nNumEmitterDescCount].sName = sName;
	}
	/* m_aEmitterDescDatabase[m_nNumEmitterDescCount].pDesc = buf;
	m_aEmitterDescDatabase[m_nNumEmitterDescCount].sName = sName;
	m_nNumEmitterDescCount++; */

	return buf;
}
/******************************************************************************
_Function	:	FrkDataServer::LoadEffect
_Description	:	Loads effect description from a PSB file into the data server.
_Arguments	:	> sName:	PSB File Name.
_Return		:	Returns pointer to Info.
*/
/*****************************************************************************/
void* FrkDataServer::LoadEffect(const char* sName)
{
	char sBuff[256];
	sprintf(sBuff, "%s%s.psb", m_sMediaPath, sName);

	FILE* InfoFile=fopen(sBuff,"rb");
	fseek(InfoFile, 0L, SEEK_END); 
	int len = ftell(InfoFile); 
	fseek(InfoFile, 0L, SEEK_SET); 

	void* buf = malloc (len);
	fread(buf, len, 1, InfoFile);
	fclose(InfoFile);

	m_nNumEffectDescCount = SearchEmptySlot((IAssetInfoNode*)m_aEffectDescDatabase, m_nNumEffectDescCount, sizeof(EffectDescNode), frkPARTICLESYSTEM_MAX_ENTRIES);

	if (m_nNumEffectDescCount != -1)
	{
		m_aEffectDescDatabase[m_nNumEffectDescCount].pDesc = buf;
		m_aEffectDescDatabase[m_nNumEffectDescCount].sName = sName;
		m_aEffectDescDatabase[m_nNumEffectDescCount].nNumRefs = 1;
		m_nNumEffectDescCount++;
	}

	return buf;
}
/******************************************************************************
_Function	:	FrkDataServer::GetCurrentTextureName
_Description:	Returns current Texture's name with path from pEmitter.
_Arguments	:	> pEmitter:	Emitter Pointer.
> [out] sTextureName: Texture name with path is returned in it. 
_Return		:	None.
*/
/*****************************************************************************/
void FrkDataServer::GetCurrentTextureName(_t_frkPEmitter* pEmitter, char *sTextureName)
{
	_t_frkPEmitterInfo *pPSB = frkPEmitterGetPropertyInfo(pEmitter);
	_t_frkAssetInfo* pAsset = (_t_frkAssetInfo*)(frkPPropertyCurAssetPtr (pPSB));
	char *sKey = frkPAssetGetKeyFileName(pAsset);
	sprintf(sTextureName, "%s%s", m_sMediaPath, sKey);
}
/******************************************************************************
_Function	:	FrkDataServer::EmitterDescUpdate
_Description:	Updates Emitter description in the data server on Live Tuner update from Particle Studio.
_Arguments	:	> pEmitter:	Emitter Pointer.
> pPSB:	Emitter Info from Live Tuner.
> nSize: Size of PSB Data.
_Return		:	Returns pointer to emitter description.
*/
/*****************************************************************************/
void* FrkDataServer::EmitterDescUpdate(_t_frkPEmitter* pEmitter, _t_frkPEmitterInfo* pPSB, int nSize )
{
	_t_frkPEmitterInfo* Old = frkPEmitterGetPropertyInfo ( pEmitter );
	int i = 0;
	while(i<m_nNumEmitterDescCount && Old!= m_aEmitterDescDatabase[i].pDesc)
		i++;
	if(Old== m_aEmitterDescDatabase[i].pDesc)
	{
		if(m_aEmitterDescDatabase[i].nSize > 0 )
		{
			free(m_aEmitterDescDatabase[i].pDesc);
			m_aEmitterDescDatabase[i].pDesc = NULL;
		}	
		_t_frkPEmitterInfo* buf = (_t_frkPEmitterInfo*)malloc ( nSize );
		memcpy ( buf, pPSB, nSize );
		m_aEmitterDescDatabase[i].pDesc = buf;
		m_aEmitterDescDatabase[i].nSize = nSize;
		frkPEmitterSetPropertyInfo ( pEmitter, buf );
		buf = NULL;
		return m_aEmitterDescDatabase[i].pDesc;
	}
	return NULL;
}
/******************************************************************************
_Function	:	FrkDataServer::SearchEmitterDescs
_Description	:	Searches for the emitter description in the data server.
_Arguments	:	> pFilename: Filename of PSB file containing the Info.
_Return		:	If emitter description found returns a pointer to it,
else returns NULL.
*/
/*****************************************************************************/
void* FrkDataServer::SearchEmitterDescs(const char* pFileName)
{
	void* pEDesc = NULL; 
	// Search for emitter description in database
	bool bFound = false;
	int i = 0;
	while (!bFound && i < frkPARTICLESYSTEM_MAX_ENTRIES/* m_nNumEffectDescCount */)
	{
		if (m_aEffectDescDatabase[i].sName.compare((string)pFileName) == 0)
		{
			bFound = true;
			pEDesc = m_aEffectDescDatabase[i].pDesc;
		}
		else
			i++;
	}
	return pEDesc;
}
/******************************************************************************
_Function	:	FrkDataServer::SearchEffectDescs
_Description	:	Searches for the effect description in the data server.
_Arguments	:	> pFilename: Filename of PSB file containing the Info.
_Return		:	If emitter description found returns a pointer to it,
else returns NULL.
*/
/*****************************************************************************/
void* FrkDataServer::SearchEffectDescs(const char* pFileName)
{
	void* pEDesc = NULL; 

	// Search for emitter description in database
	bool bFound = false;
	int i = 0;
	while (!bFound && i < frkPARTICLESYSTEM_MAX_ENTRIES/* m_nNumEffectDescCount */)
	{
		if (m_aEffectDescDatabase[i].sName.compare((string)pFileName) == 0)
		{
			bFound = true;
			pEDesc = (void*)&m_aEffectDescDatabase[i];
		}
		else
			i++;
	}

	return pEDesc;
}
/******************************************************************************
_Function	:	FrkDataServer::SearchEffectDescs
_Description	:	Searches for the effect description in the data server.
_Arguments	:	> pFilename: Filename of PSB file containing the Info.
_Return		:	If emitter description found returns a pointer to it,
else returns NULL.
*/
/*****************************************************************************/
EffectDescNode* FrkDataServer::SearchEffectDescs(_t_frkPEffectInfo* pInfo)
{
	EffectDescNode* pEDesc = NULL; 

	// Search for emitter description in database
	bool bFound = false;
	int i = 0;
	while (!bFound && i < frkPARTICLESYSTEM_MAX_ENTRIES)
	{
		if (m_aEffectDescDatabase[i].pPEffectInfo == pInfo)
		{
			bFound = true;
			pEDesc = &m_aEffectDescDatabase[i];
		}
		else
			i++;
	}

	return pEDesc;
}
/******************************************************************************
_Function	:	FrkDataServer::SearchTextures
_Description	:	Searches for the texture in the data server.
_Arguments	:	> sName: Texture Name.
_Return		:	If texture found returns the pointer to the texture,
else returns NULL.
*/
/*****************************************************************************/
void* FrkDataServer::SearchTextures ( char* sName )
{
	for ( int i = 0; i < m_nNumTextureAssetCount; i++ )
	{
		if ( m_aTextureAssetDatabase[i].sName == sName )
			return (void *)&m_aTextureAssetDatabase[i].nTextureID; 
	}
	return NULL;
}
/******************************************************************************
_Function	:	FrkDataServer::SearchModels
_Description	:	Searches for the model in the data server.
_Arguments	:	> sName:	Model Name.
_Return		:	If model found returns the pointer to the model,
else returns NULL.
*/
/*****************************************************************************/
void* FrkDataServer::SearchModels ( char* sName )
{
	for ( int i = 0; i < m_nNumModelAssetCount; i++ )
	{
		if ( m_aModelsAssetDatabase[i].sName == sName )
			return m_aModelsAssetDatabase[i].pModel;
	}
	return NULL;
}
/******************************************************************************
Function	:	FrkDataServer::Unload
Description	:	Unloads the data server.
Arguments	:	None.
Return		:	None.
*/
/*****************************************************************************/
void FrkDataServer::Unload()
{
	m_nNumEmitterDescCount = frkPARTICLESYSTEM_MAX_ENTRIES - 1;/* m_nNumEmitterDescCount--; */
	while(m_nNumEmitterDescCount >= 0)
	{
		if(m_aEmitterDescDatabase[m_nNumEmitterDescCount].pDesc && m_aEmitterDescDatabase[m_nNumEmitterDescCount].nSize > 0)/* if(m_aEmitterDescDatabase[m_nNumEmitterDescCount].nSize > 0) */
			free(m_aEmitterDescDatabase[m_nNumEmitterDescCount].pDesc);

		m_nNumEmitterDescCount--;
	}

	m_nNumEffectDescCount = frkPARTICLESYSTEM_MAX_ENTRIES - 1;/* m_nNumEffectDescCount--; */
	while(m_nNumEffectDescCount >= 0)
	{
		if (m_aEffectDescDatabase[m_nNumEffectDescCount].pDesc)/* void* pPSB = m_aEffectDescDatabase[m_nNumEffectDescCount].pDesc; */
			delete m_aEffectDescDatabase[m_nNumEffectDescCount].pDesc;
		m_nNumEffectDescCount--;
	}

	m_nNumTextureAssetCount = frkPARTICLESYSTEM_MAX_ENTRIES - 1;/* m_nNumTextureAssetCount--; */
	while(m_nNumTextureAssetCount >= 0)
	{
		glDeleteTextures(1, &m_aTextureAssetDatabase[m_nNumTextureAssetCount].nTextureID);
		m_nNumTextureAssetCount--;
	}
	m_nNumModelAssetCount = frkPARTICLESYSTEM_MAX_ENTRIES - 1;/* m_nNumModelAssetCount--; */
	while(m_nNumModelAssetCount >= 0)
	{
		if(m_aModelsAssetDatabase[m_nNumModelAssetCount].pModel!=NULL)
			delete m_aModelsAssetDatabase[m_nNumModelAssetCount].pModel;
		m_nNumModelAssetCount--;
	}
}

/******************************************************************************
Function	:	FrkDataServer::LoadTexture
Description	:	Loads texture asset in the texture asset database.
Arguments	:	[In]sName	:	Texture name
Return		:	pTexture	:	Returns pointer to texture.
/*****************************************************************************/
void *FrkDataServer::LoadTexture(char *sKey)
{
	char sTempKey[256];
	sprintf(sTempKey, "%s%s", m_sMediaPath, sKey);

	void *pTexture = SearchTextures(sTempKey);
	if (pTexture)
		return pTexture;

	CImage img;	
	HRESULT hr = img.Load(sTempKey);
	if (!SUCCEEDED(hr))	//ÎÄ¼þ¼ÓÔØÊ§°Ü
	{
		string mes = sTempKey;
		mes += "¼ÓÔØÊ§°Ü";
		MessageBox(NULL, mes.c_str(), "´íÎó", 0);
		return NULL;
	}
	HBITMAP hbmp = img;
	BITMAP bm;
	if (!GetObject(hbmp, sizeof(bm), &bm)) {
		return NULL;
	}
		
	GLuint nNewTexture = 0;
	glGenTextures(1, &nNewTexture);
	if (nNewTexture){
		glBindTexture(GL_TEXTURE_2D, nNewTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		if (bm.bmBitsPixel == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, 4, bm.bmWidth, bm.bmHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bm.bmBits);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bm.bmBits);
		}
	}
	else{
		return NULL;
	}

	m_aTextureAssetDatabase[m_nNumTextureAssetCount].sName = sTempKey;
	m_aTextureAssetDatabase[m_nNumTextureAssetCount].nTextureID = nNewTexture;
	m_nNumTextureAssetCount++;

	return (void *)(&m_aTextureAssetDatabase[m_nNumTextureAssetCount-1].nTextureID);
}

/******************************************************************************
Function	:	DataServerLoadModel
Description	:	Loads model asset in the texture asset database.
Arguments	:	[In]sName	:	Model name
Return		:	pMesh		:	Returns pointer to model.
/*****************************************************************************/
void* FrkDataServer::LoadModel(char* sKey)
{
	return NULL;
}

/******************************************************************************
Function	:	DestroyEffectInfo
Description	:	Frees and removes the effect info from the data server array if
				reference count falls to zero.
Arguments	:	[In]pEffectInfo	:	Effect info to be removed
Return		:	true if effect info was removed, false otherwise.
/*****************************************************************************/
bool FrkDataServer::DestroyEffectInfo(_t_frkPEffectInfo** pEffectInfo)
{
	EffectDescNode* pDescNode = (EffectDescNode*)SearchEffectDescs(*pEffectInfo);
	if (pDescNode == NULL)
		return false;

	if(pDescNode->nNumRefs == 1)
	{
		pDescNode->pPEffectInfo = NULL;
		pDescNode->sName = "";
		pDescNode->nNumRefs = 0;
		free(pDescNode->pDesc);
		pDescNode->pDesc = NULL;
		m_nNumEffectDescCount--;
	}
	else
	{
		pDescNode->nNumRefs--;
	}
	return true;
}
/******************************************************************************
Function	:	SetEffectInfo
Description	:	Stores the passed effect info in the dataserver array.
Arguments	:	[In]pEffectInfo	:	Effect info to be inserted
				[In]pFileName   :   Name of the info file
Return		:	None.
/*****************************************************************************/
void FrkDataServer::SetEffectInfo(const char* pFileName, _t_frkPEffectInfo* pEffectInfo)
{
	// Search for emitter description in database
	bool bFound = false;
	int i = 0;
	while (!bFound && i < frkPARTICLESYSTEM_MAX_ENTRIES/* m_nNumEffectDescCount */)
	{
		if (m_aEffectDescDatabase[i].sName.compare((string)pFileName) == 0)
		{
			bFound = true;
			m_aEffectDescDatabase[i].pPEffectInfo = pEffectInfo;
		}
		else
			i++;
	}
}
/******************************************************************************
Function	:	DataServerLoadTunerInfo
Description	:	Points Emitter Info from a memory into the emitter database.
Arguments	:	[In]sName	:	PSB File Name.
[In]pEDesc	:	Emitter Info.
[In]nSize	:	Size of pEDesc data size. 
Return		:	buff	:	Returns pointer to Info.
/*****************************************************************************/
void* FrkDataServer::DataServerLoadTunerInfo(char* sName, _t_frkPEmitterInfo* pEDesc)
{
	void* pInfo = pEDesc;
	m_aEmitterDescDatabase[m_nNumEmitterDescCount].pDesc = pInfo;
	m_aEmitterDescDatabase[m_nNumEmitterDescCount].sName = sName;
	m_aEmitterDescDatabase[m_nNumEmitterDescCount].nSize = 0;
	m_nNumEmitterDescCount++;
	return pInfo;
}
/******************************************************************************
Function	:	LoadPSBPackage
Description	:	Loads a PSB file into the passed buffer.
Arguments	:	[In]pFileName	 :	Name of the the file to load
				[Out]pPSB        :  The PSB image
				[Out]pEffectInfo :  EffectInfo of the PSB (if already present
				                    in dataserver)
Return		:	true if package already loaded, false otherwise.
/*****************************************************************************/

bool FrkDataServer::LoadPSBPackage(const char *pFileName, void **pPSB, _t_frkPEffectInfo **pEffectInfo)
{
	*pPSB = NULL; 

	EffectDescNode* pDesc = (EffectDescNode*)SearchEffectDescs(pFileName);
	if (pDesc) {
		*pPSB = pDesc->pDesc;
		*pEffectInfo = pDesc->pPEffectInfo;
		pDesc->nNumRefs++;
		return true;
	}

	*pPSB = LoadEffect(pFileName);
	// Effect info not set
	return false;
}
/******************************************************************************
Function	:	GetPSBData
Description	:	Retrieves chunk data pointer.
Arguments	:	> pPropertyInfo: Pointer to emitter property information.
Return		:	Pointer to chunk custom data, otherwise NULL if no chunks remaining.
*/
/*****************************************************************************/
void FrkDataServer::GetPSBData(void* pPackageDesc, char** pEmitterNames, int *nEmitterCount, _t_frkPEmitterInfo** aEInfo, char** sTrackName)
{
	*nEmitterCount = 0;
	//extract Emitter and EventTrack Filename from Package File and pass outside this function
	_t_frkLdrChunk* pTracer = frkPSBChunkResetTracer(pPackageDesc);
	_t_frkLdrChunk*	pChunkTracer = frkPSBChunkGetTracerItem(pTracer);

	while(pChunkTracer)
	{
		int nType = frkPSBChunkGetType(pChunkTracer);
		if( nType == frkPSYSTEM_CHUNKID_PSB )
		{
			pEmitterNames[*nEmitterCount] = frkPSBChunkGetName(pChunkTracer);
			aEInfo[*nEmitterCount] = (_t_frkPEmitterInfo*) frkPSBChunkGetData(pChunkTracer);
			*nEmitterCount += 1;
		}
		else if( nType == frkPSYSTEM_CHUNKID_EVENTTRACK )
		{
			//copy event track name 
			*sTrackName = frkPSBChunkGetName(pChunkTracer);
		}

		pChunkTracer = frkPSBChunkIncTracer(pChunkTracer);
	}
}
/******************************************************************************
Function	:	FrkDataServer::UserLoadAssetCB
Description	:	Callback for Fork SDK to handle loading of associated assets.
Arguments	:	pAsset:	pointer to asset information structure.
Return		:	Pointer to loaded asset.
/*****************************************************************************/
void* FrkDataServer::UserLoadAssetCB(_t_frkAssetInfo* pAsset, void* pUserData)
{
	int nType = frkPAssetGetType(pAsset);
	char * sKey =  frkPAssetGetKeyFileName(pAsset);

	if(nType == ePSYSTEM_ASSETTYPE_TEXTURE)
	{
		return FrkDataServer::GetInstance()->LoadTexture(sKey);
	}
	else if(nType == ePSYSTEM_ASSETTYPE_MODEL)
	{
		return FrkDataServer::GetInstance()->LoadModel(sKey);
	}

	return NULL;
}

/******************************************************************************
Function	:	FrkDataServer::LoadNoteTrkFile
Description	:	Loads an Event Track from a trk file.
Arguments	:	[In]sInFileName:	File Name.
Return		:	pTrk		   :	Returns pointer to Loaded Event Track.
/*****************************************************************************/
_t_frkAnmTrk* FrkDataServer::LoadNoteTrkFile(char *sInFileName)
{

	char sNoteFilePath[256];

	strcpy(sNoteFilePath, m_sMediaPath);
	strcat(sNoteFilePath, sInFileName);
	strcat(sNoteFilePath, ".trk");

	FILE* pInFile;
	pInFile = fopen (sNoteFilePath, "rb");

	if (pInFile == NULL)
		return NULL;

	int nEventAnimSize = 0;
	int nSize = 0;

	fseek (pInFile, 0, SEEK_END);
	nEventAnimSize = ftell (pInFile);
	fseek (pInFile, 0, SEEK_SET);
	if (nEventAnimSize)
	{
		void * pPackageDesc = malloc (nEventAnimSize);
		fread (pPackageDesc, 1, nEventAnimSize, pInFile);
		//extract event track from Package File 
		_t_frkLdrChunk* pChunkTracer = frkPSBChunkResetTracer(pPackageDesc);

		if(pChunkTracer)
		{
			void* pChunkTracerData = frkPSBChunkGetData(pChunkTracer);
			int nType = frkPSBChunkGetType(pChunkTracer);

			if( nType == frkPSYSTEM_CHUNKID_EVENTTRACK )
			{
				_t_frkAnmTrk* pTrk = (_t_frkAnmTrk*)pChunkTracerData;
				char *sEventTrkName = frkPSBChunkGetName(pChunkTracer);
				int nChunkDataSize = frkPSBChunkGetDataSize(pChunkTracer);
				if(pTrk && nChunkDataSize > 0 )
				{
					void * pReadTrk = malloc(nChunkDataSize);
					memset(pReadTrk, 0 , nChunkDataSize);
					memcpy(pReadTrk, pTrk, nChunkDataSize);
					_t_frkAnmTrk* pEventTrk = (_t_frkAnmTrk*)pReadTrk;
					frkTRKPrepare (pEventTrk);
					if(pEventTrk)
					{
						//remove  package in memory
						free(pPackageDesc);
						pPackageDesc = NULL;
						return pEventTrk;
					}	
				}
			}
		}
		//remove  package in memory
		free(pPackageDesc);
		pPackageDesc = NULL;
	}
	return NULL;	//failure to load track;
}
/******************************************************************************
Function	:	FrkDataServer::LoadNoteTrkFromPackage
Description	:	Loads an Event Track from the PSB package description.
Arguments	:	[In]sInEventTrkName :	Name Of the event track.
				[In]pPackageDesc	:	The psb package description
Return		:	Returns pointer to Loaded Event Track.
/*****************************************************************************/
_t_frkAnmTrk* FrkDataServer::LoadNoteTrkFromPackage(char *sInEventTrkName, void *pPackageDesc)
{
	//extract event track from Package File 
	int bDone = 0;
	_t_frkLdrChunk* pTracer = frkPSBChunkResetTracer(pPackageDesc);
	_t_frkLdrChunk*	pChunkTracer = frkPSBChunkGetTracerItem(pTracer);

	while(pChunkTracer)
	{
		void* pChunkTracerData = frkPSBChunkGetData(pChunkTracer);
		int nType = frkPSBChunkGetType(pChunkTracer);

		if( nType == frkPSYSTEM_CHUNKID_EVENTTRACK )
		{
			_t_frkAnmTrk* pTrk = (_t_frkAnmTrk*)pChunkTracerData;
			char *sEventTrkName = frkPSBChunkGetName(pChunkTracer);
			int nChunkDataSize = frkPSBChunkGetDataSize(pChunkTracer);
			int nNameMatch = strcmp(sInEventTrkName, sEventTrkName);
			if(pTrk && nChunkDataSize > 0 && nNameMatch == 0 )
			{
				void * pReadTrk = malloc(nChunkDataSize);
				memset(pReadTrk, 0 , nChunkDataSize);
				memcpy(pReadTrk, pTrk, nChunkDataSize);
				_t_frkAnmTrk* pEventTrk = (_t_frkAnmTrk*)pReadTrk;
				frkTRKPrepare (pEventTrk);
				if(pEventTrk)
				{
					return pEventTrk;
				}	
			}
		}
		pChunkTracer = frkPSBChunkIncTracer(pChunkTracer);
	}
	return NULL;	//event track was not found
}
int FrkDataServer::SearchEmptySlot(IAssetInfoNode* aArray, int nStartIdx, int nStride, int nMaxEntries)
{
	if (nStartIdx == nMaxEntries)
		nStartIdx = 0;

	void* pEDesc = NULL; 

	bool bFound = false;
	int i = nStartIdx;
	while (!bFound && i < nMaxEntries)
	{
		if (aArray->pData == NULL)
			bFound = true;
		else
		{
			aArray = (IAssetInfoNode*)((unsigned long)aArray + nStride);
			i++;
		}
	}

	return i == nMaxEntries ? -1 : i;
}

/************************************************************************/
bool FrkDataServer::RetrieveEffect(const char* pFileName, void **pPSB, _t_frkPEffectInfo** pEffectInfo)
{
	*pPSB = NULL; 
	// Search for emitter description in database
	bool bFound = false;
	int i = 0;
	while (!bFound && i < frkPARTICLESYSTEM_MAX_ENTRIES)
	{
		if (m_aEffectDescDatabase[i].sName.compare((string)pFileName) == 0)
		{
			bFound = true;
			*pPSB = m_aEffectDescDatabase[i].pDesc;
			*pEffectInfo = m_aEffectDescDatabase[i].pPEffectInfo;

		}
		else
			i++;
	}
	return bFound;
}