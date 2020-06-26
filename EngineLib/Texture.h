#pragma once

/*
* Texture
* Facilitates loading of image files to be used as textures, which are applied to Mesh objects
* using wrapping techniques. The library STB image is used to simplify the image load process.
*
* All STB libraries can be found at: https://github.com/nothings/stb. They were created by Sean Barrett.
*/

#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>

namespace Engine {
	// So we can bind the texture with the appropriate number of channels, have an enum for file types
	enum FileExtension { PNG, JPG };

	class Texture {
	public:
		Texture();

		bool generateTexture(const char* filePath, FileExtension type);
		void useTexture();

		static void clearTexture();

		GLuint getID() { return id; };
		GLuint getHeight() { return height; };
		GLuint getWidth() { return width; };

		~Texture();

	private:
		GLuint id;
		int width, height, depth; // depth -> bit-depth, used by image loader to store colour info (e.g 32-bit)

		void bindTexture(unsigned char* textureData, FileExtension extension);
		void deleteTexture();
	};

}