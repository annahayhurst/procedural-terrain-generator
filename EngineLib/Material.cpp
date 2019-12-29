#include "Material.h"

namespace Engine {
	// Default constructor
	Material::Material() : specularIntensity(0.5f), shininess(32) {
	}

	// Constructor with params
	Material::Material(GLfloat sInt, GLuint shininess) :
		specularIntensity(sInt), shininess(shininess) {
	}

	// Set uniform values in the shaders this material is linked to
	void Material::useMaterial(Shader* s) {
		glUniform1f(s->getSpecIntensityUL(), specularIntensity);
		glUniform1i(s->getShininessUL(), shininess);

	}

}