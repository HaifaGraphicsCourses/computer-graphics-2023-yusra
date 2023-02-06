#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>	
#include "Renderer.h"
#include "InitShader.h"
#include "Utils.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
using namespace std;
using namespace std;
#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))

Renderer::Renderer(int viewport_width, int viewport_height) :
	viewport_width(viewport_width),
	viewport_height(viewport_height)
{
	InitOpenglRendering();
	CreateBuffers(viewport_width, viewport_height);
}

Renderer::~Renderer()
{
	delete[] color_buffer;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width) return;
	if (j < 0) return; if (j >= viewport_height) return;
	
	color_buffer[INDEX(viewport_width, i, j, 0)] = color.x;
	color_buffer[INDEX(viewport_width, i, j, 1)] = color.y;
	color_buffer[INDEX(viewport_width, i, j, 2)] = color.z;
}

extern int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0;
void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	double x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = x1 - x0, dy = y1 - y0, D = 2 * dy - dx, x = x0, y = y0, yi = 1, xi = 1, m;
	if (dx == 0) m = 200; // so we wont have something undefined
	else { m = dy / dx; }; // calcutaleing the Incline
	//if (m < 1 && m > -1) // the cases is -1 < Incline < 1
	//{
	//	//plotLineLow
	//	if (dy < 0) {
	//		yi = -1;
	//		dy = -dy;
	//	}
	//	D = (2 * dy) - dx;
	//	y = y0;
	//	for (int x = x0; x <= x1; x++)
	//	{
	//		PutPixel(x, y, color);
	//		if (D > 0)
	//		{
	//			y = y + yi;
	//			D = D + (2 * (dy - dx));
	//		}
	//		else
	//			D = D + 2 * dy;
	//	}
	//	// plotLineHigh
	//	if (dx < 0)
	//	{
	//		xi = -1;
	//		dx = -dx;
	//	}
	//	D = (2 * dx) - dy;
	//	x = x0;
	//	for (int y = y0; y <= y1; y++)
	//	{
	//		PutPixel(x, y, color);
	//		if (D > 0)
	//		{
	//			x = x + xi;
	//			D = D + (2 * (dx - dy));
	//		}
	//		else
	//			D = D + 2 * dx;
	//	}
	//	if (dy > 0)
	//	{

	//		if (x0 > x1) //plotLineLow(x1, y1, x0, y0)
	//		{
	//			dx = x0 - x1;
	//			dy = y0 - y1;
	//			yi = 1;
	//			if (dy < 0) {
	//				yi = -1;
	//				dy = -dy;
	//			}
	//			D = (2 * dy) - dx;
	//			y = y1;
	//			cnt3++;
	//			for (int x = x1; x <= x0; x++)
	//			{
	//				PutPixel(x, y, color);
	//				if (D > 0)
	//				{
	//					y = y + yi;
	//					D = D + (2 * (dy - dx));
	//				}
	//				else
	//					D = D + 2 * dy;
	//			}
	//		}
	//		else // plotLineLow(x0, y0, x1, y1)
	//		{
	//			dx = x1 - x0;
	//			dy = y1 - y0;
	//			yi = 1;
	//			if (dy < 0) {
	//				yi = -1;
	//				dy = -dy;
	//			}
	//			D = (2 * dy) - dx;
	//			y = y0;
	//			for (int x = x0; x <= x1; x++)
	//			{
	//				PutPixel(x, y, color);
	//				if (D > 0)
	//				{
	//					y = y + yi;
	//					D = D + (2 * (dy - dx));
	//				}
	//				else
	//					D = D + 2 * dy;
	//			}
	//		}
	//	}
	//}
	//else 
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1) //plotLineLow(x1, y1, x0, y0)
		{
			dx = x0 - x1;
			dy = y0 - y1;
			yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			D = (2 * dy) - dx;
			y = y1;
			cnt3++;
			for (int x = x1; x <= x0; x++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					y = y + yi;
					D = D + (2 * (dy - dx));
				}
				else
					D = D + 2 * dy;
			}
		}
		else // plotLineLow(x0, y0, x1, y1)
		{
			dx = x1 - x0;
			dy = y1 - y0;
			yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			D = (2 * dy) - dx;
			y = y0;
			for (int x = x0; x <= x1; x++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					y = y + yi;
					D = D + (2 * (dy - dx));
				}
				else
					D = D + 2 * dy;
			}
		}
	}
	else {
		if (y0 > y1) // plotLineHigh(x1, y1, x0, y0)
		{
			dx = x0 - x1;
			dy = y0 - y1;
			xi = 1;
			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			D = (2 * dx) - dy;
			x = x1;
			for (int y = y1; y <= y0; y++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					x = x + xi;
					D = D + (2 * (dx - dy));
				}
				else
					D = D + 2 * dx;
			}
		}
		else // plotLineHigh(x0, y0, x1, y1)
		{
			dx = x1 - x0;
			dy = y1 - y0;
			xi = 1;
			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			D = (2 * dx) - dy;
			x = x0;
			for (int y = y0; y <= y1; y++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					x = x + xi;
					D = D + (2 * (dx - dy));
				}
				else
					D = D + 2 * dx;
			}
		}
	}


	// algorethem from the enternet with some changes
	/*double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	int dx = x2 - x1,
		dy = y2 - y1,
		p = 2 * dy - dx,
		x = x1,
		y = y1;
	while (x <= x2)
	{
		if (p >= 0)
		{
			PutPixel(x, y, color);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			PutPixel(x, y, color);
			p = p + 2 * dy;
		}
		x = x + 1;
	}*/
	
	// algorethem from the slides
	/*double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	int x = x1, y = y1, e = -1 * (x2 - x1), dx = x2 - x1,dy = y2 - y1;
	while (x <= x2)
	{
		e = 2 * dy * x + 2 * dx * y - 1;
		if (e > 0)
		{
			y = y + 1; e = e - 2 * dx;
		}
		PutPixel(x, y, color);
		x = x + 1; e = e + 2 * dy;
	}*/

}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenglBuffer(); //Do not remove this line.
	color_buffer = new float[3 * w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::CreateOpenglBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width, viewport_height, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width, viewport_height);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width, viewport_height, GL_RGB, GL_FLOAT, color_buffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width; i++)
	{
		for (int j = 0; j < viewport_height; j++)
		{
			PutPixel(i, j, color);
		}
	}
}

