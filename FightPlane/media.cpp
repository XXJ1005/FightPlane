#include <windows.h>  
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <atlimage.h>
#include <conio.h>
#include <io.h>
#include "media.h"
#include "FPGameManager.h"

GLuint LoadTexture(const char *fileName) {
	BITMAP bm;
	GLuint idTexture = 0;
	CImage img;				//��Ҫͷ�ļ�atlimage.h
	HRESULT hr = img.Load(fileName);
	if (!SUCCEEDED(hr))	//�ļ�����ʧ��
	{
		MessageBox(NULL, "�ļ�����ʧ��", "ERROR", 0);
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
			glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bm.bmBits);
		}
	}
	return idTexture;
}

// ==========Cloud
Cloud::Cloud(const char *imgPath, Color4F color, int speed) {
	m_speed = speed;
	m_texture = LoadTexture(imgPath);
	m_color = color;
	for (int i = -4000; i <= 0; i++) {
		double x = 1000 * m_rand.nextFloat() - 500;
		double y = -m_rand.nextFloat() * m_rand.nextFloat() * 200 - 15;
		glm::vec3 bottomLeft(x - 32, y - 32, i);
		glm::vec3 topLeft(x - 32, y + 32, i);
		glm::vec3 topRight(x + 32, y + 32, i);
		glm::vec3 bottomRight(x + 32, y - 32, i);
		m_rects.push_back(new Rect(bottomLeft, topLeft, topRight, bottomRight));
	}
}

void Cloud::draw() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
	for (int i = 0; i < m_rects.size(); i++) {
		glTexCoord2f(0.0, 0.0);
		glVertex3f(m_rects[i]->bottomLeft.x, m_rects[i]->bottomLeft.y, m_rects[i]->bottomLeft.z);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(m_rects[i]->topLeft.x, m_rects[i]->topLeft.y, m_rects[i]->topLeft.z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(m_rects[i]->topRight.x, m_rects[i]->topRight.y, m_rects[i]->topRight.z);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(m_rects[i]->bottomRight.x, m_rects[i]->bottomRight.y, m_rects[i]->bottomRight.z);
	}
	glEnd();

	glPopAttrib();

	update();
}

void Cloud::update() {
	// �����ƶ䣬������ǰ�ƶ�
	for (int count = 0; count < m_speed; count++) {
		Rect *buffer = m_rects[m_rects.size() - 1];
		for (int i = m_rects.size() - 1; i > 0; i--) {
			m_rects[i] = m_rects[i - 1];
			m_rects[i]->topLeft.z = i - 4000;
			m_rects[i]->bottomLeft.z = i - 4000;
			m_rects[i]->topRight.z = i - 4000;
			m_rects[i]->bottomRight.z = i - 4000;
		}
		m_rects[0] = buffer;
		m_rects[0]->topLeft.z = -4000;
		m_rects[0]->bottomLeft.z = -4000;
		m_rects[0]->topRight.z = -4000;
		m_rects[0]->bottomRight.z = -4000;
	}
}

// ==========Effect

FPEffect::FPEffect(EffectType type) {
	m_effect = FPGameManager::GetInstance()->GetEffectFactory()->getEffect(type);
	m_pos = glm::vec3(0, 0, 0);
	m_direction = glm::vec3(0, 1, 0);
	m_scale = 1;
}

void FPEffect::Draw(int accurate) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z); //ƽ��
	if (m_direction.x == 0 && m_direction.y == -1 && m_direction.z == 0) {
		glRotatef(180, 1.0, 0.0, 0.0);
	}
	else if (m_direction.x != 0 || m_direction.y != 1 || m_direction.z != 0){
		glm::vec3  rotateAxis = glm::cross(glm::vec3(0, 1, 0), m_direction);
		glRotatef(acos(m_direction.y) * 180 / PI, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	}
	glScalef(m_scale, m_scale, m_scale);

	m_effect->Frame(accurate);

	glPopMatrix();
}

