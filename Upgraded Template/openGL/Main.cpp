#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL\SOIL.h>

#include "Shader.h"

using namespace std;

//-- Global Defínitions --//
const GLint WIDTH = 1024, HEIGHT = 768;

//-- The main key callback method that allows GLFW to receive and handle user input --//
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

//-- Shader Source Code --//
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.545f, 0.604f, 0.545f, 1.0f);\n"
"}\n\0";

int main()
{
	//-- Initial Definitions Section --//

	//-- Initialization of the Vertex Buffers --//
	GLuint VBO;
	GLuint VAO;

	//--------------------------------//

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

	//-- Compiling Shaders --//
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	//-- Shader Linking  --//
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//-- Delete any residual shaders --//
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//-- Viewport Dimension Setting --//
	glViewport(0, 0, screenWidth, screenHeight);

	//-- Designate the keyCallback Method --//
	glfwSetKeyCallback(mainWindow, keyCallback);


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


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}