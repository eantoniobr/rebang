#pragma once

#include <string>
#include <list>
#include <map>
#include <vector>
#include "actor.h"
#include "scenemanager.h"

class CCreature;

class CNPC : public IActor
{
public:
	virtual ~CNPC() { }

	DECLARE_OBJECT(CNPC)

	virtual void OnInit();
	virtual void OnProcess(float delta);
	virtual void OnDestroy();

protected:
	virtual void HandleMsg(const MsgObject& msg);

	void Destroy();
	void SetNPC(const std::vector<WVector>& node, const char* option);
	void SetNPC(const Waabb& area, char* option);

	std::list<CCreature*> m_creatureList;

protected:
	CNPC() { }
};

class CCreature : public CRenderFuncPtr
{
	friend class CNPC;

public:
	struct sAlpha
	{
		float alpha;
		float time;
	};

	virtual ~CCreature();

	virtual void Process(float dt);
	virtual void Display();
	virtual void SetArea(const Waabb& area, unsigned long flag);
	virtual void SetArea(const std::vector<WVector>& node, float time,
		unsigned long flag);
	virtual void PlayEvent();
	virtual void CheckTarget(float dt);

	bool GetActive() { return m_bActive; }
	void SetActive(bool bActive) { m_bActive = bActive; }
	Waabb GetArea() { return m_area; }
	void SetMotion(const char* name, float time);
	void ParsePuppetScript(const char* script);
	void ScriptProcess(const w_motion_data* motion, float prevTime,
		float curTime);
	void Record();
	void Replay();
	void DrawDebugLine();
	void SetType(int type) { m_type = type; }
	int GetType() { return m_type; }
	void SetRadius(float radius) { m_radius = radius; }
	WPuppet* GetPet() { return m_pPet; }
	void SetAddTex(int tex) { m_addTex = tex; }

protected:
	CCreature()
		: m_flag(0),
		  m_pPet(NULL),
		  m_time(0.0f),
		  m_pMotion(NULL),
		  m_pHistory(NULL),
		  m_radius(0.0f)
	{
	}

	void Init(const char* name, unsigned long flag);

	unsigned long m_flag;
	Waabb m_area;
	WPuppet* m_pPet;
	int m_addTex;
	WMatrix m_mat;
	float m_time;
	int m_type;
	w_motion_data* m_pMotion;
	WVector m_target;
	float m_rotSpeed;
	float m_speed;
	float m_roll;
	float m_maxRoll;
	float m_rollSpeed;
	float m_cellSize;
	int m_cellNumX;
	int m_cellNumY;
	int m_cellNumZ;
	float m_cellLenX;
	float m_cellLenY;
	float m_cellLenZ;
	int m_historyNum;
	int* m_pHistory;
	unsigned char m_alpha;
	bool m_bActive;
	float m_radius;
	std::list<sAlpha> m_alphaList;
	std::vector<WVector> m_nodeList;
	unsigned char m_nodeIndex;
	std::vector<WVector> m_recordList;
	unsigned char m_recordIndex;
	WMatrix m_recMat;
	float m_recTime;
	float m_recRoll;
	bool m_bRecActive;
	bool m_bRecord;
};

class CGull : public CCreature
{
public:
	CGull(const char* name);
	virtual ~CGull();
};

class CButterfly : public CCreature
{
public:
	CButterfly(const char* name);
	virtual ~CButterfly();
};

class CDuck : public CCreature
{
public:
	CDuck(const char* name, int num);
	virtual ~CDuck()
	{
		if (m_pMat)
		{
			delete[] m_pMat;
			m_pMat = NULL;
		}
	}

	virtual void Process(float dt);
	virtual void Display();
	virtual void SetArea(const Waabb& area, unsigned long flag);

protected:
	int m_num;
	WMatrix* m_pMat;
};

class CMole : public CCreature
{
public:
	CMole(const char* name);
	virtual ~CMole() { }

	virtual void PlayEvent();
};

class CDolphin : public CCreature
{
public:
	CDolphin(const char* name);
	virtual ~CDolphin() { }

	virtual void PlayEvent();
};

class CCrab : public CCreature
{
public:
	CCrab(const char* name);
	virtual ~CCrab() { }

	virtual void PlayEvent();
};

class CSparrow : public CCreature
{
public:
	CSparrow(const char* name, int num);
	virtual ~CSparrow()
	{
		if (m_pMat)
		{
			delete[] m_pMat;
			m_pMat = NULL;
		}
	}

	virtual void Display();
	virtual void PlayEvent();

protected:
	int m_maxNum;
	int m_num;
	WMatrix* m_pMat;
};

class CSanta : public CCreature
{
public:
	CSanta(const char* name);
	virtual ~CSanta();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	float m_velY;
	int m_phase;
};

class CFighter : public CCreature
{
public:
	CFighter(const char* name);
	virtual ~CFighter();

	virtual void CheckTarget(float dt);

protected:
	float m_velY;
	int m_phase;
};

class CUfo : public CCreature
{
public:
	CUfo(const char* name);
	virtual ~CUfo();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	float m_velY;
	int m_phase;
};

class ntPenguin : public CCreature
{
public:
	ntPenguin(const char* name);
	virtual ~ntPenguin();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	float m_velY;
	int m_phase;
};

class ntPenguin_Sailor : public CCreature
{
public:
	ntPenguin_Sailor(const char* name);
	virtual ~ntPenguin_Sailor();

	virtual void Process(float dt);
	virtual void Display();
	virtual void CheckTarget(float dt);

protected:
	float m_scale;
	bool m_bWalk;
};

class ntPenguin_Duck : public CCreature
{
public:
	ntPenguin_Duck(const char* name, int num);
	virtual ~ntPenguin_Duck();

