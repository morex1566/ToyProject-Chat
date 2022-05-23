#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

using namespace std;

class Thread;

class Server
{
	struct DataBase
	{
		char	name[100];
		IN_ADDR ip;
		int		port;
		int		share;
	};

private:
	WSADATA		windowSock;
	SOCKET		clientSock;
	SOCKET		listenSock;
	DataBase	database;
	SOCKADDR_IN hostAddr;
	SOCKADDR_IN clientAddr;

public:
	Server();
	~Server();
	
	bool initialize();
	bool start();
	bool update(Thread&);
	void release();
	
	// utility
	int	getShare();
	void setShare(int);
	void setShare(const char*);
};

