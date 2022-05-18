#pragma once

#include "Server.h"
#include "Thread.h"

#include <Windows.h>

class System
{
private:
	// entity
	Server server;
	Thread thread;

	// system
	bool looping;

public:
	System();
	~System();

	void begin();
	void run();
	void shutdown();
};

