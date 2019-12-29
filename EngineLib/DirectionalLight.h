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
		DirectionalLight(vec3 colour, vec3 direction, GLfloat aInt, GLfloat dInt);

		void useLight(Shader* s) override;

		vec3 getDirection() { return direction; };
		GLfloat getDiffuseIntensity() { return diffuseIntensity; };

		void setDirection(vec3 dir) { direction = dir; };
		void setDiffuseIntensity(GLfloat dIntensity) { diffuseIntensity = dIntensity; };

		// No need for destructor - use ~Light()

	protected:
		vec3 direction;
		GLfloat diffuseIntensity;
	};
}
