#ifndef __RouteSearch_h__
#define __RouteSearch_h__

#include "Node.h"

class Node;

//*************************************************
//
//	�o�H�T���p�N���X
//
//*************************************************

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch();

	void Update();
	void Draw();

	// �}�b�v�����Z�b�g����֐�
	void SetMapData(int* mapData);

	// �J�n�n�_��ύX����֐�
	void ChangeStart(int x, int y)
	{
		nextStartPos.Set(x, y);
	}
	// �J�n�n�_���W�i���j���擾����֐�
	int GetStartPosX()
	{
		return startPos.x;
	}
	// �J�n�n�_���W�i���j���擾����֐�
	int GetStartPosY()
	{
		return startPos.y;
	}

	// �ړI�n��ύX����֐�
	void ChangeGoal(int x, int y)
	{
		nextGoalPos.Set(x, y);
	}
	// �ړI�n���W�i���j���擾����֐�
	int GetGoalPosX()
	{
		return goalPos.x;
	}
	// �ړI�n���W�i���j���擾����֐�
	int GetGoalPosY()
	{
		return goalPos.y;
	}

private:

	void Reset(int x, int y);
	void ResetNodeData();
	void SetNode(Node* node, Position pos, int score, Node* parentNode);
	int GetDistance(Position fromPos);
	int BackTrace(Position pos);
	bool Search();

private:
	std::map <int, Node> mapOpen;
	std::map <int, Node> mapClose;

	Position startPos;
	Position goalPos;

	Position nextStartPos;
	Position nextGoalPos;

	//-----------------------------
	// �e�X�g�f�[�^
	static const int SIZE_X = 80;
	static const int SIZE_Y = 80;
	//-----------------------------

	int m_RouteData[SIZE_Y][SIZE_X];
	Node m_NodeData[SIZE_Y][SIZE_X];

	CMesh m_meshPin;
};


#define KEY(P) (P.x + P.y * 100)
#define KEYDATA(P, N) std::pair<int, Node>(KEY(P), N)

#endif