#pragma once

#include <list>
#include <map>
#include "frform.h"
#include "frtextbutton.h"
#include "frlistbox.h"
#include "../../shared/recycletable.h"

class CSimpleUI;
class CExhibition;
class FrSelectPartDlg;
class WTitleFont;
struct sItemInfo;
class FrRecycleDlg : public FrForm
{
	DECLARE_OBJECT(FrRecycleDlg)

	FrRecycleDlg();
	virtual ~FrRecycleDlg();

	struct MiniBtn
	{
		WRect rect;
		const Bitmap* pBitmap;
		int index;
	};

	void InitDataCharacterSelect();
	void InitListCharacterSelect();
	void InitPositionItemData();
	void SetListRecycleItem(int level, int character);
	void SetDataTotalItem(int index);
	void SetMaxEnableRecycle(int index);
	void ControlRecycleNumber(int mode);
	void EnableMixControls(bool bEnable);
	void EnableTotalControls(bool bEnable);
	void ClickRecycleItem();
	void SendDataRecycleItem(int index, int count);
	void SetResultRecycleItem(bool bSuccess, std::list<sRecycleItem>& items,
		short index);
	void SetCadieMessage(const char* msg);
	bool SetEventMessage(int type);
	void OpenInformation(unsigned long typeId);
	bool IsHaveItem(unsigned long typeId);
	void DrawRecycleItem();
	void DrawArrow();
	void DrawItem(WPoint pos, unsigned long typeId, int count,
		unsigned char level, const Bitmap* pBitmap, unsigned long color);
	void DrawPartsSlot(FrGraphicInterface* pGI, sItemInfo* pItem,
		FrArea* pArea);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);
	virtual void OnCancel();

	void OnRecycleDlgInit(int param);
	void OnCloseBnInit(int param);
	void OnCloseBnUp();
	void OnAboutBnInit(int param);
	void OnAboutBnUp();
	void OnLevelLowBnInit(int param);
	void OnLevelLowBnUp();
	void OnLevelMidBnInit(int param);
	void OnLevelMidBnUp();
	void OnLevelHighBnInit(int param);
	void OnLevelHighBnUp();
	void OnLevelSpecialBnInit(int param);
	void OnLevelSpecialBnUp();
	void OnLevelEventBnInit(int param);
	void OnLevelEventBnUp();
	void OnCharacterSelectListInit(int param);
	void OnCharacterSelectListOwnerDraw(int param);
	void OnCharacterSelectListLBnUp();
	void OnRecycleItemListInit(int param);
	void OnRecycleItemListOwnerDraw(int param);
	void OnRecycleItemListLBnUp();
	void OnRecycleItemListRBnUp();
	void OnRecycleNumberInit(int param);
	bool OnRecycleNumberEnterKey(int param);
	void OnMixBnInit(int param);
	void OnMixBnUp();
	void OnArrowMinimumBnInit(int param);
	void OnArrowMinimumBnDown();
	void OnArrowLeftBnInit(int param);
	void OnArrowLeftBnDown();
	void OnArrowLeftBnUp();
	void OnArrowRightBnInit(int param);
	void OnArrowRightBnDown();
	void OnArrowRightBnUp();
	void OnArrowMaximumBnInit(int param);
	void OnArrowMaximumBnDown();
	void OnAreaPictureInit(int param);
	void OnAreaPictureOwnerDraw();
	void OnRecycleItemNameInit(int param);
	void OnCadieMessageInit(int param);
	void OnSelectPartInit(int param);
	void OnSelectPartLBDown();
	bool OnSelectPartDlgResult(int result, FrForm* pForm);
	void OnCardSlotInit(int param);
	void OnCardSlotOwnerDraw(int param);
	void OnCardSlotResultInit(int param);

private:
	void AddHaveItemMap(const sRecycleItem* pItem);
	bool IsHaveItem(const sRecycleItem* pItem);
	bool IsUsableParts(sItemInfo& item);
	void ReInitializeHaveItem();

