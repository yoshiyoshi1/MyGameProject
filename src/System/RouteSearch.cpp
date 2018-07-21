#include "../main.h"

#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	goalPos.Set(2, 4);

	m_meshPin.LoadXFile("../data/Mesh/TestData/pin.x");


	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
	//		m_meshPin[cntY][cntX].LoadXFile("../data/Mesh/TestData/pin.x");
			m_mPin[cntY][cntX].CreateMove(cntX * 2.0f, -3.5f+0.5f, cntY * 2.0f);
			//m_mPin[cntY][cntX].SetPos(2, -2, 0);
		}
	}
}

void RouteSearch::Update()
{
	Reset(0, 0);

	if (Search(0) == -9) {
		return;
	}
	
	//TraceRoute(goalPos.x, goalPos.y);

	//out(m_RouteData);
	//return 0;
}

void RouteSearch::Draw()
{
	for (int cntY = 0; cntY < SIZE_Y; cntY++) {
		for (int cntX = 0; cntX < SIZE_X; cntX++) {
			D3DXCOLOR color;
			color = ARGB_D3DX(255, 255, 255, 255);
			if (m_RouteData[cntY][cntX] == 1)
				color = ARGB_D3DX(255, 255, 0, 0);
			else
				color = ARGB_D3DX(255, 0, 255, 0);
			m_meshPin.Draw(&m_mPin[cntY][cntX], color);
		}
	}
}


//=======================================================
//	リストを初期化してスタート地点をセットする関数
//=======================================================
void RouteSearch::Reset(int x, int y)
{
	mapOpen.clear();
	mapClose.clear();
	
	startPos.Set(x, y);

	Node startNode;
	SetNode(
		&startNode,
		startPos,
		0,
		nullptr
	);
	mapOpen.insert(KEYDATA(startPos, startNode));
}

//=======================================================
//	ノード情報をセットする関数
//	@param_out	: node
//=======================================================
void RouteSearch::SetNode(Node* node, Position pos, int cost, Node* parentNode)
{
	node->pos = pos;
	node->cost = cost;
	node->parent = parentNode;
}

//=======================================================
// マンハッタン距離を求める
//	@return	: 距離
//=======================================================
int RouteSearch::GetDistance(int fromX, int fromY, int toX, int toY)
{
	int x = fromX - toX;
	int y = fromY - toY;

	// 補正
	if (x < 0) x *= -1;
	if (y < 0) y *= -1;

	// 推定移動コストを計算
	if (x < y) {
		return (x + (y - x));
	}
	else {
		return (y + (x - y));
	}
}

//=======================================================
// 指定した地点からスタート地点までの距離を求める
//	@return	: 距離
//=======================================================
int RouteSearch::BackTrace(int x, int y)
{
	if (x == startPos.x && y == startPos.y) {
		return 1;
	}

	std::map <Position, Node > ::iterator tmp = mapClose.find(Position(x,y));

	if (tmp == mapClose.end()) return 0;

	return BackTrace(tmp->second.pos2.x, tmp->second.pos2.y) + 1;
}

