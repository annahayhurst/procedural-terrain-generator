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
		Light(vec3 col, GLfloat aInt);

		virtual void useLight(Shader* s); // this is overridden by other type(s) of light

		vec3 getColour() { return colour; };
		GLfloat getAmbientIntensity() { return ambientIntensity; };

		void setColour(vec3 col) { colour = col; };
		void setAmbientIntensity(GLfloat aIntensity) { ambientIntensity = aIntensity; };

		~Light() {};

	protected:
		vec3 colour;
		GLfloat ambientIntensity;
	};

}