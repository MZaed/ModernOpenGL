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
#include "shader.h"




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
									-0.5f, -0.5f, //0
									 0.5f, -0.5f, //1
									 0.5f,  0.5f, //2
									-0.5f,  0.5f  //3
	};

	VertexBuffer vertexBuffer(bufferData1, sizeof(bufferData1));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vertexBuffer, layout);
	
	//Index Buffer
	const unsigned int INDEX_BUFFER_1_SIZE = 6U;

	//Index Buffer Data
	unsigned int indexBufferData[INDEX_BUFFER_1_SIZE] = {
										0,	1,	2,
										2,	3,	0
	};

	IndexBuffer indexBuffer(indexBufferData, INDEX_BUFFER_1_SIZE);

	Shader shader((std::string)"res/shaders/basic.shader");
	shader.Bind();
	
	float colorRed = 0.01F;

	// Unbinding objects	
	shader.UnBind();
	va.UnBind();
	vertexBuffer.UnBind();
	indexBuffer.UnBind();

	Renderer renderer;
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.clear();
		
		shader.Bind();
		shader.SetUniform4f("u_color", colorRed, 0.1F, 0.3F, 0);
		
		renderer.Draw(va, indexBuffer, shader);
		
		
		
		colorRed = colorRed + 0.00001F;
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	glfwTerminate();


	
	return 0;
}