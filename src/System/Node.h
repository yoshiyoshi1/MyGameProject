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

	//-------------------------------------------
	// オペレータ関連
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
	// メンバ関数
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
	// メンバ変数を初期化する関数
	void Reset() 
	{
		pos.Set(0, 0);
		score = 0;
		parent = nullptr;
	}

public:
	Position pos;
	int score;		// 実コスト(スタートからの距離)と推定コスト(ゴールまでの距離)の合計値
	
	Node* parent;	// 親へのポインタ
};

#endif