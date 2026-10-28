#pragma once

class CAniObj
{
public:
	CAniObj()
	{
		m_soundDist = 100.0f;
		m_sound[0] = 0;
	}
	~CAniObj() { }

	unsigned char m_type;
	unsigned long m_startFrame;
	short m_modelId;
	float m_time;
	char m_sound[32];
	float m_soundDist;
};

class CRotObj : public CAniObj
{
public:
	CRotObj() { }
	float m_angle;
	float m_invSize;
};

class CMoveObj : public CAniObj
{
public:
	CMoveObj() { }
	WVector m_start;
	WVector m_end;
	float m_standTime;
	float m_moveTime;
};

class CVtxObj : public CAniObj
{
public:
	CVtxObj() { }
};

class CTranObj : public CAniObj
{
public:
	CTranObj() { }
};
