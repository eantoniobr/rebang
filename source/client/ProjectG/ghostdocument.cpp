#include "stdafx.h"
#include "ghostdocument.h"
#include "wind.h"
#include "golfball.h"
#include "club.h"
#include "../../shared/sharedtables.h"
#include "mathconsts.h"
#include "s5/utilities.h"
#include "type_convert.h"
#include <algorithm>
#include <iterator>
#include <io.h>

namespace GHOST
{
	enum eGHOSTACTMSG
	{
		CHANGE_WIND = 0,
		CHANGE_WEATHER = 1,
		CHANGE_DIRECTION = 2,
		CHANGE_CLUB = 4,
		USE_ITEM = 5,
		BALL_DROP = 7,
		TIME_OUT = 8,
		GAME_TIME_OVER = 11,
		SAVE_SHOT_DATA = 12
	};
}

namespace
{
	const char* GHOST_EXCEPTION_LOG_FILENAME = "ghost_exception_log.txt";
	template <class From, class To>

	void py_data_cast(From& from, To& to)
	{
		to = *reinterpret_cast<const To*>(&from);
	}

	struct card_converter
	{
		GHOST_CARD_DATA operator()(const sSCardAvilityPeriodInfo& info) const
		{
			GHOST_CARD_DATA result;
			memset(&result, 0, sizeof(result));
			type_convert(&info, &result);
			return result;
		}
	};

	const char* GetCardTypeString(int type)
	{
		if (type == 0)
			return "CARD_CHARACTER";
		if (type == 1)
			return "CARD_CADDIE";
		if (type == 2)
			return "CARD_SPECIAL";
		if (type == 3)
			return "CARD_PACK";
		if (type == 4)
			return "CARD_BOX";
		return "NOT DEFINED";
	}

	const char* GetCardAbilityString(int ability)
	{
		if (ability == -1)
			return "SPECIAL_AVILITY_NONE";
		if (ability == 0)
			return "SPECIAL_EXP_ADD";
		if (ability == 1)
			return "SPECIAL_PANG_RATE_UP_TIME";
		if (ability == 2)
			return "SPECIAL_EXP_REAE_UP_TIME";
		if (ability == 3)
			return "SPECIAL_PANG_ADD";
		if (ability == 4)
			return "SPECIAL_POWER_UP_TIME";
		if (ability == 5)
			return "SPECIAL_CONTROL_UP_TIME";
		if (ability == 6)
			return "SPECIAL_ACCCURACY_UP_TIME";
		if (ability == 7)
			return "SPECIAL_SPIN_UP_TIME";
		if (ability == 8)
			return "SPECIAL_CURVE_UP_TIME";
		if (ability == 9)
			return "SPECIAL_START_COMBOGAUGE_UP_TIME";
		if (ability == 10)
			return "SPECIAL_SLOT_UP_TIME";
		if (ability == 11)
			return "SPECIAL_PANGYAZONE_UP";
		if (ability == 12)
			return "SPECIAL_CLEARBONUS_UP_SEPIAWIND";
		if (ability == 13)
			return "SPECIAL_CLEARBONUS_UP_WINDHILL";
		if (ability == 14)
			return "SPECIAL_CLEARBONUS_UP_PINKWIND";
		if (ability == 15)
			return "SPECIAL_CLEARBONUS_UP_BLUEMOON";
		if (ability == 16)
			return "SPECIAL_RANDOMPANG_ADD";
		if (ability == 17)
			return "SPECIAL_TREASUREPOINT_UP";
		if (ability == 18)
			return "SPECIAL_RAINFALL_PROBABILITY_UP";
		return "NOT DEFINED";
	}

