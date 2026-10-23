#pragma once

#include <list>
#include <map>

#include "../../shared/classdefine.h"
#include "taskmain.h"
#include "anotherhand.h"

class CExhibition;
class CPartTidList;
class FrCheckoutDlg;
class FrUpgradeCaddieDlg;
class FrForm;
class FrEdit;
class FrStatic;
class FrArea;
class FrViewer;
class FrTabButton;
class FrButton;
class FrListBox;
class FrGroupBox;
class FrGaugeBar;
class FrComboBox;
class FrTextButton;
class FrGraphicInterface;
class Bitmap;
class WOverlay;
class MsgObject;
struct FrListItem;
struct IFF_ITEM_COMMON;
struct sCaddieInfo;

class CShopMain : public CTaskMain, public CHandOwner
{
	DECLARE_OBJECT(CShopMain)

public:
	enum mainTab_t
	{
		MAINTAB_CHARACTER = 0,
		MAINTAB_ITEM = 1,
		MAINTAB_CADDIE = 2,
		MAINTAB_MASCOT = 3,
		MAINTAB_SKIN = 4,
		MAINTAB_INTERIOR = 5,
	};

	enum subTab_t
	{
		SUBTAB_PACKAGE = 0,
		SUBTAB_PARTS1 = 1,
		SUBTAB_PARTS2 = 2,
		SUBTAB_PARTS3 = 3,
		SUBTAB_PARTS4 = 4,
		SUBTAB_HAIR = 5,
		SUBTAB_CLUBSET = 6,
		SUBTAB_AZTEC = 7,
		SUBTAB_EQUIP = 8,
		SUBTAB_NOEQUIP = 9,
		SUBTAB_CADDIE = 10,
		SUBTAB_MASCOT = 12,
		SUBTAB_SKIN1 = 13,
		SUBTAB_SKIN2 = 14,
		SUBTAB_SKIN3 = 15,
		SUBTAB_SKIN4 = 16,
		SUBTAB_UCC = 26,
		SUBTAB_CARD = 27,
		SUBTAB_INTERIOR1 = 28,
		SUBTAB_INTERIOR2 = 29,
		SUBTAB_INTERIOR3 = 30,
		SUBTAB_FURNITURE = 31,
		SUBTAB_DECORATE = 32,
		SUBTAB_CUTIN = 33,
		SUBTAB_SKIN5 = 34,
	};

	enum statTab_t
	{
		STATTAB_PART = 0,
		STATTAB_ALL = 1,
	};

	struct miniBtn_t
	{
		WRect rect;
		const Bitmap* pNormal;
		const Bitmap* pOver;
		bool bEnable;
	};

	struct oldItem_t
	{
		unsigned long typeId;
		unsigned long oldTypeId;
		unsigned long oldUid;
	};

