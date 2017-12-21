#pragma once

#include <GL/glew.h>

#define ASSERT(x)	if(!(x)) __debugbreak();
#define GLCALL(x)	GLClearError();\
					x;\
					ASSERT(GLErrorLog(#x, __FILE__, __LINE__))

void GLClearError(void);
bool GLErrorLog(char* functionName, char* file, int line);

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void GLClearError(void);
	bool GLErrorLog(char* functionName, char* file, int line);
};

