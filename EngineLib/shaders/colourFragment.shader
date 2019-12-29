#version 330

// Values taken from vertex shader
in vec3 normal;
in vec3 fragmentPos;
in vec4 vColour;

// Final single output - colour of this fragment.
out vec4 colour;

// A struct to represent a light in the scene.
// Holds all the properties that we link as uniforms in our shader class.
struct DirectionalLight {
	vec3 colour, direction;
	float aIntensity, dIntensity;
};

// Struct to hold material properties
struct Material {
	float sIntensity;
	int shininess;
};

uniform vec3 cameraPos;
uniform DirectionalLight light;
uniform Material material;

// Global(s)
float diffuseMultiplier;

vec4 calculateAmbient() {
	// Ambient light is a simple calculation of colour and intensity
	return vec4(light.colour, 1.0) * light.aIntensity;
}

vec4 calculateDiffuse() {
	// The diffuse value must account for the angle light hits the surface at. If light hits at
	// a 90 degree angle, maximum light is received - diffuseMultiplier will be 1. If the angle is
	// >90 degrees, the dot product will be negative, in which case we use 0 as it will be the max value.
	// Any angles between 0 and 90 will modify the diffuseMultiplier to be between 0 and 1.
	float dotResult = dot(normalize(normal), normalize(light.direction));
	diffuseMultiplier = max(dotResult, 0.0f);
	
	// Final diffuse value is a product of its colour, dot product modifier and intensity
	return vec4(light.colour, 1.0) * diffuseMultiplier * light.dIntensity;
}

vec4 calculateSpecular() {
	// Check that there is diffuse light on this fragment (taken from result of diffuse dot product)
	// No diffuse -> no specular
	if(diffuseMultiplier > 0.0f) {
		
		// Calculate the vector direction between fragment and the camera
		vec3 fragmentToCam = normalize(cameraPos - fragmentPos);
		
		// Specular light requires a reflection. The incident ray is in the direction of the light.
		vec3 reflection = reflect(light.direction, normalize(normal));
		reflection = normalize(reflection);
		
		// Determine whether any specular light hits the surface according to the dot product between
		// the reflection and the line between the camera + fragment.
		float specularMultiplier = dot(fragmentToCam, reflection);
		
		// If dot product is >0 there is specular light
		if(specularMultiplier > 0.0f) {
			// The shininess of an object affects how much specular light there will be (it is the exponent)
			specularMultiplier = pow(specularMultiplier, material.shininess);
			// Finally, calculate the colour
			return vec4(light.colour, 1.0) * specularMultiplier * material.sIntensity;
		}
		
	}
	
	return vec4(0.0, 0.0, 0.0, 0.0);
}


void main() {
	vec4 ambient = calculateAmbient();
	
	vec4 diffuse = calculateDiffuse();
	
	vec4 specular = calculateSpecular();
	
	// In Phong lighting, the light is a sum of ambient, diffuse and specular light values
	colour = vColour * (ambient + diffuse + specular);
}