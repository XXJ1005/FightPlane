#pragma once

class FPGameManager {
public:
	enum FPGameState { Start, Play, Success, Failure };

	FPGameManager() {}

	static FPGameManager *GetInstance() { 
		if (m_Manager == nullptr){
			m_Manager = new FPGameManager();
		}

		return m_Manager;
	}

	FPGameState GetCurrentGameState() { return m_GameState; }
	void SetCurrentGameState(FPGameState gameState) { m_GameState = gameState; }

private:
	static FPGameManager *m_Manager;
	FPGameState m_GameState;
};