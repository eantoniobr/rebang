#pragma once

#include <string>
#include <list>
#include "../../shared/globalnetworkdefine.h"
#include "tooltipmanager.h"
#include "tradedlg.h"

class CStandingInLine;

class FrOfflineTradeFinishEditDlg : public FrTradeFinishEditDlg
{
public:
	DECLARE_OBJECT(FrOfflineTradeFinishEditDlg)

	FrOfflineTradeFinishEditDlg();
	virtual ~FrOfflineTradeFinishEditDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void SetListTradeItem(std::list<sTradeItem>* pList);
	void GetSelectSlotInfo(int& uid, int& slot);

protected:
	void OnTradeItemListOwnerDraw(int param);
	void OnTradeItemListLBtnUp();
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);

	FrListItem* m_pSelectItem;
	FrArea* m_pToolTip;
	CToolTipManager m_toolTipMng;
	MiniBtn m_extendBtn[2];
	MiniBtn m_returnBtn[2];
	MiniBtn m_buyBtn[2];
	MiniBtn m_uploadBtn[2];
	MiniBtn m_deleteBtn[2];
	MiniBtn m_deleteMark;
	MiniBtn m_tradeState[3];

private:
	DECLARE_FRESH_MSGMAP()
};

class COfflineTradeDlg : public FrForm
{
public:
	DECLARE_OBJECT(COfflineTradeDlg)

	COfflineTradeDlg();
	virtual ~COfflineTradeDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void SetListItem();
	void SetPageData(int curPage, int maxPage);
	void RequestMaketList();
	bool SetSearchString(std::string str);
	bool OnStandingInLineDlgResult(int result, FrForm* form);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);

	void OnAreaSubNickInit(int param);
	void OnAreaSubNickOwnerDraw(int param);
	void OnAreaSubNickLBtnUP();
	void OnAreaSubPriceInit(int param);
	void OnAreaSubPriceOwnerDraw(int param);
	void OnAreaSubPriceLBtnUP();
	void OnAreaSubItemNameInit(int param);
	void OnAreaSubItemNameOwnerDraw(int param);
	void OnAreaSubItemNameLBtnUP();
	void OnMaketListInit(int param);
	void OnMaketListOwnerDraw(int param);
	void OnMaketListBtnDown();
	void OnItemSearchInit(int param);
	bool OnItemSearchEnterKey(int param);
	void OnItemSearchLBtnUp();
	void OnBtnMainSearchInit(int param);
	void OnBtnMainSearchUp();
	void OnEditMaxPageInit(int param);
	void OnEditCurrentPageInit(int param);
	bool OnEditCurrentPageEnterKey(int param);
	void OnBtnPrevInit(int param);
	void OnBtnPrevBtnUp();
	void OnBtnNextInit(int param);
	void OnBtnNextBtnUp();
	void OnBtnGoPageInit(int param);
	void OnBtnGoPageBtnUp();
	void OnBtnRefreshInit(int param);
	void OnBtnRefreshBtnUp();
	void OnBtnDetailInit(int param);
	void OnBtnDetailBtnUp();
	void OnEditMsgInit(int param);
	void OnEditMsgLBtnUp();
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);

	FrViewer* m_pAreaSubNick;
	FrViewer* m_pAreaSubPrice;
	FrViewer* m_pAreaSubItemName;
	FrEdit* m_pItemSearch;
	FrEdit* m_pMaxPage;
	FrEdit* m_pCurPage;
	FrListBox* m_pMarketList;
	FrButton* m_pBtnPrev;
	FrButton* m_pBtnNext;
	FrButton* m_pBtnGoPage;
	FrButton* m_pBtnMainSearch;
	FrButton* m_pBtnRefresh;
	FrButton* m_pBtnDetail;
	FrEdit* m_pEditMsg;
	FrArea* m_pToolTip;
	CToolTipManager m_toolTipMng;
	CStandingInLine* m_pStandingInLineDlg;
	MiniBtn m_moveBtn[2];
	int m_maxPage;
	int m_curPage;
	int m_searchType;
	int m_detailType;
	bool m_bReserved;
	int m_bCanVisit;
	std::string m_searchString;

private:
	DECLARE_FRESH_MSGMAP()
};

struct sdays_t
{
	const char* str;
	int day;
};

class CBuyingSlotDlg : public FrForm
{
public:
	DECLARE_OBJECT(CBuyingSlotDlg)

	CBuyingSlotDlg();
	virtual ~CBuyingSlotDlg();

	void RecalculatePang();

protected:
	void OnDaysInit(int param);
	void OnDaysBtnDown();
	void OnPriceInit(int param);
	void OnMyMoneyInit(int param);
	void OnMoneyLeftInit(int param);
	void OnCheckOutInit(int param);
	void OnCheckOutBtnDown();
	void OnSlotPriceInit(int param);

	FrComboBox* m_pDays;
	FrEdit* m_pMyMoney;
	FrEdit* m_pMoneyLeft;
	FrEdit* m_pPrice;
	FrButton* m_pCheckOut;
	FrEdit* m_pSlotPrice;
	__int64 m_price;
	int m_slotNum;

public:
	void SetSlotNum(int num) { m_slotNum = num; }

private:
	DECLARE_FRESH_MSGMAP()
};

