#include "../main.h"
#include "ThreadGuard.h"

#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	// 仮データ
	nextGoalPos.Set(68, 71);
	nextStartPos.Set(1, 1);

	m_meshPin.LoadXFile("../data/Mesh/TestData/pin.x");
}

RouteSearch::~RouteSearch()
{
	// 各リストのデータを削除する
	mapOpen.clear();
	mapClose.clear();
	
	ResetNodeData();
}

void RouteSearch::Update()
{
	// 開始地点と目的地が変わっていない場合、以降の処理を行わない
	if (goalPos == nextGoalPos && startPos == nextStartPos)
		return;

	Reset(nextStartPos.x, nextStartPos.y);

	// nextGoalPos が道ならば、新たな目的地として設定
	if (m_RouteData[nextGoalPos.y][nextGoalPos.x] == 0) {
		goalPos = nextGoalPos;
	}
	// nextGoalPos が道以外ならば、以降の処理を行わない
	else {
		return;
	}


	// 経路探索を別スレッドで行う
	std::thread searchThread(&RouteSearch::Search, this);
	ThreadGuard tg(searchThread);	// エラーで落ちた際に自動でJoinを行う
	searchThread.join();			// スレッドの終了を待機

}

void RouteSearch::Draw()
{
	// 目的地まで探索できているか確認
	std::map<int, Node>::iterator itClose = mapClose.find(KEY(goalPos));
	if (itClose == mapClose.end())
		return;

	for (int i = 0; ; i++) {

		// 経路をピンのメッシュで表示
		CMatrix m;
		int blue = (int)(i * (255.0f / (int)mapClose.size()));
		int red = 255 - blue;
		m.CreateMove(itClose->second.pos.x * 2.0f, -3.0f, itClose->second.pos.y * 2.0f);
		m_meshPin.Draw(&m, ARGB_D3DX(255, red, 0, blue));

		// 開始地点の場合、処理を終了する
		if (itClose->second.pos == startPos)
			return;

		// イテレータを親のノードで更新
		itClose = mapClose.find(KEY(itClose->second.parent->pos));
		if (itClose == mapClose.end())
			return;

	}
}

void RouteSearch::SetMapData(int* mapData)
{
	int i = 0;
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++, i++) {
			m_RouteData[cntY][cntX] = mapData[i];
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
	
	ResetNodeData();

	startPos.Set(x, y);

	Node* pStartNode = &m_NodeData[startPos.y][startPos.x];
	SetNode(
		pStartNode,
		startPos,
		0,
		nullptr
	);
	mapOpen.insert(KEYDATA(startPos, *pStartNode));
}

//=======================================================
//	ノードデータをリセットする関数
//=======================================================
void RouteSearch::ResetNodeData()
{
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++) {
			m_NodeData[cntY][cntX].Reset();
		}
	}
}

//=======================================================
//	ノード情報をセットする関数
//	@param_out	: node
//=======================================================
void RouteSearch::SetNode(Node* node, Position pos, int score, Node* parentNode)
{
	node->pos = pos;
	node->score = score;
	node->parent = parentNode;
}

