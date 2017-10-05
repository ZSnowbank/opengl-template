#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize();
	void ShutDown();

	GLFWwindow * m_window;
};

