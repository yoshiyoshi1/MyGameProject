#ifndef __ThreadGuard_h__
#define __ThreadGuard_h__

//*************************************************
//
//	マルチスレッド用　安全に処理を行うためのクラス
//
//*************************************************

class ThreadGuard {
public:
	explicit ThreadGuard(std::thread& _thread) : thread(_thread) {}
	~ThreadGuard() {
		if (thread.joinable()) {
			thread.join();
		}
	}
	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;

private:
	std::thread& thread;

};

#endif