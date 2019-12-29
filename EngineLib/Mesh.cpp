#include "Mesh.h"
#include <iostream>

namespace Engine {
	// Constructor - initialise variables to 0
	Mesh::Mesh(MeshType type) : VAO(0), VBO(0), IBO(0), indexCount(0), vertexCount(0), type(type) {
		switch (type) {
		case TEXTURED:
			STRIDE = 8;
			OFFSET = 5;
			break;
		case COLOURED: // Coloured meshes do not have s and t texel values.
			STRIDE = 9;
			OFFSET = 6;
			break;
		}
	}

	// Create mesh by binding the appropriate vertex arrays and the VAO, IBO and VBO.
	// End by unbinding everything for next use.
	void Mesh::createMesh(GLfloat* vertices, GLuint* indices, GLuint vertArrayLength, GLuint indArrayLength) {
		indexCount = indArrayLength;
		vertexCount = vertArrayLength / STRIDE; // Total number of values/stride = actual amount of full vertices

		int sizeVert = sizeof(vertices[0]) * vertArrayLength;
		int sizeIdx = sizeof(indices[0]) * indArrayLength;

		// Generate the normals for the primitives to be drawn
		setNormals(vertices, indices);

		// Bind VAO
		glGenVertexArrays(1, &VAO); // 1 buffer, pass VAO by reference to give it a value
		glBindVertexArray(VAO); // assign this VAO to the vertex array

		// Bind IBO
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		// Type of array | how much data | which data | draw type
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIdx, indices, GL_STATIC_DRAW);

		// Bind VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeVert, vertices, GL_STATIC_DRAW);

		// Set attribute pointers for this mesh
		setAttributePointers();

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbind array
		glBindVertexArray(0);
	}

	// Bind the created mesh to the established VAO and draws it
	void Mesh::drawMesh() {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		// Drawing type - indexed, triangular
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	// Remove mesh from buffers/memory
	void Mesh::clearMesh() {
		if (IBO != 0) {
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}

		indexCount = 0;
		vertexCount = 0;
	}

	// Destructor
	Mesh::~Mesh() {
		clearMesh();
	}

	// Calculate (average) normals for the vertex and index data that will be
	// used in this mesh
	void Mesh::setNormals(GLfloat* vData, GLuint* iData) {

		// Loop through index array in sets of 3, examining each set of three indices
		// that will be used to draw a primitive triangle.
		for (GLsizei t = 0; t < indexCount; t += 3) {
			/* Multiply the index value by the stride to get the position of the first
			* vertex co-ordinate that corresponds with that index.
			* e.g. if index is 2, and stride is 8, 2*8=16, so we need the 16th value
			* in the vertex array. Take the set of 3 indices for this row: */
			GLuint i0 = iData[t] * STRIDE, // Access 1st vertex in triangle
				i1 = iData[t + 1] * STRIDE, // Second vertex
				i2 = iData[t + 2] * STRIDE; // Third vertex

			vec3 normal = calculateNormal(vData, i0, i1, i2);

			// Move to the positions in vData where normal values (nx, ny, nz) start
			i0 += OFFSET;
			i1 += OFFSET;
			i2 += OFFSET;

			// Add the values to their appropriate position
			// Normals of first vertex chosen
			vData[i0] = normal.x;
			vData[i0 + 1] = normal.y;
			vData[i0 + 2] = normal.z;
			// Second
			vData[i1] = normal.x;
			vData[i1 + 1] = normal.y;
			vData[i1 + 2] = normal.z;
			// Third
			vData[i2] = normal.x;
			vData[i2 + 1] = normal.y;
			vData[i2 + 2] = normal.z;
		}

		// Modify and re-normalize vertex data
		// It may seem unneccesary to normalize these values again, but it is required - some vertices
		// have their normals calculated for more than one set of indices, and aren't normalised w.r.t. each other anymore.
		for (GLsizei t = 0; t < vertexCount; t++) {
			// The value of t functions like an index value - by using the stride we can skip
			// to the vertex corresponding to that index. Then by adding the offset, we
			// move to its three normal values.
			GLuint pos = (t * STRIDE) + OFFSET;

			// Get the vertex values and normalise them
			vec3 normalVertex = normalize(vec3(vData[pos], vData[pos + 1], vData[pos + 2]));
			// Put the normalised values back in the correct place
			vData[pos] = normalVertex.x; // nx
			vData[pos + 1] = normalVertex.y; // ny
			vData[pos + 2] = normalVertex.z; // nz
		}
	}

	vec3 Mesh::calculateNormal(GLfloat* vData, GLuint a, GLuint b, GLuint c) {
		/* To find the normal:
		* - use indices to make lines from vertices, in the direction of the drawn triangle
		* - calculate the cross product of the 2 lines to find the vector at right angles to the face
		*/

		// Get the other values needed to get the vectors. They are next to each other in the vertex array.
		GLfloat x1 = vData[a], y1 = vData[a + 1], z1 = vData[a + 2],
			x2 = vData[b], y2 = vData[b + 1], z2 = vData[b + 2],
			x3 = vData[c], y3 = vData[c + 1], z3 = vData[c + 2];

		// Normalised cross product of the two lines:
		vec3 norm, line1, line2;

		// The first vector is a line between vertex a and vertex b
		line1 = vec3(x2 - x1, y2 - y1, z2 - z1);

		// The second vector is a line between vertex c and vertex b
		line2 = vec3(x3 - x1, y3 - y1, z3 - z1);

		norm = glm::cross(line2, line1);

		return normalize(norm);
	}

	void Mesh::setAttributePointers() {
		int sizeFloat = sizeof(GLfloat);

		// Pointer 0 - for x, y, z co-ordinates - shared by all mesh types
		// ID/index | number of values | type | is normalised? | how many values to skip (stride) | pointer to first value of this attrib
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeFloat * STRIDE, 0);
		glEnableVertexAttribArray(0);

		switch (type) {
		case TEXTURED:
			// Pointer 1 - for texels (s, t)
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeFloat * STRIDE, (GLvoid*)(sizeFloat * 3));
			glEnableVertexAttribArray(1);
			// Pointer 2 - for normals (nx, ny, nz)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeFloat * STRIDE, (GLvoid*)(sizeFloat * 5));
			glEnableVertexAttribArray(2);
			break;
		case COLOURED:
			// Pointer 1 - for colour info (r, g, b)
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeFloat * STRIDE, (GLvoid*)(sizeFloat * 3));
			glEnableVertexAttribArray(1);
			// Pointer 2 - for normals (nx, ny, nz)
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeFloat * STRIDE, (GLvoid*)(sizeFloat * 6));
			glEnableVertexAttribArray(2);
		}
	}
}