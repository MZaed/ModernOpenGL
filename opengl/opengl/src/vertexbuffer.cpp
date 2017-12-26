#include "vertexbuffer.h"



VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	glGenBuffers(1, &m_renderID);

	//Buffer linking and assigning data
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_renderID));
}

void VertexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderID));
}

void VertexBuffer::UnBind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0 ));
}
