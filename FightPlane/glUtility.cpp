#include "glUtility.h"

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

	m_camPos = Point3F(0,0,0);
	m_camView = Point3F(0, 0, -1);
	m_walkSpeed = 1;

	Reshape();
}

GL_Utility::~GL_Utility() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hrc);
	ReleaseDC(m_hwnd, m_hdc);
}

void GL_Utility::CamLook() {
	gluLookAt(m_camPos.x, m_camPos.y, m_camPos.z,
		m_camPos.x + m_camView.x, m_camPos.y + m_camView.y, m_camPos.z + m_camView.z,
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
			m_camPos.z += m_walkSpeed;
			break;
		case VK_UP:
			m_camPos.z -= m_walkSpeed;
			break;
		case VK_RIGHT:
			break;
		case VK_LEFT:
			break;
		case 'W':
			m_camPos.y += m_walkSpeed;
			break;
		case 'S':
			m_camPos.y -= m_walkSpeed;
			break;
		case 'A':
			m_camPos.x -= m_walkSpeed;
			break;
		case 'D':
			m_camPos.x += m_walkSpeed;
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
