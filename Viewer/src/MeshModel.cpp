#include "MeshModel.h"

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces(faces),
	vertices(vertices),
	normals(normals)
{

}

MeshModel::~MeshModel()
{
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