#ifndef __ThreadGuard_h__
#define __ThreadGuard_h__

//*************************************************
//
//	�}���`�X���b�h�p�@���S�ɏ������s�����߂̃N���X
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