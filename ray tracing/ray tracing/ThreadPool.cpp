//#include "ThreadPool.h"
//
//
//
//ThreadPool::ThreadPool(String name, int numWorkers)
//{
//
//	this->name = name;
//	this->numWorkers = numWorkers;
//
//	for (int i = 0; i < this->numWorkers; i++)
//	{
//		//this->inactiveThreads.push(new PoolableWorkerThread(i, this));
//	}
//
//}
//
//ThreadPool::~ThreadPool()
//{
//	this->stopScheduler();
//	this->activeThreads.clear();
//	while (this->inactiveThreads.empty() == false)
//	{
//		this->inactiveThreads.pop();
//	}
//}
//
//void ThreadPool::startScheduler()
//{
//	this->running = true;
//	this->start();
//}
//
//void ThreadPool::stopScheduler()
//{
//	this->running = false;
//
//}
//
//void ThreadPool::scheduleTask(IWorkerAction* action)
//{
//	this->pendingActions.push(action);
//
//}
//
//void ThreadPool::run()
//{
//	//while (running)
//	//{
//
//	//	//std::cout << ticks << std::endl;
//
//	//	if (!this->pendingActions.empty())
//	//	{
//	//		//std::cout << pendingActions.size() << std::endl;
//
//	//		if (!this->inactiveThreads.empty())
//	//		{
//
//	//			//std::cout << inactiveThreads.size() << std::endl;
//
//	//			PoolableWorkerThread* WorkerThread = this->inactiveThreads.front();
//	//			//this->activeThreads.insert({ 0, WorkerThread });
//	//			this->activeThreads[WorkerThread->getThreadID()] = WorkerThread;
//	//			this->inactiveThreads.pop();
//
//	//			this->activeThreads[WorkerThread->getThreadID()];
//	//			WorkerThread->assignTask(pendingActions.front());
//	//			pendingActions.pop();
//	//			//this->activeThreads[WorkerThread->getThreadID()]->start();
//	//			WorkerThread->start();
//
//
//
//	//		}
//	//	}
//
//	//}
//}
//
//void ThreadPool::onFinished(int threadID)
//{
//	//if (this->activeThreads[threadID])
//	//{
//
//	//	//std::cout <<"this is size"<<inactiveThreads.size() << std::endl;
//	//	delete this->activeThreads[threadID];
//	//	this->activeThreads.erase(threadID);
//
//	//	this->inactiveThreads.push(new PoolableWorkerThread(threadID, this));
//
//	//}
//
//}
//
