#include "FPGameManager.h"

HWND GameHwnd = NULL;
FPGameManager *FPGameManager::m_Manager = nullptr;

void FPGameManager::KeyControl(WPARAM wParam, LPARAM lParam) {
	m_gl->KeyHandle(wParam, lParam);
}

void FPGameManager::InitScene() {
	// 初始化OPenGL渲染环境
	m_gl = new GL_Utility(GameHwnd);
	m_gl->setCamPos(glm::vec3(0, 0, 1.2));
	m_gl->setCamView(glm::vec3(0, 0, -1));
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

	m_effectFactory = new EffectFactory();
	m_effectFactory->Init();

	m_modelFactory = new ModelFactory();
	m_modelFactory->Init();

	m_gamer = new Fighter(ModelType::Plane1);
	m_gamer->setDirection(glm::vec3(0, 0, -1));
	m_gamer->setScale(0.2);
	m_gamer->setPos(glm::vec3(0, -8, -50));
}

void FPGameManager::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_gl->CamLook();

	// 绘制云朵
	m_cloud->draw();

	// 绘制飞机
	m_gamer->Draw();

	// 绘制所有GUI
	m_guiManager->RenderGUI();

	m_gl->Flush();
}