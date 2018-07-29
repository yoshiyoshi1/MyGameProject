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

	//-------------------------------------------
	// �I�y���[�^�֘A
	bool operator<(const Position& right) const 
	{
		if (this->y < right.y) {
			return true;
		}
		else if (this->y == right.y) {
			if (this->x < right.y) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool operator==(const Position& value) const
	{
		return (this->x == value.x && this->y == value.y);
	}

	//-------------------------------------------
	// �����o�֐�
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
	// �����o�ϐ�������������֐�
	void Reset() 
	{
		pos.Set(0, 0);
		score = 0;
		parent = nullptr;
	}

public:
	Position pos;
	int score;		// ���R�X�g(�X�^�[�g����̋���)�Ɛ���R�X�g(�S�[���܂ł̋���)�̍��v�l
	
	Node* parent;	// �e�ւ̃|�C���^
};

#endif