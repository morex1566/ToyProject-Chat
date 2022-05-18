#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <WinSock2.h>
#include <iostream>

using namespace std;

class Server;

class Thread
{
private:
	thread*	 thread;
	mutex	 mutex;
	bool	 looping;

	void processClient(Server&, SOCKET&);
public:
	Thread();
	~Thread();

	bool update(Server&);
	void release();

	// utility
	bool setThread(Server&, SOCKET&);
};

