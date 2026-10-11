#pragma once

#include <stack>
#include "encrypttypes.h"

class CGolfBall;
class CGolfRuleBase;
class CSimpleUI;
class FrComboBox;
class FrEmoticonDlg;
class FrOnelineReqDlg;
class FrReplayControlDlg;
class FrApproachResultDlg;
class FrApproachEndDlg;

struct sLadderItem
{
	unsigned long typeIndex;
	unsigned long rate;
};

class CGolfRule : public CTaskMain
{
public:
	DECLARE_OBJECT(CGolfRule)

	friend class CGolfRuleBase;
	friend class CGolfRuleQuickrace;
	friend class CGolfRuleTimeattack;
	friend class CGolfRuleTutorial;

	struct sBackUp
	{
		WVector pos;
		float angle;
		bool bOB;
		unsigned char bunker;
		float gauge;
		__int64 totalPang;
		__int64 bonusPang;
		__int64 pang;
		unsigned long item[10];
		char club[4];
		unsigned char stroke;
		unsigned char flag;
	};

	struct sShotData
	{
		unsigned char hole;
		WVector wind;
		unsigned char weather;
		unsigned char stroke;
		sBar bar;
		WVector pos;
		float angle;
		float curve;
		float spin;
		int pvsFrame;
		unsigned long special;
		unsigned long clubPower;
		char club[4];
		unsigned char bunker;
		unsigned long item;
		float deviation;
		unsigned char holeStroke;
		int pang;
		int bonusPang;
		WCrypticValue<float> gauge;
	};

	CGolfRule();
	virtual ~CGolfRule();

	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnReload();
	virtual void OnProcess(float delta);
	virtual void OnDisplay();
	virtual void OnDestroy();
	virtual void HandleMsg(const MsgObject& msg);

	void SetCurrentGolfRule();
	void AddPlayer(unsigned char index, const char* name, unsigned long uid,
		unsigned long oid, unsigned long caddie);
	void SendHoleData();
	void LoadShot(const char* filename);
	void SaveShot(const char* filename);

protected:
	void SetPlayer();
	void SetGrade();
	void SetReady();
	bool CheckGiveUp();
	bool CheckDropOut();
	bool CheckAllHoleOut();
	bool HaveTeeShots();
	unsigned char GetFirstTurn();
	unsigned char GetNextTurn();
	void ChangeTurn();
	void ReadyForNextTurn();
	bool SetTurnChangeEvent();
	void ResetData(const WVector& pos);
	void ResetRank();
	void ChangeGameMode(unsigned long mode);

	void SetNetMsgWait(bool bWait, int line, char* msg, float time);
	void CheckNetMsgWait_Send(char* msg);
	void CheckNetMsgWait_Recv(char* msg);
	void SendReportError(unsigned char error);
	void EncodePacket(enumClientPacket type, WSendPacket& packet);
	void SendShotResult();
	void SendHoleStat();

	void SetAngle(float angle);
	WMatrix BankCamera(float angle);
	bool GetBarCondition();
	void CalcInputCommand();
	void CommandBox();
	void SetSpecialShot();
	void CheckSpecialShotSpinAndCurve();
	void DriveGauge(float delta, bool bAuto);
	void PuttingGauge(float delta, bool bAuto);
	void HitShot();
	void ReactionForShot();
	bool CanCancelShot();
	void CancelShot();
	void UpdateShotResultStat();
	void CorrectShotResult();
	void SetEnvironmentVariableA();
	void ForcedMoveBall(const WVector& pos);
	void Drop(const WVector& pos);
	void Warp(const WVector& pos);
	void Cancel();
	void Skip();
	void Replay(bool bAuto);
	void CaptureProcess();
	void IntergrateFile(const char* filename);
	void PlayBGM();
	void CheckUserBGM(const char* path);

	void SetHoleInPose(bool bHoleIn);
	bool SetHoleInPose_Skins();
	bool SetHoleInPose_Match();
	bool SetHoleInPose_Team();
	bool IsMaxWithHGParts(unsigned char player);
	unsigned long GetHolePang(unsigned char player);
	__int64 CalcWinnersPang(unsigned long pang);
	void CalcSkinsHolePang();
	void AddPrize(int prize);
	void AddExtPrize();
	void GetWinningPrize(int rank);
	void DispatchMatchItems();
	bool CanMoveToNextHole();
	void RecordPlayerList();
	void RecordPlayerData(unsigned char player);
	void RecordTeamData(unsigned char team);
	void RecordGiveUp(unsigned char player);
	void RecordScoreByPlayer(unsigned char player);
	void RecordScoreByTeam(unsigned char team);
	void ReturnLobby(bool bForce);

