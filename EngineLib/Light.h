#pragma once

/*
* Light
* Handles the creation of ambient light levels within the drawn scene.
* Works with shader uniforms to retrieve calculated light intensities.
* A base class for other specific type(s) of light used.
*/

#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <vector>
#include "Shader.h"

using glm::vec3;
using std::vector;

namespace Engine {
	class Light {
	public:
		Light();
		Light(vec3 colour, GLfloat ambientIntensity);

		virtual void useLight(Shader* shader); // this is overridden by other type(s) of light

		vec3 getColour() { return colour; };
		GLfloat getAmbientIntensity() { return ambientIntensity; };

		void setColour(vec3 colour) { this->colour = colour; };
		void setAmbientIntensity(GLfloat ambientIntensity) { this->ambientIntensity = ambientIntensity; };

		~Light() {};

	protected:
		vec3 colour;
		GLfloat ambientIntensity;
	};

}