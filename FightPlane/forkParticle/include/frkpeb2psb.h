#ifndef _Peb2PsbExport_H_
#define _Peb2PsbExport_H_ 

#define PC_ALIGN_SIZE	 16
#define XENON_ALIGN_SIZE 16
#define PS3_ALIGN_SIZE	 16
#define X64_ALIGN_SIZE	 16

#define frkPSBPC_IDENTIFIER				0x463D
#define frkPSBPS3_IDENTIFIER			0x563D
#define frkPSBXBOX360_IDENTIFIER		0x663D
#define frkPSBX64_IDENTIFIER			0x763D
#define frkPSBMAC_IDENTIFIER			0x863D


enum ePeb2PsbExport_Target {
	ePEB2PSB_TARGET_PC,	
	ePEB2PSB_TARGET_XBOX360,
	ePEB2PSB_TARGET_PS3,
	ePEB2PSB_TARGET_X64,
	ePEB2PSB_TARGET_MAC
};

enum ePeb2PsbExport_AssetLib {
	ePEB2PSB_ASSETLIB_TEXTURE,
	ePEB2PSB_ASSETLIB_PARTICLE
};

enum ePeb2PsbExport_Asset {
	ePEB2PSB_TEXTURE,
	ePEB2PSB_MODEL,
	ePEB2PSB_REFEMITTER
};

enum ePeb2PsbExport_VerboseLevel
{
	ePEB2PSB_VERBOSELEVEL_OFF = 0,
	ePEB2PSB_VERBOSELEVEL_1
};

//typedef struct _t_frkmatrix4 t_frkMatrix4;

typedef struct _t_peb2psbexportoutputinfo
{
	unsigned char** aImages;			// Array of PSB data memory images 
	int*			aImageSizes;		// Array of PSB data memory image sizes
	int				nImageCount;		// PSB data memory image count
	char**			aImageNames;		// Array of PSB names

	_t_peb2psbexportoutputinfo()
	{
		aImages		= 0;
		aImageSizes = 0;
		nImageCount = 0;
		aImageNames = 0;
	}

} t_Peb2PsbExportOutputInfo;


typedef void (*VerboseCB) (const char *sMsg);

class Peb2PsbUtility;

class Peb2PsbExport
{
public:
	Peb2PsbExport(void);
	~Peb2PsbExport(void);
	// Begin PEB Process
	void Open();
	// Set input paths for older PEB file versions
	int SetAssetPath(ePeb2PsbExport_AssetLib nDirectory, char *sPath);
	// Enable platform export
	int Enable(ePeb2PsbExport_Target nExportTarget, bool bVal);
	// Process conversion
	int Process(char* sPEBInFileName, bool bIncludeAssetPaths, bool bRelativePaths = false);
	// Get external reference asset paths
	int GetAssets(ePeb2PsbExport_Asset nAssetType, char** aAssetPaths[], int *nAssetCount, bool bRelativePath = false);
	// Get xref paths
	void GetXrefList(char** aXrefPaths[], int *nXrefCount);
	// Get export PSB memory image 
	int GetPsb(ePeb2PsbExport_Target nTargetPlatform, t_Peb2PsbExportOutputInfo& Peb2PsbInfo);
	int ExportTRKFile(char* sOutputPathPC, char *sOutputPathXBOX, char *sOutputPathPS3) ;
	static void ProcessRefEmitterChunk(char* sName, void* pData, unsigned int nDataSize);
	// End PEB Process
	void Close();
	int GetRootPaths(ePeb2PsbExport_Asset nAssetType, char** sOutPath);
	void SetVerbose(VerboseCB pCB, ePeb2PsbExport_VerboseLevel verboseLevel);
 
protected:
	VerboseCB				m_pVerboseCB;
	bool					m_bRelativePaths;
	static Peb2PsbUtility*	pUtility;

protected:
	int ProcessFile(char* sPEBInFileName, bool bIncludeAssetPaths, bool bRelativePaths = false,int* nTotalEmitters=0);	
};


#endif
