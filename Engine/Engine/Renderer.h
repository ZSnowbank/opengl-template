#pragma once
#include "system.h"
#include <GLFW\glfw3.h>
#include <iostream>

class Renderer : System
{
public:
	Renderer();
	~Renderer();

	bool Initialize();
	void Shutdown();
	void Update();

	GLuint CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	GLuint CreateShader(const std::string& shader, GLenum shaderType);

	char * ReadFile(const char * const filename);

	GLFWwindow * m_window;
	//Engine* m_engine;

};

