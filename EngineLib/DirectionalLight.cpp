#include "DirectionalLight.h"

namespace Engine {
	// Default constructor. Appropriate variables are passed upwards to the base class.
	DirectionalLight::DirectionalLight() : Light(vec3(1.0f, 1.0f, 1.0f), 0.5f),
		direction(vec3(1.0f, 1.0f, 1.0f)), diffuseIntensity(0.5f) {
	}

	// Paramater constructor
	DirectionalLight::DirectionalLight(vec3 colour, vec3 direction, GLfloat ambientIntensity, GLfloat diffuseIntensity) :
		Light(colour, ambientIntensity), direction(direction), diffuseIntensity(diffuseIntensity) {
	}

	// Set the ambient and diffuse uniform properties for the passed shader.
	void DirectionalLight::useLight(Shader* shader) {
		// Ambient
		glUniform3f(shader->getAmbientColourUL(), colour.x, colour.y, colour.z);
		glUniform1f(shader->getAmbientIntensityUL(), ambientIntensity);

		// Diffuse
		glUniform3f(shader->getDirectionUL(), direction.x, direction.y, direction.z);
		glUniform1f(shader->getDiffuseIntensityUL(), diffuseIntensity);

	}
}