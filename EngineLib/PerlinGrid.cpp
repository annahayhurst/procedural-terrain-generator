#include "PerlinGrid.h"

namespace Engine {
	// Default constructor setting class variables to values suitable for a lower end computer for safety
	PerlinGrid::PerlinGrid() :
		size(1000), horizontalScale(5.0f), verticalScale(5.0f), cellSize(0.075f),
		perlin(Perlin()),
		grid(vector<Mesh*>()) {
		// A default colour map is generated (mountain biome)
		colourMap = {
			vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f),
			vec3(0.42f, 0.05f, -0.2f),
			vec3(0.9f, 0.9f, 0.9f), vec3(0.5f, 0.5f, 0.5f), vec3(0.09f, 0.43f, 0.15f), vec3(0.16f, 0.25f, 0.58f)
		};

		generateGrid();
	}

	PerlinGrid::PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, Perlin perlin) :
		size(size), horizontalScale(scaleFactor), verticalScale(scaleFactor), cellSize(cellSize),
		perlin(perlin),
		grid(vector<Mesh*>()) {
		// A default colour map is generated (mountain biome)
		colourMap = {
			vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f),
			vec3(0.42f, 0.05f, -0.2f),
			vec3(0.9f, 0.9f, 0.9f), vec3(0.5f, 0.5f, 0.5f), vec3(0.09f, 0.43f, 0.15f), vec3(0.16f, 0.25f, 0.58f)
		};

		// Check that performance targets won't be violated
		if (size > MAX_SIZE) {
			std::cerr << "Produced grid of size " << size << " x " << size << " would be too large. Reducing size to " << MAX_SIZE << " x " << MAX_SIZE << std::endl;
			size = MAX_SIZE;
		}

		generateGrid();
	}

	// Parameter constructor 1 - takes the seed for the Perlin object and the colour map
	PerlinGrid::PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, GLuint seed, ColourMap colourMap) :
		size(size), horizontalScale(scaleFactor), verticalScale(scaleFactor), cellSize(cellSize),
		perlin(Perlin(seed)), colourMap(colourMap),
		grid(vector<Mesh*>()) {

		// Check that performance targets won't be violated
		if (size > MAX_SIZE) {
			std::cerr << "Produced grid of size " << size << " x " << size << " would be too large. Reducing size to " << MAX_SIZE << " x " << MAX_SIZE << std::endl;
			size = MAX_SIZE;
		}

		// Generate the grid
		generateGrid();
	}

	// Parameter constructor 2 - also takes the octave count and persistence value to pass to the Perlin object.
	PerlinGrid::PerlinGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, GLuint seed, GLuint octaves, GLfloat persistence, ColourMap colourMap) :
		size(size), horizontalScale(scaleFactor), verticalScale(scaleFactor), cellSize(cellSize),
		perlin(Perlin(seed, octaves, persistence)), colourMap(colourMap),
		grid(vector<Mesh*>()) {

		// Check that performance targets won't be violated
		if (size > MAX_SIZE) {
			std::cerr << "Produced grid of size " << size << " x " << size << " would be too large. Reducing size to " << MAX_SIZE << " x " << MAX_SIZE << std::endl;
			size = MAX_SIZE;
		}

		// Generate the grid
		generateGrid();
	}

	// Draw all meshes belonging to this grid.
	void PerlinGrid::render() {

		for (Mesh* mesh : grid) {
			mesh->drawMesh();
		}
	}

	// Set number of rows and refresh the grid
	void PerlinGrid::setSize(GLuint size) {
		this->size = size;
		generateGrid();
	}

	// Set number of columns and refresh the grid
	void PerlinGrid::setHorizontalScale(GLfloat horizontalScale) {
		this->horizontalScale = horizontalScale;
	}

	void PerlinGrid::setVerticalScale(GLfloat verticalScale) {
		this->verticalScale = verticalScale;
	}

	// Set seed, changing the noise permutation vector, and refresh the grid
	void PerlinGrid::setSeed(uint seed) {
		perlin.setSeed(seed);
		generateGrid();
	}

	void PerlinGrid::setColourMap(ColourMap colourMap) {
		this->colourMap = colourMap;
	}

	PerlinGrid::~PerlinGrid() {
		deleteGrid();
	}

	// (Re)generate the necessary information to produce the noise grid according to the
	// current seed, row, and column count.
	void PerlinGrid::generateGrid() {

		// If grid already exists - delete old one to remove from scene
		if (grid.size() == size) {
			deleteGrid();
		}

		// Generate index array
		generateIndexArray();

		// Generate vertex array + row meshes
		generateVertexArrays();

		// Dispose of index data after all rows generated
		delete[] indexArray;
	}

	// Generate the vertices needed to produce the grid, row by row.
	void PerlinGrid::generateVertexArrays() {
		/*
		* Example: 1 row, 1 column -> single celled grid.
		*
		* (x, y, z-cellSize)		1-----------3	(x+cellSize, y, z-cellSize)
		*							|			|
		*							|	cell	|
		*							|			|
		*				(x, y, z)	0-----------2	(x+cellSize, y, z)
		*
		* Using switch cases, we can generalise the production of the vertex array.
		* Noise is calculated per vertex and used as a height modifier.
		*/

		// The total number of values in each vertex array can be counted as :
		// Double the number of columns, plus an extra two for the first column of each row,  multiplied
		// by 9 to represent the number of values needed to produce a single cell (x y z, r g b, nx ny nz).
		vertexCount = ((size * 2) + 2) * 9;

		GLfloat x = 0.0f, y = 0.0f, z = 0.0f;
		bool low = true;
		for (size_t t = 0; t < size; t++) {
			vertexArray = new GLfloat[vertexCount];

			for (int i = 0; i < vertexCount; i += 9) {
				switch (low) {
					// Lower vertex
				case true:
					// x y z
					vertexArray[i] = x;
					vertexArray[i + 1] = y + perlin.octaveNoise2D(x, z);
					vertexArray[i + 2] = z;

					low = !low; // next vertex is high
					break;

					// Upper vertex
				case false:
					// x y z
					vertexArray[i] = x;
					vertexArray[i + 1] = y + perlin.octaveNoise2D(x, z - cellSize);
					vertexArray[i + 2] = z - cellSize;

					low = !low; // next vertex is low

					// Increase x so we can move across to the next column
					x += cellSize;
					break;
				}

				// Set colours according to position of vertex
				vec3 vCol = calculateRGB(vertexArray[i + 1]);
				vertexArray[i + 3] = vCol.r; // r
				vertexArray[i + 4] = vCol.g; // g
				vertexArray[i + 5] = vCol.b; // b

				// Default normals
				vertexArray[i + 6] = 0.0f; // nx
				vertexArray[i + 7] = 0.0f; // ny
				vertexArray[i + 8] = 0.0f; // nz
			}

			// Reset x to move to the start of the row. Increment z to move further into the screen by one row.
			x = 0.0f;
			z -= cellSize;

			// Use this vertex data to create a new row
			createRow();
		}
	}

	// Generate the indices needed to produce the grid, row by row
	void PerlinGrid::generateIndexArray() {
		/*
		* Example: Cell 1, and the two triangles that make it up, in a forwards facing row
		*
		* 1-----------3				 1				   1------3
		* |			  |				 |\					 \   |
		* |	  cell	  |		->		 | \				  \  |		with indices: 0 2 1
		* |			  |				 |  \		and		   \ |					  1 2 3
		* 0-----------2				 |   \				    \|
		*							0------2				 2
		*
		* We can generalise index production for each row by considering the bottom left corner
		* of each cell, labelled the "pivot", from which we can set the surrounding index values.
		*/

		// The total number of values in each index array can be counted as:
		// 6 times the number of columns, as every cell is made up of 2 triangles that require 3 indices to draw.
		indexCount = size * 6;
		indexArray = new GLuint[indexCount];

		for (int i = 0; i < indexCount; i += 6) {
			int pivot = (2 * i) / 6;

			indexArray[i] = pivot;
			indexArray[i + 1] = pivot + 2;
			indexArray[i + 2] = pivot + 1;

			indexArray[i + 3] = pivot + 1;
			indexArray[i + 4] = pivot + 2;
			indexArray[i + 5] = pivot + 3;
		}
	}


	// Combine the produced vertices and indices to create a mesh for each row of the grid.
	void PerlinGrid::createRow() {
		Mesh* row = new Mesh(COLOURED);
		row->createMesh(vertexArray, indexArray, vertexCount, indexCount);
		grid.push_back(row);

		// Delete the vertex data used to create the meshes.
		delete[] vertexArray;
	}

	// Output an RGB value according to how high a vertex is.
	vec3 PerlinGrid::calculateRGB(GLfloat height) {
		vec3 colour;

		// High points of the map
		if (height >= colourMap.bounds.x) {
			colour = colourMap.peak;
		}
		else if (height >= colourMap.bounds.y) {
			colour = colourMap.high;
		}
		// Low points of the map
		else if (height >= colourMap.bounds.z) {
			colour = colourMap.mid;
		}
		// Everything lower than the final bound
		else {
			colour = colourMap.low;
		}

		return colour;
	}

	void PerlinGrid::deleteGrid() {
		// Delete the meshes that were made for the grid
		for (size_t t = 0; t < grid.size(); t++) {
			delete grid[t];
		}

		// We do not delete the arrays here because they are deleted during generation.
	}

}