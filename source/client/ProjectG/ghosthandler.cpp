#include "stdafx.h"
#include "ghostdata.h"

class CGhostDocument;

class CGhostRecorder : public IActor
{
public:
	DECLARE_OBJECT(CGhostRecorder)
	CGhostRecorder();
	virtual ~CGhostRecorder() { }
	virtual void OnLoad();
	virtual void OnProcess(float delta) { }
	virtual void OnDisplay() { }
	virtual void OnReload();
	virtual void OnInit();
	virtual void OnDestroy();

protected:
	virtual void HandleMsg(const MsgObject& msg);

private:
	bool IsSaveAvailable();
	CGhostDocument* m_pDocument;
};

#include "ghosthandler.h"
#include "ghostmanager.h"
#include "ghostloader.h"
#include "ghostdocument.h"
#include "ghostgamedlg.h"
#include "golfdoc.h"
#include "mousecursor.h"
#include "tinyxml.h"
#include "minatl.h"

extern Fresh* g_pFresh;

IMPLEMENT_ACTOR(CGhostRecorder, IActor)

CGhostRecorder::CGhostRecorder()
	: m_pDocument(NULL)
{
}

bool CGhostRecorder::IsSaveAvailable()
{
	if (Doc()->m_golfGame.gameType != 4 && Doc()->m_golfGame.gameType != 0)
		return false;
	if (Doc()->m_holeType == 4)
		return false;
	if (Doc()->m_roomInfo.realGameType == 14)
		return false;
	if (Doc()->m_golfGame.holes != 18)
		return false;
	return true;
}

void CGhostRecorder::HandleMsg(const MsgObject& msg)
{
	if (!m_pDocument)
		return;
	if (msg.message != 11)
		m_pDocument->RecordHoleData(msg);
	else
		CGhostManager::Instance()->ReleaseDocument();
}

void CGhostRecorder::OnLoad()
{
	CGhostManager::Instance()->ReleaseDocument();
	if (OnlinePlay() && IsSaveAvailable())
	{
		m_pDocument = CGhostManager::Instance()->GetDocument();
		m_pDocument->RecordUserData();
		m_pDocument->RecordGameData();
	}
}

void CGhostRecorder::OnReload()
{
}

void CGhostRecorder::OnInit()
{
}

void CGhostRecorder::OnDestroy()
{
}

CGhostLoader::CGhostLoader()
{
}

bool CGhostLoader::LoadFromMemory(unsigned char* data, unsigned int size)
{
	CGhostManager::Instance()->ReleaseDocument();
	CGhostDocument* doc = CGhostManager::Instance()->GetDocument();
	return doc->Import(data, size);
}

bool CGhostLoader::LoadFromFile(const std::string& name)
{
	CGhostManager::Instance()->ReleaseDocument();
	CGhostDocument* doc = CGhostManager::Instance()->GetDocument();
	return doc->Import(name);
}

namespace
{
	const char* const NOTIFY_MSG_SERVICE_STOP = K2L_Compatibility(
		"\260\355\275\272\306\256 \274\255\272\361\275\272 \301\241\260\313\301\337\300\324\264\317\264\331. \300\314\277\353\277\241 \272\322\306\355\300\273 \265\345\267\301\274\255 \301\313\274\333\307\325\264\317\264\331.");
	const char* const RECORD_DLG_LOADING_FAIL = K2L_Compatibility(
		"\267\316\265\371\277\241 \275\307\306\320\307\317\277\264\275\300\264\317\264\331.");
	const char* const CANNOT_UNDERSTAND_MSG = K2L_Compatibility(
		"\264\324\300\307 \260\355\275\272\306\256\260\241 \276\356\270\256\265\325\300\375\307\330 \307\325\264\317\264\331.");
	const char* const NOTIFY_MSG_GHOST_NOSAVE = K2L_Compatibility(
		"\307\366\300\347 \300\257\300\372\277\241\260\324 \300\372\300\345\265\310 \260\355\275\272\306\256\260\241 \276\370\275\300\264\317\264\331.");
	const char* const NOTIFY_MSG_GHOST_NODATA = K2L_Compatibility(
		"\260\355\275\272\306\256 \265\245\300\314\305\315\260\241 \301\270\300\347 \307\317\301\366 \276\312\275\300\264\317\264\331.");
	const char* const NOTIFY_MSG_GHOST_SAVED = K2L_Compatibility(
		"\260\355\275\272\306\256 \265\245\300\314\305\315\260\241 \260\273\275\305\265\307\276\372\275\300\264\317\264\331.");
	const char* const NOTIFY_MSG_UNKNOWN_ERROR = K2L_Compatibility(
		"\275\303\275\272\305\333 \301\241\260\313\301\337\300\324\264\317\264\331.");
	const char* const NOTIFY_MSG_DATA_ERROR = K2L_Compatibility(
		"\274\325\273\363\265\310 \265\245\300\314\305\315\260\241 \271\337\260\337\265\307\276\356 \264\365\300\314\273\363 \260\324\300\323\300\273 \301\370\307\340\307\322 \274\366 \276\370\275\300\264\317\264\331.");
	const char* const NOTIFY_MSG_NETWAIT_OVER = K2L_Compatibility(
		"\274\255\271\366\277\241 \277\344\303\273\300\314 \270\271\275\300\264\317\264\331. \300\341\275\303 \310\304 \264\331\275\303 \300\314\277\353\307\330 \301\326\274\274\277\344.");
	const char* const GHOST_ROOM_JOIN_WELCOME = K2L_Compatibility(
		"(\276\313\270\262)\134c0xffffffff\134c%s\134c0xffff7878\134c\264\324\300\314 \300\324\300\345\307\317\274\314\275\300\264\317\264\331.");
	const char* const NOTIFY_MSG_DISABLE_GAME = K2L_Compatibility(
		"\274\325\273\363\265\310 \265\245\300\314\305\315\277\315\264\302 \300\347\264\353\260\341 \307\317\275\307 \274\366 \276\370\275\300\264\317\264\331. \264\331\270\245 \260\355\275\272\306\256\277\315 \264\353\300\374\307\330\301\326\274\274\277\344.");
	const char* const NOTIFY_MSG_NOT_DEFINED = K2L_Compatibility(
		"\301\244\300\307\265\310 \277\300\267\371 \270\336\274\274\301\366\260\241 \276\370\275\300\264\317\264\331.");