	virtual void SetArea(const Waabb& area, unsigned long flag);
	virtual void Process(float dt);
	virtual void Display();

protected:
	bool m_bWalk;
	int m_num;
	WMatrix* m_pMat;
	float* m_pScale;
};

class ntCatmullRom
{
public:
	ntCatmullRom();
	~ntCatmullRom();

	bool Init(const WVector* point, const float* time, int num);
	void Clean();
	WVector Evaluate(float t);
	WVector Velocity(float t);
	WVector Acceleration(float t);
	float ArcLength(float t1, float t2);
	float FindParameterByDistance(float t1, float dist);

protected:
	float SegmentArcLength(int seg, float u1, float u2);

	WVector* m_pPoint;
	float* m_pTime;
	float* m_pLength;
	float m_totalLength;
	int m_num;
};

class ntNpc_Dragon : public CCreature
{
public:
	ntNpc_Dragon(const char* name, float delay);
	virtual ~ntNpc_Dragon();

	virtual void Process(float dt);
	virtual void Display();
	virtual void SetArea(const std::vector<WVector>& node, float time,
		unsigned long flag);
	virtual void CheckTarget(float dt);

protected:
	unsigned long m_reserved;
	bool m_bWait;
	float m_delay;
	float m_t;
	ntCatmullRom m_spline;
};

class ntNpc_BlackSparrow : public CCreature
{
public:
	ntNpc_BlackSparrow(const char* name);
	virtual ~ntNpc_BlackSparrow();

	virtual void Process(float dt);
	virtual void Display();
	virtual void CheckTarget(float dt);

protected:
	bool m_bFly;
};

class ntNpc_PolaShip : public CCreature
{
public:
	ntNpc_PolaShip(const char* name, float delay);
	virtual ~ntNpc_PolaShip();

	virtual void Process(float dt);
	virtual void Display();
	virtual void SetArea(const std::vector<WVector>& node, float time,
		unsigned long flag);
	virtual void CheckTarget(float dt);

protected:
	unsigned long m_reserved;
	bool m_bWait;
	float m_delay;
	float m_t;
	ntCatmullRom m_spline;
};

class ntNpc_PolaPenguin1 : public CCreature
{
public:
	ntNpc_PolaPenguin1(const char* name, float speed);
	virtual ~ntNpc_PolaPenguin1();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	void FindTarget();
};

class ntNpc_PolaPenguin2 : public CCreature
{
public:
	ntNpc_PolaPenguin2(const char* name);
	virtual ~ntNpc_PolaPenguin2();

	virtual void Process(float dt);
	virtual void Display();
	virtual void CheckTarget(float dt);

protected:
	void FindTarget();
	bool IsSlidable();

	bool m_bWalk;
};

class CNPC_BIRD : public CCreature
{
public:
	CNPC_BIRD(const char* name, float speed);
	virtual ~CNPC_BIRD();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	void FindTarget();
};

class CNPC_PARROT : public CCreature
{
public:
	CNPC_PARROT(const char* name);
	virtual ~CNPC_PARROT();
};

class CNPC_TORTOISE : public CCreature
{
public:
	CNPC_TORTOISE(const char* name, float speed);
	virtual ~CNPC_TORTOISE();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	float m_velY;
	int m_phase;
};

class CNPC_TRSHIP : public CCreature
{
public:
	CNPC_TRSHIP(const char* name, float speed);
	virtual ~CNPC_TRSHIP();

	virtual void Process(float dt);
	virtual void Display();
	virtual void SetArea(const std::vector<WVector>& node, float time,
		unsigned long flag);
	virtual void CheckTarget(float dt);

protected:
	float m_t;
	float m_speed2;
	bool m_bStart;
	ntCatmullRom m_spline;
};

class CDisposable : public CCreature
{
public:
	CDisposable(const char* name);
	virtual ~CDisposable() { }

	virtual void PlayEvent();
};

class COnGameNet : public CCreature
{
public:
	COnGameNet(const char* name, unsigned char index);
	virtual ~COnGameNet();

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	unsigned char m_index;
	WMatrix m_headMat;
	int m_camTex;
};

class ntNpc_AreaWalker : public CCreature
{
public:
	struct MotionMap
	{
		int rate;
		std::string name;
	};

	ntNpc_AreaWalker(const char* name);
	virtual ~ntNpc_AreaWalker() = 0;

	virtual void Process(float dt);
	virtual void CheckTarget(float dt);

protected:
	virtual void ConstructNextMotion() = 0;
	void FindTarget();
	void SelectNextMotion();
	void AddWalkingMotion(const char* name);

	std::vector<std::string> m_walkingMotion;
	bool m_bWalking;
	std::map<std::string, std::list<MotionMap> > m_motionMap;
};

class ntNpc_NodeWalker : public CCreature
{
public:
	ntNpc_NodeWalker(const char* name, float speed);
	virtual ~ntNpc_NodeWalker() = 0;

	virtual void Process(float dt);
	virtual void SetArea(const std::vector<WVector>& node, float time,
		unsigned long flag);
	virtual void CheckTarget(float dt);

protected:
	void MakeSpline(const std::vector<WVector>& node, float& length,
		ntCatmullRom& spline);

	float m_length;
	float m_dist;
	ntCatmullRom m_spline;
};

class ntNpc_WizCityNode : public ntNpc_NodeWalker
{
public:
	ntNpc_WizCityNode(const char* name, float speed);

	virtual void Display();
	void SetScale(float scale) { m_scale = scale; }

protected:
	float m_scale;
};

class ntNpc_WizCityArea : public ntNpc_AreaWalker
{
public:
	ntNpc_WizCityArea(const char* name);

	virtual void Display();
	void SetScale(float scale) { m_scale = scale; }

protected:
	virtual void ConstructNextMotion();

	float m_scale;
};
