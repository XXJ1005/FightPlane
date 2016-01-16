#pragma once
#include "FPOBJManager.h"
#include "FPGUIManager.h"
#include "FPSoundManager.h"

extern HWND GameHwnd;  // 游戏窗口句柄

class FPGameManager {
public:
	enum FPGameState { Start, Play, Success, Failure };
	~FPGameManager() {
		if (m_cloud) {
			delete m_cloud;
		}
		if (m_guiManager) {
			delete m_guiManager;
		}
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hrc);
		ReleaseDC(GameHwnd, m_hdc);
	}

	void KeyControl(WPARAM wParam, LPARAM lParam);
	void InitScene();
	void Draw();
	void Update();

	FPGUIManager *GetGuiManager() { return m_guiManager; }
	FPSoundManager *GetSoundManager() { return m_soundManager; }
	FPOBJManager *GetOBJManager() { return m_objManager; }
	FPGameState GetCurrentGameState() { return m_GameState; }

	void SetCurrentGameState(FPGameState gameState) { m_GameState = gameState; }

	static FPGameManager *GetInstance() { 
		if (m_Manager == NULL) {
			m_Manager = new FPGameManager();
		}
		return m_Manager; 
	}

private:

	FPGameManager();
	static FPGameManager *m_Manager;  // 单例模式,指向自身

	FPGameState m_GameState;        // 游戏当前所处状态
	FPGUIManager *m_guiManager;     // GUI管理器
	FPSoundManager *m_soundManager; // Sound管理器
	FPOBJManager *m_objManager;     // 游戏对象管理器
	Cloud *m_cloud;                 // 移动的云，游戏背景

	HGLRC m_hrc;
	HDC  m_hdc;
	double m_rotateSpeed;
	double m_walkSpeed;
	glm::vec3 m_camPos;
};