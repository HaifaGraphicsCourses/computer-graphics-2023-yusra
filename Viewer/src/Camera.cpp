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

Camera::Camera()
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
	orth_mat= { { 1.0f, 0.0f, 0.0f, 0.0f },
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

Camera::~Camera()
{
	
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
				sum += Rotate_c_x[i][k] * Rotate_c_y[k][j];
			}
			XY[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += XY[i][k] * Rotate_c_z[k][j];
			}
			XYZ[i][j] = sum;

		}
	}
	return XYZ;

}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation;
}

const glm::mat4x4& Camera::GetViewTransformation()
{
	// multupy position * camrea tranformation
	TransformCamera();
	glm::fvec4 p; float x, y, z, w;

	p = glm::fvec4(Camera_position.x, Camera_position.y, Camera_position.z, 1);
	x = p.x * cam_transformation[0][0] + p.y * cam_transformation[0][1] + p.z * cam_transformation[0][2] + p.w * cam_transformation[0][3];
	y = p.x * cam_transformation[1][0] + p.y * cam_transformation[1][1] + p.z * cam_transformation[1][2] + p.w * cam_transformation[1][3];
	z = p.x * cam_transformation[2][0] + p.y * cam_transformation[2][1] + p.z * cam_transformation[2][2] + p.w * cam_transformation[2][3];
	w = p.x * cam_transformation[3][0] + p.y * cam_transformation[3][1] + p.z * cam_transformation[3][2] + p.w * cam_transformation[3][3];
	Camera_position = glm::fvec3(x/w, y/w, z/w);

	view_transformation = glm::lookAt(Camera_position, at, up);
	return view_transformation;
}

void  Camera::SetCameraLookAt(const glm::fvec3& eye, const glm::fvec3& at, const glm::fvec3& up)
{
    glm::mat4x4 look_at = glm::lookAt(eye, at, up);
}

void Camera::SetOrthographicProjectionMatrix(float b, float t, float l, float r, float Zn, float Zf)
{
    
    orth_mat = glm::ortho(l, r, b, t, Zn, Zf);
   /* orth_mat[0][0] = 2 / (r - l);
    orth_mat[0][1] = 0;
    orth_mat[0][2] = 0;
    orth_mat[0][3] = 0;

    orth_mat[1][0] = 0;
    orth_mat[1][1] = 2 / (t - b);
    orth_mat[1][2] = 0;
    orth_mat[1][3] = 0;

    orth_mat[2][0] = 0;
    orth_mat[2][1] = 0;
    orth_mat[2][2] = -2 / (f - n);
    orth_mat[2][3] = 0;

    orth_mat[3][0] = -(r + l) / (r - l);
    orth_mat[3][1] = -(t + b) / (t - b);
    orth_mat[3][2] = -(f + n) / (f - n);
    orth_mat[3][3] = 1;*/
}


void Camera::SetPerspectiveProjectionMatrix(float fovy, float aspect, float Zn, float Zf)
{

	pers_mat = glm::perspective(fovy/180, aspect, Zn, Zf);
}

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
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += Rotate_c[i][k] * Translate_c[k][j];
			}
			cam_transformation[i][j] = sum;
		}
	}
}
