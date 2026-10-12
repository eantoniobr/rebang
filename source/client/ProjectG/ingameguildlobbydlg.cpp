#include "guildauthcontroller.h"
#include "ingameguildlobbydlg.h"
#include "guildformcontroller.h"
#include "guildactor.h"
#include "s5/utilities.h"
#include "guilddefine.h"
#include "contentsdoc.h"
#include "actor.h"
#include "taskmanager.h"
#include "mousecursor.h"
#include "inputmanager.h"
#include "wresrcmng.h"
#include "frcontextmenuctrl.h"
#include "frscrollbar.h"
#include "netresourcemanager.h"

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

extern Fresh* g_pFresh;

namespace _guild
{

	IMPLEMENT_OBJECT(CGuildMainForm, FrForm)
	BEGIN_FRESH_MSGMAP(CGuildMainForm, FrForm)
	ON_FRESH_VI("set_info", FRCMD_INIT, CGuildMainForm::OnGuildInfo_ButtonInit)
	ON_FRESH_VV("set_info", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildInfo_LButtonUp)
	ON_FRESH_VI("set_member", FRCMD_INIT,
		CGuildMainForm::OnGuildMember_ButtonInit)
	ON_FRESH_VV("set_member", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildMember_LButtonUp)
	ON_FRESH_VI("set_search", FRCMD_INIT,
		CGuildMainForm::OnGuildSearch_ButtonInit)
	ON_FRESH_VV("set_search", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildSearch_LButtonUp)
	ON_FRESH_VI("guild_info_detail", FRCMD_INIT,
		CGuildMainForm::OnGuildDetail_AreaInit)
	ON_FRESH_VI("guild_info_detail", FRCMD_OWNERDRAW,
		CGuildMainForm::OnGuildDetail_OwnerDraw)
	ON_FRESH_VI("guild_info_introduce", FRCMD_INIT,
		CGuildMainForm::OnGuildIntroduce_AreaInit)
	ON_FRESH_VI("guild_info_notice", FRCMD_INIT,
		CGuildMainForm::OnGuildNotice_AreaInit)
	ON_FRESH_VI("guild_info_action", FRCMD_INIT,
		CGuildMainForm::OnGuildAct_AreaInit)
	ON_FRESH_VI("guild_info_empty", FRCMD_INIT,
		CGuildMainForm::OnEmptyGuild_AreaInit)
	ON_FRESH_VI("guild_info_empty", FRCMD_OWNERDRAW,
		CGuildMainForm::OnEmptyGuild_AreaOwnerDraw)
	ON_FRESH_VI("member_info_bg", FRCMD_INIT,
		CGuildMainForm::OnGuildMemberInfoBg_AreaInit)
	ON_FRESH_VI("member_info_bg", FRCMD_OWNERDRAW,
		CGuildMainForm::OnGuildMemberInfoBg_OwnerDraw)
	ON_FRESH_VI("search_bg1", FRCMD_INIT, CGuildMainForm::OnSearchBg1_AreaInit)
	ON_FRESH_VI("search_bg2", FRCMD_INIT, CGuildMainForm::OnSearchBg2_AreaInit)
	ON_FRESH_VI("guild_intro_edit", FRCMD_INIT,
		CGuildMainForm::OnGuildIntroduce_EditInit)
	ON_FRESH_VI("guild_notice_edit", FRCMD_INIT,
		CGuildMainForm::OnGuildNotice_EditInit)
	ON_FRESH_VI("guild_action_edit", FRCMD_INIT,
		CGuildMainForm::OnGuildAct_EditInit)
	ON_FRESH_VI("guild_search_edit", FRCMD_INIT,
		CGuildMainForm::OnGuildSearch_EditInit)
	ON_FRESH_VI("guild_search_edit", FRCMD_ENTERKEY,
		CGuildMainForm::OnGuildSearch_EnterKey)
	ON_FRESH_VI("guild_talk_edit", FRCMD_INIT,
		CGuildMainForm::OnGuildMemberTalk_EditInit)
	ON_FRESH_VI("form_close", FRCMD_INIT, CGuildMainForm::OnGuildForm_CloseInit)
	ON_FRESH_VV("form_close", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildForm_CloseLButtonUp)
	ON_FRESH_VI("guild_intro_confirm", FRCMD_INIT,
		CGuildMainForm::OnGuildIntroConfirm_ButtonInit)
	ON_FRESH_VV("guild_intro_confirm", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildIntroConfirm_LButtonUp)
	ON_FRESH_VI("guild_notice_confirm", FRCMD_INIT,
		CGuildMainForm::OnGuildNoticeConfirm_ButtonInit)
	ON_FRESH_VV("guild_notice_confirm", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildNoticeConfirm_LButtonUp)
	ON_FRESH_VI("guild_search_btn", FRCMD_INIT,
		CGuildMainForm::OnGuildSearchInfo_ButtonInit)
	ON_FRESH_VV("guild_search_btn", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildSearchInfo_LButtonUp)
	ON_FRESH_VI("guild_join", FRCMD_INIT,
		CGuildMainForm::OnGuildJoin_ButtonInit)
	ON_FRESH_VV("guild_join", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildJoin_LButtonUp)
	ON_FRESH_VI("guild_shutdown", FRCMD_INIT,
		CGuildMainForm::OnGuildShutDown_ButtonInit)
	ON_FRESH_VV("guild_shutdown", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildShutDown_LButtonUp)
	ON_FRESH_VI("guild_out", FRCMD_INIT, CGuildMainForm::OnGuildOut_ButtonInit)
	ON_FRESH_VV("guild_out", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildOut_LButtonUp)
	ON_FRESH_VI("join_abort", FRCMD_INIT,
		CGuildMainForm::OnGuildJoinAbort_ButtonInit)
	ON_FRESH_VV("join_abort", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildJoinAbort_LButtonUp)
	ON_FRESH_VI("talk_confirm", FRCMD_INIT,
		CGuildMainForm::OnGuildMemberTalk_ButtonInit)
	ON_FRESH_VV("talk_confirm", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildMemberTalk_LButtonUp)
	ON_FRESH_VI("search_prev", FRCMD_INIT,
		CGuildMainForm::OnGuildSearchPrev_ButtonInit)
	ON_FRESH_VV("search_prev", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildSearchPrev_LButtonUp)
	ON_FRESH_VI("search_next", FRCMD_INIT,
		CGuildMainForm::OnGuildSearchNext_ButtonInit)
	ON_FRESH_VV("search_next", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildSearchNext_LButtonUp)
	ON_FRESH_VI("guild_member_list", FRCMD_INIT,
		CGuildMainForm::OnGuildMemberInfo_ListBoxInit)
	ON_FRESH_VI("guild_member_list", FRCMD_OWNERDRAW,
		CGuildMainForm::OnGuildMemberInfo_OwnerDraw)
	ON_FRESH_VV("guild_member_list", FRCMD_LBUTTONUP,
		CGuildMainForm::OnGuildMemberInfo_LButtonDown)
	ON_FRESH_VI("member_page_listbox", FRCMD_INIT,
		CGuildMainForm::OnMemberPage_ListBoxInit)
	ON_FRESH_VI("member_page_listbox", FRCMD_OWNERDRAW,
		CGuildMainForm::OnMemberPage_ListOwnerDraw)
	ON_FRESH_VV("member_page_listbox", FRCMD_LBUTTONDOWN,
		CGuildMainForm::OnMemberPage_ListLButtonDown)
	ON_FRESH_VI("guild_search_list", FRCMD_INIT,
		CGuildMainForm::OnGuildSearchInfo_ListBoxInit)
	ON_FRESH_VI("guild_search_list", FRCMD_OWNERDRAW,
		CGuildMainForm::OnGuildSearchInfo_OwnerDraw)
	ON_FRESH_VV("guild_search_list", FRCMD_LBUTTONDOWN,
		CGuildMainForm::OnGuildSearchInfo_LButtonDown)
	ON_FRESH_VI("search_page_listbox", FRCMD_INIT,
		CGuildMainForm::OnGuildSearchPage_ListBoxInit)
	ON_FRESH_VI("search_page_listbox", FRCMD_OWNERDRAW,
		CGuildMainForm::OnGuildSearchPage_OwnerDraw)
	ON_FRESH_VV("search_page_listbox", FRCMD_LBUTTONDOWN,
		CGuildMainForm::OnGuildSearchPage_LButtonDown)
	ON_FRESH_VI("cmd_rmenu", FRCMD_INIT,
		CGuildMainForm::OnGuildManagerCmd_ContextInit)
	ON_FRESH_VV("cmd_rmenu", FRCMD_LBUTTONDOWN,
		CGuildMainForm::OnGuildManagerCmd_LButtonDown)
	ON_FRESH_VV("cmd_rmenu", FRCMD_RBUTTONDOWN,
		CGuildMainForm::OnGuildManagerCmd_LButtonUp)
	END_FRESH_MSGMAP()

