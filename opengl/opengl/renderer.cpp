#include "renderer.h"
#include <iostream>




Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}




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