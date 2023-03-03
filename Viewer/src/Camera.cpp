#define _USE_MATH_DEFINES
#include "Camera.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>	

using namespace std;


Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, const float aspectRatio) :
	
	zoom(1.0f),
	fovy(glm::pi<float>() / 4.0f),
	height(5),
	zNear(0.1f),
	zFar(200.0f),
	aspectRatio(aspectRatio),
	pers(true), orth(false),
	view_transformation(1),
	eye(eye),
	at(at),
	up(up)
{
	//setupMatrix();
	UpdateProjectionMatrix();
	view_transformation = glm::lookAt(eye, at, up);
}

Camera::Camera()
{
	//setupMatrix();
}

Camera::~Camera()
{
	
}
void Camera::setupMatrix()
{
	Translate_c = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_c_x = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_c_y = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	Rotate_c_z = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	Camera_position = glm::fvec3(1.0f, 1.0f, 1.0f);
	eye = glm::fvec3(1.0f, 1.0f, 1.0f);
	at = glm::fvec3(0.0f, 1.0f, 0.0f);
	up = glm::fvec3(0.0f, 1.0f, 0.0f);

	pers_mat = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
	orth_mat = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	projection_transformation = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	cam_transformation = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	view_transformation = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };
}

void Camera::SetOrthographicProjection(float height, float aspectRatio, float zNear, float zFar)
{
	orth = true; pers = false;
	float width = aspectRatio * height;
	projection_transformation = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar);
}

void Camera::SetPerspectiveProjection(float fovy, float aspectRatio, float zNear, float zFar)
{
	pers = true; orth = false;
	projection_transformation = glm::perspective(fovy, aspectRatio, zNear, zFar);
}

void Camera::UpdateProjectionMatrix()
{
	if (pers)
	{
		SetPerspectiveProjection(fovy, aspectRatio, zNear, zFar);
	}
	else
	{
		SetOrthographicProjection(height, aspectRatio, zNear, zFar);
	}
}



void Camera::Set_at(glm::fvec3 a)
{
	at = a;
}
glm::fvec3 Camera::Get_at()
{
	return at;
}
void Camera::Set_up(glm::fvec3 u)
{
	up = u;
}
glm::fvec3 Camera::Get_up() {
	return up;
}

void Camera::SetCamera_position(glm::fvec3 c_p)
{
	Camera_position = c_p;
}
glm::fvec3 Camera::GetCamera_position()
{
	return Camera_position;
}

glm::mat4 Camera::GetCAMERATranslate()
{
	return Translate_c;
}
void Camera::SetCAMERATranslate(float t, int index)
{
	Translate_c[index][2] = t;
}

glm::mat4 Camera::GetCAMERARotate_X()
{
	return Rotate_c_x;
}
void Camera::SetCAMERARotate_X(float d)
{
	float r = d * (M_PI / 180);
	Rotate_c_x[1][1] = cos(r); Rotate_c_x[1][2] = -1 * sin(r);
	Rotate_c_x[2][1] = sin(r); Rotate_c_x[2][2] = cos(r);
}

glm::mat4 Camera::GetCAMERARotate_Y()
{
	return Rotate_c_y;
}
void Camera::SetCAMERARotate_Y(float d)
{
	float r = d * (M_PI / 180);
	Rotate_c_z[0][0] = cos(r); Rotate_c_z[0][2] = sin(r);
	Rotate_c_z[2][0] = -1 * sin(r); Rotate_c_z[2][2] = cos(r);
}

glm::mat4 Camera::GetCAMERARotate_Z()
{
	return Rotate_c_z;
}
void Camera::SetCAMERARotate_Z(float d)
{
	float r = d * (M_PI / 180);
	Rotate_c_z[0][0] = cos(r); Rotate_c_z[0][1] = -1 * sin(r);
	Rotate_c_z[1][0] = sin(r); Rotate_c_z[1][1] = cos(r);
}

glm::mat4 Camera::Mul_RotateMat_CAMERA()
{
	return Rotate_c_x * Rotate_c_y * Rotate_c_z;
}

 glm::mat4x4& Camera::GetProjectionTransformation() 
{
	// projection_transformation= { { 1.0f, 0.0f, 0.0f, 0.0f },
	//{ 0.0f, 1.0f, 0.0f, 0.0f },
	//{ 0.0f, 0.0f, 1.0f, 0.0f },
	//{ 0.0f, 0.0f, 0.0f, 1.0f } };
	//if (orth)
	//{
	//	projection_transformation = orth_mat;
	//}
	//else if (pers) {
	//	projection_transformation = pers_mat;
	//}
	return projection_transformation;
}

const glm::mat4x4& Camera::GetViewTransformation()
{
	// multupy position * camrea tranformation
	//TransformCamera();
	//glm::fvec4 p,r; float x, y, z, w;

	//p = glm::fvec4(Camera_position.x, Camera_position.y, Camera_position.z, 1);
	//r = p * cam_transformation;
	//Camera_position = glm::fvec3(r.x / r.w, r.y / r.w, r.z / r.w);
	//view_transformation = glm::lookAt(Camera_position, at, up);
	return view_transformation;
}

void  Camera::SetCameraLookAt(const glm::fvec3& eye, const glm::fvec3& at, const glm::fvec3& up)
{
    glm::mat4x4 look_at = glm::lookAt(eye, at, up);
}

// need to chek if it takes the right parameters . . .
//void Camera::SetOrthographicProjectionMatrix(float b, float t, float l, float r, float Zn, float Zf)
//{
//	pers = false; orth = true;
//    orth_mat = glm::ortho(l, r, b, t, Zn, Zf);
//}

//void Camera::SetPerspectiveProjectionMatrix(float fovy, float aspect, float Zn, float Zf)
//{
//	pers = true; orth = false;
//	pers_mat = glm::perspective(fovy/180, aspect, Zn, Zf);
//}

glm::mat4x4 Camera::GetOrthMat()
{
	return orth_mat;
}

glm::mat4x4 Camera::GetPersMat()
{
	return pers_mat;
}
glm::mat4x4 Camera::GetCamTransformation()
{
	return cam_transformation;
}
void Camera::TransformCamera()
{
	glm::mat4x4 Rotate_c = Mul_RotateMat_CAMERA();
	cam_transformation= Rotate_c * Translate_c;
}

void Camera::Zoom(float factor)
{
	fovy = fovy * factor;
	if (fovy > glm::pi<float>())
	{
		fovy = glm::pi<float>();
	}

	UpdateProjectionMatrix();
}