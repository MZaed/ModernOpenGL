#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "glerrorcheck.h"



VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_renderID));
}


VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_renderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();

	unsigned int offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++){

	const auto& element = elements[i];
	GLCALL(glEnableVertexAttribArray(i));
	GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset));

	offset += element.count * VertexBufferElement::GetSizeOfType(element.type); 
	
	}
}

void VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_renderID));
}

void VertexArray::UnBind() const
{
	GLCALL(glBindVertexArray(0));
}
