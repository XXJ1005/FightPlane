#include "FPGameManager.h"
#include <iostream>
using namespace std;

HWND GameHwnd = NULL;
FPGameManager *FPGameManager::m_Manager = nullptr;

FPGameManager::FPGameManager() {
	// 初始化OpenGL渲染环境
	GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	m_hdc = GetDC(GameHwnd);
	PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, PixelFormat, &pfd);
	m_hrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hrc);

	// 设置透视投影矩阵
	RECT rect;
	GetWindowRect(GameHwnd, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	if (h == 0) { h = 1;}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
}

void FPGameManager::KeyControl(WPARAM wParam, LPARAM lParam) {
	if (m_GameState != FPGameState::Play) {
		return;
	}
	glm::vec3 gamer_pos = m_objManager->getGamer()->getPos();
	float gamer_rotate = m_objManager->getGamer()->getRotate();
	switch (wParam)
	{
		case VK_UP:
			m_camPos.z -= m_walkSpeed;
			gamer_pos.z -= m_walkSpeed;
			break;
		case VK_RIGHT:
			gamer_rotate += m_rotateSpeed;
			break;
		case VK_LEFT:
			gamer_rotate -= m_rotateSpeed;
			break;
		case 'W':
			m_camPos.y += m_walkSpeed;
			gamer_pos.y += m_walkSpeed;
			break;
		case 'S':
			m_camPos.y -= m_walkSpeed;
			gamer_pos.y -= m_walkSpeed;
			break;
		case 'A':
			m_camPos.x -= m_walkSpeed;
			gamer_pos.x -= m_walkSpeed;
			break;
		case 'D':
			m_camPos.x += m_walkSpeed;
			gamer_pos.x += m_walkSpeed;
			break;
		default: break;
	}
	m_objManager->getGamer()->setPosition(gamer_pos);
	m_objManager->getGamer()->setRotate(gamer_rotate);
}

void FPGameManager::InitScene() {
	glClearColor(0.325 / 1.2, 0.621 / 1.2, 0.847 / 1.2, 1.0f);
	glClearDepth(1.0f);
	m_walkSpeed = 0.5;
	m_rotateSpeed = 2.0;
	m_camPos = glm::vec3(0, 0, 0);

	// 设置游戏状态
	m_GameState = FPGameState::Play;

	// 初始化游戏UI界面
	m_guiManager = new FPGUIManager();
	m_guiManager->InitGUI();

	// 播放所有声音
	m_soundManager = new FPSoundManager();
	m_soundManager->PlayStartGameBGM();

	// 初始化游戏对象管理器
	m_objManager = new FPOBJManager();
	m_objManager->InitOBJ();

	// 初始化云朵
	m_cloud = new Cloud("../media/cloud.png", Color4F(0.9, 0.9, 0.9, 1.0), 2);
}

void FPGameManager::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_camPos[0], m_camPos[1], m_camPos[2], m_camPos[0], m_camPos[1], m_camPos[2] -1, 0, 1, 0);

	if (m_GameState == FPGameState::Play) {
		m_cloud->Draw();	      // 绘制云朵
		m_objManager->DrawOBJ();  // 绘制游戏对象
	}
	
	// 绘制GUI
	//m_guiManager->RenderGUI();

	SwapBuffers(m_hdc);
}

void FPGameManager::Update() {
	if (m_GameState == FPGameState::Play) {
		m_cloud->Update();
		m_objManager->UpDate();

		int score = m_objManager->getScore();
		int blood = m_objManager->getBlood();

		cout << "score: " << score << endl;
		cout << "blood:" << blood << endl;

		/*if (score = 100) {
			m_GameState == FPGameState::Success;
		}
		if (blood <= 0) {
			m_GameState == FPGameState::Failure;
		}*/
	}
}