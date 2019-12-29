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
		Material(GLfloat sInt, GLuint shininess);

		void useMaterial(Shader* s);

		GLfloat getSpecularIntensity() { return specularIntensity; };
		GLuint getShininess() { return shininess; };

		void setSpecularIntensity(GLfloat sIntensity) { specularIntensity = sIntensity; };
		void setShininess(GLuint shine) { shininess = shine; };

		~Material() {};

	private:
		GLfloat specularIntensity;
		GLuint shininess;

	};
}
