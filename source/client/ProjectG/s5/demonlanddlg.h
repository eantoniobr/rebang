#pragma once

#include "frform.h"
#include "treasuredlg.h"

class FrDemonNextHole : public FrForm
{
	DECLARE_OBJECT(FrDemonNextHole)
	FrDemonNextHole();
	virtual ~FrDemonNextHole();
	virtual bool OnInit();
	void SetNextHole(int hole);
	void SetState(unsigned char state);

protected:
	void OnAreaPattern_Init(int param);
	void OnAreaPattern_OwnerDraw(int param);
	void OnAreaNextHole_Init(int param);
	void OnAreaNextHole_OwnerDraw(int param);

	FrArea* m_pPattern;
	FrArea* m_pNextHole;
	WOverlay* m_pCoursePage[2];
	WRect m_sourceRect;
	const Bitmap* m_pPatternBitmap;
	int m_imageWidth;
	int m_imageHeight;
	unsigned int m_state;
	int m_page;
	DECLARE_FRESH_MSGMAP()
};

class FrDemonAttackGauge : public FrForm
{
	DECLARE_OBJECT(FrDemonAttackGauge)
	FrDemonAttackGauge();
	virtual ~FrDemonAttackGauge();
	virtual bool OnInit();
	void SetState(unsigned char state);

protected:
	void OnImageBarAttackPoint_Init(int param);
	void OnAreaAttackMarker_Init(int param);
	void OnAreaAttackMarker_OwnerDraw(int param);
	void OnAreaBlingBar_Init(int param);
	void OnAreaBlingBar_OwnerDraw(int param);

	FrGaugeBarImage* m_pAttackGauge;
	FrArea* m_pAttackMarker;
	FrArea* m_pBlingBar;
	const Bitmap* m_pMarkerBitmap;
	const Bitmap* m_pBlingBitmap;
	unsigned int m_state;
	DECLARE_FRESH_MSGMAP()
};

class FrDemonProcessRank : public FrForm
{
	DECLARE_OBJECT(FrDemonProcessRank)
	FrDemonProcessRank();
	virtual ~FrDemonProcessRank();
	virtual bool OnInit();

protected:
	void OnAreaLeaderPet_Init(int param);
	void OnAreaLeaderPet_OwnerDraw(int param);
	void OnListBoxUserInfoList_Init(int param);
	void OnListBoxUserInfoList_OwnerDraw(int param);

	FrArea* m_pLeaderPet;
	FrListBox* m_pUserInfoList;
	unsigned char m_unknown118[8];
	DECLARE_FRESH_MSGMAP()
};

class FrDemonFinalScore : public FrForm
{
	DECLARE_OBJECT(FrDemonFinalScore)
	FrDemonFinalScore();
	virtual ~FrDemonFinalScore();

protected:
	virtual bool OnInit();
	virtual void OnProc(const float dt);

	void OnImageBarAttackPoint_Init(int param);
	void OnInit_Gift_List(int param);
	void OnOwnerDraw_Gift_List(int param);

	FrGaugeBarImage* m_pAttackGauge;
	CBoxOpener m_boxOpener;
	DECLARE_FRESH_MSGMAP()
};

class FrDemonLandTicket : public FrForm
{
	DECLARE_OBJECT(FrDemonLandTicket)
	FrDemonLandTicket();
	virtual ~FrDemonLandTicket();
	void SetTicketNumber(int number);

protected:
	void OnInit_TicketMsg_Static(int param);

	FrStatic* m_pTicketMessage;
	int m_ticketNumber;
	DECLARE_FRESH_MSGMAP()
};

enum eDemonDlg
{
	DEMON_NEXT_HOLE,
	DEMON_ATTACK_GAUGE,
	DEMON_PROCESS_RANK,
	DEMON_FINAL_SCORE
};

class CDemonLandForm
{
public:
	CDemonLandForm();
	~CDemonLandForm();
	void InitializeForm();
	FrDemonNextHole* GetDemonNextHole();
	FrDemonAttackGauge* GetDemonAttackGauge();
	FrDemonProcessRank* GetDemonProcessRank();
	FrDemonFinalScore* GetDemonFinalScore();
	void AdjustWindowPos();
	bool CreateDemonLandForm(eDemonDlg dlg);

private:
	void ReleaseForm();
	void AdjustNextHolePos(WRect& rect);
	void AdjustAttackGaugePos(WRect& rect);

	FrDemonNextHole* m_pNextHole;
	FrDemonAttackGauge* m_pAttackGauge;
	FrDemonProcessRank* m_pProcessRank;
	FrDemonFinalScore* m_pFinalScore;
};
