#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	void Renderer::Scale(MeshModel& Mesh, glm::fvec3 scale_vec);
	void Renderer::Translate(MeshModel& Mesh, glm::fvec3 translate_vec);
	void Renderer::Rotate(MeshModel& Mesh, float degree);
	void Renderer::DrawTriangle(MeshModel& Mesh);
	void Renderer::FixPoints(MeshModel& Mesh);

	

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
