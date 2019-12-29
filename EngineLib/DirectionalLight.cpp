#include "DirectionalLight.h"

namespace Engine {
	// Default constructor. Appropriate variables are passed upwards to the base class.
	DirectionalLight::DirectionalLight() : Light(vec3(1.0f, 1.0f, 1.0f), 0.5f),
		direction(vec3(1.0f, 1.0f, 1.0f)), diffuseIntensity(0.5f) {
	}

	// Paramater constructor
	DirectionalLight::DirectionalLight(vec3 colour, vec3 direction, GLfloat aInt, GLfloat dInt) :
		Light(colour, aInt), direction(direction), diffuseIntensity(dInt) {
	}

	// Set the ambient and diffuse uniform properties for the passed shader.
	void DirectionalLight::useLight(Shader* s) {
		// Ambient
		glUniform3f(s->getAmbColourUL(), colour.x, colour.y, colour.z);
		glUniform1f(s->getAmbIntensityUL(), ambientIntensity);

		// Diffuse
		glUniform3f(s->getDirectionUL(), direction.x, direction.y, direction.z);
		glUniform1f(s->getDiffIntensityUL(), diffuseIntensity);

	}
}