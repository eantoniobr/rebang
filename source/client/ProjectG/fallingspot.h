#pragma once

#include "actor.h"
#include "scenemanager.h"

class C3dFont;
class CClubRangeInfo;
class CSimpleUI;

class CSpot : public IActor, public CRenderFuncPtr
{
protected:
	CSpot();

public:
	virtual ~CSpot() { }

	DECLARE_OBJECT(CSpot)

	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnProcess(float delta);
	virtual void OnDestroy();
	virtual void Display();

	struct sRivalPos
	{
		sRivalPos();
		float rate;
		float progress;
		unsigned char hole;
		WVector srcPos;
	};

protected:
	virtual void HandleMsg(const MsgObject& msg);

	void Rotate();
	void DrawRange();
	void DrawHoleIndicator();
	void DrawIndicator(const WVector& pos, int type);
	void ClipIndicator(int type);

private:
	float GetMovingRate(float t);
	bool UpdateRivals();
	bool _ValidTopViewLineDraw();

	static const unsigned long m_adwColors[5];

protected:
	C3dFont* m_pRangeFont;
	C3dFont* m_pPlayerFont;
	WVector m_pos;
	WVector m_srcPos;
	WVector m_msgPos;
	float m_angle;
	float m_moveRate;
	WVector m_prevOffset;
	WVector m_nextOffset;
	WVector m_targetPos;
	float m_offsetRate;
	int m_groundType;
	float m_rangeAngle;
	bool m_bEnable;
	float m_lineWidth;
	float m_markerSize;
	CClubRangeInfo* m_pClubRangeInfo;
	unsigned long m_color;
	float m_width;
	float m_height;
	int m_texIndicator;
	int m_texFalling;
	int m_texSlope;
	int m_texHoleTarget;
	float m_pulse;
	float m_powerBlend;
	float m_powerPhase;
	float m_powerDir;
	WOverlay* m_pFallIndicator1;
	WOverlay* m_pFallIndicator2;
	WOverlay* m_pSpotLine;
	WOverlay* m_pPlayerPos;
	CSimpleUI* m_pPlayerUI;
	float m_playerAngle;
	int m_texScoreTarget;
	WTVertex* m_pFan[5];
	WTVertex m_vtx[4];
	bool m_bRotate;
	unsigned long m_reserved;
	sRivalPos* m_pRivalPos;
	bool m_bShowPlayer;
	WFont* m_pNameFont;
};
