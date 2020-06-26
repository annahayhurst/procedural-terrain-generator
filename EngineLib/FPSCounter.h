#pragma once

/* 
* FPSCounter
* A small helper class for performance monitoring that calculates the frames-per-second (a measure of rendering speed) and appends it
* to the title of the window so we can see how well the program is running.
*
* This class was produced with assistance from: https://r3dux.org/2012/07/a-simple-glfw-fps-counter/, which outlines a single function
* method of accomplishing the same goal. For flexibility, clarity, and consistency with my codebase I adapted this function into a fully fledged
* class. */

#include "Window.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace Engine {
	class FPSCounter {
	public:
		FPSCounter() = delete;
		FPSCounter(GLdouble initTime, GLdouble minInterval, Window* theWindow);

		GLdouble getFPS() { return fps; };

		void update();

		~FPSCounter();

	private:
		Window* window;
		std::string title;
		GLdouble previousTime, minimumInterval, fps;
		int frameCount;
	};

}