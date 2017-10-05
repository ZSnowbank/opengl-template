#include "stdafx.h"
#include "Renderer.h"
#include "stdlib.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

bool Renderer::Initialize()
{
	//init glfw
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//set major and minor versions of gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	//create the window pointer
	m_window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//set context
	glfwMakeContextCurrent(m_window);

	//set how often it swaps
	glfwSwapInterval(1);

	return false;
}

void Renderer::ShutDown()
{
	//destroy window and terminate
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