	CShopMain();
	virtual ~CShopMain();

protected:
	void OnShopMainInit(int param);
	void OnShopMainFinish();
	void OnSortOptionComboInit(int param);
	void OnSortOptionComboDown();
	void OnSearchGoodsButtonInit(int param);
	void OnSearchGoodsLButtonDown();
	void InitShopDialogs();
	void InitShopControls();
	virtual void CloseAllDialogs();
	void TurnOnItemStatus();
	void TurnOffItemStatus();
	void OnPetInit(int param);
	void OnSkinPetInit(int param);
	void OnSkinPet2Init(int param);
	void DrawSkinFrame();
	void DrawSkinSlot();
	void DrawCutinFrame();
	WOverlay* GetCutinImg(unsigned long typeId);
	void DeleteCutinImages();
	void OnPetOwnerDraw(int param);
	void OnItemDescBgInit(int param);
	void OnItemDescBgOwnerDraw(int param);
	void OnItemDescInit(int param);
	void SetItemDescRect();
	void ShowItemDesc(unsigned long typeId);
	void OnPowerBarInit(int param);
	void OnControlBarInit(int param);
	void OnImpactBarInit(int param);
	void OnSpinBarInit(int param);
	void OnCurveBarInit(int param);
	void DrawItemPrice(FrGraphicInterface* pGI, float x, float y,
		IFF_ITEM_COMMON& item, FrListItem* pItem);
	void OnSelFrameInit(int param);
	void OnStatBoxInit(int param);
	void OnSelItemIconInit(int param);
	void OnSelItemIconOwnerDraw(int param);
	void OnSelItemInit(int param);
	void OnSelItemOwnerDraw(int param);
	void OnTabTxt1Init(int param);
	void OnTabTxt2Init(int param);
	void OnTabTxt3Init(int param);
	void OnSelectedNameInit(int param);
	void OnSelItemUp();
	void OnSelItemPrevInit(int param);
	void OnSelItemPrevUp();
	void OnSelItemNextInit(int param);
	void OnSelItemNextUp();
	void OnStatFrameInit(int param);
	void OnStatTextInit(int param);
	void OnStatPartInit(int param);
	void OnStatPartUp();
	void OnStatPartOwnerDraw(int param);
	void OnStatAllInit(int param);
	void OnStatAllUp();
	void OnStatAllOwnerDraw(int param);
	void OnTabMainInit(int param);
	void OnTabMainButtonUp();
	void OnTabSubInit(int param);
	void OnTabSubButtonUp();
	void OnItemListInit(int param);
	void DrawStatus(FrGraphicInterface* pGI, FrListItem* pItem,
		short* const stat, short* const upgrade, float y);
	void DrawStatus2(FrGraphicInterface* pGI, FrListItem* pItem,
		short* const stat, short* const upgrade, float y);
	void DrawStatusCard(FrGraphicInterface* pGI, FrListItem* pItem,
		short* const stat, float y);
	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);
	void OnItemListOwnerDraw(int param);
	void OnItemListBtnDown();
	void OnItemListRBtnDown();
	void OnBuyAllInit(int param);
	void OnBuyAllUp();
	void OnBuyResetInit(int param);
	void OnBuyResetUp();
	void OnBuyHoverOn(int param);
	void OnBuyHoverOff(int param);
	void OnSideTabBuyInit(int param);
	void OnSideTabBuyUp();
	void OnSideTabRentalInit(int param);
	void OnSideTabRentalUp();
	void SetVisibleSideTab(bool bVisible);
	void BuildDisplayRental(subTab_t subTab);
	void DrawRentalPrice(float x, float y, IFF_ITEM_COMMON& item,
		FrListItem* pItem);
	bool IsSelectedRentalTab();
	void OnPartCartListInit(int param);
	void OnPartCartListOwnerDraw(int param);
	void DrawStatus3(FrGraphicInterface* pGI, float x, float y,
		short* const stat, short* const upgrade);
	void OnAuxPartCartListInit(int param);
	void OnAuxPartCartListOwnerDraw(int param);
	void CheckAuxCartScroll();
	void TurnOffAuxCartScroll();
	void TurnOnAuxCartScroll();
	void OnScrollUpInit(int param);
	void OnScrollUpUp();
	void OnScrollDownInit(int param);
	void OnScrollDownUp();
	void OnItemSlotFrame1Init(int param);
	void OnItemSlotFrame2Init(int param);
	void BuildMyItemSlot(bool bRebuild);
	void OnItemSlotInit(int param);
	void OnItemSlotOwnerDraw(int param);
	void OnPowerEditInit(int param);
	void OnControlEditInit(int param);
	void OnImpactEditInit(int param);
	void OnSpinEditInit(int param);
	void OnCurveEditInit(int param);
	bool OnBuyDlgResult(int result, FrForm* pForm);
	bool OnGiftDlgResult(int result, FrForm* pForm);
	bool OnSellDlgResult(int result, FrForm* pForm);
	bool OnReemployeeResult(int result, FrForm* pForm);

public:
	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnDestroy();
	virtual void OnProcess(float delta);
	virtual void HandleMsg(const MsgObject& msg);

