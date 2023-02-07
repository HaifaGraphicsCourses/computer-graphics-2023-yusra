#define _USE_MATH_DEFINES
#include "MeshModel.h"
#include <glm/glm.hpp>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>	
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
using namespace std;

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


	InitializeDepthColor();
}

MeshModel::~MeshModel()
{
}

glm::vec3 MeshModel::GetColor() {
	return color;
}
void MeshModel::SetColor(glm::vec3 c)
{
	color = c;
}

void MeshModel::InitializeDepthColor() 
{
	for (int i = 0; i < vertices.size(); i++)
	{
		depth.push_back(1.0f);		
	}
}
int MeshModel::GetVerticesSize()
{
	return vertices.size();
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
	Translate_obj[index][3] = t; 
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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += Rotate_obj_x[i][k] * Rotate_obj_y[k][j];
			}
			XY[i][j] = sum;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += Scale_obj[i][k] * Rotate_obj[k][j];
			}
			SR[i][j] = sum;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
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
	Translate_world[index][3] = t;
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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += Rotate_world_x[i][k] * Rotate_world_y[k][j];
			}
			XY[i][j] = sum;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += Scale_world[i][k] * Rotate_world[k][j];
			}
			SR[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += SR[i][k] * Translate_world[k][j];
			}
			worldTransform[i][j] = sum;

		}
	}

}

glm::mat4x4 matrix_mul(glm::mat4x4 m1, glm::mat4x4 m2)
{
	glm::mat4x4 ret;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
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
	float min_x = vertices[0].x, min_y = vertices[0].y, min_z = vertices[0].z;
	for (int i = 0; i < vertices.size(); i++)
	{
		// min x
		if (min_x > vertices[i].x)
			min.x = vertices[i].x;
		// min y
		if (min_y > vertices[i].y)
			min_y = vertices[i].y;
		// min z
		if (min_z > vertices[i].z)
			min_z = vertices[i].z;
	}
	min = glm::fvec3(min_x, min_y, min_z);
	//std::cout << "min: " << min.x << "  " << min.y << "  " << min.z << "\n";
	return min;
}
glm::fvec3 MeshModel::FindMax() {
	float max_x = vertices[0].x, max_y = vertices[0].y, max_z = vertices[0].z;
	for (int i = 0; i < vertices.size(); i++)
	{
		// max x
		if (max_x < vertices[i].x)
			max_x = vertices[i].x;
		// max y
		if (max_y < vertices[i].y)
			max_y = vertices[i].y;
		// max z
		if (max_z < vertices[i].z)
			max_z = vertices[i].z;
	}
	max = glm::fvec3(max_x, max_y, max_z);
	//std::cout << "max: " << max.x << "  " << max.y << "  " << max.z << "\n";
	return max;
}

glm::fvec3 MeshModel::GetMin()
{
	return min;
}
glm::fvec3 MeshModel::GetMax()
{
	return max;
}

void MeshModel::SetMin(glm::fvec3 m)
{
	min = m;
}
void MeshModel::SetMax(glm::fvec3 m)
{
	max = m;
}

std::vector<glm::fvec3> MeshModel::BoundingBox() 
{
	std::vector<glm::fvec3> bb;
	glm::fvec3 center = glm::fvec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);	
	bb.push_back(glm::fvec3(min.x, min.y, min.z));// 000  0
	bb.push_back(glm::fvec3(max.x, min.y, min.z));// 100  1
	bb.push_back(glm::fvec3(max.x, max.y, min.z));// 110  2
	bb.push_back(glm::fvec3(min.x, max.y, min.z));// 010  3
	bb.push_back(glm::fvec3(min.x, min.y, max.z));// 001  4
	bb.push_back(glm::fvec3(max.x, min.y, max.z));// 101  5
	bb.push_back(glm::fvec3(max.x, max.y, max.z));// 111  6
	bb.push_back(glm::fvec3(min.x, max.y, max.z));// 011  7



	return bb;

}
