#pragma once

#include <list>
#include <vector>
#include "frform.h"

#include "../../shared/globalgamedefine.h"

class FrArea;
class FrStatic;
class FrEdit;
class FrButton;
class FrListBox;
class WOverlay;
struct sSCardAvilityPeriodInfo;

class FrSpCardUseDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrSpCardUseDlg)

	FrSpCardUseDlg();
	virtual ~FrSpCardUseDlg();

	void SetSpCardInfo(unsigned long& tid);
	unsigned long& GetSpCardTid() { return m_spCardTid; }
	unsigned long GetOverlappedCard();

protected:
	void OnItemInit(int param);
	void OnItemOwnerDraw(int param);
	void OnText1Init(int param);
	void OnText2Init(int param);

	unsigned long m_overlappedCardTid;
	unsigned long m_spCardTid;
	FrArea* m_pItem;
	FrStatic* m_pText1;
	FrStatic* m_pText2;
	DECLARE_FRESH_MSGMAP()
};

class FrCardUseDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrCardUseDlg)

	FrCardUseDlg();
	virtual ~FrCardUseDlg();

protected:
	void OnItemInit(int param);
	void OnItemOwnerDraw(int param);

public:
	unsigned long m_cardId;
	unsigned long m_cardTypeId;
	unsigned long m_reserved1;
	unsigned long m_reserved2;

protected:
	FrArea* m_pItem;
	DECLARE_FRESH_MSGMAP()
};

class FrOpenCardPackDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrOpenCardPackDlg)

	FrOpenCardPackDlg();
	virtual ~FrOpenCardPackDlg();

protected:
	void OnItemInit(int param);
	void OnItemOwnerDraw(int param);
	void OnLevelImgInit(int param);

public:
	unsigned long m_cardId;
	unsigned long m_cardTypeId;

protected:
	FrArea* m_pItem;
	FrArea* m_pLevelImg;
	DECLARE_FRESH_MSGMAP()
};

class FrOpenCardPackResultDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrOpenCardPackResultDlg)

	FrOpenCardPackResultDlg();
	virtual ~FrOpenCardPackResultDlg();

protected:
	void OnItemInit(int param);
	void OnItemOwnerDraw(int param);
	void OnCardFrmNumInit(int param);

public:
	unsigned long m_cardTypeId[4];

protected:
	FrArea* m_pItem;
	FrArea* m_pCardFrmNum;
	DECLARE_FRESH_MSGMAP()
};

class FrCardAttachDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrCardAttachDlg)

	FrCardAttachDlg();
	virtual ~FrCardAttachDlg();

	bool OnSetDlgTxt();

protected:
	void OnItemInit(int param);
	void OnItemOwnerDraw(int param);
	void OnCardAvilityInit(int param);
	void OnCardAvilityOldInit(int param);

public:
	unsigned long m_cardId;
	unsigned long m_cardTypeId;
	unsigned long m_itemId;
	unsigned long m_itemTypeId;
	int m_charSlot;
	int m_caddieSlot;
	unsigned long m_reserved1;
	unsigned long m_reserved2;

protected:
	FrArea* m_pItem;
	FrEdit* m_pCardAvility;
	FrEdit* m_pCardAvilityOld;
	DECLARE_FRESH_MSGMAP()
};

class CTFrameMove
{
public:
	CTFrameMove();
	CTFrameMove(unsigned char frameCount);
	~CTFrameMove();

	void AddFrame(FrArea* pFrame);
	bool SetFrameWidth(float width);
	bool SetFrameHeight(float height);

private:
	void Reset()
	{
		if (!m_frames.empty())
			m_frames.clear();
	}

	unsigned char m_frameCount;
	std::vector<FrArea*> m_frames;
};

class FrItemAttachCardDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrItemAttachCardDlg)

	FrItemAttachCardDlg();
	virtual ~FrItemAttachCardDlg();

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);

	void initCardSlotBtnTxt();

	void OnMyItemListInit(int param);
	void OnMyItemListLClick();
	void OnMyItemListRClick();
	void OnMyItemListOwnerDraw(int param);
	void OnAttachCardIconInit(int param);
	void OnAttachCardIconOwnerDraw();
	void OnAttachCardNameInit(int param);
	void OnAttachCardAbilityInit(int param);
	void OnAttachItemIconInit(int param);
	void OnAttachItemIconOwnerDraw();
	void OnAttachItemNameInit(int param);
	void OnAttachItemAbilityInit(int param);
	void OnAreaCharImgInit(int param);
	void OnItemListFoldInit(int param);
	void OnItemListFoldLClick();
	void OnItemListUnfoldInit(int param);
	void OnItemListUnfoldLClick();
	void OnDlgFrm_04Init(int param);
	void OnDlgFrm_05Init(int param);
	void OnDlgFrm_06Init(int param);
	void OnDlgFrm_07Init(int param);
	void OnDlgFrm_08Init(int param);
	void OnDlgFrm_09Init(int param);

	bool OnCardAttachResult(int result, FrForm* form);
	void OnOpenAttachDlg(int charSlot, int caddieSlot);
	void SetCharacterAttatchBtnTxt(unsigned long cardTypeId, char* text);
	void SetCaddieAttatchBtnTxt(unsigned long cardTypeId, char* text);
	void DrawBtnCharSlotimg(float x, float y, unsigned long cardTypeId);
	void DrawBtnCaddieSlotimg(float x, float y, unsigned long cardTypeId);

	void OnCharSlotBtnInit_1(int param);
	void OnCharSlotBtnDown_1();
	void OnCharSlotBtnOwnerDraw_1();
	void OnCharSlotBtnInit_2(int param);
	void OnCharSlotBtnDown_2();
	void OnCharSlotBtnOwnerDraw_2();
	void OnCharSlotBtnInit_3(int param);
	void OnCharSlotBtnDown_3();
	void OnCharSlotBtnOwnerDraw_3();
	void OnCharSlotBtnInit_4(int param);
	void OnCharSlotBtnDown_4();
	void OnCharSlotBtnOwnerDraw_4();
	void OnCaddieSlotBtnInit_1(int param);
	void OnCaddieSlotBtnDown_1();
	void OnCaddieSlotBtnOwnerDraw_1();
	void OnCaddieSlotBtnInit_2(int param);
	void OnCaddieSlotBtnDown_2();
	void OnCaddieSlotBtnOwnerDraw_2();
	void OnCaddieSlotBtnInit_3(int param);
	void OnCaddieSlotBtnDown_3();
	void OnCaddieSlotBtnOwnerDraw_3();
	void OnCaddieSlotBtnInit_4(int param);
	void OnCaddieSlotBtnDown_4();
	void OnCaddieSlotBtnOwnerDraw_4();

	void SetListMyItem();
	void SetListCardUsableMyItem();
	void DrawItem(WPoint pos, unsigned long typeId, unsigned long state);
	void SetCardInfo(unsigned long cardTypeId);
	void SetListEquipParts();
	bool IsEquipParts(unsigned long charTypeId, unsigned long partTypeId);
	void SetSelectMyItem(sItemAttachCard* pItem);
	void SetPartsSlot(unsigned long typeId);
	void SetPartsSlotBtnTxt();
	void DrawPartsSlot(WPoint pos, unsigned long typeId, unsigned long slot,
		FrGraphicInterface* pDevice);
	void DrawPartsLine();
	void AgreeAttaching();
	bool OnAgreeAttachingResult(int result, FrForm* form);
	void ResetCardSlotInfo();

public:
	unsigned long m_cardTypeId;
	unsigned long m_cardId;
	int m_cardType;
	unsigned long m_itemTypeId;
	unsigned long m_itemId;
	int m_selectSlot;

protected:
	FrListBox* m_pMyItemList;
	FrArea* m_pCardIcon;
	FrEdit* m_pCardName;
	FrEdit* m_pCardAbility;
	FrArea* m_pItemIcon;
	FrEdit* m_pItemName;
	FrEdit* m_pItemAbility;
	FrArea* m_pCharImg;
	FrButton* m_pFoldBtn;
	FrButton* m_pUnfoldBtn;
	FrButton* m_pCharSlotBtn[4];
	FrButton* m_pCaddieSlotBtn[4];
	unsigned long m_reserved[4];
	FrCardAttachDlg* m_pCardAttachDlg;
	const Bitmap* m_pItemClickBmp;
	const Bitmap* m_pItemOverBmp;
	sItemAttachCard* m_pSelectItem;
	std::list<sItemAttachCard> m_myItemList;
	std::list<sItemAttachCard> m_equipPartsList;
	CTFrameMove m_frameMove;
	const Bitmap* m_pCharEmptyBmp;
	const Bitmap* m_pCaddieEmptyBmp;
	WOverlay* m_pLine;
	bool m_bFold;
	char m_charSlotTxt[4][50];
	char m_caddieSlotTxt[4][50];
	bool m_bCharSlotAttached[4];
	bool m_bCaddieSlotAttached[4];
	unsigned long m_charSlotCardTypeId[4];
	unsigned long m_caddieSlotCardTypeId[4];
	const Bitmap* m_pUccOriginalBmp;
	const Bitmap* m_pUccCopiedBmp;
	const Bitmap* m_pUccTempSavedBmp;
	DECLARE_FRESH_MSGMAP()
};

class FrSPCardBuffDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrSPCardBuffDlg)

	FrSPCardBuffDlg();
	virtual ~FrSPCardBuffDlg();

	virtual bool OnInit();
	virtual bool Close(eFormRet ret, bool bSound);
	void SetBuffItem(const std::list<sSCardAvilityPeriodInfo>& cards,
		bool bClear);
	const WPoint& GetPosition() { return m_Pos; }
	int GetSpecialCardNum();
	static void SetPosition(const WPoint& pos) { m_Pos = pos; }
	static void SetSpecialBuffStartTick(unsigned long tick)
	{
		m_SpecialBuffStartTick = tick;
	}

protected:
	virtual void OnProc(const float delta);

	void OnSPCardListInit(int param);
	void OnSPCardListOwnerDraw(int param);
	int GetRemainedSec(const sSCardAvilityPeriodInfo* info);

	FrListBox* m_pSPCardList;

	static WPoint m_Pos;
	static unsigned long m_SpecialBuffStartTick;
	DECLARE_FRESH_MSGMAP()
};
