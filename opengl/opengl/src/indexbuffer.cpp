#include <GL/glew.h>
#include <glerrorcheck.h>
#include "indexbuffer.h"




IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_count(count)
{
	glGenBuffers(1, &m_renderID);

	//Buffer linking and assigning data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_renderID));
}

void IndexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID));
}

void IndexBuffer::UnBind() const 
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 ));
}

