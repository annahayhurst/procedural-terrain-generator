#version 330

// Location = x refers to the xth vertex attribute array pointer (see Mesh.cpp)
layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colours;
layout (location = 2) in vec3 normals;


// Values sent to fragment shader (note lack of texture output)
out vec3 normal;
out vec3 fragmentPos;
out vec4 vColour;

// Uniforms linked to OpenGL program
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// Calculate (global) position property for this vertex, in accordance with co-ordinate system order
	// Local space (raw co-ordinates) -> world space -> view space (camera) -> clip space (actual pos. in scene)
	gl_Position = projection * view * model * vec4(positions, 1.0);
	
	// For now set to an arbitrary colour - in future we will calculate colour based on position in scene
	vColour = vec4(colours, 1.0);
	
	// We must "undo" the transforms applied to the model. If this is not accounted for, normals 
	// will change direction when a mesh has non-uniform scaling applied to it (e.g. noise). 
	// We transpose an inverse of the model to remove this effect from the normals.
	// To do so in the shader is not the most efficient way, but works well while the scene is small.
	
	// We use a matrix conversion of the first 3 rows/columns of our model because this is where values have been
	// modified by transforms.
	mat3 modelMatrix = mat3(model);
	
	normal = transpose( inverse(modelMatrix) ) * normals;
	
	// Position of the fragment relative to this scene is the product of the model and vertex positions
	// We cut off the final (w) column of the vec4 using swizzling.
	fragmentPos = ( model * vec4(positions, 1.0) ).xyz;
}