	void DoWaitForStart(float delta);
	void DoCoursePreview(float delta);
	void DoPlayerPreview(float delta);
	void DoCloseupCaddie(float delta);
	void DoToDefaultCamera(float delta);
	void DoStand(float delta);
	void DoPowerGauge(float delta);
	void DoDrive(float delta);
	void DoFlyBall(float delta);
	void DoFlyBall_Flying(float delta);
	void DoFlyBall_Stopped(float delta);
	void DoHoleInPose(float delta);
	void DoDespairPose(float delta);
	void DoScoreBoard(float delta);
	void DoTimeOut(float delta);
	void DoGameOver(float delta);
	void DoApproachNextHole(float delta);
	void DoGetReadyToCaptureBG(float delta);
	void DoNavigateCamera(float delta);
	void DoTopViewCamera(float delta);
	void DoFixedCamera(float delta);
	void DoSpotCamera(float delta);
	void DoDebugCamera(float delta);

	bool PauseDlgResult(int result, FrForm* form);
	bool CancelDropDlgResult(int result, FrForm* form);
	bool GoStopDlgResult(int result, FrForm* form);
	bool ContinueDlgResult(int result, FrForm* form);
	bool ReturnToLobbyDlgResult(int result, FrForm* form);
	bool OnReturnLobbyResult(int result, FrForm* form);
	bool OnPlayerInfoDlgResult(int result, FrForm* form);
	bool OnEmoticonResult(int result, FrForm* form);
	bool OnReportResult(int result, FrForm* form);
	bool OnForgetDlgResult(int result, FrForm* form);
	bool OnOnelineReqDlgResult(int result, FrForm* form);
	bool OnOnelineReqChkOutDlgResult(int result, FrForm* form);
	bool OnApproachDlgResult(int result, FrForm* form);
	bool OnApproachEndDlgResult(int result, FrForm* form);

	void SetVisibleUpperBtns(bool bVisible);
	void ToggleCommandBtns(bool bEnable);
	void ResetUiPos_Board();
	void OnChatViewInit(int id);
	void OnChatTargetInit(int id);
	void OnChatTargetBtnDown(int id);
	bool OnChatTargetEnterKey(int id);
	void OnChatInputInit(int id);
	bool OnChatInputEnterKey(int id);
	void OnEmoticonInit(int id);
	void OnEmoticonBtnUp();
	void OnLanguageInit(int id);
	void OnReportInit(int id);
	void OnReportBtnUp();
	void OnSpecialCardInit(int id);
	void OnSpecialCardBtnUp();
	void OnMyInfoInit(int id);
	void OnMyInfoBtnUp();
	void OnOptionInit(int id);
	void OnOptionBtnUp();
	void OnCaddieBookInit(int id);
	void OnCaddieBookBtnUp();
	void OnUnplayableInit(int id);
	void OnUnplayableBtnUp();
	void OnPauseInit(int id);
	void OnPauseBtnUp();
	void OnChatRecordInit(int id);
	void OnChatRecordBtnUp();
	void OnOnelineViewInit(int id);
	void OnOnelineViewOwnerDraw(int id);
	void OnOnelineBtnInit(int id);
	void OnOnelineBtnUp();
	void OnTopBarHoverOn(int id);
	void OnTopBarHoverOff(int id);
	void OnMessengerBtnInit(int id);
	void OnMessengerBtnUp();
	void OnMessengerBubbleEditInit(int id);
	void OnMessenger_AlarmBtnInit(int id);
	void OnMessenger_AlarmBtnUp();
	void OnMessenger_GiftAlarmBtnInit(int id);
	void OnMessenger_GiftAlarmBtnUp();
	void OnReplayStatusInit(int id);
	void OnRadioPredictNormalShotInit(int id);
	void OnRadioPredictTomahwakShotInit(int id);
	void OnRadioPredictCobraShotInit(int id);
	void OnRadioPredictSpikeShotInit(int id);
	void OnRadioPredictNormalShotDown();
	void OnRadioPredictTomahwakShotDown();
	void OnRadioPredictCobraShotDown();
	void OnRadioPredictSpikeShotDown();
	void OnRadioPredictNormalShotDraw(int id);
	void OnRadioPredictTomahwakShotDraw(int id);
	void OnRadioPredictCobraShotDraw(int id);
	void OnRadioPredictSpikeShotDraw(int id);

private:
	void InitRadioPredictShotButton(FrButton** button, int id, float x);
	void SetRadioPredictShotPress(FrButton* button);
	void UpdateRadioPredictShotButtonStatus();
	bool StandViewClick();
	bool TopViewClick();
	void ToggleGameUI();
	void _ImeReset();
	char* GetPangyaInstallDic();
	void ProcessObserver();
	void HoleComboGaugeSetting();
	void AddSomeInfo(WSendPacket& packet);
	void CollectBallStopData();
	void FlyBy(float delta);
	void HoleReplay();
	int HoleReplay2();
	void SwingReplay();
	void AutoReplay();
	void AllReplay();
	bool IsLastShotRelplay();
	void ReplayBoxOpen();
	void ReplayBoxClose();
	void ReplayDlgRun();
	void ReplayTapeCheckAndUse();
	bool OnReplayModeDlgResult(int result, FrForm* form);
	void OnRecordAviBtnUp();
	bool OnRecordAviResult(int result, FrForm* form);
	bool GetShotCntData();
	bool ShotDataLoad(const char* filename);
	int ShotDataSave(const char* filename, bool bAppend);
	void SaveErrorFile();
	void SaveGame(int part);
	void LoadGame(int part);
	void QuickSave(const char* filename);
	void QuickLoad(char* filename);

