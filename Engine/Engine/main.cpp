// main.cpp : Defines the entry point for the console application.
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
	//Renderer Init
	Renderer * renderer = new Renderer();
	renderer->Initialize();

	//register what function to use to check errors
	glfwSetErrorCallback(error_callback);

	//register function to receive key events
	glfwSetKeyCallback(renderer->m_window, key_callback);

	// initialize vertex buffer
	renderer->CreateShaderProgram(
		"C:\\Users\\Zac S\\Documents\\Visual Studio 2017\\Projects\\GameLibraries\\Engine\\Engine\\Shader.vs", 
		"C:\\Users\\Zac S\\Documents\\Visual Studio 2017\\Projects\\GameLibraries\\Engine\\Engine\\Shader.fs"
	);

	//points
	float positionData[] =
	{
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f,  0.8f, 0.0f
	};

	float colorData[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	//create vertex buffers
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), colorData, GL_STATIC_DRAW);

	//create vertex array object
	GLuint vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexBuffer(0, vboHandles[0], 0, sizeof(GL_FLOAT) * 3);
	glBindVertexBuffer(1, vboHandles[1], 0, sizeof(GL_FLOAT) * 3);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	//run until key_callback window should close
	while (!glfwWindowShouldClose(renderer->m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(renderer->m_window);
		glfwPollEvents();
	}

	renderer->Shutdown();
	delete renderer;

    return 0;
}
