#pragma once
#include "FPmath.h"

class Path {
public:
	Path(){}
	virtual ~Path() {}
	virtual glm::mat4 getNextPose() = 0;
	virtual void reset() = 0;
};

class LinePath :public Path {
public:
	LinePath(glm::vec3 dir, float speed = 0.5) {
		m_dir = glm::normalize(dir);
		m_t = 0;
		m_speed = speed +2;
	}
	glm::mat4 getNextPose() {
		glm::mat4 pose(1.0f);
		// Æ½ÒÆ
		pose = glm::translate(pose, m_dir * m_t);
		// Ðý×ª
		if (m_dir.x == 0 && m_dir.y == 0 && m_dir.z == 1) {
			pose = glm::rotate(pose, 180.0f, glm::vec3(0.0, 1.0, 0.0));
		}
		else if (m_dir.x != 0 || m_dir.y != 0 || m_dir.z != -1) {
			glm::vec3  rotateAxis = glm::cross(glm::vec3(0, 0, -1), m_dir);
			float degree = glm::acos(glm::dot(glm::vec3(0, 0, -1), m_dir));
			pose = glm::rotate(pose, float(degree * 180.0 / PI), rotateAxis);
		}
		m_t += m_speed;
		return pose;
	}
	void reset() {
		m_t = 0;
	}
private:
	float m_t;
	float m_speed;
	glm::vec3 m_dir;
};