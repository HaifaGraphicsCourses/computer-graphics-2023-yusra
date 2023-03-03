#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include "Camera.h"


using namespace std;



/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool LOCALtransformation_window = false;
bool WORLDtransformation_window = false;
bool CAMERA_Orthographic_window = false;
bool CAMERA_Perspective_window = false;
bool windows = false;
bool Viewing_window = false;
bool CAMERA_window = false;
bool Light = false;
int Width = 1280, Height = 720;
glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_m = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_a_m = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_d_m = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_s_m = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_l = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_a_l = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_d_l = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 color_s_l = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
static float s_x_o = 1.0f, s_y_o = 1.0f, s_z_o = 1.0f,
			t_x_o = 0.0f, t_y_o = 0.0f, t_z_o = 0.0f,
			r_x_o = 0.0f, r_y_o = 0.0f, r_z_o = 0.0f,
			s_x_w = 1.0f, s_y_w = 1.0f, s_z_w = 1.0f,
			t_x_w = 0.0f, t_y_w = 0.0f, t_z_w = 0.0f,
			r_x_w = 0.0f, r_y_w = 0.0f, r_z_w = 0.0f,
			Zf_o, Zn_o, height,
			t_x_c = 0.0f, t_y_c = 0.0f, t_z_c = 0.0f,
			r_x_c = 0.0f, r_y_c = 0.0f, r_z_c = 0.0f,
			Zn_p, Zf_p , fov, aspectRatio = 1200/800,
			eyeX = 0.0f, eyeY = 0.0f, eyeZ = 0.0f,
			atX = 0.0f, atY = 0.0f, atZ = 0.0f,
			upX = 0.0f, upY = 0.0f, upZ = 0.0f,
			x_l = 1.0f, y_l = 1.0f, z_l = 1.0f, 
			red = 1.0f, green = 1.0f, blue = 1.0f,
			ambient = 1.0f, specular = 1.0f, power = 1.0f;
/**
 * Function declarations
 */

double zoomFactor = 1;
int windowWidth = 1280;
int windowHeight = 720;
char* windowTitle = "OpenGL Demo";
glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
bool zoomChanged = false;

std::shared_ptr<Scene> scene;
ImGuiIO* imgui;
GLFWwindow* window;

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
bool Setup(int windowWidth, int windowHeight, const char* windowName);
void Cleanup(GLFWwindow* window);

static void GlfwErrorCallback(int error, const char* description);
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);

void StartFrame();

void glfw_OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

static void GlfwErrorCallback(int error, const char* description);
void RenderFrame(GLFWwindow* window, std::shared_ptr<Scene> scene, Renderer& renderer, ImGuiIO& io);

float GetAspectRatio();
void DrawImguiMenus();



/**
 * Function implementation
 */


