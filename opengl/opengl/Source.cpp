#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


static GLuint CompileShader(const std::string& source, GLenum type)
{
	GLuint shaderID	= glCreateShader(type);
	const char* src	= source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	
	int result = 0; 
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
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
	GLuint program	= glCreateProgram();
	
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

	if(GLEW_OK != glewInit()){
		std::cout << "Error:: glewInit failed" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Buffer ID's
	GLuint	bufferID1 = 0;

	//Buffer Size
	const unsigned int BUFFER_1_SIZE	= 6U;

	//Buffer data info
	const unsigned int BUFFER_1_POSITION_INDEX		= 0U;
	const unsigned int BUFFER_1_POSITION_STRIDE_BYES= 2U * sizeof(float);
	const unsigned int BUFFER_1_POSITION_SIZE		= 2U;
	const void*	BUFFER_1_POSITION_OFFSET_POINTER	= NULL;


	//Buffer Data
	float	bufferData1[BUFFER_1_SIZE] =	{
									-0.5f, -0.5f,
									0.0f, 0.5f,
									0.5f, -0.5f
								};	

	glGenBuffers(1, &bufferID1);

	//Buffer linking and assigning data
	glBindBuffer(GL_ARRAY_BUFFER, bufferID1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData1), bufferData1, GL_STATIC_DRAW);
	glVertexAttribPointer(BUFFER_1_POSITION_INDEX, BUFFER_1_POSITION_SIZE, GL_FLOAT, GL_FALSE,
		BUFFER_1_POSITION_STRIDE_BYES, BUFFER_1_POSITION_OFFSET_POINTER);
	glEnableVertexAttribArray(BUFFER_1_POSITION_INDEX);

	std::string vertexShader = 
		"#version 330 core\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position  = position;\n"
		"}\n";


	std::string fragmentShader = 
		"#version 330 core\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"void main()\n"
		"{\n"
		"	color  = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";
		

	GLuint program = CreateShader(vertexShader, fragmentShader);
	glUseProgram(program);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, BUFFER_1_SIZE/2);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}