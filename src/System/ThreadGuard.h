#ifndef __ThreadGuard_h__
#define __ThreadGuard_h__

//*************************************************
//
//	�}���`�X���b�h�p�@���S�ɏ������s�����߂̃N���X
//
//*************************************************

class ThreadGuard {
public:
	explicit ThreadGuard(std::thread& t_) : t(t_) {}
	~ThreadGuard() {
		if (t.joinable()) {
			t.join();
		}
	}
	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;

private:
	std::thread& t;

};

#endif