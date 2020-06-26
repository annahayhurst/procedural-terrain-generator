#include "Scene.h"

namespace Engine {
	// Default constructor
	Scene::Scene(std::string enginePath) : title("New Scene"), engineLocation(enginePath) {
		initialise();
		setBiome(MOUNTAINS);
		setTime(MORNING);
		camera = Camera(vec3(5.f, 5.f, 0.f), vec3(0.f, 1.f, 0.f), -90.0f, 0.0f, 1.f, 1.f);
	}

	// Constructor taking a biome type and potentially a camera position, although the latter is optional
	Scene::Scene(std::string enginePath, BiomeType biome, TimeType time, vec3 cameraPosition) 
		: title("New Scene"), engineLocation(enginePath) {
		initialise();
		setBiome(biome);
		setTime(time);
		camera = Camera(cameraPosition, vec3(0.f, 1.f, 0.f), -90.0f, 0.0f, 2.5f, 2.5f);
	}

	// Initialise the key components of the scene that MUST be in place for any other function to run.
	void Scene::initialise() {
		// Initialise storage vectors
		shaders = vector<Shader*>();
		meshes = vector<MeshInfo*>();
		materials = vector<Material*>();

		// Create the window and initialise so all libraries are prepared
		window = Window(1366, 768, title);
		window.initialise();
		window.hide();
		windowOpen = true;

		// Add materials
		materials.push_back(new Material(1.0f, 64)); // shiny
		materials.push_back(new Material(0.4f, 16)); // dull
		materials.push_back(new Material(0.2f, 8)); // extra dull, for perlin grid

		// Add shaders
		createShaders();

	}

	// Ensure that a combination of biome and lighting 'works' - i.e. that the reflection
	// of light on a certain colour isn't blinding, or isn't too dark.
	void Scene::checkCompatibility() {
		// Correcting overly bright combinations
		if ((biome == DESERT || biome == GLACIER) &&
			(time == MORNING || time == MIDDAY || time == NONE)) {
			light.setAmbientIntensity(0.5f);
			light.setDiffuseIntensity(0.6f);
		}

		// Correcting overly dark combinations
		if ((biome == GRASSLAND || biome == MOUNTAINS) &&
			(time == EVENING || time == MIDNIGHT)) {
			light.setAmbientIntensity(0.75f);
			light.setDiffuseIntensity(0.85f);
		}

	}

	// Create three key shaders and add them to their data structure
	void Scene::createShaders() {
		Shader* skyboxShader = new Shader();
		std::string skyboxVertexPath = makeFullPath("\\shaders\\skyboxVertex.shader");
		std::string skyboxFragmentPath = makeFullPath("\\shaders\\skyboxFragment.shader");
		skyboxShader->createShaders(skyboxVertexPath.c_str(), skyboxFragmentPath.c_str());
		shaders.push_back(skyboxShader);

		Shader* colourShader = new Shader();
		std::string colourVertexPath = makeFullPath("\\shaders\\colourVertex.shader");
		std::string colourFragmentPath = makeFullPath("\\shaders\\colourFragment.shader");
		colourShader->createShaders(colourVertexPath.c_str(), colourFragmentPath.c_str());
		shaders.push_back(colourShader);

		Shader* textureShader = new Shader();
		std::string textureVertexPath = makeFullPath("\\shaders\\textureVertex.shader");
		std::string textureFragmentPath = makeFullPath("\\shaders\\textureFragment.shader");
		textureShader->createShaders(textureVertexPath.c_str(), textureFragmentPath.c_str());
		shaders.push_back(textureShader);
	}

