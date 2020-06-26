#pragma once

/*
* Scene
* This class provides an interface through which we can set up and render an OpenGL scene using the
* engine I have created, without manually making calls to OpenGL logic and functions. It has been designed
* so that a potential future user can set up their own 3D scene (with or without a procedurally generated grid)
* without having to learn the technicalites of OpenGL. It also aids code reusability and removes the need to
* hardcode a specific scene in main.cpp.
*
* A few helper enums and structs are implemented to simplify the process of scene creation further.
*
* A small section on how to use Scene will be included in the final README file.
*/

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Window.h"
#include "Camera.h"
#include "ColourMap.h"
#include "DirectionalLight.h"
#include "FPSCounter.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "Shader.h"
#include "Skybox.h"
#include "Texture.h"
#include "Perlin.h"
#include "PerlinGrid.h"

namespace Engine {
	// A helper enum to choose between two material types
	enum MaterialType {
		SHINY, DULL
	};

	// A helper enum to choose between the 5 implemented biome types (affecting the colour scheme) and a custom type
	enum BiomeType {
		GRASSLAND, MOUNTAINS, DESERT, GLACIER, HEATMAP, CUSTOM_B
	};

	// A helper enum to choose the time of day (affecting lighting and the skybox) and a custom type
	enum TimeType {
		MORNING, MIDDAY, EVENING, MIDNIGHT, NONE, CUSTOM_T
	};

	// Couples a mesh with relevant information about its properties so the user doesn't have to manually
	// provide these when they want to render it.
	struct MeshInfo {
		Mesh* theMesh;
		Texture* texture;
		MaterialType materialType;
		vec3 position, scale;
		vec4 rotation; // this is a vec4 to store the angle AND the three axes
	};

	class Scene {
	public:
		Scene(std::string enginePath);
		Scene(std::string enginePath, BiomeType biome, TimeType time, vec3 cameraPosition = vec3(0.0f, 0.0f, 0.0f));
		~Scene();

		bool addColourMesh(Mesh* mesh, MaterialType materialType, vec3 position = vec3(0.f, 0.f, 0.f));
		bool addColourMesh(Mesh* mesh, MaterialType materialType, vec3 position, vec3 scale, vec4 rotation);
		bool addTextureMesh(Mesh* mesh, MaterialType materialType, std::string texturePath, vec3 position = vec3(0.f, 0.f, 0.f));
		bool addTextureMesh(Mesh* mesh, MaterialType materialType, std::string texturePath, vec3 position, vec3 scale, vec4 rotation);
		bool addTextureMesh(Mesh* mesh, MaterialType materialType, Texture* texture, vec3 position = vec3(0.f, 0.f, 0.f));
		bool addTextureMesh(Mesh* mesh, MaterialType materialType, Texture* texture, vec3 position, vec3 scale, vec4 rotation);
		bool addGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, uint seed);
		bool addGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, Perlin perlin);

		bool setCameraPosition(vec3 pos);
		bool setCameraAngle(GLfloat pitch, GLfloat yaw);

		bool setLightColour(vec3 colour);
		bool setLightIntensity(GLfloat intensity);

		bool setGrid(PerlinGrid* grid);
		bool setBiome(BiomeType biome);
		bool setTime(TimeType time);
		bool setSceneTitle(std::string title);

		bool setCustomColourMap(ColourMap colourMap);
		bool setCustomSkybox(Skybox skybox);
		bool setCustomSkybox(vector<std::string> faces);

		ColourMap getColourMap() { return cmap; };
		Skybox getSkybox() { return skybox; };
		std::string getTitle() { return title; };
		std::string getEnginePath() { return engineLocation; };
		PerlinGrid* getGrid() { return grid; };

		void render();

	private:
		// Path to engine
		std::string engineLocation;

		// Objects the scene requires exactly one (or zero) of
		Window window;

		Skybox skybox;
		ColourMap cmap;

		Camera camera;
		DirectionalLight light;

		TimeType time;
		BiomeType biome;

		std::string title;

		// Uniforms, perspectives
		GLuint uModel = 0, uProjection = 0, uView = 0;
		mat4 projection, view;

		// The grid, and a flag indicating whether it exists
		PerlinGrid* grid;
		bool gridExists = false;
		// A flag checking if the window is open
		bool windowOpen = false;

		// Storage for objects the scene may require multiple of
		vector<Shader*> shaders;
		vector<MeshInfo*> meshes;
		vector<Material*> materials;

		// Private functions
		void initialise();
		void checkCompatibility();
		void createShaders();
		void renderMap();
		void renderGrid();
		void renderSkybox();
		void renderTexturedMeshes();
		void renderColouredMeshes();

		bool verifyTexturePath(std::string texturePath);

		std::string makeFullPath(std::string path);

		void deleteGrid();
	};

}