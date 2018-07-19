#ifndef __CARBASE_h__
#define __CARBASE_h__



class CarBase {

public:
	CarBase();
	~CarBase();

	virtual void Update();
	virtual void Draw();
	void Move(float maxSpeed);

	void SetPos(const CVector3 _pos) { bodyMat.CreateMove(_pos.x, _pos.y, _pos.z); }
	void SetPos(const CVector3 _pos, const float _rot) { bodyMat.CreateMove(_pos.x, _pos.y, _pos.z); bodyMat.RotateY(_rot); }

	float GetSpeed() { return Speed; }
	int GetCarType() { return carType; }

	enum TirePos {
		FR,	//â^ì]ê»ë§
		FL,	//èïéËê»ë§
		R1,	//å„ó÷1Ç¬ñ⁄
		R2	//å„ó÷2Ç¬ñ⁄
	};

	enum CarType {
		Taxi,
		Sedan,
		Onebox,
		Bus,
		Truck
	};

protected:
	int carType;

	CMatrix bodyMat;
	CMatrix tireMat[4],tireTrans[4],tmpTireMat[4];
	CMatrix beforeXMat;
	CMesh Body, FTire, RTire, DTire;

	bool isForword = false;
	bool isBack = false;

	float Speed = 0;
	float FTireRot = 0;

private:
	const float reduce = 0.05f;



};

#endif