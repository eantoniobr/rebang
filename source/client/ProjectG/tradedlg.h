#pragma once

#include <vector>
#include <list>
#include "frform.h"
#include "frlistbox.h"
#include "../../shared/globalnetworkdefine.h"
#include "tooltipmanager.h"
struct sPartEquipInfo
{
	unsigned long typeId;
	unsigned long id;

	sPartEquipInfo()
	{
		typeId = 0;
		id = 0;
	}
};

enum eTypeSalesTrade
{
	eTypeSalesTrade_None,
	eTypeSalesTrade_Each,
	eTypeSalesTrade_Package,
};

class FrTradeDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeDlg)
	FrTradeDlg();
	virtual ~FrTradeDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void OpenTradeShop(unsigned long uid);
	void SetListTradeItem(bool bClear);
	void DrawPang();
	void UpdateTradeTitle();
	void UpdateCountVisitor();
	void EnableSendingServer(bool bEnable);
	void ShowStaticOutOfStock(bool bShow);
	void EnableHideBn(bool bEnable);
	void SetPackageSale(eTypeSalesTrade type);
	bool OnTradeBuyDlgResult(int result, FrForm* form);

protected:
	virtual bool OnInit();

	void OnTradeDlgInit(int param);
	void OnVisitorBackInit(int param);
	void OnVisitorBackOwnerDraw();
	void OnMyPangInit(int param);
	void OnMyPangOwnerDraw();
	void OnTradeItemListInit(int param);
	void OnTradeItemListLClick();
	void OnTradeItemListRClick();
	void OnTradeItemListOwnerDraw(int param);
	void OnNoItem01Init(int param);
	void OnNoItem02Init(int param);
	void OnVisitorInit(int param);
	void OnUserIdInit(int param);
	void OnTitleInit(int param);
	void OnEditBnInit(int param);
	void OnEditBnUp();
	void OnCloseBnInit(int param);
	void OnCloseBnUp();
	void OnHideBnInit(int param);
	void OnHideBnUp();
	void OnExitBnInit(int param);
	void OnExitBnUp();
	void OnPackagePurchaseButtonInit(int param);
	void OnPackagePurchaseLButtonUp();

	FrArea* m_pVisitorBack;
	FrListBox* m_pTradeItemList;
	FrStatic* m_pNoItem01;
	FrStatic* m_pNoItem02;
	FrEdit* m_pVisitor;
	FrEdit* m_pUserId;
	FrEdit* m_pTitle;
	FrButton* m_pEditBn;
	FrButton* m_pCloseBn;
	FrButton* m_pHideBn;
	FrButton* m_pExitBn;
	const Bitmap* m_pItemBaseN;
	const Bitmap* m_pItemBaseO;
	const Bitmap* m_pItemBaseD;
	const Bitmap* m_pItemBaseEmpty;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	WTitleFont* m_pNumFont;
	WTitleFont* m_pPangFont;
	bool m_bMyShop;
	unsigned long m_ownerUID;
	char m_reserved168[32];
	bool m_bSendingServer;
	int m_reserved18c;
	FrButton* m_pPackagePurchaseBn;
	__int64 m_totalPrice;
	eTypeSalesTrade m_packageSale;
	MiniBtn m_buyBtn[2];
	MiniBtn m_unusedBtn;
	MiniBtn m_deleteMark;
	MiniBtn m_clock;

public:
	eTypeSalesTrade GetPackageSale() const { return m_packageSale; }
	bool IsPackageSale()
	{
		return m_packageSale == eTypeSalesTrade_Package ? true : false;
	}

private:
	DECLARE_FRESH_MSGMAP()
};

class FrTradeBuyDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeBuyDlg)
	FrTradeBuyDlg();
	virtual ~FrTradeBuyDlg();

	void SetBuyItem(sTradeItem* pItem);
	void SetBuyItemList();
	void SetControlsBuyItem(sTradeItem* pItem);
	void SetControlsItemList();
	void UpdatePrice();
	void UpdatePriceList();
	bool OnConfirmResult(int result, FrForm* form);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);

	void OnTradeBuyDlgInit(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();
	void OnBuyItemIconInit(int param);
	void OnBuyItemIconOwnerDraw();
	void OnBuyItemNameInit(int param);
	void OnBuyItemAbilityInit(int param);
	void OnMyPangInit(int param);
	void OnPriceInit(int param);
	void OnPangLeftInit(int param);
	void OnNumberInit(int param);
	void OnNumberNextBnInit(int param);
	void OnNumberNextBnUp();
	void OnNumberPrevBnInit(int param);
	void OnNumberPrevBnUp();
	void OnPurchaseListInit(int param);
	void OnPurchaseListOwnerdraw(int param);

	FrArea* m_pBuyItemIcon;
	FrEdit* m_pBuyItemName;
	FrEdit* m_pBuyItemAbility;
	FrEdit* m_pMyPang;
	FrEdit* m_pPrice;
	FrEdit* m_pPangLeft;
	FrButton* m_pNumberNextBn;
	FrButton* m_pNumberPrevBn;
	FrEdit* m_pNumber;
	FrListBox* m_pPurchaseList;
	eTypeSalesTrade m_packageSale;
	sTradeItem m_buyItem;
	sTradeItem* m_pBuyItem;
	bool m_bClosing;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	WTitleFont* m_pNumFont;
	int m_prevNumber;

public:
	bool IsClosing() { return m_bClosing; }

	void SetClosing(bool bClosing) { m_bClosing = bClosing; }

	sTradeItem* GetBuyItem() { return m_pBuyItem; }

	void SetPackageSale() { m_packageSale = eTypeSalesTrade_Package; }
	eTypeSalesTrade GetPackageSale() { return m_packageSale; }

	void ClearTradeList() { m_pPurchaseList->ClearItem(); }

private:
	DECLARE_FRESH_MSGMAP()
};

class FrTradeResultDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeResultDlg)
	FrTradeResultDlg();
	virtual ~FrTradeResultDlg();

	void SetResultItem(sTradeItem* pItem);
	void SetResultItemList(std::vector<sTradeItem>* pList);

protected:
	virtual bool OnInit();

	void OnTradeResultDlgInit(int param);
	void OnResultItemIconInit(int param);
	void OnResultItemIconOwnerDraw();
	void OnResultItemNameInit(int param);
	void OnResultItemAbilityInit(int param);
	void OnPurchaseListInit(int param);
	void OnPurchaseListOwnerdraw(int param);

	FrArea* m_pResultItemIcon;
	FrEdit* m_pResultItemName;
	FrEdit* m_pResultItemAbility;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	sTradeItem m_resultItem;
	WTitleFont* m_pNumFont;
	unsigned long m_reserved1d8;
	std::vector<sTradeItem> m_resultItemList;
	FrListBox* m_pPurchaseList;

private:
	DECLARE_FRESH_MSGMAP()
};

enum eResultTrade
{
	eResultTrade_Success = 1,
	eResultTrade_EmptyTitle = 5,
	eResultTrade_FilteredTitle = 7,
};

class FrTradeEditDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeEditDlg)
	FrTradeEditDlg();
	virtual ~FrTradeEditDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void SetListMyItem();
	void SetListTradeItem();
	void SetListEquipParts();
	void SetListTradingItem();
	void SetListEnableTradingMyItem();
	void AddListMyItem(sTradeItem* pItem);
	void DelListMyItem(sTradeItem* pItem);
	void AddListTradeItem(sTradeItem* pItem);
	void DelListTradeItem(sTradeItem* pItem);
	void CancelSelectedTradeItem();
	void SetTradeMyItem(sTradeItem* pItem);
	void SetControlsTradeMyItem(sTradeItem* pItem, bool bEnable);
	void SetControlsButton(bool bOpen, bool bClose);
	int GetNumEquipItem(unsigned long typeId);
	int GetNumTradingItem(unsigned long id);
	bool IsEquipParts(unsigned long typeId, unsigned long id);
	int CheckTradeEdit();
	eResultTrade SendTradeTitle();
	void UpdateTradeTitle();
	void UpdateTradeTitleEdit();
	void DrawPang();
	void DrawItem(WPoint pos, sTradeItem* pItem, unsigned char state);

