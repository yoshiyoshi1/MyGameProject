#ifndef __Node_h__
#define __Node_h__

//*************************************************
//
//	�m�[�h�̍��W�p�N���X
//
//*************************************************
class Position {
public:
	Position(){}
	Position(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

	bool operator<(const Position &right) const 
	{
		return this->y < right.y; 
	}

	void Set(int _x, int _y) 
	{
		x = _x;
		y = _y;
	}

public:
	int x;
	int y;
};

//*************************************************
//
//	�m�[�h�N���X
//
//*************************************************
class Node
{
public:
	Position pos;
	Position pos2;

	int cost;		// ���R�X�g(�X�^�[�g����̋���)
	int heuristic;	// ����R�X�g(��Q���𖳎������S�[���܂ł̋���)
	Node* parent;	// �e�ւ̃|�C���^
};

#endif