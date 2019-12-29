#version 330
// Value taken from vertex colour
in vec3 textureCoord;

// Final fragment colour
out vec4 colour;

// A 3D texture sampler for the whole skybox, which is a cubemap
uniform samplerCube skybox;

void main() {
	colour = texture(skybox, textureCoord);
}