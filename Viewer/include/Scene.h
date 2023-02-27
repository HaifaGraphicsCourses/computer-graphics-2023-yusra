#pragma once

#include <vector>
#include <memory>

#include "Camera.h"
#include "MeshModel.h"


using namespace std;

class Scene {
public:
	Scene();

	void AddModel(const shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	MeshModel& GetModel(int index) const;
	MeshModel& GetActiveModel() const;
	
	void AddCamera(const Camera& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index);
	Camera& GetActiveCamera();

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;

	glm::vec3 GetLightPosition();
	void SetLightPosition(glm::vec3 p);
	glm::vec3 GetColor();
	void SetColor(glm::vec3 c);

	void SetAmbient(float a);
	float GetAmbient();
	glm::vec3 GetAmbientColor();
	void SetAmbientColor(glm::vec3 c);

	void SetDiffuse(float d);
	float GetDiffuse();
	glm::vec3 GetDiffuseColor();
	void SetDiffuseColor(glm::vec3 c);

	float GetSpecular();
	void SetSpecular(float s);
	glm::vec3 GetSpecularColor();
	void SetSpecularColor(glm::vec3 c);
	void SetPower(float p);
	float GetPower();
	
	glm::vec3 CalculateAmbient();
	glm::vec4 CalculateDiffuse();
	glm::vec4 CalculateSpecular();


	
private:
	vector<shared_ptr<MeshModel>> mesh_models;
	std::vector<Camera> cameras;
	int active_camera_index;
	int active_model_index;
	glm::vec3 light_position;
	glm::vec3 color;
	float ambient;
	glm::vec3 ambient_color;
	float diffuse;
	glm::vec3 diffuse_color;
	float specular;
	glm::vec3 specular_color;
	float power;

};