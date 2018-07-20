#pragma once

#include <vector>
#include <functional>
#include "imgui/imgui.h"

namespace test {
	class Test
	{
	public:
		Test();
		virtual ~Test();

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};


	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer):m_currentTest(currentTestPointer){}
		
		virtual void onUpdate(float deltaTime) {}
		virtual void onImGuiRender();
	
		template<typename T>
		void registerTest(const std::string& name)
		{
			std::cout << "Registering tests: " << name << std::endl;
			m_tests.push_back(std::make_pair(name, [](){ return new T(); }));
		}

	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
	};
}

