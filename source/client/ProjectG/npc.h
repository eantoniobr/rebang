#pragma once

#include <list>
#include <vector>
#include "scenemanager.h"

struct w_motion_data;

class CCreature : public CRenderFuncPtr
{
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
