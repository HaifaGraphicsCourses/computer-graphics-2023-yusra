#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

class MeshModel
{
public:
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	glm::fvec3 MeshModel::GetVertices(int index);
	void MeshModel::SetVertices(glm::fvec3 vec, int index);
	int MeshModel::RetVerticesSize();
	glm::mat4x4 GetTransformation();

	glm::mat4 GetobjectTransform();
	void SetobjectTransform();

	glm::mat4 GetworldTransform();
	void SetworldTransform();

	glm::mat4 GetOBJScale();
	void SetOBJScale(float s, int index);

	glm::mat4 GetOBJTranslate();
	void SetOBJTranslate(float t, int index);

	glm::mat4 GetOBJRotate_X();
	void SetOBJRotate_X(float degree);

	glm::mat4 GetOBJRotate_Y();
	void SetOBJRotate_Y(float degree);

	glm::mat4 GetOBJRotate_Z();
	void SetOBJRotate_Z(float degree);

	glm::mat4 GetWORLDScale();
	void SetWORLDScale(float s, int index);

	glm::mat4 GetWORLDTranslate();
	void SetWORLDTranslate(float t,int index);

	glm::mat4 GetWORLDRotate_X();
	void SetWORLDRotate_X(float degree);

	glm::mat4 GetWORLDRotate_Y();
	void SetWORLDRotate_Y(float degree);

	glm::mat4 GetWORLDRotate_Z();
	void SetWORLDRotate_Z(float degree);

	glm::mat4 Mul_RotateMat_World();
	glm::mat4 Mul_RotateMat_OBJ();

	glm::fvec3 FindMax();
	glm::fvec3 FindMin();
	
	glm::fvec3 GetMax();
	glm::fvec3 GetMin();
	void SetMax(glm::fvec3 m);
	void SetMin(glm::fvec3 m);

	std::vector<glm::fvec3> BoundingBox();



private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string model_name;

	glm::mat4 objectTransform;
	glm::mat4 Scale_obj;
	glm::mat4 Translate_obj;
	glm::mat4 Rotate_obj_x;
	glm::mat4 Rotate_obj_y;
	glm::mat4 Rotate_obj_z;

	glm::mat4 worldTransform;
	glm::mat4 Scale_world;
	glm::mat4 Translate_world;
	glm::mat4 Rotate_world_x;
	glm::mat4 Rotate_world_y;
	glm::mat4 Rotate_world_z;

	glm::fvec3 max;
	glm::fvec3 min;
};
