//#pragma once
//
////����
////https://modoocode.com/285
//
//#include <functional>
//#include <queue>
//#include <thread>
//#include <vector>
//
//using namespace std;
//
//class ThreadPool
//{
//private:
//	int threadNum;
//
//	vector<thread> vWorkerThread;
//	queue<function<void()>> jobs;
//
//	// ��� ������ ����
//	bool stop_all;
//
//	// Worker ������
//	void WorkerThread();
//
//public:
//	ThreadPool(int threadNum_);
//	~ThreadPool();
//
//	// job �� �߰��Ѵ�.
//	void EnqueueJob(function<void()> job);
//};
//
