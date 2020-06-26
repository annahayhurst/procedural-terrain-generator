#pragma once
/*
* Material
* A class defining the physical properties of a mesh/texture.
* Allows different levels of specular lighting to be set for objects.
*/

#include <GL\glew.h>
#include <vector>
#include "Shader.h"

using std::vector;

namespace Engine {
	class Material {
	public:
		Material();
		Material(GLfloat specularIntensity, GLuint shininess);

		void useMaterial(Shader* shader);

		GLfloat getSpecularIntensity() { return specularIntensity; };
		GLuint getShininess() { return shininess; };

		void setSpecularIntensity(GLfloat specularIntensity) { this->specularIntensity = specularIntensity; };
		void setShininess(GLuint shininess) { this->shininess = shininess; };

		~Material() {};

	private:
		GLfloat specularIntensity;
		GLuint shininess;

	};
}
