#define STB_IMAGE_IMPLEMENTATION
#include "stdafx.h"
#include "CppUnitTest.h"

#include "Texture.h"
#include "Texture.cpp"

#include "stb_image.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Texture class
	TEST_CLASS(TextureTest) {
	public:
		TEST_METHOD(Texture_DefaultConstructor) {
			Engine::Texture tex = Engine::Texture();
			GLuint defaultVal = 0;

			Assert::AreEqual(tex.getID(), defaultVal);
			Assert::AreEqual(tex.getHeight(), defaultVal);
			Assert::AreEqual(tex.getWidth(), defaultVal);
		}

		TEST_METHOD(Texture_LoadJPG) {
			Engine::Texture tex = Engine::Texture();
			GLuint defaultVal = 0;

			//tex.genTextureFromJPG("../Main_PCG/textures/marble.jpg");
			//Assert::AreNotEqual(tex.getHeight(), defaultVal);
		}
	};
}