protected:
	virtual void OnAnotherHand(int key, void* pParam);
	void OpenLayout(const char* name);
	void SetPetCtrl(unsigned long typeId);
	void ShowPet(unsigned long typeId);
	void HidePet(bool bHide);
	void LoadItemImages();
	void LoadShopImages();
	bool HaveCharacter(unsigned long typeId);
	void BuildDisplayStand(subTab_t subTab);
	void Net_StartPeriodItem(unsigned long typeId);
	void SetLevelBar();
	void OpenInformation(unsigned long typeId);
	void OpenCaddieInfo(const sCaddieInfo& info);
	void ResetItemList(bool bResetSel);
	int GetItemNumInMyPocket(unsigned long typeId, bool bRental);
	void Checkout();
	void SendGift(const IFF_ITEM_COMMON& item);
	void Repay(const IFF_ITEM_COMMON& item, unsigned long uid);
	void ClearCartList(bool bRestore, CPartTidList* pParts);
	std::list<FrListItem*>::iterator DeleteItemFromCartList(
		unsigned long typeId);
	std::list<FrListItem*>::iterator DeleteItemFromAuxCartList(
		unsigned long typeId);
	bool SelectItemList(unsigned long typeId);
	bool SelectItemList(FrListItem* pItem);
	void UnselectItemList(unsigned long typeId);
	bool UnselectItemFromItemList(unsigned long typeId);

private:
	void TakeOff_PartNCartList(CPartTidList& parts, unsigned long typeId);
	void TakeOff_AuxPartNCartList(CPartTidList& parts, unsigned long typeId);
	void SetLevelBar_Char();
	void SetLevelBar_Clubset();
	void Build_Package(subTab_t subTab, int category);
	void Build_Hair(subTab_t subTab, int category);
	void Build_Parts(subTab_t subTab, int category);
	void Build_Clubset(subTab_t subTab, int category);
	void Build_Aztec(subTab_t subTab, int category);
	void Build_Equip(subTab_t subTab, int category);
	void Build_NoEquip(subTab_t subTab, int category);
	void Build_Card(subTab_t subTab, int category);
	void Build_Interior(subTab_t subTab, int category);
	void Build_Furniture(subTab_t subTab, int category);
	void Build_Decorate(subTab_t subTab, int category);
	void Build_Cutin(subTab_t subTab, int category);
	void Build_Caddie(subTab_t subTab, int category);
	void Build_Mascot(subTab_t subTab, int category);

