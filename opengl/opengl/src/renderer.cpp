#include <GL/glew.h>
#include <glerrorcheck.h>

#include "renderer.h"





Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	// Binding objects
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}