void Renderer::Render( Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width / 2;
	int half_height = viewport_height / 2;	
	
	// HW2
	//auto Cam = scene.GetCamera(1);
	for (int i = 0; i < scene.GetModelCount(); i++)
	{
		

		auto Mesh = scene.GetModel(i);
		auto Cam = scene.GetActiveCamera();
	/*	DrawBoundingBoxModel(Mesh, Cam);
		DrawBoundingBoxWorld(Mesh, Cam);
		DrawAxesModel(Mesh, Cam);
		DrawAxesWorld(Mesh, Cam);*/
		vector<vector<float>>z_depth = GetBuffer(11, 44);
		ProjectionTransformation(Mesh, Cam);
		glm::vec4 ambient = scene.CalculateAmbient();
		Ambient(Mesh, ambient);
		//DrawTriangle(Mesh,z_depth);
		
		//DrawFaceNormals(Mesh);
		//DrawVertexNormals(Mesh);

		
	}
	
	
}


void Renderer::Ambient(MeshModel& Mesh, glm::vec4 ambient) 
{
	glm::vec3 color = ambient;
	glm::fvec3 p1, p2, p3, p;
	float a12, a13, a23, b12, b13, b23, c12, c13, c23;
	int ur = 0, ul = 0, dl = 0, dr = 0;
	glm::fvec2 z_max_min = max_min_z(Mesh);
	glm::fvec2 z_max_min_avg = max_min_z_avg(Mesh);
	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		//glm::vec3 c = glm::vec3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		auto face = Mesh.GetFace(i);
		p1 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(0) - 1).x, Mesh.GetVertices(face.GetVertexIndex(0) - 1).y, Mesh.GetVertices(face.GetVertexIndex(0) - 1).z);
		p2 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(1) - 1).x, Mesh.GetVertices(face.GetVertexIndex(1) - 1).y, Mesh.GetVertices(face.GetVertexIndex(1) - 1).z);
		p3 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(2) - 1).x, Mesh.GetVertices(face.GetVertexIndex(2) - 1).y, Mesh.GetVertices(face.GetVertexIndex(2) - 1).z);
		DrawLine(p1, p2, color);
		DrawLine(p2, p3, color);
		DrawLine(p3, p1, color);
		float min_x = p1.x, max_x = p1.x, min_y = p1.y, max_y = p1.y, min_z = p1.z, max_z = p1.z;
		// max x
		if (max_x < p2.x)
			max_x = p2.x;
		if (max_x < p3.x)
			max_x = p3.x;
		// max y
		if (max_y < p2.y)
			max_y = p2.y;
		if (max_y < p3.y)
			max_y = p3.y;
		//min x
		if (min_x > p2.x)
			min_x = p2.x;
		if (min_x > p3.x)
			min_x = p3.x;
		// min y
		if (min_y > p2.y)
			min_y = p2.y;
		if (min_y > p3.y)
			min_y = p3.y;
		//min z
		if (min_z > p2.z)
			min_z = p2.z;
		if (min_z > p3.z)
			min_z = p3.z;
		// min z
		if (min_z > p2.z)
			min_z = p2.z;
		if (min_z > p3.z)
			min_z = p3.z;

		float w = max_x - min_x, h = max_y - min_y, k, m, l;
		float sum = (Mesh.GetVertices(face.GetVertexIndex(0) - 1).z + Mesh.GetVertices(face.GetVertexIndex(1) - 1).z + Mesh.GetVertices(face.GetVertexIndex(2) - 1).z) / 3.0f;
		glm::vec3 color_poly = glm::fvec3(sum, sum, sum);
		float a12 = p1.y - p2.y;
		float a23 = p2.y - p3.y;
		float a31 = p3.y - p1.y;
		float b12 = p2.x - p1.x;
		float b23 = p3.x - p2.x;
		float b31 = p1.x - p3.x;
		float c12 = (p1.x * p2.y - p2.x * p1.y);
		float c23 = (p2.x * p3.y - p3.x * p2.y);
		float c31 = (p3.x * p1.y - p1.x * p3.y);
		float e1, e2, e3, d, z, z_tag;
		//color_poly = glm::fvec3(255, 36, 36);
		float w1, w2, w3;
		//glm::fvec3 c = glm::fvec3(0, 36, 36);
		for (float y = min_y ; y <max_y; y++)
		{
			for (float x = min_x ; x < max_x; x++)
			{
				e1 = a12 * x + b12 * y + c12;
				e2 = a23 * x + b23 * y + c23;
				e3 = a31 * x + b31 * y + c31;
				if (e1 > 0 && e2 > 0 && e3 > 0) // inside the poly
				{
					PutPixel(x, y, color);
				}
			}
		}
	}
}

