#include "FPOBJManager.h"
#include <iostream>
using namespace std;

void FPOBJManager::InitOBJ() {
	// ��ʼ�����ս��
	m_gamer = new GamerFighter();
	m_gamer->setScale(0.1);
	m_gamer->setRotate(0);
	m_gamer->setDirection(glm::vec3(0, 0, -1));
	m_gamer->setPosition(glm::vec3(0, -2, -16));

	// ��ʼ���л���
	for (int i = 0; i < 20; i++) {
		m_enemys.push_back(new EnemyFighter());
	}

	// ��ʼ��������
	for (int i = 0; i < 50; i++) {
		m_gamerMissile.push_back(new Missile());
	}
	for (int i = 0; i < 100; i++) {
		m_enemyMissile.push_back(new Missile());
	}

	addEnemyFighter();
	addEnemyFighter();
	addEnemyFighter();
}

void FPOBJManager::addGamerMissile(glm::mat4 pose) {
	for (int i = 0; i < m_gamerMissile.size(); i++) {
		if (m_gamerMissile[i]->isIdle()) {
			m_gamerMissile[i]->setIsIdle(false);
			m_gamerMissile[i]->setOriginPose(pose);
			m_gamerMissile[i]->setMissileState(Missile::MissileState::Ready);
			break;
		}
	}
}

void FPOBJManager::addEnemyMissile(glm::mat4 pose) {
	for (int i = 0; i < m_enemyMissile.size(); i++) {
		if (m_enemyMissile[i]->isIdle()) {
			m_enemyMissile[i]->setIsIdle(false);
			m_enemyMissile[i]->setOriginPose(pose);
			m_enemyMissile[i]->setMissileState(Missile::MissileState::Ready);
			break;
		}
	}
}

void FPOBJManager::addEnemyFighter() {
	for (int i = 0; i < m_enemys.size(); i++) {
		if (m_enemys[i]->isIdle()) {
			m_enemys[i]->setIsIdle(false);
			m_enemys[i]->setScale(0.1);
			//float rotate = (m_rng.nextFloat() - 0.5) * 90;
			//m_enemys[i]->setRotate(rotate);
			m_enemys[i]->setDirection(glm::vec3(0, 0, 1));
			float x = 40.0 * m_rng.nextFloat() - 20;
			float y = -10.0 * m_rng.nextFloat() + 5;
			float z = -80 + 10 * m_rng.nextFloat() - 5;
			m_enemys[i]->setPosition(glm::vec3(x, y, z));
			break;
		}
	}
}

void FPOBJManager::DrawOBJ() {
	m_gamer->Draw();

	for(int i = 0; i < m_enemys.size(); i++){
		if (!m_enemys[i]->isIdle()) {
			m_enemys[i]->Draw();
		}
	}
	for (int i = 0; i < m_gamerMissile.size(); i++) {
		m_gamerMissile[i]->Draw();
	}
	for (int i = 0; i < m_enemyMissile.size(); i++) {
		m_enemyMissile[i]->Draw();
	}
}

void FPOBJManager::UpDate() {
	// ���ս����л�������ײ���
	for (int i = 0; i < m_enemys.size(); i++) {
		if (!m_enemys[i]->isIdle()) {
			bool test = CollisionDect(m_gamer->getCoverBox(), m_gamer->getWorldPose(), m_enemys[i]->getCoverBox(), m_enemys[i]->getWorldPose());
			if (test) {
				m_gamer->DealCollision(m_enemys[i]->getDamage());
				m_enemys[i]->DealCollision(m_gamer->getDamage());
			}
		}
	}
	// ���ս����з�������ײ���
	for (int i = 0; i < m_enemyMissile.size(); i++) {
		if (!m_enemyMissile[i]->isIdle()) {
			bool test = CollisionDect(m_gamer->getCoverBox(), m_gamer->getWorldPose(), m_enemyMissile[i]->getCoverBox(), m_enemyMissile[i]->getWorldPose());
			if (test) {
				m_gamer->DealCollision(m_enemyMissile[i]->getDamage());
				m_enemyMissile[i]->DealCollision(m_gamer->getDamage());
			}
		}
	}

	// ��ҵ�����з�ս����ײ���
	for (int i = 0; i < m_gamerMissile.size(); i++) {
		if (!m_gamerMissile[i]->isIdle()) {
			for (int j = 0; j < m_enemys.size(); j++) {
				if (!m_enemys[j]->isIdle()) {
					bool test = CollisionDect(m_enemys[j]->getCoverBox(), m_enemys[j]->getWorldPose(), m_gamerMissile[i]->getCoverBox(), m_gamerMissile[i]->getWorldPose());
					if (test) {
						m_enemys[j]->DealCollision(m_gamerMissile[i]->getDamage());
						m_gamerMissile[i]->DealCollision(m_enemys[j]->getDamage());
						m_score++;
					}
				}
			}
		}
	}
	
	// ս�����£���Ҫ�Ƿ��䵼��
	m_gamer->Update(this);
	int count= 0;
	for (int i = 0; i < m_enemys.size(); i++) {
		if (!m_enemys[i]->isIdle()) {
			m_enemys[i]->Update(this);
			count++;
		}
	}
	cout << "�л�" << count<< endl;
	for (int i = 0; i < 3-count; i++) {
		addEnemyFighter();
	}
}