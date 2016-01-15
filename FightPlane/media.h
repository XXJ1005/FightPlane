#pragma once
#include <vector>
#include "FPmath.h"
#include "ParticleEffect.h"
#include "path.h"

#include "Collision.h"

// 云
class Cloud {
public:
	Cloud(const char *imgPath, Color4F color, int speed = 1);
	void Update();
	void Draw();

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
	~EffectFactory() {
		for (int i = 0; i < m_effects.size(); i++) {
			delete m_effects[i];
		}
	}

	static EffectFactory* getInstance() {
		if (m_effectFactory == NULL) {
			m_effectFactory = new EffectFactory();
		}
		return m_effectFactory;
	}
	ParticleEffect* getEffect(EffectType type) {
		switch (type) {
			case EffectType::JetFlame:
			case EffectType::Recover:
			case EffectType::Smoke:
				return m_effects[type];
			case EffectType::Explode:
				return new ParticleEffect("../media/effects/", "finalSkill");
			default:
				return NULL;
		}
	}
private:
	EffectFactory() {
		m_effects.push_back(new ParticleEffect("../media/effects/", "jetFlame"));
		m_effects.push_back(new ParticleEffect("../media/effects/", "recover"));
		m_effects.push_back(new ParticleEffect("../media/effects/", "smoke"));
	}
	static EffectFactory* m_effectFactory;
	vector<ParticleEffect *> m_effects;
};

// 加入位移旋转参数的特效
class FPEffect {
public:
	FPEffect(EffectType type);
	void Draw(int accurate = 1);

	void setPos(glm::vec3 pos) { m_pos = pos; }
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

public:
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
	M_Missile,
	M_GamerFighter,
	M_EnemyFighter,
};
class ModelFactory {
public:
	static ModelFactory* getInstance() {
		if (m_modelFactory == NULL) {
			m_modelFactory = new ModelFactory();
		}
		return m_modelFactory;
	}
	Model3DS* getModel(ModelType type) {
		if (type < 0 || type > m_models.size() - 1) {
			return NULL;
		}
		return m_models[type];
	}
private:
	ModelFactory() {
		m_models.push_back(new Model3DS("../media/missile1/model.3ds", "../media/missile1/texture.png"));
		m_models.push_back(new Model3DS("../media/plane1/model.3ds", "../media/plane1/texture.png"));
		m_models.push_back(new Model3DS("../media/plane2/model.3ds", "../media/plane2/texture.png"));
	}
	static ModelFactory* m_modelFactory;
	vector<Model3DS*> m_models;
};

class FPOBJManager;
class GameOBJ {
public:
	GameOBJ() {
		m_originPose = glm::mat4(1.0f);
		m_rotate = 0.0f;
		m_scale = 1.0f;
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
		m_damage = 0;
		m_pathPose = glm::mat4(1.0f);
		m_isIdle = true;
	}
	virtual ~GameOBJ() {}
	virtual void Draw() = 0;
	virtual void Update(FPOBJManager *objManager) = 0;
	virtual void DealCollision(int damage) = 0;
	virtual void Reset(){}

	CoverBox* getCoverBox() { return m_coverBox; }
	glm::vec3 getPos() { return m_position; }
	float getRotate() { return m_rotate; }
	int getDamage() { return m_damage; }
	bool isIdle() { return m_isIdle; }

	void setOriginPose(glm::mat4 pose) { m_originPose = pose; }
	void setRotate(float degree) { m_rotate = degree; }
	void setScale(float scale) { m_scale = scale; }
	void setDirection(glm::vec3 direction) { m_direction = glm::normalize(direction); }
	void setPosition(glm::vec3 position) { m_position = position; }
	void setIsIdle(bool state) { m_isIdle = state; }

