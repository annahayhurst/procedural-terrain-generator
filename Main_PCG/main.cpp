#include "Scene.h"
#include "userinterface.h"
#include "loaddialog.h"

using namespace Engine;

void runPCG(int argc, char *argv[]);
void testScene();

// Main method - choose to run the procedural generator (runPCG) or view a sample run of a non-PCG scene (testScene)
// Comment and uncomment as desired.
int main(int argc, char *argv[]) {
	
	runPCG(argc, argv);

	return 0;
}

// Using the procedural generator -
// > The qt GUI is loaded and executed
// > The result from the GUI form is saved and stored (or, if the user cancels, the program exits)
// > Depending on whether the user specified their PC hardware was low-end, scaling, grid size and cell size are set
// > A camera position is calculated from the scale factor and cell size
// > An instance of Scene is created to handle rendering logic and backend setup
// > A PerlinGrid instance is created using the user's chosen options and assigned to the Scene
// > Scene's rendering loop is run
// > Once the rendering window is closed, the form opens again, so the user can create a different output if they'd like.
void runPCG(int argc, char *argv[]) {
	// Set up qt GUI
	QApplication app(argc, argv);
	FormDialog gui;
	LoadDialog loading;

	while (true) {
		std::string path = ".\\..\\EngineLib";
		Scene scene = Scene(path); // initialise scene
		UserInput results;

		// Show the form to the user
		if (gui.exec() == QDialog::Accepted) { // User presses OK and submits their desired parameters.
			results = gui.getUserInput();
		}
		else { // User presses cancel, escape, or clicks the X to exit the GUI.
			return;
		}

		// Show a simple loading screen so the user is aware that the program hasn't crashed.
		loading.show();
		QApplication::processEvents();

		// Select appropriate performance settings
		uint size;
		GLfloat sf = 1.0f, cellSize;
		switch (results.isLowEnd) {
		case true: // Low end performance
			size = 1500;
			cellSize = 0.012f;
			break;
		case false: // High end performance
			size = 3000;
			cellSize = 0.005f;
			break;
		}

		// Set user's choice of biome and time of day
		scene.setTime((TimeType)results.timeChoice);
		scene.setBiome((BiomeType)results.biomeChoice);

		// Create the grid with user's options
		PerlinGrid* grid = new PerlinGrid(size, cellSize, sf, results.seed, results.octave, results.persistence / 100.f, scene.getColourMap());
		grid->setVerticalScale(sf + sf * (results.scale / 100.f));

		scene.setGrid(grid);
		scene.setSceneTitle("Procedural Generator | Seed: " + std::to_string(results.seed));

		loading.hide(); // loading screen no longer needed, as the OpenGL window will open upon call to render

		// Set camera position
		scene.setCameraPosition(vec3(-1.7f, 1.05f + (results.scale / 200.f), 1.04f));
		scene.setCameraAngle(-4, -40);
		
		// Call the rendering loop to run until user closes window
		scene.render();
	}

}
