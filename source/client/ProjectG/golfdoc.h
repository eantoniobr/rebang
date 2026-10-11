#pragma once

#include <bitset>
#include "encrypttypes.h"
#include "parttidlist.h"
#include <map>

class WPolySoup;
struct sApproachResultData;
class CSky;
class CAutoTarget;

enum eTeamName
{
};

enum eApproachMissionType
{
};

#pragma pack(push, 1)
struct sWinningPrize
{
	unsigned long holeInOne;
	unsigned long albatross;
	unsigned long eagle;
	unsigned long birdie;
	unsigned long par;
	unsigned long bogey;
};

struct sPrizeInfo
{
	unsigned long typeId;
	unsigned char unknown[2];
	unsigned short quantity;
	int type;
};

struct sShotResult
{
	unsigned long oid;
	float pos[3];
	unsigned char result;
	unsigned char bunker;
	unsigned char ruleFlag;
	unsigned long pang;
	unsigned long bonusPang;
	unsigned long shotFlag;
	unsigned long actionFlag;
	unsigned short traceNum;
};
#pragma pack(pop)

struct sPlayerData
{
	int state;
	unsigned char index;
	WVector startPos;
	WVector pos;
	WCrypticValue<unsigned char> stroke[18];
	WCrypticValue<unsigned char> putt[18];
	WCrypticValue<int> pang[18];
	WCrypticValue<int> skinsPang[18];
	unsigned long color;
	unsigned long uid;
	unsigned long oid;
	unsigned char itemNum;
	unsigned long item;
	unsigned char teeOrder;
	WCrypticValue<float> gauge;
	unsigned short unusedWord;
	unsigned char bunker;
	unsigned char timeout;
	unsigned char giveUp;
	unsigned long shotFlag;
	WFlags event;
	unsigned char flag;
	unsigned char team;
	unsigned char teammate;
	unsigned long shotTime;
	unsigned char order : 4;
	unsigned char rank : 4;
	unsigned char totalStroke;
	int score;
	WCrypticValue<int> totalPang;
	WCrypticValue<int> bonusPang;
	unsigned long holeNum;
	WCrypticValue<int> power;
	WCrypticValue<int> accuracy;
	WCrypticValue<int> control;
	WCrypticValue<int> spin;
	WCrypticValue<int> curve;
	unsigned char chatBlock;
	sWinningPrize prize;
	unsigned char extPrizeNum;
	sPrizeInfo extPrize[128];
	unsigned char holeInPose;
	unsigned char holeInCollision;
	__int64 skinsTotalPang;
	__int64 skinsSumPang;
	__int64 skinsHolePang;
	unsigned char level;
};

struct sTeamData
{
	int state;
	WCrypticValue<unsigned char> stroke[18];
	WCrypticValue<unsigned char> putt[18];
	WCrypticValue<int> pang[18];
	unsigned char totalStroke;
	int score;
	WCrypticValue<int> totalPang;
	WCrypticValue<int> bonusPang;
	WVector pos;
	unsigned long color;
	WCrypticValue<float> gauge;
	unsigned char bunker;
	unsigned char shooter;
	unsigned char club;
	unsigned char turn;
	unsigned char teeShooter;
	unsigned char holeInPose;
	unsigned char holeInCollision;
};

struct sProperty
{
	float bound;
	float roll;
	float min[3];
	float max[3];
	unsigned char pass;
	unsigned char ground;

	sProperty()
	{
		boundSound[0] = 0;
		rollSound[0] = 0;
	}
	~sProperty() { }

	char boundSound[64];
	char rollSound[64];
	char stepSound[64];
};

class CPropertyInfo
{
public:
	CPropertyInfo() { m_defaultIndex = -1; }
	~CPropertyInfo();

	void Init(const TiXmlDocument& doc);
	int GetPropertyIndex(const char* texture);
	const sProperty& GetProperty(int index);

private:
	std::vector<sProperty> m_property;
	std::map<std::string, int> m_textureIndex;
	int m_defaultIndex;
};

struct sWave
{
	char texture[32];
	float width;
	float freq;
};

class CWaveInfo
{
public:
	void Load(const char* filename);

	char* GetTexture(int index) { return m_wave[index].texture; }
	float GetWidth(int index) { return m_wave[index].width; }
	float GetFreq(int index) { return m_wave[index].freq; }

private:
	std::map<int, sWave> m_wave;
};

struct sRiver
{
	float scrollVel;
	float tileHead;
	float tileSide;
	float depth;
};

class CRiverInfo
{
public:
	void Load(const char* filename);

private:
	std::map<int, sRiver> m_river;
};

const float BAR_GAUGE_START = 105.0f;
const float BAR_END = 500.0f;
const float BAR_START = 140.0f;
static float BAR_LENGTH = BAR_END - BAR_START;
static float BAR_CENTER = (BAR_START + BAR_END) / 2;

struct sBar
{
	float power;
	float impact;
	float gauge;
	float gaugeStep;
	int grade;
	bool bFullPower;
	int dir;
	float center;
	float calipers;

	void Reset();
	float Persent() const { return (power - BAR_START) / BAR_LENGTH; }
	float Delta() const { return impact - center; }
};

struct sHoleData
{
	WVector tee;
	WVector pin;
	unsigned char par;
	unsigned char playerNum;
	unsigned char rank[4];
	unsigned char result;
	unsigned char carry;
	__int64 pang;
	__int64 basePang;
	unsigned long checkSum;
	unsigned long reserved;
};

struct sCameraData
{
	float distance;
	float height;
	float clearance;
	WVector target;
	float angle;
	float angleOffset;
	WMatrix mat;
	float pitch;
};

class CGolfDoc
{
public:
	CGolfDoc();
	virtual ~CGolfDoc();

