#include "Load3ds.h"

#include <windows.h>  
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <atlimage.h>
#include <conio.h>
#include <io.h>

#include "ParticleEffect.h"
#include "FightPlane.h"

extern GLuint LoadTexture(const char *fileName);

Model_3DS::Model_3DS(char *modelPath, char *texturePath) {
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file = fopen(modelPath, "rb")) == NULL) return; //Open the file

	while (ftell(l_file) < _filelength(_fileno(l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread(&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n", l_chunk_id);
		fread(&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n", l_chunk_lenght);

		switch (l_chunk_id)
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
			i = 0;
			do
			{
				fread(&l_char, 1, 1, l_file);
				model.name[i] = l_char;
				i++;
			} while (l_char != '\0' && i<20);
			break;

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
			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			model.vertices_qty = l_qty;
			printf("Number of vertices: %d\n", l_qty);
			for (i = 0; i<l_qty; i++)
			{
				fread(&model.vertex[i].x, sizeof(float), 1, l_file);
				printf("Vertices list x: %f\n", model.vertex[i].x);
				fread(&model.vertex[i].y, sizeof(float), 1, l_file);
				printf("Vertices list y: %f\n", model.vertex[i].y);
				fread(&model.vertex[i].z, sizeof(float), 1, l_file);
				printf("Vertices list z: %f\n", model.vertex[i].z);
			}
			break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons) 
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
		case 0x4120:
			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			model.polygons_qty = l_qty;
			printf("Number of polygons: %d\n", l_qty);
			for (i = 0; i<l_qty; i++)
			{
				fread(&model.polygon[i].a, sizeof(unsigned short), 1, l_file);
				printf("Polygon point a: %d\n", model.polygon[i].a);
				fread(&model.polygon[i].b, sizeof(unsigned short), 1, l_file);
				printf("Polygon point b: %d\n", model.polygon[i].b);
				fread(&model.polygon[i].c, sizeof(unsigned short), 1, l_file);
				printf("Polygon point c: %d\n", model.polygon[i].c);
				fread(&l_face_flags, sizeof(unsigned short), 1, l_file);
				printf("Face flags: %x\n", l_face_flags);
			}
			break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points) 
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
		case 0x4140:
			fread(&l_qty, sizeof(unsigned short), 1, l_file);
			for (i = 0; i<l_qty; i++)
			{
				fread(&model.mapcoord[i].u, sizeof(float), 1, l_file);
				printf("Mapping list u: %f\n", model.mapcoord[i].u);
				fread(&model.mapcoord[i].v, sizeof(float), 1, l_file);
				printf("Mapping list v: %f\n", model.mapcoord[i].v);
			}
			break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
		default:
			fseek(l_file, l_chunk_lenght - 6, SEEK_CUR);
		}
	}
	fclose(l_file); // Closes the file stream

	texture = LoadTexture(texturePath);
}

void Model_3DS::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	for (int l_index = 0; l_index< model.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(model.mapcoord[model.polygon[l_index].a].u,
			model.mapcoord[model.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(model.vertex[model.polygon[l_index].a].x,
			model.vertex[model.polygon[l_index].a].y,
			model.vertex[model.polygon[l_index].a].z); //Vertex definition

														 //----------------- SECOND VERTEX -----------------
														 // Texture coordinates of the second vertex
		glTexCoord2f(model.mapcoord[model.polygon[l_index].b].u,
			model.mapcoord[model.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(model.vertex[model.polygon[l_index].b].x,
			model.vertex[model.polygon[l_index].b].y,
			model.vertex[model.polygon[l_index].b].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(model.mapcoord[model.polygon[l_index].c].u,
			model.mapcoord[model.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(model.vertex[model.polygon[l_index].c].x,
			model.vertex[model.polygon[l_index].c].y,
			model.vertex[model.polygon[l_index].c].z);
	}
	glEnd();
}