class COfflineShopEditDlg : public FrTradeEditDlg
{
	friend class CTask;

public:
	DECLARE_OBJECT(COfflineShopEditDlg)

	COfflineShopEditDlg();
	virtual ~COfflineShopEditDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void SetSelectData(unsigned long uid, unsigned long slot);
	void InitAllUI();
	void SetListTradeItem();
	void SetSlotData();
	bool IsCheckCardPats(unsigned long typeId, unsigned long id);
	bool OnOfflineEquitCancelDlgResult(int result, FrForm* form);
	bool OnOfflineTradeItemOnDlgResult(int result, FrForm* form);
	void DelListMyItem(sTradeItem* pItem, unsigned long count,
		unsigned char slot);
	bool OnOfflineTradeBuyDlgResult(int result, FrForm* form);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);

	void OnAreaBg01Init(int param);
	void OnAreaBg02Init(int param);
	void OnAreaBg03Init(int param);
	void OnAreaBg04Init(int param);
	void OnAreaBg05Init(int param);
	void OnStallSlotNumInit(int param);
	void OnSlotNumInit(int param);
	void OnTradeItemListInit(int param);
	void OnTradeItemListLClick();
	void OnTradeItemListOwnerDraw(int param);
	void OnVisitorInit(int param);
	void OnOpenBnInit(int param);
	void OnTradeMyItemOkBnUp();
	void OnCloseBnInit(int param);
	void OnExitBnUp();
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);

	FrListBox* m_pTradeItemList;
	FrEdit* m_pVisitor;
	FrButton* m_pOpenBn;
	FrButton* m_pCloseBn;
	unsigned long m_reserved;
	FrArea* m_pAreaBg01;
	FrArea* m_pAreaBg02;
	FrArea* m_pAreaBg03;
	FrArea* m_pAreaBg04;
	FrArea* m_pAreaBg05;
	FrEdit* m_pStallSlotNum;
	FrEdit* m_pSlotNum;
	FrArea* m_pToolTip;
	CToolTipManager m_toolTipMng;
	FrOfflineTradeFinishEditDlg* m_pFinishEditDlg;
	MiniBtn m_buyBtn[2];
	MiniBtn m_deleteBtn[2];
	int m_usedSlotNum;
	int m_bExit;
	unsigned long m_selectUID;
	unsigned long m_selectSlot;

private:
	DECLARE_FRESH_MSGMAP()
};

class COfflineShopDlg : public FrTradeDlg
{
public:
	DECLARE_OBJECT(COfflineShopDlg)

	COfflineShopDlg();
	virtual ~COfflineShopDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	bool OnOfflineShopEditDlgCreateResult(int result, FrForm* form);
	void SetListTradeItem(bool bRefresh);

protected:
	virtual void OnProc(const float delta);

	void OnVisitorBackOwnerDraw();
	void OnVisitorInit(int param);
	void OnCloseBnUp();
	void OnVisitorBackInit(int param);
	void OnTradeItemListOwnerDraw(int param);
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);
	void OnTradeItemListLClick();

	FrArea* m_pVisitorBack;
	FrEdit* m_pVisitor;
	FrArea* m_pToolTip;
	CToolTipManager m_toolTipMng;
	MiniBtn m_extendBtn[2];
	MiniBtn m_returnBtn[2];
	MiniBtn m_buyBtn[2];
	MiniBtn m_uploadBtn[2];
	MiniBtn m_deleteBtn[2];
	MiniBtn m_deleteMark;
	MiniBtn m_tradeState[3];
	int m_bExit;
	FrListItem* m_pSelectItem;

private:
	DECLARE_FRESH_MSGMAP()
};

class COfflineShopVisitorDlg : public FrTradeDlg
{
public:
	DECLARE_OBJECT(COfflineShopVisitorDlg)

	COfflineShopVisitorDlg();
	virtual ~COfflineShopVisitorDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	bool OnOfflineShopEditDlgCreateResult(int result, FrForm* form);
	void SetListTradeItem(bool bRefresh);

protected:
	virtual void OnProc(const float delta);

	void OnEditBnUp();
	void OnVisitorBackOwnerDraw();
	void OnCloseBnUp();
	void OnVisitorInit(int param);
	void OnVisitorBackInit(int param);
	void OnTradeItemListOwnerDraw(int param);
	void OnTradeItemListLClick();
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);

	FrEdit* m_pVisitor;
	FrArea* m_pVisitorBack;
	FrArea* m_pToolTip;
	CToolTipManager m_toolTipMng;
	MiniBtn m_buyBtn[2];
	MiniBtn m_unusedBtn;
	MiniBtn m_tradeState[3];

private:
	DECLARE_FRESH_MSGMAP()
};

class COfflineBuyDlg : public FrTradeBuyDlg
{
public:
	DECLARE_OBJECT(COfflineBuyDlg)

	COfflineBuyDlg();
	virtual ~COfflineBuyDlg();

	bool OnConfirmResult(int result, FrForm* form);

protected:
	void OnOkBnUp();

	sStallSlot m_buyItemData;
	int m_count;

public:
	void SetBuyitemData(sStallSlot data) { m_buyItemData = data; }

private:
	DECLARE_FRESH_MSGMAP()
};
