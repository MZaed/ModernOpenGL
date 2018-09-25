#include "testtexture2D.h"
#include "renderer.h"
#include <glerrorcheck.h>
#include <imgui\imgui.h>
#include <glerrorcheck.h>
#include <texture2D.h>
#include <ext\stb_image.h>
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <vertexbuffer.h>
#include <vertexarray.h>
#include <vertexbufferlayout.h>
#include <indexbuffer.h>
#include <renderer.h>
#include <memory>


test::TestTexture2D::TestTexture2D()
	:	m_translationA(200, 200, 0),
		m_translationB(400, 200, 0),
		m_proj(glm::ortho(0.0F, 960.00F, 0.0F, 540.0F, -1.0F, 1.0F)),
		m_view(glm::translate(glm::mat4(1.0F), glm::vec3(0, 0, 0)))
{

	float position[] = 
	{
		-50.0f,  -50.0f, 0.0f, 0.0f,//0
		 50.0f,  -50.0f, 1.0f, 0.0f,//1
		 50.0f,   50.0f, 1.0f, 1.0f,//2
		-50.0f,   50.0f, 0.0f, 1.0f //32
	};

 	unsigned int indices[] = 
	{
 		0,	1,	2,
 		2,	3,	0
 	};

	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ));

	m_shader = std::make_unique<Shader>((std::string)"res/shaders/basic.shader");
	m_VAO = std::make_unique<VertexArray>();
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_vertexBuffer = std::make_unique<VertexBuffer>(position, sizeof(position));
	VertexBufferLayout layout;

	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VAO->AddBuffer(*m_vertexBuffer, layout);


	m_shader->Bind();
	m_shader->SetUniform1i("u_texture", 0);  
	m_texture2D = std::make_unique<Texture2D>(((std::string)"res/textures/coolDarkWallpaper.png"));
	
	float colorRed = 0.01F;

}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::onUpdate(float deltaTime)
{
}

void test::TestTexture2D::onRender()
{
	GLCALL(glClearColor(0.0F, 0.0F, 0.0F, 1.0F));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;

	m_texture2D->Bind();

		//Render Model A
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->SetUniformMat4fv("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
		//Render Model B
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->SetUniformMat4fv("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void test::TestTexture2D::onImGuiRender()
{
	ImGui::SliderFloat3("ModelA: Translate ", &m_translationA.x, 0.0f, 960.0f);
	ImGui::SliderFloat3("ModelB: Translate ", &m_translationB.x, 0.0f, 960.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
