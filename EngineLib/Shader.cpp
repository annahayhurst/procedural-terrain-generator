#include "Shader.h"

namespace Engine {
	// Constructor - initialise default values, which will be updated later
	Shader::Shader() : id(0),
		uModel(0), uProjection(0), uView(0),
		uAmbientColour(0), uAmbientIntensity(0),
		uDirection(0), uDiffuseIntensity(0),
		uShininess(0), uSpecularIntensity(0), uCameraPosition(0) {
	}

	// Using helper function to read shader from file, convert the output to a C-style
	// string and then pass to the method compiling the shader.
	// Exists as a public call to the compilation method.
	bool Shader::createShaders(const char* vPath, const char* fPath) {
		return compileShaders(readSourceCode(vPath).c_str(), readSourceCode(fPath).c_str());
	}

	// Simply makes public call to OpenGL to use the shader after we have already compiled/linked it
	void Shader::useShaders() {
		glUseProgram(id);
	}

	// Static function that unbinds whatever shader is currently in use
	void Shader::clearShaders() {
		glUseProgram(0);
	}

	void Shader::deleteShaders() {
		if (id != 0) { // (An ID of 0 indicates shader is not in use)
			glDeleteProgram(id);
			id = 0;
		}

		// Reset all uniforms
		uModel = 0; uProjection = 0; uView = 0;
		uAmbientColour = 0; uAmbientIntensity = 0;
		uDirection = 0; uDiffuseIntensity = 0;
		uShininess = 0; uSpecularIntensity = 0;
		uCameraPosition = 0;
	}

	// Use file stream to extract shader text
	string Shader::readSourceCode(const char* filePath) {
		string content;
		ifstream fileIn(filePath, std::ios::in);

		// Check file was found successfully and was opened
		if (!fileIn.is_open()) {
			std::cout << "Couldn't read file at: " << filePath << " File does not exist. \n";
			return "";
		}

		string line = "";
		// Get each line until end of file
		while (!fileIn.eof()) {
			std::getline(fileIn, line);
			content.append(line + "\n");
		}

		fileIn.close();

		return content;
	}

	bool Shader::compileShaders(const char* vCode, const char* fCode) {
		id = glCreateProgram(); // assigns empty program to ID with non-zero value you can reference

		if (!id || id == 0) { // check program was created
			std::cout << "Error creating program for shader. \n";
			return false;
		}

		// Pair the code with its appropriate shader type
		attachShader(id, vCode, GL_VERTEX_SHADER);
		attachShader(id, fCode, GL_FRAGMENT_SHADER);

		// Variables for debugging + error reporting
		GLint result = 0;
		GLchar errors[1024] = { 0 };

		// Link the shader program (now with attached frag/vertex shaders) to OpenGL
		glLinkProgram(id);

		// Check that program linked correctly
		glGetProgramiv(id, GL_LINK_STATUS, &result);
		if (!result) {
			// Get error if link failed
			glGetProgramInfoLog(id, sizeof(errors), NULL, errors);
			std::cout << "Couldn't link program. Error: " << errors << "\n";
			return false;
		}

		// Confirm that program can execute in current state of OpenGL
		glValidateProgram(id);

		// Check that validation was successful
		glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
		if (!result) {
			glGetProgramInfoLog(id, sizeof(errors), NULL, errors);
			std::cout << "Couldn't validate program. Error: " << errors << "\n";
			return false;
		}

		// Finally initialise uniform values
		assignUniforms();

		return true;
	}

	// Compiles the actual shader code and ensures it is used for the appropriate type, then attaches it to the running program
	void Shader::attachShader(GLuint program, const char* code, GLenum type) {
		GLuint newShader = glCreateShader(type);

		// Method for getting shader source code needs two arrays
		// In this case we are working with one source per shader so the array is only of length 1.
		const GLchar* codeSource[1]{ code };

		// Measure the length of the code.
		GLint codeLength[1]{ (GLint)strlen(code) };

		// Signify to the new shader where it can find its data, and how long this data is.
		glShaderSource(newShader, 1, codeSource, codeLength);
		// Compile the shader using the data set as the source.
		glCompileShader(newShader);

		// Error checking
		GLint result = 0;
		GLchar errors[1024] = { 0 };

		// Has it compiled?
		glGetShaderiv(newShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(newShader, sizeof(errors), NULL, errors);
			std::cout << "Could not compile " << type << " shader. Error: " << errors << "\n";
			return;
		}

		// Attach the properly compiled shader to the passed program ID.
		glAttachShader(program, newShader);

	}

	// Locate uniforms (by name within the code of the shader with this ID.
	void Shader::assignUniforms() {
		// Matrices
		uProjection = glGetUniformLocation(id, "projection");
		uModel = glGetUniformLocation(id, "model");
		uView = glGetUniformLocation(id, "view");

		// Light variables
		uAmbientColour = glGetUniformLocation(id, "light.colour");
		uAmbientIntensity = glGetUniformLocation(id, "light.aIntensity");

		uDirection = glGetUniformLocation(id, "light.direction");
		uDiffuseIntensity = glGetUniformLocation(id, "light.dIntensity");

		uShininess = glGetUniformLocation(id, "material.shininess");
		uSpecularIntensity = glGetUniformLocation(id, "material.sIntensity");

		// Camera
		uCameraPosition = glGetUniformLocation(id, "camPos");
	}
}