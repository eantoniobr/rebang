#pragma once

#include <list>
#include <map>
#include <string>
#include "frform.h"
#include "../../shared/globalgamedefine.h"
#include "wtemplate.h"

class WTitleFont;
class FrButton;
class FrArea;
class FrEdit;
class FrListBox;
class FrContextMenuCtrl;
struct FrListItem;

namespace _guild
{
	enum eFormStyle;
	enum eAuthority;
	class CGuildInfo;
	class CGuildFormController;
	class CPageArrow;
	class IGuildAuthController;

	class CGuildMainForm : public FrForm
	{
	public:
		DECLARE_OBJECT(CGuildMainForm)

		CGuildMainForm();
		virtual ~CGuildMainForm();

		virtual bool OnInit();
		virtual void OnProc(const float delta);
		void Refresh();
		void RefreshMyGuildInfo();
		void RefreshMyGuildHistory();
		void RefreshGuildMember();
		void RefreshGuildSearch();
		void RefreshMemberPageList();
		void RefreshSearchPageList();
		void RequestMember_Page(int page);
		void RequestSearch_Page(int page);
		void RequestChangeClass(GUILD_CLASS_IDX classIdx);
		void ClearForm();
		void DisableJoinButton();
		void InitSearchMode();
		void LockScrollMemberList();
		void UnLockScrollMemberList();

	protected:
		void OnGuildInfo_ButtonInit(int param);
		void OnGuildInfo_LButtonUp();
		void OnGuildMember_ButtonInit(int param);
		void OnGuildMember_LButtonUp();
		void OnGuildSearch_ButtonInit(int param);
		void OnGuildSearch_LButtonUp();
		void OnGuildDetail_AreaInit(int param);
		void OnGuildDetail_OwnerDraw(int param);
		void OnGuildIntroduce_AreaInit(int param);
		void OnGuildNotice_AreaInit(int param);
		void OnGuildAct_AreaInit(int param);
		void OnEmptyGuild_AreaInit(int param);
		void OnEmptyGuild_AreaOwnerDraw(int param);
		void OnGuildMemberInfoBg_AreaInit(int param);
		void OnGuildMemberInfoBg_OwnerDraw(int param);
		void OnSearchBg1_AreaInit(int param);
		void OnSearchBg2_AreaInit(int param);
		void OnGuildIntroduce_EditInit(int param);
		void OnGuildNotice_EditInit(int param);
		void OnGuildAct_EditInit(int param);
		void OnGuildSearch_EditInit(int param);
		void OnGuildSearch_EnterKey(int param);
		void OnGuildMemberTalk_EditInit(int param);
		void OnGuildForm_CloseInit(int param);
		void OnGuildForm_CloseLButtonUp();
		void OnGuildIntroConfirm_ButtonInit(int param);
		void OnGuildIntroConfirm_LButtonUp();
		void OnGuildNoticeConfirm_ButtonInit(int param);
		void OnGuildNoticeConfirm_LButtonUp();
		void OnGuildJoin_ButtonInit(int param);
		void OnGuildJoin_LButtonUp();
		void OnGuildSearchInfo_ButtonInit(int param);
		void OnGuildSearchInfo_LButtonUp();
		void OnGuildJoinAbort_ButtonInit(int param);
		void OnGuildJoinAbort_LButtonUp();
		void OnGuildMemberTalk_ButtonInit(int param);
		void OnGuildMemberTalk_LButtonUp();
		void OnGuildSearchPrev_ButtonInit(int param);
		void OnGuildSearchPrev_LButtonUp();
		void OnGuildSearchNext_ButtonInit(int param);
		void OnGuildSearchNext_LButtonUp();
		void OnGuildShutDown_ButtonInit(int param);
		void OnGuildShutDown_LButtonUp();
		void OnGuildOut_ButtonInit(int param);
		void OnGuildOut_LButtonUp();
		void OnGuildMemberInfo_ListBoxInit(int param);
		void OnGuildMemberInfo_OwnerDraw(int param);
		void OnGuildMemberInfo_LButtonDown();
		void OnMemberPage_ListBoxInit(int param);
		void OnMemberPage_ListOwnerDraw(int param);
		void OnMemberPage_ListLButtonDown();
		void OnGuildSearchInfo_ListBoxInit(int param);
		void OnGuildSearchInfo_OwnerDraw(int param);
		void OnGuildSearchInfo_LButtonDown();
		void OnGuildSearchPage_ListBoxInit(int param);
		void OnGuildSearchPage_OwnerDraw(int param);
		void OnGuildSearchPage_LButtonDown();
		void OnGuildManagerCmd_ContextInit(int param);
		void OnGuildManagerCmd_LButtonDown();
		void OnGuildManagerCmd_LButtonUp();

