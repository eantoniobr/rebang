#pragma once

#include <vector>
#include "polysoup.h"
#include "golfball.h"

// TODO: incomplete
class CQuadTree
{
public:
	void ResetHoleData();
	int GetMeshIndex(const WVector& pos, bool bObject);
	void PreProcess(float dt, bool bOneFrame);
	void AddWater(Waabb aabb, int type);
	unsigned char GetGroundType(WVector pos, bool bCheckTee,
		CGolfBall::eWater* water);
	WVector GetGroundPoint(WVector pos, bool bObject, int* index, bool bWater);
	WVector GetRayIntersection(WVector start, WVector ray);
	void BallProcess(float dt);
	void Reserve(short num);
	bool IsOBArea(const WVector& pos);
	void MakeBaseStructure(WPolySoup::sModel* model, bool bRebuild);
	void MakeObjStructure(short index, int modelIndex, bool bRebuild);
	float GetMaxPowerOnGround() const;
	float GetMinPowerOnGround() const;
	void CalcGreenPlane();
	int GetObjColNum();
	float GetBasePosY(WVector pos, float height);
	void ResetVariable();
	bool IsOverWater(WVector pos);

	void SetSlopeFactor(float slope) { m_slopeFactor = slope; }

	void SetPolySoup(WPolySoup* pPolySoup) { m_pPolySoup = pPolySoup; }

	float GetLowest() const { return m_lowest; }

	const std::vector<WPolySoup::sTriangle*>* GetTriArray(int texHandle) const
	{
		return m_pPolySoup->GetTriArray(texHandle);
	}

	WVector GetPenaltyPos() { return m_penaltyPos; }

	void SetFrame(unsigned long frame)
	{
		m_frame = frame;
		m_frameTime = 0.0f;
	}

	unsigned long GetFrame() { return m_frame; }

	WPolySoup* m_pPolySoup;
	unsigned char m_unknown4[0x2080];
	WVector m_penaltyPos;
	unsigned char m_unknown2090[0x108];
	float m_lowest;
	unsigned char m_unknown219c[0x20];
	float m_frameTime;
	unsigned long m_frame;
	unsigned char m_unknown21c4[0x14];
	float m_slopeFactor;
};

CQuadTree& GetPVS();