	glm::mat4 getPose() {
		glm::mat4 modelMatrix(1.0f);
		// 平移
		modelMatrix = glm::translate(modelMatrix, m_position);
		// 旋转
		if (m_direction.x == 0 && m_direction.y == 0 && m_direction.z == 1) {
			modelMatrix = glm::rotate(modelMatrix, 180.0f, glm::vec3(0.0, 1.0, 0.0));
		}
		else if (m_direction.x != 0 || m_direction.y != 0 || m_direction.z != -1) {
			glm::vec3  rotateAxis = glm::cross(glm::vec3(0, 0, -1), m_direction);
			float degree = glm::acos(glm::dot(glm::vec3(0, 0, -1), m_direction));
			modelMatrix = glm::rotate(modelMatrix, float(degree * 180.0 / PI), rotateAxis);
		}
		modelMatrix = glm::scale(modelMatrix,glm::vec3(m_scale, m_scale, m_scale));
		modelMatrix = glm::rotate(modelMatrix, m_rotate, glm::vec3(0.0, 0.0, -1.0));

		return modelMatrix;
	}

	glm::mat4 getWorldPose() {
		return   getPose() * m_originPose * m_pathPose;
	}
	
protected:
	glm::mat4 m_originPose;// 初始姿态矩阵，一般为单位矩阵，对于挂在飞机上的导弹则需设置这个矩阵
	float m_rotate;        // 绕对象主轴旋转角度
	float m_scale;         // 缩放比例
	glm::vec3 m_direction; // 朝向
	glm::vec3 m_position;  // 位置

	int m_damage;
	bool m_isIdle;
	CoverBox *m_coverBox;
	glm::mat4 m_pathPose;
};

class Missile : public GameOBJ{
public:
	enum MissileState {
		Hang,
		Ready,
		Fly,
		Explode,
		Idle
	};
	Missile();

	void Draw();
	void Update(FPOBJManager *objManager) {}
	void DealCollision(int damage);

	void Reset() {
		m_originPose = glm::mat4(1.0f);
		m_rotate = 0.0f;
		m_scale = 1.0f;
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
		m_pathPose = glm::mat4(1.0f);
		m_path->reset();
		m_time = 400;
		m_currentState = MissileState::Idle;
		m_isIdle = true;
	}

	void setMissileState(MissileState state) { m_currentState = state; }
	MissileState getMissileState() { return m_currentState; }

	Point3F getDirection() { return m_direction; }
	void setDirection(double deltaTime);

	Point3F getPos() { return m_pos; }
	void setPos(double deltaTime);

	void setLastDirection(Point3F lastDir) { m_lastDirection = lastDir; }
	void setLastPos(Point3F lastPos) { m_lastPos = lastPos; }

private:
	Path *m_path;
	float m_time;
	MissileState m_currentState;

	FPEffect *m_jetflame;
	FPEffect *m_explode;
	Model3DS *m_model;
};

class GamerFighter: public GameOBJ {
public:
	GamerFighter();
	void Draw();
	void Update(FPOBJManager *objManager);
	void DealCollision(int damage);

	int getBlood() { return m_blood; }
private:
	Model3DS *m_model;
	FPEffect *m_jetflame;
	//FPEffect *m_smoking;
	//FPEffect *m_explode;
	//FPEffect *m_recover;
	Missile *m_leftMissile, *m_rightMissile;

	int m_blood;
	int m_time;
};

class EnemyFighter :public GameOBJ {
public:
	EnemyFighter();
	void Draw();
	void Update(FPOBJManager *objManager);
	void DealCollision(int damage);
	void Reset() {
		m_originPose = glm::mat4(1.0f);
		m_rotate = 0.0f;
		m_scale = 1.0f;
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
		m_blood = 100;
		m_pathPose = glm::mat4(1.0f);
		m_path->reset();
		m_isIdle = true;
		m_time = 0;
	}

private:
	Model3DS *m_model;
	FPEffect *m_jetflame;
	//FPEffect *m_smoking;
	//FPEffect *m_explode;
	Missile *m_leftMissile, *m_rightMissile;

	int m_blood;
	int m_time;
	Path *m_path;
};
