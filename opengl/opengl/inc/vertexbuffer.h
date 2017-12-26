#pragma once
#include "renderer.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	virtual ~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	GLuint m_renderID;
};