	class CEventGhostXmlFile
	{
	public:
		bool Load()
		{
			m_gameList.clear();
			TiXmlDocument doc;
			if (!doc.LoadFileEx("event_ghost.xml"))
				return false;
			std::string uid, file;
			TiXmlNode* active = doc.FirstChild("active");
			if (!active)
				return false;
			uid = active->ToElement()->Attribute("uid");
			if (uid == "-1")
				return false;
			TiXmlNode* element = active->FirstChild("element");
			TiXmlElement* item;
			while (element)
			{
				item = element->ToElement();
				if (uid == item->Attribute("uid"))
				{
					m_nick = item->Attribute("nick");
					TiXmlNode* param = element->FirstChild("param");
					while (param)
					{
						file = param->ToElement()->Attribute("file");
						if (!file.empty())
						{
							GHOST_GAME_BRIEF brief;
							memset(&brief, 0, sizeof(brief));
							GetGhostGameBriefFromFileName(&brief, file.c_str());
							brief.recordCount = 1;
							m_gameList.push_back(brief);
						}
						param = param->NextSibling();
					}
					return !m_gameList.empty();
				}
				element = element->NextSibling();
			}
			return false;
		}
		const std::string& GetNick() const { return m_nick; }
		const std::list<GHOST_GAME_BRIEF>& GetGameList() const
		{
			return m_gameList;
		}

	private:
		std::string m_nick;
		std::list<GHOST_GAME_BRIEF> m_gameList;
	};
}

CGhostHandler::CGhostHandler()
{
}

CGhostHandler::~CGhostHandler()
{
}

bool CGhostHandler::IsAvailableGhostSystem()
{
	if (!IsLocalContent(S4_GHOST))
		return false;
	if (Doc()->m_curChannel.Type & 0x800)
		return false;
	return true;
}

void CGhostHandler::OpenNotifyDlg(int type)
{
	FrForm* dlg = CreateForm<FrForm>(g_pFresh->GetManager(), this, "notify");
	dlg->SetTopmost(true);
	dlg->FindNextTopFocus(NULL);
	dlg->SetTimeLimit(7.0f);
	switch (type)
	{
	case 7:
		dlg->SetMessage(NOTIFY_MSG_SERVICE_STOP, false);
		break;
	case 0:
		dlg->SetMessage(NOTIFY_MSG_GHOST_NOSAVE, false);
		break;
	case 1:
		dlg->SetMessage(NOTIFY_MSG_GHOST_NODATA, false);
		break;
	case 2:
		dlg->SetMessage(RECORD_DLG_LOADING_FAIL, false);
		break;
	case 4:
		dlg->SetMessage(NOTIFY_MSG_UNKNOWN_ERROR, false);
		break;
	case 5:
		dlg->SetMessage(NOTIFY_MSG_DATA_ERROR, false);
		break;
	case 6:
		dlg->SetMessage(NOTIFY_MSG_NETWAIT_OVER, false);
		break;
	case 8:
		dlg->SetMessage(NOTIFY_MSG_DISABLE_GAME, false);
		break;
	default:
		dlg->SetMessage(NOTIFY_MSG_NOT_DEFINED, false);
		break;
	}
	dlg->Open(NULL, 0);
}

