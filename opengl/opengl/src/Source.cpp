#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"


struct shaderProgramSourceType
{
	std::string vertexSource;
	std::string fragmentSource;
};

static shaderProgramSourceType ParseShader(std::string& filePath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("SHADER") != std::string::npos) {
			if (line.find("VERTEX") != std::string::npos) {
				shaderType = ShaderType::VERTEX;

			}
			else if (line.find("FRAGMENT") != std::string::npos) {
				shaderType = ShaderType::FRAGMENT;

			}
			else {
				//not expected to reach here
				shaderType = ShaderType::NONE;
			}

		}
		else {
			ss[(int)shaderType] << line << '\n';
		}
	}

	return{ ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}


static GLuint CompileShader(const std::string& source, GLenum type)
{
	GLuint shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);


	int result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(shaderID, length, &length, message);
		std::cout << "Failed to compile shader" << std::endl;
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader"
			<< std::endl;
	}

	return shaderID;
}


static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();

	GLuint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


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



	// 3+--------------------------------.2 
	//  |                              ,'|  
	//  |                           ,-`  |  
	//  |                         ,'     |  
	//  |                       .`       |  
	//  |                     .`         |  
	//  |                   ,'           |  
	//  |                ,-`             |  
	//  |              ,'                |  
	//  |            .`                  |  
	//  |          .`                    |  
	//  |        ,'                      |  
	//  |     ,-`                        |  
	//  |   ,'                           |  
	//  | .`                             |  
	// 0-`-------------------------------+1 



	
	//Vertex array object
	VertexArray va;	
	
	//Vertex Buffers
	//Buffer data info
	const unsigned int BUFFER_1_POSITION_INDEX = 0U;
	const unsigned int BUFFER_1_POSITION_STRIDE_BYES = 2U * sizeof(float);
	const unsigned int BUFFER_1_POSITION_SIZE = 2U;
	const void*	BUFFER_1_POSITION_OFFSET_POINTER = NULL;

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
	//Index Buffer Data info
	const unsigned int INDEX_BUFFER_1_SIZE = 6U;

	//Index Buffer Data
	unsigned int indexBufferData[INDEX_BUFFER_1_SIZE] = {
										0,	1,	2,
										2,	3,	0
	};


	IndexBuffer indexBuffer(indexBufferData, INDEX_BUFFER_1_SIZE);

	shaderProgramSourceType shaderSource = ParseShader((std::string)"res/shaders/basic.shader");

	GLuint program = CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
	glUseProgram(program);

	GLCALL(GLint locationColor = glGetUniformLocation(program, "u_color"));
	ASSERT(locationColor != -1);
	float colorRed = 0.01F;
	
	GLCALL(glUseProgram(0));
	GLCALL(glBindVertexArray(0));
	indexBuffer.UnBind();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		GLCALL(glUseProgram(program));
		GLCALL(glUniform4f(locationColor,  colorRed, 0.1F, 0.3F, 0));

		va.Bind();
		indexBuffer.Bind();

		GLCALL(glDrawElements(GL_TRIANGLES, INDEX_BUFFER_1_SIZE, GL_UNSIGNED_INT, nullptr));

		
		colorRed = colorRed + 0.00001F;
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	glDeleteProgram(program);

	
	return 0;
}