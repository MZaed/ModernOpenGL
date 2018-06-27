#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


#include "renderer.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "glerrorcheck.h"
#include "texture2D.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "test/test.h"
#include "test/testclearcolor.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Setting opengl version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit()) {
		std::cout << "Error:: glewInit failed" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
	// Setup ImGui binding
    ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

	test::TestClearColor test;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		ImGui_ImplGlfwGL3_NewFrame();

		test.onUpdate(0.0f);
		test.onRender();
		test.onImGuiRender();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
	glfwTerminate();


	
	return 0;
}