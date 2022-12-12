#define _USE_MATH_DEFINES
#include "MeshModel.h"
#include <glm/glm.hpp>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>	

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces(faces),
	vertices(vertices),
	normals(normals)
{
	Scale_obj = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Translate_obj = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_obj = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Scale_world = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Translate_world = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_world = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	objectTransform = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	worldTransform = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

}

MeshModel::~MeshModel()
{
	
}



glm::mat4 MeshModel::GetOBJScale()
{
	return Scale_obj;
}
void MeshModel::SetOBJScale(float s)
{
	Scale_obj[0][0] = s; Scale_obj[1][1] = s; Scale_obj[2][2] = 1; Scale_obj[3][3] = 1;
}

glm::mat4 MeshModel::GetOBJTranslate()
{
	return Translate_obj;
}
void MeshModel::SetOBJTranslate(float t)
{
	Translate_obj[0][3] = t; Translate_obj[1][3] = t; Translate_obj[2][2] = 1; Translate_obj[3][3] = 1;
}

glm::mat4 MeshModel::GetOBJRotate()
{
	return Rotate_obj;
}
void MeshModel::SetOBJRotate(float d)
{
	float r = d * (M_PI / 180);
	Rotate_obj[0][0] = cos(r); Rotate_obj[0][1] = -1 * sin(r);
	Rotate_obj[1][0] = sin(r); Rotate_obj[1][1] = cos(r);
	Rotate_obj[2][2] = 1; Rotate_obj[3][3] = 1;
}

glm::mat4 MeshModel::GetWORLDScale()
{
	return Scale_world;
}
void MeshModel::SetWORLDScale(float s)
{
	Scale_world[0][0] = s; Scale_world[1][1] = s; Scale_world[2][2] = 1; Scale_world[3][3] = 1;
}

glm::mat4 MeshModel::GetWORLDTranslate()
{
	return Translate_world;
}

void MeshModel::SetWORLDTranslate(float t)
{
	Translate_world[0][3] = t; Translate_world[1][3] = t; Translate_world[2][2] = 1; Translate_world[3][3] = 1;
}

glm::mat4 MeshModel::GetWORLDRotate()
{
	return Rotate_world;
}

void MeshModel::SetWORLDRotate(float d)
{
	float r = d * (M_PI / 180);
	Rotate_world[0][0] = cos(r); Rotate_world[0][1] = -1 * sin(r);
	Rotate_world[1][0] = sin(r); Rotate_world[1][1] = cos(r);
	Rotate_world[2][2] = 1; Rotate_world[3][3] = 1;
}


glm::mat4 MeshModel::GetobjectTransform()
{
	return objectTransform;
}

void MeshModel::SetobjectTransform()
{
	glm::mat4  SR= { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += Scale_obj[i][k] * Rotate_obj[k][j];
			}
			SR[i][j] = sum;
		}
	}
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += SR[i][k] * Translate_obj[k][j];
			}
			objectTransform[i][j] = sum;
			
		}
	}

}

glm::mat4x4 MeshModel::GetworldTransform()
{
	return worldTransform;
}
void MeshModel::SetworldTransform()
{
	SetobjectTransform();

	glm::mat4  SR = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } }, M;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += Scale_world[i][k] * Rotate_world[k][j];
			}
			SR[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += SR[i][k] * Translate_world[k][j];
			}
			M[i][j] = sum;

		}
	}

	//worldTransform * objectTransform
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += M[i][k] * objectTransform[k][j];
			}
			worldTransform[i][j] = sum;

		}
	}
}

glm::mat4x4 MeshModel::GetTransformation()
{
	return worldTransform*objectTransform;

}

const Face& MeshModel::GetFace(int index) const
{
	return faces[index];
}

int MeshModel::GetFacesCount() const
{
	return faces.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name;
}


glm::fvec3 MeshModel::GetVertices(int index)
{
	return vertices[index];
}

void MeshModel::SetVertices(glm::fvec3 vec , int index)
{
	vertices[index]= vec;
}

int MeshModel::RetVerticesSize()
{
	return vertices.size();
}
