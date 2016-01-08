#include "FPGameManager.h"

HWND GameHwnd = NULL;
FPGameManager *FPGameManager::m_Manager = nullptr;

void FPGameManager::KeyControl(WPARAM wParam, LPARAM lParam) {
	m_gl->KeyHandle(wParam, lParam);
}

void FPGameManager::InitScene() {
	// 初始化OPenGL渲染环境
	m_gl = new GL_Utility(GameHwnd);
	m_gl->setCamPos(Point3F(0, 0, 1.2));
	m_gl->setCamView(Point3F(0, 0, -1));
	m_gl->setWalkSpeed(2);
	glClearColor(0.325 / 1, 0.621 / 1, 0.847 / 1, 1.0f);
	glClearDepth(1.0f);

	// 设置游戏状态
	m_GameState = FPGameState::Start;

	// 初始化游戏UI界面
	m_guiManager = new FPGUIManager();
	m_guiManager->InitGUI();

	// 初始化游戏资源
	m_cloud = new Cloud("../media/cloud.png", Color4F(0.9, 0.9, 0.9, 1.0), 3);
	jetFlame = new ParticleEffect("../media/effects/", "fire_sample");
	missile = new Model3DS("../media/missile1/model.3ds", "../media/missile1/texture.png");
	plane = new Model3DS("../media/plane1/model.3ds", "../media/plane1/texture.png");
}

void FPGameManager::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_gl->CamLook();

	// 绘制云朵
	m_cloud->draw();

	// 绘制导弹
	glPushMatrix();
	glTranslated(-6, -10.2, -47);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	missile->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(6, -10.2, -47);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	missile->draw();
	glPopMatrix();

	// 绘制飞机
	glPushMatrix();
	glTranslated(0, -8, -50);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	plane->draw();
	glPopMatrix();

	// 绘制火焰
	glPushMatrix();
	glTranslated(6, -10.2, -42);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	jetFlame->Frame(3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-6, -10.2, -42);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	jetFlame->Frame(3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -8.5, -40);
	glRotatef(90, 1, 0, 0);
	glScalef(0.4, 0.4, 0.4);
	jetFlame->Frame(6);
	glPopMatrix();

	// 绘制所有GUI
	m_guiManager->RenderGUI();

	m_gl->Flush();
}