// ==========Model3DS
Model3DS::Model3DS(char *modelPath, char *texturePath) {
	FILE *modelFile = fopen(modelPath, "rb");
	if (!modelFile) {
		m_faceNum = 0;
		MessageBox(NULL, "ģ�ͼ���ʧ��", "����", 0);
	}

	while (ftell(modelFile) < _filelength(_fileno(modelFile))) {
		unsigned short chunkId = 0;
		unsigned int chunkLength = 0;
		fread(&chunkId, 2, 1, modelFile);
		fread(&chunkLength, 4, 1, modelFile);

		switch (chunkId)
		{
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, models layout info 
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x3d3d:
			break;

			//--------------- EDIT_model ---------------
			// Description: model block, info for each model
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(model name) + sub chunks
			//-------------------------------------------
		case 0x4000:
		{
			int maxLoop = 20;
			char temp = 0;
			while (maxLoop--) {
				fread(&temp, 1, 1, modelFile);
				if (temp == '\0') {
					break;
				}
			}
			break;
		}

		//--------------- OBJ_TRIMESH ---------------
		// Description: Triangular mesh, contains chunks for 3d mesh info
		// Chunk ID: 4100 (hex)
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices) 
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
		case 0x4110:
		{
			fread(&m_vertexNum, sizeof(unsigned short), 1, modelFile);
			//printf("Number of vertices: %d\n", m_vertexNum);
			m_vertex = new glm::vec3[m_vertexNum];
			for (int i = 0; i < m_vertexNum; i++) {
				fread(&m_vertex[i].x, sizeof(float), 1, modelFile);
				fread(&m_vertex[i].y, sizeof(float), 1, modelFile);
				fread(&m_vertex[i].z, sizeof(float), 1, modelFile);
			}
			break;
		}

		//--------------- TRI_FACEL1 ----------------
		// Description: Polygons (faces) list
		// Chunk ID: 4120 (hex)
		// Chunk Lenght: 1 x unsigned short (number of polygons) 
		//             + 3 x unsigned short (polygon points) x (number of polygons)
		//             + sub chunks
		//-------------------------------------------
		case 0x4120:
		{
			fread(&m_faceNum, sizeof(unsigned short), 1, modelFile);
			//printf("Number of polygons: %d\n", m_faceNum);
			m_face = new Face[m_faceNum];
			unsigned short temp;
			for (int i = 0; i< m_faceNum; i++) {
				fread(&m_face[i].a, sizeof(unsigned short), 1, modelFile);
				fread(&m_face[i].b, sizeof(unsigned short), 1, modelFile);
				fread(&m_face[i].c, sizeof(unsigned short), 1, modelFile);
				fread(&temp, sizeof(unsigned short), 1, modelFile);
			}
			break;
		}

		//------------- TRI_MAPPINGCOORS ------------
		// Description: Vertices list
		// Chunk ID: 4140 (hex)
		// Chunk Lenght: 1 x unsigned short (number of mapping points) 
		//             + 2 x float (mapping coordinates) x (number of mapping points)
		//             + sub chunks
		//-------------------------------------------
		case 0x4140:
		{
			fread(&m_uvNum, sizeof(unsigned short), 1, modelFile);
			m_uv = new UVcoord[m_uvNum];
			for (int i = 0; i< m_uvNum; i++) {
				fread(&m_uv[i].u, sizeof(float), 1, modelFile);
				fread(&m_uv[i].v, sizeof(float), 1, modelFile);
			}
			break;
		}


		//----------- Skip unknow chunks ------------
		//We need to skip all the chunks that currently we don't use
		//We use the chunk lenght information to set the file pointer
		//to the same level next chunk
		//-------------------------------------------
		default:
			fseek(modelFile, chunkLength - 6, SEEK_CUR);
		}
	}
	fclose(modelFile); // Closes the file stream

					   // ��������
	m_texture = LoadTexture(texturePath);
}

void Model3DS::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_TRIANGLES);
	for (int index = 0; index < m_faceNum; index++) {
		glTexCoord2f(m_uv[m_face[index].a].u,
			m_uv[m_face[index].a].v);
		glVertex3f(m_vertex[m_face[index].a].x,
			m_vertex[m_face[index].a].y,
			m_vertex[m_face[index].a].z);

		glTexCoord2f(m_uv[m_face[index].b].u,
			m_uv[m_face[index].b].v);
		glVertex3f(m_vertex[m_face[index].b].x,
			m_vertex[m_face[index].b].y,
			m_vertex[m_face[index].b].z);

		glTexCoord2f(m_uv[m_face[index].c].u,
			m_uv[m_face[index].c].v);
		glVertex3f(m_vertex[m_face[index].c].x,
			m_vertex[m_face[index].c].y,
			m_vertex[m_face[index].c].z);
	}
	glEnd();
}