//=======================================================
// A*で経路探査する
//	@return	: 何回サーチしたか	(-1:見つかった	(-9:見つからなかった
//=======================================================
int RouteSearch::Search(int count)
{

	// Openリストが空なら終了
	if (mapOpen.empty()) return -9;

	int costMin = 9999;
	int backCost = 0;
	
	Node node;
	{
		std::map<Position, Node>::iterator itMin;
		{
			//Openリストから最小のコストを持つノードを取り出す
			std::map<Position, Node>::iterator it = mapOpen.begin();
			while (it != mapOpen.end()) {
				if (costMin > GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y)) {
					costMin = GetDistance(it->second.pos.x, it->second.pos.y, goalPos.x, goalPos.y);
					itMin = it;
				}
				it++;
			}
		}

		SetNode(
			&node,
			itMin->second.pos,
			itMin->second.cost,
			nullptr
		);
	}

	// OpenリストからCloseリストへ移動
	mapClose.insert(KEYDATA(node.pos, node));
	mapOpen.erase(Position(node.pos.x, node.pos.y));

	// 最小コストのノードからスタートまでの移動コスト
	backCost = BackTrace(node.pos.x, node.pos.y);

	Node nodes[4];

	int way[4][2] = {
		{  0, -1 },
		{  1,  0 },
		{  0,  1 },
		{ -1,  0 },
	};

	for (int i = 0; i < 4; i++) {
		// 隣接するマスの座標を計算 (４方向)
		Position tmpPos;
		tmpPos.x = node.pos.x + way[i][0];
		tmpPos.y = node.pos.y + way[i][1];

		// 範囲外の場合は処理を行わない
		if (tmpPos.x < 0) continue;
		if (tmpPos.y < 0) continue;
		if (tmpPos.x >= SIZE_X) continue;
		if (tmpPos.y >= SIZE_Y) continue;

		// 道以外をよける
		if (m_RouteData[tmpPos.y][tmpPos.x] == 0) continue;

		SetNode(
			&nodes[i],												
			tmpPos,													
			backCost + GetDistance(tmpPos.x, tmpPos.y, goalPos.x, goalPos.y) + 1,	// 推定移動コスト
			&node													
		);

		{
			//Openリストに求めた座標と同じノードがあるか確認
			if (mapOpen.find(tmpPos) != mapOpen.end()) {	// ある場合

				// リストでのコストより求めたコストが少ない場合
				if (nodes[i].cost < mapOpen[tmpPos].cost) {
					mapOpen[tmpPos].parent = &node;
					mapOpen[tmpPos].cost = nodes[i].cost;
				}
				continue;
			}

			//Closeリストにこの座標と同じノードがあるか確認
			if (mapClose.find(tmpPos) != mapClose.end()) {
				if (nodes[i].cost < mapClose[tmpPos].cost) {
					Node tmp;

					SetNode(
						&tmp,
						tmpPos,
						nodes[i].cost,
						&node
					);

					mapOpen.insert(KEYDATA(tmpPos, tmp));
					mapClose.erase(tmpPos);
				}
				continue;
			}

			// 見つからなければ新規としてOpenリストへ追加
			mapOpen.insert(KEYDATA(nodes[i].pos, nodes[i]));
		}

	}

	//見つかったら探索終了
	if (node.pos.x == goalPos.x && node.pos.y == goalPos.y) return -1;

	// 見つからなかったらもう一度探索
	return Search(count + 1);
}

/*
// 最短ルートをマップデータに書き出す
void RouteSearch::TraceRoute(int x, int y)
{
	if (x == startPos.x && y == startPos.y) {
		printf("開始ノード>");
		return;
	}

	std::map<Position, Node>::iterator node_it = mapClose.find(Position(x, y));

	if (node_it != mapClose.end()) {
		m_RouteData[y][x] = 1;

		TraceRoute(node_it->second.pos2.x, node_it->second.pos2.y);

		if (x == goalPos.x && y == goalPos.y) {
			printf("ゴール\n");
			return;
		}
		else {
			printf("(%d,%d)>", x, y);
		}
	}

	return;
}
*/

/*
// マップの情報を綺麗に表示する
int RouteSearch::out(int(*d)[SIZE_X])
{
	for (int h = 0; h < SIZE_Y; h++) {
		for (int w = 0; w < SIZE_X; w++) {
			char ch = ' ';
			if (w == goalPos.x && h == goalPos.y) ch = '*';
			if (w == startPos.x && h == startPos.y) ch = '@';

			printf("%c", ch);

			if (d[h][w] > 0)  ch = 'o';
			if (d[h][w] < 0)  ch = '#';
			if (d[h][w] == 0) ch = '.';

			printf("%c", ch);
		}
		printf("\n");
	}
	return 0;
}
/*
int RouteSearch::_tmain(int argc, char* argv[])
{
	Node start;

	SetNode(
		&start,
		startPos.x, startPos.y,
		-1, -1,
		0
	);

	mapOpen.insert(KEYDATA(startPos.x, startPos.y, start));

	if (Search(0) == -1) {
		printf("見つかった！\n");
	}
	TraceRoute(goalPos.x, goalPos.y);

	out(m_RouteData);

	return 0;
}
*/