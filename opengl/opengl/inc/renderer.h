#pragma once

#include <vertexarray.h>
#include <indexbuffer.h>
#include <shader.h>



class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const;

	void clear() const;


};

