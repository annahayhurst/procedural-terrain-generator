#pragma once

/*
* ColourMap
* A utility struct with no methods or constructor that exists purely to store information about
* a 'biome', namely a collection of colours, directions and boundaries that combine to give a cohesive
* sense of location to a map procedurally generated by the system.
*/

#include <glm/glm.hpp>
using namespace glm;

namespace Engine {
	struct ColourMap {
		// The colour of light corresponding to this map
		vec3 lightColour;
		// The direction of the light, determining the angle at which it will hit the terrain.
		vec3 lightDirection;

		// The boundaries at which we transition from one terrain type to the next
		// bounds.x = peak bound, bounds.y = high bound, bounds.z = low bound
		vec3 bounds;

		// Colours of the different layers of striation, according to height
		vec3 peak, high, mid, low;
	};
}