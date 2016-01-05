#include "ParticleEffect.h"
#include "glUtility.h"
#include "FightPlane.h"
#include "Load3ds.h"

GL_Utility::GL_Utility(HWND hwnd) {
	m_hwnd = hwnd;
	GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	m_hdc = GetDC(m_hwnd);
	PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, PixelFormat, &pfd);
	m_hrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hrc);

	m_camPos[0] = 0, m_camPos[1] = 0, m_camPos[2] = 0;
	m_camView[0] = 0, m_camView[1] = 0, m_camView[2] = -1;
	m_walkSpeed = 1;

	Reshape();
}

GL_Utility::~GL_Utility() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hrc);
	ReleaseDC(m_hwnd, m_hdc);
}

void GL_Utility::CamLook() {
	gluLookAt(m_camPos[0], m_camPos[1], m_camPos[2],
		m_camPos[0] + m_camView[0], m_camPos[1] + m_camView[1], m_camPos[2] + m_camView[2],
		0.0, 1.0, 0.0
		);
}

void GL_Utility::KeyHandle(WPARAM wParam, LPARAM lParam) {
	switch (wParam)
	{
	case VK_ESCAPE:
		PostMessage(m_hwnd, WM_CLOSE, 0, 0);
		break;
	case VK_DOWN:
		m_camPos[2] += m_walkSpeed;
		break;
	case VK_UP:
		m_camPos[2] -= m_walkSpeed;
		break;
	case VK_RIGHT:
		break;
	case VK_LEFT:
		break;
	case 'W':
		m_camPos[1] += m_walkSpeed;
		break;
	case 'S':
		m_camPos[1] -= m_walkSpeed;
		break;
	case 'A':
		m_camPos[0] -= m_walkSpeed;
		break;
	case 'D':
		m_camPos[0] += m_walkSpeed;
		break;
	default: break;
	}
}

void GL_Utility::Reshape() {
	RECT rect;
	GetWindowRect(m_hwnd, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	if (h == 0) {
		h = 1;
	}

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
}


Cloud *cloud = NULL;
ParticleEffect* recover = NULL;
Model_3DS *plane = NULL;

bool GL_Utility::InitScene(double *camPos, double *camView, double walkSpeed = 1) {
	m_camPos[0] = camPos[0], m_camPos[1] = camPos[1], m_camPos[2] = camPos[2];
	m_camView[0] = camView[0], m_camView[1] = camView[1], m_camView[2] = camView[2];
	m_walkSpeed = walkSpeed;

	// ========

	glClearColor(0.325f, 0.621f, 0.847f, 1.0f);
	glClearDepth(1.0f);

	recover = new ParticleEffect("../media/effects/", "magic02");

	cloud = new Cloud("../media/cloud.png", 2);
	plane = new Model_3DS("../media/plane.3ds", "../media/plane.bmp");

	
	return true;
}

void GL_Utility::Draw() {
	// ========

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CamLook();

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
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);

	SwapBuffers(m_hdc);
}