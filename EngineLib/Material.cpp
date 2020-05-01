#include "Material.h"

namespace Engine {
	// Default constructor
	Material::Material() : specularIntensity(0.5f), shininess(32) {
	}

	// Constructor with params
	Material::Material(GLfloat specularIntensity, GLuint shininess) :
		specularIntensity(specularIntensity), shininess(shininess) {
	}

	// Set uniform values in the shaders this material is linked to
	void Material::useMaterial(Shader* shader) {
		glUniform1f(shader->getSpecularIntensityUL(), specularIntensity);
		glUniform1i(shader->getShininessUL(), shininess);

	}

}