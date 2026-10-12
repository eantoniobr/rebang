#pragma once

#include <list>
#include <string>
#include "frform.h"
#include "frienddlg.h"
#include "standinginline.h"
#include "../../shared/globalnetworkdefine.h"

class FrEmoticonDlg;
class FrArea;
class FrEdit;
class FrButton;
class FrListBox;
struct FrListItem;
class FrGraphicInterface;
class WTitleFont;
class Bitmap;
class CStandingInLine;
class CPost_MyItemList;
class CPost_ItemCountDlg;

class CPost_SendDlg : public FrForm
{
	friend class FrFriendDlg;

public:
	DECLARE_OBJECT(CPost_SendDlg)

	CPost_SendDlg();
	virtual ~CPost_SendDlg();

	void Reset();
	void SetReceiverInfo(unsigned long uid, const sPangYaUserInfo& info);
	void UpdateFriendList()
	{
		if (m_pFriendDlg)
			m_pFriendDlg->UpdateFriendList();
	}

	std::string GetLetterMsg();
	int GetSendListSize();
	std::list<sMailIncludeItem>* GetSendList();
	int GetSendServiceCharge();
	bool VerifySendItemList();
	unsigned long GetSendUID() { return m_receiverUid; }
	bool VerifyIncludeSameItem();

	bool OnSendQuestionResult(int result, FrForm* form);
	bool OnFriendListResult(int result, FrForm* form);
	bool OnPostItemListResutl(int result, FrForm* form);
	bool OnEmoticonResult(int result, FrForm* form);

protected:
	virtual void OnOK();
	virtual void OnCancel();

	void OnPostReciveUserInit(int param);
	bool OnPostReceiveUserEnterKey(int param);
	void OnPostReciveMsgInit(int param);
	bool OnPostReciveMsgEnterKey(int param);
	void OnPostUserNickInit(int param);
	void OnPostSearchUserInit(int param);
	void OnPostSearchUserBtnUp();
	void OnPostFriendListInit(int param);
	void OnPostFriendListBtnUp();
	void OnPostItemAddInit(int param);
	void OnPostItemAddBtnUp();
	void OnPostListInit(int param);
	void OnPostListOwnerDraw(int param);
	void OnPostServiceChargeInit(int param);
	void OnEmoticonBtnInit(int param);
	void OnEmoticonBtnUp();

	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);

	FrFriendDlg* m_pFriendDlg;
	FrButton* m_pFriendList;
	FrButton* m_pEmoticonBtn;
	FrButton* m_pItemAdd;
	FrEmoticonDlg* m_pEmoticonDlg;
	CPost_MyItemList* m_pMyItemList;
	FrListBox* m_pPostList;
	FrEdit* m_pServiceCharge;
	std::string m_receiverNick;
	std::string m_receiverId;
	unsigned long m_receiverUid;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	WTitleFont* m_pTitleFont;
	FrEdit* m_pUserNick;
	FrEdit* m_pReciveUser;
	FrEdit* m_pReciveMsg;
	FrButton* m_pSearchUser;
	bool m_bReceiverChecked;
	std::list<sTradeItem> m_tradeItemList;
	std::list<sMailIncludeItem> m_sendList;

	DECLARE_FRESH_MSGMAP()
};

class CPost_MyItemList : public FrForm
{
public:
	DECLARE_OBJECT(CPost_MyItemList)

	CPost_MyItemList();
	virtual ~CPost_MyItemList();

	struct miniBtn_t
	{
		WRect rect;
		const Bitmap* pNormal;
		const Bitmap* pOver;
		bool bEnable;
	};

	void SetParent(CPost_SendDlg* pParent);
	void DrawItem(WPoint pos, sTradeItem* pItem, unsigned char state);
	void DrawPang();

	void OnPost_ItemListInit(int param);
	void OnPost_ItemListOwnerDraw(int param);
	void OnPost_ItemListBtnDown();
	void OnPost_ItemListRBtnDown();
	void OnPost_ItemListMouseMove();
	void OnPost_ItemListDClick();
	void OnPost_ImgSelect(int param);
	void OnPost_SelectListInit(int param);
	void OnPost_SelectListOwnerDraw(int param);
	void OnPost_SelectListBtnDown();
	void OnPost_SelectListMouseMove();
	void OnPost_SelectListDClick();
	void OnPost_EditArrayInit(int param);
	void OnPostBtnArrayInit(int param);
	void OnPostBtnArrayButtonUp();

	bool OnPostItemCountResult(int result, FrForm* form);
	bool OnPostItemArrayResult(int result, FrForm* form);

protected:
	virtual bool OnInit();
	virtual void OnOK();

	void SetList();
	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);

	FrListBox* m_pItemList;
	FrListBox* m_pSelectList;
	FrArea* m_pImgSelect;
	FrListItem* m_pCountItem;
	FrButton* m_pBtnArray;
	FrEdit* m_pEditArray;
	CPost_SendDlg* m_pParent;
	WTitleFont* m_pTitleFont;
	WTitleFont* m_pPangFont;
	const Bitmap* m_pSelectN;
	const Bitmap* m_pSelectD;
	const Bitmap* m_pLine;
	int m_count;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	CPost_ItemCountDlg* m_pItemCountDlg;
	CStandingInLine* m_pArrayDlg;
	miniBtn_t m_cancelBtn;
	int m_arrayType;

	DECLARE_FRESH_MSGMAP()
};

class CPost_ItemCountDlg : public FrForm
{
public:
	DECLARE_OBJECT(CPost_ItemCountDlg)

	CPost_ItemCountDlg();
	virtual ~CPost_ItemCountDlg();

	void SetSelectItem(unsigned long item, int maxCount);
	unsigned long GetSelectItem();
	int GetCount();

	void OnPostMinusInit(int param);
	void OnPostMinusBtnUp();
	void OnPostPluseInit(int param);
	void OnPostPluseBtnUp();
	void OnPostEditItemCountInit(int param);
	bool OnPostEditItemCountEnterKey(int param);

protected:
	void SetText();

	FrButton* m_pMinus;
	FrButton* m_pPluse;
	FrEdit* m_pEditItemCount;
	int m_count;
	int m_maxCount;
	unsigned long m_selectItem;

	DECLARE_FRESH_MSGMAP()
};
