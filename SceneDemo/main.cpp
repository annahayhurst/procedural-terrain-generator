/*
* Scene Demo
* Demonstrates the capability to add different mesh types to a Scene. Changes settings to
* show customisability. Transforms meshes to show that transformations may be applied.
*
* Console has been left open for this application to demonstrate (hopefully!) a lack of error output.
*/

#include "Scene.h"

using namespace Engine;

void testScene();

int main() {
	
	testScene();
	return 0;
}

void testScene() {
	std::string path = ".\\..\\EngineLib"; // location of engine relative to executable
	Scene s = Scene(path); // create the scene

	// Vertices for the two example pyramid meshes
	GLfloat colourVertices[] = {
		//	x      y      z		r	  g		b		nx	   ny	 nz
		-1.0f, -1.0f, -0.5f,	0.0f, 0.5f,	0.7f,	0.0f, 0.0f, 0.0f,	// bottom left
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,	0.4f,	0.0f, 0.0f, 0.0f,	// point of triangle coming out of the screen
		1.0f, -1.0f, -0.5f,		0.0f, 0.5f,	0.7f,	0.0f, 0.0f, 0.0f,	// bottom right
		0.0f, 1.0f, 0.0f,		0.3f, 0.0f,	0.7f,	0.0f, 0.0f, 0.0f	// top point
	};

	GLfloat textureVertices[] = {
		//	x      y      z		s	  t		 		nx	   ny	 nz
		-1.0f, -1.0f, -0.5f,	0.0f, 0.0f,			0.0f, 0.0f, 0.0f,	// bottom left
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,			0.0f, 0.0f, 0.0f,	// point of triangle coming out of the screen
		1.0f, -1.0f, -0.5f,		1.0f, 0.0f,			0.0f, 0.0f, 0.0f,	// bottom right
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,			0.0f, 0.0f, 0.0f	// top point
	};

	// Indices for the pyramid shapes. Both may use the same array, as they are drawn identically.
	GLuint pyramidIndices[] = {
		1, 0, 3,
		3, 2, 1,
		2, 0, 3,
		0, 1, 2
	};

	// Vertices and indices for a flat floor/base
	GLfloat baseVertices[] = {
		//	x    y    z			s	  t		 			nx	   ny	 nz
		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,				0.0f, 0.0f, 0.0f,	// top left
		-1.0f, 0.0f, 1.0f,		0.0f, 10.0f,			0.0f, 0.0f, 0.0f,	// bottom left
		0.0f, 0.0f, 0.0f,		10.0f, 0.0f,			0.0f, 0.0f, 0.0f,	// top right
		0.0f, 0.0f, 1.0f,		10.0f, 10.0f,			0.0f, 0.0f, 0.0f	// bottom right
	};

	GLuint baseIndices[] = {
		1, 3, 0,
		0, 3, 2
	};

	// Create the meshes
	Mesh* mesh1 = new Mesh(COLOURED);
	mesh1->createMesh(colourVertices, pyramidIndices, 36, 12);

	Mesh* mesh2 = new Mesh(TEXTURED);
	mesh2->createMesh(textureVertices, pyramidIndices, 32, 12);

	Mesh* mesh3 = new Mesh(TEXTURED);
	mesh3->createMesh(baseVertices, baseIndices, 32, 6);

	Texture* t = new Texture();
	t->generateTexture("textures\\checker.png", PNG);

	// Adding the meshes to the scene, to demonstrate the different overloads in action
	s.addColourMesh(mesh1, SHINY, vec3(0.f, 0.f, 0.f));
	s.addTextureMesh(mesh2, DULL, t, vec3(2.5f, 0.f, 0.f), vec3(1.0f, 1.5f, 1.0f), vec4(1.f, 1.0f, 0.f, 90.0f));
	s.addTextureMesh(mesh3, DULL, "textures\\wood.jpg", vec3(10.0f, -2.5f, -10.0f), vec3(25.0f, 1.0f, 25.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f));

	// Setting other scene properties
	s.setSceneTitle("Add Mesh Test");
	s.setTime(EVENING);
	s.setBiome(GRASSLAND);

	// Point the camera at the drawn meshes
	s.setCameraPosition(vec3(1.75f, 1.62f, 11.0f));
	s.setCameraAngle(-12, -89);

	s.render();
}
