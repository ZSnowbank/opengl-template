#pragma once
#include "system.h"
class Engine :
	public System
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Update();
};

