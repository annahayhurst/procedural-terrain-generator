#include "Light.h"

namespace Engine {
	// Default constructor - basic white light at 50% intensity
	Light::Light() :
		colour(vec3(1.0f, 1.0f, 1.0f)), ambientIntensity(0.5f) {
	}

	// Constructor with paramaters
	Light::Light(vec3 col, GLfloat aInt) :
		colour(col), ambientIntensity(aInt) {
	}

	// Give the colour and intensity values associated with this object to the shader which
	// will then apply the light to the scene.
	void Light::useLight(Shader* s) {
		glUniform3f(s->getAmbColourUL(), colour.x, colour.y, colour.z);
		glUniform1f(s->getAmbIntensityUL(), ambientIntensity);
	}

}