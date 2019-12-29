#include "stdafx.h"
#include "CppUnitTest.h"

#include "Mesh.h"
#include "Mesh.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Mesh class
	TEST_CLASS(MeshTest) {
	public:
		// Test default constructor
		TEST_METHOD(Mesh_DefaultConstructor) {
			Engine::Mesh* mesh = new Engine::Mesh(Engine::COLOURED);

			GLuint defaultVal = 0;
			Assert::AreEqual(mesh->getVAO(), defaultVal);
			Assert::AreEqual(mesh->getVBO(), defaultVal);
			Assert::AreEqual(mesh->getIBO(), defaultVal);
		}
	};
}