void Renderer::DrawAxesWorld(MeshModel& Mesh, Camera& Cam)
{
	glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// max x
		if (max.x < Mesh.GetVertices(i).x)
			max.x = Mesh.GetVertices(i).x;
		// max y
		if (max.y < Mesh.GetVertices(i).y)
			max.y = Mesh.GetVertices(i).y;
		// max z
		if (max.z < Mesh.GetVertices(i).z)
			max.z = Mesh.GetVertices(i).z;
	}
	glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// min x
		if (min.x > Mesh.GetVertices(i).x)
			min.x = Mesh.GetVertices(i).x;
		// min y
		if (min.y > Mesh.GetVertices(i).y)
			min.y = Mesh.GetVertices(i).y;
		// min z
		if (min.z > Mesh.GetVertices(i).z)
			min.z = Mesh.GetVertices(i).z;
	}
	float max_ = max.x;
	if (max.y > max_)
		max_ = max.y;
	if (max.z > max_)
		max_ = max.z;

	//glm::fvec3 center = glm::fvec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
	glm::fvec3 center = glm::fvec3(100.0f, 100, 100.0f);
	center = WolrdTransform_point(center, Mesh, Cam);
	glm::fvec3 p1 = WolrdTransform_point(glm::fvec3(max.x, 0.0f, 0.0f), Mesh, Cam);
	glm::fvec3 p2 = WolrdTransform_point(glm::fvec3(0.0f, max.y, 0.0f), Mesh, Cam);
	glm::fvec3 p3 = WolrdTransform_point(glm::fvec3(0.0f, 0.0f, max.z), Mesh, Cam);
	//
	
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 10.0f);
	DrawLine(center, p1, color);
	DrawLine(center, p2, color);
	DrawLine(center, p3, color);

}
void Renderer::DrawAxesModel(MeshModel& Mesh, Camera& Cam)
{
	glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// max x
		if (max.x < Mesh.GetVertices(i).x)
			max.x = Mesh.GetVertices(i).x;
		// max y
		if (max.y < Mesh.GetVertices(i).y)
			max.y = Mesh.GetVertices(i).y;
		// max z
		if (max.z < Mesh.GetVertices(i).z)
			max.z = Mesh.GetVertices(i).z;
	}
	glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// min x
		if (min.x > Mesh.GetVertices(i).x)
			min.x = Mesh.GetVertices(i).x;
		// min y
		if (min.y > Mesh.GetVertices(i).y)
			min.y = Mesh.GetVertices(i).y;
		// min z
		if (min.z > Mesh.GetVertices(i).z)
			min.z = Mesh.GetVertices(i).z;
	}
	float max_ = max.x;
	if (max.y > max_)
		max_ = max.y;
	if (max.z > max_)
		max_ = max.z;

	//glm::fvec3 center = glm::fvec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
	glm::fvec3 center = glm::fvec3(100.0f, 100.0f, 100.0f);
	center = LocalTransform_point(center, Mesh, Cam);
	glm::fvec3 p1 = LocalTransform_point(glm::fvec3(200.0f, 0.0f, 0.0f), Mesh, Cam);
	glm::fvec3 p2 = LocalTransform_point(glm::fvec3(0.0f, 200.0f, 0.0f), Mesh, Cam);
	glm::fvec3 p3 = LocalTransform_point(glm::fvec3(0.0f, 0.0f, 200.0f), Mesh, Cam);
	//
	glm::vec3 color = glm::vec3(50.0f, 0.0f, 0.0f);
	DrawLine(center, p1, color);
	DrawLine(center, p2, color);
	DrawLine(center, p3, color);
	
}

glm::fvec3 Renderer::LocalTransform_point(glm::fvec3 a, MeshModel& Mesh, Camera& Cam) {
	
	// tranformatiom = projection * inv(cam_trans) * mesh_trans
	glm::mat4x4 Projection = Cam.GetProjectionTransformation();
	glm::mat4x4 cam_trans = glm::inverse(Cam.GetViewTransformation());
	glm::mat4 Mesh_trans = Mesh.GetTransformation();
	glm::mat4  M = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	M = Projection * Mesh_trans;
	glm::fvec4 p = glm::fvec4(a.x, a.y, a.z, 1);
	p = p * M;
	return glm::fvec3(p.x, p.y , p.z);
}
glm::fvec3 Renderer::WolrdTransform_point(glm::fvec3 a, MeshModel& Mesh, Camera& Cam) {
	// tranformatiom = projection * inv(cam_trans)
	glm::mat4x4 Projection = Cam.GetProjectionTransformation();
	glm::mat4x4 cam_trans = glm::inverse(Cam.GetViewTransformation());
	glm::mat4x4 world_trans = Mesh.GetworldTransform();
	glm::mat4  M = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	M = Projection * world_trans;
	glm::fvec4 p = glm::fvec4(a.x, a.y, a.z, 1.0f);
	p = M * p;
	/*p.x = p.x * M[0][0] + p.y * M[0][1] + p.z * M[0][2] + p.w * M[0][3];
	p.y = p.x * M[1][0] + p.y * M[1][1] + p.z * M[1][2] + p.w * M[1][3];
	p.z = p.x * M[2][0] + p.y * M[2][1] + p.z * M[2][2] + p.w * M[2][3];
	p.w = p.x * M[3][0] + p.y * M[3][1] + p.z * M[3][2] + p.w * M[3][3];*/
	return glm::fvec3(p.x, p.y, p.z);
}

void Renderer::DrawFaceNormals(MeshModel& Mesh)
{
	glm::vec3 color = glm::vec3(0.0f, 170.0f, 200.0f);
	glm::fvec3 p1, p2, p3, normal, n1, n2;
	glm::fvec2  middle;

	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		auto face = Mesh.GetFace(i);
		p1 = Mesh.GetVertices(face.GetVertexIndex(0) - 1);
		p2 = Mesh.GetVertices(face.GetVertexIndex(1) - 1);
		p3 = Mesh.GetVertices(face.GetVertexIndex(2) - 1);

		middle = glm::fvec2((p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3);
		normal = glm::cross(p2 - p1, p3 - p1); //normal = normal * 2.0f;
		glm::fvec2 p;
		p.x = normal.x / 6.0f + middle.x;
		p.y = normal.y / 6.0f + middle.y;
		DrawLine(middle, p, color);

	}
}
void Renderer::DrawVertexNormals(MeshModel& Mesh)
{
	glm::vec3 color = glm::vec3(200.0f, 0.0f, 0.0f);
	glm::fvec3 p1, p2, p3, n1, n2, n3;
	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		auto face = Mesh.GetFace(i);

		p1 = Mesh.GetVertices(face.GetVertexIndex(0) - 1);
		p2 = Mesh.GetVertices(face.GetVertexIndex(1) - 1);
		p3 = Mesh.GetVertices(face.GetVertexIndex(2) - 1);
		n1 = glm::normalize(p1) * 20.0f + p1;
		n2 = glm::normalize(p2) * 20.0f + p2;
		n3 = glm::normalize(p3) * 20.0f + p3;
		DrawLine(glm::fvec2(p1.x, p1.y), glm::fvec2(n1.x, n1.y), color);
		DrawLine(glm::fvec2(p2.x, p2.y), glm::fvec2(n2.x, n2.y), color);
		DrawLine(glm::fvec2(p3.x, p3.y), glm::fvec2(n3.x, n3.y), color);

	}

}

