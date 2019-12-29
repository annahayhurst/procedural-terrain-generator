#pragma once

/*
* Skybox
* A class that creates a skybox, a cubemap texture that wraps around a rendered scene and looks like a realistic backdrop for any camera direction.
* This combines the texture type GL_TEXTURE_CUBE_MAP with a standard 1x1 cube mesh.
* I used the following tutorial to help me create this class, and as such it (and the associated shaders) will bear similarity -
* https://learnopengl.com/Advanced-OpenGL/Cubemaps
* 
*/

#include <vector>
#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

using std::vector;

namespace Engine {
	class Skybox {
	public:
		Skybox();
		Skybox(vector<std::string> filePaths);

		void loadSkybox(vector<std::string> filePaths);
		void drawSkybox();
		~Skybox() {};

	private:
		void bindSkybox();
		void createFace(unsigned char* data, int width, int height, int position);
		void createSkybox();
		void setParameters();

		GLuint id, VAO, VBO;

		// 6 faces of the skybox mesh (a simple unit cube)
		float vertices[108] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
	};
}