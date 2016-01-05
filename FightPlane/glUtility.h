#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/GL.h>
#include <gl/GLU.h>

class GL_Utility {
public:
	GL_Utility(HWND hwnd);
	~GL_Utility();

	void CamLook();
	void Reshape();
	void KeyHandle(WPARAM wParam, LPARAM lParam);

	bool InitScene(double *camPos, double *camView, double walkSpeed);
	void Draw();

private:
	HGLRC m_hrc;
	HWND m_hwnd;
	HDC  m_hdc;

	double m_walkSpeed;
	double m_camPos[3];
	double m_camView[3];
};