	// Initialise final variables and run the rendering loop until the main window must close.
	void Scene::render() {
		// Failsafe condition - check if window is open. 
		// If not, something went wrong during initialisation and it isn't safe to run the rest of render()
		if (!windowOpen) {
			std::cerr << "Could not render the scene - main window is not open.\n";
			return;
		}

		checkCompatibility();

		// Add fps counter, bound to the main window
		FPSCounter fps = FPSCounter(glfwGetTime(), 1.0, &window);

		// Create time measurements
		GLfloat deltaTime = .0f, lastTime = .0f;

		// Set projection
		// FOV (y-axis), aspect ratio, near plane position, far plane position
		projection = glm::perspective(glm::radians(40.0f), (GLfloat)(window.getBufferWidth() / window.getBufferHeight()), 0.1f, 20000.f);

		// Adjust the camera speed to be able to navigate across a large grid appropriately
		if (gridExists) this->camera.setMovementSpeed(grid->getHorizontalScale() / 1.5f + grid->getVerticalScale() / 2.5f);
		//if (gridExists) this->camera.setMovementSpeed(0.5f);

		// For as long as the main window isn't closing -
		while (!window.shouldClose()) {
			// Current time
			GLfloat now = (GLfloat)glfwGetTime();
			// Time elapsed since last loop
			deltaTime = now - lastTime;
			lastTime = now;

			// Update the fps counter
			fps.update();

			// Listen for user interactions
			glfwPollEvents();

			// Handle/map key presses
			camera.keyControl(window.getKeys(), deltaTime);
			camera.mouseControl(window.getDx(), window.getDy());

			// Set view
			view = camera.getViewMatrix();

			// Update how the scene looks
			renderMap();
			if (gridExists) renderGrid();
			if (!meshes.empty()) {
				renderColouredMeshes();
				renderTexturedMeshes();
			}

			// Finally, render the skybox if a time of day is set. This is done last because it 'wraps' around the rest of the meshes
			if (time != NONE) renderSkybox();

			if (window.isHidden()) window.show();

			// Exchanges rendered scene with visible scene
			window.swapBuffers();
		}

		// Clear out shaders for safety
		Shader::clearShaders();

		window.setShouldClose(false);

		// Hide window in case it will be needed later
		window.hide();
	}

	// Interface for creating a colour mesh and adding it to the scene
	bool Scene::addColourMesh(Mesh* mesh, MaterialType materialType, vec3 position) {
		// Check type matches
		if (mesh->getType() != COLOURED) {
			std::cerr << "Cannot add a TEXTURED mesh as a colour mesh.\n";
			return false;
		}

		// Create info for this mesh and store
		MeshInfo* meshInfo = new MeshInfo{ mesh, nullptr, materialType, position, vec3(1.0f, 1.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f) };
		meshes.push_back(meshInfo);

		return true;
	}

	// Interface for creating a colour mesh and adding it to the scene (overload)
	bool Scene::addColourMesh(Mesh* mesh, MaterialType materialType, vec3 position, vec3 scale, vec4 rotation) {
		// Check type matches
		if (mesh->getType() != COLOURED) {
			std::cerr << "Cannot add a TEXTURED mesh as a colour mesh.\n";
			return false;
		}

		// Create info for this mesh and store
		MeshInfo* meshInfo = new MeshInfo{ mesh, nullptr, materialType, position, scale, rotation };
		meshes.push_back(meshInfo);

		return true;
	}

	// Interface for creating a textured mesh and adding it to the scene
	bool Scene::addTextureMesh(Mesh* mesh, MaterialType materialType, std::string texturePath, vec3 position) {
		// Check filepath exists
		if (!verifyTexturePath(texturePath)) {
			return false;
		}
		else {
			Texture* texture = new Texture();
			if (texturePath.find(".jpg")) {
				texture->generateTexture(texturePath.c_str(), JPG);
			}
			else if (texturePath.find(".png")) {
				texture->generateTexture(texturePath.c_str(), PNG);
			}

			MeshInfo* meshInfo = new MeshInfo{ mesh, texture, materialType, position, vec3(1.f, 1.f, 1.f), vec4(0.f, 1.f, 0.f, 0.f) };
			meshes.push_back(meshInfo);
		}

		return true;
	}

	// Interface for creating a textured mesh and adding it to the scene (overload)
	bool Scene::addTextureMesh(Mesh* mesh, MaterialType materialType, std::string texturePath, vec3 position, vec3 scale, vec4 rotation) {

		if (!verifyTexturePath(texturePath)) {
			return false;
		}
		else {
			Texture* texture = new Texture();
			if (texturePath.find(".jpg")) {
				texture->generateTexture(texturePath.c_str(), JPG);
			}
			else if (texturePath.find(".png")) {
				texture->generateTexture(texturePath.c_str(), PNG);
			}
			MeshInfo* meshInfo = new MeshInfo{ mesh, texture, materialType, position, scale, rotation };
			meshes.push_back(meshInfo);
		}


		return true;
	}

