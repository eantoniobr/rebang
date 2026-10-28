#pragma once

#include <queue>
#include <map>
#include <string>
#include <vector>
#include "taskmain.h"

enum eMacroType
{
	MACRO_NONE = 0,
	MACRO_KEY = 1,
	MACRO_REPEAT_KEY = 2,
	MACRO_STOP_REPEAT_KEY = 3,
	MACRO_BUTTON = 4,
	MACRO_MOVE_CURSOR = 5,
	MACRO_SET_CURSOR = 6,
	MACRO_CURSOR_TO_SLOT = 7,
	MACRO_MISSION = 8,
	MACRO_TIP = 9,
	MACRO_TIP_CADDIE = 10,
	MACRO_TIP_ARROW = 11,
	MACRO_WAIT_INPUT = 12,
	MACRO_TIP_IMAGE = 13,
	MACRO_CADDIE_FACE = 14,
	MACRO_ENABLE_SELECT = 15,
	MACRO_OVERLAY_SHOW = 16,
	MACRO_OVERLAY_SHOW_SCREEN = 17,
	MACRO_OVERLAY_HIDE = 18,
	MACRO_OVERLAY_MOVE = 19,
	MACRO_QUIZ = 20,
	MACRO_TARGET = 21,
	MACRO_SENDMSG = 22,
	MACRO_SHOW_CURSOR = 23,
	MACRO_BLOCK_INPUT = 24,
	MACRO_FREE_INPUT = 25,
	MACRO_NEXT_STEP = 26,
	MACRO_SPECIAL = 27,
	MACRO_POWER = 28,
	MACRO_KEY_PRESS = 29,
	MACRO_BLOCK_MOUSE = 30,
	MACRO_FREE_MOUSE = 31,
};

class FrQuizDlg;

struct sMacro
{
	eMacroType type;
	char param[32];
	int delay;
};

class AnimatedOverlay
{
public:
	AnimatedOverlay();
	~AnimatedOverlay();

	void SetSourceOverlay(const char* name, int column, int row, int mode,
		float width, float height);
	void Activate(bool bActivate, bool bFade, bool bLoop);
	void Process(float delta);
	void Render();

	bool IsActivate() { return m_bActive; }

protected:
	void GetNextOverlay();

public:
	WRect m_rect;
	float m_interval;
	WRect m_srcRect;
	float m_elapsed;
	int m_frame;
	int m_frameNum;
	bool m_bRender;
	bool m_bActive;
	bool m_bLoop;
	int m_fade;
	float m_alpha;
	WOverlay* m_pOverlay;
	int m_column;
	std::vector<WOverlay*> m_overlayList;
};

class CTutorial : public CTaskMain
{
public:
	DECLARE_OBJECT(CTutorial)

protected:
	CTutorial();

public:
	virtual ~CTutorial();

	virtual void OnInit();
	virtual void OnLoad();
	virtual void OnProcess(float delta);
	virtual void OnDisplay();
	virtual void OnDestroy();
	virtual void HandleMsg(const MsgObject& msg);

protected:
	bool CheckMissionComplete();
	void BlockInput();
	void FreeInput();
	char* GetLine(char* src, char* dst);
	void IsPractice();
	void ReviewTutorial();
	void MoveNextStep();
	void MissionComplate();
	void PrepareMission();
	void SkipMission();
	void OnImageLoad();
	void Again_Msg(bool bAgain);
	void ChanceOverlay();
	void PriviewOverlay();
	bool OnTipFormResult(int result, FrForm* form);
	bool OnCompleteFormResult(int result, FrForm* form);
	bool OnReviewFormResult(int result, FrForm* form);
	bool OnSkipMissionFormResult(int result, FrForm* form);
	bool OnPracticeFormResult(int result, FrForm* form);
	void OpenTipCaddieForm(const char* text,
		bool (FrCmdTarget::*handler)(int, FrForm*));
	bool OnTipCaddieFormResult(int result, FrForm* form);
	bool OnTipCaddieReopenQuizResult(int result, FrForm* form);
	bool OnTipCaddieNoneResult(int result, FrForm* form);
	void OpenMissionForm();
	bool OnMissionFormResult(int result, FrForm* form);
	void OpenQuizForm(int type);
	bool OnQuizFormResult(int result, FrForm* form);
	void OpenMissionFailedForm();
	bool OnMissionFailedFormResult(int result, FrForm* form);

	void PushMacroCamera();
	void PushMacroClub();
	void PushMacroShot();
	void PushMacroGreen();
	void PushMacroGauge();
	void PushMacroGround();
	void PushMacroItemUse();
	void PushMacroScore();
	void PushMacroHoleIn();
	void PushMacroWindReading();
	void PushMacroBallMove();
	void PushMacroBallSlope();
	void PushMacroHitPoint();
	void PushMacroHitPointMission();
	void PushMacroPowerSpin();
	void PushMacroPowerCurve();

private:
	void InitTutorialMode(int mode);
	bool CheckCameraTarget();
	bool CheckClubTarget();
	WVector* GetPoint(const char* name);
	void PushMacro(eMacroType type, const char* param, int delay, int count);
	void PopSpecial();
	void PopMacro();
	void ClearMacro();

protected:
	std::queue<sMacro*> m_macroPtrQueue;
	std::queue<sMacro> m_macroQueue;
	int m_delay;
	char m_repeatKey[16];
	bool m_bKeyPress;
	int m_state;
	int m_tutorialIndex;
	int m_failCount;
	int m_hitCount;
	std::map<int, std::string> m_textMap;
	int m_cameraTargetCount;
	float m_screenX;
	float m_screenY;
	FrForm* m_pTipForm;
	FrForm* m_pResultForm;
	FrForm* m_pReviewForm;
	FrForm* m_pCaddieForm;
	FrButton* m_pSelectButton;
	int m_caddieFace;
	int m_selectButton;
	FrForm* m_pMissionForm;
	WOverlay* m_pMissionImage;
	FrQuizDlg* m_pQuizForm;
	int m_quizType;
	unsigned long m_itemTypeId[10];
	bool m_bSkipped;
	int m_skipCount;
	bool m_bPractice;
	bool m_bComplete[15];
	bool m_bRepeatTip;
	int m_repeatTipTime;
	WRect m_tipRect;
	float m_clearScale;
	int m_reserved;
	bool m_bKeepBlockInput;
	bool m_bReserved;
	float m_gaugePos;
	int m_completeCode;
	bool m_bCorrectAnswer;
	AnimatedOverlay m_overlay[26];
	AnimatedOverlay m_chanceOverlay[3];
	AnimatedOverlay m_clearOverlay;
	AnimatedOverlay m_unusedOverlay[2];
	bool m_bBlockInput;
};