	DECLARE_FRESH_MSGMAP()

protected:
	unsigned long m_command;
	unsigned long m_spinCommand;
	unsigned long m_specialShot;
	WVector m_cameraPos;
	WVector m_cameraTarget;
	float m_processTime;
	float m_goStopTime;
	unsigned long m_debugCameraMode;
	WMatrix m_debugCameraMat;
	unsigned long m_reserved240[2];
	bool m_bDrivePose;
	bool m_bShotEnable;
	WVector m_target;
	WVector m_holeInPos;
	bool m_bShotResult;
	bool m_bSendFinishShot;
	bool m_bBallStopped;
	bool m_bTurnSetup;
	bool m_bCanSkip;
	float m_timer;
	WPolySoup::sArea* m_pCameraArea;
	bool m_bClubCameraEnd;
	float m_shotSync;
	std::stack<sBackUp> m_backUpList;
	sBackUp m_backUp;
	unsigned char m_nextPlayer;
	sShotData m_shotData;
	WVector m_wind;
	char m_flySound[32];
	std::vector<WVector> m_flyByPos;
	unsigned char m_turn;
	unsigned long m_gaugeTime;
	unsigned long m_gaugeStartTime;
	unsigned long m_gaugePauseTime;
	bool m_bGaugePause;
	bool m_bUnused3c9;
	bool m_bModal;
	bool m_bNetMsgWait;
	int m_netMsgWaitLine;
	char* m_netMsgSend;
	char* m_netMsgRecv;
	unsigned long m_netMsgSendTime;
	unsigned long m_netMsgRecvTime;
	float m_netMsgWaitTime;
	bool m_bReserved3e4;
	bool m_bAutoShot;
	float m_autoShotPos[2];
	bool m_bSpecialPuttPose;
	unsigned long m_reservedSpecial;
	unsigned char m_bgm;
	unsigned long m_commandTime;
	bool m_bReserved400;
	bool m_bShotBlock;
	float m_shotBlockTime;
	bool m_bRemoteClick;
	unsigned long m_observerTime;
	bool m_bChatTyping;
	FrForm* m_pPauseDlg;
	FrForm* m_pGoStopDlg;
	FrForm* m_pCancelDropDlg;
	FrForm* m_pPlayerInfoDlg;
	FrApproachResultDlg* m_pApproachDlg;
	FrApproachEndDlg* m_pApproachEndDlg;
	bool m_bTrajectoryFx;
	float m_debugCameraSpeed;
	float m_debugCameraRadius;
	WVector m_debugCameraCenter;
	bool m_bForgetDlg;
	float m_forgetDlgTime;
	int m_forgetItemSlot;
	bool m_bSkinsNextHole;
	float m_coinTime;
	int m_coinCount;
	int m_coinNum;
	std::vector<std::string> m_bgmList;
	FrComboBox* m_pChatTarget;
	FrEdit* m_pChatInput;
	FrButton* m_pEmoticonBtn;
	FrArea* m_pLanguage;
	FrButton* m_pReportBtn;
	FrEdit* m_pChatView;
	FrEmoticonDlg* m_pEmoticonDlg;
	FrForm* m_pReportDlg;
	FrForm* m_pForgetDlg;
	FrOnelineReqDlg* m_pOnelineReqDlg;
	FrReplayControlDlg* m_pReplayDlg;
	FrForm* m_pRecordAviDlg;
	FrArea* m_pReplayStatus;
	FrButton* m_pMyInfoBtn;
	FrButton* m_pOptionBtn;
	FrButton* m_pCaddieBookBtn;
	FrButton* m_pUnplayableBtn;
	FrButton* m_pPauseBtn;
	FrButton* m_pChatRecordBtn;
	FrArea* m_pOnelineView;
	FrButton* m_pOnelineBtn;
	bool m_bClosedBonusBall;
	sBonusBall m_closedBonusBall[5];
	int m_shotPvsFrame;
	int m_replayPvsFrame;
	int m_flyPvsFrame;
	FrButton* m_pPredictNormalBtn;
	FrButton* m_pPredictTomahawkBtn;
	FrButton* m_pPredictCobraBtn;
	FrButton* m_pPredictSpikeBtn;
	CSimpleUI* m_pPredictUI;
	int m_captureScale;
	int m_captureStep;
	int m_captureMode;
	bool m_bShowUI;
	char m_fileName[64];
	int m_recordPang;
	int m_recordBonusPang;
	float m_recordGauge;
	unsigned long m_shotFlag;
	int m_replayCamera;
	bool m_bDisconnect;
	bool m_bRainbow;
	bool m_bFlagCutin;
	CGolfRuleBase* m_pCurrentRule;
	bool m_bPlayerPreviewReady;
	bool m_bWaitForStart;
	int m_topViewMode;

public:
	sShotData* GetShotData() { return &m_shotData; }

	void SetFlagCutin(bool bFlag) { m_bFlagCutin = bFlag; }
	bool GetFlagCutin() { return m_bFlagCutin; }
};
