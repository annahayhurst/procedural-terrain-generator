#include "stdafx.h"
#include "CppUnitTest.h"

#include "Shader.h"
#include "Shader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Shader class
	TEST_CLASS(ShaderTest) {
	public:
		// Test default constructor
		TEST_METHOD(Shader_DefaultConstructor) {
			Engine::Shader* shader = new Engine::Shader();
			Assert::IsNotNull(shader);

			GLuint id = 0;
			Assert::AreEqual(shader->getID(), id);
			shader = nullptr;
		}
	};
}