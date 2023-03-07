#pragma once
#include <iostream>
#include <thread>


class WorkerThread
{

public:
	WorkerThread();
	~WorkerThread();

	void start(); //schedules thread execution
	static void sleep(int ms);

protected:
	virtual void run() = 0;

};

