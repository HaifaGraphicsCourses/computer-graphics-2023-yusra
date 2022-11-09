#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

#include "Renderer.h"
#include "InitShader.h"

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


void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	double x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = x1 - x0,
		dy = y1 - y0,
		D = 2 * dy - dx,
		x = x0,
		y = y0,
		yi = 1,
		xi = 1, m, val = 0;
	if (dx == 0) m = 200;
	else { m = dy / dx; };
	/*if (dy < 0) {
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

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	x = x0;
	for (int y = y0; y <= x1; y++)
	{
		PutPixel(x, y, color);
		if (D > 0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else
			D = D + 2 * dx;
	}*/
	if (m<1 && m > -1)
	{
		
		if (dx > 0)
		{
			val = 1; ////////////////////////////////////
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
		else {
			val = 2; ////////////////////////////////////
			if (dy > 0)
			{
				if (dx < 0)
				{
					xi = -1;
					dx = -dx;
				}
				D = (2 * dx) - dy;
				x = x0;
				for (int y = y0; y <= x1; y++)
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
	}
	

	//////////
	else if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
		{
			val = 3; ////////////////////////////////////
			dx = x0 - x1;
			dy = y0 - y1;
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
		else
		{
			val = 4; ////////////////////////////////////
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
		if (y0 > y1)
		{
			val = 5; ////////////////////////////////////
			dx = x0 - x1;
			dy = y0 - y1;
			xi = 1;
			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			D = (2 * dx) - dy;
			x = x0;
			for (int y = y0; y <= x1; y++)
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
		else
		{
			val = 6; ////////////////////////////////////
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
			for (int y = y0; y <= x1; y++)
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
	if (val == 0)
	{
		val = -1;
	}
	
					
	
					
	


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

void Renderer::Render(const Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width / 2;
	int half_height = viewport_height / 2;
	/*glm::ivec2 p1 = glm::ivec2(0.0f, 00.0f);
	glm::ivec2 p2 = glm::ivec2(100.0f, 50000.0f);
	glm::ivec2 p3 = glm::ivec2(500.0f, 8000.0f);
	glm::vec3 color = glm::vec3(10.0f, 0.0f, 0.0f);
	DrawLine(p1, p2, color);
	DrawLine(p2, p3, color);*/
	 glm::ivec2 p1 = glm::ivec2(500.0f, 500.0f);
	int x0 = p1.x, y0 = p1.y;
	glm::vec3 color = glm::vec3(10.0f, 0.0f, 0.0f);
	glm::ivec2 p2, p3, p4,p5,p11;
	int a = 360, r = 200;
	
	for (int i = 0; i < 360; i++)
	{
		p2 = glm::ivec2(x0 + r * sin(2 * M_PI * i / a), y0 + r * cos(2 * M_PI * i / a));
		//DrawLine(p1, p2, color);
		DrawLine(p2, p1, color);
	}

	// draw circle

}

int Renderer::GetViewportWidth() const
{
	return viewport_width;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height;
}