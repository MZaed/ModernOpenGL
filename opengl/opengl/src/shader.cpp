#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glerrorcheck.h>

#include "shader.h"


Shader::Shader(const std::string&  filePath)
	:m_filePath(filePath),
	m_rendererID(0)
{
	shaderProgramSourceType shaderSource = ParseShader(m_filePath);

	m_rendererID =   CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const
{
	GLCALL(glUseProgram(m_rendererID));
}

void Shader::UnBind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCALL(glUniform1i(GetUniformLocation(name), value));
}


int Shader::GetUniformLocation(const std::string & uniformName)
{
	GLCALL(int location = glGetUniformLocation(m_rendererID, uniformName.c_str()));
	
	if(-1 == location){
		std::cout << "Warning:: uniform" << "doesn't exist" << std::endl;
	}

	return location;
}

shaderProgramSourceType Shader::ParseShader(std::string& filePath)
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


unsigned int Shader::CompileShader(const std::string& source, GLenum type)
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


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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


