#include "stdafx.h"
#include "CppUnitTest.h"

#include "Camera.h"
#include "Camera.cpp"


#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {

	// Tests concerning the Camera class
	TEST_CLASS(CameraTest) {	
	public:

		// Test constructor
		TEST_METHOD(Camera_Constructor) {
			makeCamera(vec3(0.0f, 0.0f, 0.0f));

			// Angle
			Assert::AreEqual(camera.getPitch(), 90.0f);
			Assert::AreEqual(camera.getYaw(), 0.0f);

			// Speed
			Assert::AreEqual(camera.getMovementSpeed(), 1.0f);
			Assert::AreEqual(camera.getTurnSpeed(), 1.5f);

			// Position
			Assert::AreEqual(camera.getPosition().x, 0.0f);
			Assert::AreEqual(camera.getPosition().y, 0.0f);
			Assert::AreEqual(camera.getPosition().z, 0.0f);
		}

		// Test that direction is calculated, and normalised correctly
		TEST_METHOD(Camera_Direction) {
			vec3 pos = generateRandomVector();
			makeCamera(pos);

			// Normalised direction is in range [0, 1]
			Assert::AreEqual(camera.getDirection().x, 0.0f, 1.0f);
			Assert::AreEqual(camera.getDirection().y, 0.0f, 1.0f);
			Assert::AreEqual(camera.getDirection().z, 0.0f, 1.0f);
		}

		// Test that correct view matrix is calculated
		TEST_METHOD(Camera_ViewMatrix) {
			vec3 pos = generateRandomVector();
			makeCamera(pos);

			vec3 up(0.0f, 1.0f, 0.0f), front(0.0f, 0.0f, -1.0f);
			glm::mat4 result = glm::lookAt(pos, pos + front, up);

			Assert::AreEqual(camera.getViewMatrix()[1][0], result[1][0]);
		}

		// Test that key input can change position of the camera
		TEST_METHOD(Camera_UpdatePosition) {
			vec3 pos = generateRandomVector();
			makeCamera(pos);

			bool keys[1024] = { false };
			int w = (int)(GLFW_KEY_W);
			keys[w] = true; // GLFW_KEY_W -> forward -> move on x axis

			camera.keyControl(keys, 200.0f);

			Assert::AreNotEqual(camera.getPosition().x, pos.x);
		}

		// Test that mouse input can change the direction of the camera
		TEST_METHOD(Camera_UpdateDirection) {
			vec3 pos = generateRandomVector();
			makeCamera(pos);

			vec3 direction = camera.getDirection();

			camera.mouseControl(7.5f, 5.0f);

			Assert::AreNotEqual(camera.getDirection().x, direction.x);
			Assert::AreNotEqual(camera.getDirection().y, direction.y);
			Assert::AreNotEqual(camera.getDirection().z, direction.z);
		}

	private:
		Engine::Shader* testShader;
		Engine::Camera camera;

		void makeCamera(vec3 position) {
			vec3 up(0.0f, 1.0f, 0.0f);
			GLfloat yaw = 0.0f, pitch = 90.0f;
			GLfloat moveSpeed = 1.0f, turnSpeed = 1.5f;
			
			camera = Engine::Camera(position, up, yaw, pitch, moveSpeed, turnSpeed);
		}

		vec3 generateRandomVector() {
			srand((unsigned int)time(0));
			float x = (float)((rand() % 10) + 1); // ensure all values above 0
			float y = x + 1.5f;
			float z = y + 1.5f;

			return vec3(x, y, z);
		}
	};
}