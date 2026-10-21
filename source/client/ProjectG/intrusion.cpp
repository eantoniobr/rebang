#include "stdafx.h"
#include "intrusion.h"
#include "optiondlg.h"
#include "messengerdlg.h"
#include "mousecursor.h"
#include "bongdarishopdlg.h"
#include "user_info.h"
#include "cardsystem.h"
#include "contentsdoc.h"
#include "chatmsg.h"

extern Fresh* g_pFresh;

#pragma pack(push, 1)
struct sIntrusionScore
{
	unsigned char stroke[18];
	int score[18];
	__int64 pang[18];
};

struct sIntrusionReport
{
	sIntrusionScore score;
	unsigned long source;
	unsigned long target;
};
#pragma pack(pop)

struct sFindRival
{
	unsigned long oid;
	sFindRival(unsigned long value)
		: oid(value)
	{
	}
	bool operator()(sRivalData& rival) { return rival.oid == oid; }
};

unsigned char CIntrusion::GetCalcExpMemberSize()
{
	return m_calcExpMemberSize;
}

void CIntrusion::FinishGame()
{
	m_calcExpMemberSize = 0;
}

unsigned long CIntrusion::GetActiveColor()
{
	return 0xc3e5ffd8;
}

bool CIntrusion::OnAccessRoom(sRoomInfo& room)
{
	if (room.bIntrusion != true || room.bAvailable)
		return false;
	room.bAvailable = true;
	return true;
}

void CIntrusion::GetInfoTime(sInfoTime* info, unsigned long passTime,
	unsigned long remainTime)
{
	int passed = passTime / 1000;
	int remaining = remainTime / 1000 - passTime / 1000;
	info->passMin = passed / 60;
	info->passSec = passed - info->passMin * 60;
	info->remainMin = remaining / 60;
	info->remainSec = remaining - info->remainMin * 60;
}

CIntrusion::CIntrusion()
	: m_pDlg(NULL), m_roomNumber(0), m_calcExpMemberSize(0)
{
	(void)&g_EPSILON;
}

CIntrusion::~CIntrusion()
{
}

void CIntrusion::DoJoinRoom(unsigned short roomNumber)
{
	m_roomNumber = roomNumber;
	WSendPacket packet((enumClientPacket)154);
	packet.Encode1(0);
	packet.Encode2(m_roomNumber);
	packet.Send(TO_GAME);
}

bool CIntrusion::OnDelayDlgResult(int result, FrForm* form)
{
	if (result != FrOK)
	{
		AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 59, 0, 0, 0, 0, 0);
		m_pDlg = NULL;
		return true;
	}
	m_pDlg = NULL;
	return true;
}

bool CIntrusion::OnDenyDlgResult(int result, FrForm* form)
{
	AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 59, 0, 0, 0, 0, 0);
	m_pDlg = NULL;
	return true;
}

