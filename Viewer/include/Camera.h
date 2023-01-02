#pragma once
#include <glm/glm.hpp>


class Camera
{
public:
	Camera();
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetOrthographicProjectionMatrix(float b, float t, float l, float r, float Zn, float Zf);
	void SetPerspectiveProjectionMatrix(float fovy, float aspect, float Zn, float Zf);
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;
	void SetTransformation(const glm::mat4x4& transform);
	void SetProjection(const glm::mat4x4& projection);

	glm::mat4 GetCAMERATranslate();
	void SetCAMERATranslate(float t, int index);

	glm::mat4 GetCAMERARotate_X();
	void SetCAMERARotate_X(float degree);

	glm::mat4 GetCAMERARotate_Y();
	void SetCAMERARotate_Y(float degree);

	glm::mat4 GetCAMERARotate_Z();
	void SetCAMERARotate_Z(float degree);

	glm::mat4 Mul_RotateMat_CAMERA();
	glm::mat4 TransformCamera();
	// traslate and rotate the camera 
	void SetCamera_position(glm::fvec3 c_p);
	glm::fvec3 GetCamera_position();

	void Set_eye(glm::fvec3 e);
	glm::fvec3 Get_eye();
	void Set_at(glm::fvec3 a);
	glm::fvec3 Get_at();
	void Set_up(glm::fvec3 u);
	glm::fvec3 Get_up();

	glm::mat4x4 GetOrthMat();
	glm::mat4x4 GetPersMat();

private:
	glm::mat4x4 view_transformation;
	glm::mat4x4 projection_transformation;
	glm::mat4x4	orth_mat;
	glm::mat4x4 pers_mat;
	glm::mat4 Translate_c;
	glm::mat4 Rotate_c_x;
	glm::mat4 Rotate_c_y;
	glm::mat4 Rotate_c_z;
	glm::fvec3 Camera_position;
	glm::fvec3 eye;
	glm::fvec3 at;
	glm::fvec3 up;
};
