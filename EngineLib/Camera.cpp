#include "Camera.h"
#include <iostream>

namespace Engine {
	// Constructor with parameters
	Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed) :
		position(position), worldUp(up), front(vec3(0.0f, 0.0f, -1.0f)),
		yaw(yaw), pitch(pitch),
		moveSpeed(moveSpeed), turnSpeed(turnSpeed) {
		calculateDirection();
	}

	// The view matrix translates our perspective from world-space to view-space
	glm::mat4 Camera::getViewMatrix() {
		// Eye position | center | up
		// position + front = the target, i.e. what we are looking at
		return glm::lookAt(position, position + front, up);
	}

	// Set the current camera position in the uniform found in the fragment shader
	void Camera::updateUniformPosition(Shader* s) {
		glUniform3f(s->getCameraPositionUL(), this->getPosition().x, this->getPosition().y, this->getPosition().z);
	}

	// Assign camera navigation to WASD/up-left-down-right. Makes use of dT to move at appropriate speed
	void Camera::keyControl(bool* keys, GLfloat dT) {
		// Speed of camera movement relative to change in time
		GLfloat velocity = moveSpeed * dT;

		if (keys[GLFW_KEY_W]) {
			position += front * velocity; // move relative to where the "front" of the camera faces
		}

		if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
			position -= front * velocity;
		}

		if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
			position -= right * velocity; // move relative to where the "right" of the camera is
		}

		if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
			position += right * velocity;
		}

		if (keys[GLFW_KEY_SPACE] || keys[GLFW_KEY_UP]) {
			position += vec3(0.f, 2.5f, 0.f) * velocity; // ascend vertically
		}

		if (keys[GLFW_KEY_DOWN]) {
			position -= vec3(0.f, 2.5f, 0.f) * velocity; // descend vertically
		}

		if (keys[GLFW_KEY_Q]) {
			std::cout << front.x << " " << front.y << " " << front.z << "\n";
		}
	}

	// Allow change of angle using mouse movement - depending on turn speed
	// Pitch and yaw are used to change camera directions
	void Camera::mouseControl(GLdouble dX, GLdouble dY) {
		dX *= turnSpeed;
		dY *= turnSpeed;
		yaw += (GLfloat)dX;
		pitch += (GLfloat)dY;

		// Restrict angles to <90 to avoid visual anomalies
		if (pitch >= 90.0f) {
			pitch = 89.0f;
		}
		else if (pitch <= -90.0f) {
			pitch = -89.0f;
		}

		calculateDirection();
	}

	// Update the front, right and up vectors using current angles
	void Camera::calculateDirection() {
		front.x = cos(radians(yaw)) * cos(radians(pitch));
		front.y = sin(radians(pitch)); // y direction doesn't depend on yaw
		front.z = sin(radians(yaw)) * cos(radians(pitch));
		front = glm::normalize(front); // create a unit vector from (x, y, z) to get current direction

		// The right is a cross product between front (just calculated) and the reference world up
		right = glm::normalize(glm::cross(front, worldUp));
		// The relative up direction is a cross product between right and front
		up = glm::normalize(glm::cross(right, front));

	}

}

