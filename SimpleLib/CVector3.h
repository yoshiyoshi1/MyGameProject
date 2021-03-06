#ifndef __CVector3_h__
#define __CVector3_h__

namespace SimpleLib{

//============================================================================
// ３次元ベクトルクラス
//	D3DXVECTOR3の機能拡張版
//============================================================================
class CVector3 : public D3DXVECTOR3{
public:
	// コンストラクタ
	CVector3(){
		x = 0;
		y = 0;
		z = 0;
	}
	CVector3(float fx,float fy,float fz){
		x = fx;
		y = fy;
		z = fz;
	}
	CVector3(const D3DXVECTOR3 &In){
		x = In.x;
		y = In.y;
		z = In.z;
	}

	void Set(float fx,float fy,float fz){
		x = fx;
		y = fy;
		z = fz;
	}
	void Set(const D3DXVECTOR3 *v){
		x = v->x;
		y = v->y;
		z = v->z;
	}

	CVector3& operator=(const D3DXVECTOR3& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	// 各演算子
	CVector3 operator + () const{ return D3DXVECTOR3::operator+(); }
	CVector3 operator - () const{ return D3DXVECTOR3::operator-(); }

	CVector3 operator + ( CONST D3DXVECTOR3& v) const{ return D3DXVECTOR3::operator+(v); }
	CVector3 operator - ( CONST D3DXVECTOR3& v) const{ return D3DXVECTOR3::operator-(v); }
	CVector3 operator * ( FLOAT f) const{ return D3DXVECTOR3::operator*(f); }
	CVector3 operator / ( FLOAT f) const{ return D3DXVECTOR3::operator/(f); }

	//ベクトル加算
	static void Add(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){	// 静的関数
		D3DXVec3Add(vOut,v1,v2);
	}
	void Add(float fx,float fy,float fz){
		Add(this,this,&D3DXVECTOR3(fx,fy,fz));
	}
	void Add(const CVector3 *p){
		Add(this,this,p);
	}
	
	//ベクトル減算
	static void Sub(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){	// 静的関数
		D3DXVec3Subtract(vOut,v1,v2);
	}
	void Sub(float fx,float fy,float fz){
		Sub(this,this,&D3DXVECTOR3(fx,fy,fz));
	}
	void Sub(const D3DXVECTOR3 *p){
		Sub(this,this,p);
	}
	
	// 内積
	static float Dot(const D3DXVECTOR3 *v1,const D3DXVECTOR3 *v2){			// 静的関数
		return D3DXVec3Dot(v1,v2);
	}
	float Dot(const D3DXVECTOR3 *v1){
		return Dot(this,v1);
	}

	// 外積
	static void Cross(D3DXVECTOR3 *vOut, const D3DXVECTOR3 *v1, const D3DXVECTOR3 *v2) {// 静的関数
		D3DXVec3Cross(vOut, v1, v2);
	}
	void Cross(const D3DXVECTOR3 *v1, const D3DXVECTOR3 *v2) {
		D3DXVec3Cross(this, v1, v2);
	}
	// 外積 自分 x vBack
	void CrossBack(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vBack){
		Cross(vOut,this,vBack);
	}
	// 外積 vBack x 自分
	void CrossFront(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vFront){
		Cross(vOut,vFront,this);
	}
	
	// スカラー倍
	static void Scale(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,float s){		// 静的関数
		D3DXVec3Scale(vOut,vSrc,s);
	}
	void Scale(float s){
		Scale(this,this,s);
	}

	// 長さ
	static float Length(const D3DXVECTOR3 *vSrc){						// 静的関数
		return D3DXVec3Length(vSrc);
	}
	float Length(){
		return Length(this);
	}
	// 正規化
	static void Normalize(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc){			// 静的関数
		D3DXVec3Normalize(vOut,vSrc);
	}
	void Normalize(){
		Normalize(this,this);
	}
	void Normalize(D3DXVECTOR3 *vOut) const{
		Normalize(vOut,this);
	}


	// 行列で変換(回転・座標)
	static void TransformCoord(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){	// 静的関数
		D3DXVec3TransformCoord(vOut,vSrc,D3DXMATRIX);
	}
	void TransformCoord(const D3DXMATRIX *D3DXMATRIX){
		TransformCoord(this,this,D3DXMATRIX);
	}
	void TransformCoord(D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){
		TransformCoord(this,vSrc,D3DXMATRIX);
	}
	
	// 行列で変換(回転のみの変換)
	static void TransformNormal(D3DXVECTOR3 *vOut,const D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){// 静的関数
		D3DXVec3TransformNormal(vOut,vSrc,D3DXMATRIX);
	}
	void TransformNormal(const D3DXMATRIX *D3DXMATRIX){
		TransformNormal(this,this,D3DXMATRIX);
	}
	void TransformNormal(D3DXVECTOR3 *vSrc,const D3DXMATRIX *D3DXMATRIX){
		TransformNormal(this,vSrc,D3DXMATRIX);
	}

};

}

#endif
