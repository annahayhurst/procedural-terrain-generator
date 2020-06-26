#include "Light.h"

namespace Engine {
	// Default constructor - basic white light at 50% intensity
	Light::Light() :
		colour(vec3(1.0f, 1.0f, 1.0f)), ambientIntensity(0.5f) {
	}

	// Constructor with paramaters
	Light::Light(vec3 colour, GLfloat ambientIntensity) :
		colour(colour), ambientIntensity(ambientIntensity) {
	}

	// Give the colour and intensity values associated with this object to the shader which
	// will then apply the light to the scene.
	void Light::useLight(Shader* shader) {
		glUniform3f(shader->getAmbientColourUL(), colour.x, colour.y, colour.z);
		glUniform1f(shader->getAmbientIntensityUL(), ambientIntensity);
	}

}