FPModel::FPModel(ModelType type) {
	m_model = FPGameManager::GetInstance()->GetModelFactory()->getModel(type);
	m_pos = glm::vec3(0, 0, 0);
	m_direction = glm::vec3(0, 1, 0);
	m_scale = 1;
}

Missile::Missile(ModelType type): FPModel(type){
	m_currentState = MissileState::Hang;

	m_jetflame = new FPEffect(EffectType::JetFlame);
	//m_explode = new  FPEffect(EffectType::Explode);

	// ���ݵ����������û���ͱ�ըЧ��λ�á����򼰴�С
	switch (type) {
		case ModelType::Missile1:
			{
				m_jetflame->setDirection(glm::vec3(0, -1, 0));
				m_jetflame->setScale(0.6);
				m_jetflame->setPos(glm::vec3(0, -12, 0));

				/*m_explode->setDirection(glm::vec3(0, 1, 0));
				m_explode->setScale(2);
				m_explode->setPos(glm::vec3(0,10,0));*/
				break;
			}
		default:
			break;
	}
	m_time = 5;
	m_attack = 10;
}

void Missile::Draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// ƽ��
	glTranslatef(m_pos.x, m_pos.y, m_pos.z); 
	// ��ת
	if (m_direction.x == 0 && m_direction.y == -1 && m_direction.z == 0) {
		glRotatef(180, 1.0, 0.0, 0.0);
	}
	else if (m_direction.x != 0 || m_direction.y != 1 || m_direction.z != 0) {
		glm::vec3  rotateAxis = glm::cross(glm::vec3(0, 1, 0), m_direction);
		glRotatef(acos(m_direction.y) * 180 / PI, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	}
	glScalef(m_scale, m_scale, m_scale);

	switch (m_currentState) {
		case MissileState::Hang:
		{
			m_model->draw();
			m_jetflame->Draw(3);
			break;
		}
		case MissileState::Ready:
		{
			break;
		}
		case MissileState::Fly:
		{
			break;
		}
		case MissileState::Explode:
		{
			break;
		}
		default: break;
	}

	glPopMatrix();
}

Fighter::Fighter(ModelType type) : FPModel(type) {
	m_currentState = FighterState::Fly;

	m_jetflame = new FPEffect(EffectType::JetFlame);
	//m_explode = new  FPEffect(EffectType::Explode);

	m_leftMissile = new Missile(ModelType::Missile1);
	m_rightMissile = new Missile(ModelType::Missile1);

	// ����ս�����������û��漰��������
	switch (type) {
		case ModelType::Plane1:
		{
			m_jetflame->setDirection(glm::vec3(0, -1, 0));
			m_jetflame->setScale(1.8);
			m_jetflame->setPos(glm::vec3(0, -38, -2));

			m_leftMissile->setDirection(glm::vec3(-0.1, 1, 0));
			m_leftMissile->setScale(1.8);
			m_leftMissile->setPos(glm::vec3(-22, -8, -9.2));

			m_rightMissile->setDirection(glm::vec3(0.1, 1, 0));
			m_rightMissile->setScale(1.8);
			m_rightMissile->setPos(glm::vec3(22, -8, -9.2));

			/*m_explode->setDirection(glm::vec3(0, 1, 0));
			m_explode->setScale(2);
			m_explode->setPos(glm::vec3(0,10,0));*/
			break;
		}
		default:
			break;
	}
	m_blood = 100;
	m_attack = 10;
}

void Fighter::Draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// ƽ��
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	// ��ת
	if (m_direction.x == 0 && m_direction.y == -1 && m_direction.z == 0) {
		glRotatef(180, 1.0, 0.0, 0.0);
	}
	else if (m_direction.x != 0 || m_direction.y != 1 || m_direction.z != 0) {
		glm::vec3  rotateAxis = glm::cross(glm::vec3(0, 1, 0), m_direction);
		glRotatef(acos(m_direction.y) * 180 / PI, rotateAxis.x, rotateAxis.y, rotateAxis.z);
	}
	glScalef(m_scale, m_scale, m_scale);

	switch (m_currentState) {
		case FighterState::Idle:
		{
			break;
		}
		case FighterState::Fly:
		{
			m_model->draw();
			m_leftMissile->Draw();
			m_rightMissile->Draw();
			m_jetflame->Draw(6);
			break;
		}
		case FighterState::Explode:
		{
			break;
		}
		default: break;
	}

	glPopMatrix();
}