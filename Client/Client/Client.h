#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

class Client
{
private:
	WSADATA windowSock;
	SOCKET connectSock;
	SOCKADDR_IN serveraddr;
	int serverPort;
	int share;

public:
	Client();
	~Client();

	bool initialize();
	bool start();
	bool update();
	void release();
};