void CIntrusion::DenyAnlaysis(eIntrusionDenyCode code)
{
	if (!m_pDlg)
	{
		m_pDlg =
			CreateForm<FrForm>(g_pFresh->GetManager(), this, "IntrusionDeny");
		m_pDlg->SetCaption(
			"30\300\316 \264\353\310\270 \260\324\300\323\301\337 \300\324\300\345");
		m_pDlg->SetDesc(
			" \241\330 \260\324\300\323\301\337 \300\324\300\345 \260\341\260\372");
		switch (code)
		{
		case INTRUSION_DENY_CROWDED:
			m_pDlg->SetMessage(
				"\300\316\277\370\300\314 \260\241\265\346 \302\367\274\255 \271\346\277\241 \300\324\300\345 \307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_LATE:
			m_pDlg->SetMessage(
				"\260\324\300\323 \275\303\300\333 \310\304 5\272\320\300\314 \301\366\263\255 \271\346\277\241\264\302 \300\324\300\345 \307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_PRIVATE:
			m_pDlg->SetMessage(
				"\272\361\260\370\260\263 \271\346\277\241\264\302 \260\324\300\323\301\337 \300\324\300\345 \307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_RECENT:
			m_pDlg->SetMessage(
				"\300\314\300\374\277\241 \260\324\300\323\301\337 \300\324\300\345\307\321 \261\342\267\317\300\314 \300\326\276\356\274\255 \264\347\272\320\260\243 \300\324\300\345\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_CLOSED:
			m_pDlg->SetMessage(
				"\307\366\300\347 \260\324\300\323\301\337 \300\324\300\345\300\314 \272\322\260\241\264\311\307\321 \271\346\300\324\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_PLAYED:
			m_pDlg->SetMessage(
				"\307\330\264\347 \271\346\277\241\274\255 \307\303\267\271\300\314\307\321 \261\342\267\317\300\314 \300\326\276\356\274\255 \260\324\300\323\301\337 \300\324\300\345\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		case INTRUSION_DENY_KICKED:
			m_pDlg->SetMessage(
				"\307\330\264\347 \271\346\277\241\274\255 \260\255\301\246 \305\360\300\345\264\347\307\321 \261\342\267\317\300\314 \300\326\276\356\274\255 \300\324\300\345\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				false);
			break;
		}
		m_pDlg->Open((FRESH_PFN_RESULT)&CIntrusion::OnDenyDlgResult, 3);
	}
}

void CIntrusion::RivalDataUpdate(WReceivedPacket& packet)
{
	unsigned long oid = packet.Decode4();
	unsigned char stroke = packet.Decode1();
	unsigned char hole = packet.Decode1();
	int score = packet.Decode4();
	__int64 pang = packet.Decode8();
	sIntrusionReport report;
	memset(&report, 0, sizeof(report));
	packet.DecodeBuffer(&report, sizeof(report));
	if (oid != Doc()->m_myInfo.info.dwGuid)
	{
		RIVAL_LIST_IT it = std::find_if(Doc()->m_rivalList.begin(),
			Doc()->m_rivalList.end(), sFindRival(oid));
		if (it != Doc()->m_rivalList.end())
		{
			it->totalStroke = stroke;
			it->hole = hole;
			it->totalScore = score;
			it->totalPang = pang;
			memcpy(it->holeStroke, report.score.stroke, sizeof(it->holeStroke));
			memcpy(it->holeScore, report.score.score, sizeof(it->holeScore));
			memcpy(it->holePang, report.score.pang, sizeof(it->holePang));
			IActor* scoreActor = AfxGetTask()->GetActor("Score");
			if (scoreActor)
				scoreActor << MsgObject(NULL, 316, 0, 0, 0, 0, 0);
			IActor* spotActor = AfxGetTask()->GetActor("Spot");
			if (spotActor)
				spotActor << MsgObject(NULL, 251, 0, 0, 0, 0, 0);
		}
	}
}

bool CIntrusion::IsIntrusionGame(unsigned short roomNumber)
{
	bool result = false;
	for (std::list<sRoomInfo>::iterator it = Doc()->m_roomList.begin();
		it != Doc()->m_roomList.end(); it++)
		if ((*it).roomGuid == roomNumber)
		{
			result = (*it).bIntrusion;
			break;
		}
	return result;
}

bool CIntrusion::OnAlarmDlgResult(int result, FrForm* form)
{
	if (result == FrOK)
	{
		WSendPacket packet((enumClientPacket)154);
		packet.Encode1(1);
		packet.Encode2(m_roomNumber);
		packet.Send(TO_GAME);
		CSharedDoc* doc = Doc();
		unsigned long caddie = doc->m_myInfo.userEquip.guidCaddie;
		std::map<unsigned int, sCaddieInfo>& caddies = doc->m_caddieMap;
		CADDIE_MAP_IT it = caddies.find(caddie);
		if (it != caddies.end())
		{
			IFF_STRUCT::sCaddie* info =
				ItemManager()->FindCaddie(it->second.tid);
			if (it->second.Rent_flag && !it->second.Remain_Date && info &&
				info->MonthlyFee > 0)
				caddie = 0;
		}
		unsigned long equipment[4];
		memset(equipment, 0, sizeof(equipment));
		equipment[0] = Doc()->m_myInfo.userEquip.guidChar;
		Doc()->m_myInfo.userEquip.guidCaddie = caddie;
		equipment[1] = caddie;
		equipment[2] = Doc()->m_myInfo.userEquip.guidClubSet;
		equipment[3] = Doc()->m_myInfo.userEquip.tidBall;
		WSendPacket equipPacket((enumClientPacket)12);
		equipPacket.Encode1(7);
		equipPacket.EncodeBuffer(equipment, sizeof(equipment));
		equipPacket.Send(TO_GAME);
	}
	else
	{
		AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 59, 0, 0, 0, 0, 0);
		Doc()->m_myInfo.roomIndex = 0xffff;
	}
	m_pDlg = NULL;
	return true;
}

void CIntrusion::DoIntrusionAccess(WReceivedPacket& packet,
	eIntrusionPermitCode code)
{
	switch (code)
	{
	case INTRUSION_PERMIT_ROOM:
	{
		Doc()->m_myInfo.info.dwIdentity &= ~2u;
		Doc()->m_myInfo.info.dwGalleryGuid = -1;
		Doc()->m_slotList.clear();
		Doc()->m_rivalList.clear();
		Doc()->m_guildMatchupList.clear();
		Doc()->m_bGameOver = false;
		packet.DecodeBuffer(&Doc()->m_roomInfo, sizeof(sRoomInfo));
		Doc()->m_chatManager.FilteringHack(Doc()->m_roomInfo.title, false);
		Doc()->m_myInfo.roomIndex = Doc()->m_roomInfo.roomGuid;
		if (WNetworkSystem::Instance()->IsConnected(WNetworkSystem::NET_MSN) &&
			CMessengerInfo::Instance()->GetComplete() == 4)
		{
			sUserPosition position;
			memset(&position, 0, sizeof(position));
			position.iServerGUID = Doc()->m_gameServerUID;
			position.iChannelUid = Doc()->m_curChannel.Uid;
			position.iRoomIdx = Doc()->m_roomInfo.roomGuid;
			position.iRoomType = Doc()->m_roomInfo.gameType;
			wsprintf(position.csChannelName, "%s", Doc()->m_curChannel.Name);
			WSendPacket send(35);
			send.EncodeBuffer(&position, sizeof(position));
			send.Send(TO_MSN);
		}
		break;
	}
	case INTRUSION_PERMIT_SLOTS:
	{
		AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 46, 0, 0, 0, 0, 0);
		Doc()->m_chatLineList.clear();
		std::list<sSlotInfo>& slots = Doc()->m_slotList;
		slots.clear();
		unsigned char count = packet.Decode1();
		for (int i = 0; i < count; ++i)
		{
			sSlotInfo slot;
			packet.DecodeBuffer(&slot, sizeof(slot));
			if (slot.bMaster)
				slot.bReady = true;
			else
				slot.bReady = false;
			slots.push_back(slot);
		}
		break;
	}
	case INTRUSION_PERMIT_MATCH:
		Doc()->m_expRate = packet.Decode4();
		break;
	case INTRUSION_PERMIT_RIVAL:
	{
		Doc()->ClearRivalVars(false);
		Doc()->m_myInfo.info.angelicWings = packet.Decode1();
		Doc()->m_myInfo.info.angelicWingsEffect = packet.Decode1();
		Doc()->m_myInfo.info.devilWings = packet.Decode1();
		if (IsLocalContent((localContentType_t)81))
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			CCardManager::Instance()->m_playerSlot[0] = 0;
			unsigned long character = Doc()->m_myInfo.userEquip.guidChar;
			CHAR_MAP_IT it = Doc()->m_charMap.find(character);
			if (it != Doc()->m_charMap.end())
				CCardManager::Instance()->m_charInfo[0] = it->second;
		}
		Doc()->SetEquipCharCaddieInfoFromMyInfo();
		break;
	}
	case INTRUSION_PERMIT_GAME:
	{
		FrWnd* wnd = g_pFresh->GetDesktop()->FindChildByName("bongdari_shop");
		FrBongdariShopDlg* shop = wnd ? (FrBongdariShopDlg*)wnd
									  : DYNAMIC_CAST(FrBongdariShopDlg, wnd);
		if (shop)
			shop->Clear();
		if (CUserInfo::Instance())
			CUserInfo::Instance()->Clear();
		SetCurMap(packet.Decode1());
		SetGameType(packet.Decode1());
		SetHoleType(packet.Decode1());
		SetHoles(packet.Decode1());
		Doc()->m_roomType = packet.Decode4();
		SetShotTimeLimit(packet.Decode4());
		SetGameTimeLimit(packet.Decode4());
		if (!IsMassGame())
			for (int index = 0; index < 4; ++index)
				if (Doc()->m_userInfo[index].info.dwGuid ==
					Doc()->m_myInfo.info.dwGuid)
					break;
		for (int i = 0; i < 18; ++i)
		{
			Doc()->m_holeRandom[i] = packet.Decode4();
			Doc()->m_courseMap[i] = Doc()->m_holeRandom[i] % 3;
			Doc()->m_holeOrder[i] = packet.Decode1();
		}
		CGimmickContainer* gimmick = NULL;
		CContentsDoc::Instance()->GetContainer((localContentType_t)163,
			gimmick);
		gimmick->LoadFromPacket(packet);
		memset(Doc()->m_holePar, 0, sizeof(Doc()->m_holePar));
		Doc()->m_roomSetupStage = 0;
		Doc()->LogGstUpdateHole(-1, 0xff, -1, -1);
		if (IsLocalContent((localContentType_t)23))
			Doc()->SetInitWearHalloweenItem();
		if (CMessengerInfo::Instance()->GetMyStatus() != 3)
			CMessengerInfo::Instance()->SetMyStatus((MSN::eStatusType)0);
		Doc()->m_bGameOver = false;
		CMouseCursor::Instance()->SetMode(1);
		CMouseCursor::Instance()->SetActive(false);
		COption::Instance()->vSetMinimumScreenSize(false, 800, 600);
		CTaskManager::Instance()->ChangeTask("CGolfTask", "CGolfDoc", false);
		IActor* score = AfxGetTask()->GetActor("Score");
		if (score)
		{
			score << MsgObject(NULL, 305, 0, 0, 0, 0, 0);
			score << MsgObject(NULL, 42, 0, 0, 0, 0, 0);
		}
		break;
	}
	}
}

void CIntrusion::PlayersUpdate(int state)
{
	std::list<sSlotInfo>& slots = Doc()->m_slotList;
	std::vector<sRivalData>& rivals = Doc()->m_rivalList;
	for (std::list<sSlotInfo>::iterator slot = slots.begin();
		slot != slots.end(); ++slot)
	{
		RIVAL_LIST_IT it = std::find_if(rivals.begin(), rivals.end(),
			sFindRival(slot->dwGuid));
		if (it != rivals.end())
			it->quitOrder = state;
		else if (slot->dwGuid == -1)
			GOLFDOC()->GetPlayer(0)->state = 3;
		else
		{
			Doc()->SetIndex(slot->dwGuid);
			sRivalData rival;
			memset(&rival, 0, sizeof(rival));
			strcpy(rival.nickname, slot->sNick);
			strcpy(rival.guildName, slot->sGuild);
			rival.uid = slot->dwUserUID;
			rival.order = state;
			rival.quitOrder = state;
			rival.capability = slot->dwIdentity;
			strcpy(rival.guildMark, slot->szEmblemName);
			rival.finishOrder = slots.size();
			rival.flag = slot->gender;
			rival.oid = slot->dwGuid;
			rival.guildUID = slot->GuildId;
			rival.hole = Doc()->m_holeOrder[0];
			rival.level = slot->level;
			rival.pangMastery = slot->pangma[0];
			rival.pangNitro = slot->pangma[1];
			rival.ballPos = GOLFDOC()->GetHoleData().tee;
			rival.team = slot->bTeam;
			rival.observerState = 1;
			rival.rank = 1;
			rival.observerRank = 1;
			rival.state = 0;
			rival.mascotTypeId = slot->tidMascot;
			rival.titleTypeId = slot->dwTitle;
			rivals.push_back(rival);
		}
	}
	IActor* score = AfxGetTask()->GetActor("Score");
	if (score)
		score << MsgObject(NULL, 316, 0, 0, 0, 0, 0);
	IActor* spot = AfxGetTask()->GetActor("Spot");
	if (spot)
		spot << MsgObject(NULL, 251, 0, 0, 0, 0, 0);
}

void CIntrusion::PacketAnalysis(WReceivedPacket& packet)
{
	if (!m_pDlg)
	{
		unsigned char command = packet.Decode1();
		unsigned char code = packet.Decode1();
		switch (command)
		{
		case 3:
		{
			m_roomNumber = packet.Decode2();
			unsigned long passed = packet.Decode4();
			unsigned long limit = packet.Decode4();
			packet.DecodeBuffer(&Doc()->m_roomInfo, sizeof(sRoomInfo));
			Doc()->m_chatManager.FilteringHack(Doc()->m_roomInfo.title, false);
			Doc()->m_myInfo.roomIndex = Doc()->m_roomInfo.roomGuid;
			m_pDlg = CreateForm<FrForm>(g_pFresh->GetManager(), this,
				"IntrusionAlarm");
			m_pDlg->SetCaption(
				"30\300\316 \264\353\310\270 \260\324\300\323\301\337 \300\324\300\345 \310\256\300\316");
			m_pDlg->SetDesc(
				" \241\330 '\277\271'\270\246 \264\251\270\243\270\351 \301\357\275\303 \260\324\300\323\300\314 \275\303\300\333\265\313\264\317\264\331.");
			sInfoTime info;
			GetInfoTime(&info, passed, limit);
			const char* message = MakeStr(
				"\307\330\264\347 \260\324\300\323\300\272 \260\324\300\323 \275\303\300\333 \310\304\012\\c0xffff0000\\c'%2d\272\320%2d\303\312'\\c0xff000000\\c\260\241 \301\366\263\265\260\355 \\c0xffff0000\\c'%2d\272\320%2d\303\312'\\c0xff000000\\c\260\241\012\263\262\276\306 \300\326\275\300\264\317\264\331.\012\012\301\370\307\340\301\337\300\316 \271\346\277\241 \300\324\300\345\307\317\275\303\260\332\275\300\264\317\261\356?",
				info.passMin, info.passSec, info.remainMin, info.remainSec);
			m_pDlg->SetMessage(message, false);
			m_pDlg->Open((FRESH_PFN_RESULT)&CIntrusion::OnAlarmDlgResult, 1);
			break;
		}
		case 7:
		{
			std::string nick = packet.DecodeStr();
			CChatMsg::Instance()->AddChatMsg(
				MakeStr(
					"(\276\313\270\262) \\c0xffffffff\\c%s\\c0xffff7878\\c\264\324\300\314 \260\324\300\323\301\337\277\241 \300\324\300\345\307\317\274\314\275\300\264\317\264\331.",
					nick.c_str()),
				0xffff7878, true, false);
			packet.DecodeBuffer(&Doc()->m_roomInfo, sizeof(sRoomInfo));
			Doc()->m_chatManager.FilteringHack(Doc()->m_roomInfo.title, false);
			unsigned long match = Doc()->m_roomInfo.tidMatch;
			if (Doc()->m_roomType != match)
			{
				IFF_STRUCT::sMatch* info = ItemManager()->FindMatch(match);
				if (info)
				{
					Doc()->m_roomType = match;
					CChatMsg::Instance()->AddChatMsg(
						MakeStr(
							"(\276\313\270\262) \264\353\310\270 \265\356\261\336\300\314 \\c0xffffffff\\c[ %s ]\\c0xffff7878\\c\300\270\267\316 \272\257\260\346 \265\307\276\372\275\300\264\317\264\331.",
							info->Name),
						0xffff7878, true, false);
				}
			}
			std::list<sSlotInfo>& slots = Doc()->m_slotList;
			slots.clear();
			int count = packet.Decode1();
			unsigned long state = packet.Decode4();
			for (int i = 0; i < count; ++i)
			{
				sSlotInfo slot;
				packet.DecodeBuffer(&slot, sizeof(slot));
				if (slot.bMaster)
					slot.bReady = true;
				else
					slot.bReady = false;
				slots.push_back(slot);
			}
			PlayersUpdate(state);
			break;
		}
		case 4:
			DoIntrusionAccess(packet, (eIntrusionPermitCode)code);
			break;
		case 5:
			m_pDlg = CreateForm<FrForm>(g_pFresh->GetManager(), this,
				"IntrusionAlarm");
			m_pDlg->SetCaption(
				"30\300\316 \264\353\310\270 \260\324\300\323\301\337 \300\324\300\345");
			m_pDlg->SetDesc(
				" \241\330 '\277\271'\270\246 \264\251\270\243\270\351 \264\331\275\303 \300\324\300\345\300\273 \275\303\265\265\307\325\264\317\264\331.");
			m_pDlg->SetMessage(
				"\300\257\300\372\260\241 \270\271\276\306 \300\324\300\345\277\241 \275\307\306\320 \307\317\277\264\275\300\264\317\264\331. \264\331\275\303 \275\303\265\265 \307\317\275\303\260\332\275\300\264\317\261\356?",
				false);
			m_pDlg->Open((FRESH_PFN_RESULT)&CIntrusion::OnDelayDlgResult, 1);
			break;
		case 6:
			DenyAnlaysis((eIntrusionDenyCode)code);
			break;
		case 9:
		{
			unsigned long oid = packet.Decode4();
			unsigned char state = packet.Decode4();
			unsigned long myOid = Doc()->m_myInfo.info.dwGuid;
			if (oid == myOid)
			{
				for (RIVAL_LIST_IT it = Doc()->m_rivalList.begin();
					it != Doc()->m_rivalList.end(); ++it)
					it->quitOrder = state;
			}
			else
			{
				sIntrusionReport report;
				memset(&report, 0, sizeof(report));
				RIVAL_LIST_IT it = std::find_if(Doc()->m_rivalList.begin(),
					Doc()->m_rivalList.end(), sFindRival(myOid));
				if (it != Doc()->m_rivalList.end())
				{
					sIntrusionScore score;
					memset(&score, 0, sizeof(score));
					memcpy(score.score, it->holeScore, sizeof(score.score));
					memcpy(score.stroke, it->holeStroke, sizeof(score.stroke));
					memcpy(score.pang, it->holePang, sizeof(score.pang));
					report.score = score;
					report.source = oid;
					report.target = Doc()->m_myInfo.info.dwGuid;
				}
				else
				{
					report.source = oid;
					report.target = -1;
				}
				WSendPacket send((enumClientPacket)154);
				send.Encode1(2);
				send.EncodeBuffer(&report, sizeof(report));
				send.Send(TO_GAME);
			}
			break;
		}
		case 10:
			RivalDataUpdate(packet);
			break;
		case 8:
			m_calcExpMemberSize = packet.Decode1();
			break;
		}
	}
}
