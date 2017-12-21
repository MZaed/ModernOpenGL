#pragma once
#include "renderer.h"

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	virtual ~IndexBuffer();

	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_count;}

private:
	GLuint m_renderID;
	GLuint m_count;
};

