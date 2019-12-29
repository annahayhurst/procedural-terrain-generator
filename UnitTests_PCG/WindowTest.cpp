#include "stdafx.h"
#include "CppUnitTest.h"
//#include "Context.h"

#include "Window.h"
#include "Window.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Window class
	TEST_CLASS(WindowTest) {
	public:
		// Test default constructor
		TEST_METHOD(Window_DefaultConstructor) {
			Engine::Window window = Engine::Window();

			GLint width = 800, height = 600;
			Assert::AreEqual(width, window.getWidth());
			Assert::AreEqual(height, window.getHeight());
		}

		// Test parameter constructor
		TEST_METHOD(Window_Constructor) {
			GLint width = 1024, height = 768;
			std::string title = "Test";
			Engine::Window window = Engine::Window(width, height, title);

			Assert::AreEqual(width, window.getWidth());
			Assert::AreEqual(height, window.getHeight());
			Assert::AreEqual(title, window.getTitle());
		}
	};
}