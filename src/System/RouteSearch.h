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
	~RouteSearch(){}

	void Update();
	void Draw();

	void Reset(int x, int y);
	void SetNode(Node* node,Position pos, int cost, Node* parentNode);
	int GetDistance(int fromX, int fromY, int toX, int toY);

	int BackTrace(int x, int y);
	int Search(int count);
	
	void TraceRoute(int x, int y);
	int out(int(*d)[10]);
	int _tmain(int argc, char* argv[]);

private:

	std::map <Position, Node> mapOpen;
	std::map <Position, Node> mapClose;

	//CVector2 startPos;
	//CVector2 goalPos;

	Position startPos;
	Position goalPos;

	//-----------------------------
	// テストデータ
	static const int SIZE_X = 5;
	static const int SIZE_Y = 5;
	
	int m_RouteData[SIZE_Y][SIZE_X] = {
		{ 0,1,0,1,0 },
		{ 0,1,0,1,1 },
		{ 0,1,0,0,0 },
		{ 0,1,1,0,1 },
		{ 0,0,0,0,1 },
	};

	CMesh m_meshPin;
	//CMesh m_meshPin[SIZE_Y][SIZE_X];
	CMatrix m_mPin[SIZE_Y][SIZE_X];
	//-----------------------------
};


//#define POS(X,Y) Position(X, Y)
#define KEYDATA(P, N) std::pair<Position, Node>(P, N)

#endif