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
#include<stdio.h> 
#include <frksdk.h>
#include <windows.h>
#include "FrkGraphicsHandler.h"
#include "OGLExtensions.h"
#include "frkmath.h"

FrkGraphicsHandler* FrkGraphicsHandler::s_Inst = NULL;

typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
PFNGLBLENDEQUATIONPROC    glBlendEquation;

HGLRC   g_hRC;
HDC		g_hDC;
extern HWND    g_hwnd;
//extern int g_nHeight;
//extern int g_nWidth;

// --------------------- OpenGL Shader Functions ----------------------------------------------------
PFNGLCREATESHADEROBJECTARBPROC  glCreateShader;
PFNGLSHADERSOURCEARBPROC		glShaderSource;
PFNGLCOMPILESHADERARBPROC		glCompileShader;
PFNGLATTACHSHADERPROC			glAttachShader;
PFNGLDETACHSHADERPROC			glDetachSahder;
PFNGLDELETESHADERPROC			glDeleteShader;
PFNGLGETSHADERINFOLOGPROC		glGetShaderInfoLog;

PFNGLCREATEPROGRAMPROC			glCreateProgram;
PFNGLLINKPROGRAMPROC			glLinkProgram;
PFNGLUSEPROGRAMPROC				glUseProgram;
PFNGLDELETEPROGRAMPROC			glDeleteProgram;
PFNGLGETPROGRAMINFOLOGPROC		glGetProgramInfoLog;

// VERTEX ATTRIBUTE VARIABLE
PFNGLGETATTRIBLOCATIONARBPROC   glGetAttributeLocation;
PFNGLVERTEXATTRIB1FARBPROC		glVertexAttrib1f;
PFNGLVERTEXATTRIB2FARBPROC		glVertexAttrib2f;
PFNGLVERTEXATTRIB3FARBPROC		glVertexAttrib3f;
PFNGLVERTEXATTRIB4FARBPROC		glVertexAttrib4f;

// UNIFORM VARIABLE
PFNGLGETUNIFORMLOCATIONARBPROC  glGetUniformLocation;
PFNGLUNIFORM1FARBPROC			glUniform1f;
PFNGLUNIFORM2FARBPROC			glUniform2f;
PFNGLUNIFORM3FARBPROC			glUniform3f;
PFNGLUNIFORM4FARBPROC			glUniform4f;

/******************************************************************************
Function	:	GraphicsHandler Constructor
Description	:	Creates GraphicsHandler object.
Arguments	:	None.
Return		:	None.
/*****************************************************************************/
FrkGraphicsHandler::FrkGraphicsHandler()
{
	m_vEye.x = 0.0f;
	m_vEye.y = 0.0f;
	m_vEye.z = 0.0f;
	
	m_vLook.x = 0.0f;
	m_vLook.y = 0.0f;
	m_vLook.z = -1.0f;

	m_vUp.x = 0.0f;
	m_vUp.y = 1.0f;
	m_vUp.z = 0.0f;

	m_vRight.x = 1.0f;
	m_vRight.y = 0.0f;
	m_vRight.z = 0.0f;

	m_nShaderProgram  = 0;
	m_nVertexShader   = 0;
	m_nFragmentShader = 0;

	MatrixIdentity(&m_view);

	Vec3Normalize(&m_vLook, &m_vLook);

	Vec3Cross(&m_vRight, &m_vLook, &m_vUp);
	Vec3Normalize(&m_vRight, &m_vRight);

	Vec3Cross(&m_vUp, &m_vRight, &m_vLook);
	Vec3Normalize(&m_vUp, &m_vUp);

	m_view.m00 =  m_vRight.x;
	m_view.m01 =  m_vUp.x;
	m_view.m02 = -m_vLook.x;
	m_view.m03 =  0.0f;

	m_view.m10 =  m_vRight.y;
	m_view.m11 =  m_vUp.y;
	m_view.m12 = -m_vLook.y;
	m_view.m13 =  0.0f;

	m_view.m20 =  m_vRight.z;
	m_view.m21 =  m_vUp.z;
	m_view.m22 =  -m_vLook.z;
	m_view.m23 =  0.0f;

	m_view.m30 = -Vec3Dot(&m_vRight, &m_vEye);
	m_view.m31 = -Vec3Dot(&m_vUp, &m_vEye);
	m_view.m32 =  Vec3Dot(&m_vLook, &m_vEye);
	m_view.m33 =  1.0f;
}

/******************************************************************************
Function	:	FrkGraphicsHandler::LoadPixelShader
Description	:	Loads pixel shader and sets it on device. 
Arguments	:	[In]sShaderName :	String containing the shader name
Return		:	None.
/*****************************************************************************/

void FrkGraphicsHandler::LoadPixelShader (char* sShaderName)
{
	FILE * pFile = NULL;
	char * pShaderBuff = NULL;
	pFile = fopen(sShaderName, "rb");

	if (!pFile) return;
	
	fseek(pFile, 0, SEEK_END);
	int nLength = ftell(pFile);
	
	pShaderBuff = (char *)malloc(nLength+1);
	fseek(pFile, 0, SEEK_SET);
	fread(pShaderBuff, 1, nLength, pFile);
	pShaderBuff[nLength] = '\0';

	// Create the fragment shader object
	m_nFragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);
	glShaderSource(m_nFragmentShader, 1, (const char **)&pShaderBuff, NULL);
	glCompileShader(m_nFragmentShader);

	//// Loads, Creates and Attaches the vertex shader object
	//LoadVertexShader("VertexShader.vert");
	glAttachShader(m_nShaderProgram, m_nFragmentShader);
	glLinkProgram(m_nShaderProgram);
	free(pShaderBuff);
}

/******************************************************************************
Function	:	FrkGraphicsHandler::ShaderPreRender
Description	:	Sets the shader before each render. 
Arguments	:	None.
Return		:	None.
/*****************************************************************************/
void FrkGraphicsHandler::ShaderPreRender ()
{
	GLuint textureSampler;
	textureSampler = glGetUniformLocation(m_nShaderProgram, "texture");
	glUniform1f(textureSampler, 0);
	// use the fragment shader processor
	glUseProgram(m_nShaderProgram);
}

/******************************************************************************
Function	:	FrkGraphicsHandler::ShaderPostRender
Description	:	Ends the pixel shader after each render. 
Arguments	:	None
Return		:	None.
/*****************************************************************************/
void FrkGraphicsHandler::ShaderPostRender ()
{

	// use the fixed functionality pipeline
	glUseProgram(0);
}

/******************************************************************************
Function	:	GraphicsHandler Destructor
Description	:	Destroys the Graphics Handler object, releases the D3D device and object. 
Arguments	:	None.
Return		:	None.
/*****************************************************************************/
FrkGraphicsHandler::~FrkGraphicsHandler(void)
{
	if (m_nFragmentShader && glDeleteShader)
		glDeleteShader(m_nFragmentShader);
	if (m_nVertexShader && glDeleteShader)
		glDeleteShader(m_nVertexShader);
	if (m_nShaderProgram && glDeleteProgram)
		glDeleteProgram(m_nShaderProgram);
}