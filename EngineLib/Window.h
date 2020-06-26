#pragma once
/*
* Window
* Using GLFW, creates an active window that the user can interact with using mouse/keyboard,
* and can see the rendered scene within. WASD controls camera movement, the mouse can be used
* for rotating the camera, and escape causes the program to exit. The mouse is locked to this
* window as long as this program is running in the foreground.
*/

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {
	class Window {
	public:
		Window();
		Window(GLuint width, GLuint height, std::string title);

		int initialise();
		void swapBuffers() { glfwSwapBuffers(mainWindow); }
		bool shouldClose() { return glfwWindowShouldClose(mainWindow); }
		bool isHidden() { return hidden; }
		void destroyWindow();

		void hide();
		void show();

		void setShouldClose(bool state);

		GLdouble getDx();
		GLdouble getDy();

		bool* getKeys() { return keys; }
		GLint getWidth() { return width; }
		GLint getHeight() { return height; }
		GLint getBufferWidth() { return bufferWidth; }
		GLint getBufferHeight() { return bufferHeight; }

		std::string getTitle() { return title; }
		void setTitle(std::string title);

		~Window();

	private:
		GLFWwindow* mainWindow;

		std::string title;

		GLuint width, height;
		int bufferWidth, bufferHeight;
		GLdouble dX, dY, lastX, lastY;

		bool hidden = false;
		bool mouseHasMoved;
		bool keys[1024];

		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, GLdouble xPosition, GLdouble yPosition);
	};

}