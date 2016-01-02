#include <windows.h>  
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <atlimage.h>

#include "ParticleEffect.h"
#include "main.h"
#include "FightPlane.h"

GLuint LoadTexture(const char *fileName) {
	BITMAP bm;
	GLuint idTexture = 0;
	CImage img;				//需要头文件atlimage.h
	HRESULT hr = img.Load(fileName);
	if (!SUCCEEDED(hr))	//文件加载失败
	{
		MessageBox(NULL, "文件加载失败", "ERROR", 0);
		return NULL;
	}
	HBITMAP hbmp = img;
	if (!GetObject(hbmp, sizeof(bm), &bm))
		return 0;

	glGenTextures(1, &idTexture);
	if (idTexture) {
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		if (bm.bmBitsPixel == 32) {
			glTexImage2D(GL_TEXTURE_2D, 0, 4, bm.bmWidth, bm.bmHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bm.bmBits);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bm.bmBits);	//这里不是GL_RGB
		}
	}
	return idTexture;
}

Cloud::Cloud(const char *imgPath, int speed = 1):_speed(speed){
	_texture = LoadTexture(imgPath);
	for (int i = -4000; i <= 0;  i++) {
		Rectangle *rect = new Rectangle();
		double x = 1000 * _rand.nextFloat() - 500;
		double y = -_rand.nextFloat() * _rand.nextFloat() * 200 - 15;
		rect->bottomLeft[0] = x - 32, rect->bottomLeft[1] = y - 32, rect->bottomLeft[2] = i;
		rect->topLeft[0] = x - 32, rect->topLeft[1] = y + 32, rect->topLeft[2] = i;
		rect->topRight[0] = x + 32, rect->topRight[1] = y + 32, rect->topRight[2] = i;
		rect->bottomRight[0] = x + 32, rect->bottomRight[1] = y - 32, rect->bottomRight[2] = i;
		_pos.push_back(rect);
	}
}

void Cloud ::draw() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _texture);
	glBegin(GL_QUADS);
		for (int i = 0; i < _pos.size(); i++) {
			glTexCoord2f(0.0, 0.0);
				glVertex3fv(_pos[i]->bottomLeft);
			glTexCoord2f(0.0, 1.0);
				glVertex3fv(_pos[i]->topLeft);
			glTexCoord2f(1.0, 1.0);
				glVertex3fv(_pos[i]->topRight);
			glTexCoord2f(1.0, 0.0);
				glVertex3fv(_pos[i]->bottomRight);
		}
	glEnd();

	glPopAttrib();

	// 更新云朵，让其向前移动
	for (int count = 0; count < _speed; count++) {
		Rectangle *buffer = _pos[_pos.size() - 1];
		for (int i = _pos.size() - 1; i > 0; i--) {
			_pos[i] = _pos[i - 1];
			_pos[i]->topLeft[2] = i - 4000;
			_pos[i]->bottomLeft[2] = i - 4000;
			_pos[i]->topRight[2] = i - 4000;
			_pos[i]->bottomRight[2] = i - 4000;
		}
		_pos[0] = buffer;
		_pos[0]->topLeft[2] = -4000;
		_pos[0]->bottomLeft[2] = -4000;
		_pos[0]->topRight[2] = -4000;
		_pos[0]->bottomRight[2] = -4000;
	}
}
