
#include <windows.h>  
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <atlimage.h>

#include "ParticleEffect.h"
#include "main.h"
#include "FightPlane.h"

#include "Load3ds.h"

const double walk_speed = 1.0;
double cam_pos[3] = { 0, 0, 1.2};
HGLRC hRC = NULL;
HWND hWnd = NULL;
HDC  hDC = NULL;

Cloud *cloud;
GLuint texture = 0;
ParticleEffect* recover = NULL;
Model_3DS *plane;

void camLook(){
	gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2],
			cam_pos[0], cam_pos[1], cam_pos[2] - 1,
			0.0, 1.0, 0.0
			);
}

void DrawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camLook();

	cloud->draw();

	glPushMatrix();
	glTranslated(0, 1, -10);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	plane->draw();
	glPopMatrix();


	glEnable(GL_TEXTURE_2D);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	glTranslated(0, 1, -10);
	//glColor3f(177/255.0, 17/255.0, 22/255.0);
	recover->Frame();
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glDisable( GL_BLEND );

	glDisable(GL_TEXTURE_2D);
}

void InitOpenGL()
{
	GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	hDC = GetDC(hWnd);
	PixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, PixelFormat, &pfd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
}

bool InitScene(){
	glClearColor(0.325, 0.621, 0.847, 1.0);
	glClearDepth(1.0f);

	recover = new ParticleEffect("../media/effects/", "magic02");

	cloud = new Cloud("../media/cloud.png", 2);
	plane = new Model_3DS("../media/plane.3ds", "../media/plane.bmp");

	return true;
}

void DestroyOpenGL()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}

void KeyHandle(WPARAM wParam, LPARAM lParam) {
	switch (wParam)
	{
	case VK_ESCAPE:
		PostMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	case VK_DOWN:
		cam_pos[2] += walk_speed;
		break;
	case VK_UP:
		cam_pos[2] -= walk_speed;
		break;
	case VK_RIGHT:
		break;
	case VK_LEFT:
		break;
	case 'W':
		cam_pos[1] += walk_speed;
		break;
	case 'S':
		cam_pos[1] -= walk_speed;
		break;
	case 'A':
		cam_pos[0] -=  walk_speed;
		break;
	case 'D':
		cam_pos[0] += walk_speed;
		break;
	default: break;
	}
}

void Reshape() {
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	if (h == 0){
		h = W_HEIGHT;
		w = W_WIDTH;
	}

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f); 
}