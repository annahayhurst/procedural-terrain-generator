#pragma once

/*
* PerlinGrid
*
* This class is the backbone of procedural generation for the system. An instance of the class is a set of meshes made up of cells
* of constant width and height "cellSize", constructed into a grid with row and column counts equal to "size".
* Each row is its own mesh. In a sense, this means that terrain is constructed in strips which combine to form the overall grid.
*
* The class makes use of octaveNoise2D(float, float) from Perlin. Each vertex has a noise value calculated from its x and z 
* co-ordinates, which is added to its y co-ordinate to determine its height. The final terrain depends on the seed, octave count
* and persistence passed to the Perlin object.
*
* Colour striation is applied to the terrain according to final vertex height. A ColourMap is also applied, which will change the colour
* scheme and boundaries of colour division in the grid.
*/


#include "Perlin.h"
#include "Mesh.h"
#include "Shader.h"
#include "ColourMap.h"

#include <iostream>

namespace Engine {

	class PerlinGrid {
	public:
		PerlinGrid();
		PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, Perlin perlin);
		PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, GLuint seed, ColourMap colourMap);
		PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, GLuint seed, GLuint octaves, GLfloat persistence, ColourMap colourMap);

		void render();

		GLuint getSize() { return size; };
		GLfloat getHorizontalScale() { return horizontalScale; };
		GLfloat getVerticalScale() { return verticalScale; };
		GLuint getSeed() { return perlin.getSeed(); };

		void setSize(GLuint s);
		void setHorizontalScale(GLfloat horizontalScale);
		void setVerticalScale(GLfloat verticalScale);
		void setSeed(uint seed);
		void setColourMap(ColourMap colourMap);

		~PerlinGrid();

	private:
		GLuint size;
		GLfloat horizontalScale, verticalScale;
		GLsizei vertexCount, indexCount;

		Perlin perlin;
		ColourMap colourMap;

		GLfloat* vertexArray;
		GLuint* indexArray;
		vector<Mesh*> grid;

		const uint MAX_SIZE = 4000;
		GLfloat cellSize;

		void generateGrid();

		void generateVertexArrays();
		void generateIndexArray();
		void createRow();

		vec3 calculateRGB(GLfloat height);

		void deleteGrid();
	};

}
