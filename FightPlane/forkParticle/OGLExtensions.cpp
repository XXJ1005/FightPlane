#include "OGLExtensions.h"

bool CheckExtension(char *pExtensionName)
{
	char *pExtensionList = (char *)glGetString(GL_EXTENSIONS);
	char *pTempExtensionList = pExtensionList;
	bool bIsFound = false;

	while (*pTempExtensionList)
	{
		int nExtensionListNameSize = (int)strcspn(pTempExtensionList, " ");

		if( (strlen(pExtensionName) == nExtensionListNameSize) && 
			(strncmp(pExtensionName, pTempExtensionList, nExtensionListNameSize) == 0) )
			return true;

		pTempExtensionList += nExtensionListNameSize + 1;
	}
	return false;
}

void * LoadExtension(char *pExtensionName)
{
	return wglGetProcAddress(pExtensionName);
}