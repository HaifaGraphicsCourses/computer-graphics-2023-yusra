#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	active_camera_index(0),
	active_model_index(0)
{

}

glm::vec3  Scene::GetLightPosition()
{
	return light_position;
}
void  Scene::SetLightPosition(glm::vec3 p)
{
	light_position = p;
}
glm::vec3  Scene::GetColor()
{
	return color;
}
void  Scene::SetColor(glm::vec3 c) 
{
	color = c;
}

float Scene::GetAmbient() {
	return ambient;
}
void Scene::SetAmbient(float a)
{
	ambient = a;
}
glm::vec3  Scene::GetAmbientColor()
{
	return ambient_color;
}
void  Scene::SetAmbientColor(glm::vec3 c)
{
	ambient_color = c;
}

float Scene::GetDiffuse()
{
	return diffuse;
}
void Scene::SetDiffuse(float d)
{
	diffuse = d;
}
glm::vec3  Scene::GetDiffuseColor()
{
	return diffuse_color;
}
void  Scene::SetDiffuseColor(glm::vec3 c)
{
	diffuse_color = c;
}

float Scene::GetSpecular()
{
	return specular;
}
void Scene::SetSpecular(float s)
{
	specular = s;
}
glm::vec3  Scene::GetSpecularColor()
{
	return specular_color;
}
void  Scene::SetSpecularColor(glm::vec3 c)
{
	specular_color = c;
}

glm::vec4 Scene::CalculateAmbient()
{
	// ambient light intensity * ambient color
	return glm::vec4(ambient * ambient_color, 1.0);

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& mesh_model)
{
	mesh_models.push_back(mesh_model);
}

int Scene::GetModelCount() const
{
	return mesh_models.size();
}	

MeshModel& Scene::GetModel(int index) const
{
	return *mesh_models[index];
}

MeshModel& Scene::GetActiveModel() const
{
	return *mesh_models[active_model_index];
}

void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{
	cameras.push_back(camera);
}

int Scene::GetCameraCount() const
{
	return cameras.size();
}

Camera& Scene::GetCamera(int index)
{

	return *cameras[index];
}

Camera& Scene::GetActiveCamera()
{
	return *cameras[active_camera_index];
}

void Scene::SetActiveCameraIndex(int index)
{
	active_camera_index = index;
}

int Scene::GetActiveCameraIndex() const
{
	return active_camera_index;
}

void Scene::SetActiveModelIndex(int index)
{
	active_model_index = index;
}

int Scene::GetActiveModelIndex() const
{
	return active_model_index;
}