	bool Scene::addTextureMesh(Mesh* mesh, MaterialType materialType, Texture* texture, vec3 position) {
		// Check correct type
		if (mesh->getType() != TEXTURED) {
			std::cerr << "Cannot add a COLOURED mesh as a texture mesh.\n";
			return false;
		}

		MeshInfo* meshInfo = new MeshInfo{ mesh, texture, materialType, position, vec3(1.f, 1.f, 1.f), vec4(0.f, 1.f, 0.f, 0.f) };
		meshes.push_back(meshInfo);

		return true;
	}

	bool Scene::addTextureMesh(Mesh* mesh, MaterialType materialType, Texture* texture, vec3 position, vec3 scale, vec4 rotation) {
		// Check correct type
		if (mesh->getType() != TEXTURED) {
			std::cerr << "Cannot add a COLOURED mesh as a texture mesh.\n";
			return false;
		}

		MeshInfo* meshInfo = new MeshInfo{ mesh, texture, materialType, position, scale, rotation };
		meshes.push_back(meshInfo);

		return true;
	}

	// Interface for creating a grid and adding it to the scene
	bool Scene::addGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, uint seed) {
		if (cellSize < 0 || scaleFactor < 0) {
			std::cerr << "Cannot set a negative size or scale.\n";
			return false;
		}
		else if (cellSize == 0) {
			std::cerr << "Cannot create an empty grid.\n";
			return false;
		}

		Perlin perlin = Perlin(seed);
		grid = new PerlinGrid(size, cellSize, scaleFactor, perlin);

		gridExists = true;

		return true;
	}

	// Interface for creating a grid and adding it to the scene (overload)
	bool Scene::addGrid(GLuint size, GLfloat cellSize, GLfloat scaleFactor, Perlin perlin) {
		if (cellSize < 0 || scaleFactor < 0) {
			std::cerr << "Cannot set a negative size or scale.\n";
			return false;
		}
		else if (cellSize == 0) {
			std::cerr << "Cannot create an empty grid.\n";
			return false;
		}

		grid = new PerlinGrid(size, cellSize, scaleFactor, perlin);
		gridExists = true;

		return true;
	}

	// Update position of main camera
	bool Scene::setCameraPosition(vec3 position) {
		camera.setPosition(position);
		return true;
	}

	// Update angle of main camera, checking that pitch and yaw angles are safe to set
	bool Scene::setCameraAngle(GLfloat pitch, GLfloat yaw) {
		if (pitch > 90.f || pitch < -90.f || yaw > 90.f || yaw < -90.f) {
			std::cerr << "Camera angles must be between -90 and 90 degrees.\n";
			return false;
		}

		camera.setPitch(pitch);
		camera.setYaw(yaw);
		return true;
	}

	// Change light colour, checking that rgb values are valid
	bool Scene::setLightColour(vec3 colour) {
		if (colour.r > 1.0f || colour.g > 1.0f || colour.b > 1.0f) {
			std::cerr << "RGB values must be equal to or less than 1.0.\n";
			return false;
		}

		if (colour.r < 0.0f || colour.g < 0.0f || colour.b < 0.0f) {
			std::cerr << "RGB values must be greater than 0.0.\n";
			return false;
		}

		light.setColour(colour);
		return true;
	}

	// Update light intensity, checking it is within a valid range.
	bool Scene::setLightIntensity(GLfloat intensity) {
		if (intensity < 0.0f || intensity > 1.0f) {
			std::cerr << "Light intensity must be between 0.0 and 1.0.\n";
			return false;
		}

		light.setAmbientIntensity(intensity);
		light.setDiffuseIntensity(intensity);
		return true;
	}

	// Replace the grid (if it exists) with a pointer to a new one 
	bool Scene::setGrid(PerlinGrid* grid) {
		if (grid == nullptr) {
			std::cerr << "Cannot assign a nullpointer to the grid.\n";
			return false;
		}

		if (gridExists) {
			deleteGrid();
		}

		grid = grid;
		gridExists = true;

		return true;
	}

	// Using the selected biome, construct the appropriate colour map.
	bool Scene::setBiome(BiomeType biome) {
		vector<std::string> faces;

		switch (biome) {
		case GRASSLAND:
			cmap.bounds = vec3(0.5f, 0.05f, -0.4f);
			cmap.peak = vec3(0.49f, 0.91f, 0.38f);
			cmap.high = vec3(0.29f, 0.69f, 0.16f);
			cmap.mid = vec3(0.18f, 0.5f, 0.08f);
			cmap.low = vec3(0.38f, 0.27f, 0.19f);
			break;

		case MOUNTAINS:
			cmap.bounds = vec3(0.42f, 0.05f, -0.2f);
			cmap.peak = vec3(0.9f, 0.9f, 0.9f);
			cmap.high = vec3(0.5f, 0.5f, 0.5f);
			cmap.mid = vec3(0.09f, 0.43f, 0.15f);
			cmap.low = vec3(0.16f, 0.25f, 0.58f);
			break;

		case DESERT:
			cmap.bounds = vec3(0.7f, -0.2f, -0.5f);
			cmap.peak = vec3(0.58f, 0.58f, 0.14f);
			cmap.high = vec3(0.92f, 0.89f, 0.69f);
			cmap.mid = vec3(0.87f, 0.82f, 0.51f);
			cmap.low = vec3(0.18f, 0.76f, 0.83f);
			break;

		case GLACIER:
			cmap.bounds = vec3(0.075f, 0.02f, -0.1f);
			cmap.peak = vec3(1.f, 1.f, 1.f);
			cmap.high = vec3(170.f / 255.f, 170.f / 255.f, 170.f / 255.f);
			cmap.mid = vec3(170.f / 255.f, 242.f / 255.f, 247.f / 233.f);
			cmap.low = vec3(143.f / 255.f, 213.f / 255.f, 219.f / 255.f);
			break;

		case HEATMAP:
			cmap.bounds = vec3(0.35f, 0.05f, -0.2f);
			cmap.peak = vec3(0.93f, 0.99f, 0.2f);
			cmap.high = vec3(0.8f, 0.54f, 0.1f);
			cmap.mid = vec3(0.8f, 0.1f, 0.1f);
			cmap.low = vec3(0.6f, 0.2f, 0.73f);
			break;

		default:
			std::cerr << "Could not assign this biome type.\n";
			return false;
		}

		this->biome = biome;

		return true;
	}

	// Set the time of day, with its corresponding skybox and light colour.
	bool Scene::setTime(TimeType time) {
		vector<std::string> faces;
		this->time = time;

		switch (time) {
		case MORNING:
			faces = {
			makeFullPath("\\skyboxes\\morning\\right.bmp"), makeFullPath("\\skyboxes\\morning\\left.bmp"), makeFullPath("\\skyboxes\\morning\\top.bmp"),
			makeFullPath("\\skyboxes\\morning\\bottom.bmp"),makeFullPath("\\skyboxes\\morning\\front.bmp"),makeFullPath("\\skyboxes\\morning\\back.bmp")
			};

			cmap.lightColour = vec3(1.0f, 1.0f, 0.85f);
			cmap.lightDirection = vec3(-0.51f, -1.0f, 0.59f);
			break;

		case MIDDAY:
			faces = {
			makeFullPath("\\skyboxes\\midday\\right.bmp"), makeFullPath("\\skyboxes\\midday\\left.bmp"), makeFullPath("\\skyboxes\\midday\\top.bmp"),
			makeFullPath("\\skyboxes\\midday\\bottom.bmp"),makeFullPath("\\skyboxes\\midday\\front.bmp"),makeFullPath("\\skyboxes\\midday\\back.bmp")
			};

			cmap.lightColour = vec3(1.0f, 1.0f, 1.0f);
			cmap.lightDirection = vec3(0.0f, -1.0f, 0.0f);
			break;

		case EVENING:
			faces = {
			makeFullPath("\\skyboxes\\evening\\right.bmp"), makeFullPath("\\skyboxes\\evening\\left.bmp"), makeFullPath("\\skyboxes\\evening\\top.bmp"),
			makeFullPath("\\skyboxes\\evening\\bottom.bmp"),makeFullPath("\\skyboxes\\evening\\front.bmp"),makeFullPath("\\skyboxes\\evening\\back.bmp")
			};

			cmap.lightColour = vec3(0.68f, 0.52f, 0.22f);
			cmap.lightDirection = vec3(0.69f, -0.34f, 0.64f);
			break;

		case MIDNIGHT:
			faces = {
			makeFullPath("\\skyboxes\\midnight\\right.png"), makeFullPath("\\skyboxes\\midnight\\left.png"), makeFullPath("\\skyboxes\\midnight\\top.png"),
			makeFullPath("\\skyboxes\\midnight\\bottom.png"),makeFullPath("\\skyboxes\\midnight\\front.png"),makeFullPath("\\skyboxes\\midnight\\back.png")
			};

			cmap.lightColour = vec3(0.28f, 0.32f, 0.46f);
			cmap.lightDirection = vec3(0.0f, -1.0f, -0.0f);
			break;

		case NONE:
			cmap.lightColour = vec3(1.0f, 1.0f, 1.0f);
			cmap.lightDirection = vec3(0.0f, -1.f, 0.0f);
			break;

		default:
			std::cerr << "Could not assign this time type.\n";
			return false;
		}

		// Create and load the skybox faces from the chosen file locations
		if (time != NONE) {
			skybox = Skybox();
			skybox.loadSkybox(faces);
		}

		// Update light colour and direction according to the colour map
		light = DirectionalLight(cmap.lightColour, cmap.lightDirection, 0.6f, 0.8f);
		//light = DirectionalLight(cmap.lightColour, cmap.lightDir, 1.0f, 1.0f);
		return true;
	}

	// Sets a title for the scene by modifying the main window's title (as long as it opened successfully)
	bool Scene::setSceneTitle(std::string title) {
		if (!windowOpen) {
			std::cerr << "Could not assign title; main window was not open.\n";
			return false;
		}

		title = title;
		window.setTitle(title);
		return true;
	}

	bool Scene::setCustomColourMap(ColourMap colourMap){
		cmap = colourMap;
		biome = CUSTOM_B;
		return true;
	}

	bool Scene::setCustomSkybox(Skybox skybox) {
		this->skybox = skybox;
		time = CUSTOM_T;
		return true;
	}

	bool Scene::setCustomSkybox(vector<std::string> faces) {
		if (faces.size() != 6) {
			std::cerr << "Number of faces provided for skybox must be 6.\n";
		}

		skybox = Skybox();
		skybox.loadSkybox(faces);
		time = CUSTOM_T;

		return true;
	}

	// Run all necessary operations involving shaders, meshes, lighting and camera to produce 
	// an updated basic view of the whole scene
	void Scene::renderMap() {
		// Update the projection and view locations so we can send appropriate values to the shader.
		shaders[1]->useShaders();
		uProjection = shaders[1]->getProjectionUL();
		uView = shaders[1]->getViewUL();

		// Set user's perspective ((0,0) refers to the bottom left corner of the window's co-ordinates)
		glViewport(0, 0, 1366, 768);

		// Clear the window
		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update projection and view uniforms
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));
		camera.updateUniformPosition(shaders[1]);
	}

	// Render the grid object using the colour shader
	void Scene::renderGrid() {
		shaders[1]->useShaders();

		uModel = shaders[1]->getModelUL();
		uProjection = shaders[1]->getProjectionUL();
		uView = shaders[1]->getViewUL();

		camera.updateUniformPosition(shaders[1]);
		light.useLight(shaders[1]);

		// Update projection and depthlessView uniforms
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));

		// The model is a 4D matrix modified to be used with each mesh
		mat4 model = mat4(1.0f);
		// Set scale according to the grids scale attributes
		model = glm::scale(model, vec3(grid->getHorizontalScale(), grid->getVerticalScale(), grid->getHorizontalScale()));

		materials[2]->useMaterial(shaders[1]);
		glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model)); // Link uniforms to model (4fv = 4 floats in a vector)

		grid->render();
	}

	// Render the skybox at a seemingly infinite distance by modifiying the view matrix and disabling depth parsing
	// Adapted from LearnOpenGL (see Skybox.h)
	void Scene::renderSkybox() {
		glDepthFunc(GL_LEQUAL);

		// Remove translation properties of view matrix by converting to mat3 and then back
		mat4 depthlessView = mat4(glm::mat3(camera.getViewMatrix()));

		shaders[0]->useShaders();
		uProjection = shaders[0]->getProjectionUL();
		uView = shaders[0]->getViewUL();

		glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(depthlessView));
		camera.updateUniformPosition(shaders[0]);

		skybox.drawSkybox();

		glDepthFunc(GL_LESS);
	}

	// Render any textured meshes with the texture shader by only working with meshes that have an existing texture object bound to them
	void Scene::renderTexturedMeshes() {
		shaders[2]->useShaders();

		uModel = shaders[2]->getModelUL();
		uProjection = shaders[2]->getProjectionUL();
		uView = shaders[2]->getViewUL();

		camera.updateUniformPosition(shaders[2]);
		light.useLight(shaders[2]);

		glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));

		for (MeshInfo* meshInfo : meshes) {
			if (meshInfo->texture != nullptr) {
				mat4 model = mat4(1.0f);
				model = glm::translate(model, meshInfo->position);
				model = glm::scale(model, meshInfo->scale);
				if (meshInfo->rotation.w > 0) model = glm::rotate(model, glm::radians(meshInfo->rotation.w), vec3(meshInfo->rotation.x, meshInfo->rotation.y, meshInfo->rotation.z));

				meshInfo->texture->useTexture();

				materials[meshInfo->materialType]->useMaterial(shaders[2]);
				glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model));

				meshInfo->theMesh->drawMesh();
			}
		}

	}

	// Render any coloured meshes with the colour shader by only working with meshes that have a nullptr texture
	void Scene::renderColouredMeshes() {
		shaders[1]->useShaders();

		uModel = shaders[1]->getModelUL();
		uProjection = shaders[1]->getProjectionUL();
		uView = shaders[1]->getViewUL();

		camera.updateUniformPosition(shaders[1]);
		view = camera.getViewMatrix();
		light.useLight(shaders[1]);

		glUniformMatrix4fv(uProjection, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));

		for (MeshInfo* meshInfo : meshes) {
			if (meshInfo->texture == nullptr) {
				mat4 model = mat4(1.0f);
				model = glm::translate(model, meshInfo->position);
				model = glm::scale(model, meshInfo->scale);
				if (meshInfo->rotation.w > 0) model = glm::rotate(model, glm::radians(meshInfo->rotation.w), vec3(meshInfo->rotation.x, meshInfo->rotation.y, meshInfo->rotation.z));

				materials[meshInfo->materialType]->useMaterial(shaders[1]);
				glUniformMatrix4fv(uModel, 1, GL_FALSE, value_ptr(model));

				meshInfo->theMesh->drawMesh();
			}
		}
	}

	// Check the array sizes and filepath of a potential texture mesh to ensure it is a valid construct
	bool Scene::verifyTexturePath(std::string texturePath) {
		if (texturePath == "") {
			std::cerr << "Cannot supply empty file path to texture image.\n";
			return false;
		}

		Texture texture;
		if (texturePath.find(".jpg")) {
			texture = Texture();
			if (!(texture.generateTexture(texturePath.c_str(), JPG))) {
				std::cerr << "Could not produce mesh with this texture.";
				return false;
			}
		}
		else if (texturePath.find(".png")) {
			texture = Texture();
			if (!(texture.generateTexture(texturePath.c_str(), PNG))) {
				std::cerr << "Could not produce mesh with this texture.";
				return false;
			}
		}
		else {
			std::cerr << "Texture file formats must be PNG or JPG, could not produce textured mesh from "
				<< texturePath << ".\n";
			return false;
		}

		return true;
	}

	std::string Scene::makeFullPath(std::string path) {
		std::string newPath = engineLocation;
		return newPath.append(path).c_str();
	}

	// Delete the PerlinGrid object bound to this instance and remove the dangling pointer
	void Scene::deleteGrid() {
		delete grid;
		grid = nullptr;
	}

	// Destructor
	Scene::~Scene() {
		if (gridExists) deleteGrid();

		for (MeshInfo* meshInfo : meshes) {
			delete meshInfo->theMesh;
			if (meshInfo->texture != nullptr) delete meshInfo->texture;

			delete meshInfo;
			meshInfo = nullptr;
		}

		for (Shader* shader : shaders) delete shader;

		for (Material* material : materials) delete material;
	}

}