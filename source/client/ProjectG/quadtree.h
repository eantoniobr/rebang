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
	float GetMaxPowerOnGround(const WVector& pos);
	WVector GetMeshNormal(const WVector& pos);
	WVector GetMeshNormal(int index);
	float GetMinPowerOnGround() const;
	float GetMinPowerOnGround(const WVector& pos);
	void CalcGreenPlane();
	float GetGreenPos(const WVector& pos);
	float RayIntersectAll(const WVector& start, const WVector& ray,
		bool bObject);
	void GetMeshList(WVector pos);
	void GetMeshList(WVector start, const WVector& end);
	void GetMeshList(Waabb aabb);
	void Display();
	float GetHighestGround(WVector pos, int* index);
	float GetLowestGround(WVector pos);
	void SetCondition();
	void UpdateProperty();
	void SetAvatarPosition(const WVector& pos, float radius);
	void HoleIn();
	int GetBounceCount();
	WVector ColObject(const WVector& pos, bool bObject, int* index,
		bool bWater);
	void GetObjList(Waabb aabb);
	void GetObjList(WVector start, const WVector& end);
	bool OverlappedWithObject(WVector pos, float radius);
	void SetObjVtxColor(unsigned long color);
	bool SimpleColTest(const WVector& start, const WVector& end);
	bool IsFallenIntoWater(WVector pos, Waabb* aabb, bool bCheck);
	float GetShadowIntensity(const WVector& pos);
	WVector GetRayIntersectionObj(WVector start, WVector ray);
	int CheckCamera();
	bool CheckPickRoom(WVector pos);
	WVector TestCameraCollision(const WVector& pos);
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

	void SetRandSeed(unsigned long seed) { m_randSeed = seed; }
	unsigned long GetFrame() { return m_frame; }

	WPolySoup* m_pPolySoup;
	unsigned char m_unknown4[0x2080];
	WVector m_penaltyPos;
	unsigned char m_unknown2090[0x108];
	float m_lowest;
	unsigned char m_unknown219c[0x20];
	float m_frameTime;
	unsigned long m_frame;
	unsigned char m_unknown21c4[0x10];
	unsigned long m_randSeed;
	float m_slopeFactor;
};

CQuadTree& GetPVS();
