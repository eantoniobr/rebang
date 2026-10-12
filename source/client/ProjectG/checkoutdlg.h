#pragma once

#include <list>
#include <map>
#include "frform.h"
#include "../../shared/classdefine.h"
#include "../../shared/globalgamedefine.h"

class FrButton;
class FrEdit;
class FrStatic;
class FrListBox;
class FrComboBox;
class Bitmap;
struct days_t
{
	const char* text;
	int days;
};

class FrCheckoutDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrCheckoutDlg)
	struct sDaysCombo;
	struct CartItem
	{
		const IFF_ITEM_COMMON* pItem;
		int ownedNum;
		unsigned long reserved;
		int period;
		sDaysCombo* pDaysCombo;
	};

	struct sDaysCombo
	{
		FrComboBox* pCombo;
		CartItem* pItem;
		bool bRebuild;
	};

	struct sCoupon
	{
		unsigned long reserved[2];
		bool bUsable;
		int period;
	};

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	FrCheckoutDlg();
	std::list<CartItem>& Cart();
	void Checkout(__int64 pang, __int64 cookie, bool bRental);
	void Process();

	bool IsUnderLevel() { return m_bUnderLevel; }
	bool IsOverLevel() { return m_bOverLevel; }

protected:
	struct sChildOption
	{
		char text[32];
		bool bCookie;
		__int64 numPrice;
		unsigned char numType;
		unsigned short num;
		unsigned long periodPrice;
		unsigned char periodType;
		unsigned short period;
	};

	void RecalculateTotalCookie(__int64 pang, __int64 cookie, bool bUpdate);
	void FixCartItem(CartItem& item);
	void SetPrice(int num);
	bool OnChargeResult(int result, FrForm* form);
	bool OnConfirmResult(int result, FrForm* form);
	unsigned long GetGuidSelectedCoupon();
	void OpenCaddieInfo(const sCaddieInfo& info);

	void OnCheckoutInit(int param);
	void OnCheckoutLBtnUp();
	void OnDaysInit(int param);
	void OnDays2Init(int param);
	void OnDaysBtnDown();
	void OnDays2BtnDown();
	void OnCartInit(int param);
	void OnCartOwnerDraw(int param);
	void OnPriceInit(int param);
	void OnMyMoneyInit(int param);
	void OnMoneyLeftInit(int param);
	void OnPrice_CookieInit(int param);
	void OnMyMoney_CookieInit(int param);
	void OnMoneyLeft_CookieInit(int param);
	void OnNumStaticInit(int param);
	void OnExplaneStaticInit(int param);
	void OnNumInit(int param);
	bool OnNumEnterKey(int param);
	void OnNumPrevInit(int param);
	void OnNumPrevLBtnUp();
	void OnNumNextInit(int param);
	void OnNumNextLBtnUp();

	FrButton* m_pCheckout;
	FrListBox* m_pCart;
	FrEdit* m_pPrice;
	FrEdit* m_pMyMoney;
	FrEdit* m_pMoneyLeft;
	FrEdit* m_pPrice_Cookie;
	FrEdit* m_pMyMoney_Cookie;
	FrEdit* m_pMoneyLeft_Cookie;
	FrStatic* m_pNumStatic;
	FrStatic* m_pExplaneStatic;
	FrEdit* m_pNum;
	FrButton* m_pNumPrev;
	FrButton* m_pNumNext;
	sDaysCombo m_daysCombo[2];
	std::list<CartItem> m_cart;
	bool m_bUnderLevel;
	bool m_bOverLevel;
	bool m_bOwned;
	bool m_bRental;
	__int64 m_totalPang;
	__int64 m_totalCookie;
	bool m_bEnoughPang;
	bool m_bEnoughCookie;
	int m_confirmType;
	int m_num;
	__int64 m_myPang;
	__int64 m_myCookie;
	__int64 m_remainCash;
	bool m_bShowCash;
	std::map<unsigned int, sCoupon> m_coupons;
	bool m_bCouponEnable;
	int m_selectedCoupon;
	int m_reserved1c0;
	__int64 m_discountPang;
	__int64 m_discountCookie;
	int m_reserved1d8;
	bool m_bSubmitted;
	MiniBtn m_miniBtn[7];
	int m_childOptionNum;
	sChildOption m_childOption[5];

	DECLARE_FRESH_MSGMAP()
};