	const char* GetActionString(GHOST::eGHOSTACTMSG action)
	{
		if (action == 0)
			return "GHOST::CHANGE_WIND";
		if (action == 1)
			return "GHOST::CHANGE_WEATHER";
		if (action == 2)
			return "GHOST::CHANGE_DIRECTION";
		if (action == 4)
			return "GHOST::CHANGE_CLUB";
		if (action == 5)
			return "GHOST::USE_ITEM";
		if (action == 7)
			return "GHOST::BALL_DROP";
		if (action == 8)
			return "GHOST::TIME_OUT";
		if (action == 11)
			return "GHOST::GAME_TIME_OVER";
		if (action == 12)
			return "GHOST::SAVE_SHOT_DATA";
		return "NOT DEFINED";
	}

	struct print_ghost_card_data
	{
		print_ghost_card_data(FILE* fp)
			: m_fp(fp)
		{
		}
		void operator()(const GHOST_CARD_DATA& card) const
		{
			if (card.partsTypeId)
				fprintf(m_fp, "\tATTACHED : %d(%s), PARTS_ITEMID : %d\n",
					card.partsTypeId,
					ItemManager()->GetItemName(card.partsTypeId),
					card.partsItemId);
			fprintf(m_fp, "\tCARD TYPEID : %d(%s)\n", card.typeId,
				ItemManager()->GetItemName(card.typeId));
			fprintf(m_fp, "\tCARD ITEMID : %d\n", card.itemId);
			fprintf(m_fp, "\tCARD TYPE : %d(%s)\n", card.cardType,
				GetCardTypeString(card.cardType));
			fprintf(m_fp, "\tCARD ABILITY : %d(%s)\n", card.ability,
				GetCardAbilityString(card.ability));
			fprintf(m_fp, "\tABILITY VALUE : %d\n", card.abilityValue);
			fprintf(m_fp, "\tCARD SLOTNUM : %d\n", card.slotNum);
			fprintf(m_fp, "\n");
		}
		FILE* m_fp;
	};
}

CGhostHoleData::CGhostHoleData()
	: m_holeNum(0)
{
	m_pRecordShot = new GHOST_SHOT_DATA;
	memset(m_pRecordShot, 0, sizeof(GHOST_SHOT_DATA));
}

CGhostHoleData::~CGhostHoleData()
{
	std::for_each(m_shotDataList.begin(), m_shotDataList.end(),
		Delete_Object());
	m_shotDataList.clear();
	if (m_pRecordShot)
	{
		delete m_pRecordShot;
		m_pRecordShot = NULL;
	}
}

void CGhostHoleData::RecordAct(int index, int valueType, const int* param,
	int paramNum)
{
	GHOST_ACTION& action = m_pRecordShot->action[index];
	action.bActive = true;
	action.valueType = valueType;
	memset(action.param, -1, sizeof(action.param));
	if (paramNum && param)
	{
		memcpy(action.param, param, Between(1, paramNum, 5) * sizeof(int));
	}
}

void CGhostHoleData::RecordDummyShot(unsigned int index)
{
	m_pRecordShot->bDummy = 1;
	m_pRecordShot->shotIndex = index;
	m_pRecordShot->holeIndex = GOLFDOC()->m_currentHole;
	GHOST_SHOT_DATA* shot = new GHOST_SHOT_DATA;
	memcpy(shot, m_pRecordShot, sizeof(GHOST_SHOT_DATA));
	m_shotDataList.push_back(shot);
	memset(m_pRecordShot, 0, sizeof(GHOST_SHOT_DATA));
}

unsigned int CGhostHoleData::RollBackShotData(unsigned int count)
{
	unsigned int remain = count;
	memset(m_pRecordShot, 0, sizeof(GHOST_SHOT_DATA));
	for (std::list<GHOST_SHOT_DATA*>::reverse_iterator it =
			 m_shotDataList.rbegin();
		it != m_shotDataList.rend() && remain;)
	{
		--remain;
		delete *it;
		it = std::list<GHOST_SHOT_DATA*>::reverse_iterator(
			m_shotDataList.erase((++it).base()));
	}
	return count - remain;
}