int main(int argc, char** argv)
{

	if (!Setup(windowWidth, windowHeight, windowTitle))
	{
		std::cerr << "Setup failed" << std::endl;
		return -1;
	}

	scene = std::make_shared<Scene>();
	glm::vec3 eye = glm::vec3(0, 0, 10);
	glm::vec3 at = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	Camera camera = Camera(eye, at, up, GetAspectRatio());
	scene->AddCamera(camera);

	Renderer renderer;
	renderer.LoadShaders();
	renderer.LoadTextures();

	while (!glfwWindowShouldClose(window))
	{
		// Poll and process events
		glfwPollEvents();

		// Imgui stuff
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		DrawImguiMenus();
		ImGui::Render();
		//HandleImguiInput();

		// Clear the screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Render scene
		renderer.Render(scene);

		// Imgui stuff
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap front and back buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


//int main(int argc, char** argv)
//{
//	int windowWidth = 1280, windowHeight = 720;
//	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
//	if (!window)
//		return 1;
//
//	int frameBufferWidth, frameBufferHeight;
//	glfwMakeContextCurrent(window);
//	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
//
//	scene = std::make_shared<Scene>();
//	glm::vec3 eye = glm::vec3(0, 0, 10);
//	glm::vec3 at = glm::vec3(0, 0, 0);
//	glm::vec3 up = glm::vec3(0, 1, 0);
//	Camera camera = Camera(eye, at, up, GetAspectRatio());
//	scene->AddCamera(camera);
//
//	//scene->AddLight(std::make_shared<PointLight>(glm::vec3(0, 0, 15), glm::vec3(1, 1, 1)));
//	//scene->AddLight(std::make_shared<PointLight>(glm::vec3(0, 5, 5), glm::vec3(0, 0, 0)));
//	//scene->AddLight(std::make_shared<PointLight>(glm::vec3(-5, 0, 0), glm::vec3(0, 0, 0)));
//
//
//	Renderer renderer;
//	renderer.LoadShaders();
//	//renderer.LoadTextures();
//	ImGuiIO& io = SetupDearImgui(window);
//	glfwSetScrollCallback(window, ScrollCallback);
//
//	while (!glfwWindowShouldClose(window)) /////////
//	{
//		/*glfwPollEvents();
//		StartFrame();
//		glfwSetWindowSize(window, Width, Height);
//		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
//		DrawImguiMenus(io, scene);
//		RenderFrame(window, scene, renderer, io);*/
//		// Poll and process events
//		glfwPollEvents();
//
//		// Imgui stuff
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//		DrawImguiMenus();
//		//DrawImguiMenus(io, scene);
//		ImGui::Render();
//		//HandleImguiInput();
//
//		// Clear the screen and depth buffer
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// Render scene
//		renderer.Render(scene);
//
//		// Imgui stuff
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//		// Swap front and back buffers
//		glfwSwapBuffers(window);
//	}
//
//	Cleanup(window);
//	return 0;
//}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


bool Setup(int windowWidth, int windowHeight, const char* windowName)
{
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, windowName);
	if (!window)
	{
		std::cerr << "Window setup failed" << std::endl;
		return false;
	}

	imgui = &SetupDearImgui(window);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glEnable(GL_DEPTH_TEST);

	return true;
}


GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	// Intialize GLFW
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create an OpenGL 3.3 core, forward compatible context window
	window = glfwCreateWindow(windowWidth, windowHeight, window_name, NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(window);

	// Setup window events callbacks
	//glfwSetFramebufferSizeCallback(window, glfw_OnFramebufferSize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// An error occured
		std::cerr << "GLAD initialization failed" << std::endl;
		return false;
	}

	return window;

	//glfwSetErrorCallback(GlfwErrorCallback);
	//if (!glfwInit())
	//	return NULL;
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//
	//#if __APPLE__
	//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//#endif
	//
	//GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	//glfwMakeContextCurrent(window);
	//glfwSwapInterval(1); // Enable vsync
	//					 // very importent!! initialization of glad
	//					 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped
	//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	//return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	// Setup style
	ImGui::StyleColorsDark();

	glfwSetScrollCallback(window, glfw_OnMouseScroll);

	return io;
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void glfw_OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	zoomFactor = glm::pow(1.1, -yoffset);
	zoomChanged = true;
}

float GetAspectRatio()
{
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}
//void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
//{
//	ImGui::Render();
//	int frameBufferWidth, frameBufferHeight;
//	glfwMakeContextCurrent(window);
//	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
//	
//	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
//	{
//		// TODO: Set new aspect ratio
//		
//	}
//
//	if (!io.WantCaptureKeyboard)
//	{
//		// TODO: Handle keyboard events here
//		// we will use :
//		// W = +y traslate
//		// S = -y traslate
//		// A = -x traslate
//		// D = +x traslate
//		//
//		  
//		if (io.KeysDown[87]) // w = +y traslate
//		{
//			if (scene.GetModelCount() > 0)
//				scene.GetActiveModel().SetOBJTranslate(t_y_w++, 1);
//		}
//		if (io.KeysDown[83]) // S = -y traslate
//		{
//			if (scene.GetModelCount() > 0)
//				scene.GetActiveModel().SetOBJTranslate(t_y_w--, 1);
//		}
//		if (io.KeysDown[65]) // A = -x traslate
//		{
//			if (scene.GetModelCount() > 0)
//				scene.GetActiveModel().SetOBJTranslate(t_x_w--, 0);
//		}
//		if (io.KeysDown[68]) // D = +x traslate
//		{
//			if (scene.GetModelCount() > 0)
//				scene.GetActiveModel().SetOBJTranslate(t_x_w++, 0);
//		}
//	}
//
//	if (!io.WantCaptureMouse)
//	{
//		// TODO: Handle mouse events here
//		if (io.MouseDown[0])
//		{
//			// Left mouse button is down
//		}
//	}
//
//	renderer.ClearColorBuffer(clear_color);
//	renderer.Render(scene);
//	renderer.SwapBuffers();
//
//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//	glfwMakeContextCurrent(window);
//	glfwSwapBuffers(window);
//}



//void DrawImguiMenus(ImGuiIO& io, Scene& scene)
void DrawImguiMenus()

