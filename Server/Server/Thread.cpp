#include "Thread.h"
#include "Server.h"

///    private area begin    ///

void Thread::processClient(Server& server, SOCKET& client)
{
    SOCKET clientSock;
    SOCKADDR_IN clientAddr;
    int  result;
    int  addrLength;
    char buf[513];

    // client information
    clientSock = client;
    addrLength = sizeof(clientAddr);
    getpeername(clientSock, (SOCKADDR*)&clientAddr, &addrLength);

    while (1) {

        // data receive
        result = recv(clientSock, buf, 513, 0);
        if (result == SOCKET_ERROR) // recv failed
        {
            break;
        }
        else if (result == 0) // recv success, but there's no data
        {
            break;
        }
        else if (result >= 1 && result <= 512) // recv success, there is data
        {
            buf[result] = '\0';
        }
        else // buffer overflow
        {
            MessageBox(NULL, L"'recv()' is failed!", L"processClient Error", MB_ICONERROR);
            break;
        }

        // data output
        cout << "[TCP/" << inet_ntoa(clientAddr.sin_addr);
        cout << ":" << ntohs(clientAddr.sin_port) << "] " << buf << endl;

        // data interface
        switch (buf[0])
        {
        case 'b':
            _itoa_s(server.getShare(), buf, 10);
            break;

        default:
            server.setShare(buf);
            strcpy_s(buf, "data update!");
            break;
        }

        // data send
        result = send(clientSock, buf, (int)strlen(buf), 0);
        if (result == SOCKET_ERROR)
        {
            MessageBox(NULL, L"'send()' is failed!", L"processClient Error", MB_ICONERROR);
            looping = false;
            break;
        }
    }

    // closesocket()
    closesocket(clientSock);

    // output
    cout << "[TCP 서버] 클라이언트 종료: IP 주소 = " << inet_ntoa(clientAddr.sin_addr);
    cout << ", 포트 번호 = " << ntohs(clientAddr.sin_port) << endl;

    return;
}

///    private area end      ///

///    public area begin     ///

Thread::Thread()
{
    looping = true;
}

Thread::~Thread()
{

}

bool Thread::update(Server& server)
{
    if (!looping) { return false; }

    

	return true;
}

void Thread::release()
{
    if (pool.size() > 0)
    {
        pool.clear();
        vector<thread*>().swap(pool);
    }
	return;
}

bool Thread::setThread(Server& server, SOCKET& socket)
{
    pool.push_back(new std::thread([&] { processClient(server, socket); }));

	return pool.back() != nullptr ? true : false;
}

///    public area end       ///