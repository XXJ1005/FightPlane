#pragma once

#include <vector>
#include <GL/GL.h>
#include <gl/GLU.h>

class Cloud {
public:
	// 随机数生成器
	struct Rng{
		unsigned int m_z, m_w;

		Rng(unsigned int z = 362436069, unsigned int w = 521288629) : m_z(z), m_w(w) { }

		// Returns a 'canonical' float from [0,1)
		float nextFloat()
		{
			unsigned int i = nextUInt32();
			return i * 2.328306e-10f;
		}

		// Returns an int with random bits set
		unsigned int nextUInt32()
		{
			m_z = 36969 * (m_z & 65535) + (m_z >> 16);
			m_w = 18000 * (m_w & 65535) + (m_w >> 16);
			return (m_z << 16) + m_w;  /* 32-bit result */
		}
	};

	struct Rectangle {
		float bottomLeft[3];
		float topLeft[3];
		float topRight[3];
		float bottomRight[3];
	};

	Cloud(const char *imgPath, int speed);
	void update();
	void draw();

private:
	std::vector<Rectangle *> _pos;
	unsigned int _texture;
	int _speed;
	Rng _rand;
	int _current;
};

//class Missile {
//public:
//private:
//};
//
//class Fighter {
//public:
//private:
//	int _life;
//	int _attack;
//};
//
//class MyGame {
//public:
//
//private:
//	std::vector<Fighter *> _enemy;
//	Fighter *_gamer;
//	std::vector<Missile> _enemyMissile;
//	std::vector<Missile> _gamerMissile;
//};