void Renderer::ProjectionTransformation(MeshModel& Mesh,Camera& Cam)
{
	glm::mat4x4 Projection = Cam.GetProjectionTransformation();
	glm::mat4x4 cam_trans = glm::inverse(Cam.GetViewTransformation());
	glm::mat4x4 mesh_transformation = Mesh.GetTransformation();
	glm::mat4x4 M;
	M = Projection * /*cam_trans**/ mesh_transformation;
	glm::fvec4 p, r; float x, y, z, w;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		p = glm::fvec4(Mesh.GetVertices(i).x, Mesh.GetVertices(i).y, Mesh.GetVertices(i).z, 1);
		r = p * M;
		Mesh.SetVertices(glm::fvec3(r.x, r.y, r.z), i);
	}
}
void Renderer::CameraTransformarion(MeshModel& Mesh, Camera& Cam)
{
	glm::mat4x4 mesh_transformation = Mesh.GetTransformation();
	glm::mat4x4 view_trans = Cam.GetViewTransformation();
	glm::mat4x4 M;
	M = view_trans * mesh_transformation;
	glm::fvec4 p,r; float x, y, z, w;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		p = glm::fvec4(Mesh.GetVertices(i).x, Mesh.GetVertices(i).y, Mesh.GetVertices(i).z, 1);
		r = p * M;
		Mesh.SetVertices(glm::fvec3(r.x, r.y, r.z), i);
	}	
}
void Renderer::Orth(MeshModel& Mesh, Camera& Cam)
{
	glm::mat4x4 mesh_transformation = Mesh.GetTransformation();
	glm::mat4x4 camera_orth = Cam.GetOrthMat();
	glm::mat4x4 M;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += camera_orth[i][k] * mesh_transformation[k][j];
			}
			M[i][j] = sum;
		}
	}
	glm::fvec4 p; float x, y, z, w;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		p = glm::fvec4(Mesh.GetVertices(i).x, Mesh.GetVertices(i).y, Mesh.GetVertices(i).z, 1);
		x = p.x * M[0][0] + p.y * M[0][1] + p.z * M[0][2] + p.w * M[0][3];
		y = p.x * M[1][0] + p.y * M[1][1] + p.z * M[1][2] + p.w * M[1][3];
		z = p.x * M[2][0] + p.y * M[2][1] + p.z * M[2][2] + p.w * M[2][3];
		w = p.x * M[3][0] + p.y * M[3][1] + p.z * M[3][2] + p.w * M[3][3];
		Mesh.SetVertices(glm::fvec3(x, y, z), i);
	}
}
void Renderer::Perspective(MeshModel& Mesh, Camera& Cam)
{
	glm::mat4x4 mesh_transformation = Mesh.GetTransformation();
	glm::mat4x4 camera_pers = Cam.GetPersMat();
	glm::mat4x4 M;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += camera_pers[i][k] * mesh_transformation[k][j];
			}
			M[i][j] = sum;
		}
	}
	glm::fvec4 p; float x, y, z, w;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		p = glm::fvec4(Mesh.GetVertices(i).x, Mesh.GetVertices(i).y, Mesh.GetVertices(i).z, 1);
		x = p.x * M[0][0] + p.y * M[0][1] + p.z * M[0][2] + p.w * M[0][3];
		y = p.x * M[1][0] + p.y * M[1][1] + p.z * M[1][2] + p.w * M[1][3];
		z = p.x * M[2][0] + p.y * M[2][1] + p.z * M[2][2] + p.w * M[2][3];
		w = p.x * M[3][0] + p.y * M[3][1] + p.z * M[3][2] + p.w * M[3][3];
		//std::cout << p.z<< "\n";
		Mesh.SetVertices(glm::fvec3(x, y, z), i);
	}
}