protected:
	bool IsItemInCart(FrListItem* pItem);
	void PutOnNBackupShoppersOldItem(unsigned long typeId, CPartTidList& parts,
		unsigned long oldTypeId);
	void RestoreShoppersOldItem(unsigned long typeId, CPartTidList& parts);
	void ChangeSubTab(subTab_t subTab, bool bForce);
	void SetPetAreaRect();
	void SetMyItemSlot();
	void SetAutoScroll();
	void ChangeMainTab(mainTab_t mainTab, bool bForce);
	void ChangeStatTab(statTab_t statTab);
	void ChangeCharacter(unsigned long typeId);
	void ChangeCaddie(unsigned long typeId);
	void ChangeMascot(unsigned long typeId);
	void ChangeSkin(unsigned long typeId);
	void ChangeClubset(unsigned long typeId);
	void ChangeAztec(unsigned long typeId);
	void TurnOnItemSelect();
	void TurnOffItemSelect();
	const Bitmap* GetItemIcon(unsigned long typeId);
	void DrawSelItem(FrGraphicInterface* pGI, unsigned long typeId);
	void DrawCharacterList(FrGraphicInterface* pGI, unsigned long typeId);
	void DrawCaddieList(FrGraphicInterface* pGI, unsigned long typeId);
	void DrawMascotList(FrGraphicInterface* pGI, unsigned long typeId);
	void DrawSelArrow(FrGraphicInterface* pGI);
	bool IsVisibleInStock(IFF_ITEM_COMMON& item);
	void SafeLoadPet(unsigned long* pParts, bool bWait);
	void ShowMainModel(CPartTidList& parts);
	void LoadCardImages();
	void DeleteCardImages();
	WOverlay* GetCardImg(unsigned long typeId);
	void DrawCard();
	void InitalizeUpgradeCaddieInfo();
	void BuildVisibleCaddieList();
	void UpgradeCaddie(unsigned long typeId);

	FrEdit* m_pPopupEdit;
	float m_popupTime;
	FrStatic* m_pSelectedName;
	FrArea* m_pStatFrame;
	FrArea* m_pStatText;
	FrViewer* m_pStatPart;
	FrViewer* m_pStatAll;
	FrTabButton* m_pTabMain;
	FrTabButton* m_pTabSub;
	FrButton* m_pBuyAll;
	FrButton* m_pBuyReset;
	FrListBox* m_pItemList;
	FrListBox* m_pPartCartList;
	FrListBox* m_pAuxPartCartList;
	FrArea* m_pTabTxt[3];
	FrWnd* m_pReserved228;
	FrArea* m_pPetArea;
	FrArea* m_pSelItemIcon;
	FrButton* m_pSelItem;
	FrGroupBox* m_pStatBox;
	FrArea* m_pSelFrame;
	FrGaugeBar* m_pStatBar[5];
	FrStatic* m_pStatEdit[5];
	FrButton* m_pSelItemPrev;
	FrButton* m_pSelItemNext;
	FrButton* m_pScrollUp;
	FrButton* m_pScrollDown;
	FrArea* m_pItemDescBg;
	FrEdit* m_pItemDesc;
	FrArea* m_pSkinPet;
	FrArea* m_pSkinPet2;
	FrArea* m_pPet;
	FrArea* m_pItemSlotFrame1;
	FrArea* m_pItemSlotFrame2;
	FrListBox* m_pItemSlot;
	FrButton* m_pSideTabBuy;
	FrButton* m_pSideTabRental;
	FrCheckoutDlg* m_pCheckoutDlg;
	FrUpgradeCaddieDlg* m_pUpgradeCaddieDlg;
	std::map<unsigned long, unsigned long> m_upgradeCaddie;
	std::map<unsigned int, IFF_STRUCT::sCaddie> m_visibleCaddie;
	const Bitmap* m_pItemBase[5];
	const Bitmap* m_pReserved2d4[2];
	const Bitmap* m_pMarkNew;
	const Bitmap* m_pMarkHot;
	const Bitmap* m_pMarkLimited;
	const Bitmap* m_pMarkBegin;
	const Bitmap* m_pReserved2ec[3];
	const Bitmap* m_pStatDot[5][2];
	const Bitmap* m_pSelect[4];
	const Bitmap* m_pSelectCursor[2];
	const Bitmap* m_pStatBtn[3][3];
	const Bitmap* m_pStatAllBtn[3];
	const Bitmap* m_pStatIcon[5];
	const Bitmap* m_pCartSlot;
	const Bitmap* m_pCancelBtn[2];
	const Bitmap* m_pReserved388;
	const Bitmap* m_pGender[2];
	const Bitmap* m_pMasterSign;
	const Bitmap* m_pTeamBase;
	const Bitmap* m_pItemSlotBmp;
	const Bitmap* m_pSelArrow;
	const Bitmap* m_pItemDescBmp[2];
	const Bitmap* m_pReserved3ac[4];
	miniBtn_t m_miniBtn[7];
	std::map<unsigned long, const Bitmap*> m_itemIcon;
	std::map<unsigned int, WOverlay*> m_cardImg;
	std::map<unsigned int, WOverlay*> m_cutinImg;
	int m_reserved4a4[3];
	bool m_bSelectItemList;
	char* m_pCharStat;
	unsigned long* m_pCharParts;
	unsigned long m_partsUid[24];
	unsigned long* m_pAuxParts;
	unsigned char m_hairColor;
	unsigned long m_charTypeId;
	unsigned long m_caddieTypeId;
	unsigned long m_mascotTypeId;
	unsigned long m_aztecTypeId;
	unsigned long m_clubSetTypeId;
	statTab_t m_statTab;
	mainTab_t m_mainTab;
	subTab_t m_subTab;
	float m_selArrowOffset;
	float m_selArrowTime;
	WPoint m_itemDescOffset;
	WPoint m_itemDescPos;
	int m_statSubject;
	CExhibition* m_pExhibition;
	CAnotherHand m_anotherHand;
	std::list<unsigned long> m_removeList;
	std::list<oldItem_t> m_oldItemList;
	unsigned long m_skinTypeId[6];
	float m_skinScroll[2];
	int m_skinScrollDir[2];
	unsigned long m_cardTypeId;
	WOverlay* m_pEmptyCharCard;
	WOverlay* m_pEmptyCaddieCard;
	FrComboBox* m_pSortOptionCombo;
	FrTextButton* m_pSearchGoods;

	DECLARE_FRESH_MSGMAP()
};