const GHOST_SHOT_DATA* CGhostHoleData::RecordShotData(
	const sShotProtocol* protocol, unsigned int index)
{
	m_pRecordShot->bDummy = 0;
	m_pRecordShot->shotIndex = index;
	m_pRecordShot->holeIndex = GOLFDOC()->m_currentHole;
	type_convert(protocol, &m_pRecordShot->shotProtocol);
	if (GetCurMap() == 7)
	{
		int frame = Wind().GetSpWindStartFrame();
		RecordAct(3, 2, &frame, 1);
	}
	m_pRecordShot->windDirection = Wind().GetGlobalDirection();
	m_pRecordShot->windPower = Wind().GetGlobalIntensity();
	m_pRecordShot->globalWind.x = Wind().GetGlobalWind().x;
	m_pRecordShot->globalWind.y = Wind().GetGlobalWind().y;
	m_pRecordShot->globalWind.z = Wind().GetGlobalWind().z;
	m_pRecordShot->ballPosition.x = GolfBall().m_pos.x;
	m_pRecordShot->ballPosition.y = GolfBall().m_pos.y;
	m_pRecordShot->ballPosition.z = GolfBall().m_pos.z;
	int power = Wind().GetGlobalIntensity();
	m_pRecordShot->windPowerTenth =
		(Wind().GetGlobalIntensity() - power) * 10.f;
	m_pRecordShot->cameraAngle = GOLFDOC()->m_cameraData.angle;
	GHOST_SHOT_DATA* shot = new GHOST_SHOT_DATA;
	memcpy(shot, m_pRecordShot, sizeof(GHOST_SHOT_DATA));
	m_shotDataList.push_back(shot);
	memset(m_pRecordShot, 0, sizeof(GHOST_SHOT_DATA));
	return shot;
}

void CGhostHoleData::AddShotData(const GHOST_SHOT_DATA* data)
{
	GHOST_SHOT_DATA* shot = new GHOST_SHOT_DATA;
	memcpy(shot, data, sizeof(GHOST_SHOT_DATA));
	m_shotDataList.push_back(shot);
}

CGhostDocument::CGhostDocument()
	: m_shotIndex(0), m_bInvalidate(0)
{
	m_pUserData = new GHOST_USER_DATA;
	memset(m_pUserData, 0, sizeof(GHOST_USER_DATA));
	m_pGameData = new GHOST_GAME_DATA;
	memset(m_pGameData, 0, sizeof(GHOST_GAME_DATA));
	m_pHoleData = new CGhostHoleData[18];
	for (int i = 0; i < 18; ++i)
		m_pHoleData[i].SetHoleNum(i + 1);
}

CGhostDocument::~CGhostDocument()
{
	if (m_pUserData)
	{
		delete m_pUserData;
		m_pUserData = NULL;
	}
	if (m_pGameData)
	{
		delete m_pGameData;
		m_pGameData = NULL;
	}
	if (m_pHoleData)
	{
		delete[] m_pHoleData;
		m_pHoleData = NULL;
	}
}

void CGhostDocument::RecordGameData()
{
	m_pGameData->course = GetCurMap();
	m_pGameData->gameType = Doc()->m_golfGame.gameType;
	m_pGameData->holeType = GetHoleType();
	m_pGameData->serverProperty = S5::UTIL::GetServerProperty();
	for (int i = 0; i < 18; ++i)
	{
		m_pGameData->holeRandom[i] = Doc()->m_holeRandom[i];
		m_pGameData->holeIndex[i] = Doc()->m_holeOrder[i];
	}
}

void CGhostDocument::RecordUserData()
{
	const sUserInfo& user = Doc()->m_userInfo[MyIndex()];
	memset(m_pUserData, 0, sizeof(GHOST_USER_DATA));
	type_convert(&user, m_pUserData);
	const std::list<sSCardAvilityPeriodInfo>& source =
		Doc()->m_cardAbilityList[MyIndex()];
	std::list<sSCardAvilityPeriodInfo> cards;
	std::copy(source.begin(), source.end(), std::back_inserter(cards));
	for (std::list<sSCardAvilityPeriodInfo>::iterator it = cards.begin();
		it != cards.end();)
	{
		if ((*it).cardType == 0 || (*it).cardType == 1)
		{
			bool found = false;
			for (int i = 0; i < 24; ++i)
			{
				if ((*it).partsTid == user.charInfo.tidParts[i] &&
					(*it).partsUid == user.charInfo.ItemIdList[i])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				it = cards.erase(it);
				continue;
			}
		}
		++it;
	}
	if (!cards.empty())
	{
		m_cardList.reserve(cards.size());
		card_converter convert;
		std::transform(cards.begin(), cards.end(),
			std::back_inserter(m_cardList), convert);
	}
}

