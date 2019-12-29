#include "stdafx.h"
#include "CppUnitTest.h"
#include "Context.h"

#include "Light.h"
#include "Light.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Light class and its subclasses
	TEST_CLASS(LightTest) {
		public:

		// Test default constructor
		TEST_METHOD(Light_DefaultConstructor) {
			//Context c = Context();
			
			Engine::Light light = Engine::Light();

			glm::vec3 whiteLight = light.getColour();
			float r = whiteLight.x;
			float g = whiteLight.y;
			float b = whiteLight.z;
			/*Assert::AreEqual(r, 1.0f);
			Assert::AreEqual(g, 1.0f);
			Assert::AreEqual(b, 1.0f);

			GLfloat intensity = 0.5f;*/
			//Assert::AreEqual(light.getAmbientIntensity(), intensity);
			
		}

	private:

	};
}