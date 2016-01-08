#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "FPmath.h"

class GL_Utility {
public:
	GL_Utility(HWND hwnd);
	~GL_Utility();

	void CamLook();
	void Reshape();
	void Flush() { SwapBuffers(m_hdc); }
	void KeyHandle(WPARAM wParam, LPARAM lParam);

	void setWalkSpeed(float walkSpeed) { m_walkSpeed = walkSpeed; }
	void setCamPos(Point3F camPos) { m_camPos = camPos; }
	void setCamView(Point3F camView) { m_camView = camView; }

private:
	HGLRC m_hrc;
	HWND m_hwnd;
	HDC  m_hdc;

	float m_walkSpeed;
	Point3F m_camPos;
	Point3F m_camView;
};