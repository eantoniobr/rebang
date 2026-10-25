#pragma once

#include "actor.h"
#include "scenemanager.h"

class CBallTrace;
class CBallTrack;
class CBallWindTrack;
class CSkidMark;
class CComet;
class CDoughnut;
class CPuttLine;
class ntSkidMark_Cobra;
class ntExplodeMark;

class CTrajectory : public IActor, public CRenderFuncPtr
{
protected:
	CTrajectory();

public:
	virtual ~CTrajectory() { }
	DECLARE_OBJECT(CTrajectory)

	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnProcess(float delta);
	virtual void OnDestroy();
	virtual void HandleMsg(const MsgObject& msg);

	virtual void Display();

private:
	CBallTrace* m_pTrace[2];
	CComet* m_pComet;
	CDoughnut* m_pDoughnut;
	CPuttLine* m_pPuttLine;
	CBallTrack* m_pBallTrack;
	CSkidMark* m_pSkidMark;
	CBallWindTrack* m_pBallWindTrack;
	CPuttLine* m_pPuttLines[32];
	CPuttLine* m_pLastPuttLine;
	ntSkidMark_Cobra* m_pSkidMarkCobra;
	ntExplodeMark* m_pExplodeMark;
};

class CBallTrace
{
public:
	CBallTrace();

	virtual ~CBallTrace() { }

	virtual void Init() = 0;
	virtual void Process(float delta) = 0;
	virtual void Display() = 0;

protected:
	virtual void Generate() { }
	virtual void BlowAway(float delta, int dir) { }

	int m_reserved;
	int m_texHandle;
	int m_genNum;
	int m_genIndex;
	float m_genTime;
	float m_genInterval;
	bool m_bActive;
	WTVertex* m_vl[5];
	WTVertex m_vtx[4];
};

class CBallTrack : public CBallTrace
{
public:
	CBallTrack();
	virtual ~CBallTrack();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

private:
	void UpdateRainbowEffect(float delta);

	struct sPoint
	{
		WVector pos1;
		WVector pos2;
		float alpha;

		sPoint() { alpha = 1.0f; }
	};

	struct sPointEx
	{
		bool bActive;
		float scale;
		WVector center;
		WVector side;
	};

	sPoint* m_pPoint;
	bool m_bRainbow;
	sPointEx* m_pPointEx;
	int m_rainbowTexHandle;
	int m_pointNum;
	float m_alpha;
	float m_fadeTime;
	float m_fadeDuration;
	float m_maxAlpha;
	int m_lastFrame;
};

class CSkidMark : public CBallTrace
{
public:
	CSkidMark();
	virtual ~CSkidMark();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

	void SetFrame(int start, int end);

protected:
	unsigned char GetPointAlpha(int index, int frame);

	struct sPoint
	{
		WVector pos[2];
		unsigned char alpha;
	};

	sPoint* m_pPoint;
	int m_pointNum;
	int m_curPoint;
	int m_startFrame;
	int m_endFrame;
	int m_lastFrame;
};

class CBallWindTrack : public CBallTrace
{
public:
	CBallWindTrack();
	virtual ~CBallWindTrack();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

private:
	struct sLineEffect
	{
		WVector start;
		WVector end;
		int alpha;
		float length;
		bool bActive;
	};

	sLineEffect* m_pLineEffect;
	CBallTrack m_ballTrack;
	float m_lineFactor;
	WVector m_prevCamPos;
	WVector m_camMove;
};

class CComet : public CBallTrace
{
public:
	CComet();
	virtual ~CComet();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

protected:
	virtual void Generate();

private:
	WVector m_point[20][2];
	float m_length;
	unsigned char m_reserved2b8[4];
	float m_alpha;
	int m_cometTexHandle;
	int m_tailNum;
	WVector m_tail[2];
};

class CDoughnut : public CBallTrace
{
public:
	CDoughnut();
	virtual ~CDoughnut();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

private:
	struct sParticle
	{
		float size;
		float alpha;
		bool bActive;
		WMatrix mat;
	};

	sParticle* m_pParticle;
};

class CPuttLine : public CBallTrace
{
public:
	CPuttLine();
	virtual ~CPuttLine();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

	bool IsKeep();
	int HowOldAreYou();
	void RemoveUnkeptAlpha();

private:
	struct sPoint
	{
		int alpha;
		WVector pos[2];
	};

	sPoint* m_pPoint;
	int m_lastPoint;
	unsigned long m_createTime;
};

class ntSkidMark_Cobra : public CBallTrace
{
public:
	ntSkidMark_Cobra();
	virtual ~ntSkidMark_Cobra();

	virtual void Init();
	virtual void Process(float delta);
	virtual void Display();

	void SetFrame(int start, int end);

private:
	struct sPoint
	{
		WVector pos[2];
	};

	sPoint* m_pPoint;
	int m_pointNum;
	int m_curPoint;
	int m_startFrame;
	int m_endFrame;
	int m_lastFrame;
};

class ntExplodeMark
{
public:
	ntExplodeMark();
	~ntExplodeMark();

	void Init(const WVector& pos);
	void Uninit();
	void Process();
	void Display();

	bool m_bActive;
	int m_texHandle;
	WVector m_pos;
};
