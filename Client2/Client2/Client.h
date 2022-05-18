#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

class Client
{
private:
	WSADATA		windowSock;
	SOCKET		connectSock;
	SOCKADDR_IN serverAddr;
	int			serverPort;
	int			share;
	bool		looping;

public:
	Client();
	~Client();


	void initialize();
	void start(char[]);
	void update();
	void release();

	int recvn(SOCKET, char*, int, int);
};