protected:
	FrButton* m_pCloseBn;
	FrButton* m_pLevelLowBn;
	FrButton* m_pLevelMidBn;
	FrButton* m_pLevelHighBn;
	FrButton* m_pLevelSpecialBn;
	FrButton* m_pLevelEventBn;
	FrListBox* m_pCharacterSelectList;
	FrListBox* m_pRecycleItemList;
	FrEdit* m_pRecycleNumber;
	FrButton* m_pMixBn;
	FrButton* m_pArrowMinimumBn;
	FrButton* m_pArrowLeftBn;
	FrButton* m_pArrowRightBn;
	FrButton* m_pArrowMaximumBn;
	FrEdit* m_pRecycleItemName;
	FrEdit* m_pCadieMessage;
	WTitleFont* m_pFont;
	const Bitmap* m_pItemBn[2];
	CSimpleUI* m_pSimpleUI;
	int m_listLevel;
	unsigned long m_characterTypeId[10];
	int m_selRecycleIndex;
	int m_selCharacter;
	int m_level;
	sRecycleItem m_totalItem;
	sRecycleItem m_needItem[4];
	sRecycleItem m_haveItem[4];
	int m_recycleNumber;
	int m_maxRecycleNumber;
	sRecycleItem m_resultItem;
	WPoint m_totalPos;
	WPoint m_needPos[4];
	WPoint m_havePos[4];
	WPoint m_resultPos;
	CExhibition* m_pExhibition;
	bool m_bArrowLeftDown;
	bool m_bArrowRightDown;
	float m_arrowRepeat;
	bool m_bMixing;
	int m_arrowState[2];
	float m_arrowBlink[2];
	float m_sendDelay;
	float m_resultTime;
	float m_messageTime;
	unsigned long m_selTypeId;
	unsigned long m_selPartId;
	bool m_bPartSelected;
	bool m_bReserved;
	int m_reserved[2];
	FrButton* m_pSelectPartBn;
	FrArea* m_pCardSlot;
	FrArea* m_pCardSlotResult;
	FrSelectPartDlg* m_pSelectPartDlg;
	MiniBtn m_unusedBtn[3];
	MiniBtn m_deleteIcon;
	MiniBtn m_clockIcon;
	MiniBtn m_unusedBtn2[3];
	std::map<const sRecycleItem*, int> m_haveItemMap;

	DECLARE_FRESH_MSGMAP()
};

class FrRecycleAboutDlg : public FrForm
{
	DECLARE_OBJECT(FrRecycleAboutDlg)

	FrRecycleAboutDlg();
	virtual ~FrRecycleAboutDlg();

	void SetImgAboutIndex(int index);

protected:
	virtual bool OnInit();

	void OnAboutInit(int param);
	void OnAboutViewerInit(int param);
	void OnIndex01Init(int param);
	void OnIndex01BnUp();
	void OnIndex02Init(int param);
	void OnIndex02BnUp();
	void OnIndex03Init(int param);
	void OnIndex03BnUp();
	void OnIndex04Init(int param);
	void OnIndex04BnUp();
	void OnIndex05Init(int param);
	void OnIndex05BnUp();
	void OnBackwardBnInit(int param);
	void OnBackwardBnUp();
	void OnForwardBnInit(int param);
	void OnForwardBnUp();
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrTextButton* m_pIndex[5];
	int m_aboutIndex;
	FrButton* m_pBackwardBn;
	FrButton* m_pForwardBn;
	FrViewer* m_pViewer;

	DECLARE_FRESH_MSGMAP()
};

class FrSelectPartDlg : public FrForm
{
	DECLARE_OBJECT(FrSelectPartDlg)

	FrSelectPartDlg();
	virtual ~FrSelectPartDlg();

	void SetPartTID(unsigned long typeId);
	friend class FrRecycleDlg;
	void DrawPartsSlot(FrGraphicInterface* pGI, FrListItem* pItem);
	void DrawStatus2(FrGraphicInterface* pGI, FrListItem* pItem,
		short* const pStat, short* const pSlot, float alpha);

protected:
	void OnInitListBox(int param);
	void OnOwnerDrawListBox(int param);
	void OnLBUpListBox();

	FrListBox* m_pListBox;
	unsigned long m_partTypeId;
	unsigned long m_selectedId;

	DECLARE_FRESH_MSGMAP()
};
