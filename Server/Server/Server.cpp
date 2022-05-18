#include "Server.h"
#include "Thread.h"

///    private area begin    ///

///    private area end      ///

///    public area begin     ///

Server::Server()
{
	windowSock = { 0 };
	clientSock = { 0 };
	listenSock = { 0 };
	database = { 0 };
	hostAddr = { 0 };
	clientAddr = { 0 };

	return;
}

Server::~Server()
{
	return;
}

bool Server::initialize()
{
	HOSTENT* hostEntry;
	SOCKET	 result;

	// socket
	result = WSAStartup(MAKEWORD(2, 2), &windowSock);
	if (result != NULL)
	{
		MessageBox(NULL, L"'WSAStartup()' is failed!", L"Initialize Error", MB_ICONERROR);
		return false;
	}

	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	result = listenSock;
	if (result == INVALID_SOCKET)
	{
		MessageBox(NULL, L"'socket()' is failed!", L"Initialize Error", MB_ICONERROR);
		return false;
	}

	clientSock = 0;

	// database
	result = gethostname(database.name, 100);
	if (result == SOCKET_ERROR)
	{
		MessageBox(NULL, L"'gethostname()' is failed!", L"Initialize Error", MB_ICONERROR);
		return false;
	}
	else
	{
		hostEntry = gethostbyname(database.name);
		memcpy(&database.ip, hostEntry->h_addr_list[0], hostEntry->h_length);
		database.share = 0;
		database.port = 9000;
	}

	// address
	ZeroMemory(&hostAddr, sizeof(hostAddr));
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	hostAddr.sin_port = htons(database.port);

	return true;
}

bool Server::start()
{
	SOCKET	result;

	// bind 
	result = bind(listenSock,(SOCKADDR*)&hostAddr, sizeof(hostAddr));
	if (result == SOCKET_ERROR)
	{
		MessageBox(NULL, L"'bind()' is failed!", L"Start Error", MB_ICONERROR);
		return false;
	}

	// listen
	result = listen(listenSock, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		MessageBox(NULL, L"'listen()' is failed!", L"Start Error", MB_ICONERROR);
		return false;
	}

	cout << "서버가 켜졌습니다!" << endl;
	cout << "IP 주소 : " << inet_ntoa(database.ip) << endl;

	return true;
}

bool Server::update(Thread& thread)
{
	int		addrLength;
	SOCKET	result;

	// accept
	addrLength = sizeof(clientAddr);
	clientSock = accept(listenSock, (SOCKADDR*)&clientAddr, &addrLength);
	result = clientSock;
	if (result == INVALID_SOCKET)
	{
		MessageBox(NULL, L"'accept()' is failed!", L"Update Error", MB_ICONERROR);
		return false;
	}

	// output
	cout << "\n[TCP 서버] 클라이언트 접속 : IP 주소 = " << inet_ntoa(clientAddr.sin_addr);
	cout << ", 포트 번호 = " << ntohs(clientAddr.sin_port) << endl;

	// create thread
	result = thread.setThread(*this, clientSock);
	if (!result)
	{
		MessageBox(NULL, L"'addThread()' is failed!", L"Update Error", MB_ICONERROR);
		return false;
	}

	return true;
}

void Server::release()
{
	closesocket(listenSock);
	WSACleanup();

	return;
}

SOCKADDR_IN& Server::getClientAddr()
{
	return clientAddr;
}

SOCKET& Server::getClientScok()
{
	return clientSock;
}

int Server::getShare()
{
	return database.share;
}

void Server::setShare(int value)
{
	database.share = value;
	return;
}

void Server::setShare(const char* value)
{
	database.share = atoi(value);
	return;
}

///    public area end       ///