void CGhostDocument::RecordHoleData(const MsgObject& msg)
{
	CGhostHoleData& hole = m_pHoleData[GOLFDOC()->m_currentHole - 1];
	switch (msg.message)
	{
	case 1:
		hole.RecordAct(1, 0, &msg.param1, 1);
		break;
	case 0:
		hole.RecordAct(0, 0, &msg.param1, 4);
		break;
	case 2:
		hole.RecordAct(2, 1, &msg.param1, 1);
		break;
	case 7:
	{
		WVector* pos = (WVector*)msg.param1;
		int param[3];
		py_data_cast(pos->x, param[0]);
		py_data_cast(pos->y, param[1]);
		py_data_cast(pos->z, param[2]);
		hole.RecordAct(7, 1, param, 3);
		hole.RecordDummyShot(++m_shotIndex);
	}
	break;
	case 5:
		hole.RecordAct(5, 2, &msg.param1, 2);
		if (msg.param1 == 0x1800000e)
		{
			hole.RollBackShotData(1);
			--m_shotIndex;
		}
		break;
	case 6:
		hole.RecordAct(6, 0, &msg.param1, 1);
		break;
	case 12:
	{
		const sShotProtocol* protocol = (const sShotProtocol*)msg.param1;
		hole.RecordShotData(protocol, ++m_shotIndex);
	}
	break;
	case 8:
		hole.RecordAct(8, 0, NULL, 0);
		hole.RecordDummyShot(++m_shotIndex);
		break;
	}
}

void CGhostDocument::RecordException(const char* exception)
{
	if (exception)
		m_exceptionList.push_back(std::string(exception));
}

