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
#include "test/testtexture2D.h"


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
	window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
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

	Renderer renderer;
		
	// Setup ImGui binding
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->registerTest<test::TestClearColor>("Clear color");
	testMenu->registerTest<test::TestTexture2D>("Texture 2D");


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		renderer.clear();

		/* Render here */
		ImGui_ImplGlfwGL3_NewFrame();

		if (currentTest)
		{
			currentTest->onUpdate(0.0f);
			currentTest->onRender();
			ImGui::Begin("Test", NULL, ImGuiWindowFlags_AlwaysAutoResize);

			if ((currentTest != testMenu) && (ImGui::Button("<-")))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			
			currentTest->onImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	if (currentTest != testMenu)
	{
		delete testMenu;
	}

	delete currentTest;

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}