	sPlayerData* GetPlayer(unsigned char index);
	sTeamData* GetTeam(unsigned char index);
	void MakePlayer(unsigned char num);
	void MakeTeam();
	void MakeHoleData();
	void ResetTeamVars();
	void RefreshPlayerNum();
	unsigned char GetCurrentPlayerNum();
	void InitShotResultMsg();
	void ClearShotResultMsg();
	void SetPlayerLevel(unsigned char index);
	CPartTidList& GetPartTidList(unsigned char index);
	void SetPartTidList(unsigned char index, unsigned long charTid,
		unsigned char hairColor, unsigned char shirtColor,
		unsigned long* partTid, unsigned long* partId);
	void ApproachDataAllClear();
	std::list<sApproachResultData*>& GetApproachCurHoleResult();
	std::list<sApproachResultData*>& GetApproachGameResult();
	void LoadXml(const char* filename, unsigned char hole, bool bReload);
	eApproachMissionType GetApproachMissionType() const;
	WMatrix GetDefaultCamera();
	void MakeDefaultCamera(bool bApply);
	WMatrix MakeTopViewCameraMatrix(bool bKeep);

	unsigned char GetCurrentPlayer() { return m_currentPlayer; }
	unsigned char GetPlayerNum() { return m_playerNum; }
	sHoleData& GetHoleData() { return m_pHoleData[m_currentHole - 1]; }
	sHoleData& GetHoleData(unsigned char hole) { return m_pHoleData[hole - 1]; }
	unsigned char& GetUIAlpha() { return m_uiAlpha; }
	sBar& GetBar() { return m_bar; }

	unsigned long& GameMode() { return m_gameMode; }

	void NetGameEnd() { m_bNetGameEnd = true; }
	bool IsNetGameEnd() { return m_bNetGameEnd; }
	void SetTeeShotReady(bool bReady) { m_bTeeShotReady = bReady; }
	bool IsTeeShotReady() { return m_bTeeShotReady; }

	void SetPause(bool bPause) { m_bPause = bPause; }
	bool IsPause() { return m_bPause; }

	void SetDay(bool bDay) { m_bDay = bDay; }
	void SetTeamGameWinner(eTeamName team) { m_teamGameWinner = team; }
	void SetReport(bool bReport) { m_bReported = bReport; }

	void ShowChat(bool bShow) { m_bShowChat = bShow; }
	bool IsShowChat() { return m_bShowChat; }

	void SetStatUpdated(bool bUpdated) { m_bStatUpdated = bUpdated; }
	bool GetStatUpdated() const { return m_bStatUpdated; }

	bool GetApproachReloaded() { return m_bApproachReloaded; }
	void SetApproachReloaded(bool bReloaded)
	{
		m_bApproachReloaded = bReloaded;
	}

	struct sTarget
	{
		WPuppet* pet;
		WVector pos;
		bool bShow;
	};

#pragma pack(push, 1)
	struct sGameResult
	{
		unsigned long oid;
		unsigned char rank;
		char score;
		unsigned char totalStroke;
		short exp;
		__int64 pang;
		__int64 bonusPang;
		__int64 skinsPang;
	};

	struct sGaugeInfo
	{
		unsigned char phase;
		float pos;
	};
#pragma pack(pop)

	// TODO: incomplete
	WPolySoup* m_pPolySoup;
	CSky* m_pSky;
	CAutoTarget* m_pAutoTarget;
	CPropertyInfo m_propertyInfo;
	unsigned char m_unused34[0xc];
	CWaveInfo m_waveInfo;
	CRiverInfo m_riverInfo;
	WList<char*> m_modelNameList;
	int m_tutorialMode;
	std::list<unsigned long> m_commandList;
	sTarget m_target;
	unsigned char m_unused9c[0x24];
	eTeamName m_teamGameWinner;
	unsigned char m_currentPlayerNum;
	unsigned char m_playerNum;
	unsigned char m_unusedc6[2];
	sHoleData* m_pHoleData;
	unsigned char m_uiAlpha;
	sBar m_bar;
	sCameraData m_cameraData;
	unsigned long m_gameMode;
	bool m_bNetGameEnd;
	bool m_bPause;
	bool m_bTeeShotReady;
	bool m_bReported;
	bool m_bDay;
	bool m_bShowChat;
	unsigned char m_unused152[2];
	int m_saveChatNum;
	bool m_bReplay;
	bool m_bShowDropPos;
	bool m_bLockGauge;
	unsigned char m_unused15b[0xd];
	unsigned char m_currentHole;
	unsigned char m_unused169[3];
	unsigned long m_remainTime;
	unsigned long m_shotTime;
	unsigned char m_shotPhase;
	unsigned char m_currentPlayer;
	unsigned char m_unused176[2];
	float m_bright;
	bool m_bDropRequest;
	bool m_bStopRequest;
	unsigned char m_maxGrade;
	bool m_bStopDlg;
	bool m_bNoStat;
	float m_timeScale;
	float m_maxTimeScale;
	unsigned long m_skinsWinner;
	unsigned long m_skinsDonator;
	unsigned short m_skinsState;
	__int64 m_skinsHolePang;
	__int64 m_skinsCarryPang;
	unsigned long m_skinsMultiple;
	unsigned char m_skinsCarryNum;
	__int64 m_skinsCoursePang;
	__int64 m_skinsForfeitPang;
	unsigned char m_unused1c0[0x168];
	sGameResult m_gameResult[4];
	sShotResult m_shotResult[4];
	sShotProtocol m_shotInfo;
	sGaugeInfo m_gaugeInfo;
	unsigned char m_unused473[0x321];
	bool m_bStatUpdated;
	bool m_bApproachReloaded;
};