bool CGhostDocument::WriteTextFile(const char* filename) const
{
	if (!strlen(m_pUserData->nickname))
		return false;
	FILE* fp = NULL;
	if (!filename)
		fp = fopen(MakeTextFileName().c_str(), "wt");
	else
		fp = fopen(filename, "wt");
	if (!fp)
		return false;
	SYSTEMTIME time;
	GetLocalTime(&time);
	fprintf(fp,
		"=================================================================================\n");
	fprintf(fp, "SAVE DATE      : %04d-%02d-%02d %02d:%02d:%02d\n", time.wYear,
		time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	fprintf(fp, "DATA VERSION   : %d\n", 1001);
	fprintf(fp, "HEADER SIZE    : %d\n", sizeof(GHOST_DATA_HEADER));
	fprintf(fp,
		"DATA SIZE      : GHOST_GAME_DATA(%d), GHOST_USER_DATA(%d), GHOST_SHOT_DATA(%d)\n",
		sizeof(GHOST_GAME_DATA), sizeof(GHOST_USER_DATA),
		sizeof(GHOST_SHOT_DATA));
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	fprintf(fp, "USER NICK      : %s\n", m_pUserData->nickname);
	fprintf(fp, "USER ID        : %s\n", m_pUserData->id);
	fprintf(fp, "GUILD          : %s\n",
		strlen(m_pUserData->guildName) ? m_pUserData->guildName : "-");
	fprintf(fp, "EMBLEM         : %s\n",
		strlen(m_pUserData->guildMark) ? m_pUserData->guildMark : "-");
	fprintf(fp, "IDENTITY       : %d\n", m_pUserData->capability);
	fprintf(fp, "GENDER         : %s\n",
		m_pUserData->female ? "FEMALE" : "MALE");
	fprintf(fp, "ANGEL WING     : %d\n", m_pUserData->angelWing);
	fprintf(fp, "ANGEL EFFECT   : %d\n", m_pUserData->angelEffect);
	fprintf(fp, "DEVIL WING     : %d\n", m_pUserData->devilWing);
	fprintf(fp, "LEVEL          : %d(%s)\n", m_pUserData->level,
		g_LevelTable[Between(0, (int)m_pUserData->level, 70)].name);
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	fprintf(fp, "CHAR TYPEID    : %d(%s)\n", m_pUserData->charTypeId,
		ItemManager()->GetItemName(m_pUserData->charTypeId));
	fprintf(fp, "HAIR COLOR     : %d\n", m_pUserData->hairColor);
	fprintf(fp, "SHIRTS COLOR   : %d\n", m_pUserData->shirtsColor);
	for (int i = 0; i < 24; ++i)
		if (m_pUserData->partTypeId[i])
		{
			fprintf(fp, "PARTS(%02d)      : %d(%s)\n", i,
				m_pUserData->partTypeId[i],
				ItemManager()->GetItemName(m_pUserData->partTypeId[i]));
		}
	for (int i = 0; i < 5; ++i)
		if (m_pUserData->auxPartTypeId[i])
		{
			fprintf(fp, "AUXPARTS(%02d)   : %d(%s)\n", i,
				m_pUserData->auxPartTypeId[i],
				ItemManager()->GetItemName(m_pUserData->auxPartTypeId[i]));
		}
	fprintf(fp, "CHAR PCL       : ");
	for (int i = 0; i < 5; ++i)
		fprintf(fp, "%d ", m_pUserData->charPcl[i]);
	fprintf(fp, "\n");
	fprintf(fp, "CLUB TYPEID    : %d(%s)\n", m_pUserData->clubTypeId,
		ItemManager()->GetItemName(m_pUserData->clubTypeId));
	fprintf(fp, "CLUB PCL       : ");
	for (int i = 0; i < 5; ++i)
		fprintf(fp, "%d ", m_pUserData->clubPcl[i]);
	fprintf(fp, "\n");
	fprintf(fp, "BALL TYPEID    : %d(%s)\n", m_pUserData->ballTypeId,
		ItemManager()->GetItemName(m_pUserData->ballTypeId));
	fprintf(fp, "CADDIE TYPEID  : %d(%s)\n", m_pUserData->caddieTypeId,
		m_pUserData->caddieTypeId
			? ItemManager()->GetItemName(m_pUserData->caddieTypeId)
			: "NULL");
	fprintf(fp, "CADDIE PARTS   : %d(%s)\n", m_pUserData->caddiePartsTypeId,
		m_pUserData->caddiePartsTypeId
			? ItemManager()->GetItemName(m_pUserData->caddiePartsTypeId)
			: "NULL");
	fprintf(fp, "CADDIE LEVEL   : %d\n", m_pUserData->caddieLevel);
	fprintf(fp, "MASCOT TYPEID  : %d(%s)\n", m_pUserData->mascotTypeId,
		m_pUserData->mascotTypeId
			? ItemManager()->GetItemName(m_pUserData->mascotTypeId)
			: "NULL");
	fprintf(fp, "MASCOT MSG     : %s\n",
		strlen(m_pUserData->mascotMsg) ? m_pUserData->mascotMsg : "-");
	for (int i = 0; i < 10; ++i)
		if (m_pUserData->itemSlot[i])
		{
			fprintf(fp, "ITEMSLOT(%02d)   : %d(%s)\n", i,
				m_pUserData->itemSlot[i],
				ItemManager()->GetItemName(m_pUserData->itemSlot[i]));
		}
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	fprintf(fp, "CARD SIZE      : %d\n", m_cardList.size());
	std::for_each(m_cardList.begin(), m_cardList.end(),
		print_ghost_card_data(fp));
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	unsigned char course = m_pGameData->course;
	int realCourse = course > 0x7f && course != 0xfd ? course - 0x80 : course;
	fprintf(fp, "COURSE         : %s\n",
		ItemManager()->GetItemName(realCourse | 0x28000000));
	const char* gameType;
	switch (m_pGameData->gameType)
	{
	case 4:
	case 5:
	case 6:
	case 9:
	case 10:
	case 14:
		gameType = "30S_BATTLE";
		break;
	default:
		gameType = "STROKE";
		break;
	}
	fprintf(fp, "GAME TYPE      : %d(%s)\n", m_pGameData->gameType, gameType);
	fprintf(fp, "HOLE TYPE      : %d\n", m_pGameData->holeType);
	fprintf(fp, "HOLE INDEX     : ");
	for (int i = 0; i < 18; ++i)
		fprintf(fp, "%d ", m_pGameData->holeIndex[i]);
	fprintf(fp, "\n");
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	if (fp)
	{
		for (int i = 0; i < 18; ++i)
			WriteTextFile(fp, &m_pHoleData[i]);
		fclose(fp);
	}
	return true;
}

bool CGhostDocument::WriteTextFile(FILE* fp, const CGhostHoleData* hole) const
{
	const std::list<GHOST_SHOT_DATA*>& shots = hole->GetShotDataList();
	for (std::list<GHOST_SHOT_DATA*>::const_iterator it = shots.begin();
		it != shots.end(); ++it)
		WriteTextFile(fp, *it);
	return true;
}

bool CGhostDocument::WriteTextFile(FILE* fp, const GHOST_SHOT_DATA* shot) const
{
	fprintf(fp, "HOLE INDEX     : %d\n", shot->holeIndex);
	fprintf(fp, "SHOT INDEX     : %d\n", shot->shotIndex);
	fprintf(fp, "DUMMY SHOT     : %s\n", shot->bDummy ? "TRUE" : "FALSE");
	fprintf(fp, "MAX CLICK      : %.02f\n", shot->shotProtocol.maxClick);
	fprintf(fp, "MIN CLICK      : %.02f\n", shot->shotProtocol.minClick);
	fprintf(fp, "CURVE, SPIN    : %.02f, %.02f\n", shot->shotProtocol.curve,
		shot->shotProtocol.spin);
	fprintf(fp, "ACCURACY       : %d\n", shot->shotProtocol.accuracy);
	fprintf(fp, "SPECIAL        : %d\n", shot->shotProtocol.special);
	fprintf(fp, "FRAME          : %d\n", shot->shotProtocol.frame);
	fprintf(fp, "SHOT ANGLE     : %.02f\n", shot->shotProtocol.shotAngle);
	fprintf(fp, "SHOT TIME      : %d\n", shot->shotProtocol.shotTime);
	fprintf(fp, "CENTER         : %.02f\n", shot->shotProtocol.center);
	fprintf(fp, "CLUB INDEX     : %d(%s)\n", shot->shotProtocol.clubIndex,
		GolfClub().GetClubString((CClub::eClub)shot->shotProtocol.clubIndex));
	fprintf(fp, "RANDOM POWER   : %.02f\n", shot->shotProtocol.randomPower);
	fprintf(fp, "RANDOM ANGLE   : %.02f\n", shot->shotProtocol.randomAngle);
	fprintf(fp, "CAMERA ANGLE   : %.02f\n", shot->cameraAngle);
	fprintf(fp, "\n");
	for (int i = 0; i < 9; ++i)
	{
		const GHOST_ACTION& action = shot->action[i];
		if (action.bActive)
		{
			fprintf(fp, "\tACTION : [%s] ",
				GetActionString((GHOST::eGHOSTACTMSG)i));
			for (int j = 0; j < 5; ++j)
			{
				if (action.param[j] != -1)
				{
					if (action.valueType == 1)
					{
						float value;
						py_data_cast(action.param[j], value);
						fprintf(fp, "%.02f ", value);
					}
					else
						fprintf(fp, "%d ", action.param[j]);
				}
			}
			fprintf(fp, "\n");
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "\t\tBALL POSITION : %.02f, %.02f, %.02f\n",
		shot->ballPosition.x, shot->ballPosition.y, shot->ballPosition.z);
	fprintf(fp, "\t\tWIND DIR : %.02f\n", shot->windDirection);
	fprintf(fp, "\t\tWIND PWR : %.02f\n", shot->windPower);
	fprintf(fp, "\t\tGLOBAL WIND : %.02f, %.02f, %.02f\n", shot->globalWind.x,
		shot->globalWind.y, shot->globalWind.z);
	fprintf(fp,
		"---------------------------------------------------------------------------------\n");
	return true;
}

std::string CGhostDocument::MakeTextFileName() const
{
	char filename[MAX_PATH] = { 0 };
	sprintf(filename, "ghost_save_data(%s).txt", Doc()->m_myInfo.info.sNick);
	return filename;
}

const CGhostHoleData* CGhostDocument::GetHoleData(unsigned char hole) const
{
	const CGhostHoleData* result = NULL;
	if (m_pHoleData)
		result = &m_pHoleData[hole - 1];
	return result;
}

class memory_buffer
{
public:
	memory_buffer(unsigned int size)
		: m_buffer(NULL), m_length(0), m_position(0)
	{
		reserve(size);
	}
	memory_buffer(char* data, unsigned int size)
		: m_buffer(NULL), m_length(0), m_position(0)
	{
		reserve(size);
		encode(data, size);
	}
	~memory_buffer()
	{
		if (m_buffer)
			free(m_buffer);
	}
	unsigned int reserve(unsigned int size)
	{
		m_capacity = size;
		if (!m_buffer)
			m_buffer = (char*)calloc(size, 1);
		else
			m_buffer = (char*)realloc(m_buffer, size);
		return m_capacity;
	}
	void encode(const void* data, unsigned int size)
	{
		if (m_length + size > m_capacity)
		{
			m_capacity = 1;
			while (m_capacity < m_length + size)
				m_capacity <<= 1;
			reserve(m_capacity);
		}
		memcpy(m_buffer + m_length, data, size);
		m_length += size;
	}
	void decode(void* data, unsigned int size)
	{
		memcpy(data, m_buffer + m_position, size);
		m_position += size;
	}
	const void* get_buffer() const { return m_buffer; }
	unsigned int length() const { return m_length; }

private:
	char* m_buffer;
	unsigned int m_length, m_position, m_capacity;
};
void CGhostDocument::Export(const std::string& filename)
{
	GHOST_DATA_HEADER header;
	memset(&header, 0, sizeof(header));
	header.version = 1001;
	header.userDataSize = sizeof(GHOST_USER_DATA);
	header.gameDataSize = sizeof(GHOST_GAME_DATA);
	header.shotDataSize = sizeof(GHOST_SHOT_DATA);
	header.cardDataSize = sizeof(GHOST_CARD_DATA);
	header.cardCount = m_cardList.size();
	for (int i = 0; i < 18; ++i)
	{
		const std::list<GHOST_SHOT_DATA*>& shots =
			m_pHoleData[i].GetShotDataList();
		header.shotCount += shots.size();
	}
	unsigned int length = header.GetDataBodySize() + sizeof(header);
	calloc(length, 1);
	memory_buffer buffer(length);
	unsigned int version = 1001;
	buffer.encode(&version, sizeof(version));
	unsigned int headerSize = sizeof(header);
	buffer.encode(&headerSize, sizeof(headerSize));
	buffer.encode(&header, headerSize);
	buffer.encode(m_pUserData, sizeof(GHOST_USER_DATA));
	buffer.encode(m_pGameData, sizeof(GHOST_GAME_DATA));
	for (int i = 0; i < 18; ++i)
	{
		const std::list<GHOST_SHOT_DATA*>& shots =
			m_pHoleData[i].GetShotDataList();
		unsigned int size = shots.size();
		buffer.encode(&size, sizeof(size));
		for (std::list<GHOST_SHOT_DATA*>::const_iterator it = shots.begin();
			it != shots.end(); ++it)
			buffer.encode(*it, sizeof(GHOST_SHOT_DATA));
	}
	unsigned int cardCount = m_cardList.size();
	buffer.encode(&cardCount, sizeof(cardCount));
	if (cardCount)
		buffer.encode(&m_cardList[0],
			m_cardList.size() * sizeof(GHOST_CARD_DATA));
	HZIP zip = CreateZipZ((void*)filename.c_str(), 0, ZIP_FILENAME, 0);
	CreateDirectoryA(".\\temporary_save\\", NULL);
	ZipAdd(zip, "ghost_document_data", (void*)buffer.get_buffer(),
		buffer.length(), ZIP_MEMORY);
	if (!m_exceptionList.empty())
		WriteExceptionLogFile();
	std::string exceptionFile = ".\\temporary_save\\";
	exceptionFile += GHOST_EXCEPTION_LOG_FILENAME;
	if (_access(exceptionFile.c_str(), 0) != -1)
		ZipAdd(zip, GHOST_EXCEPTION_LOG_FILENAME, (void*)exceptionFile.c_str(),
			0, ZIP_FILENAME);
	if (IsZipHandleU(zip))
		CloseZipU(zip);
	else
		CloseZipZ(zip);
	DeleteFileA(exceptionFile.c_str());
	RemoveDirectoryA(".\\temporary_save\\");
}

bool CGhostDocument::Import(const std::string& filename)
{
	cFile* file = GetCFile(filename.c_str(), -1, 0);
	if (!file)
		return false;
	unsigned int length = file->Length();
	unsigned char* data = new unsigned char[length];
	file->Read(data, length);
	CloseCFile(file);
	bool result = Import(data, length);
	delete[] data;
	return result;
}

bool CGhostDocument::Import(unsigned char* data, unsigned int size)
{
	if (!data || !size)
		return false;
	int index = 0;
	ZIPENTRY entry;
	HZIP zip = OpenZipU(data, size, ZIP_MEMORY);
	if (FindZipItemA(zip, "ghost_document_data", true, &index, &entry))
	{
		if (IsZipHandleU(zip))
			CloseZipU(zip);
		else
			CloseZipZ(zip);
		return false;
	}
	char* extracted = new char[entry.unc_size];
	UnzipItem(zip, index, extracted, entry.unc_size, ZIP_MEMORY);
	if (IsZipHandleU(zip))
		CloseZipU(zip);
	else
		CloseZipZ(zip);
	memory_buffer buffer(extracted, entry.unc_size);
	delete[] extracted;
	unsigned int version;
	buffer.decode(&version, sizeof(version));
	if (version != 1001)
		return false;
	unsigned int headerSize;
	buffer.decode(&headerSize, sizeof(headerSize));
	GHOST_DATA_HEADER header;
	memset(&header, 0, sizeof(header));
	buffer.decode(&header, headerSize);
	buffer.decode(m_pUserData, header.userDataSize);
	buffer.decode(m_pGameData, header.gameDataSize);
	for (int i = 0; i < 18; ++i)
	{
		unsigned int count;
		buffer.decode(&count, sizeof(count));
		for (unsigned int j = 0; j < count; ++j)
		{
			GHOST_SHOT_DATA shot;
			memset(&shot, 0, sizeof(shot));
			buffer.decode(&shot, header.shotDataSize);
			m_pHoleData[i].AddShotData(&shot);
		}
	}
	unsigned int cardCount;
	buffer.decode(&cardCount, sizeof(cardCount));
	if (cardCount)
		m_cardList.reserve(cardCount);
	for (unsigned int i = 0; i < cardCount; ++i)
	{
		GHOST_CARD_DATA card;
		memset(&card, 0, sizeof(card));
		buffer.decode(&card, header.cardDataSize);
		m_cardList.push_back(card);
	}
	return true;
}

bool CGhostDocument::WriteExceptionLogFile() const
{
	return true;
}