	public:
		struct sMemberItem
		{
			const GUILD_USER_LIST* pInfo;
			bool bEdit;

			sMemberItem()
			{
				pInfo = NULL;
				bEdit = false;
			}
		};

	public:
		typedef std::list<sMemberItem>::iterator MemberIterator;
		typedef std::list<const GUILD_LIST*>::iterator SearchIterator;

		void SetLinkGuildInfo(CGuildInfo* pInfo) { m_pGuildInfo = pInfo; }
		void SetCommandUserInfo(const GUILD_USER_LIST* pInfo)
		{
			m_pCommandUser = pInfo;
		}
		void ClearCommandUserInfo() { m_pCommandUser = NULL; }

	private:
		void InitControl();
		void LoadResource();
		void CreateAuthController();

		void PopupMemberCommand(float x, float y);
		void SelectMemberItem(FrListBox* pListBox, FrListItem* pItem);
		void ProcManagerCommand(const char* command);
		void CheckTalkState();
		void EnableAuthCommand(GUILD_CLASS_IDX classIdx);
		void ResetEditState(void* pData);
		void UnSelectMember();

		eAuthority ConvertGuildClass();
		bool CanExecuteClass(const GUILD_USER_LIST* pInfo);
		const char* GuildMsg(int index);
		GUILD_CLASS_IDX MyGuildClassIndex();

		CGuildInfo* GuildInfo() { return m_pGuildInfo; }
		CGuildFormController* Controller() { return m_pController; }

	public:
		FrButton* m_pTabButton[3];
		FrButton* m_pButton[11];
		FrArea* m_pArea[8];
		FrEdit* m_pEdit[5];
		FrListBox* m_pListBox[4];
		FrContextMenuCtrl* m_pCmdMenu;
		FrListItem* m_pSelectedItem;
		const Bitmap* m_pBitmap[17];
		WTitleFont* m_pNormalFont;
		WTitleFont* m_pOverFont;
		eFormStyle m_formStyle;
		CGuildFormController* m_pController;
		CGuildInfo* m_pGuildInfo;
		GUILD_LIST m_selectGuild;
		std::map<GUILD_CLASS_IDX, IGuildAuthController*> m_authController;
		float m_talkEditPosX;
		float m_talkButtonPosX;
		std::list<sMemberItem> m_memberList;
		CPageArrow* m_pPageArrow;
		const GUILD_USER_LIST* m_pCommandUser;
		std::list<const GUILD_LIST*> m_searchList;
		int m_memberPage;
		int m_searchPage;
		int m_searchMode;
		std::string m_searchName;

	private:
		DECLARE_FRESH_MSGMAP()
	};

	class FrGuildJoin : public FrForm
	{
	public:
		DECLARE_OBJECT(FrGuildJoin)

		FrGuildJoin();
		virtual ~FrGuildJoin();

		virtual bool OnInit();

		void SetGuildNumber(int number);
		void SetSuccessRequest();

	protected:
		void OnGuildJoin_AreaInit(int param);
		void OnGuildJoin_AreaOwnerDraw(int param);
		void OnJoin_EditInit(int param);
		void OnRequestJoin_ButtonInit(int param);
		void OnRequestJoin_LButtonUp();
		void OnRequestOK_ButtonInit(int param);
		void OnRequestOK_LButtonUp();
		void OnFormClose_ButtonInit(int param);
		void OnFormClose_LButtonUp();

		FrArea* m_pPaperArea;
		FrEdit* m_pStoryEdit;
		FrButton* m_pButton[3];
		const Bitmap* m_pPaperBg;
		int m_guildNumber;
		bool m_bSuccess;

	private:
		DECLARE_FRESH_MSGMAP()
	};

}
