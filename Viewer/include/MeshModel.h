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
	void SetOBJScale(float s);

	glm::mat4 GetOBJTranslate();
	void SetOBJTranslate(float t);

	glm::mat4 GetOBJRotate();
	void SetOBJRotate(float degree);

	glm::mat4 GetWORLDScale();
	void SetWORLDScale(float s);

	glm::mat4 GetWORLDTranslate();
	void SetWORLDTranslate(float t);

	glm::mat4 GetWORLDRotate();
	void SetWORLDRotate(float degree);


private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string model_name;
	glm::mat4 objectTransform;
	glm::mat4 Scale_obj;
	glm::mat4 Translate_obj;
	glm::mat4 Rotate_obj;
	glm::mat4 Scale_world;
	glm::mat4 Translate_world;
	glm::mat4 Rotate_world;
	glm::mat4 worldTransform;
};
