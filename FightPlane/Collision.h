#pragma once
#include "FPmath.h"
 
class Model3DS;

class AABB {
public:
	glm::vec3  max, min;
	AABB(const glm::vec3 &a);
	void operator +=(const glm::vec3 &p);


	void operator +=(const AABB &other);
	bool overlap(const AABB &other);
	bool collide(const glm::mat4 &, const AABB &, const glm::mat4&);

	void drawBox(const glm::mat4 &mat);
	void drawBox();
};

class CoverBox {
public:
	std::vector<AABB> proximity_volume;

	void updateBV(Model3DS* mdl);


	void drawBox() {
		int sz = proximity_volume.size();
		for (int i = 0; i < sz; i++) {
			proximity_volume[i].drawBox();

		}
	}
	void drawBox(glm::mat4 pose) {
		int sz = proximity_volume.size();
		for (int i = 0; i < sz; i++) {
			proximity_volume[i].drawBox(pose);

		}
	}

};
extern bool CollisionDect(CoverBox *box1, glm::mat4 &pos1, CoverBox *box2, glm::mat4 &pos2);

