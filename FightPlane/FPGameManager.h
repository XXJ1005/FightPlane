#pragma once
#include "FPOBJManager.h"
#include "FPGUIManager.h"
#include "FPSoundManager.h"

extern HWND GameHwnd;  // ��Ϸ���ھ��

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
	static FPGameManager *m_Manager;  // ����ģʽ,ָ������

	FPGameState m_GameState;        // ��Ϸ��ǰ����״̬
	FPGUIManager *m_guiManager;     // GUI������
	FPSoundManager *m_soundManager; // Sound������
	FPOBJManager *m_objManager;     // ��Ϸ���������
	Cloud *m_cloud;                 // �ƶ����ƣ���Ϸ����

	HGLRC m_hrc;
	HDC  m_hdc;
	double m_rotateSpeed;
	double m_walkSpeed;
	glm::vec3 m_camPos;
};