#include "FPSCounter.h"

namespace Engine {
	FPSCounter::FPSCounter(GLdouble initTime, GLdouble minInterval, Window* theWindow) :
		previousTime(initTime), minInterval(minInterval), theWindow(theWindow), title(theWindow->getTitle()),
		fps(0), frameCount(0) {}


	// Decide whether the FPS should be calculated, depending on time elapsed since last calculation
	// and update the title of the window if required.
	void FPSCounter::update() {
		GLdouble now = glfwGetTime();
		GLdouble deltaTime = now - previousTime;

		if (deltaTime > minInterval) {
			// Calculate the fps
			fps = frameCount / deltaTime;

			// Set decimal place count to 2
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << fps;
			std::string preciseFps = ss.str();

			// Update the window title
			std::string newTitle = title + " | FPS: " + preciseFps;
			theWindow->setTitle(newTitle);

			// Clear the accumulated frame count
			frameCount = 0;

			// Update the previous time, to be used on the next call to update.
			previousTime = now;
		}
		else {
			// Increment the number of frames (representing rendering loops) seen since the last FPS calculation.
			frameCount++;
		}
	}

	// Destructor - breaks link to the window
	FPSCounter::~FPSCounter() {
		if (theWindow != nullptr) theWindow = nullptr;
	}
}