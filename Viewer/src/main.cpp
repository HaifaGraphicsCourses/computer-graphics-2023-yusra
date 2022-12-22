#define _USE_MATH_DEFINES
#include <cmath>
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

using namespace std;

/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool LOCALtransformation_window = false;
bool WORLDtransformation_window = false;
glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
static float s_x_o = 1.0f, s_y_o = 1.0f, s_z_o = 1.0f, 
			t_x_o = 0.0f, t_y_o = 0.0f, t_z_o = 0.0f, 
			r_x_o = 0.0f, r_y_o = 0.0f, r_z_o = 0.0f,
			s_x_w = 1.0f, s_y_w = 1.0f, s_z_w = 1.0f, 
			t_x_w = 0.0f, t_y_w = 0.0f, t_z_w = 0.0f, 
			r_x_w = 0.0f, r_y_w = 0.0f, r_z_w = 0.0f;



/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char **argv)
{
	int windowWidth = 1280, windowHeight = 720;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
	Scene scene = Scene();
	
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene);
		RenderFrame(window, scene, renderer, io);
    }

	Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
		
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		// we will use :
		// W = +y traslate
		// S = -y traslate
		// A = -x traslate
		// D = +x traslate
		//
		  
		if (io.KeysDown[87]) // w = +y traslate
		{
			if (scene.GetModelCount() > 0)
				scene.GetActiveModel().SetOBJTranslate(t_y_w++, 1);
		}
		if (io.KeysDown[83]) // S = -y traslate
		{
			if (scene.GetModelCount() > 0)
				scene.GetActiveModel().SetOBJTranslate(t_y_w--, 1);
		}
		if (io.KeysDown[65]) // A = -x traslate
		{
			if (scene.GetModelCount() > 0)
				scene.GetActiveModel().SetOBJTranslate(t_x_w--, 0);
		}
		if (io.KeysDown[68]) // D = +x traslate
		{
			if (scene.GetModelCount() > 0)
				scene.GetActiveModel().SetOBJTranslate(t_x_w++, 0);
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	renderer.SwapBuffers();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
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
					scene.AddModel(Utils::LoadMeshModel(outPath));
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

			ImGui::SliderFloat("LOCAL Scale X", &s_x_o, 1.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Scale Y", &s_y_o, 1.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Scale Z", &s_z_o, 1.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Translate X", &t_x_o, 0.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Translate Y", &t_y_o, 0.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Translate Z", &t_z_o, 0.0f, 100.0f);
			ImGui::SliderFloat("LOCAL Rotate X", &r_x_o, 0.0f, 360.0f);
			ImGui::SliderFloat("LOCAL Rotate Y", &r_y_o, 0.0f, 360.0f);
			ImGui::SliderFloat("LOCAL Rotate Z", &r_z_o, 0.0f, 360.0f);

			if (scene.GetModelCount() > 0)
			{
				scene.GetActiveModel().SetOBJScale(s_x_o, 0);
				scene.GetActiveModel().SetOBJScale(s_y_o, 1);
				scene.GetActiveModel().SetOBJScale(s_z_o, 2);
				scene.GetActiveModel().SetOBJTranslate(t_x_o, 0);
				scene.GetActiveModel().SetOBJTranslate(t_x_o, 0);
				scene.GetActiveModel().SetOBJTranslate(t_y_o, 1);
				scene.GetActiveModel().SetOBJTranslate(t_z_o, 2);
				scene.GetActiveModel().SetOBJRotate_X(r_x_o);
				scene.GetActiveModel().SetOBJRotate_Y(r_y_o);
				scene.GetActiveModel().SetOBJRotate_Z(r_z_o);
			}
			//LOCALtransformation_window = false;
		}
		ImGui::Checkbox("WORLD", &WORLDtransformation_window);
		//  --- SCALE & TRASLATE & Rotate ---  WORLD
		if (WORLDtransformation_window)
		{

			ImGui::SliderFloat("WORLD Scale X", &s_x_w, 1.0f, 100.0f);
			ImGui::SliderFloat("WORLD Scale Y", &s_y_w, 1.0f, 100.0f);
			ImGui::SliderFloat("WORLD Scale Z", &s_z_w, 1.0f, 100.0f);
			ImGui::SliderFloat("WORLD Translate X", &t_x_w, 0.0f, 100.0f);
			ImGui::SliderFloat("WORLD Translate Y", &t_y_w, 0.0f, 100.0f);
			ImGui::SliderFloat("WORLD Translate Z", &t_z_w, 0.0f, 100.0f);
			ImGui::SliderFloat("WORLD Rotate X", &r_x_w, 0.0f, 360.0f);
			ImGui::SliderFloat("WORLD Rotate Y", &r_y_w, 0.0f, 360.0f);
			ImGui::SliderFloat("WORLD Rotate Z", &r_z_w, 0.0f, 360.0f);

			if (scene.GetModelCount() > 0)
			{
				scene.GetActiveModel().SetWORLDScale(s_x_w, 0);
				scene.GetActiveModel().SetWORLDScale(s_y_w, 1);
				scene.GetActiveModel().SetWORLDScale(s_z_w, 2);
				scene.GetActiveModel().SetWORLDTranslate(t_x_w, 0);
				scene.GetActiveModel().SetWORLDTranslate(t_y_w, 1);
				scene.GetActiveModel().SetWORLDTranslate(t_z_w, 2);
				scene.GetActiveModel().SetWORLDRotate_X(r_x_w);
				scene.GetActiveModel().SetWORLDRotate_Y(r_y_w);
				scene.GetActiveModel().SetWORLDRotate_Z(r_z_w);
			}

			//	WORLDtransformation_window = false;

		}

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		
		
		
		
		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	/*if (LOCALtransformation_window)
		ImGui::ShowDemoWindow(&LOCALtransformation_window);

	//  --- SCALE & TRASLATE & Rotate ---  LOCAL
	{
		//static float s_x = 1.0f, s_y = 1.0f, s_z = 1.0f, t_x = 0.0f, t_y = 0.0f, t_z = 0.0f, r_x = 0.0f, r_y = 0.0f, r_z = 0.0f;

		ImGui::Begin("LOCAL TRANSFORMATION");                          // Create a window called "Hello, world!" and append into it.

		ImGui::SliderFloat("Scale X", &s_x, 1.0f, 100.0f); 
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJScale(s_x, 0);
		ImGui::SliderFloat("Scale Y", &s_y, 1.0f, 100.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJScale(s_y, 1);
		ImGui::SliderFloat("Scale Z", &s_z, 1.0f, 100.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJScale(s_z, 2);
		
		ImGui::SliderFloat("Translate X", &t_x, 0.0f, 100.0f);  
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJTranslate(t_x, 0);
		ImGui::SliderFloat("Translate Y", &t_y, 0.0f, 100.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJTranslate(t_y, 1);
		ImGui::SliderFloat("Translate Z", &t_z, 0.0f, 100.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJTranslate(t_z, 2);
		
		ImGui::SliderFloat("Rotate X", &r_x, 0.0f, 360.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJRotate_X(r_x);
		ImGui::SliderFloat("Rotate Y", &r_y, 0.0f, 360.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJRotate_Y(r_y);
		ImGui::SliderFloat("Rotate Z", &r_z, 0.0f, 360.0f);
		if (scene.GetModelCount() > 0)
			scene.GetActiveModel().SetOBJRotate_Z(r_z);
		LOCALtransformation_window = false;
		ImGui::End();
	}*/

	//if (WORLDtransformation_window)
	//	ImGui::ShowDemoWindow(&WORLDtransformation_window);

	////  --- SCALE & TRASLATE & Rotate ---  WORLD
	//{
	//	static float s_x = 1.0f, s_y = 1.0f, s_z = 1.0f, t_x = 0.0f, t_y = 0.0f, t_z = 0.0f, r_x = 0.0f, r_y = 0.0f, r_z = 0.0f;

	//	//ImGui::Begin("WORLD TRANSFORMATION");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::SliderFloat("Scale X", &s_x, 1.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDScale(s_x,0);
	//	ImGui::SliderFloat("Scale Y", &s_y, 1.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDScale(s_y,1);
	//	ImGui::SliderFloat("Scale Z", &s_z, 1.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDScale(s_z, 2);

	//	ImGui::SliderFloat("Translate X", &t_x, 0.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDTranslate(t_x,0);
	//	ImGui::SliderFloat("Translate Y", &t_y, 0.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDTranslate(t_y, 1);
	//	ImGui::SliderFloat("Translate Z", &t_z, 0.0f, 100.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDTranslate(t_z, 2);

	//	ImGui::SliderFloat("Rotate X", &r_x, 0.0f, 360.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDRotate_X(r_x);
	//	ImGui::SliderFloat("Rotate Y", &r_y, 0.0f, 360.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDRotate_Y(r_y);
	//	ImGui::SliderFloat("Rotate Z", &r_z, 0.0f, 360.0f);
	//	if (scene.GetModelCount() > 0)
	//		scene.GetActiveModel().SetWORLDRotate_Z(r_z);
	//	WORLDtransformation_window = false;
	//	//ImGui::End();
	//}
}