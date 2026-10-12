#pragma once

#include <list>
#include <vector>
#include <string>
#include "ghosttypes.h"
#include "formbar.h"
class FrRecentMatch : public FrForm
{
public:
	DECLARE_OBJECT(FrRecentMatch)

	struct sRecentMatchForm
	{
		unsigned char sex;
		std::string nick;
		unsigned long win;
		unsigned char grade;
		_SYSTEMTIME date;
		unsigned long pang;
	};

	FrRecentMatch();
	virtual ~FrRecentMatch();

	void Init(const std::string& nick, int course, int character, int score,
		int pang);
	void AddHistory(const sRecentMatchForm& form);
	void AddFinish();
	void Exception();

protected:
	void OnInitBgArea(int param);
	void OnDrawBgArea();
	void OnInitHistoryList(int param);
	void OnDrawHistoryList(int param);
	void OnInitStaticText1(int param);

private:
	const Bitmap* m_pCourseImg;
	const Bitmap* m_pCharacterImg;
	const Bitmap* m_pPangImg;
	int m_score;
	int m_pang;
	FrListBox* m_pMatchList;
	std::list<sRecentMatchForm*> m_historyList;
	FrArea* m_pBgArea;
	FrStatic* m_pText;
	WTitleFont* m_pFont;
	std::string m_ghostNick;

	DECLARE_FRESH_MSGMAP()
};

class FrGhostGameMapDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrGhostGameMapDlg)

	struct sImgInfo
	{
		float x;
		float destX;
		float alpha;
		float lockAlpha;
		bool bSelectable;
		bool bLock;
		bool bArrived;
		int course;
		bool bDrawn;
		sImgInfo(float _x, float _destX)
			: x(_x),
			  destX(_destX),
			  alpha(0.0f),
			  lockAlpha(0.0f),
			  bSelectable(false),
			  bLock(false),
			  bArrived(false),
			  bDrawn(false)
		{
		}
		void AnimateLock(float dt);
	};

	struct sImgTag
	{
		const Bitmap* pBg;
		const Bitmap* pInfo;
		WRect bgRect;
		WRect infoRect;
		float x;
		float bgAlpha;
		float infoAlpha;

		void Animate(float dt);
		void Reset();
	};

	FrGhostGameMapDlg();
	virtual ~FrGhostGameMapDlg();

	virtual void OnProc(const float dt);
	void Init(unsigned long uid, const std::string& nick,
		const std::list<GHOST_GAME_BRIEF>& briefList);
	void* GetSelectItem();

protected:
	void OnDownOK();
	void OnDownCancel();
	void OnInitRecentMatch(int param);
	void OnDownRecentMatch();
	void OnInitSelMapList(int param);
	void OnDrawSelMapList(int param);
	void OnDownSelMapList();
	void OnInitAreaSelecText(int param);
	void OnDrawSelecText();
	void OnInitAreaMap(int param);
	void OnDrawChoiceMap(int param);
	void OnInitAreaBg(int param);
	void OnDrawAreaBg(int param);

public:
	std::string GetGhostNick() { return m_ghostNick; }

private:
	std::vector<sImgInfo> m_imgInfo;
	std::vector<sImgTag> m_imgTag;
	std::list<GHOST_GAME_BRIEF> m_briefList;
	unsigned long m_uid;
	std::string m_unused;
	std::string m_ghostNick;
	WRect m_choiceMapRect;
	FrListBox* m_pMapList;
	int m_selCourse;
	FrArea* m_pChoiceText;
	float m_tipAlpha;
	FrButton* m_pRecentBtn;

	DECLARE_FRESH_MSGMAP()
};

class FrGhostTimeBar : public FrFormBar
{
public:
	DECLARE_OBJECT(FrGhostTimeBar)

	FrGhostTimeBar();
	virtual ~FrGhostTimeBar();

	virtual bool Open(FRESH_PFN_RESULT pFnResult, unsigned long flag);

protected:
	virtual void OnProc(const float dt);

	void OnInitMouseArea(int param);
	void OnDrawMouseArea();

private:
	float m_bonusTime;
	float m_closeDelay;
	float m_gaugePos;
	bool m_bFinished;
	FrArea* m_pMouseArea;
	const Bitmap* m_pMouseImg;

	DECLARE_FRESH_MSGMAP()
};

class FrGhostAward : public FrForm
{
public:
	DECLARE_OBJECT(FrGhostAward)

	FrGhostAward();
	virtual ~FrGhostAward();

	virtual void OnProc(const float dt);

	void Init(bool bUserFirst);
	bool IsFinishCalcBonus();
	bool IsLevelUpState();

	int GetAutoBonus() { return m_autoBonus; }
	int GetClickBonus() { return m_clickBonus; }
	unsigned char GetClickCount() { return m_clickCount; }
	int GetBasePang() { return m_basePang; }

	class cPangFx
	{
	public:
		cPangFx();
		~cPangFx();

		bool IsAlive();
		void Create(const WRect& pouch);
		void Proc(float dt);
		void Render(FrGraphicInterface* pDevice);

	private:
		const Bitmap* m_pBitmap;
		WRect m_rect;
		float m_speed;
		float m_alpha;
		float m_endY;
	};

	struct sResultInfo
	{
		std::string nick;
		WPoint pos;
		std::string levelImg;
		int score;
		unsigned long exp;
		bool bGhost;
	};

protected:
	void SetResultInfo(sResultInfo& info, int index);
	void AwardProc(float dt);

	void OnInitDescText(int param);
	void OnInitGaugeText(int param);
	void OnInitGaugeBar(int param);
	void OnInitPouchArea(int param);
	void OnDrawScore(int param);
	void OnDrawPouch(int param);

private:
	FrGhostTimeBar* m_pTimeBar;
	FrArea* m_pPouchArea;
	FrGaugeBar* m_pExpGauge;
	FrStatic* m_pDescText;
	FrStatic* m_pGaugeText;
	unsigned long m_unknown[2];
	std::list<cPangFx*> m_pangFxList;
	float m_elapsedTime;
	unsigned char m_clickCount;
	WTitleFont* m_pFont;
	int m_autoBonus;
	int m_clickBonus;
	int m_basePang;
	float m_displayPang;
	int m_exp;
	int m_remainExp;
	sResultInfo m_result1;
	sResultInfo m_result2;

	DECLARE_FRESH_MSGMAP()
};
