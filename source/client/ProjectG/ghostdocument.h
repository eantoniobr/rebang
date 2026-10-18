#pragma once
#include "ghostmanager.h"
#include "ghostdata.h"
#include <vector>
#include <list>

struct GHOST_GAME_DATA;
struct GHOST_SHOT_DATA;
class CGhostHoleData;

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
