#pragma once

#include "frform.h"
#include "frienddlg.h"
#include "../../shared/classdefine.h"
#include <string>

class FrFriendDlg;
class FrEmoticonDlg;
class FrComboBox;
struct sPangYaUserInfo;

class FrGiftDlg : public FrForm
{
	friend class FrFriendDlg;
	DECLARE_OBJECT(FrGiftDlg)

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* bitmap;
		int index;
	};

	FrGiftDlg();
	void SetReceiverInfo(unsigned long uid, const sPangYaUserInfo& info);
	void SendGift(const IFF_ITEM_COMMON& item, __int64 pang, __int64 cash);
	void GiftProgress();
	void UpdateFriendList()
	{
		if (m_pFriendForm)
			m_pFriendForm->UpdateFriendList();
	}

protected:
	bool OnFriendListResult(int, FrForm*);
	bool OnEdIdEnterKey(int);
	void OnEdIdDown(void);
	void OnEdNickDown(void);
	void OnBtIdCheckUp(void);
	void OnCheckoutInit(int);
	void OnFriendBtnInit(int);
	void OnCartInit(int);
	void OnSxIdInit(int);
	void OnEdIdInit(int);
	void OnBtIdCheckInit(int);
	void OnSxNickInit(int);
	void OnEdNickInit(int);
	void OnMsgInit(int);
	void OnEdConfirmInit(int);
	void OnBtNickCheckInit(int);
	void OnPriceInit(int);
	void OnMyMoneyInit(int);
	void OnMoneyLeftInit(int);
	void OnPrice_CookieInit(int);
	void OnMyMoney_CookieInit(int);
	void OnMoneyLeft_CookieInit(int);
	void OnNumStaticInit(int);
	void OnNumInit(int);
	void OnNumPrevInit(int);
	void OnNumNextInit(int);
	void OnDaysInit(int);
	void OnWarnInit(int);
	void OnEmoticonBtnInit(int);
	void OnExplaneStaticInit(int);
	bool OnEmoticonResult(int, FrForm*);
	void SetPrice(int);
	void RecalculateTotalCookie(__int64, __int64, bool);
	bool OnChargeResult(int, FrForm*);
	void OnFriendBtnUp(void);
	void OnCartOwnerDraw(int);
	void OnBtNickCheckUp(void);
	void OnNumPrevBtnUp(void);
	void OnNumNextBtnUp(void);
	void OnDaysBtnDown(void);
	void OnEmoticonBtnUp(void);
	bool OnConfirmResult(int, FrForm*);
	void OnCheckoutBtnUp(void);
	bool OnEdNickEnterKey(int);
	bool OnMsgEnterKey(int);

	FrButton* m_pCheckout;
	FrButton* m_pFriendBtn;
	FrListBox* m_pCart;
	FrStatic* m_pSxId;
	FrEdit* m_pEdId;
	FrButton* m_pBtIdCheck;
	FrStatic* m_pSxNick;
	FrEdit* m_pEdNick;
	FrButton* m_pBtNickCheck;
	FrEdit* m_pEdConfirm;
	FrEdit* m_pMessage;
	FrEdit* m_pPrice;
	FrEdit* m_pMyMoney;
	FrEdit* m_pMoneyLeft;
	FrEdit* m_pPriceCookie;
	FrEdit* m_pMyMoneyCookie;
	FrEdit* m_pMoneyLeftCookie;
	FrStatic* m_pNumStatic;
	FrEdit* m_pNum;
	FrButton* m_pNumPrev;
	FrButton* m_pNumNext;
	FrStatic* m_pWarn;
	FrStatic* m_pExplane;
	FrButton* m_pEmoticonBtn;
	FrEmoticonDlg* m_pEmoticonForm;
	FrComboBox* m_pDays;
	int m_periodIndex;
	bool m_rebuildDays;
	IFF_ITEM_COMMON m_item;
	__int64 m_totalPang;
	__int64 m_totalCookie;
	std::string m_receiver;
	unsigned long m_receiverUid;
	bool m_enoughPang;
	bool m_enoughCookie;
	FrFriendDlg* m_pFriendForm;
	__int64 m_initialPang;
	__int64 m_initialCookie;
	__int64 m_remainingCash;
	bool m_showCashInfo;
	MiniBtn m_miniBtn[7];
	int m_childCount;
	struct ChildOption
	{
		char label[32];
		bool currency;
		__int64 quantityPrice;
		unsigned char quantityMode;
		unsigned short quantity;
		unsigned long durationPrice;
		unsigned char durationMode;
		unsigned short duration;
	};
	ChildOption m_childOptions[5];
	std::string m_packetText;
	int m_receiverMode;
	DECLARE_FRESH_MSGMAP()
};
