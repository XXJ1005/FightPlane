#pragma once
#include "media.h"
#include "glUtility.h"
#include "FPGUIManager.h"

extern HWND GameHwnd;  // ��Ϸ���ھ��

class FPGameManager {
public:
	enum FPGameState { Start, Play, Success, Failure };

	void KeyControl(WPARAM wParam, LPARAM lParam);
	void InitScene();
	void Draw();

	FPGUIManager *GetGuiManager() { return m_guiManager; }
	FPGameState GetCurrentGameState() { return m_GameState; }
	EffectFactory *GetEffectFactory() { return m_effectFactory; }
	ModelFactory *GetModelFactory() { return m_modelFactory; }

	void SetCurrentGameState(FPGameState gameState) { m_GameState = gameState; }

	static FPGameManager *GetInstance() { 
		if (m_Manager == NULL) {
			m_Manager = new FPGameManager();
		}
		return m_Manager; 
	}

private:
	FPGameManager() {}

	FPGameState m_GameState;        // ��Ϸ��ǰ����״̬
	GL_Utility *m_gl;               // OpenGL������
	FPGUIManager *m_guiManager;     // GUI������

	Cloud *m_cloud;                 // �ƶ�����

	EffectFactory *m_effectFactory; // ��Ч����
	ModelFactory *m_modelFactory;   // ģ�͹���

	FPModel *m_gamer;

	static FPGameManager *m_Manager;  // ����ģʽ,ָ������
};