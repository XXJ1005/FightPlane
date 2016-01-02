/******************************************************************************
Disclaimer Notice:
This file is provided as is with no warranties of any kind and is
provided without any obligation on Fork Particle, Inc. to assist in 
its use or modification. Fork Particle, Inc. will not, under any
circumstances, be liable for any lost revenue or other damages arising 
from the use of this file.

(c) Copyright 2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#pragma once
#ifndef FRKDATASERVER_H
#define FRKDATASERVER_H

#define frkPARTICLESYSTEM_MAX_ENTRIES             128	// Max Entries in Asset Database.
#define frkPARTICLESYSTEM_MAX_PATH_LENGTH		  256	// Max Lenght of Resource Path.
#define frkPARTICLESYSTEM_MAX_NAME_LENGTH		  256	// Max Lenght of Database Emtry Name.
#define frkPARTICLESYSTEM_MAX_EMITTERS_IN_PACKAGE 256

#include <stdio.h>
#include <string>
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glaux.h>


using namespace std;

typedef struct _IAssetInfoNode {
	char			sName[256];
	void*			pData;
} IAssetInfoNode;

typedef struct _TextureAssetInfoNode {
	string				sName;
	GLuint				nTextureID;
}TextureAssetInfoNode;

// Hold a Model Asset for Emitter System.
typedef struct _ModelAssetInfoNode {
	string				sName;
	void*			pModel;
} ModelAssetInfoNode;


//Holds Description of an Emitter.
typedef struct _EmitterDescNode {
	string				sName;
	void*				pDesc;
	int					nSize;
}EmitterDescNode;

typedef struct _EffectDescNode {
	string				sName;
	void*				pDesc;
	_t_frkPEffectInfo*   pPEffectInfo;
	int nNumRefs;
}EffectDescNode;
/************************************************************************/
//	Class:			DataServer
//	Description:	Holds the Particle System.
/************************************************************************/
class FrkDataServer{
public:
	static FrkDataServer* GetInstance()
	{
		if (!s_Inst)
		{
			s_Inst = new FrkDataServer();
			return s_Inst;
		}

		return s_Inst;
	}

	static void DestroyInstance()
	{
		if (s_Inst)
			delete s_Inst;
	}
private: 
	int						m_nNumTextureAssetCount;
	int						m_nNumModelAssetCount;
	int						m_nNumEmitterDescCount;
	int						m_nNumPsbPackageDescCount;
	int						m_nNumEffectDescCount;

	TextureAssetInfoNode	m_aTextureAssetDatabase[frkPARTICLESYSTEM_MAX_ENTRIES];
	ModelAssetInfoNode		m_aModelsAssetDatabase[frkPARTICLESYSTEM_MAX_ENTRIES];
	EmitterDescNode			m_aEmitterDescDatabase[frkPARTICLESYSTEM_MAX_ENTRIES];
	EffectDescNode			m_aEffectDescDatabase[frkPARTICLESYSTEM_MAX_ENTRIES];

	static char				m_sMediaPath[frkPARTICLESYSTEM_MAX_PATH_LENGTH];
public:
	void Init(){}
	// Virtual Interface Functions.
	virtual void* LoadEmitter(const char* sName);
	virtual void* DataServerLoadTunerInfo(char* sName, _t_frkPEmitterInfo* pEDesc);

	bool DestroyEffectInfo(_t_frkPEffectInfo** pEffectInfo);	

	virtual void* EmitterDescUpdate(_t_frkPEmitter* pEmitter, _t_frkPEmitterInfo* pPSB, int nSize );
	virtual void GetCurrentTextureName(_t_frkPEmitter* pEmitter, char *sTextureName);

	virtual void* LoadModel(char* sKey);
	virtual void* LoadTexture(char* sKey);

	virtual void Unload();
	void* LoadEffect(const char* sName);
	static void* UserLoadAssetCB(_t_frkAssetInfo* pAsset, void* pUserData);

	// Media Path Function For Application
	static void SetMediaPath(char* sPath); 
	static char* GetMediaPath(); 
public:
	bool RetrieveEffect(const char* pFileName, void **pPSB, _t_frkPEffectInfo** pEffectInfo);
	void SetEffectInfo(const char* pFileName, _t_frkPEffectInfo* pEffectInfo);
	//Support Member Functions
	void* SearchEmitterDescs(const char* pFileName);
	// Support Search Functions
	EffectDescNode* SearchEffectDescs(_t_frkPEffectInfo* pDesc);
	void* SearchEffectDescs(const char* pFileName);
	void* SearchTextures ( char* sName );
	void* SearchModels ( char* sName );
	int SearchEmptySlot(IAssetInfoNode* aArray, int nStartIdx, int nStride, int nMaxEntries);
	FrkDataServer();
	~FrkDataServer(void);
	void GetPSBData(void* pPackageDesc, char** pEmitterNames, int *nEmitterCount, _t_frkPEmitterInfo** aEInfo, char** sTrackName);
	bool LoadPSBPackage(const char *sFileName, void **pPSB, _t_frkPEffectInfo **pEffectInfo);
	_t_frkAnmTrk* LoadNoteTrkFromPackage(char *sInEventTrkName, void *pPackageDesc);
	_t_frkAnmTrk* LoadNoteTrkFile(char *sInFileName);
	static FrkDataServer *s_Inst;
};

#endif