void Renderer::DrawBoundingBoxModel(MeshModel& Mesh, Camera& Cam)
{

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 200.0f);
	glm::mat4x4 Projection = Cam.GetProjectionTransformation();
	glm::mat4x4 cam_trans = glm::inverse(Cam.GetViewTransformation());
	glm::mat4 Mesh_trans = Mesh.GetTransformation();
	glm::mat4  M = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	M = Projection  * Mesh_trans;
	//glm::mat4 M = Mesh.GetTransformation();
	glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// max x
		if (max.x < Mesh.GetVertices(i).x)
			max.x = Mesh.GetVertices(i).x;
		// max y
		if (max.y < Mesh.GetVertices(i).y)
			max.y = Mesh.GetVertices(i).y;
		// max z
		if (max.z < Mesh.GetVertices(i).z)
			max.z = Mesh.GetVertices(i).z;
	}
	glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// min x
		if (min.x > Mesh.GetVertices(i).x)
			min.x = Mesh.GetVertices(i).x;
		// min y
		if (min.y > Mesh.GetVertices(i).y)
			min.y = Mesh.GetVertices(i).y;
		// min z
		if (min.z > Mesh.GetVertices(i).z)
			min.z = Mesh.GetVertices(i).z;
	}

	std::vector<glm::fvec3> bb;
	bb.push_back(glm::fvec3(min.x, min.y, min.z));// 000  0
	bb.push_back(glm::fvec3(max.x, min.y, min.z));// 100  1
	bb.push_back(glm::fvec3(max.x, max.y, min.z));// 110  2
	bb.push_back(glm::fvec3(min.x, max.y, min.z));// 010  3
	bb.push_back(glm::fvec3(min.x, min.y, max.z));// 001  4
	bb.push_back(glm::fvec3(max.x, min.y, max.z));// 101  5
	bb.push_back(glm::fvec3(max.x, max.y, max.z));// 111  6
	bb.push_back(glm::fvec3(min.x, max.y, max.z));// 011  7
	glm::fvec4 p;
	for (auto i = 0; i < 8; i++)
	{
		p = glm::fvec4(bb[i].x, bb[i].y, bb[i].z, 1);
		p = p * M;
		bb[i]=glm::fvec3(p.x , p.y ,p.z);
	}



	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[1].x, bb[1].y), color);
	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[4].x, bb[4].y), color);

	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[4].x, bb[4].y), color);

	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[1].x, bb[1].y), color);

	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[4].x, bb[4].y), color);
	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[1].x, bb[1].y), color);
	
}
void Renderer::DrawBoundingBoxWorld(MeshModel& Mesh, Camera& Cam)
{

	glm::vec3 color = glm::vec3(180.0f, 0.0f, 180.0f);
	/*Mesh.SetworldTransform();
	glm::mat4 M = Mesh.GetworldTransform();*/
	glm::mat4x4 Projection = Cam.GetProjectionTransformation();
	glm::mat4x4 cam_trans = glm::inverse(Cam.GetViewTransformation());
	glm::mat4  M = { { 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f } };

	M = Projection * Mesh.GetTransformation();
	glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// max x
		if (max.x < Mesh.GetVertices(i).x)
			max.x = Mesh.GetVertices(i).x;
		// max y
		if (max.y < Mesh.GetVertices(i).y)
			max.y = Mesh.GetVertices(i).y;
		// max z
		if (max.z < Mesh.GetVertices(i).z)
			max.z = Mesh.GetVertices(i).z;
	}
	glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, Mesh.GetVertices(0).z);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// min x
		if (min.x > Mesh.GetVertices(i).x)
			min.x = Mesh.GetVertices(i).x;
		// min y
		if (min.y > Mesh.GetVertices(i).y)
			min.y = Mesh.GetVertices(i).y;
		// min z
		if (min.z > Mesh.GetVertices(i).z)
			min.z = Mesh.GetVertices(i).z;
	}

	std::vector<glm::fvec3> bb;
	bb.push_back(glm::fvec3(min.x, min.y, min.z));// 000  0
	bb.push_back(glm::fvec3(max.x, min.y, min.z));// 100  1
	bb.push_back(glm::fvec3(max.x, max.y, min.z));// 110  2
	bb.push_back(glm::fvec3(min.x, max.y, min.z));// 010  3
	bb.push_back(glm::fvec3(min.x, min.y, max.z));// 001  4
	bb.push_back(glm::fvec3(max.x, min.y, max.z));// 101  5
	bb.push_back(glm::fvec3(max.x, max.y, max.z));// 111  6
	bb.push_back(glm::fvec3(min.x, max.y, max.z));// 011  7
	glm::fvec4 p;
	for (auto i = 0; i < 8; i++)
	{
		p = glm::fvec4(bb[i].x, bb[i].y, bb[i].z, 1);
		p = p * M;
		bb[i] = glm::fvec3(p.x, p.y, p.z);
	}



	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[1].x, bb[1].y), color);
	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[0].x, bb[0].y), glm::fvec2(bb[4].x, bb[4].y), color);

	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[7].x, bb[7].y), glm::fvec2(bb[4].x, bb[4].y), color);

	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[3].x, bb[3].y), color);
	DrawLine(glm::fvec2(bb[2].x, bb[2].y), glm::fvec2(bb[1].x, bb[1].y), color);

	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[4].x, bb[4].y), color);
	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[6].x, bb[6].y), color);
	DrawLine(glm::fvec2(bb[5].x, bb[5].y), glm::fvec2(bb[1].x, bb[1].y), color);

}

void Depth(MeshModel& Mesh , glm::fvec3 p1, glm::fvec3 p2, glm::fvec3 p3, glm::fvec3 p)
{
	// first we find the max Z
	float w1, w2, w3;
	w1 = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) /
		((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));

	w2 = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) /
		((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));

	w3 = 1 - w1 - w2;
	p.z = w1 * p1.z + w2 * p2.z + w3 * p3.z;
	float max_z = Mesh.GetVertices(0).z;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		if (max_z < Mesh.GetVertices(i).z)
			max_z = Mesh.GetVertices(i).z;
	}
	std::vector<float> Depth;

}

