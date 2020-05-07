#pragma once
/*
* Shader
* Handles the loading and compilation of shaders, as well as initialising the value
* of uniforms that are then used by other classes. Shaders are stored as plain text
* and are compiled into GLSL (C-style code).
* Due to the constraints of GLSL, the file paths and extracted code must be of type 
* const char* (a C string).
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;
using std::ifstream;

namespace Engine {
	class Shader {
	public:
		Shader();

		bool createShaders(const char* vertexShaderPath, const char* fragmentShaderPath);

		void useShaders();
		static void clearShaders();

		// Get methods for uniforms - UL = uniform location. We access their 'locations' in the shader,
		// denoted by an integer ID.
		GLuint getProjectionUL() { return uProjection; };
		GLuint getModelUL() { return uModel; };
		GLuint getViewUL() { return uView; };
		GLuint getAmbientColourUL() { return uAmbientColour; };
		GLuint getAmbientIntensityUL() { return uAmbientIntensity; };
		GLuint getDirectionUL() { return uDirection; };
		GLuint getDiffuseIntensityUL() { return uDiffuseIntensity; };
		GLuint getShininessUL() { return uShininess; };
		GLuint getSpecularIntensityUL() { return uSpecularIntensity; };
		GLuint getCameraPositionUL() { return uCameraPosition; }

		GLuint getID() { return id; };

		~Shader() { deleteShaders(); };

	private:
		GLuint id;

		// Uniforms are variables found inside the shader files that must be linked to the OpenGL system.
		// In this system they're denoted by a "u" before the variable name.
		GLuint uProjection, uModel, uView,
			uAmbientColour, uAmbientIntensity,
			uDirection, uDiffuseIntensity,
			uShininess, uSpecularIntensity, uCameraPosition;

		string readSourceCode(const char* filePath);

		bool compileShaders(const char* vertexShaderCode, const char* fragmentShaderCode);
		void attachShader(GLuint program, const char* code, GLenum type);
		void assignUniforms();
		void deleteShaders();
	};

}