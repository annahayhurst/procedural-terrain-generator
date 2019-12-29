#include "stdafx.h"
#include "Context.h"


Context::Context()  {
	initContext();
}

Context::~Context() {
	destroyContext();
}

void Context::initContext() {
	// OpenGL version (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set to core GL profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	theContext = glfwCreateWindow(640, 480, "Test", NULL, NULL);

	// Get buffer size information from main window
	glfwGetFramebufferSize(theContext, &bufferWidth, &bufferHeight);

	// Set current context to the main window
	glfwMakeContextCurrent(theContext);
	glfwSetInputMode(theContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// GLEW SETUP
	// Allow modern extension access
	glewExperimental = GL_TRUE;

	// Initialise
	glewInit();

	// Allow depth perception for shaders
	glEnable(GL_DEPTH_TEST);

	// Create viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Assert that this class (Window) owns main window
	glfwSetWindowUserPointer(theContext, this);
}

void Context::destroyContext() {
	glfwDestroyWindow(theContext);
	glfwTerminate();
}
