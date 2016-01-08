#include "FPGameManager.h"

HWND GameHwnd = NULL;
FPGameManager *FPGameManager::m_Manager = nullptr;

void FPGameManager::KeyControl(WPARAM wParam, LPARAM lParam) {
	m_gl->KeyHandle(wParam, lParam);
}

void FPGameManager::InitScene() {
	// ��ʼ��OPenGL��Ⱦ����
	m_gl = new GL_Utility(GameHwnd);
	m_gl->setCamPos(Point3F(0, 0, 1.2));
	m_gl->setCamView(Point3F(0, 0, -1));
	m_gl->setWalkSpeed(2);
	glClearColor(0.325 / 1, 0.621 / 1, 0.847 / 1, 1.0f);
	glClearDepth(1.0f);

	// ������Ϸ״̬
	m_GameState = FPGameState::Start;

	// ��ʼ����ϷUI����
	m_guiManager = new FPGUIManager();
	m_guiManager->InitGUI();

	// ��ʼ����Ϸ��Դ
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

	// �����ƶ�
	m_cloud->draw();

	// ���Ƶ���
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

	// ���Ʒɻ�
	glPushMatrix();
	glTranslated(0, -8, -50);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	plane->draw();
	glPopMatrix();

	// ���ƻ���
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

	// ��������GUI
	m_guiManager->RenderGUI();

	m_gl->Flush();
}