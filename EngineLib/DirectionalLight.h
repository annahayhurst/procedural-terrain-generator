#pragma once

/*
* DirectionalLight
* Inherits from Light. Facilitates creation of a light source at an infinite distance (parallel rays),
* shining in a given direction.
*/

#include "Light.h"

namespace Engine {
	class DirectionalLight : public Light {
	public:
		DirectionalLight();
		DirectionalLight(vec3 colour, vec3 direction, GLfloat ambientIntensity, GLfloat diffuseIntensity);

		void useLight(Shader* shader) override;

		vec3 getDirection() { return direction; };
		GLfloat getDiffuseIntensity() { return diffuseIntensity; };

		void setDirection(vec3 direction) { this->direction = direction; };
		void setDiffuseIntensity(GLfloat diffuseIntensity) { this->diffuseIntensity = diffuseIntensity; };

		// No need for destructor - use ~Light()

	protected:
		vec3 direction;
		GLfloat diffuseIntensity;
	};
}
