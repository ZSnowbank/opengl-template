#pragma once
#include "system.h"
class Input :
	public System
{
public:
	Input();
	~Input();

	bool Initialize();
	void Shutdown();
	void Update();
};

