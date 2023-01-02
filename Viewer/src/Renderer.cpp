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
	if (m < 1 && m > -1) // the cases is -1 < Incline < 1
	{
		//plotLineLow
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
		// plotLineHigh
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
		if (dy > 0)
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
	}
	else if (abs(y1 - y0) < abs(x1 - x0))
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
		//auto Cam = scene.GetActiveCamera();

		glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, 1);
		for (int i = 0; i < Mesh.RetVerticesSize(); i++)
		{
			// max x
			if (max.x < Mesh.GetVertices(i).x)
				max.x = Mesh.GetVertices(i).x;
			// max y
			if (max.y < Mesh.GetVertices(i).y)
				max.y = Mesh.GetVertices(i).y;
		}
		glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, 1);
		for (int i = 0; i < Mesh.RetVerticesSize(); i++)
		{
			// min x
			if (min.x > Mesh.GetVertices(i).x)
				min.x = Mesh.GetVertices(i).x;
			// min y
			if (min.y > Mesh.GetVertices(i).y)
				min.y = Mesh.GetVertices(i).y;
		}
		glm::fvec2 A = glm::fvec2(min.x, max.y), B = glm::fvec2(max.x, max.y),
			C = glm::fvec2(min.x, min.y), D = glm::fvec2(max.x, min.y);
		Mesh.SetMax(max); Mesh.SetMin(min);
		Transformation(Mesh);
		//DrawTriangle(Mesh);
		DrawBoundingBox(Mesh);
		/// we need to multipy Orth x trasformation.
		//glm::mat4x4 mesh_transformation = Mesh.GetTransformation();
		//glm::mat4x4 camera_orth = Cam.GetOrthMat();
		//glm::mat4x4 M;
		//for (int i = 0; i < 3; i++) {
		//	for (int j = 0; j < 3; j++) {
		//		float sum = 0.0f;
		//		for (int k = 0; k < 3; k++) {
		//			sum += mesh_transformation[i][k] * camera_orth[k][j];
		//		}
		//		M[i][j] = sum;
		//	}
		//}
		//for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
		//{
		//	Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * M[0][0] + Mesh.GetVertices(i).y * M[0][1] + M[0][2],
		//		Mesh.GetVertices(i).x * M[1][0] + Mesh.GetVertices(i).y * M[1][1] + M[1][2], 1), i);
		//}
		//DrawTriangle(Mesh);

		
	}
	
	
}


void Renderer::Transformation(MeshModel& Mesh)
{
	glm::mat4 M = Mesh.GetTransformation();
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * M[0][0] + Mesh.GetVertices(i).y * M[0][1] + M[0][2],
			Mesh.GetVertices(i).x * M[1][0] + Mesh.GetVertices(i).y * M[1][1] + M[1][2], 1), i);
	}
}

void Renderer::DrawBoundingBox(MeshModel& Mesh)
{

	glm::vec3 color = glm::vec3(20.0f, 10.0f, 20.0f);
	//glm::fvec3 max = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, 1);
	//for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	//{
	//	// max x
	//	if (max.x < Mesh.GetVertices(i).x)
	//		max.x = Mesh.GetVertices(i).x;
	//	// max y
	//	if (max.y < Mesh.GetVertices(i).y)
	//		max.y = Mesh.GetVertices(i).y;

	//}
	//glm::fvec3 min = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, 1);
	//for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	//{
	//	// min x
	//	if (min.x > Mesh.GetVertices(i).x)
	//		min.x = Mesh.GetVertices(i).x;
	//	// min y
	//	if (min.y > Mesh.GetVertices(i).y)
	//		min.y = Mesh.GetVertices(i).y;
	//}

	glm::fvec3 min = Mesh.GetMin();  glm::fvec3 max = Mesh.GetMax();
	glm::fvec2 A = glm::fvec2(min.x, max.y), B = glm::fvec2(max.x, max.y),
		C = glm::fvec2(min.x, min.y), D = glm::fvec2(max.x, min.y);
	glm::mat4 M = Mesh.GetTransformation();
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		A= glm::fvec2(A.x * M[0][0] + A.y * M[0][1] + M[0][2],A.x * M[1][0] + A.y * M[1][1] + M[1][2]);
		B = glm::fvec2(B.x * M[0][0] + B.y * M[0][1] + M[0][2], B.x * M[1][0] + B.y * M[1][1] + M[1][2]);
		C = glm::fvec2(C.x * M[0][0] + C.y * M[0][1] + M[0][2], C.x * M[1][0] + C.y * M[1][1] + M[1][2]);
		D = glm::fvec2(D.x * M[0][0] + D.y * M[0][1] + M[0][2], D.x * M[1][0] + D.y * M[1][1] + M[1][2]);

	}
	
	DrawLine(A, B, color); // A B
	DrawLine(A, C, color); // A C
	DrawLine(C, D, color); // C D
	DrawLine(D, B, color); // D B
}



void Renderer::DrawTriangle(MeshModel& Mesh)
{
	glm::vec3 color = glm::vec3(200.0f, 10.0f, 0.0f);
	glm::fvec2 p1, p2, p3;
	for (int i = 0; i < Mesh.GetFacesCount(); i++)
	{
		auto face = Mesh.GetFace(i);
		//std::cout << "( " << Mesh.GetVertices(face.GetVertexIndex(0) - 1).x << " , " << Mesh.GetVertices(face.GetVertexIndex(0) - 1).y << "\n";
		p1 = glm::fvec2(Mesh.GetVertices(face.GetVertexIndex(0) - 1).x, Mesh.GetVertices(face.GetVertexIndex(0) - 1).y);
		p2 = glm::fvec2(Mesh.GetVertices(face.GetVertexIndex(1) - 1).x, Mesh.GetVertices(face.GetVertexIndex(1) - 1).y);
		p3 = glm::fvec2(Mesh.GetVertices(face.GetVertexIndex(2) - 1).x, Mesh.GetVertices(face.GetVertexIndex(2) - 1).y);
		DrawLine(p1, p2, color);
		DrawLine(p2, p3, color);
		DrawLine(p3, p1, color);

	}
}

