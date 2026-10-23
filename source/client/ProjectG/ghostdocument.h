#pragma once
#include "ghostmanager.h"
#include "ghostdata.h"
#include <vector>
#include <list>

struct GHOST_GAME_DATA
{
	unsigned char holeIndex[18];
	unsigned long holeRandom[18];
	unsigned char course;
	unsigned char holeType;
	unsigned char gameType;
	unsigned long serverProperty;
};

struct GHOST_ACTION
{
	bool bActive;
	unsigned char valueType;
	int param[5];
};

struct GHOST_SHOT_DATA
{
	int bDummy;
	unsigned int holeIndex;
	unsigned int shotIndex;
	GHOST_ACTION action[9];
	GHOST_SHOT_PROTOCOL shotProtocol;
	float windPower;
	float windDirection;
	unsigned char windPowerTenth;
	struct
	{
		float x, y, z;
	} ballPosition;
	struct
	{
		float x, y, z;
	} globalWind;
	float cameraAngle;
};

class CGhostHoleData
{
public:
	CGhostHoleData();
	~CGhostHoleData();

	void RecordAct(int index, int valueType, const int* param, int paramNum);

	void SetHoleNum(unsigned char hole) { m_holeNum = hole; }
	const GHOST_SHOT_DATA* RecordShotData(const sShotProtocol* protocol,
		unsigned int shotIndex);
	void RecordDummyShot(unsigned int shotIndex);
	void AddShotData(const GHOST_SHOT_DATA* shot);
	const std::list<GHOST_SHOT_DATA*>& GetShotDataList() const
	{
		return m_shotDataList;
	}
	unsigned int RollBackShotData(unsigned int count);

private:
	unsigned char m_holeNum;
	std::list<GHOST_SHOT_DATA*> m_shotDataList;
	GHOST_SHOT_DATA* m_pRecordShot;
};

struct GHOST_CARD_DATA
{
	unsigned long typeId;
	unsigned long itemId;
	unsigned long partsTypeId;
	unsigned long partsItemId;
	int ability;
	int abilityValue;
	int slotNum;
	int cardType;
};

class CGhostDocument
{
	friend CGhostDocument* CreateDocument();

protected:
	CGhostDocument();

public:
	~CGhostDocument();

	void RecordGameData();
	void RecordUserData();
	void RecordHoleData(const MsgObject& msg);
	void RecordException(const char* exception);

	void Export(const std::string& fileName);
	bool Import(const std::string& fileName);
	bool Import(unsigned char* data, unsigned int size);
	bool WriteTextFile(const char* fileName) const;

	void SetInvalidate() { m_bInvalidate = 1; }
	int IsInvalidate() const { return m_bInvalidate; }

	const CGhostHoleData* GetHoleData(unsigned char hole) const;

	const GHOST_USER_DATA* GetUserData() const { return m_pUserData; }
	const GHOST_GAME_DATA* GetGameData() const { return m_pGameData; }

private:
	std::string MakeTextFileName() const;
	bool WriteTextFile(FILE* fp, const GHOST_SHOT_DATA* shot) const;
	bool WriteTextFile(FILE* fp, const CGhostHoleData* hole) const;
	bool WriteExceptionLogFile() const;

	GHOST_GAME_DATA* m_pGameData;
	GHOST_USER_DATA* m_pUserData;
	CGhostHoleData* m_pHoleData;
	std::vector<GHOST_CARD_DATA> m_cardList;
	std::list<std::string> m_exceptionList;
	unsigned int m_shotIndex;
	int m_bInvalidate;
};
