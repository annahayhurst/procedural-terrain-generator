#version 330

// (Location = x) refers to the xth vertex attribute array pointer
layout (location = 0) in vec3 positions;

// Values sent to fragment shader
out vec3 textureCoord;

// Uniforms, bound to OpenGL program
uniform mat4 projection;
uniform mat4 view;

void main() {
	// Calculate position property for this vertex, in accordance with co-ordinate system order
	// Unlike the other shaders, the model is not used. This is because the skybox will appear at a far distance
	// from the actual rendered scene we see.
	vec4 skyPos = projection * view * vec4(positions, 1.0);
	// This swizzle 'tricks' the depth test, allowing us to set the skybox at an infinite distance, encapsulating
	// the actual rendered scene. It removes the z axis element of the position vector.
	gl_Position = skyPos.xyww;
	
	textureCoord = positions;
}