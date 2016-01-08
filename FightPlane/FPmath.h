#pragma once

// 纹理坐标
struct UVcoord {
	float u, v;
};

// 颜色
struct Color4F {
	Color4F(float r = 0, float g = 0, float b = 0, float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	float r, g, b, a;
};

// 空间三维点
struct Point3F {
	Point3F(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float x, y, z;
};

// 三角面片，a,b,c代表顶点索引
struct Face {
	unsigned short a, b, c;
};

// 矩形
struct Rect {
	Rect(Point3F &bottomLeft, Point3F &topLeft, Point3F &topRight, Point3F &bottomRight) {
		this->bottomLeft = bottomLeft;
		this->topLeft = topLeft;
		this->topRight = topRight;
		this->bottomRight = bottomRight;
	}
	Point3F bottomLeft, topLeft, topRight, bottomRight;
};

// 随机数生成器
struct Rng {
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