{
	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");
	
	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = "NULL";
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);

				if (result == NFD_OKAY)
				{
					//glm::vec3 modelColor;
					//if (ImGui::ColorEdit3("Model Color", (float*)&modelColor))
					//{
					//	scene->GetActiveModel()->SetColor(modelColor);
					//}
					scene->AddModel(Utils::LoadMeshModel(outPath));
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed
	
	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::Checkbox("OBJECT", &LOCALtransformation_window);
		//  --- SCALE & TRASLATE & Rotate ---  LOCAL
		if (LOCALtransformation_window)
		{

			ImGui::SliderFloat("LOCAL Scale X", &s_x_o, 1.0f, 5.0f);
			ImGui::SliderFloat("LOCAL Scale Y", &s_y_o, 1.0f, 5.0f);
			ImGui::SliderFloat("LOCAL Scale Z", &s_z_o, 1.0f, 5.0f);
			ImGui::SliderFloat("LOCAL Translate X", &t_x_o, -50.0f, 50.0f);
			ImGui::SliderFloat("LOCAL Translate Y", &t_y_o, -200.0f, 500.0f);
			ImGui::SliderFloat("LOCAL Translate Z", &t_z_o, -50.0f, 50.0f);
			ImGui::SliderFloat("LOCAL Rotate X", &r_x_o, 0.0f, 360.0f);
			ImGui::SliderFloat("LOCAL Rotate Y", &r_y_o, 0.0f, 360.0f);
			ImGui::SliderFloat("LOCAL Rotate Z", &r_z_o, 0.0f, 360.0f);

			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetOBJScale(s_x_o, 0);
				scene->GetActiveModel()->SetOBJScale(s_y_o, 1);
				scene->GetActiveModel()->SetOBJScale(s_z_o, 2);
				scene->GetActiveModel()->SetOBJTranslate(t_x_o, 0);
				scene->GetActiveModel()->SetOBJTranslate(t_y_o, 1);
				scene->GetActiveModel()->SetOBJTranslate(t_z_o, 2);
				scene->GetActiveModel()->SetOBJRotate_X(r_x_o);
				scene->GetActiveModel()->SetOBJRotate_Y(r_y_o);
				scene->GetActiveModel()->SetOBJRotate_Z(r_z_o);
			}
			//LOCALtransformation_window = false;
		}
		ImGui::Checkbox("WORLD", &WORLDtransformation_window);
		//  --- SCALE & TRASLATE & Rotate ---  WORLD
		if (WORLDtransformation_window)
		{

			ImGui::SliderFloat("WORLD Scale X", &s_x_w, 1.0f, 5.0f);
			ImGui::SliderFloat("WORLD Scale Y", &s_y_w, 1.0f, 5.0f);
			ImGui::SliderFloat("WORLD Scale Z", &s_z_w, 1.0f, 5.0f);
			ImGui::SliderFloat("WORLD Translate X", &t_x_w, -200.0f, 200.0f);
			ImGui::SliderFloat("WORLD Translate Y", &t_y_w, -200.0f, 200.0f);
			ImGui::SliderFloat("WORLD Translate Z", &t_z_w, -200.0f, 200.0f);
			ImGui::SliderFloat("WORLD Rotate X", &r_x_w, 0.0f, 360.0f);
			ImGui::SliderFloat("WORLD Rotate Y", &r_y_w, 0.0f, 360.0f);
			ImGui::SliderFloat("WORLD Rotate Z", &r_z_w, 0.0f, 360.0f);

			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetWORLDScale(s_x_w, 0);
				scene->GetActiveModel()->SetWORLDScale(s_y_w, 1);
				scene->GetActiveModel()->SetWORLDScale(s_z_w, 2);
				scene->GetActiveModel()->SetWORLDTranslate(t_x_w, 0);
				scene->GetActiveModel()->SetWORLDTranslate(t_y_w, 1);
				scene->GetActiveModel()->SetWORLDTranslate(t_z_w, 2);
				scene->GetActiveModel()->SetWORLDRotate_X(r_x_w);
				scene->GetActiveModel()->SetWORLDRotate_Y(r_y_w);
				scene->GetActiveModel()->SetWORLDRotate_Z(r_z_w);
			}

			//	WORLDtransformation_window = false;

		}
		ImGui::Checkbox("Camera", &CAMERA_window);
		//  --- SCALE & TRASLATE & Rotate ---  WORLD
		if (CAMERA_window)
		{
			ImGui::SliderFloat("CAMERA Translate X", &t_x_c, 0.0f, 100.0f);
			ImGui::SliderFloat("CAMERA Translate Y", &t_y_c, 0.0f, 100.0f);
			ImGui::SliderFloat("CAMERA Translate Z", &t_z_c, 0.0f, 100.0f);
			ImGui::SliderFloat("CAMERA Rotate X", &r_x_c, 0.0f, 360.0f);
			ImGui::SliderFloat("CAMERA Rotate Y", &r_y_c, 0.0f, 360.0f);
			ImGui::SliderFloat("CAMERA Rotate Z", &r_z_c, 0.0f, 360.0f);

			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetWORLDTranslate(t_x_c, 0);
				scene->GetActiveModel()->SetWORLDTranslate(t_y_c, 1);
				scene->GetActiveModel()->SetWORLDTranslate(t_z_c, 2);
				scene->GetActiveModel()->SetWORLDRotate_X(r_x_c);
				scene->GetActiveModel()->SetWORLDRotate_Y(r_y_c);
				scene->GetActiveModel()->SetWORLDRotate_Z(r_z_c);
			}

			//	WORLDtransformation_window = false;

		}

		ImGui::Checkbox("ORTHOGRAPHIC", &CAMERA_Orthographic_window);
		//  --- ORTHOGRAPHIC
		if (CAMERA_Orthographic_window)
		{
			ImGui::SliderFloat("Height", &height, 0.0f, M_PI);
			ImGui::SliderFloat("Near", &Zn_o, 1.0f, 10.0f);
			ImGui::SliderFloat("Far", &Zf_o, 1.0f, 10.0f);
			scene->GetActiveCamera().orth = true;
			scene->GetActiveCamera().pers = false;
			CAMERA_Perspective_window = false;
			scene->GetActiveCamera().SetOrthographicProjection(height, aspectRatio, Zn_o, Zf_o);

		}

		ImGui::Checkbox("PERSPECTIVE", &CAMERA_Perspective_window);
		//  --- PERSPECTIVE
		if (CAMERA_Perspective_window)
		{
			ImGui::SliderFloat("Fov", &fov, 0.0f, M_PI);
			ImGui::SliderFloat("Near", &Zn_p, 0.0f, 10.0f);
			ImGui::SliderFloat("Far", &Zf_p, 0.0f, 10.0f);
			scene->GetActiveCamera().pers= true;
			scene->GetActiveCamera().orth = false;
			CAMERA_Orthographic_window = false;
			scene->GetActiveCamera().SetPerspectiveProjection(fov, aspectRatio, Zn_p, Zf_p);
		}
		

		ImGui::Checkbox("WINDOWS", &windows);
		//  --- WINDOW
		if (windows)
		{
			ImGui::SliderInt("Height", &Height, 1, 3000);
			ImGui::SliderInt("Width", &Width, 1, 3000);


		}

		ImGui::Checkbox("LIGHT", &Light);
		//  --- Light
		if (Light)
		{
			ImGui::Text("Mesh RGB ");
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetColor(clear_color);
			}

			ImGui::Text("Mesh Ambient RGB");
			ImGui::ColorEdit3("color_a_m", (float*)&color_a_m);
			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetAmbientColor(color_a_m);
			}

			ImGui::Text("\nMesh Diffuse RGB");
			ImGui::ColorEdit3("color_d_m", (float*)&color_d_m);
			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetDiffuseColor(color_d_m);
			}

			ImGui::Text("Mesh Specular RGB");
			ImGui::ColorEdit3("color_s_m", (float*)&color_s_m);
			if (scene->GetModelCount() > 0)
			{
				scene->GetActiveModel()->SetSpecularColor(color_s_m);
			}

			ImGui::Text("Light Coordinate: ");
			ImGui::SliderFloat("X", &x_l, 0.0f, 1200.0f);
			ImGui::SliderFloat("Y", &y_l, 0.0f, 1200.0f);
			ImGui::SliderFloat("Z", &z_l, 0.0f, 1200.0f);
			scene->SetLightPosition(glm::vec3(x_l, y_l, z_l));
			ImGui::Text("Light RGB");
			ImGui::ColorEdit3("color_l", (float*)&color_l);
			scene->SetColor(color_l);
			
			ImGui::Text("\nAmbient");
			ImGui::SliderFloat("Ambient", &ambient, 0.0f, 1.0f);
			ImGui::Text("Ambient RGB");
			ImGui::ColorEdit3("color_a_l", (float*)&color_a_l);
			scene->SetAmbientColor(color_a_l);
			scene->SetAmbient(ambient);
			
			ImGui::Text("\nDiffuse RGB");
			ImGui::ColorEdit3("color_d_l", (float*)&color_d_l);
			scene->SetDiffuseColor(color_d_l);
			
			ImGui::Text("\nSpecular");
			ImGui::SliderFloat("", &specular,-2.0f, 1.0f);
			ImGui::Text("Specular RGB");
			ImGui::ColorEdit3("color_s_l", (float*)&color_s_l);
			ImGui::SliderFloat("Power\n", &power, 0.0f, 2.0f);
			scene->SetSpecularColor(color_s_l);
			scene->SetSpecular(specular);
			scene->SetPower(power);

		}

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	
		ImGui::End();
	}


}