#pragma once
#include <vector>
#include "FPmath.h"
#include "ParticleEffect.h"

// 云
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

// raw特效工厂
enum EffectType {
	JetFlame,
	Recover,
	Smoke,
	Explode
};
class EffectFactory {
public:
	EffectFactory() {}
	~EffectFactory() {
		for (int i = 0; i < m_effects.size(); i++) {
			delete m_effects[i];
		}
	}
	void Init() {
		m_effects.push_back(new ParticleEffect("../media/effects/", "jetFlame"));
		m_effects.push_back(new ParticleEffect("../media/effects/", "recover"));
		m_effects.push_back(new ParticleEffect("../media/effects/", "smoke"));
	}
	ParticleEffect* getEffect(EffectType type) {
		switch (type) {
			case EffectType::JetFlame:
			case EffectType::Recover:
			case EffectType::Smoke:
				return m_effects[type];
			case EffectType::Explode:
				return new ParticleEffect("../media/effects/", "smoke");
			default:
				return NULL;
		}
	}
private:
	vector<ParticleEffect *> m_effects;
};

// 加入位移旋转参数的特效
class FPEffect {
public:
	FPEffect(EffectType type);
	void Draw(int accurate = 1);

	void setPos(glm::vec3 pos) { 
		m_pos = pos; }
	void setDirection(glm::vec3 dir) { m_direction = glm::normalize(dir); }
	void setScale(float scale) { m_scale = scale; }
private:
	glm::vec3 m_pos;
	glm::vec3 m_direction;
	float m_scale;
	ParticleEffect *m_effect;
};

// 3ds模型
class Model3DS {
public:
	Model3DS(char *modelPath, char *texturePath);
	void draw();

private:
	int m_vertexNum;        // 顶点个数
	int m_faceNum;          // 三角面片个数
	int m_uvNum;            // 纹理坐标个数
	unsigned int m_texture; // 纹理对象

	glm::vec3 *m_vertex;  // 顶点数组
	Face *m_face;       // 面片索引数组
	UVcoord *m_uv;      // 纹理坐标索引
};

// raw模型工厂
enum ModelType {
	Missile1,
	Plane1
};
class ModelFactory {
public:
	ModelFactory() {}
	void Init() {
		m_models.push_back(new Model3DS("../media/missile1/model.3ds", "../media/missile1/texture.png"));
		m_models.push_back(new Model3DS("../media/plane1/model.3ds", "../media/plane1/texture.png"));
	}
	Model3DS* getModel(ModelType type) {
		if (type < 0 || type > m_models.size() - 1) {
			return NULL;
		}
		return m_models[type];
	}
private:
	vector<Model3DS*> m_models;
};

// 加入位移旋转参数的模型
class FPModel {
public:
	FPModel(ModelType type);
	virtual ~FPModel() {}
	virtual void Draw() = 0;

	void setPos(glm::vec3 pos) { m_pos = pos; }
	void setDirection(glm::vec3 dir) { m_direction = glm::normalize(dir); }
	void setScale(float scale) { m_scale = scale; }

protected:
	glm::vec3 m_pos;
	glm::vec3 m_direction;
	float m_scale;

	Model3DS *m_model;
};

// 导弹
class Missile : public FPModel {
public:
	enum MissileState{
		Hang,
		Ready,
		Fly,
		Explode,
		Idle
	};
	Missile(ModelType type);

	void Draw();

private:

	double m_time;
	int m_attack;
	MissileState m_currentState;
	FPEffect *m_jetflame;
	FPEffect *m_explode;
};

// 战斗机
class Fighter : public FPModel {
public:
	enum FighterState {
		Idle,
		Fly,
		Explode
	};
	Fighter(ModelType type);

	void Draw();
private:
	int m_blood;
	int m_attack;
	FighterState m_currentState;

	FPEffect *m_jetflame;
	FPEffect *m_smoking;
	FPEffect *m_explode;

	Missile *m_leftMissile, *m_rightMissile;
};
