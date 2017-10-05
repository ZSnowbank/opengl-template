// Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "stdlib.h"
#include "GLFW\glfw3.h"

//If an error, print it to stderr
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//If escape key is pressed, set window should close to true
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	//init glfw
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//register what function to use to check errors
	glfwSetErrorCallback(error_callback);

	//set major and minor versions of gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	//create the window pointer
	GLFWwindow* window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//register function to receive key events
	glfwSetKeyCallback(window, key_callback);

	//set context
	glfwMakeContextCurrent(window);

	//set how often it swaps
	glfwSwapInterval(1);

	//run until key_callback window should close
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

    return 0;
}
