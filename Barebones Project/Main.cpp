#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

const GLint WIDTH = 1024, HEIGHT = 768;

int main()
{
	//- Initialize GLFW -//
	glfwInit();

	//-- Necessary Setups for GLFW --//
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	//-- We allocate and create a pointer to the GLFW Window object --//
	GLFWwindow * mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(mainWindow, &screenWidth, &screenHeight);

	if (nullptr == mainWindow)
	{
		cout << "GLFW Window failed to initialize!" << std::endl;
		glfwTerminate();
		return 1;
	}

	//-- Set the main window to the current context --//
	glfwMakeContextCurrent(mainWindow);

	//-- This set operation indicates that we are utilizing the modern shorthands for GLEW --//
	glewExperimental = GL_TRUE;

	//-- Initialize GLEW to setup the OpenGL Function pointers --//
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return 1;
	}

	//-- Viewport Dimension Setting --//
	glViewport(0, 0, screenWidth, screenHeight);

	//-- Main Program Loop --//
	while (!glfwWindowShouldClose(mainWindow))
	{
		//-- Poll the window for incoming events such as keyboard input or mouse operations --//
		glfwPollEvents();

		//-- Render --//
		//-- Clear the colorbuffer --//
		glClearColor(0.184314f, 0.309804f, 0.184314f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//-- Swap the screen buffers --//
		glfwSwapBuffers(mainWindow);
	}

	//-- Terminate GLFW, clearing any resources allocated by GLFW. --//
	glfwTerminate();

	return 0;
}