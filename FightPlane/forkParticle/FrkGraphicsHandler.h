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
#include "frksdk.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include "gl/glext.h"
#include "frkmath.h"

/************************************************************************/
//	Class:			FrkGraphicsHandler
//	Description:	Displays the Particle System using Direct 3D.
/************************************************************************/
class FrkGraphicsHandler
{
public:
	int i;

	t_frkVector3 m_vEye;   // Eye Position
	t_frkVector3 m_vLook;  // Look Vector
	t_frkVector3 m_vUp;    // Up Vector
	t_frkVector3 m_vRight; // Right Vector
	t_frkMatrix4 m_view;

	GLuint m_nFragmentShader;
	GLuint m_nVertexShader;
	GLuint m_nShaderProgram;

	float fLookAtX;
	float fLookAtY;
	float fLookAtZ;

	static FrkGraphicsHandler* GetInstance()
	{
		if (!s_Inst)
		{
			s_Inst = new FrkGraphicsHandler();
			return s_Inst;
		}
		return s_Inst;
	}

	static void DestroyInstance() 
	{
		if (s_Inst)
		{
			delete s_Inst;
			s_Inst = NULL;
		}
	}

	// Render Functions
	bool BeginRender();
	void EndRender();

	// Shader Functions
	void LoadPixelShader(char* sShaderName);
	void ShaderPreRender();
	void ShaderPostRender();

private:
	static FrkGraphicsHandler* s_Inst;

	FrkGraphicsHandler();
	~FrkGraphicsHandler();

};
