#pragma once
#include "media.h"
#include "glUtility.h"
#include "FPGUIManager.h"

extern HWND GameHwnd;  // 游戏窗口句柄

class FPGameManager {
public:
	enum FPGameState { Start, Play, Success, Failure };

	void KeyControl(WPARAM wParam, LPARAM lParam);
	void InitScene();
	void Draw();

	GL_Utility *GetGLUtility() { return m_gl; }
	FPGUIManager *GetGuiManager() { return m_guiManager; }
	FPGameState GetCurrentGameState() { return m_GameState; }
	void SetCurrentGameState(FPGameState gameState) { m_GameState = gameState; }

	static FPGameManager *GetInstance() { 
		if (m_Manager == NULL) {
			m_Manager = new FPGameManager();
		}
		return m_Manager; 
	}

private:
	FPGameManager() {}

	FPGameState m_GameState;    // 游戏当前所处状态
	GL_Utility *m_gl;           // OpenGL管理器
	FPGUIManager *m_guiManager; // GUI管理器

	Cloud *m_cloud;             // 移动的云
	ParticleEffect* jetFlame;
	Model3DS *plane;
	Model3DS *missile;

	static FPGameManager *m_Manager;  // 单例模式,指向自身
};