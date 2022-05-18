#include "Thread.h"
#include "Server.h"

///    private area begin    ///

void Thread::processClient(Server& server, SOCKET& client)
{
    int  result;
    int  addrLength;
    char buf[513];
    char share[512];


    // client information
    addrLength = sizeof(server.getClientAddr());
    getpeername(server.getClientScok(), (SOCKADDR*)&server.getClientAddr(), &addrLength);

    while (1) {

        // data receive
        result = recv(server.getClientScok(), buf, 513, 0);
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
        cout << "[TCP/" << inet_ntoa(server.getClientAddr().sin_addr);
        cout << ":" << ntohs(server.getClientAddr().sin_port) << "] " << buf << endl;

        // data interface
        switch (buf[0])
        {
        case 'b':
            _itoa_s(server.getShare(), buf, 10);
            break;

        default:
            mutex.lock();
            server.setShare(buf);
            strcpy_s(buf, "data update!");
            mutex.unlock();
            break;
        }

        // data send
        result = send(server.getClientScok(), buf, (int)strlen(buf), 0);
        if (result == SOCKET_ERROR)
        {
            MessageBox(NULL, L"'send()' is failed!", L"processClient Error", MB_ICONERROR);
            looping = false;
            break;
        }
    }

    // closesocket()
    closesocket(server.getClientScok());

    // output
    cout << "[TCP 서버] 클라이언트 종료: IP 주소 = " << inet_ntoa(server.getClientAddr().sin_addr);
    cout << ", 포트 번호 = " << ntohs(server.getClientAddr().sin_port) << endl;

    return;
}

///    private area end      ///

///    public area begin     ///

Thread::Thread()
{
    looping = true;
	thread = 0;
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
    delete thread;

	return;
}

bool Thread::setThread(Server& server, SOCKET& socket)
{
	thread = new std::thread([&]{ processClient(server, socket); });
	thread->join();

	return thread != nullptr ? true : false;
}

///    public area end       ///