bool CGhostHandler::IsExistEventGhost()
{
	CEventGhostXmlFile file;
	return file.Load();
}

bool CGhostHandler::OpenEventGhostGameDlg()
{
	CEventGhostXmlFile file;
	if (!file.Load())
		return false;
	OpenGhostGameDlg(-1, file.GetNick(), file.GetGameList(),
		(FRESH_PFN_RESULT)&CGhostHandler::OnResultEventGhostGameDlg);
	return true;
}

void CGhostHandler::OpenGhostGameDlg(unsigned long uid, const std::string& nick,
	const std::list<GHOST_GAME_BRIEF>& list, FRESH_PFN_RESULT callback)
{
	if (g_pFresh->GetDesktop()->FindChildForm("GHOST_GAMEMAP"))
		return;
	FrGhostGameMapDlg* dlg = CreateForm<FrGhostGameMapDlg>(
		g_pFresh->GetManager(), this, "GHOST_GAMEMAP");
	dlg->SetTopmost(true);
	dlg->FindNextTopFocus(NULL);
	dlg->Init(uid, nick, list);
	dlg->EnableDrag(false);
	dlg->SetFlag(FrNOTAIL);
	dlg->Open(callback, 1);
}

void CGhostHandler::RecordComplete()
{
	if (GOLFDOC())
	{
		int score = PLAYER(MyIndex())->score;
		int pang = PLAYER(MyIndex())->totalPang;
		score += (int)PLAYER(MyIndex())->stroke[GOLFDOC()->m_currentHole - 1] -
			GOLFDOC()->GetHoleData().par;
		unsigned char character =
			(unsigned char)Doc()->m_userInfo[MyIndex()].charInfo.tid;
		if (score < 0)
		{
			WSendPacket packet((enumClientPacket)186);
			packet.Encode1(4);
			packet.Encode1(GetCurMap());
			packet.Encode1(character);
			packet.Encode4(abs(score));
			packet.Encode4(pang);
			packet.Send((eSendTo)0);
			return;
		}
	}
	CGhostManager::Instance()->ReleaseDocument();
}

void CGhostHandler::LoadingComplete(bool success)
{
	AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 2, 0, 0, 0, 0, 0));
	if (success)
	{
		CMouseCursor::Instance()->SetActive(false);
		CTaskManager::Instance()->ChangeTask("CGhostTask", "",
			CTaskManager::Instance()->GetPreservedTask() != NULL);
		CTaskManager::Instance()->PostMsg(NULL, "Ghost", 0, (int)"GHOST", 0, 0,
			0);
	}
	else
	{
		OpenNotifyDlg(2);
		SendErrorReport("GHOST FILE LOAD FAILED",
			CGhostManager::Instance()->GetLatestFileName());
	}
}

void CGhostHandler::UploadComplete(bool success, const std::string& name)
{
	ClearLocalGhostFiles();
	if (success)
	{
		WSendPacket packet((enumClientPacket)186);
		packet.Encode1(5);
		packet.EncodeStr(name);
		packet.Send((eSendTo)0);
	}
	else
		SendErrorReport("GHOST FILE UPLOAD FAILED.", name);
}

