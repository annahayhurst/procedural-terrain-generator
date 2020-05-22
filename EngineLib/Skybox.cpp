#include "Skybox.h"

namespace Engine {
	// Default constructor
	Skybox::Skybox() : id(0) {}

	// Load skybox through constructor
	Skybox::Skybox(vector<string> filePaths) : id(0) {
		this->loadSkybox(filePaths);
	}

	// Load the images at each of the filepaths in the vector and pass them to createFace to make the texture for that cube face.
	void Skybox::loadSkybox(vector<string> filePaths) {
		if (filePaths.size() != 6) { // check there are the correct number of images
			std::cerr << "Invalid number of filenames supplied for skybox creation. You must provide 6 filenames.\n";
			return;
		}

		bindSkybox(); // set up the texture unit

		int width, height, depth;
		for (size_t t = 0; t < filePaths.size(); t++) {
			// Load the current face
			unsigned char* face = stbi_load(filePaths[t].c_str(), &width, &height, &depth, 0);

			// Image exists at this path
			if (face) {
				createFace(face, width, height, t);
				stbi_image_free(face); // free up data that isn't needed
			}
			// Image does not exist at this path
			else {
				std::cerr << "Couldn't load texture for skybox at path: " << filePaths[t].c_str() << "\n";
				stbi_image_free(face); // free up data that isn't needed
			}
		}

		setParameters(); // set texture properties
		createSkybox(); // make the skybox mesh
	}

	// Rebind the VAO and textures, then draw
	void Skybox::drawSkybox() {
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// Set up a cubemap texture set with a unique IDs
	void Skybox::bindSkybox() {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	}

	void Skybox::createFace(unsigned char* data, int width, int height, int position) {
		// Increment the enum according to the passed position - this allows us to access all 6 faces by 
		// going through the loop in loadSkybox
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + position, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	// Make the simple cube mesh
	void Skybox::createSkybox() {

		// Bind VAO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Bind VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 108, &vertices, GL_STATIC_DRAW);

		// Set 0th attribute pointer to contain x, y, z co-ordinates
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), 0);
	}

	// Set the properties for each of the cubemap textures
	void Skybox::setParameters() {
		// 3D wrapping properties - ensure texture stretches correctly to each edge in each direction (x,y,z)
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// How the textures should appear from near and far distances (both linear - pixel smoothing applied)
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

}