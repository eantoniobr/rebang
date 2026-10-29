#pragma once

#include <map>

#include "wmath.h"
#include "finitestatemachine.h"
#include "wfont.h"
#include "wlist.h"
#include "woverlay.h"
#include "contentsdoc.h"
#include "caddiebonus.h"

class WTitleFont;
class CSimpleUI;

static const int s_clearBonusTable[20] = { 20, 50, 55, 80, 65, 24, 50, 70, 40,
	55, 40, 20, 0, 80, 20, 20, 40, 40, 0, 40 };
static const float s_minDistance = 1.f;
static const float s_maxMoveSpeed = 15.f;
static const float s_half = .5f;
static const float s_accuracyScale = .35f;
static const float s_angleStep = .017453292f;

class CFontInfo
{
public:
	struct sFontInfo : public tagWTITLEFONT
	{
		int m_index;
		char m_name[0x20];
	};

	struct sFont
	{
		WTitleFont* pFont;
		sFontInfo* pInfo;
	};

	CFontInfo();
	virtual ~CFontInfo();
	virtual void Process(float fDelta) { }

	virtual void Display(void) { }
	virtual void Init(char* pszName, sFont* pFont);
	virtual void GetScreenPos(float* pfX, float* pfY) { }

	void SetColor(unsigned long color) { m_color = color; }

	virtual void Reset(void) { }

	void Clear(void);
	float GetTextWidth(const char* text, float space, float scale);
	float GetExactTextWidth(const char* text, float space, float scale);
	float Print(float x, float y, const char* text, float space, int flag,
		float scale, sFont* pFont);

protected:
	char*& Buffer(void) { return m_buffer; }

	static bool m_loaded;
	static WList<sFontInfo*> m_fontList;

	sFont m_font;
	unsigned long m_color;
	int m_align;
	char* m_buffer;

private:
	void AddFont(const char* name, int fontw, int fonth, int numPages, int texw,
		int texh, char* charSet);
};

class CDistToHoleInfo : public CFontInfo
{
public:
	CDistToHoleInfo(void);

	virtual void Process(float fDelta);
	virtual void Display(void);
	virtual void Reset(void);
	virtual void ResetUiPosition(void);

	void Fix(void);

private:
	float m_fDistance;
	int m_nState;
	float m_fTime;
	float m_fBlend;
	float m_uiX;
	float m_uiY;
	float m_fScale;
	WVector m_curPos;
	WVector m_fixPos;
	float m_fAlpha;
	float m_fOffsetX;
	char m_reserved54[4];
};

class CHoleCupInfo : public CFontInfo
{
public:
	CHoleCupInfo(void);
	virtual ~CHoleCupInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);
	virtual void GetScreenPos(float* pfX, float* pfY);
	virtual void Reset(void);

	void Fix(void);
	void ResetUiPosition(void);

private:
	float m_screenX;
	float m_screenY;
	float m_fCupHeight;
	WOverlay* m_pTopHoleOverlay[3];
	int m_nDisplayMode;
	CDistToHoleInfo* m_pDistToHole;
};

class CTimeOutInfo : public CFontInfo
{
public:
	CTimeOutInfo(void);

	virtual void Process(float fDelta);
	virtual void Display(void);
	virtual void Reset(void);

private:
	int m_nState;
	float m_fAlpha;
	float m_fTime;
};

class CShotCountInfo : public CFontInfo
{
public:
	CShotCountInfo(void);
	virtual ~CShotCountInfo();

	virtual void Process(float fDelta);

	void StartFloating(void);
	void Display(float x, float y, unsigned char nPlayer);

private:
	WOverlay* m_pCoinOverlay;
	unsigned char m_alpha;

	float m_fFloatTime;
	int m_nFloatCount;
	sFont m_redFont;
	sFont m_greyFont;
	sFont m_blueFont;
};

class CHoleInfo : public CFontInfo
{
public:
	CHoleInfo(void);
	virtual ~CHoleInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);
	virtual void Reset(void);

	void Flicker(void);
	void Fix(void);
	void ResetUiPosition(void);

