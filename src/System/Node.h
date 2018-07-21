#ifndef __Node_h__
#define __Node_h__

//*************************************************
//
//	ノードの座標用クラス
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
//	ノードクラス
//
//*************************************************
class Node
{
public:
	Position pos;
	Position pos2;

	int cost;		// 実コスト(スタートからの距離)
	int heuristic;	// 推定コスト(障害物を無視したゴールまでの距離)
	Node* parent;	// 親へのポインタ
};

#endif