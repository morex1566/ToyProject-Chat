#include "System.h"

///    private area begin    ///

///    private area end      ///

///    public area begin     ///

System::System()
{
	looping = true;
}

System::~System(){}

void System::begin()
{
	int result;

	result = server.initialize();
	if (!result)
	{
		looping = false;
		return;
	}

	return;
}

void System::run()
{
	int result;

	server.start();

	while (looping)
	{
		result = server.update(thread);
		if (!result)
		{
			looping = false;
			break;
		}

		result = thread.update(server);
		if (!result)
		{
			looping = false;
			break;
		}
	}

	return;
}

void System::shutdown()
{
	thread.release();
	server.release();

	return;
}

///    public area end       ///