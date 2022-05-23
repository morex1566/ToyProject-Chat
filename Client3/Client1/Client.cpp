#include "Client.h"

///    private area begin    ///

///    private area end      ///

///    public area begin     ///

Client::Client()
{
	windowSock = { 0 };
	connectSock = { 0 };
	serverAddr = { 0 };
	serverPort = 9000;
	share = 0;
	looping = true;
}

Client::~Client()
{

}

void Client::initialize()
{
	SOCKET result;

	result = WSAStartup(MAKEWORD(2, 2), &windowSock);
	if (result)
	{
		MessageBox(NULL, L"'WSAStartup()' is failed!", L"Initialize Error", MB_ICONERROR);
		looping = false;
		return;
	}

	connectSock = socket(AF_INET, SOCK_STREAM, 0);
	result = connectSock;
	if (result == INVALID_SOCKET)
	{
		MessageBox(NULL, L"'socket()' is failed!", L"Initialize Error", MB_ICONERROR);
		looping = false;
		return;
	}
}

void Client::start(char buf[])
{
	string hostIp;
	string data;
	int	   result;

	// connect
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(serverPort);


	cout << "������ �ּҸ� �Է����ּ��� : ";
	getline(cin, hostIp);
	serverAddr.sin_addr.s_addr = inet_addr(hostIp.c_str());

	result = connect(connectSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{
		cout << "connect failed!!..." << endl;
	}
	else
	{
		cout << "connect success!!..." << endl;
	}

	// get share
	buf[0] = 'b';
	buf[1] = '\0';

	result = send(connectSock, buf, (int)strlen(buf), 0);
	if (result == SOCKET_ERROR) {
		MessageBox(NULL, L"'send()' is failed!", L"Start Error", MB_ICONERROR);
		looping = false;
		return;
	}
	result = recvn(connectSock, buf, result, 0);
	if (result == SOCKET_ERROR) {
		MessageBox(NULL, L"'recvn()' is failed!", L"Start Error", MB_ICONERROR);
		looping = false;
		return;
	}

	buf[result] = '\0';
	share = atoi(buf);

	cout << "[TCP Ŭ���̾�Ʈ] " << result << "����Ʈ�� �޾ҽ��ϴ�." << endl;
	cout << "[���� ������] " << buf << endl;

	cout << "a�� ������ ���� �����Ϳ� 10�� ���ؼ� ������ �����մϴ�." << endl;
	cout << "b�� ������ ������ share���� ��û�մϴ�." << endl;
}

void Client::update()
{
	string data;
	char   buf[513];
	int	   result;
	int	   len;

	start(buf);

	while (looping)
	{
		cout << "[�Է�] " << endl;
		if (fgets(buf, bufsize, stdin) == NULL)
			break;

		// input interface
		switch (buf[0])
		{
		case 'a':
			share += 10;
			data = std::to_string(share);
			strcpy_s(buf, data.c_str());
			break;

		case 'b':
			break;

		default:
			continue;
		}


		// '\n' ���� ����
		len = (int)strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// send data
		result = send(connectSock, buf, (int)strlen(buf), 0);
		if (result == SOCKET_ERROR)
		{
			MessageBox(NULL, L"'send()' is failed!", L"Update Error", MB_ICONERROR);
			looping = false;
			break;
		}
		cout << "[TCP Ŭ���̾�Ʈ] " << (int)strlen(buf) << "����Ʈ�� ���½��ϴ�." << endl;


		//  get data
		result = recvn(connectSock, buf, result, 0);
		if (result == SOCKET_ERROR)
		{
			MessageBox(NULL, L"'recvn()' is failed!", L"Update Error", MB_ICONERROR);
			looping = false;
			break;
		}
		else if (result == 0)
			break;

		buf[result] = '\0';
		share = atoi(buf);

		cout << "[TCP Ŭ���̾�Ʈ] " << result << "����Ʈ�� �޾ҽ��ϴ�." << endl;
		cout << "[���� ������] " << buf << endl;
	}

	release();
	return;
}

void Client::release()
{
	closesocket(connectSock);
	WSACleanup();
	return;
}

int Client::recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;

	received = recv(s, buf, 513, flags);
	if (received == SOCKET_ERROR)
		return SOCKET_ERROR;
	else if (received == 0)
		return 0;

	return received;
}

///    public area end       ///