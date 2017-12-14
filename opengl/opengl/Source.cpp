#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x)	if(!(x)) __debugbreak();
#define GLCALL(x)	GLClearError();\
					x;\
					ASSERT(GLErrorLog(#x, __FILE__, __LINE__))

void GLClearError(void)
{
	while(glGetError() != GL_NO_ERROR){
		//do nothing
	}
}

bool GLErrorLog(char* functionName, char* file, int line)
{
	while(GLenum error = glGetError()){
		std::cout << "GL Error: [" << error << "]" << std::endl;
		std::cout << "Funcation Name: " << functionName << std::endl;
		std::cout << "File Name: " << file << " at Line no. '" << line << "'" << std::endl; 
		return false;
	}

	return true;
}

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



	//Vertex Buffers
	//Buffer ID's
	GLuint	buffer1 = 0;

	//Buffer Size
	const unsigned int BUFFER_1_SIZE = 8U;

	//Buffer data info
	const unsigned int BUFFER_1_POSITION_INDEX = 0U;
	const unsigned int BUFFER_1_POSITION_STRIDE_BYES = 2U * sizeof(float);
	const unsigned int BUFFER_1_POSITION_SIZE = 2U;
	const void*	BUFFER_1_POSITION_OFFSET_POINTER = NULL;


	//Buffer Data
	float	bufferData1[BUFFER_1_SIZE] = {
									-0.5f, -0.5f, //0
									 0.5f, -0.5f, //1
									 0.5f,  0.5f, //2
									-0.5f,  0.5f  //3
	};

	glGenBuffers(1, &buffer1);

	//Buffer linking and assigning data
	glBindBuffer(GL_ARRAY_BUFFER, buffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData1), bufferData1, GL_STATIC_DRAW);
	glVertexAttribPointer(BUFFER_1_POSITION_INDEX, BUFFER_1_POSITION_SIZE, GL_FLOAT, GL_FALSE,
		BUFFER_1_POSITION_STRIDE_BYES, BUFFER_1_POSITION_OFFSET_POINTER);
	glEnableVertexAttribArray(BUFFER_1_POSITION_INDEX);

	//Index Buffer
	GLuint index1 = 0;

	//Index Buffer Data info
	const unsigned int INDEX_BUFFER_1_SIZE = 6U;
	const unsigned int INDEX_BUFFER_1_INDEX = 0U;

	//Index Buffer Data
	unsigned int indexBufferData[INDEX_BUFFER_1_SIZE] = {
										0,	1,	2,
										2,	3,	0
	};

	glGenBuffers(1, &index1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferData), indexBufferData, GL_STATIC_DRAW);



	shaderProgramSourceType shaderSource = ParseShader((std::string)"res/shaders/basic.shader");

	GLuint program = CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
	glUseProgram(program);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		GLCALL(glDrawElements(GL_TRIANGLES, INDEX_BUFFER_1_SIZE, GL_UNSIGNED_INT, nullptr));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}