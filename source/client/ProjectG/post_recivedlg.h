#pragma once

#include <list>
#include "frform.h"
#include "../../shared/globalnetworkdefine.h"
#include "tooltipmanager.h"
#include "mailboxpage.h"

class CPost_Contents;
class FrButton;
class FrListBox;
class FrArea;
class FrEdit;
struct FrListItem;
class FrGraphicInterface;
class Bitmap;
class WTitleFont;
struct sGiftInfo;
struct sMailInfo;
struct sMailInfoBrief;
struct sMailIncludeItem;

class CPost_ReciveDlg : public FrForm
{
public:
	DECLARE_OBJECT(CPost_ReciveDlg)

	CPost_ReciveDlg();
	virtual ~CPost_ReciveDlg();

	void OnReset();
	void OnLoadPostList();
	void SetLoadPostList();
	void SetLoadPostList(std::list<sMailInfoBrief>* pList);
	void BuildIndexPage(int page);
	void EnableMiniBtns(bool bEnable);
	void Question(int type);
	void ToServerSendData(FrListItem* pItem, unsigned long packet);
	void OnPostDescDlgCreate();
	int GetItemNumInMyPocket(unsigned long typeId);

	bool OnPostMessageResult(int result, FrForm* form);
	bool OnPostQuestionResult(int result, FrForm* form);
	bool OnDeleteAllLetterResult(int result, FrForm* form);
	bool OnReturnGiftDlgResult(int result, FrForm* form);
	bool OnMoveGiftDlgResult(int result, FrForm* form);

protected:
	struct miniBtn_t
	{
		miniBtn_t() { }
		WRect rect;
		const Bitmap* pNormal;
		const Bitmap* pOver;
		bool bEnable;
	};

	void OnRecivePostInit(int param);
	void OnRecivePostBtnUp();
	void OnSendPostInit(int param);
	void OnSendPostBtnUp();
	void OnDeleteAllLetterInit(int param);
	void OnDeleteAllLetterBtnUp();
	void OnWriteLetterInit(int param);
	void OnWriteLetterBtnUp();
	void OnPageListInit(int param);
	void OnPageListOwnerDraw(int param);
	void OnPageListBtnDown();
	void OnPostListInit(int param);
	void OnPostListOwnerDraw(int param);
	void OnPostListBtnDown();
	void OnPostListRBtnDown();
	void OnPostListMouseMove();
	void OnPostListDClick();
	void OnPageDownInit(int param);
	void OnPageDownBtnUp();
	void OnPageUpInit(int param);
	void OnPageUpBtnUp();
	bool OnEditPageEndterKey(int param);
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);
	void OnIndexAreaInit(int param);
	void OnIndexAreaOwnerDraw();
	void OnIndexListInit(int param);
	void OnIndexListLBDown();
	void OnIndexListMouseMove();

	void OnLoadImage();
	void OnDeleteItem(FrListItem* pItem);
	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);
	void DrawStatus2(FrGraphicInterface* pGI, FrListItem* pItem, short* const x,
		short* const y, float alpha);
	const char* MakeStatusString(int a, int b, int c);

	FrButton* m_pRecivePost;
	FrButton* m_pSendPost;
	FrButton* m_pDeleteAllLetter;
	FrButton* m_pWriteLetter;
	FrListBox* m_pPostList;
	FrListBox* m_pPageList;
	unsigned char m_unknown128[8];
	FrButton* m_pPageDown;
	FrButton* m_pPageUp;
	unsigned char m_unknown138[4];
	FrArea* m_pToolTip;
	miniBtn_t m_miniBtn[2];
	const Bitmap* m_pItemBaseN;
	const Bitmap* m_pItemBaseO;
	const Bitmap* m_pItemBaseD;
	const Bitmap* m_pItemBaseEmpty;
	const Bitmap* m_pArrivalMail;
	const Bitmap* m_pOpenMail;
	CToolTipManager m_toolTipMng;
	sGiftInfo* m_pMoveGift;
	unsigned char m_unknown1a4[4];
	int m_requestPage;
	sMailBoxListForPage m_mailList;
	CPost_Contents* m_pContents;
	int m_totalPage;
	int m_curPage;
	int m_pageStep;
	FrListItem* m_pSelectItem;
	int m_questionType;
	WTitleFont* m_pTitleFont;
	unsigned char m_unknown1e0[4];
	FrArea* m_pIndexArea;
	FrListBox* m_pIndexList;
	int m_indexPageNum;
	int m_curIndexPage;
	unsigned char m_selIndex;
	unsigned char m_overIndex;
	unsigned char m_indexNum;
	WRect* m_pIndexRect;
	int m_lastSelRow;

	DECLARE_FRESH_MSGMAP()
};

class CPost_Contents : public FrForm
{
public:
	DECLARE_OBJECT(CPost_Contents)

	CPost_Contents();
	virtual ~CPost_Contents();

	void SetData(sMailInfo* pInfo);
	void SetData(std::list<sMailIncludeItem>* pList);

	void OnPostMessage_ReciveUserInit(int param);
	void OnPostMessage_SendUserInit(int param);
	void OnPostMessage_LetterContentsInit(int param);
	void OnPostMessage_LetterDateInit(int param);
	void OnPostListInit(int param);
	void OnPostListOwnerDraw(int param);
	void OnPostListBtnDown();
	void OnPostListRBtnDown();
	void OnPostListMouseMove();
	void OnPostListDClick();

protected:
	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);

	FrEdit* m_pSendUser;
	FrEdit* m_pReciveUser;
	FrEdit* m_pLetterContents;
	FrEdit* m_pLetterDate;
	FrListBox* m_pPostList;
	WTitleFont* m_pTitleFont;
	unsigned char m_unknown128[8];

	DECLARE_FRESH_MSGMAP()
};

class CPost_MessgeDlg : public FrForm
{
public:
	DECLARE_OBJECT(CPost_MessgeDlg)

	CPost_MessgeDlg();
	virtual ~CPost_MessgeDlg();

	void OnPostMessage_ReciveUserInit(int param);
	void OnPostMessage_LetterContentsInit(int param);
	void OnPostMessage_LetterDateInit(int param);
	void OnPostDescFrame(bool bShow);
	void SetGiftDescString(const char* item, const char* contents,
		const char* sender, const char* date);

protected:
	virtual void OnOK();

	unsigned char m_unknown110[0x18];
	FrEdit* m_pReciveUser;
	FrEdit* m_pLetterContents;
	FrEdit* m_pLetterDate;

	DECLARE_FRESH_MSGMAP()
};
