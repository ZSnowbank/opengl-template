#include "stdafx.h"
#include "renderer.h"
#include <iostream>
#include <fstream>

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//create the window pointer
	m_window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//set context
	glfwMakeContextCurrent(m_window);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{ 
		return false; 
	}

	//set how often it swaps
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return true;
}

void Renderer::Shutdown()
{
	//destroy window and terminate
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Renderer::Update()
{

}

GLuint Renderer::CreateShaderProgram(const std::string & vertexShaderFilename, const std::string & fragmentShaderFilename)
{
	GLuint vertexShader = CreateShader(vertexShaderFilename, GL_VERTEX_SHADER);
	GLuint fragmentShader = CreateShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	if (program == 0)
	{
		std::cerr << "Error creating program.\n";
		return 0;
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "Failed to link shader program.\n";

		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength)
		{
			char* log = new char[logLength];
			GLsizei written;
			glGetProgramInfoLog(program, logLength, &written, log);

			std::cerr << "Program log: " << log << std::endl;

			delete[] log;
		}
	}
	else
	{
		glUseProgram(program);
	}

	return program;
}

GLuint Renderer::CreateShader(const std::string & shaderFilename, GLenum shaderType)
{
	// read shader file
	std::string shaderText = ReadFile(shaderFilename.c_str());
	const char* shaderString = shaderText.c_str();

	// vertex shader
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << "Error creating shader: " << shaderFilename << std::endl;
		return 0;
	}

	glShaderSource(shader, 1, &shaderString, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "Shader compilation failed: " << shaderFilename << std::endl;
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength)
		{
			char* log = new char[logLength];
			GLsizei written;
			glGetShaderInfoLog(shader, logLength, &written, log);

			std::cerr << "Shader log: " << log << std::endl;

			delete[] log;
		}
	}

	return shader;
}

char * Renderer::ReadFile(const char * const filename)
{
	std::ifstream stream(filename);
	std::filebuf* pbuf = stream.rdbuf();

	auto size = pbuf->pubseekoff(0, stream.end);
	long buflen = 1 + static_cast<long> (size);

	std::cout << "FILE READ - " << filename << " : length " << buflen - 1 << '\n';
	if (buflen <= 0)
	{
		throw std::exception("File had a length of 0 or less");
		return nullptr;
	}

	char* fileString = new char[buflen] {0};

	pbuf->pubseekpos(0);

	pbuf->sgetn(fileString, buflen);

	stream.close();

	//std::cout << filename << " : " << fileString;

	return fileString;
}
