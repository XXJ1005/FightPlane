#pragma once
#include <vector>
#include "FPmath.h"
#include "ParticleEffect.h"

// ��
class Cloud {
public:
	Cloud(const char *imgPath, Color4F color, int speed = 1);
	void update();
	void draw();

	void setSpeed(int speed) {
		m_speed = speed > 0 ? speed : 1;
	}
	void setColor(Color4F &color) { m_color = color; }

private:
	Rng m_rand;
	unsigned int m_texture;
	int m_speed;
	Color4F m_color;
	std::vector<Rect *> m_rects;
};

class EffectFactory {
public:
	enum EffectType {
		JetFlame,
		Recover,
		Explode
	};
	EffectFactory() {}
	void Init();

	ParticleEffect* getEffect(EffectType type) {
		if (type < 0 || type > m_effects.size() - 1) {
			return NULL;
		}
		return m_effects[type];
	}

private:
	vector<ParticleEffect *> m_effects;
};

class FPEffect {
public:
	FPEffect(char *path, char *fileName);
	void Draw();

private:
	Point3F m_pos;
	Point3F m_diection;
	float m_scale;

	ParticleEffect *m_effect;
};

// 3dsģ��
class Model3DS {
public:
	Model3DS(char *modelPath, char *texturePath);
	void draw();

private:
	int m_vertexNum;        // �������
	int m_faceNum;          // ������Ƭ����
	int m_uvNum;            // �����������
	unsigned int m_texture; // �������

	Point3F *m_vertex;  // ��������
	Face *m_face;       // ��Ƭ��������
	UVcoord *m_uv;      // ������������
};

class FPModel {
public:

	Point3F getDirection() { return m_direction; }
	void setDirection(double deltaTime);

	Point3F getPos() { return m_pos; }
	void setPos(double deltaTime);

	void setLastDirection(Point3F lastDir) { m_lastDirection = lastDir; }
	void setLastPos(Point3F lastPos) { m_lastPos = lastPos; }

private:
	Point3F m_pos;
	Point3F m_direction;

	Point3F m_lastPos;
	Point3F m_lastDirection;

	float m_scale;

	Model3DS *m_mesh;

	vector<FPEffect *> m_effect;
};
