#include "Client.h"

///    private area begin    ///

///    private area end      ///

///    public area begin     ///

Client::Client()
{
	windowSock = { 0 };
	connectSock = { 0 };
	serverPort = 9000;
	share = 0;
}

Client::~Client()
{

}

bool Client::initialize()
{
	SOCKET result;

	result = WSAStartup(MAKEWORD(2, 2), &windowSock);
	if (result)
	{
		MessageBox(NULL, L"'WSAStartup()' is failed!", L"Initialize Error", MB_ICONERROR);
		return false;
	}

	connectSock = socket(AF_INET, SOCK_STREAM, 0);
	result = connectSock;
	if (result == INVALID_SOCKET)
	{
		MessageBox(NULL, L"'socket()' is failed!", L"Initialize Error", MB_ICONERROR);
		return false;
	}
}

bool Client::start()
{
	string hostIp;
	int result;

	// connect
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(serverPort);

	while (1)
	{
		cout << "서버의 주소를 입력해주세요 : ";
		getline(cin, hostIp);
		serveraddr.sin_addr.s_addr = inet_addr(hostIp.c_str());

		result = connect(connectSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		if (result == SOCKET_ERROR)
		{
			cout << "connect failed!!..." << endl;
		}
		else
		{
			cout << "connect success!!..." << endl;
			break;
		}
	}

	// get share

}

bool Client::update()
{

}

void Client::release()
{

}

///    public area end       ///