#pragma once
#include <iostream>
#include <GL/glew.h>

struct shaderProgramSourceType
{
	std::string vertexSource;
	std::string fragmentSource;
};


class Shader
{
public:
	Shader(const std::string& fileName);
	~Shader();

	void Bind() const;
	void UnBind() const;


	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniform1i(const std::string& name, int value);



private:

	unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	shaderProgramSourceType ParseShader(std::string& filePath);

	unsigned int CompileShader(const std::string & source, GLenum type);

	int GetUniformLocation(const std::string& uniformName);
	unsigned int m_rendererID;
	std::string m_filePath;


};