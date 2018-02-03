#pragma once

// Forward Declarations
class VertexBuffer;
class VertexBufferLayout;


  
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