protected:
	virtual bool OnInit();

	bool PushPackageSaleButton();
	bool IsPushedPackageSaleButton();

	void OnTradeEditDlgInit(int param);
	void OnMyItemListInit(int param);
	void OnMyItemListLClick();
	void OnMyItemListRClick();
	void OnMyItemListOwnerDraw(int param);
	void OnTradeItemListInit(int param);
	void OnTradeItemListLClick();
	void OnTradeItemListOwnerDraw(int param);
	void OnVisitorInit(int param);
	void OnUserIdInit(int param);
	void OnTitleInit(int param);
	void OnTitleEditInit(int param);
	bool OnTitleEditEnterKey(int param);
	void OnTitleEditBnInit(int param);
	void OnTitleEditBnUp();
	void OnTradeMyItemIconInit(int param);
	void OnTradeMyItemIconOwnerDraw();
	void OnTradeMyItemNameInit(int param);
	void OnTradeMyItemAbilityInit(int param);
	void OnTradeMyItemNumberInit(int param);
	void OnTradeMyItemPriceInit(int param);
	void OnTradeMyItemPriceClick();
	void OnTradeMyItemOkBnInit(int param);
	void OnTradeMyItemOkBnUp();
	void OnTradeMyItemCancelBnInit(int param);
	void OnTradeMyItemCancelBnUp();
	void OnOpenBnInit(int param);
	void OnOpenBnUp();
	void OnCloseBnInit(int param);
	void OnCloseBnUp();
	void OnExitBnInit(int param);
	void OnExitBnUp();
	void OnPackageSaleInit(int param);
	void OnPackageSaleButtonUp();
	void OnTooltipAreaInit(int param);
	void OnTooltipAreaOwnerDraw(int param);

	FrListBox* m_pTradeItemList;
	FrListBox* m_pMyItemList;
	FrEdit* m_pVisitor;
	FrEdit* m_pUserId;
	FrEdit* m_pTitle;
	FrEdit* m_pTitleEdit;
	FrArea* m_pTradeMyItemIcon;
	FrEdit* m_pTradeMyItemName;
	FrEdit* m_pTradeMyItemAbility;
	FrEdit* m_pTradeMyItemNumber;
	FrEdit* m_pTradeMyItemPrice;
	FrButton* m_pTradeMyItemOkBn;
	FrButton* m_pTradeMyItemCancelBn;
	FrButton* m_pOpenBn;
	FrButton* m_pCloseBn;
	FrButton* m_pExitBn;
	FrButton* m_pPackageSale;
	FrArea* m_pTooltipArea;
	CToolTipManager m_toolTipMng;
	const Bitmap* m_pMyItemBaseClick;
	const Bitmap* m_pMyItemBaseOver;
	const Bitmap* m_pTradeItemBaseNormal;
	const Bitmap* m_pTradeItemBaseOver;
	const Bitmap* m_pTradeItemBaseClick;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	WTitleFont* m_pNumFont;
	WTitleFont* m_pPangFont;
	char m_reserved190[32];
	char m_title[32];
	std::list<sTradeItem> m_myItemList;
	std::list<sTradeItem> m_tradeItemList;
	sTradeItem* m_pSelectItem;
	std::list<sPartEquipInfo> m_equipPartsList;
	eTypeSalesTrade m_packageSale;
	MiniBtn m_deleteBtn[2];
	MiniBtn m_editBtn[2];
	MiniBtn m_deleteMark;
	MiniBtn m_clock;

public:
	void SetPackageSale(eTypeSalesTrade type) { m_packageSale = type; }
	bool IsPackageSale()
	{
		return m_packageSale == eTypeSalesTrade_Package ? true : false;
	}

private:
	DECLARE_FRESH_MSGMAP()
};

class FrTradeFinishEditDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeFinishEditDlg)
	FrTradeFinishEditDlg();
	virtual ~FrTradeFinishEditDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void SetListTradeItem(std::list<sTradeItem>* pList);
	void SetTradeUserId();
	void SetTradeTitle(char* title);

protected:
	virtual bool OnInit();

	void OnTradeFinishEditDlgInit(int param);
	void OnTradeItemListInit(int param);
	void OnTradeItemListOwnerDraw(int param);
	void OnUserIdInit(int param);
	void OnTitleInit(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrListBox* m_pTradeItemList;
	FrEdit* m_pUserId;
	FrEdit* m_pTitle;
	const Bitmap* m_pItemBaseN;
	const Bitmap* m_pItemBaseO;
	const Bitmap* m_pItemBaseD;
	const Bitmap* m_pItemBaseEmpty;
	const Bitmap* m_pUccOriginal;
	const Bitmap* m_pUccCopied;
	const Bitmap* m_pUccTempSaved;
	WTitleFont* m_pNumFont;
	char m_title[32];
	std::list<sTradeItem>* m_pTradeList;
	unsigned char m_titleState;
	eTypeSalesTrade m_packageSale;
	MiniBtn m_deleteMark;
	MiniBtn m_clock;

public:
	void SetPackageSale(eTypeSalesTrade type) { m_packageSale = type; }
	bool IsPackageSale()
	{
		return m_packageSale == eTypeSalesTrade_Package ? true : false;
	}

private:
	DECLARE_FRESH_MSGMAP()
};

class FrTradeWarningDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeWarningDlg)
	FrTradeWarningDlg();
	virtual ~FrTradeWarningDlg();

	void SetControls(int type);
	void SetWarningMessageType(int type, unsigned char param);
	void SetWarningMessageForPackage(int type);

protected:
	void OnTradeWarningDlgInit(int param);
	void OnMsg01Init(int param);
	void OnMsg02Init(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();
	void OnCancelBnInit(int param);
	void OnCancelBnUp();

	FrStatic* m_pMsg01;
	FrStatic* m_pMsg02;
	FrButton* m_pOkBn;
	FrButton* m_pCancelBn;
	int m_type;

private:
	DECLARE_FRESH_MSGMAP()
};

class FrTradeLevelLimitDlg : public FrForm
{
	DECLARE_OBJECT(FrTradeLevelLimitDlg)
	FrTradeLevelLimitDlg();
	virtual ~FrTradeLevelLimitDlg();

protected:
	virtual bool OnInit();

	void OnOkBnInit(int param);
	void OnOkBnUp();

private:
	DECLARE_FRESH_MSGMAP()
};

void SetTradeResultCode(int code, int packetType, sTradeItem* item);