	CGuildMainForm::CGuildMainForm()
	{
		(void)&g_EPSILON;
		InitControl();
	}

	CGuildMainForm::~CGuildMainForm()
	{
		if (g_resrcmng && m_pOverFont)
		{
			g_resrcmng->Release(m_pOverFont);
			m_pOverFont = NULL;
		}
		if (g_resrcmng && m_pNormalFont)
		{
			g_resrcmng->Release(m_pNormalFont);
			m_pNormalFont = NULL;
		}
		std::for_each(m_authController.begin(), m_authController.end(),
			Delete_SecondObject());
		if (m_pPageArrow)
		{
			delete m_pPageArrow;
			m_pPageArrow = NULL;
		}
		if (m_pController)
		{
			delete m_pController;
			m_pController = NULL;
		}
	}

	bool CGuildMainForm::OnInit()
	{
		LoadResource();
		static char* normalFont[] = { "guild_normal_font.tga" };
		static char* overFont[] = { "guild_over_font.tga" };
		WTITLEFONT font;
		memset(&font, 0, sizeof(font));
		font.filename = normalFont;
		font.fontw = 12;
		font.fonth = 14;
		font.numPages = 1;
		font.texw = 120;
		font.texh = 14;
		font.pCharSet = "0123456789";
		m_pNormalFont = g_resrcmng->GetTitleFont();
		m_pNormalFont->Create(&font);
		memset(&font, 0, sizeof(font));
		font.filename = overFont;
		font.fontw = 13;
		font.fonth = 16;
		font.numPages = 1;
		font.texw = 130;
		font.texh = 16;
		font.pCharSet = "0123456789";
		m_pOverFont = g_resrcmng->GetTitleFont();
		m_pOverFont->Create(&font);
		m_formStyle = FORM_INFO;
		Controller()->ControllForm(m_formStyle, ConvertGuildClass());
		m_pTabButton[0]->SetStatus(FrButton::PRESSED);
		CreateAuthController();
		const WRect& listRect = m_pListBox[0]->GetRect();
		m_talkEditPosX = listRect.w * .5f + 6;
		m_talkButtonPosX = (listRect.w - m_pButton[8]->GetRect().w * 1.4f) - 1;
		unsigned long guild = GuildInfo()->GetMyGuildInfo().guildUID;
		if (guild)
		{
			WSendPacket packet((enumClientPacket)257);
			packet.Encode4(guild);
			packet.Send(TO_GAME);
		}
		{
			WSendPacket packet((enumClientPacket)261);
			packet.Encode4(1);
			packet.Send(TO_GAME);
		}
		return FrForm::OnInit();
	}

	void CGuildMainForm::OnProc(const float delta)
	{
		if (m_formStyle == FORM_MEMBER)
		{
			if (g_input->GetButton(LEFT_BUTTON) == 0 &&
				g_input->GetButton(RIGHT_BUTTON) == 0)
				return;
			if (!CMouseCursor::Instance()->InArea(m_pListBox[0]->GetRect()) &&
				m_pCmdMenu)
				m_pCmdMenu->SetVisible(false);
		}
	}

	void CGuildMainForm::Refresh()
	{
		switch (m_formStyle)
		{
		case FORM_INFO:
			RefreshMyGuildInfo();
			RefreshMyGuildHistory();
			break;
		case FORM_MEMBER:
			RefreshGuildMember();
			break;
		case FORM_SEARCH:
			RefreshGuildSearch();
			break;
		}
	}

	void CGuildMainForm::RefreshMyGuildInfo()
	{
		const GUILD_INFO& info = GuildInfo()->GetMyGuildInfo();
		if (info.classIdx == 9)
			Controller()->ControllForm(FORM_INFO, AUTH_WAIT);
		else if (info.classIdx == 3)
			Controller()->ControllForm(FORM_INFO, AUTH_MEMBER);
		m_pEdit[0]->ClearLine();
		m_pEdit[0]->AddText(info.introduce, false, true);
		m_pEdit[0]->ResetKeyFocus();
		m_pEdit[0]->GetScrollBar()->ScrollToFirst();
		m_pEdit[1]->ClearLine();
		m_pEdit[1]->AddText(info.notice, false, true);
		m_pEdit[1]->GetScrollBar()->ScrollToFirst();
		m_pEdit[2]->ClearLine();
	}

	void CGuildMainForm::RefreshMyGuildHistory()
	{
		const std::list<GUILD_HISTORY>& history = GuildInfo()->GetHistoryList();
		std::string text;
		for (std::list<GUILD_HISTORY>::const_iterator it = history.begin();
			it != history.end(); ++it)
		{
			char line[256];
			memset(line, 0, sizeof(line));
			sprintf(line, s_guildJoinDateFormat, (*it).time.wYear,
				(*it).time.wMonth, (*it).time.wDay,
				GuildInfo()->GuildMsg(ConvertGuildHistory((*it).state)));
			text += line;
		}
		m_pEdit[2]->AddText(text.c_str(), false, true);
	}

	void CGuildMainForm::RefreshGuildMember()
	{
		if (m_pListBox[0]->GetCurrentItemSize(true) > 0)
			m_pListBox[0]->ClearItem();
		if (!m_memberList.empty())
			m_memberList.clear();
		m_pSelectedItem = NULL;
		const std::list<GUILD_USER_LIST>* members =
			GuildInfo()->GetMemberList(m_memberPage);
		if (members)
		{
			for (std::list<GUILD_USER_LIST>::const_iterator it =
					 members->begin();
				it != members->end(); ++it)
			{
				sMemberItem item;
				item.pInfo = &*it;
				m_memberList.push_back(item);
			}
			for (MemberIterator it = m_memberList.begin();
				it != m_memberList.end(); ++it)
				m_pListBox[0]->AddItem(&*it);
			RefreshMemberPageList();
			ClearCommandUserInfo();
			if (m_pCmdMenu)
				m_pCmdMenu->SetVisible(false);
		}
	}