void Renderer::DrawTriangle(MeshModel& Mesh, vector<vector<float>>& z_depth)
{
	
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f) ,temp;
	glm::fvec3 p1, p2, p3, p;
	float a12, a13, a23, b12, b13, b23, c12, c13, c23;
	int ur = 0, ul = 0, dl = 0, dr = 0;
	glm::fvec2 z_max_min = max_min_z(Mesh);
	glm::fvec2 z_max_min_avg = max_min_z_avg(Mesh);
	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		//glm::vec3 c = glm::vec3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		auto face = Mesh.GetFace(i);
		p1 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(0) - 1).x, Mesh.GetVertices(face.GetVertexIndex(0) - 1).y, Mesh.GetVertices(face.GetVertexIndex(0) - 1).z);
		p2 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(1) - 1).x, Mesh.GetVertices(face.GetVertexIndex(1) - 1).y, Mesh.GetVertices(face.GetVertexIndex(1) - 1).z);
		p3 = glm::fvec3(Mesh.GetVertices(face.GetVertexIndex(2) - 1).x, Mesh.GetVertices(face.GetVertexIndex(2) - 1).y, Mesh.GetVertices(face.GetVertexIndex(2) - 1).z);
		DrawLine(p1, p2, color);
		DrawLine(p2, p3, color);
		DrawLine(p3, p1, color);

		// Drawing Bounding Rectangle
		// fisrt we find the min x, min y, max x, max y
		//float min_x = p1.x, max_x = p1.x, min_y = p1.y, max_y = p1.y, min_z = p1.z, max_z = p1.z;
		//// max x
		//if (max_x < p2.x)
		//	max_x = p2.x;
		//if (max_x < p3.x)
		//	max_x = p3.x;
		//// max y
		//if (max_y < p2.y)
		//	max_y = p2.y;
		//if (max_y < p3.y)
		//	max_y = p3.y;
		////min x
		//if (min_x > p2.x)
		//	min_x = p2.x;
		//if (min_x > p3.x)
		//	min_x = p3.x;
		//// min y
		//if (min_y > p2.y)
		//	min_y = p2.y;
		//if (min_y > p3.y)
		//	min_y = p3.y;
		////min z
		//if (min_z > p2.z)
		//	min_z = p2.z;
		//if (min_z > p3.z)
		//	min_z = p3.z;
		//// min z
		//if (min_z > p2.z)
		//	min_z = p2.z;
		//if (min_z > p3.z)
		//	min_z = p3.z;
		////glm::fvec2 c1, c2, c3, c4;
		////c1 = glm::fvec2(min_x, min_y);
		////c2 = glm::fvec2(min_x, max_y);
		////c3 = glm::fvec2(max_x, min_y);
		////c4 = glm::fvec2(max_x, max_y);
		////float c_z = (Mesh.GetVertices(face.GetVertexIndex(0) - 1).z + Mesh.GetVertices(face.GetVertexIndex(1) - 1).z +
		////	Mesh.GetVertices(face.GetVertexIndex(1) - 1).z) / 3.0f;
		////glm::vec3 color_rec = glm::vec3(255.0f / c_z, 36.0f / c_z, 36.0f / c_z);
		////DrawLine(c1, c2, color_rec);
		////DrawLine(c1, c3, color_rec);
		////DrawLine(c3, c4, color_rec);
		////DrawLine(c4, c2, color_rec);
		// //we have a rectangle w x h
		//float w = max_x - min_x, h = max_y - min_y, k, m, l;
		//float sum = (Mesh.GetVertices(face.GetVertexIndex(0) - 1).z + Mesh.GetVertices(face.GetVertexIndex(1) - 1).z + Mesh.GetVertices(face.GetVertexIndex(2) - 1).z) / 3.0f;
		//glm::vec3 color_poly = glm::fvec3(sum, sum, sum);
		//float a12 = p1.y - p2.y;
		//float a23 = p2.y - p3.y;
		//float a31 = p3.y - p1.y;
		//float b12 = p2.x - p1.x;
		//float b23 = p3.x - p2.x;
		//float b31 = p1.x - p3.x;
		//float c12 = (p1.x * p2.y - p2.x * p1.y);
		//float c23 = (p2.x * p3.y - p3.x * p2.y);
		//float c31 = (p3.x * p1.y - p1.x * p3.y);
		//float e1, e2, e3, d, z, z_tag;
		////color_poly = glm::fvec3(255, 36, 36);
		//float w1, w2, w3;
		////glm::fvec3 c = glm::fvec3(0, 36, 36);
		//for (float y = min_y ; y <max_y; y++)
		//{
		//	for (float x = min_x ; x < max_x; x++)
		//	{
		//		e1 = a12 * x + b12 * y + c12;
		//		e2 = a23 * x + b23 * y + c23;
		//		e3 = a31 * x + b31 * y + c31;
		//		if (e1 > 0 && e2 > 0 && e3 > 0) // inside the poly
		//		{
		//			float avg = (p1.z + p2.z + p3.z) / 3.0;
		//			float z_d = (avg - z_max_min_avg.y) / (z_max_min_avg.x - z_max_min_avg.y);
		//			if (z_depth[x][y] > z_d)
		//			{
		//				z_depth[x][y ] = z_d;
		//				//PutPixel(x, y, c);
		//				PutPixel(x, y, glm::fvec3(z_d, z_d, z_d));
		//			}
		//		}
		//	}
		//}
	}
}

glm::fvec2 Renderer::max_min_z(MeshModel& Mesh)
{
	int s = Mesh.GetVerticesSize();
	float max = Mesh.GetVertices(0).z, min = Mesh.GetVertices(0).z;
	for (int i = 0; i < s; i++)
	{
		if (Mesh.GetVertices(i).z < Mesh.depth[i])
		{
			if (max < Mesh.GetVertices(i).z)
			{
				max = Mesh.GetVertices(i).z;
			}
			if (min > Mesh.GetVertices(i).z)
			{
				min = Mesh.GetVertices(i).z;
			}
		}
	}
	return glm::fvec2(max, min);
}

glm::fvec2 Renderer::max_min_z_avg(MeshModel& Mesh)
{
	int s = Mesh.GetVerticesSize();
	glm::fvec3 p1, p2, p3;
	auto face = Mesh.GetFace(0);
	float avg = 0, max = -1000*Mesh.GetVertices(face.GetVertexIndex(0) - 1).z, min = 1000 *Mesh.GetVertices(face.GetVertexIndex(0) - 1).z;
	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		//	glm::vec3 c = glm::vec3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		auto face = Mesh.GetFace(i);
		avg = Mesh.GetVertices(face.GetVertexIndex(0) - 1).z + Mesh.GetVertices(face.GetVertexIndex(1) - 1).z +
			Mesh.GetVertices(face.GetVertexIndex(2) - 1).z;
		if (max < avg) max = avg;
		if (min > avg) min = avg;

	}
	return glm::fvec2(max, min);
}


