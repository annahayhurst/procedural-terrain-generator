#include "stdafx.h"
#include "CppUnitTest.h"

#include "Material.h"
#include "Material.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Material class
	TEST_CLASS(MaterialTest) {
	public:
		// Test default constructor
		TEST_METHOD(Material_DefaultConstructor) {
			Engine::Material mat = Engine::Material();
			
			GLfloat spec = 0.5f;
			Assert::AreEqual(mat.getSpecularIntensity(), spec);
			
			GLuint shininess = 32;
			Assert::AreEqual(mat.getShininess(), shininess);

		}

		TEST_METHOD(Material_Constructor) {
			GLfloat spec = 0.75f;
			GLuint shininess = 64;

			Engine::Material mat = Engine::Material(spec, shininess);

			Assert::AreEqual(mat.getSpecularIntensity(), spec);
			Assert::AreEqual(mat.getShininess(), shininess);

		}

	private:
		
	};
}