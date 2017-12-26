#pragma once
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"


  
class VertexArray
{
public:
	VertexArray();
	virtual ~VertexArray();


	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;

private:
	 
	unsigned int m_renderID;


};

