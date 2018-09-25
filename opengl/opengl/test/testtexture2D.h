#pragma once

#include "test.h"
#include "glm/glm.hpp"
#include <shader.h>
#include <texture2D.h>
#include <memory>
#include <vertexarray.h>
#include <vertexBuffer.h>
#include <indexbuffer.h>

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		glm::mat4 m_proj;
		glm::mat4 m_view;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture2D> m_texture2D;

	};


}