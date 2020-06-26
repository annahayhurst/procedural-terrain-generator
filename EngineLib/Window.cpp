#include "Window.h"

namespace Engine {
	// Default constructor
	Window::Window() : width(800), height(600), title("New Window"), dX(0.0), dY(0.0) {
		// initialise the keys array to all false
		for (int i = 0; i < 1024; ++i) {
			keys[i] = 0;
		}
	}

	// Constructor with parameters
	Window::Window(GLuint width, GLuint height, std::string title) : width(width), height(height), title(title), dX(0.0), dY(0.0) {
		// initialise the keys array to all false
		for (int i = 0; i < 1024; ++i) {
			keys[i] = 0;
		}
	}

	// Set up GLFW - allow window to display and be interacted with
	int Window::initialise() {
		// Check GLFW has initialised
		if (!glfwInit()) {
			// If initialisation fails, exit with error message
			// (when glfwInit fails, it automatically handles termination)
			std::cout << "Error initialising GLFW \n";
			return 1;
		}

		// Window properties
		// OpenGL version (3.3)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Set to core GL profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Allow forward compatibility
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// Create window
		mainWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!mainWindow) {
			// If window creation fails, terminate and exit with error message
			std::cout << "Error creating GLFW window \n";
			glfwTerminate();
			return 1;
		}

		// Get buffer size information from main window
		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

		// Set current context to the main window
		glfwMakeContextCurrent(mainWindow);

		// Allow for key/mouse input
		glfwSetKeyCallback(mainWindow, handleKeys);
		glfwSetCursorPosCallback(mainWindow, handleMouse);

		// Lock cursor to window
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// GLEW SETUP
		// Allow modern extension access
		glewExperimental = GL_TRUE;

		// Initialise
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			// Debug - print error produced, destroy window and exit
			std::cout << "Error: " << glewGetErrorString(error) << "\n";
			glfwDestroyWindow(mainWindow);
			glfwTerminate();
			return 1;
		}

		// Allow depth perception for shaders
		glEnable(GL_DEPTH_TEST);

		// Create viewport
		glViewport(0, 0, bufferWidth, bufferHeight);

		// Assert that this class (Window) owns main window
		glfwSetWindowUserPointer(mainWindow, this);

		return 0;
	}

	// Call to glfw to dispose of the window and shut down glfw.
	void Window::destroyWindow() {
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	void Window::hide() {
		glfwHideWindow(mainWindow);
		hidden = true;
	}

	void Window::show() {
		glfwShowWindow(mainWindow);
		hidden = false;
	}

	void Window::setShouldClose(bool state) {
		glfwSetWindowShouldClose(mainWindow, state);
	}

	// Retrieve how much movement has been made on the X axis, reset and return
	GLdouble Window::getDx() {
		GLdouble change = dX;
		dX = 0.0f;
		return change;
	}

	// Retrieve how much movement has been made on the Y axis, reset and return
	GLdouble Window::getDy() {
		GLdouble change = dY;
		dY = 0.0f;
		return change;
	}

	// Detects key presses/depresses. Sets ASCII equivalent in keys[] to true until depressed
	void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
		// Get user pointer from current active GLFW window so it can be converted to a Window object
		Window* activeWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		// If escape key is pressed, exit the program.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		// All other key presses - set flag in correct array entry
		if (key >= 0 && key < 1024) {
			// Press button
			if (action == GLFW_PRESS) {
				activeWindow->keys[key] = true;
			}
			// Depress button
			else if (action == GLFW_RELEASE) {
				activeWindow->keys[key] = false;
			}

		}

	}

	// Detect mouse movement and assign appropriate values to dX/dY and lastX/lastY
	void Window::handleMouse(GLFWwindow* window, GLdouble xPosition, GLdouble yPosition) {
		// Get user pointer from current active GLFW window so it can be converted to a Window object
		Window* activeWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		// At the point where the mouse first moves, initialise variables
		if (activeWindow->mouseHasMoved) {
			activeWindow->lastX = xPosition;
			activeWindow->lastY = yPosition;
			activeWindow->mouseHasMoved = false;
		}

		// Calculate dX and dY
		activeWindow->dX = xPosition - activeWindow->lastX;
		activeWindow->dY = activeWindow->lastY - yPosition; // this is reversed because (yPosition - lastY) would give 'tank controls'

		// Update position values
		activeWindow->lastX = xPosition;
		activeWindow->lastY = yPosition;
	}

	// Update the title of the window by converting the passed string to a const char*
	void Window::setTitle(std::string title) {
		this->title = title;
		glfwSetWindowTitle(mainWindow, title.c_str());
	}

	// Destructor - destroys window and terminates GLFW processes
	Window::~Window() {
		if (mainWindow != nullptr) {
			destroyWindow();
		}
	}

}