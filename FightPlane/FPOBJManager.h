#pragma once

#include "media.h"

class FPOBJManager {
public:
	FPOBJManager() {}
	void InitOBJ();
	void DrawOBJ();
	void UpDate();

	GamerFighter* getGamer() { return m_gamer;}
	int getScore() { return m_score; }
	int getBlood() { return m_gamer->getBlood() / 20; }

	void addGamerMissile(glm::mat4 pose);

	void addEnemyMissile(glm::mat4 pose);

	void addEnemyFighter();

private:
	GamerFighter *m_gamer;
	std::vector<EnemyFighter*> m_enemys;
	std::vector<Missile*> m_gamerMissile;
	std::vector<Missile*> m_enemyMissile;

	int m_score;
	Rng m_rng;
};
