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
	void setCamPos(glm::vec3 camPos) { m_camPos = camPos; }
	void setCamView(glm::vec3 camView) { m_camView = camView; }

private:
	HGLRC m_hrc;
	HWND m_hwnd;
	HDC  m_hdc;

	float m_walkSpeed;
	glm::vec3 m_camPos;
	glm::vec3 m_camView;
};