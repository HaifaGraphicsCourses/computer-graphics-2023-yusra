#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render( Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	void Scale(MeshModel& Mesh, glm::fvec3 scale_vec);
	void Translate(MeshModel& Mesh, glm::fvec3 translate_vec);
	void Rotate(MeshModel& Mesh, float degree);
	void DrawTriangle(MeshModel& Mesh);
	void FixPoints(MeshModel& Mesh);
	void Transformation(MeshModel& Mesh);
	void DrawBoundingBox(MeshModel& Mesh);
	void Orth(MeshModel& Mesh, Camera& Cam);
	void Perspective(MeshModel& Mesh, Camera& Cam);
	void View(MeshModel& Mesh, Camera& Cam);
	void DrawAxes(MeshModel& Mesh);
	void DrawFaceNormals(MeshModel& Mesh);
	void DrawVertexNormals(MeshModel& Mesh);
	glm::fvec3 Transform_point(glm::fvec3 a, MeshModel& Mesh);
	//void udateModelTranform(glm::mat4x4 Transform, MeshModel& Mesh);

	

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
};