	void CGuildMainForm::RefreshGuildSearch()
	{
		if (m_pListBox[1]->GetCurrentItemSize(true) > 0)
			m_pListBox[1]->ClearItem();
		if (!m_searchList.empty())
			m_searchList.clear();
		const std::list<GUILD_LIST>* guilds =
			GuildInfo()->GetSearchList(m_searchPage);
		if (guilds)
		{
			for (std::list<GUILD_LIST>::const_iterator it = guilds->begin();
				it != guilds->end(); ++it)
				m_searchList.push_back(&*it);
			for (SearchIterator it = m_searchList.begin();
				it != m_searchList.end(); ++it)
				m_pListBox[1]->AddItem((void*)*it);
			RefreshSearchPageList();
		}
	}

	void CGuildMainForm::RefreshMemberPageList()
	{
		m_pListBox[2]->ClearItem();
		int pages = GuildInfo()->GetMaxMemberPage();
		for (int i = 0; i < pages; ++i)
			m_pListBox[2]->AddItem(NULL);
		const WRect& listRect = m_pListBox[2]->GetRect();
		int count = m_pListBox[2]->GetCurrentItemSize(true);
		int width = m_pListBox[2]->GetItemWidth();
		float center = (GetRect().x + GetRect().w) * .5f;
		WRect rect(listRect);
		rect.x = center - (float)width * count + count * 10.f;
		m_pListBox[2]->SetRect(rect);
	}

	void CGuildMainForm::RefreshSearchPageList()
	{
		m_pListBox[3]->ClearItem();
		int pages = GuildInfo()->GetMaxSearchPage();
		m_pListBox[1]->GetCurrentItemSize(true);
		unsigned group = (m_searchPage - 1U) / 5;
		int first = group * 5;
		int last = 0;
		if (m_searchPage < pages)
		{
			if (group == (pages - 1U) / 5)
				last = pages;
			else
				last = first + 5;
		}
		else
		{
			const int& current = m_searchPage;
			if (current == pages)
				last = current;
		}
		for (int i = first; i < last; ++i)
			m_pListBox[3]->AddItem((void*)i);
		m_pPageArrow->RefreshArrowButton(pages, m_searchPage);
		int count = m_pListBox[3]->GetCurrentItemSize(true);
		const WRect& area = m_pArea[7]->GetRect();
		float center = area.x + area.w * .5f;
		float position =
			center - (float)m_pListBox[3]->GetItemWidth() * count * .5f + 6;
		WRect rect(m_pListBox[3]->GetRect());
		rect.x = position;
		m_pListBox[3]->SetRect(rect);
	}

	void CGuildMainForm::RequestMember_Page(int page)
	{
		GUILD_CLASS_IDX classIdx = MyGuildClassIndex();
		if (classIdx != 0 && classIdx != 9)
		{
			WSendPacket packet((enumClientPacket)271);
			packet.Encode4(GuildInfo()->GetMyGuildInfo().guildUID);
			packet.Encode4(page ? page : m_memberPage);
			packet.Send(TO_GAME);
		}
	}

	void CGuildMainForm::RequestSearch_Page(int page)
	{
		if (m_searchMode == 0)
		{
			m_searchPage = page;
			WSendPacket packet((enumClientPacket)261);
			packet.Encode4(page ? page : 1);
			packet.Send(TO_GAME);
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
		}
		else if (m_searchMode == 1)
		{
			m_searchPage = page;
			WSendPacket packet((enumClientPacket)262);
			packet.Encode4(page);
			packet.EncodeStr(m_searchName);
			packet.Send(TO_GAME);
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
		}
	}

	void CGuildMainForm::RequestChangeClass(GUILD_CLASS_IDX classIdx)
	{
		if (m_pCommandUser)
		{
			WSendPacket packet((enumClientPacket)269);
			packet.Encode4(GuildInfo()->GetMyGuildInfo().guildUID);
			packet.Encode4(m_pCommandUser->userUID);
			packet.Encode4(classIdx);
			packet.Send(TO_GAME);
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
		}
	}

	void CGuildMainForm::ClearForm()
	{
		m_pEdit[0]->ClearLine();
		m_pEdit[1]->ClearLine();
		m_pEdit[2]->ClearLine();
		m_pListBox[0]->ClearItem();
		m_memberList.clear();
		Controller()->ControllForm(FORM_INFO, ConvertGuildClass());
		m_formStyle = FORM_INFO;
		m_pTabButton[0]->SetStatus(FrButton::PRESSED);
		m_pTabButton[1]->SetStatus(FrButton::NORMAL);
		m_pTabButton[2]->SetStatus(FrButton::NORMAL);
	}

	void CGuildMainForm::DisableJoinButton()
	{
		FrButton* button = m_pButton[3];
		if (button)
		{
			button->SetVisible(false);
			button->Enable(false);
		}
	}

	void CGuildMainForm::InitSearchMode()
	{
		m_searchMode = 0;
	}

	void CGuildMainForm::LockScrollMemberList()
	{
		if (m_pListBox[0])
			m_pListBox[0]->EnableScrollBar(false);
	}

	void CGuildMainForm::UnLockScrollMemberList()
	{
		if (m_pListBox[0] && m_pListBox[0]->GetSelected())
			m_pListBox[0]->EnableScrollBar(true);
	}

	void CGuildMainForm::InitControl()
	{
		memset(m_pTabButton, 0, sizeof(m_pTabButton));
		memset(m_pArea, 0, sizeof(m_pArea));
		memset(m_pEdit, 0, sizeof(m_pEdit));
		memset(m_pButton, 0, sizeof(m_pButton));
		memset(m_pListBox, 0, sizeof(m_pListBox));
		memset(m_pBitmap, 0, sizeof(m_pBitmap));
		memset(&m_selectGuild, 0, sizeof(m_selectGuild));
		m_pSelectedItem = NULL;
		m_pController = _util::NewCreator<CGuildFormController>::CreateObject();
		m_pPageArrow = _util::NewCreator<CPageArrow>::CreateObject();
		m_pNormalFont = NULL;
		m_pOverFont = NULL;
		m_pGuildInfo = NULL;
		m_formStyle = FORM_NONE;
		m_talkEditPosX = 0;
		m_talkButtonPosX = 0;
		m_pCommandUser = NULL;
		m_memberPage = 1;
		m_searchPage = 1;
		m_searchMode = 0;
	}

	void CGuildMainForm::LoadResource()
	{
		const char* names[] = { "guild_con_member_bg01",
			"guild_con_member_bg02", "guild_con_member_bg03",
			"guild_con_member_bg04", "guild_icon_manager",
			"guild_icon_assistant", "guild_icon_member", "guild_icon_waiting",
			"guild_not_join_bg1", "guild_not_join_bg2", "guild_wating_bg",
			"guild_member_on", "guild_member_off", "guild_select_line_o",
			"guild_select_line_d", "guild_btn_modification_n",
			"guild_btn_ok_n" };
		for (int i = 0; i < 17; ++i)
			m_pBitmap[i] = g_pFresh->RegisterBitmap(names[i]);
	}

	void CGuildMainForm::CreateAuthController()
	{
		m_authController.insert(std::make_pair((GUILD_CLASS_IDX)1,
			_util::NewCreator<CGuildMaster>::CreateObject()));
		m_authController.insert(std::make_pair((GUILD_CLASS_IDX)2,
			_util::NewCreator<CGuildSubMaster>::CreateObject()));
		m_authController.insert(std::make_pair((GUILD_CLASS_IDX)3,
			_util::NewCreator<CGuildMember>::CreateObject()));
		m_authController.insert(std::make_pair((GUILD_CLASS_IDX)9,
			_util::NewCreator<CGuildWaitMember>::CreateObject()));
		m_authController.insert(std::make_pair((GUILD_CLASS_IDX)0,
			_util::NewCreator<CGuildNull>::CreateObject()));
		m_authController[(GUILD_CLASS_IDX)1];
		IGuildAuthController::SetLinkDepends(this, GuildInfo());
	}

