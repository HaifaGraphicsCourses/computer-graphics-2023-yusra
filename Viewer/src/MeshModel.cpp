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
	Rotate_obj_x = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_obj_y = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_obj_z = { { 1.0f, 0.0f, 0.0f, 0.0f },
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
	Rotate_world_x = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_world_y = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_world_z= { { 1.0f, 0.0f, 0.0f, 0.0f },
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
	glm::fvec3 max = glm::fvec3(vertices[0].x, vertices[0].y, vertices[0].z);
	glm::fvec3 min = glm::fvec3(vertices[0].x, vertices[0].y, vertices[0].z);

}

MeshModel::~MeshModel()
{
	
}


// ** OBJECT \ LOCAL TRANSFORMATION MATRICSES ** 
glm::mat4 MeshModel::GetOBJScale()
{
	return Scale_obj;
}
void MeshModel::SetOBJScale(float s, int index)
{
	Scale_obj[index][index] = s;
}

glm::mat4 MeshModel::GetOBJTranslate()
{
	return Translate_obj;
}
void MeshModel::SetOBJTranslate(float t, int index)
{
	Translate_obj[index][2] = t; 
}

glm::mat4 MeshModel::GetOBJRotate_X()
{
	return Rotate_obj_x;
}
void MeshModel::SetOBJRotate_X(float d)
{
	float r = d * (M_PI / 180);
	Rotate_obj_x[1][1] = cos(r); Rotate_obj_x[1][2] = -1 * sin(r);
	Rotate_obj_x[2][1] = sin(r); Rotate_obj_x[2][2] = cos(r);
}

glm::mat4 MeshModel::GetOBJRotate_Y()
{
	return Rotate_obj_y;
}
void MeshModel::SetOBJRotate_Y(float d)
{
	float r = d * (M_PI / 180);
	Rotate_obj_z[0][0] = cos(r); Rotate_obj_z[0][2] = sin(r);
	Rotate_obj_z[2][0] = -1 * sin(r); Rotate_obj_z[2][2] = cos(r);
}

glm::mat4 MeshModel::GetOBJRotate_Z()
{
	return Rotate_obj_z;
}
void MeshModel::SetOBJRotate_Z(float d)
{
	float r = d * (M_PI / 180);
	Rotate_obj_z[0][0] = cos(r); Rotate_obj_z[0][1] = -1 * sin(r);
	Rotate_obj_z[1][0] = sin(r); Rotate_obj_z[1][1] = cos(r);
}

glm::mat4 MeshModel::Mul_RotateMat_OBJ()
{
	glm::mat4  XY = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } },
		XYZ = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += Rotate_obj_x[i][k] * Rotate_obj_y[k][j];
			}
			XY[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += XY[i][k] * Rotate_obj_z[k][j];
			}
			XYZ[i][j] = sum;

		}
	}
	return XYZ;

}

glm::mat4 MeshModel::GetobjectTransform()
{
	return objectTransform;
}
void MeshModel::SetobjectTransform()
{
	glm::mat4  SR = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } }, Rotate_obj = Mul_RotateMat_OBJ();

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


// ** WORLD \ LOCAL TRANSFORMATION MATRICSES ** 

glm::mat4 MeshModel::GetWORLDScale()
{
	return Scale_world;
}
void MeshModel::SetWORLDScale(float s, int index)
{
	Scale_world[index][index] = s;
}

glm::mat4 MeshModel::GetWORLDTranslate()
{
	return Translate_world;
}
void MeshModel::SetWORLDTranslate(float t,int index)
{
	Translate_world[index][2] = t;
}

glm::mat4 MeshModel::GetWORLDRotate_X()
{
	return Rotate_world_x;
}
void MeshModel::SetWORLDRotate_X(float d)
{
	float r = d * (M_PI / 180);
	Rotate_world_x[1][1] = cos(r); Rotate_world_x[1][2] = -1 * sin(r);
	Rotate_world_x[2][1] = sin(r); Rotate_world_x[2][2] = cos(r);
}

glm::mat4 MeshModel::GetWORLDRotate_Y()
{
	return Rotate_world_y;
}
void MeshModel::SetWORLDRotate_Y(float d)
{
	float r = d * (M_PI / 180);
	Rotate_world_z[0][0] = cos(r); Rotate_world_z[0][2] = sin(r);
	Rotate_world_z[2][0] = -1 * sin(r); Rotate_world_z[2][2] = cos(r);
}

glm::mat4 MeshModel::GetWORLDRotate_Z()
{
	return Rotate_world_z;
}
void MeshModel::SetWORLDRotate_Z(float d)
{
	float r = d * (M_PI / 180);
	Rotate_world_z[0][0] = cos(r); Rotate_world_z[0][1] = -1 * sin(r);
	Rotate_world_z[1][0] = sin(r); Rotate_world_z[1][1] = cos(r);
}

glm::mat4 MeshModel::Mul_RotateMat_World()
{
	glm::mat4  XY = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } },
		XYZ = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += Rotate_world_x[i][k] * Rotate_world_y[k][j];
			}
			XY[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += XY[i][k] * Rotate_world_z[k][j];
			}
			XYZ[i][j] = sum;

		}
	}
	return XYZ;
	
}	

glm::mat4x4 MeshModel::GetworldTransform()
{
	return worldTransform;
}

void MeshModel::SetworldTransform()
{
	glm::mat4  SR = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } }, Rotate_world=Mul_RotateMat_World();
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
			worldTransform[i][j] = sum;

		}
	}

}

glm::mat4x4 matrix_mul(glm::mat4x4 m1, glm::mat4x4 m2)
{
	glm::mat4x4 ret;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += m1[i][k] * m2[k][j];
			}
			ret[i][j] = sum;
		}
	}
	return ret;
}

glm::mat4x4 MeshModel::GetTransformation()
{
	SetobjectTransform();
	SetworldTransform();
	glm::mat4x4 trans;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += worldTransform[i][k] * objectTransform[k][j];
			}
			trans[i][j] = sum;
		}
	}
	return trans;

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


glm::fvec3 MeshModel::FindMin()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		// min x
		if (min.x > vertices[i].x)
			min.x = vertices[i].x;
		// min y
		if (min.y > vertices[i].y)
			min.y = vertices[i].y;
		// min z
		if (min.z > vertices[i].z)
			min.z = vertices[i].z;
	}
	return min;
}
glm::fvec3 MeshModel::FindMax() {
	for (int i = 0; i < vertices.size(); i++)
	{
		// max x
		if (max.x < vertices[i].x)
			max.x = vertices[i].x;
		// max y
		if (max.y < vertices[i].y)
			max.y = vertices[i].y;
		// max z
		if (max.z < vertices[i].z)
			max.z = vertices[i].z;
	}
	return max;
}
glm::fvec3 MeshModel::GetMaxVec()
{
	return max;
}
glm::fvec3 MeshModel::GetMinVec() {
	return min;
}