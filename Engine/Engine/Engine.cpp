// Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Renderer.h"

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
	//Renderer Init////////////////////////
	
	Renderer renderer;
	renderer.Initialize();

	///////////////////////////////////////

	//register what function to use to check errors
	glfwSetErrorCallback(error_callback);

	//register function to receive key events
	glfwSetKeyCallback(renderer.m_window, key_callback);

	//run until key_callback window should close
	while (!glfwWindowShouldClose(renderer.m_window))
	{
		glfwSwapBuffers(renderer.m_window);
		glfwPollEvents();
	}

	renderer.ShutDown();

    return 0;
}
