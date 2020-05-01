#pragma once
/*
* Mesh
* Allows creation of a collection of edges, vertices and faces according to OpenGL standards.
* Creates fragments and renders them for the scene. Additionally calculates normal values for lighting.
*/

#include <GL/glew.h>
#include <glm/glm.hpp>

using glm::vec3;
using glm::normalize;

namespace Engine {
	enum MeshType {
		TEXTURED, COLOURED
	};

	class Mesh {
	public:
		Mesh(MeshType type);

		void createMesh(GLfloat* vertices, GLuint* indices, GLuint vertexArrayLength, GLuint indexArrayLength);
		void drawMesh();

		GLuint getVAO() { return VAO; };
		GLuint getVBO() { return VBO; };
		GLuint getIBO() { return IBO; };
		MeshType getType() { return type; };

		~Mesh();

	protected:
		/* VAO - Vertex Array Object - defines the type of data a vertex has
		*  VBO - Vertex Buffer Object - contains the vertex array data
		*  IBO - Index Buffer Object - contains indices used with vertices while rendering
		*/
		GLuint VAO, VBO, IBO;
		MeshType type;

		GLsizei vertexCount, indexCount;

		// Stride refers to how many values exist per vertex.
		// Offset refers to how many values must be traversed to reach the first normal value (nx).
		int STRIDE, OFFSET;

		void setNormals(GLfloat* vertexData, GLuint* indexData);
		vec3 calculateNormal(GLfloat* vData, GLuint vertexPositionA, GLuint vertexPositionB, GLuint vertexPositionC);
		void setAttributePointers();
		void clearMesh();


	};
}