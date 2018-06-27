#include "testclearcolor.h"
#include "renderer.h"
#include <glerrorcheck.h>
#include <imgui\imgui.h>


test::TestClearColor::TestClearColor()
	:m_clearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::onUpdate(float deltaTime)
{
}

void test::TestClearColor::onRender()
{
	GLCALL(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2],
		m_clearColor[3]));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::onImGuiRender()
{
	ImGui::ColorEdit4("clear color", m_clearColor);
}