void Renderer::FixPoints(MeshModel& Mesh)
{
	glm::fvec3 vec;
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)  // (x/y, z/y, 1)
	{
		vec = glm::fvec3((float)(Mesh.GetVertices(i).x) / Mesh.GetVertices(i).z, (float)(Mesh.GetVertices(i).y) / Mesh.GetVertices(i).z, 1.0f);
		Mesh.SetVertices(vec, i);
	}

	glm::fvec3 trans_vec = glm::fvec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).y, 1);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// min x
		if (trans_vec.x > Mesh.GetVertices(i).x)
			trans_vec.x = Mesh.GetVertices(i).x;
		// min y
		if (trans_vec.y > Mesh.GetVertices(i).y)
			trans_vec.y = Mesh.GetVertices(i).y;
	}
	float min = trans_vec.x;
	if (trans_vec.y < min)
		min = trans_vec.y;
	if (trans_vec.z < min)
		min = trans_vec.z;
	if (min < 0)
	{
		min *= (-1.0f);
		trans_vec.x = min; trans_vec.y = min; trans_vec.z = min;
		Translate(Mesh, trans_vec);
	}
	/// 

	glm::fvec3 scale_vec = glm::vec3(Mesh.GetVertices(0).x, Mesh.GetVertices(0).x, 1);
	for (int i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		// max x
		if (scale_vec.x < Mesh.GetVertices(i).x)
			scale_vec.x = Mesh.GetVertices(i).x;
		// max y
		if (scale_vec.y < Mesh.GetVertices(i).y)
			scale_vec.y = Mesh.GetVertices(i).y;

	}
	float max = scale_vec.x;
	if (scale_vec.y > max)
		max = scale_vec.y;
	if (scale_vec.z > max)
		max = scale_vec.z;
	scale_vec.x = 600 / max; scale_vec.y = 600 / max; scale_vec.z = 600 / max;
	Scale(Mesh, scale_vec);
}

void Renderer::worldMat(MeshModel& Mesh)
{
	FixPoints(Mesh);

	//rotate;
	float radian = 0.0f * (M_PI / 180);
	float cs = cos(radian);
	float sn = sin(radian);
	float R[3][3] = {
			{cs, -1 * sn, 0},
			{sn, cs, 0},
			{0, 0, 1} };

	float inv_R[3][3] = {
			{cs, sn, 0},
			{-1 * sn, cs, 0},
			{0, 0, 1} };

	//translate:
	float T[3][3] = {
		{1, 0, 200.0f},
		{0, 1, 30.0f},
		{0, 0, 1} };

	float inv_T[3][3] = {
		{1, 0, -200.0f},
		{0, 1, -30.0f},
		{0, 0, 1} };

	//scale
	float S[3][3] = {
	   { 0.5f, 0, 0 },
	   { 0, 0.5f, 0 },
	   { 0, 0, 1} };

	float inv_S[3][3] = {
	   { 1 / 0.5f, 0, 0 },
	   { 0, 1 / 0.5f, 0 },
	   { 0, 0, 1} };

	// the world transformation matrix ( model matrix) is :
	// M= SRT
	// S = scale matrix, R = rotate matrix, T = translate matrix 
	float M[3][3], SR[3][3];
	// Multiplying scale matrix and the traslate matrix and putting the result in ST
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += S[i][k] * R[k][j];
			}
			SR[i][j] = sum;
			//std::cout << SR[i][j] << "  ";
		}
	}
	// Multiplying SR and teh rotatle matrix 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += SR[i][k] * T[k][j];
			}
			M[i][j] = sum;
			//std::cout << M[i][j] << "  ";
		}
		//std::cout << "\n";
	}

	/// inverse 
	float inv_M[3][3], invTR[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += inv_T[i][k] * inv_R[k][j];
			}
			invTR[i][j] = sum;
			//std::cout << SR[i][j] << "  ";
		}
	}
	// Multiplying INVERSE TR and teh rotatle matrix 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 3; k++) {
				sum += invTR[i][k] * inv_S[k][j];
			}
			inv_M[i][j] = sum;
			//std::cout << inv_M[i][j] << "  ";
		}
		//std::cout << "\n";
	}
	// Now we need to multiply M * (x, y, z)
	// each time we multipy one coordinate with M
	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * M[0][0] + Mesh.GetVertices(i).y * M[0][1] + M[0][2],
			Mesh.GetVertices(i).x * M[1][0] + Mesh.GetVertices(i).y * M[1][1] + M[1][2], 1), i);

	}


	///

	DrawTriangle(Mesh);


	for (auto i = 0; i < Mesh.RetVerticesSize(); i++)
	{
		Mesh.SetVertices(glm::fvec3(Mesh.GetVertices(i).x * inv_M[0][0] + Mesh.GetVertices(i).y * inv_M[0][1] + inv_M[0][2],
			Mesh.GetVertices(i).x * inv_M[1][0] + Mesh.GetVertices(i).y * inv_M[1][1] + M[1][2], 1), i);

	}


	///
	DrawTriangle(Mesh);

}

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