vector<vector<float>> Renderer::GetBuffer(int h, int w)
{
	vector<vector<float>>z_depth;
	for (int i = 0; i < 720; i++)
	{
		vector<float> row;
		for (int j = 0; j < 1280; j++)
		{
			row.push_back(INFINITY);
		}
		z_depth.push_back(row);
	}
	return z_depth;
}
void Renderer::Z_Buffer(MeshModel& Mesh)
{

	int s = Mesh.GetVerticesSize();
	for (int i = 0; i < s; i++)
	{
		if (Mesh.GetVertices(i).z < Mesh.depth[i])
		{
			Mesh.depth[i] = Mesh.GetVertices(i).z;
			Mesh.color[i] = glm::fvec3(5 * Mesh.depth[i], 5 * Mesh.depth[i], 5 * Mesh.depth[i]);
		}
	}
}
void Renderer::Transformation(MeshModel& Mesh)
{
	glm::mat4 M = Mesh.GetTransformation();
	glm::fvec4 p; float x, y, z, w;
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		p = glm::fvec4(Mesh.GetVertices(i).x, Mesh.GetVertices(i).y, Mesh.GetVertices(i).z, 1);
		x = p.x * M[0][0] + p.y * M[0][1] + p.z * M[0][2] + p.w * M[0][3];
		y = p.x * M[1][0] + p.y * M[1][1] + p.z * M[1][2] + p.w * M[1][3];
		z = p.x * M[2][0] + p.y * M[2][1] + p.z * M[2][2] + p.w * M[2][3];
		w = p.x * M[3][0] + p.y * M[3][1] + p.z * M[3][2] + p.w * M[3][3];
		Mesh.SetVertices(glm::fvec3(x / w, y / w, z / w), i);
	}
}

//void Renderer::FixPoints(MeshModel& Mesh)
//{
//	glm::fvec3 vec;
//	for (int i = 0; i < Mesh.RetVerticesSize(); i++)  // (x/y, z/y, 1)
//	{
//		vec = glm::fvec3((float)(Mesh.GetVertices(i).x) / Mesh.GetVertices(i).z, (float)(Mesh.GetVertices(i).y) / Mesh.GetVertices(i).z, 1);
//		Mesh.SetVertices(vec, i);
//	}
//
//	glm::fvec3 trans_vec = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, Mesh.GetVertices(0).z);
//	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
//	{
//		// min x
//		if (trans_vec.x > Mesh.GetVertices(i).x)
//			trans_vec.x = Mesh.GetVertices(i).x;
//		// min y
//		if (trans_vec.y > Mesh.GetVertices(i).y)
//			trans_vec.y = Mesh.GetVertices(i).y;
//		// min z
//		if (trans_vec.z > Mesh.GetVertices(i).z)
//			trans_vec.z = Mesh.GetVertices(i).z;
//	}
//	float min = trans_vec.x;
//	if (trans_vec.y < min)
//		min = trans_vec.y;
//	if (trans_vec.z < min)
//		min = trans_vec.z;
//	if (min < 0)
//	{
//		min *= (-1.0f);
//		trans_vec.x = min; trans_vec.y = min; trans_vec.z = min;
//		for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
//		{
//			Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x + trans_vec.x, Mesh.GetVertices(i).y + trans_vec.y, Mesh.GetVertices(i).z + trans_vec.z), i);
//		}
//	}
//	/// 
//
//	glm::fvec3 scale_vec = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, 1);
//	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
//	{
//		// max x
//		if (scale_vec.x < Mesh.GetVertices(i).x)
//			scale_vec.x = Mesh.GetVertices(i).x;
//		// max y
//		if (scale_vec.y < Mesh.GetVertices(i).y)
//			scale_vec.y = Mesh.GetVertices(i).y;
//		// max z
//		if (scale_vec.z < Mesh.GetVertices(i).z)
//			scale_vec.z = Mesh.GetVertices(i).z;
//
//	}
//	float max = scale_vec.x;
//	if (scale_vec.y > max)
//		max = scale_vec.y;
//	if (scale_vec.z > max)
//		max = scale_vec.z;
//	scale_vec.x = 600 / max; scale_vec.y = 600 / max; scale_vec.z = 600 / max;
//	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
//	{
//		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * scale_vec.x, Mesh.GetVertices(i).y * scale_vec.y, Mesh.GetVertices(i).z * scale_vec.z), i);
//	}
//}



/// okay here we have (x/z, y/z, 1) 
// scale:
// first we will biuld the matrix:
/*
*	Sx 0  0  0     x     Sx * x
*	0  Sy 0  0  *  y  =	 Sy * y
*	0  0  Sz 0     z     Sz * z
*	0  0  0  1     w        w
*/
void Renderer::Scale(MeshModel& Mesh, glm::fvec3 scale_vec)
{
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * scale_vec.x, Mesh.GetVertices(i).y * scale_vec.y, 1), i);
	}

}

// Translate:
// first we will biuld the matrix:
/*
*	1  0  0  Tx     x     Tx + x
*	0  1  0  Ty  *  y  =  Ty + y
*	0  0  1  Tz     z     Tz + z
*	0  0  0  1      w        w
*/
void Renderer::Translate(MeshModel& Mesh, glm::fvec3 translate_vec)
{
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x + translate_vec.x, Mesh.GetVertices(i).y + translate_vec.y, 1), i);
	}
}

// Rotate Z:
/*
*	cosa -sina  0  0     x     x * cosa - y * sina
*	sina  cosa  0  0  *  y  =  x * sina + x * cosa
*	0       0   1  0     z        z
*	0       0   0  1     w        w
*/

void Renderer::Rotate(MeshModel& Mesh, float degree)
{
	glm::fvec3 rotate_vec = glm::vec3(0.0f, 0.0f, 1.0f);
	float radian = degree * (M_PI / 180);
	float cs = cos(radian);
	float sn = sin(radian);
	// now we have to rotate
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		rotate_vec.x = Mesh.GetVertices(i).x * cs - Mesh.GetVertices(i).y * sn;
		rotate_vec.y = Mesh.GetVertices(i).x * sn + Mesh.GetVertices(i).y * cs;
		Mesh.SetVertices(glm::fvec3(rotate_vec.x, rotate_vec.y, 1), i);
	}
}