	void CGuildMainForm::PopupMemberCommand(float x, float y)
	{
		if (m_pSelectedItem)
		{
			sMemberItem* item = (sMemberItem*)m_pSelectedItem->pData;
			ClearCommandUserInfo();
			SetCommandUserInfo(item->pInfo);
			m_authController[MyGuildClassIndex()]->PopupCommandMenu(x, y);
			EnableAuthCommand(MyGuildClassIndex());
		}
	}

	void CGuildMainForm::SelectMemberItem(FrListBox* list, FrListItem* item)
	{
		if (m_pSelectedItem &&
			((sMemberItem*)m_pSelectedItem->pData)->bEdit == true)
		{
			m_pEdit[4]->ClearLine();
			FrWnd* control = m_pEdit[4];
			control->SetVisible(false);
			control->Enable(false);
			control = m_pButton[8];
			control->SetVisible(false);
			control->Enable(false);
			list->OrderItem(
				_util::MakeMemFun1(*this, &CGuildMainForm::ResetEditState));
		}
		list->UnselectItem(m_pSelectedItem);
		list->SelectItem(item, true);
		m_pSelectedItem = item;
	}

	void CGuildMainForm::ProcManagerCommand(const char* command)
	{
		if (strlen(command) >= 1)
			m_authController[MyGuildClassIndex()]->ProcManagerCommand(command);
	}

	void CGuildMainForm::CheckTalkState()
	{
		FrWnd* control = m_pButton[8];
		control->SetVisible(true);
		control->Enable(true);
		control = m_pEdit[4];
		control->SetVisible(true);
		control->Enable(true);
		if (!m_pSelectedItem)
		{
			m_pSelectedItem = m_pListBox[0]->GetSelected();
			if (!m_pSelectedItem)
				return;
		}
		{
			const WPoint& point = m_pSelectedItem->pos;
			WRect rect(0, point.y + 5, 0, m_pListBox[0]->GetItemHeight());
			rect.x = m_talkEditPosX + point.x;
			rect.w = m_pEdit[4]->GetRect().w;
			m_pEdit[4]->SetRect(rect);
			rect.x = m_talkButtonPosX + point.x;
			rect.w = m_pButton[8]->GetRect().w;
			rect.h = m_pButton[8]->GetRect().h;
			m_pButton[8]->SetRect(rect);
			sMemberItem* item = (sMemberItem*)m_pSelectedItem->pData;
			int length = strlen(item->pInfo->message);
			if (length > 0)
			{
				if (length > 25)
					return;
				m_pEdit[4]->ClearLine();
				m_pEdit[4]->ForcedEdit(item->pInfo->message, 0);
			}
			LockScrollMemberList();
		}
	}

	void CGuildMainForm::EnableAuthCommand(GUILD_CLASS_IDX classIdx)
	{
		GUILD_CLASS_IDX targetClass =
			((sMemberItem*)m_pSelectedItem->pData)->pInfo->classIdx;
		switch (classIdx)
		{
		case 1:
			if (targetClass == 1)
			{
			}
			else
				switch (targetClass)
				{
				case 2:
					m_pCmdMenu->UnableMenuItem(GuildMsg(1081));
					break;
				case 3:
				case 9:
					m_pCmdMenu->UnableMenuItem(GuildMsg(1082));
					break;
				}
			break;
		case 2:
			switch (targetClass)
			{
			case 1:
			case 2:
				m_pCmdMenu->UnableMenuItem(GuildMsg(1081));
				m_pCmdMenu->UnableMenuItem(GuildMsg(1082));
				m_pCmdMenu->UnableMenuItem(GuildMsg(1083));
				break;
			case 3:
			case 9:
				m_pCmdMenu->UnableMenuItem(GuildMsg(1082));
				break;
			}
		}
	}

	void CGuildMainForm::ResetEditState(void* data)
	{
		((sMemberItem*)data)->bEdit = false;
	}

	void CGuildMainForm::UnSelectMember()
	{
		FrListItem* item = m_pListBox[0]->GetSelected();
		if (item)
		{
			ResetEditState(item->pData);
			UnLockScrollMemberList();
			m_pListBox[0]->UnselectItem(item);
		}
	}

	eAuthority CGuildMainForm::ConvertGuildClass()
	{
		eAuthority authority = AUTH_ALL;
		const GUILD_INFO& info = GuildInfo()->GetMyGuildInfo();
		switch (info.classIdx)
		{
		case 0:
			authority = AUTH_NONE;
			break;
		case 1:
			authority = AUTH_MASTER;
			break;
		case 2:
			authority = AUTH_SUBMASTER;
			break;
		case 3:
			authority = AUTH_MEMBER;
			break;
		case 9:
			authority = AUTH_WAIT;
			break;
		}
		return authority;
	}

	bool CGuildMainForm::CanExecuteClass(const GUILD_USER_LIST* info)
	{
		GUILD_CLASS_IDX classIdx = MyGuildClassIndex();
		if (classIdx > 0 &&
			(classIdx <= 2 ||
				(classIdx == 3 && info->userUID == Doc()->m_myInfo.info.dwUID)))
			return true;
		return false;
	}

	const char* CGuildMainForm::GuildMsg(int index)
	{
		return GuildInfo()->GuildMsg(index);
	}

	GUILD_CLASS_IDX CGuildMainForm::MyGuildClassIndex()
	{
		return GuildInfo()->GetClassIndex();
	}

