#pragma once

class Context {
public:
	Context();
	~Context();

	void initContext();
	void destroyContext();

private:
	GLFWwindow* theContext;
	int bufferWidth, bufferHeight;

};