void HW1()
{
	// points
	// --- ALL THE FOLLOWING ARE FROM HW1 --- 
	/*glm::ivec2 p1 = glm::ivec2(700.0f, 500.0f), p2;
	int x0 = p1.x, y0 = p1.y;
	// the color = red :)
	glm::vec3 color = glm::vec3(10.0f, 0.0f, 0.0f);
	int a = 360, r = 200;
	// draw circle
	for (int i = 0; i < 360; i++)
	{
		p2 = glm::ivec2(x0 - r * sin(2 * M_PI * i / a), y0 - r * cos(2 * M_PI * i / a));
		DrawLine(p1, p2, color);
	}

	// trying to make a cube:
	glm::vec3 cube_color = glm::vec3(0.0f, 0.0f, 100.0f);
	glm::vec3 pyramid_color = glm::vec3(50.0f, 0.0f, 10.0f);
	glm::ivec2 _a = glm::ivec2(0.0f, 0.0f),
		b = glm::ivec2(300.0f, 0.0f),
		c = glm::ivec2(300.0f, 300.0f),
		d = glm::ivec2(0.0f, 300.0f),
		e = glm::ivec2(150.0f, 150.0f),
		f = glm::ivec2(450.0f, 150.0f),
		g = glm::ivec2(450.0f, 450.0f),
		h = glm::ivec2(150.0f, 450.0f),
		top = glm::ivec2(255.0f, 600.0f);
	// dtawing cube:
	DrawLine(_a, d, cube_color);
	DrawLine(_a, b, cube_color);
	DrawLine(_a, e, cube_color);
	DrawLine(d, c, cube_color);
	DrawLine(d, h, cube_color);
	DrawLine(c, b, cube_color);
	DrawLine(c, g, cube_color);
	DrawLine(h, g, cube_color);
	DrawLine(h, e, cube_color);
	DrawLine(g, f, cube_color);
	DrawLine(e, f, cube_color);
	DrawLine(f, b, cube_color);
	// drawing pyramid in top of the cube to get a houe:)
	DrawLine(d, top, pyramid_color);
	DrawLine(h, top, pyramid_color);
	DrawLine(g, top, pyramid_color);
	DrawLine(c, top, pyramid_color);

	// trying to darw a cat: just for fun :)
	// the face coordinates

	int Face[29][2] = { {301,7},{409,60},{613,343},{1015,432},{1203,293},{1379,259},{1408,325},{1384,448},
		{1384,448},{1314,645},{1321,687},{1290,758},{1314,978},{1133,1266},{991,1342},{815,1345},{826,1371},
		{650,1358},{482,1253},{338,1112},{225,994},{183,855},{178,752},{220,613},{194,493},{215,390},{204,306},
		{207,183},{259,26} };
	glm::vec2 cat_cor1, cat_cor2;
	glm::vec3 cat_color = glm::vec3(50.0f, 0.0f, 10.0f);
	for (int i = 0; i < 28; i++)
	{
		cat_cor1 = glm::vec2(Face[i][0] / 2, Face[i][1] / 2);
		cat_cor2 = glm::vec2(Face[i + 1][0] / 2, Face[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	DrawLine(cat_cor1, glm::vec2(Face[0][0] / 2, Face[0][1] / 2), cat_color);
	int right_eye[9][2] = { {417,660},{451,603},{532,598},{584,626},{634,679},{548,760},{479,742},{451,710}, {417,660} };
	for (int i = 0; i < 8; i++)
	{
		cat_cor1 = glm::vec2(right_eye[i][0] / 2, right_eye[i][1] / 2);
		cat_cor2 = glm::vec2(right_eye[i + 1][0] / 2, right_eye[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	int left_eye[11][2] = { {973,815},{965,760},{999,718},{1046,697},{1112,700},{1164,737},{1175,786},
		{1133,836},{1080,844},{1022,831},{975,818} };
	for (int i = 0; i < 10; i++)
	{
		cat_cor1 = glm::vec2(left_eye[i][0] / 2, left_eye[i][1] / 2);
		cat_cor2 = glm::vec2(left_eye[i + 1][0] / 2, left_eye[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	int nose[13][2] = { {689,915},{729,897},{786,894},{839,915},{860,939},{881,962},{839,988},{813,1009},
		{779,1025},{747,996},{721,973},{702,941},{692,915} };
	for (int i = 0; i < 12; i++)
	{
		cat_cor1 = glm::vec2(nose[i][0] / 2, nose[i][1] / 2);
		cat_cor2 = glm::vec2(nose[i + 1][0] / 2, nose[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	int mouth1[8][2] = { {758,1093},{726,1109},{684,1133},{640,1154},{574,1177},{514,1169},{493,1138},{464,1109} };
	for (int i = 0; i < 7; i++)
	{
		cat_cor1 = glm::vec2(mouth1[i][0] / 2, mouth1[i][1] / 2);
		cat_cor2 = glm::vec2(mouth1[i + 1][0] / 2, mouth1[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	int mouth2[9][2] = { {760,1099},{786,1117},{818,1148},{849,1175},{878,1203 }, { 910,1224 },
	{ 944,1245 }, { 988,1232 }, { 1007,1211 } };
	for (int i = 0; i < 8; i++)
	{
		cat_cor1 = glm::vec2(mouth2[i][0] / 2, mouth2[i][1] / 2);
		cat_cor2 = glm::vec2(mouth2[i + 1][0] / 2, mouth2[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	int mouth3[6][2] = { {629,1172},{676,1169},{729,1172},{784,1172},{828,1193},{870,1209} };
	for (int i = 0; i < 5; i++)
	{
		cat_cor1 = glm::vec2(mouth3[i][0] / 2, mouth3[i][1] / 2);
		cat_cor2 = glm::vec2(mouth3[i + 1][0] / 2, mouth3[i + 1][1] / 2);
		DrawLine(cat_cor1, cat_cor2, cat_color);
	}
	*/
}





int Renderer::GetViewportWidth() const
{
	return viewport_width;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height;
}