private:
	struct sItem
	{
		float baseX, baseY;
		float curX, curY;
		float fixX, fixY;
		float scale;
	};

	sItem m_items[4];
	float m_fAlpha[2];
	float m_fTime;
	int m_nFlickerTime;
	int m_nState;
	CSimpleUI* m_pCourseUI;
	CSimpleUI* m_pHoleUI;
	CSimpleUI* m_pStartPosiUI;
	CSimpleUI* m_pPlayerNumUI;
	CSimpleUI* m_pEmotiUI;
	WOverlay* m_pShuffleBonusOverlay;
	WOverlay* m_pCompleteOverlay;
	WOverlay* m_pScoreEventOverlay;
	WOverlay* m_pExtraStageOverlay;
	WOverlay* m_pExtraStageSmallOverlay;
	WOverlay* m_pCoin1Overlay;
	WOverlay* m_pCoin2Overlay;
	WOverlay* m_pCoin3Overlay;
	WOverlay* m_pMapBonusOverlay;
	WOverlay* m_pSkinsPang1Overlay;
	WOverlay* m_pSkinsPang3Overlay;
	WOverlay* m_pApproachOverlay;
	unsigned char m_firstPlayer;
	int m_nEmoti;
};

class CAccuracyInfo : public CFontInfo
{
public:
	CAccuracyInfo(void);
	virtual ~CAccuracyInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);

	void SetPower(void);
	void SetAccuracy(void);

private:
	char*& Buffer2(void) { return m_buffer2; }

	bool m_bFlicker;

	float m_fAlpha;
	CSimpleUI* m_pImpactUI;
	float m_fTextX;
	char* m_buffer2;
};

class CGuildInfo : public CFontInfo
{
public:
	CGuildInfo(void);
	virtual ~CGuildInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);

	void SetScore(int nScore1, int nScore2);

protected:
	char*& Buffer2(void) { return m_buffer2; }

	char m_reserved18[4];
	float m_fTime;
	float m_fScale;
	sFont m_leftFont;
	sFont m_rightFont;
	char* m_buffer2;
	int m_targetScore[2];
	int m_displayScore[2];
	const char* m_pszSound;
};

class CClubRangeInfo : public CFontInfo
{
public:
	CClubRangeInfo(void);

	virtual void Display(void);

	void SetPos(const WVector& vPos) { m_pos = vPos; }

private:
	friend class CSpot;

	WVector m_pos;
};

class CPowerInfo : public CFontInfo
{
public:
	CPowerInfo(void);

	virtual void Display(void);

	void SetPos(const WVector& vPos) { m_pos = vPos; }

private:
	WVector m_pos;
};

class CWindInfo : public CFontInfo
{
public:
	CWindInfo(void);

	virtual void Display(void);
};

class CBonusInfo : public CFontInfo
{
public:
	CBonusInfo(void);
	virtual ~CBonusInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);

private:
	WOverlay* m_pPangOverlay;
	WOverlay* m_pPcBangOverlay;
	float m_fTime;

	__int64 m_awardPang;
	__int64 m_extraPang;
	__int64 m_auxPartPang;
	__int64 m_itemPang;
	__int64 m_totalPang;
	std::map<unsigned long, WOverlay*> m_overlays;
	WOverlay* m_pEventOverlay;
};

class CRemainTimeInfo : public CFontInfo
{
public:
	CRemainTimeInfo(void);

	virtual void Display(void);
};

class CTotalDistInfo : public CFontInfo
{
public:
	CTotalDistInfo(void);

	virtual void Display(void);

private:
	float m_fDistance;
};

class CClubTypeInfo : public CFontInfo
{
public:
	CClubTypeInfo(void);

	virtual void Display(void);
};

class CCalipers : public CFontInfo
{
public:
	CCalipers(void);
	virtual ~CCalipers();

	virtual void Process(float fDelta);
	virtual void Display(void);
	virtual void Reset(void);

	void SetEvent(int nEvent);
	void MoveNone(void);
	void MoveLeft(void);
	void MoveRight(void);
	void KeyInputEnd(void);
	void ResetBar(void);
	void ExecuteKeyAction(int nKey);
	void ChangeKeyState(void);
	void SetCalipersLimit(float fLimit);
	void DrawShotPowerRange(float& fPos, bool bImpact);
	void DrawLimitLine(float& fPos, bool bImpact);
	void ProcKeyState(float fDelta);
	void KeyCheck(float fDelta);
	bool IsVisiblePowerBar(void) const
	{
		return m_nPowerBarState == 1 ? true : false;
	}

