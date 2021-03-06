#ifndef __map_h__ 
#define __map_h__

class map {
public:
	static const int SIZE_X = 80;
	static const int SIZE_Y = 80;

	void LoadXFile(void);						// メッシュデータ読み込み

	void LoadMap(void);						// mapの読み込み
	void DrawMap(CVector3 _pos);		// mapの描画

										// 地形
	FILE* t_fp;									// 地形fileポインタ
	int t_MapData[80][80];					// 地形mapデータ

											// 建物
	FILE* b_fp;									// 建物fileポインタ
	int b_MapData[80][80];					// 建物mapデータ

private:
	CMesh m_meshLand;					// 地形メッシュ
	CMesh m_meshRoad;					// 道路メッシュ
	CMesh m_meshSee;						// 海メッシュ
	CMesh m_meshSand;					// 砂メッシュ
	CMesh m_meshHouse[20];			// 建物メッシュ

	CMatrix m[80][80];						// map行列
	CMatrix mSee[100][100];					// map行列(海用)

};
#endif