//=======================================================
// 指定した地点からゴールまでの距離を求める（推定）
//	@return	: 距離
//=======================================================
int RouteSearch::GetDistance(Position fromPos)
{
	// 絶対値に修正
	int x = abs(fromPos.x - goalPos.x);
	int y = abs(fromPos.y - goalPos.y);

	// 推定移動コストを計算 （斜め）
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
int RouteSearch::BackTrace(Position pos)
{
	int res = 0;			// 距離
	Position tmpPos = pos;	// キーとなる座標

	//------------------------------------------
	// 親を遡っていき、距離を求める
	//------------------------------------------
	while (true) {
		// 開始地点まで戻った場合、処理を終了する
		if (tmpPos == startPos) {
			res++;
			break;
		}

		// Closeリストから指定された座標のノードを探す
		std::map<int, Node>::iterator it = mapClose.find(KEY(tmpPos));
		if (it == mapClose.end())
			break;
		if (it->second.parent == nullptr)
			break;

		// リストから探してきたノードの親の座標を新たな座標とする
		tmpPos = it->second.parent->pos;
		res++;
	}

	return res;
}

//=======================================================
// A*で経路探索する
//	@return	: 目的地まで探索できたかどうか
//=======================================================
bool RouteSearch::Search()
{
	int res = 0;

	while (true) {

		// Openリストが空なら探索終了（ゴールまでの道がない状態）
		if (mapOpen.empty()) {
			return false;
		}

		Node* pNode;	// 最小のコストを持つノードのポインタ

		//-----------------------------------------------
		//Openリストから最小のコストを持つノードを取り出す
		//-----------------------------------------------
		{
			int costMin = 9999;
			std::map<int, Node>::iterator itMin;

			{
				std::map<int, Node>::iterator it = mapOpen.begin();
				while (it != mapOpen.end()) {
					if (costMin > GetDistance(it->second.pos)) {
						costMin = GetDistance(it->second.pos);
						itMin = it;
					}
					it++;
				}
			}

			//m_NodeData[itMin->second.pos.y][itMin->second.pos.x] = itMin->second;
			pNode = &m_NodeData[itMin->second.pos.y][itMin->second.pos.x];

			// OpenリストからCloseリストへ移動
			mapClose.insert(KEYDATA(pNode->pos, *pNode));
			mapOpen.erase(KEY(pNode->pos));
		}


		// 最小コストのノードからスタートまでの移動コスト
		int backCost = 0;
		backCost = BackTrace(pNode->pos);


		//-----------------------------------------------
		// 上下左右の４方向を確認
		//-----------------------------------------------
		Node* pSubNode;
		int way[4][2] = {
			{  0, -1 },		// 下
			{  1,  0 },		// 左
			{  0,  1 },		// 上
			{ -1,  0 },		// 右
		};

		for (int i = 0; i < 4; i++) {
			// 隣接するマスの座標を計算 (４方向)
			Position tmpPos;
			tmpPos.x = pNode->pos.x + way[i][0];
			tmpPos.y = pNode->pos.y + way[i][1];

			// 範囲外の場合は処理を行わない
			if (tmpPos.x < 0) continue;
			if (tmpPos.y < 0) continue;
			if (tmpPos.x >= SIZE_X) continue;
			if (tmpPos.y >= SIZE_Y) continue;

			// 道以外の場合は処理を行わない
			if (m_RouteData[tmpPos.y][tmpPos.x] != 0) continue;

			pSubNode = &m_NodeData[tmpPos.y][tmpPos.x];
			SetNode(
				pSubNode,
				tmpPos,
				backCost + GetDistance(tmpPos),	// スコア（スタートまでの距離 + ゴールまでの距離）
				pNode
			);


			//-----------------------------------------------
			//Openリストに求めた座標と同じノードがあるか確認
			//-----------------------------------------------
			if (mapOpen.find(KEY(tmpPos)) != mapOpen.end()) {	// ある場合

				// Openリストでのスコアより求めたスコアが少ない場合、書き変える
				if (pSubNode->score < mapOpen[KEY(tmpPos)].score) {
					mapOpen[KEY(tmpPos)].parent = pNode;
					mapOpen[KEY(tmpPos)].score = pSubNode->score;
				}
				continue;
			}


			//-----------------------------------------------
			//Closeリストにこの座標と同じノードがあるか確認
			//-----------------------------------------------
			if (mapClose.find(KEY(tmpPos)) != mapClose.end()) {	// ある場合

				// Closeリストでのスコアより求めたスコアが少ない場合、
				//	新たなノードをOpenリストに追加しCloseリストから除く
				if (pSubNode->score < mapClose[KEY(tmpPos)].score) {
					Node tmp;
					SetNode(
						&tmp,
						tmpPos,
						pSubNode->score,
						pNode
					);

					mapOpen.insert(KEYDATA(tmpPos, tmp));
					mapClose.erase(KEY(tmpPos));
				}
				continue;
			}

			// 見つからなければ新規としてOpenリストへ追加
			mapOpen.insert(KEYDATA(pSubNode->pos, *pSubNode));
		}

		//-----------------------------------------------
		//見つかったら探索終了
		//-----------------------------------------------
		if (pNode->pos == goalPos) {
			return true;
		}

		// 見つからなかったらもう一度探索
	}
}