	void VisiblePowerBar(int nState) { m_nPowerBarState = nState; }

private:
	FiniteStateMachine m_fsm;
	float m_fCursorPos;
	float m_fDisplayPos;
	unsigned long m_prevKeyFlags;
	unsigned long m_keyFlags;
	unsigned long m_prevState;
	unsigned long m_curState;
	bool m_bPowerFixed;
	bool m_bAccuracyFixed;

	float m_fBarScale;
	float m_fMoveSpeed;
	int m_nPowerBarState;
	WOverlay* m_pIndicatorOverlay;
	WOverlay* m_pCalipersOverlay;
	bool m_bKeyMoving;

	float m_fMoveDelta;
	float m_fSoundTime;
	bool m_bSoundPlayed;
	bool m_bResetFlag;
};

struct PangOverlayInfo
{
	unsigned int m_overlay;
	unsigned int m_height;
	unsigned int m_width;
};

extern PangOverlayInfo g_holeInPangOverlayInfo[];
extern PangOverlayInfo g_specialShotPangOverlayInfo[][4];

class CPangInfo : public CFontInfo
{
public:
	struct sPangCase
	{
		union
		{
			unsigned long m_flags;
			struct
			{
				unsigned int m_state : 12;
			};
		};

		__int64 m_pang;
		int m_nIndex;
		float m_fTime;
		float m_fY;
		float m_fTargetY;
		unsigned int m_nOverlay;
		WRect m_rect;
		unsigned char m_byAlpha;
	};

	CPangInfo(void);
	virtual ~CPangInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);

	void Skip(void);
	void Restore(void);
	void ChangeTurn(void);
	void ShowMyPang(void);
	void PreCalcMatchHoleInBonus(void);
	void PreCalcTeamHoleInBonus(void);
	void PreCalc(bool bFlag);
	bool IsFinalized(void) { return (m_flags & 0x10) ? true : false; }

protected:
	void ResetVars(int nFlags, int nCaseState);
	void Record(unsigned char index, __int64* pangs);
	void ProcessHappyBonus(float fDelta);
	void ProcessAztecBonus(float fDelta);
	void ProcessAngelBonus(float fDelta);
	void ProcessDevilBonus(float fDelta);
	void Insert(int nCase);
	void UpdateBallState(void);
	void Approach(void);
	void LongPutt(void);
	void Multiply(int nCase, int nMultiply);
	void SuperPangya(void);
	void BeamImpact(void);
	void SpecialShot(void);
	void NiceRecovery(void);
	void HoleIn(void);
	void DormieBonus(void);
	void HappyBonus(void);
	void AztecBonus(void);
	void ClearBonus(void);
	void AngelWingBonus(void);
	void DevilWingBonus(void);
	void MascotBonus(void);
	void AbilityItemBonus(void);
	void RecoveryBonus(void);
	void MakeDecision(int nCase, bool bSuccess);
	void GetHoleInOverlayInfo(int nScore, int nPar, unsigned int& overlay,
		float& fWidth, float& fHeight);
	void GetSpecialShotOverlayInfo(unsigned long flags, unsigned char index,
		unsigned int& overlay, float& fWidth, float& fHeight);
	__int64 GetHoleInPang(int nScore, int nPar);
	void LongDrive(void);
	void ProcessTotal(float fDelta);
	void ProcessCases(float fDelta);
	void CheckReadyToMakeDecision(void);
	void CheckReadyToFinalize(float fDelta);
	void LongChipIn(void);
	void ClashCombo(void);
	void AztecBonusWater(void);
	void GimmickItem(GIMMICK_ITEM_TYPE itemType);
	void Display_TotalPang(void);
	void Display_TotalGimmickNum(void);

public:
	void ResetUiPosition(void);

