#include "test.h"

namespace test {

	Test::Test()
	{
	}


	Test::~Test()
	{
	}

	void TestMenu::onImGuiRender()
	{
		for (auto test : m_tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_currentTest = test.second();
			}
		}
	}
}