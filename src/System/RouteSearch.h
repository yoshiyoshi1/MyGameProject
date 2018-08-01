#ifndef __RouteSearch_h__
#define __RouteSearch_h__

#include "Node.h"

class Node;

//*************************************************
//
//	経路探索用クラス
//
//*************************************************

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch();

	void Update();
	void Draw();

	// マップ情報をセットする関数
	void SetMapData(int* mapData);

	// 開始地点を変更する関数
	void ChangeStart(int x, int y)
	{
		nextStartPos.Set(x, y);
	}
	// 開始地点座標（ｘ）を取得する関数
	int GetStartPosX()
	{
		return startPos.x;
	}
	// 開始地点座標（ｙ）を取得する関数
	int GetStartPosY()
	{
		return startPos.y;
	}

	// 目的地を変更する関数
	void ChangeGoal(int x, int y)
	{
		nextGoalPos.Set(x, y);
	}
	// 目的地座標（ｘ）を取得する関数
	int GetGoalPosX()
	{
		return goalPos.x;
	}
	// 目的地座標（ｙ）を取得する関数
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
	// テストデータ
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