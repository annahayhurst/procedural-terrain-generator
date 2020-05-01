#pragma once

/*
* Camera
* Allows creation of a camera which can be controlled by the user. Speed of movement 
* depends on delta time (dT), and the speed of rotation depends on mouse movement speed.
*/

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"

using glm::radians;
using glm::vec3;
using std::vector;

namespace Engine {
	class Camera {
	public:
		Camera() {};
		Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

		vec3 getPosition() { return position; };
		vec3 getDirection() { return front; };
		glm::mat4 getViewMatrix();

		GLfloat getYaw() { return yaw; };
		GLfloat getPitch() { return pitch; };
		GLfloat getMovementSpeed() { return moveSpeed; };
		GLfloat getTurnSpeed() { return turnSpeed; };

		void setMovementSpeed(GLfloat moveSpeed) { this->moveSpeed = moveSpeed; };
		void setTurnSpeed(GLfloat turnSpeed) { this->turnSpeed = turnSpeed; };
		void setPosition(vec3 position) { this->position = position; };
		void setYaw(GLfloat yaw) { 
			this->yaw = yaw; 
			calculateDirection(); 
		};
		void setPitch(GLfloat pitch) { 
			this->pitch = pitch;
			calculateDirection();
		};

		void updateUniformPosition(Shader* shader);

		void keyControl(bool* keys, GLfloat dT);
		void mouseControl(GLdouble dX, GLdouble dY);

		~Camera() {};

	private:
		vec3 position, up, worldUp, front, right;

		GLfloat yaw, pitch;
		GLfloat moveSpeed, turnSpeed;

		void calculateDirection();
	};

}
