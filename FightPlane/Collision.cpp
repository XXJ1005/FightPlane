#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include "media.h"
//#include "Collision.h"


#define MMax(a, b) (a > b ? a : b)
#define MMin(a, b) (a < b ? a : b)

AABB::AABB(const glm::vec3 &a) {
	max.x = min.x = a.x;
	max.y = min.y = a.y;
	max.z = min.z = a.z;
}

void AABB::operator +=(const glm::vec3 &p) {

	max.x = MMax(this->max.x, p.x);
	max.y = MMax(this->max.y, p.y);
	max.z = MMax(this->max.z, p.z);
	min.x = MMin(this->min.x, p.x);
	min.y = MMin(this->min.y, p.y);
	min.z = MMin(this->min.z, p.z);
}

void AABB::operator +=(const AABB &other) {
	max.x = MMax(this->max.x, other.max.x);
	max.y = MMax(this->max.y, other.max.y);
	max.z = MMax(this->max.z, other.max.z);
	min.x = MMin(this->min.x, other.min.x);
	min.y = MMin(this->min.y, other.min.y);
	min.z = MMin(this->min.z, other.min.z);
}

bool AABB::overlap(const AABB &other) {
	if (MMin(this->max.x, other.max.x) < MMax(this->min.x, other.min.x)) {
		return true;
	}
	if (MMin(this->max.y, other.max.y) < MMax(this->min.y, other.min.y)) {
		return true;
	}
	if (MMin(this->max.z, other.max.z) < MMax(this->min.z, other.min.z)) {
		return true;
	}
	return false;

}

static bool rayTest(const glm::vec3 face[4], glm::vec3 org, glm::vec3 dir) {
	glm::vec3 fn = glm::cross(face[1] - face[0], face[2] - face[1]);

	float t = (glm::dot(face[0], fn) - glm::dot(org, fn)) / glm::dot(dir, fn);
	

	if(t < 0 || t > 1) {
		return false;
	}

	glm::vec3 cp = org + dir * t;
	bool mark[2];
	mark[0] = false;
	mark[1] = false;
	glm::vec3 first = glm::cross(face[0] - cp, face[1] - cp);
	for (int i = 1; i < 5; i++) {
		if(glm::dot(glm::cross(face[(i - 1) % 4] - cp, face[(i) % 4] - cp), first) > 0.0f) {
			mark[0] = true;
		}else {
			mark[1] = true;
		}
	}
	if(mark[0] && mark[1]) {
		return false;
	}
	return true;

}

//使用射线和四边形进行碰撞测试的方法进行，碰撞检测。
static bool pCollide(const glm::vec3 p1[4], const glm::vec3 p2[4]) {
	for (int i = 1; i < 5; i++) {
		if(rayTest(p1, p2[(i - 1) % 4], p2[i % 4] - p2[(i - 1) % 4])) {
			return true;
		}
	}
	return false;
}
//n1,n2分别表示的是0, 1, 2那个不变，设定为0还是1。
static void GetFaceFromAABB(double mm[3][2], int n1, int n2, glm::vec3 p[4]) {
	int t1, t2;
	switch (n1) {
	case 0:
		t1 = 1;
		t2 = 2;
		break;
	case 1:
		t1 = 0;
		t2 = 2;
		break;
	case 2:
		t1 = 0;
		t2 = 1;
		break;
	}
	int tempMark[4][2] = {
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 }
	};
	for (int i = 0; i < 4; i++) {
		p[i][n1] = mm[n1][n2];
		p[i][t1] = mm[t1][tempMark[i][0]];
		p[i][t2] = mm[t2][tempMark[i][1]];
	}

}
static glm::vec3 translatePos(const glm::vec3& pos, const glm::mat4& mat) {
	glm::vec3 re;
	glm::vec4 tmp(pos[0], pos[1], pos[2], 1);
	glm::vec4 tmp2 = mat * tmp;
	re[0] = tmp2[0] / tmp2[3];
	re[1] = tmp2[1] / tmp2[3];
	re[2] = tmp2[2] / tmp2[3];
	return re;
}
bool AABB::collide(const glm::mat4& mineMat, const AABB& other, const glm::mat4& otherMat) {
	double mtmp[3][2];
	double otmp[3][2];
	for (int i = 0; i < 3; i++) {
		mtmp[i][0] = max[i];

		mtmp[i][1] = min[i];

		otmp[i][0] = other.max[i];
		otmp[i][1] = other.min[i];
	}

	glm::vec3 p1[4], p2[4];
	for (int n1 = 0; n1 < 3; n1++) {
		for (int t1 = 0; t1 < 2; t1++) {
			GetFaceFromAABB(mtmp, n1, t1, p1);
			for (int i = 0; i < 4; i++) {
				p1[i] = translatePos(p1[i], mineMat);
			}
			for (int n2 = 0; n2 < 3; n2++) {
				for (int t2 = 0; t2 < 2; t2++) {
					GetFaceFromAABB(otmp, n2, t2, p2);
					for (int i = 0; i < 4; i++) {
						p2[i] = translatePos(p2[i], otherMat);
					}
					if (pCollide(p1, p2)) {
						return true;
					}
				}
			}
		}

	}
	return false;
}
void AABB::drawBox(const glm::mat4 &mat) {
	double mtmp[3][2];
	for (int i = 0; i < 3; i++) {
		mtmp[i][0] = max[i];
		mtmp[i][1] = min[i];
	}

	glm::vec3 p1[4];
	for (int n1 = 0; n1 < 3; n1++) {
		for (int t1 = 0; t1 < 2; t1++) {
			GetFaceFromAABB(mtmp, n1, t1, p1);
			for (int i = 0; i < 4; i++) {
				p1[i] = translatePos(p1[i], mat);
			}
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 4; i++) {
				glVertex3fv(&p1[i][0]);
			}

			glEnd();

		}

	}
}
void AABB::drawBox() {
	double mtmp[3][2];
	for (int i = 0; i < 3; i++) {
		mtmp[i][0] = max[i];
		mtmp[i][1] = min[i];
	}

	glm::vec3 p[4];
	for (int n1 = 0; n1 < 3; n1++) {
		for (int t1 = 0; t1 < 2; t1++) {
			GetFaceFromAABB(mtmp, n1, t1, p);
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 4; i++) {
				glVertex3fv(&p[i][0]);
			}

			glEnd();

		}

	}
}


bool CollisionDect(CoverBox *box1, glm::mat4 &pos1, CoverBox *box2, glm::mat4 &pos2) {
	return box1->proximity_volume[0].collide(pos1, box2->proximity_volume[0], pos2);
}

void CoverBox::updateBV(Model3DS* mdl) {
	//AABB tmpBV;
	AABB tmpBV(glm::vec3(mdl->m_vertex[0].x, mdl->m_vertex[0].y, mdl->m_vertex[0].z));
	for (int i = 1; i < mdl->m_vertexNum; i++) {
		tmpBV += glm::vec3(mdl->m_vertex[i].x, mdl->m_vertex[i].y, mdl->m_vertex[i].z);
	}
	proximity_volume.clear();
	proximity_volume.push_back(tmpBV);
}