private:
	struct sHoleInPang
	{
		__int64 m_holeInOne;
		__int64 m_albatross;
		__int64 m_eagle;
		__int64 m_birdie;
		__int64 m_par;
		__int64 m_perStroke;
	};

	WOverlay* m_pPangOverlay[2];
	unsigned long m_flags;
	const char* m_pszSfx;
	__int64 m_pangs[4];
	__int64 m_bonusPangs[4];
	__int64 m_shownPangs[4];
	__int64 m_extraPangs[4];
	sPangCase m_totalCases[4];
	sPangCase m_cases[24];
	WVector m_aimDir;
	int m_nPangRate;
	int m_nClubType;
	int m_nStartGround;
	float m_fLongestDrive;
	float m_fStartToPin;
	float m_fDriveDistance;
	float m_fToPin;
	int m_nState;
	int m_nSubState;
	float m_fPopupX;
	float m_fPopupY;
	float m_uiPos[8][2];
	float m_fHappyBonusTime;
	float m_fAztecBonusTime;
	float m_fAngelBonusTime;
	float m_fDevilBonusTime;
	float m_fFinalizeTime;
	int m_nBonusEffects;
	unsigned char m_bReserved;

	__int64 m_turnExtraPangs[4];
	int m_nWaterHits;
	int m_nLastWaterHit;
	unsigned int m_nTotalOverlay;
	WRect m_totalRect;
	CCaddieBonus m_caddieBonus;
	sHoleInPang m_holeInPangs[20];
};

class CFlyInfo : public CFontInfo
{
public:
	CFlyInfo(void);
	virtual ~CFlyInfo();

	virtual void Process(float fDelta);
	virtual void Display(void);

private:
	void CalcDistance(void);

	float m_fTime;
	CSimpleUI* m_pGroundUI;
	CSimpleUI* m_pGroundTextUI;
	WOverlay* m_pApproachOutOverlay;
	float m_fGroundAlpha;
	float m_fCarryAlpha;
	float m_fToPinAlpha;
	float m_fCarry;
	float m_fToPin;
	char m_szGround[8];
};

class CExtraHoleInfo : public CFontInfo
{
public:
	CExtraHoleInfo(void);
	virtual ~CExtraHoleInfo();

	virtual void Display(void);

	void SetShotTime(unsigned long time);
	void UpdateLeader(void);

private:
	unsigned long m_shotTime[4];
	CSimpleUI* m_pPlayerNumUI;
	unsigned char m_leader;
	unsigned long m_cupDistance[4];
};

class CHolePoseSkins : public CFontInfo
{
public:
	CHolePoseSkins(void);
	virtual ~CHolePoseSkins();

	virtual void Process(float fDelta);
	virtual void Display(void);

	void SetPose(int nResult, int nValue);

private:
	WOverlay* m_pWinOverlay[3];
	WOverlay* m_pLoseOverlay[2];
	WOverlay* m_pDrawOverlay[2];
	WOverlay* m_pPoseOverlay[2];
	int m_nValue;
	int m_nResult;
	float m_fAlpha;
	float m_fScale;
	int m_nState;
};

struct sPlayerData;

int GetAngelBonus(sPlayerData* player);

class CFontOverlay
{
public:
	CFontOverlay(void);
	~CFontOverlay();

	void Init(void);
	void Process(float fDelta);
	void Display(void);
	void ResetUiPosition(void);

	enum eInfo
	{
		INFO_HOLECUP = 0,
		INFO_FLY = 1
	};

	void FixHoleInfo(void) { m_pHoleInfo->Fix(); }
	void FixHoleCupInfo(void) { m_pHoleCupInfo->Fix(); }
	void FlickerHoleInfo(void) { m_pHoleInfo->Flicker(); }
	void ResetHoleInfo(void) { m_pHoleInfo->Reset(); }
	void ResetHoleCupInfo(void) { m_pHoleCupInfo->Reset(); }
	void ResetTimeOutInfo(void) { m_pTimeOutInfo->Reset(); }
	void GetHoleInfoPos(float* pfX, float* pfY)
	{
		m_pHoleCupInfo->GetScreenPos(pfX, pfY);
	}
	void SetAccuracy(void) { m_pAccuracyInfo->SetAccuracy(); }
	void SetActive(eInfo info, bool bActive)
	{
		(&m_bShowHoleCup)[info] = bActive;
	}

private:
	CHoleCupInfo* m_pHoleCupInfo;
	CFlyInfo* m_pFlyInfo;
	CHoleInfo* m_pHoleInfo;
	CAccuracyInfo* m_pAccuracyInfo;
	CTimeOutInfo* m_pTimeOutInfo;
	bool m_bShowHoleCup;
	bool m_bShowFly;
	bool m_bShowHole;
	bool m_bShowAccuracy;
	bool m_bShowTimeOut;
};
