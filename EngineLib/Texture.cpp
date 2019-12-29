#define STB_IMAGE_IMPLEMENTATION // for use of stb_image.h

#include "Texture.h"

namespace Engine {
	// Default constructor - all initialised to 0 as they will be changed in image loading
	Texture::Texture() : id(0), width(0), height(0), depth(0) {}

	bool Texture::generateTexture(const char* filePath, FileExtension type)
	{
		unsigned char* textureData = stbi_load(filePath, &width, &height, &depth, 0);

		if (textureData) {
			bindTexture(textureData, type);
			stbi_image_free(textureData); // free the memory held by the loaded image
		}
		else {
			std::cout << "Couldn't load a texture from " << filePath << ". File does not exist.\n";
			return false;
		}

		return true;
	}

	// Set texture to be used for next drawn object
	void Texture::useTexture() {
		// Set the active texture unit to be unit 0
		glActiveTexture(GL_TEXTURE0);
		// Bind the generated texture to this unit
		glBindTexture(GL_TEXTURE_2D, id);
	}

	// Unbind the texture from texture unit (static)
	void Texture::clearTexture() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Bind the texture data to the texture unit so it can be used.
	void Texture::bindTexture(unsigned char* texData, FileExtension ext) {
		// Generate one texture and assign it an ID.
		glGenTextures(1, &id);
		// Assert that the type of texture for this ID is a 2D image.
		glBindTexture(GL_TEXTURE_2D, id);

		// Set the parameters for a 2D texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // tile texture in x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // tile texture in y axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // when we're close to the texture, linear sampling (smooth)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when we're far from the texture, linear sampling

		GLenum type1, type2;
		// Set the channel type according to the image type we have been given
		switch (ext) {
		case PNG:
			type1 = GL_RGBA;
			type2 = GL_RGBA;
			break;
		case JPG:
			type1 = GL_RGBA;
			type2 = GL_RGB;
			break;
		default:
			type1 = GL_RGB;
			type2 = GL_RGB;
			break;
		}

		// Now create the actual texture
		// type | initial mipmap | image type | width | height | (legacy value) | loaded data type | stored data type | the data
		glTexImage2D(GL_TEXTURE_2D, 0, type1, width, height, 0, type2, GL_UNSIGNED_BYTE, texData);
		// Create mipmaps (different resizes of the texture that will be seen at different distances)
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	// Remove texture from memory and reset variables.
	void Texture::deleteTexture() {
		glDeleteTextures(1, &id); // delete one texture with this id.

		height = 0;
		width = 0;
		depth = 0;
	}

	// Destructor
	Texture::~Texture() {
		if (id != 0) {
			deleteTexture();
		}
	}


}