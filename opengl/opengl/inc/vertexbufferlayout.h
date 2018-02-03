#pragma once
#include <vector>
#include "glerrorcheck.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	char normalised;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch(type)
		{
		case GL_FLOAT: 
			return 4;
			
		case GL_UNSIGNED_INT:
			return 4;

		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout
{

public:
	VertexBufferLayout()
		:m_stride(0)
	{
	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Element.push_back({GL_FLOAT, count, GL_FALSE});
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Element.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Element.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}


	inline unsigned int GetStride() const { return m_stride; }
	inline const std::vector<VertexBufferElement> GetElements() const{ return m_Element; }
		 
private:
	std::vector<VertexBufferElement> m_Element;
	unsigned int m_stride;

};