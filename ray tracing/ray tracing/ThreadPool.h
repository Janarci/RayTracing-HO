//#pragma once
//#include <queue>
//#include <string>
//#include <unordered_map>
//#include "WorkerThread.h"
//
//#include "PoolableWorkerThread.h"
//class IWorkerAction;
//class IFinishedTask
//{
//public:
//	virtual void onFinished(int threadID) = 0;
//};
//
//class ThreadPool : public WorkerThread, public IFinishedTask
//{
//private:
//	typedef std::string String;
//	typedef std::queue<PoolableWorkerThread*> ThreadList;
//	typedef std::unordered_map<int, PoolableWorkerThread*> ActiveThreadMap;
//	typedef std::queue<IWorkerAction*> ActionList;
//
//public:
//	ThreadPool(String name, int numWorkers);
//	~ThreadPool();
//
//	void startScheduler();
//	void stopScheduler();
//	void scheduleTask(IWorkerAction* action);
//
//private:
//	void run() override;
//	void onFinished(int threadID) override;
//
//	String name;
//	bool running = false;
//	int numWorkers = 0;
//
//	ActiveThreadMap activeThreads;
//	ThreadList inactiveThreads;
//	ActionList pendingActions; // the things to execute
//};