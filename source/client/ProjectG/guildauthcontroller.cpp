#include "guildauthcontroller.h"
#include "ingameguildlobbydlg.h"
#include "guildactor.h"
#include "guilddefine.h"
#include "contentsdoc.h"
#include "taskmanager.h"
#include "frcontextmenuctrl.h"
#include "user_info.h"

extern Fresh* g_pFresh;

namespace _guild
{
	CGuildMainForm* IGuildAuthController::m_linkForm = NULL;
	CGuildInfo* IGuildAuthController::m_linkInfo = NULL;

	IGuildAuthController::IGuildAuthController()
	{
		(void)&g_EPSILON;
	}

	IGuildAuthController::~IGuildAuthController()
	{
	}

	void IGuildAuthController::SetLinkDepends(CGuildMainForm* pForm,
		CGuildInfo* pInfo)
	{
		m_linkForm = pForm;
		m_linkInfo = pInfo;
	}

	void IGuildAuthController::PopupCommandMenu(float x, float y)
	{
		m_linkForm->m_pCmdMenu->MoveWindow(WPoint(x, y));
		m_linkForm->m_pCmdMenu->SetVisible(true);
	}

	void IGuildAuthController::OnGuildJoin_LButtonUp()
	{
		if (m_linkInfo->IsGuildMember() == true)
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
				(int)m_linkInfo->GuildMsg(1013), 0, 0, 0, 0));
	}

	void CGuildManager::DrawGuildTalk(FrListItem* pItem)
	{
		CGuildMainForm::sMemberItem* pMember =
			(CGuildMainForm::sMemberItem*)pItem->pData;
		if (pMember->bEdit)
			return;
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		gdi->Print(WPoint(pItem->pos.x + m_linkForm->m_talkEditPosX,
					   pItem->pos.y + 10),
			0, pMember->pInfo->message);
		const Bitmap* bitmap = m_linkForm->m_pBitmap[15];
		if (bitmap)
			gdi->DrawTexture(bitmap,
				WRect(pItem->pos.x + m_linkForm->m_talkButtonPosX,
					pItem->pos.y + 5, (float)bitmap->Width(),
					(float)bitmap->Height()),
				0xffffffff, 0);
	}

	void CGuildManager::ProcManagerCommand(const char* cmd)
	{
		if (!m_linkForm->m_pSelectedItem)
			return;
		const GUILD_USER_LIST* pInfo = m_linkForm->m_pCommandUser;
		if (strcmp("\xbd\xc2\xc0\xce(\xbd\xc2\xb1\xde)", cmd) == 0)
		{
			if (pInfo->userUID == MyUID())
				return;
			if (m_linkInfo->IsGuildMember(pInfo->classIdx))
			{
				if (pInfo->classIdx == 1 || pInfo->classIdx == 2)
					AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
						(int)m_linkInfo->GuildMsg(1011), 0, 0, 0, 0));
				else if (pInfo->classIdx == 3)
				{
					WSendPacket packet((enumClientPacket)0x10d);
					packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
					packet.Encode4(pInfo->userUID);
					packet.Encode4(2);
					packet.Send(TO_GAME);
					AfxGetTask()->SendMsgToMainActor(
						MsgObject(NULL, 1, 0, 0, 0, 0, 0));
				}
			}
			else
			{
				WSendPacket packet((enumClientPacket)0x10b);
				packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
				packet.Encode4(pInfo->userUID);
				packet.Send(TO_GAME);
				AfxGetTask()->SendMsgToMainActor(
					MsgObject(NULL, 1, 0, 0, 0, 0, 0));
			}
		}
		else if (strcmp("\xb0\xad\xb5\xee", cmd) == 0)
		{
			if (pInfo->userUID == MyUID())
				return;
			if (m_linkInfo->IsGuildMember(pInfo->classIdx))
			{
				if (pInfo->classIdx == 2)
				{
					WSendPacket packet((enumClientPacket)0x10d);
					packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
					packet.Encode4(pInfo->userUID);
					packet.Encode4(3);
					packet.Send(TO_GAME);
					AfxGetTask()->SendMsgToMainActor(
						MsgObject(NULL, 1, 0, 0, 0, 0, 0));
				}
				else
					AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
						(int)m_linkInfo->GuildMsg(1012), 0, 0, 0, 0));
			}
			else if (pInfo->classIdx == 9)
			{
				WSendPacket packet((enumClientPacket)0x10c);
				packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
				packet.Encode4(pInfo->userUID);
				packet.Send(TO_GAME);
				AfxGetTask()->SendMsgToMainActor(
					MsgObject(NULL, 1, 0, 0, 0, 0, 0));
			}
		}
		else if (strcmp("\xb1\xe6\xb5\xe5\xc0\xe5 \xc0\xa7\xc0\xd3", cmd) == 0)
		{
			if (pInfo->userUID == MyUID())
				return;
			if (pInfo->classIdx > 2)
				AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
					(int)m_linkInfo->GuildMsg(1036), 0, 0, 0, 0));
			else if (pInfo->classIdx == 2)
			{
				IActor* pActor = AfxGetTask()->GetActor(s_guildActor[1]);
				pActor << MsgObject(NULL, 611, 30,
					(int)m_linkInfo->GuildMsg(1032), 1, 0, 0);
			}
		}
		else if (strcmp("\xb1\xe6\xb5\xe5\xbf\xf8 \xc3\xdf\xb9\xe6", cmd) == 0)
		{
			if (pInfo->userUID == MyUID())
				return;
			WSendPacket packet((enumClientPacket)0x111);
			packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
			packet.Encode4(pInfo->userUID);
			packet.Send(TO_GAME);
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
		}
		else if (strcmp("\xc1\xa4\xba\xb8\xba\xb8\xb1\xe2", cmd) == 0)
		{
			CUserInfo::Instance()->SetInfo(pInfo->userUID, -1, false, true,
				false, true, pInfo->nickname);
		}
	}

	void CGuildManager::OnGuildIntroConfirm_LButtonUp()
	{
		std::string text;
		int lines = m_linkForm->m_pEdit[0]->GetLineNum();
		for (int i = 1; i <= lines; ++i)
		{
			text += m_linkForm->m_pEdit[0]->GetLine(i, false);
			if (i != lines)
				text += s_guildLineFeed;
		}
		if (text == m_linkInfo->GetMyGuildInfo().introduce)
		{
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
				(int)m_linkInfo->GuildMsg(1060), 0, 0, 0, 0));
			return;
		}
		str_Replace(text, "'", "`");
		int result = Doc()->m_chatManager.FilteringGuildString(text.c_str(), 2,
			100, false);
		if (result != 1)
		{
			if (result > 0)
				AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
					(int)m_linkInfo->GuildMsg(result), 0, 0, 0, 0));
			return;
		}
		std::string introduce = text;
		str_Replace(introduce, "`", "'");
		m_linkInfo->SetGuildIntroduce(introduce);
		WSendPacket packet((enumClientPacket)0x103);
		packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
		packet.Encode4(MyUID());
		packet.EncodeStr(text);
		packet.Send(TO_GAME);
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
	}

	void CGuildManager::OnGuildNoticeConfirm_LButtonUp()
	{
		std::string text;
		int lines = m_linkForm->m_pEdit[1]->GetLineNum();
		for (int i = 1; i <= lines; ++i)
		{
			text += m_linkForm->m_pEdit[1]->GetLine(i, false);
			text += s_guildLineFeed;
		}
		if (text == m_linkInfo->GetMyGuildInfo().notice)
		{
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
				(int)m_linkInfo->GuildMsg(1060), 0, 0, 0, 0));
			return;
		}
		str_Replace(text, "'", "`");
		int result = Doc()->m_chatManager.FilteringGuildString(text.c_str(), 2,
			100, false);
		if (result != 1)
		{
			if (result > 0)
				AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
					(int)m_linkInfo->GuildMsg(result), 0, 0, 0, 0));
			return;
		}
		std::string notice = text;
		str_Replace(notice, "`", "'");
		m_linkInfo->SetGuildNotice(notice);
		WSendPacket packet((enumClientPacket)0x102);
		packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
		packet.Encode4(MyUID());
		packet.EncodeStr(text);
		packet.Send(TO_GAME);
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
	}

	void CGuildMaster::PopupCommandMenu(float x, float y)
	{
		IGuildAuthController::PopupCommandMenu(x, y);
		m_linkForm->m_pCmdMenu->SetMenuList(m_linkInfo->GuildMsg(1008));
	}

	void CGuildMaster::OnGuildShutDown_LButtonUp()
	{
		IActor* pActor = AfxGetTask()->GetActor(s_guildActor[1]);
		pActor << MsgObject(NULL, 611, 30, (int)m_linkInfo->GuildMsg(1024), 0,
			0, 0);
	}

	void CGuildMaster::OnGuildOut_LButtonUp()
	{
		AfxGetTask()->SendMsgToMainActor(
			MsgObject(NULL, 35, (int)m_linkInfo->GuildMsg(1022), 0, 0, 0, 0));
	}

	void CGuildSubMaster::PopupCommandMenu(float x, float y)
	{
		IGuildAuthController::PopupCommandMenu(x, y);
		m_linkForm->m_pCmdMenu->SetMenuList(m_linkInfo->GuildMsg(1009));
	}

	void CGuildSubMaster::OnGuildOut_LButtonUp()
	{
		IActor* pActor = AfxGetTask()->GetActor(s_guildActor[1]);
		pActor << MsgObject(NULL, 611, 30, (int)m_linkInfo->GuildMsg(1047), 2,
			0, 0);
	}

	void CGuildMember::DrawGuildTalk(FrListItem* pItem)
	{
		CGuildMainForm::sMemberItem* pMember =
			(CGuildMainForm::sMemberItem*)pItem->pData;
		if (pMember->bEdit)
			return;
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		gdi->Print(WPoint(pItem->pos.x + m_linkForm->m_talkEditPosX,
					   pItem->pos.y + 10),
			0, pMember->pInfo->message);
		if (pMember->pInfo->userUID != MyUID())
			return;
		const Bitmap* bitmap = m_linkForm->m_pBitmap[15];
		if (bitmap)
		{
			gdi->DrawTexture(bitmap,
				WRect(pItem->pos.x + m_linkForm->m_talkButtonPosX,
					pItem->pos.y + 5, (float)bitmap->Width(),
					(float)bitmap->Height()),
				0xffffffff, 0);
		}
	}

	void CGuildMember::PopupCommandMenu(float x, float y)
	{
		IGuildAuthController::PopupCommandMenu(x, y);
		m_linkForm->m_pCmdMenu->SetMenuList(m_linkInfo->GuildMsg(1010));
	}

	void CGuildMember::ProcManagerCommand(const char* cmd)
	{
		if (!m_linkForm->m_pSelectedItem)
			return;
		CGuildMainForm::sMemberItem* pMember =
			(CGuildMainForm::sMemberItem*)m_linkForm->m_pSelectedItem->pData;
		if (strcmp("\xc1\xa4\xba\xb8\xba\xb8\xb1\xe2", cmd) == 0)
		{
			CUserInfo::Instance()->SetInfo(pMember->pInfo->userUID, -1, false,
				true, false, true, pMember->pInfo->nickname);
		}
	}

	void CGuildMember::OnGuildOut_LButtonUp()
	{
		IActor* pActor = AfxGetTask()->GetActor(s_guildActor[1]);
		pActor << MsgObject(NULL, 611, 30, (int)m_linkInfo->GuildMsg(1047), 2,
			0, 0);
	}

	void CGuildWaitMember::OnGuildJoinAbort_LButtonUp()
	{
		WSendPacket packet((enumClientPacket)0x10a);
		packet.Encode4(m_linkInfo->GetMyGuildInfo().guildUID);
		packet.Send(TO_GAME);
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
	}

	void CGuildWaitMember::OnGuildOut_LButtonUp()
	{
		AfxGetTask()->SendMsgToMainActor(
			MsgObject(NULL, 35, (int)m_linkInfo->GuildMsg(1022), 0, 0, 0, 0));
	}

	void CGuildNull::OnGuildJoin_LButtonUp()
	{
		IGuildAuthController::OnGuildJoin_LButtonUp();
		IActor* pActor = AfxGetTask()->GetActor(s_guildActor[1]);
		if (pActor)
		{
			pActor << MsgObject(NULL, 611, 29,
				m_linkForm->m_selectGuild.guildUID, 0, 0, 0);
		}
	}
}
