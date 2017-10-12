#pragma once

class System
{
public:
	System();
	~System();

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Update() = 0;
};

