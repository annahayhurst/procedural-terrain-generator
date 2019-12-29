#version 330

// (Location = x) refers to the xth vertex attribute array pointer (see Mesh.cpp)
layout (location = 0) in vec3 positions;
layout (location = 1) in vec2 texels;
layout (location = 2) in vec3 normals;

// Values sent to fragment shader
out vec2 textureCoord;
out vec3 normal;
out vec3 fragmentPos;

// Uniforms, bound to OpenGL program
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	// Calculate position property for this vertex, in accordance with co-ordinate system order
	// Local space (raw co-ordinates) -> world space -> view space (camera) -> clip space (actual pos. in scene)
	gl_Position = projection * view * model * vec4(positions, 1.0);
	
	textureCoord = texels; // texels don't need to be changed before being passed to fragment shader
	
	// We must "undo" the transforms applied to the model. If this is not accounted for, normals 
	// will change direction when a mesh has non-uniform scaling applied to it. We transpose an 
	// inverse of the model to remove this effect from the normals.
	// To do so in the shader is not the most efficient way, but works well while the scene is small.
	
	// We use a matrix of the first 3 rows/columns of our model because this is where values have been
	// modified by transforms.
	mat3 modelMatrix = mat3(model);
	
	normal = transpose(inverse(modelMatrix)) * normals;
	
	// Position of the fragment relative to the scene is the product of the model and the vertex positions
	fragmentPos = ( model * vec4(positions, 1.0) ).xyz; // cut off the final column with swizzling
}