void CGhostHandler::OnGhostPacket(WReceivedPacket& packet)
{
	if (!IsAvailableGhostSystem())
		return;
	switch (packet.Decode1())
	{
	case 12:
	{
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 2, 0, 0, 0, 0, 0));
		int count = packet.Decode4();
		unsigned long uid = packet.Decode4();
		if (!count)
		{
			OpenNotifyDlg(0);
			break;
		}
		{
			std::list<GHOST_GAME_BRIEF> games;
			std::string nick;
			for (int i = 0; i < count; ++i)
			{
				unsigned long values[5] = { 0 };
				for (int j = 0; j < 5; ++j)
					values[j] = packet.Decode4();
				packet.DecodeStr(nick);
				unsigned long recordCount = packet.Decode4();
				GHOST_GAME_BRIEF brief;
				brief.owner = uid;
				brief.course = values[0];
				brief.itemId = values[1];
				brief.score = values[2];
				brief.pang = values[3];
				brief.recordId = values[4];
				brief.recordCount = recordCount;
				games.push_back(brief);
			}
			OpenGhostGameDlg(uid, nick, games,
				(FRESH_PFN_RESULT)&CGhostHandler::OnResultGhostGameDlg);
		}
	}
	break;
	case 13:
	{
		std::string name;
		packet.DecodeStr(name);
		CGhostManager::Instance()->SaveDocument(name);
	}
	break;
	case 14:
		CGhostManager::Instance()->ReleaseDocument();
		ClearLocalGhostFiles();
		break;
	case 16:
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 2, 0, 0, 0, 0, 0));
		switch (packet.Decode1())
		{
		case 25:
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 2, 0, 0, 0, 0, 0));
			OpenNotifyDlg(1);
			break;
		case 28:
			OpenNotifyDlg(7);
			break;
		case 26:
			OpenNotifyDlg(6);
			break;
		}
		break;
	case 19:
	{
		packet.Decode1();
		unsigned long typeId = packet.Decode4();
		unsigned long itemId = packet.Decode4();
		packet.Decode1();
		if (!(typeId & 0x2000000))
			AfxGetTask()->GetActor("Item")
				<< MsgObject(NULL, 415, -1, typeId, itemId, 0, 0);
	}
	break;
	case 22:
	{
		FrWnd* wnd = g_pFresh->GetDesktop()->FindChildByName("GHOST_HISTORY");
		if (!wnd && !IS_KINDOF(FrRecentMatch, wnd))
			break;
		FrRecentMatch* dlg = (FrRecentMatch*)wnd;

		{
			if (packet.Decode1() != 255)
			{
				unsigned long count = packet.Decode4();
				for (unsigned long i = 0; i < count; ++i)
				{
					FrRecentMatch::sRecentMatchForm record;
					record.sex = packet.Decode1();
					record.nick = packet.DecodeStr();
					record.win = packet.Decode4();
					packet.DecodeBuffer(&record.date, sizeof(record.date));
					record.pang = packet.Decode4();
					record.grade = packet.Decode1();
					dlg->AddHistory(record);
				}
				dlg->AddFinish();
			}
			else
				dlg->Exception();
		}
	}
	break;
	}
}

bool CGhostHandler::OnResultGhostGameDlg(int result, FrForm* form)
{
	if (result == FrOK)
	{
		FrGhostGameMapDlg* dlg = DYNAMIC_CAST(FrGhostGameMapDlg, form);
		GHOST_GAME_BRIEF* brief = (GHOST_GAME_BRIEF*)dlg->GetSelectItem();
		if (brief)
		{
			std::string name = MakeGhostGameFileName(brief);
			CGhostManager::Instance()->LoadDocument(name);
			CGhostManager::Instance()->SetRecentSelectedGhostNick(
				dlg->GetGhostNick());
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
		}
		else
			OpenNotifyDlg(4);
	}
	return true;
}

bool CGhostHandler::OnResultEventGhostGameDlg(int result, FrForm* form)
{
	if (result == FrOK)
	{
		FrGhostGameMapDlg* dlg = DYNAMIC_CAST(FrGhostGameMapDlg, form);
		GHOST_GAME_BRIEF* brief = (GHOST_GAME_BRIEF*)dlg->GetSelectItem();
		if (brief)
		{
			std::string name = MakeGhostGameFileName(brief);
			CGhostManager::Instance()->SetRecentSelectedGhostNick(
				dlg->GetGhostNick());
			CGhostManager::Instance()->LoadDocumentFromLocalFile(name);
		}
		else
			OpenNotifyDlg(4);
	}
	return true;
}

void CGhostHandler::ClearLocalGhostFiles()
{
	WIN32_FIND_DATA data;
	HANDLE find = FindFirstFile(".\\temporary_save\\*.GST", &data);
	if (find != INVALID_HANDLE_VALUE)
	{
		do
		{
			DeleteFile(data.cFileName);
		} while (FindNextFile(find, &data));
		FindClose(find);
	}
}

void CGhostHandler::SendErrorReport(const std::string& error,
	const std::string& name)
{
	WSendPacket packet((enumClientPacket)186);
	packet.Encode1(8);
	packet.EncodeStr(name);
	packet.EncodeStr(error);
	packet.Send((eSendTo)0);
}

void CGhostHandler::ExceptionFinishGame()
{
	CGhostManager::Instance()->ReleaseDocument();
	CProjectG::Instance()->FromGolfToLobbySettings();
	OpenNotifyDlg(5);
	CTaskManager::Instance()->ChangeTask("CGhostTask", "", false);
	CTaskManager::Instance()->PostMsg(NULL, "Ghost", 0, (int)"GHOST", 1, 0, 0);
}

void CGhostHandler::RequestGhostGameList(unsigned long uid)
{
	if (!IsAvailableGhostSystem())
		return;
	if (IsLocalContent(S4_MATCHING_SYSTEM))
	{
		WSendPacket packet((enumClientPacket)185);
		packet.Encode1(2);
		packet.Send((eSendTo)0);
	}
	WSendPacket packet((enumClientPacket)186);
	packet.Encode1(0);
	packet.Encode4(uid);
	packet.Send((eSendTo)0);
	AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
}