	void CGuildMainForm::OnGuildInfo_ButtonInit(int param)
	{
		m_pTabButton[0] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void CGuildMainForm::OnGuildInfo_LButtonUp()
	{
		if (m_formStyle != FORM_INFO)
		{
			m_pEdit[0]->ClearLine();
			m_pEdit[0]->AddText(GuildInfo()->GetMyGuildInfo().introduce, false,
				true);
			m_pEdit[0]->GetScrollBar()->ScrollToFirst();
			Controller()->ControllForm(FORM_INFO, ConvertGuildClass());
			m_formStyle = FORM_INFO;
			if (m_pTabButton[1]->GetStatus() == FrButton::PRESSED)
				UnSelectMember();
			m_pTabButton[0]->SetStatus(FrButton::PRESSED);
			m_pTabButton[1]->SetStatus(FrButton::NORMAL);
			m_pTabButton[2]->SetStatus(FrButton::NORMAL);
		}
	}

	void CGuildMainForm::OnGuildMember_ButtonInit(int param)
	{
		m_pTabButton[1] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void CGuildMainForm::OnGuildMember_LButtonUp()
	{
		if (m_formStyle != FORM_MEMBER)
		{
			Controller()->ControllForm(FORM_MEMBER, ConvertGuildClass());
			m_formStyle = FORM_MEMBER;
			m_pTabButton[0]->SetStatus(FrButton::NORMAL);
			m_pTabButton[1]->SetStatus(FrButton::PRESSED);
			m_pTabButton[2]->SetStatus(FrButton::NORMAL);
		}
	}

	void CGuildMainForm::OnGuildSearch_ButtonInit(int param)
	{
		m_pTabButton[2] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void CGuildMainForm::OnGuildSearch_LButtonUp()
	{
		if (m_formStyle != FORM_SEARCH)
		{
			Controller()->ControllForm(FORM_SEARCH, ConvertGuildClass());
			m_formStyle = FORM_SEARCH;
			int maxPage = GuildInfo()->GetMaxSearchPage();
			m_pPageArrow->RefreshArrowButton(maxPage, m_searchPage);
			if (m_pTabButton[1]->GetStatus() == FrButton::PRESSED)
				UnSelectMember();
			m_pTabButton[0]->SetStatus(FrButton::NORMAL);
			m_pTabButton[1]->SetStatus(FrButton::NORMAL);
			m_pTabButton[2]->SetStatus(FrButton::PRESSED);
		}
	}

	void CGuildMainForm::OnGuildDetail_AreaInit(int param)
	{
		m_pArea[0] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[0]);
		Controller()->InsertPostAction(m_pArea[0], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pArea[0], FORM_INFO,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::MoveLeftSide);
		Controller()->InsertPostAction(m_pArea[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pArea[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::MoveRightSide);
	}

	void CGuildMainForm::OnGuildDetail_OwnerDraw(int param)
	{
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		const WRect& rect = m_pArea[0]->GetRect();
		static const float lineHeight = 28.f;
		float x = rect.x + 86;
		float y = rect.y + 14;
		if (m_formStyle == FORM_INFO)
		{
			if (GuildInfo()->IsGuildMember() == true)
			{
				gdi->SetTextStyle(1);
				gdi->SetTextColor(0xff33365f, 0xffffffff);
				const GUILD_INFO& info = GuildInfo()->GetMyGuildInfo();
				const Bitmap* bitmap =
					NetResourceManager::Instance()->GetEmblemByName(
						info.guildMark);
				if (bitmap)
					gdi->DrawTexture(bitmap,
						WRect(x + 99, rect.y + 3, (float)bitmap->Width(),
							(float)bitmap->Height()),
						0xffffffff, 0);
				gdi->Print11(WPoint(x, y), 0, info.guildName);
				y += lineHeight;
				gdi->Print11(WPoint(x, y), 0, info.masterNickname);
				y += lineHeight;
				gdi->Print11(WPoint(x, y), 0, "%d \xb8\xed", info.memberCount);
				y += lineHeight;
				gdi->Print11(WPoint(x, y), 0, "%d \xc6\xce", info.guildPang);
				y += lineHeight;
				gdi->Print11(WPoint(x, y), 0, "- \xb7\xb9\xba\xa7(%d \xc1\xa1)",
					info.guildPoint);
			}
		}
		else if (m_formStyle == FORM_SEARCH)
		{
			if (m_selectGuild.guildUID == 0)
				return;
			gdi->SetTextStyle(1);
			gdi->SetTextColor(0xff33365f, 0xffffffff);
			const Bitmap* bitmap =
				NetResourceManager::Instance()->GetEmblemByName(
					m_selectGuild.guildMark);
			if (bitmap)
				gdi->DrawTexture(bitmap,
					WRect(x + 99, rect.y + 3, (float)bitmap->Width(),
						(float)bitmap->Height()),
					0xffffffff, 0);
			gdi->Print11(WPoint(x, y), 0, m_selectGuild.guildName);
			y += lineHeight;
			gdi->Print11(WPoint(x, y), 0, m_selectGuild.masterNickname);
			y += lineHeight;
			gdi->Print11(WPoint(x, y), 0, "%d \xb8\xed",
				m_selectGuild.memberCount);
			y += lineHeight;
			gdi->Print11(WPoint(x, y), 0, "%d \xc6\xce",
				m_selectGuild.guildPang);
			y += lineHeight;
			gdi->Print11(WPoint(x, y), 0, "- \xb7\xb9\xba\xa7(%d \xc1\xa1)",
				m_selectGuild.guildPoint);
		}
		gdi->SetTextStyle(0);
		gdi->SetTextColor(0, 0xffffffff);
	}

	void CGuildMainForm::OnGuildIntroduce_AreaInit(int param)
	{
		m_pArea[1] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[1]);
		Controller()->InsertPostAction(m_pArea[1], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pArea[1], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::MoveLeftSide);
		Controller()->InsertPostAction(m_pArea[1], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pArea[1], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::MoveRightSide);
	}

	void CGuildMainForm::OnGuildNotice_AreaInit(int param)
	{
		m_pArea[2] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[2]);
		Controller()->InsertPostAction(m_pArea[2], FORM_INFO,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildAct_AreaInit(int param)
	{
		m_pArea[3] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[3]);
		Controller()->InsertPostAction(m_pArea[3], FORM_INFO,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnEmptyGuild_AreaInit(int param)
	{
		m_pArea[4] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[4]);
		Controller()->InsertPostAction(m_pArea[4], FORM_INFO,
			AUTH_NONE | AUTH_WAIT, &CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnEmptyGuild_AreaOwnerDraw(int param)
	{
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		if (GuildInfo()->IsWaitingJoin())
		{
			const WRect& rect = m_pArea[4]->GetRect();
			gdi->DrawTexture(m_pBitmap[10],
				WRect(rect.x + 15, rect.y + 57, m_pBitmap[10]->Width(),
					m_pBitmap[10]->Height()),
				0xffffffff, 0);
			gdi->SetTextStyle(1);
			gdi->SetTextColor(0xff33365f, 0xffffffff);
			gdi->Print(WPoint(rect.x + 107, rect.y + 89), 1,
				GuildInfo()->GetMyGuildInfo().guildName);
			gdi->SetTextStyle(0);
			gdi->SetTextColor(0, 0xffffffff);
		}
		else if (!GuildInfo()->IsGuildMember())
		{
			const WRect& rect = m_pArea[4]->GetRect();
			gdi->DrawTexture(m_pBitmap[8],
				WRect(rect.x, rect.y, m_pBitmap[8]->Width(),
					m_pBitmap[8]->Height()),
				0xffffffff, 0);
			gdi->DrawTexture(m_pBitmap[9],
				WRect(rect.x, rect.y + 256, m_pBitmap[8]->Width(),
					m_pBitmap[9]->Height()),
				0xffffffff, 0);
		}
	}

	void CGuildMainForm::OnGuildMemberInfoBg_AreaInit(int param)
	{
		m_pArea[5] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[5]);
		Controller()->InsertPostAction(m_pArea[5], FORM_MEMBER,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildMemberInfoBg_OwnerDraw(int param)
	{
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		gdi->DrawTexture(m_pBitmap[0],
			WRect(GetRect().x + 68, GetRect().y + 83, m_pBitmap[0]->Width(),
				m_pBitmap[0]->Height()),
			0xffffffff, 0);
		gdi->DrawTexture(m_pBitmap[1],
			WRect(GetRect().x + 324, GetRect().y + 83, m_pBitmap[1]->Width(),
				m_pBitmap[1]->Height()),
			0xffffffff, 0);
		gdi->DrawTexture(m_pBitmap[2],
			WRect(GetRect().x + 68, GetRect().y + 339, m_pBitmap[2]->Width(),
				m_pBitmap[2]->Height()),
			0xffffffff, 0);
		gdi->DrawTexture(m_pBitmap[3],
			WRect(GetRect().x + 324, GetRect().y + 339, m_pBitmap[3]->Width(),
				m_pBitmap[3]->Height()),
			0xffffffff, 0);
	}

	void CGuildMainForm::OnSearchBg1_AreaInit(int param)
	{
		m_pArea[6] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[6]);
		Controller()->InsertPostAction(m_pArea[6], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnSearchBg2_AreaInit(int param)
	{
		m_pArea[7] = DYNAMIC_CAST(FrArea, (FrWnd*)param);
		Controller()->InsertControl(m_pArea[7]);
		Controller()->InsertPostAction(m_pArea[7], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildIntroduce_EditInit(int param)
	{
		m_pEdit[0] = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
		Controller()->InsertControl(m_pEdit[0]);
		Controller()->InsertPostAction(m_pEdit[0], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pEdit[0], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::MoveLeftSide);
		Controller()->InsertPostAction(m_pEdit[0], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER,
			&CGuildFormController::WritableWindow);
		Controller()->InsertPostAction(m_pEdit[0], FORM_INFO, AUTH_MEMBER,
			&CGuildFormController::ReadOnlywindow);
		Controller()->InsertPostAction(m_pEdit[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pEdit[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::MoveRightSide);
		Controller()->InsertPostAction(m_pEdit[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::ClearEdit);
		Controller()->InsertPostAction(m_pEdit[0], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::ReadOnlywindow);
	}

	void CGuildMainForm::OnGuildNotice_EditInit(int param)
	{
		m_pEdit[1] = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
		Controller()->InsertControl(m_pEdit[1]);
		Controller()->InsertPostAction(m_pEdit[1], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pEdit[1], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER,
			&CGuildFormController::WritableWindow);
		Controller()->InsertPostAction(m_pEdit[1], FORM_INFO,
			AUTH_NONE | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::ReadOnlywindow);
	}

	void CGuildMainForm::OnGuildAct_EditInit(int param)
	{
		m_pEdit[2] = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
		Controller()->InsertControl(m_pEdit[2]);
		Controller()->InsertPostAction(m_pEdit[2], FORM_INFO,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
		Controller()->InsertPostAction(m_pEdit[2], FORM_INFO,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::ReadOnlywindow);
	}

	void CGuildMainForm::OnGuildSearch_EditInit(int param)
	{
		m_pEdit[3] = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
		Controller()->InsertControl(m_pEdit[3]);
		Controller()->InsertPostAction(m_pEdit[3], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildSearch_EnterKey(int param)
	{
		OnGuildSearchInfo_LButtonUp();
	}

	void CGuildMainForm::OnGuildMemberTalk_EditInit(int param)
	{
		m_pEdit[4] = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
		Controller()->InsertControl(m_pEdit[4]);
	}

	void CGuildMainForm::OnGuildForm_CloseInit(int param)
	{
		m_pButton[0] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void CGuildMainForm::OnGuildForm_CloseLButtonUp()
	{
		Close(true);
	}

	void CGuildMainForm::OnGuildIntroConfirm_ButtonInit(int param)
	{
		m_pButton[1] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[1]);
		Controller()->InsertPostAction(m_pButton[1], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER, &CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildIntroConfirm_LButtonUp()
	{
		m_authController[MyGuildClassIndex()]->OnGuildIntroConfirm_LButtonUp();
	}

	void CGuildMainForm::OnGuildNoticeConfirm_ButtonInit(int param)
	{
		m_pButton[2] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[2]);
		Controller()->InsertPostAction(m_pButton[2], FORM_INFO,
			AUTH_MASTER | AUTH_SUBMASTER, &CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildNoticeConfirm_LButtonUp()
	{
		m_authController[MyGuildClassIndex()]->OnGuildNoticeConfirm_LButtonUp();
	}

	void CGuildMainForm::OnGuildJoin_ButtonInit(int param)
	{
		m_pButton[3] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[3]);
		Controller()->InsertPostAction(m_pButton[3], FORM_SEARCH, AUTH_NONE,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildJoin_LButtonUp()
	{
		if (m_selectGuild.guildUID == 0)
		{
			AfxGetTask()->SendMsgToMainActor(
				MsgObject(NULL, 35, (int)GuildMsg(1038), 0, 0, 0, 0));
			return;
		}
		m_authController[MyGuildClassIndex()]->OnGuildJoin_LButtonUp();
	}

	void CGuildMainForm::OnGuildSearchInfo_ButtonInit(int param)
	{
		m_pButton[4] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[4]);
		Controller()->InsertPostAction(m_pButton[4], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildSearchInfo_LButtonUp()
	{
		m_searchName = m_pEdit[3]->GetLine(1, false);
		if (m_searchName.empty())
		{
			AfxGetTask()->SendMsgToMainActor(
				MsgObject(NULL, 35, (int)GuildMsg(1037), 0, 0, 0, 0));
			return;
		}
		if (m_searchName.length() < 4)
		{
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
				(int)MakeStr(
					"\\c0xffff0000\\c\xbf\xb5\xb9\xae %d\xb1\xdb\xc0\xda\\c0xff000000\\c \xb6\xc7\xb4\xc2 \\c0xffff0000\\c\xc7\xd1\xb1\xdb %d\xb1\xdb\xc0\xda\\c0xff000000\\c\xc0\xcc\xbb\xf3 \xc0\xd4\xb7\xc2\xc7\xcf\xbf\xa9\xbe\xdf \xc7\xd5\xb4\xcf\xb4\xd9.",
					4, 2),
				0, 0, 0, 0));
			return;
		}
		if (m_searchName.find("%%") == std::string::npos)
		{
			m_searchMode = 1;
			RequestSearch_Page(1);
		}
	}

	void CGuildMainForm::OnGuildJoinAbort_ButtonInit(int param)
	{
		m_pButton[6] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[6]);
		Controller()->InsertPostAction(m_pButton[6],
			FORM_INFO | FORM_MEMBER | FORM_SEARCH, AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildJoinAbort_LButtonUp()
	{
		m_authController[MyGuildClassIndex()]->OnGuildJoinAbort_LButtonUp();
	}

	void CGuildMainForm::OnGuildMemberTalk_ButtonInit(int param)
	{
		m_pButton[8] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[8]);
	}

	void CGuildMainForm::OnGuildMemberTalk_LButtonUp()
	{
		if (!m_pSelectedItem)
		{
			m_pSelectedItem = m_pListBox[0]->GetSelected();
			if (!m_pSelectedItem)
			{
				Close(FrCANCEL, true);
				return;
			}
		}
		sMemberItem* item = (sMemberItem*)m_pSelectedItem->pData;
		item->bEdit = false;
		bool sent = false;
		std::string text(m_pEdit[4]->GetLine(1, false));
		str_Replace(text, "'", "`");
		int result = Doc()->m_chatManager.FilteringGuildString(text.c_str(), 0,
			20, false);
		if (result != 1 && result > 0)
		{
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 35,
				(int)GuildInfo()->GuildMsg(result), 0, 0, 0, 0));
			return;
		}
		if (strcmp(item->pInfo->message, text.c_str()) != 0)
		{
			WSendPacket packet((enumClientPacket)270);
			packet.Encode4(GuildInfo()->GetMyGuildInfo().guildUID);
			packet.Encode4(item->pInfo->userUID);
			packet.EncodeStr(text);
			packet.Send(TO_GAME);
			sent = true;
		}
		FrWnd* control = m_pButton[8];
		control->SetVisible(false);
		control->Enable(false);
		control = m_pEdit[4];
		control->SetVisible(false);
		control->Enable(false);
		if (sent == true)
			AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
	}

	void CGuildMainForm::OnGuildSearchPrev_ButtonInit(int param)
	{
		m_pButton[9] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[9]);
		Controller()->InsertPostAction(m_pButton[9], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::VisibleWindow);
		m_pPageArrow->SetLeftArrow(m_pButton[9]);
	}

	void CGuildMainForm::OnGuildSearchPrev_LButtonUp()
	{
		RequestSearch_Page(((m_searchPage - 1U) / 5) * 5);
	}

	void CGuildMainForm::OnGuildSearchNext_ButtonInit(int param)
	{
		m_pButton[10] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[10]);
		Controller()->InsertPostAction(m_pButton[10], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::VisibleWindow);
		m_pPageArrow->SetRightArrow(m_pButton[10]);
	}

	void CGuildMainForm::OnGuildSearchNext_LButtonUp()
	{
		RequestSearch_Page(((m_searchPage - 1U) / 5) * 5 + 6);
	}

	void CGuildMainForm::OnGuildShutDown_ButtonInit(int param)
	{
		m_pButton[5] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[5]);
		Controller()->InsertPostAction(m_pButton[5],
			FORM_INFO | FORM_MEMBER | FORM_SEARCH, AUTH_MASTER,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildShutDown_LButtonUp()
	{
		m_authController[MyGuildClassIndex()]->OnGuildShutDown_LButtonUp();
	}

	void CGuildMainForm::OnGuildOut_ButtonInit(int param)
	{
		m_pButton[7] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		Controller()->InsertControl(m_pButton[7]);
		Controller()->InsertPostAction(m_pButton[7],
			FORM_INFO | FORM_MEMBER | FORM_SEARCH, AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildOut_LButtonUp()
	{
		m_authController[MyGuildClassIndex()]->OnGuildOut_LButtonUp();
	}

	void CGuildMainForm::OnGuildMemberInfo_ListBoxInit(int param)
	{
		m_pListBox[0] = DYNAMIC_CAST(FrListBox, (FrWnd*)param);
		Controller()->InsertControl(m_pListBox[0]);
		Controller()->InsertPostAction(m_pListBox[0], FORM_MEMBER,
			AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildMemberInfo_OwnerDraw(int param)
	{
		FrListItem* item = (FrListItem*)param;
		if (!item)
			return;
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		sMemberItem* member = (sMemberItem*)item->pData;
		if (item->selected == true)
			gdi->DrawTexture(m_pBitmap[14],
				WRect(item->pos.x + 1, item->pos.y,
					(float)m_pListBox[0]->GetItemWidth() + 2,
					(float)m_pListBox[0]->GetItemHeight()),
				0xffffffff, 0);
		const Bitmap* bitmap = NULL;
		switch (member->pInfo->classIdx)
		{
		case 1:
			bitmap = m_pBitmap[4];
			break;
		case 2:
			bitmap = m_pBitmap[5];
			break;
		case 3:
			bitmap = m_pBitmap[6];
			break;
		case 9:
			bitmap = m_pBitmap[7];
			break;
		default:
			return;
		}
		if (bitmap)
			gdi->DrawTexture(bitmap,
				WRect(item->pos.x + 20, item->pos.y + 7, (float)bitmap->Width(),
					(float)bitmap->Height()),
				0xffffffff, 0);
		bitmap = NULL;
		switch (member->pInfo->online)
		{
		case 0:
			bitmap = m_pBitmap[12];
			break;
		case 1:
			bitmap = m_pBitmap[11];
			break;
		}
		gdi->DrawTexture(bitmap,
			WRect(item->pos.x + 96, item->pos.y + 9, (float)bitmap->Width(),
				(float)bitmap->Height()),
			0xffffffff, 0);
		gdi->SetTextStyle(1);
		gdi->SetTextColor(0xff333333, 0xffffffff);
		gdi->Print(WPoint(item->pos.x + 120, item->pos.y + 9), 0,
			member->pInfo->nickname);
		gdi->SetTextColor(0xff376f90, 0xffffffff);
		m_authController[MyGuildClassIndex()]->DrawGuildTalk(item);
		gdi->SetTextStyle(0);
		gdi->SetTextColor(0, 0xffffffff);
	}

	void CGuildMainForm::OnGuildMemberInfo_LButtonDown()
	{
		FrListBox* list = m_pListBox[0];
		FrListItem* item = list->GetItemUnderCursor();
		if (!item)
		{
			if (m_pCmdMenu)
				m_pCmdMenu->SetVisible(false);
			return;
		}
		if (item)
		{
			SelectMemberItem(list, item);
			double y = item->pos.y;
			WRect rect(item->pos.x, y, 0.f, 0.f);
			CMouseCursor* cursor = CMouseCursor::Instance();
			// HACK: Workaround to preserve some stores that otherwise get eliminated
			_WriteBarrier();
			rect.w = list->GetRect().w * .5f;
			rect.h = (float)list->GetItemHeight();
			if (cursor->InArea(rect))
			{
				WVector mouse = g_input->GetMousePoint();
				PopupMemberCommand(mouse.x, mouse.y);
				return;
			}
			rect.x = m_talkButtonPosX + item->pos.x;
			if (CMouseCursor::Instance()->InArea(rect))
			{
				sMemberItem* member = (sMemberItem*)item->pData;
				if (CanExecuteClass(member->pInfo) && member->bEdit == false)
				{
					member->bEdit = true;
					CheckTalkState();
					return;
				}
				if (m_pCmdMenu->IsVisible())
					m_pCmdMenu->SetVisible(false);
			}
			else
				m_pCmdMenu->SetVisible(false);
		}
	}

	void CGuildMainForm::OnMemberPage_ListBoxInit(int param)
	{
		m_pListBox[2] = DYNAMIC_CAST(FrListBox, (FrWnd*)param);
		Controller()->InsertControl(m_pListBox[2]);
		Controller()->InsertPostAction(m_pListBox[2], FORM_MEMBER,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
		m_pListBox[2]->EnableScrollBar(false);
	}

	void CGuildMainForm::OnMemberPage_ListOwnerDraw(int param)
	{
		FrListItem* item = (FrListItem*)param;
		if (item)
		{
			static char text[8];
			_itoa(item->idx + 1, text, 10);
			if (m_memberPage == item->idx + 1)
				m_pOverFont->Print(g_view, item->pos.x, item->pos.y, text, 0,
					0xffffffff, NULL);
			else
				m_pNormalFont->Print(g_view, item->pos.x, item->pos.y, text, 0,
					0xffffffff, NULL);
		}
	}

	void CGuildMainForm::OnMemberPage_ListLButtonDown()
	{
		FrListItem* item = m_pListBox[2]->GetSelected();
		if (item)
		{
			int page = item->idx + 1;
			if (page != m_memberPage)
			{
				m_memberPage = page;
				RequestMember_Page(page);
			}
		}
	}

	void CGuildMainForm::OnGuildSearchInfo_ListBoxInit(int param)
	{
		m_pListBox[1] = DYNAMIC_CAST(FrListBox, (FrWnd*)param);
		Controller()->InsertControl(m_pListBox[1]);
		Controller()->InsertPostAction(m_pListBox[1], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildSearchInfo_OwnerDraw(int param)
	{
		FrListItem* item = (FrListItem*)param;
		if (!item)
			return;
		FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
		const GUILD_LIST* info = (const GUILD_LIST*)item->pData;
		if (item->selected == true)
			gdi->DrawTexture(m_pBitmap[14],
				WRect(item->pos.x, item->pos.y,
					(float)m_pListBox[1]->GetItemWidth(),
					(float)m_pListBox[1]->GetItemHeight()),
				0xffffffff, 0);
		gdi->SetTextStyle(1);
		gdi->SetTextColor(0xff333333, 0xffffffff);
		gdi->Print(WPoint(item->pos.x + 38, item->pos.y + 10), 0,
			info->guildName);
		gdi->SetTextStyle(0);
		gdi->SetTextColor(0, 0xffffffff);
	}

	void CGuildMainForm::OnGuildSearchInfo_LButtonDown()
	{
		FrListItem* item = m_pListBox[1]->GetSelected();
		if (!item)
		{
			memset(&m_selectGuild, 0, sizeof(m_selectGuild));
			m_pEdit[0]->ClearLine();
			return;
		}
		if (item)
		{
			const GUILD_LIST* info = (const GUILD_LIST*)item->pData;
			if (m_selectGuild.guildUID != info->guildUID)
			{
				m_selectGuild = *info;
				m_pEdit[0]->ClearLine();
				m_pEdit[0]->AddText(m_selectGuild.introduce, false, true);
				m_pEdit[0]->GetScrollBar()->ScrollToFirst();
			}
		}
	}

	void CGuildMainForm::OnGuildSearchPage_ListBoxInit(int param)
	{
		m_pListBox[3] = DYNAMIC_CAST(FrListBox, (FrWnd*)param);
		Controller()->InsertControl(m_pListBox[3]);
		Controller()->InsertPostAction(m_pListBox[3], FORM_SEARCH,
			AUTH_NONE | AUTH_MASTER | AUTH_SUBMASTER | AUTH_MEMBER | AUTH_WAIT,
			&CGuildFormController::EnableWindow);
	}

	void CGuildMainForm::OnGuildSearchPage_OwnerDraw(int param)
	{
		FrListItem* item = (FrListItem*)param;
		if (!item)
			return;
		static char text[8];
		memset(text, 0, sizeof(text));
		int page = (int)item->pData + 1;
		_itoa(page, text, 10);
		if (m_searchPage == page)
			m_pOverFont->Print(g_view, item->pos.x, item->pos.y, text, 0,
				0xffffffff, NULL);
		else
			m_pNormalFont->Print(g_view, item->pos.x, item->pos.y, text, 0,
				0xffffffff, NULL);
	}

	void CGuildMainForm::OnGuildSearchPage_LButtonDown()
	{
		FrListItem* item = m_pListBox[3]->GetSelected();
		if (!item)
			return;
		int page = (int)item->pData + 1;
		if (page != m_searchPage)
		{
			m_searchPage = page;
			RequestSearch_Page(page);
		}
	}

	void CGuildMainForm::OnGuildManagerCmd_ContextInit(int param)
	{
		m_pCmdMenu = (FrContextMenuCtrl*)DYNAMIC_CAST(FrWnd, (FrWnd*)param);
		if (!m_pCmdMenu)
			return;
		m_pCmdMenu->SetVisible(false);
		m_pCmdMenu->SetFixed(true);
	}

	void CGuildMainForm::OnGuildManagerCmd_LButtonDown()
	{
		const char* command = m_pCmdMenu->GetSelectMenuText();
		m_pCmdMenu->SetVisible(false);
		ProcManagerCommand(command);
	}

	void CGuildMainForm::OnGuildManagerCmd_LButtonUp()
	{
		m_pCmdMenu->SetVisible(false);
	}

	IMPLEMENT_OBJECT(FrGuildJoin, FrForm)
	BEGIN_FRESH_MSGMAP(FrGuildJoin, FrForm)
	ON_FRESH_VI("request_paper", FRCMD_INIT, FrGuildJoin::OnGuildJoin_AreaInit)
	ON_FRESH_VI("request_paper", FRCMD_OWNERDRAW,
		FrGuildJoin::OnGuildJoin_AreaOwnerDraw)
	ON_FRESH_VI("story", FRCMD_INIT, FrGuildJoin::OnJoin_EditInit)
	ON_FRESH_VI("request_join", FRCMD_INIT,
		FrGuildJoin::OnRequestJoin_ButtonInit)
	ON_FRESH_VV("request_join", FRCMD_LBUTTONUP,
		FrGuildJoin::OnRequestJoin_LButtonUp)
	ON_FRESH_VI("request_ok", FRCMD_INIT, FrGuildJoin::OnRequestOK_ButtonInit)
	ON_FRESH_VV("request_ok", FRCMD_LBUTTONUP,
		FrGuildJoin::OnRequestOK_LButtonUp)
	ON_FRESH_VI("form_close", FRCMD_INIT, FrGuildJoin::OnFormClose_ButtonInit)
	ON_FRESH_VV("form_close", FRCMD_LBUTTONUP,
		FrGuildJoin::OnFormClose_LButtonUp)
	END_FRESH_MSGMAP()

	FrGuildJoin::FrGuildJoin()
		: m_pPaperArea(NULL),
		  m_pStoryEdit(NULL),
		  m_pPaperBg(NULL),
		  m_guildNumber(0),
		  m_bSuccess(false)
	{
		memset(m_pButton, 0, sizeof(m_pButton));
	}

	FrGuildJoin::~FrGuildJoin()
	{
	}

	bool FrGuildJoin::OnInit()
	{
		m_pPaperBg = g_pFresh->RegisterBitmap("guild_popup_write_bg");
		return FrForm::OnInit();
	}

	void FrGuildJoin::SetGuildNumber(int number)
	{
		m_guildNumber = number;
	}

	void FrGuildJoin::SetSuccessRequest()
	{
		m_bSuccess = true;
		m_pStoryEdit->SetReadOnly(true);
		m_pStoryEdit->ClearLine();
		m_pStoryEdit->SetFontColor(0xff33365f);
		m_pStoryEdit->AddText(
			"\xb0\xa1\xc0\xd4 \xbd\xc5\xc3\xbb\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
			false, true);
		FrButton* button = m_pButton[0];
		button->SetVisible(false);
		button->Enable(false);
		button = m_pButton[1];
		button->SetVisible(true);
		button->Enable(true);
	}

	void FrGuildJoin::OnGuildJoin_AreaInit(int param)
	{
		m_pPaperArea = DYNAMIC_CAST(FrArea, (FrWnd*)param);
	}

	void FrGuildJoin::OnGuildJoin_AreaOwnerDraw(int param)
	{
		if (m_bSuccess == true)
			return;
		g_pFresh->GetManager()->GetGDI()->DrawTexture(m_pPaperBg,
			WRect(GetRect().x + 33, GetRect().y - 20, m_pPaperBg->Width(),
				m_pPaperBg->Height()),
			0xffffffff, 0);
	}

	void FrGuildJoin::OnJoin_EditInit(int param)
	{
		m_pStoryEdit = DYNAMIC_CAST(FrEdit, (FrWnd*)param);
	}

	void FrGuildJoin::OnRequestJoin_ButtonInit(int param)
	{
		m_pButton[0] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void FrGuildJoin::OnRequestJoin_LButtonUp()
	{
		if (!m_pStoryEdit)
			return;
		std::string story;
		int line = 1;
		int lines = m_pStoryEdit->GetLineNum();
		for (; line <= lines; ++line)
			story += m_pStoryEdit->GetLine(line, false);
		if (story.empty())
			return static_cast<void>(AfxGetTask()->GetActor(s_guildActor[1])
				<< MsgObject(NULL, 611, 26, 1014, 0, 0, 0));
		WSendPacket packet((enumClientPacket)265);
		packet.Encode4(m_guildNumber);
		packet.EncodeStr(story);
		packet.Send(TO_GAME);
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
	}

	void FrGuildJoin::OnRequestOK_ButtonInit(int param)
	{
		m_pButton[1] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
		FrButton* button = m_pButton[1];
		if (!button)
			return;
		button->SetVisible(false);
		button->Enable(false);
	}

	void FrGuildJoin::OnRequestOK_LButtonUp()
	{
		Close(FrOK, true);
	}

	void FrGuildJoin::OnFormClose_ButtonInit(int param)
	{
		m_pButton[2] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	}

	void FrGuildJoin::OnFormClose_LButtonUp()
	{
		Close(FrNO, true);
	}
}
