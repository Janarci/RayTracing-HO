#include "PoolWorkerThread.h"

PoolWorkerThread::PoolWorkerThread(int id, int lCol, int uCol, int lRow, int uRow)
{

	this->id = id;
		this->lCol = lCol;
		this->uCol = uCol;
		this->lRow = lRow;
		this->uRow = uRow;
}

void PoolWorkerThread::run()
{

	std::cout << "testing" << std::endl;
}
