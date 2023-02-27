#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <memory>
#include "Texture2D.h"
#include "ShaderProgram.h"

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	Renderer();
	~Renderer();
	void Render(const std::shared_ptr<Scene>& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;	
	int GetViewportHeight() const;
	
	void LoadShaders();
	void LoadTextures();
	
	

	void DrawTriangle(MeshModel& Mesh, vector<vector<float>>& z_depth);
	void FixPoints(MeshModel& Mesh);
	void Transformation(MeshModel& Mesh);
	void Orth(MeshModel& Mesh, Camera& Cam);
	void Perspective(MeshModel& Mesh, Camera& Cam);
	void CameraTransformarion(MeshModel& Mesh, Camera& Cam);
	void DrawAxesModel(MeshModel& Mesh, Camera& Cam);
	void DrawAxesWorld(MeshModel& Mesh, Camera& Cam);
	void DrawFaceNormals(MeshModel& Mesh);
	void DrawVertexNormals(MeshModel& Mesh);
	void DrawBoundingBoxModel(MeshModel& Mesh, Camera& Cam);
	void DrawBoundingBoxWorld(MeshModel& Mesh, Camera& Cam);
	glm::fvec3 LocalTransform_point(glm::fvec3 a, MeshModel& Mesh, Camera& Cam);
	glm::fvec3 WolrdTransform_point(glm::fvec3 a, MeshModel& Mesh, Camera& Cam);
	void Depth(MeshModel& Mesh);
	void Z_Buffer(MeshModel& Mesh);
	vector<vector<float>> GetBuffer(int h, int w);
	void ProjectionTransformation(MeshModel& Mesh, Camera& Cam);
	glm::fvec2 max_min_z(MeshModel& Mesh);
	glm::fvec2 max_min_z_avg(MeshModel& Mesh);

	void Ambient(MeshModel& Mesh, glm::vec3 ambient);
	void Diffuse(glm::vec3 light_pos, glm::vec3 ambient, glm::vec3 diffuce_color, MeshModel& Mesh);
	void Specular(float Fa, vector<vector<float>>z_depth, glm::fvec2 z_max_min, glm::fvec2 z_max_min_avg, glm::vec3 light_pos, glm::vec3 ambient,glm::vec3 diffuce_color, float Ks, float power, glm::vec3 specular_color, MeshModel& Mesh, glm::vec3 viewPos);
	void Reflect(glm::vec3 light_pos, float specular, float power, glm::vec3 specular_color, MeshModel& Mesh, glm::vec3 viewPos);


private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);

	void CreateBuffers(int w, int h);
	void CreateOpenglBuffer();
	void InitOpenglRendering();
	

	float* color_buffer;
	int viewport_width;
	int viewport_height;
	GLuint gl_screen_tex;
	GLuint gl_screen_vtc;

	ShaderProgram lightShader;
	ShaderProgram colorShader;
	Texture2D texture1;
};
