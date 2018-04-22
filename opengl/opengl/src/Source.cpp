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
	
	//Vertex array object
	VertexArray va;	
	
	float	bufferData1[] = {
									00.0f, 00.0f, 0.0f, 0.0f,//0
									00.0f, 100.0f, 0.0f, 1.0f,//1
									100.0f, 00.0f, 1.0f, 0.0f,//2
									100.0f, 100.0f, 1.0f, 1.0f //3
	};

	VertexBuffer vertexBuffer(bufferData1, sizeof(bufferData1));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vertexBuffer, layout);
	
	//Index Buffer
	const unsigned int INDEX_BUFFER_1_SIZE = 6U;

	//Index Buffer Data
	unsigned int indexBufferData[INDEX_BUFFER_1_SIZE] = {
										0,	1,	2,
										1,	2,	3
	};

	IndexBuffer indexBuffer(indexBufferData, INDEX_BUFFER_1_SIZE);

	Shader shader((std::string)"res/shaders/basic.shader");
	shader.Bind();

	glm::mat4 projection= glm::ortho(0.0f, 960.0f, 0.00f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));



	shader.SetUniform1i("u_texture", 0); 

	Texture2D texture2D((std::string)"res/textures/coolDarkWallpaper.png");
	texture2D.Bind();

	// Unbinding objects	
	shader.UnBind();
	va.UnBind();
	vertexBuffer.UnBind();
	indexBuffer.UnBind();

	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Renderer renderer;
	
	// Setup ImGui binding
    ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

	glm::vec3 translate(200.0f, 200.0f, 0.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.clear();
		ImGui_ImplGlfwGL3_NewFrame();

		shader.Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);
		glm::mat4 mvp = projection * view * model;
		shader.SetUniformMat4fv("u_MVP", mvp);
		ImGui::SliderFloat("Model: Translate along X", &translate.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Model: Translate along Y", &translate.y, 0.0f, 540.0f);
		
		renderer.Draw(va, indexBuffer, shader);
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