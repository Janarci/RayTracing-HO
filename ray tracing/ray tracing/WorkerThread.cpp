#include "WorkerThread.h"


WorkerThread::WorkerThread()
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::start()
{
	std::thread(&WorkerThread::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void WorkerThread::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
