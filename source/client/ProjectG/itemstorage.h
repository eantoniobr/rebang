#pragma once

#include <list>
#include <vector>

#include "../../shared/globalnetworkdefine.h"
#include "indexcontrol.h"

struct sItemInfo;
class FrItemStorageNotice : public FrForm
{
public:
	FrItemStorageNotice() { }
	virtual ~FrItemStorageNotice() { }

	virtual void OnProc(const float delta);
	virtual void OnDraw();
	DECLARE_OBJECT(FrItemStorageNotice)

protected:
	void OnLBDownConfirm();
	void OnOwnerDrawPrintOut(int param);

	DECLARE_FRESH_MSGMAP()
};

class FrItemStorageAccessPanel : public FrForm
{
public:
	enum eFormType
	{
		eFORM_INIT_PASSWORD,
		eFORM_INPUT_PASSWORD,
		eFORM_CHANGE_PASSWORD,
		eFORM_LOCK,
		eFORM_UNLOCK
	};

	static const int COUNT_NUMBER_SLOT = 10;
	static const int MIN_PASSWORD_LENGTH = 4;
	static const int MAX_PASSWORD_LENGTH = 4;

	FrItemStorageAccessPanel();
	virtual ~FrItemStorageAccessPanel();

protected:
	eFormType m_formType;
	int m_phase;
	char m_oldPassword[32];
	char m_password[32];
	char m_confirmPassword[32];
	unsigned char m_slotNumber[COUNT_NUMBER_SLOT];
	FrArea* m_pPrintOut;
	FrButton* m_pNumberSlot[COUNT_NUMBER_SLOT];
	FrButton* m_pConfirm;
	FrButton* m_pCancel;

	template <typename T>
	bool TBindControl(T*& pControl, int param)
	{
		pControl = DYNAMIC_CAST(T, param);

		return pControl != NULL;
	}

public:
	void SetFormType(eFormType type)
	{
		m_formType = type;

		switch (type)
		{
		case eFORM_INIT_PASSWORD:
		{
			SetCaption(
				"\xC3\xD6\xC3\xCA \xC6\xD0\xBD\xBA\xBF\xF6\xB5\xE5\xB8\xA6 \xBC\xB3\xC1\xA4\xC7\xD8\xC1\xD6\xBC\xBC\xBF\xE4.");
			SetDesc(
				"\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 4\xC0\xDA\xB8\xAE \xC0\xD4\xB7\xC2.");
			m_phase = 1;
		}
		break;
		case eFORM_INPUT_PASSWORD:
		{
			SetCaption("\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 \xC0\xD4\xB7\xC2");
			SetDesc(
				"\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 4\xC0\xDA\xB8\xAE \xC0\xD4\xB7\xC2.");
			m_phase = 1;
		}
		break;

		case eFORM_CHANGE_PASSWORD:
		{
			SetCaption("\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 \xBA\xAF\xB0\xE6");
			SetDesc(
				"\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 4\xC0\xDA\xB8\xAE \xC0\xD4\xB7\xC2.");
			m_phase = 0;
		}
		break;

		case eFORM_LOCK:
		{
			SetCaption("\xC0\xE1\xB1\xDD\xBC\xB3\xC1\xA4");
			SetDesc(
				"\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 4\xC0\xDA\xB8\xAE \xC0\xD4\xB7\xC2.");
			m_phase = 1;
		}
		break;

		case eFORM_UNLOCK:
		{
			SetCaption("\xC0\xE1\xB1\xDD\xC7\xD8\xC1\xA6");
			SetDesc(
				"\xBA\xF1\xB9\xD0\xB9\xF8\xC8\xA3 4\xC0\xDA\xB8\xAE \xC0\xD4\xB7\xC2.");
			m_phase = 1;
		}
		break;

		default:
			LogOut(0, "FrItemStorageAccessPanel::SetFormType %d\n", type);
			break;
		}
	}
	eFormType GetFormType() const { return m_formType; }

protected:
	void OnInitPrintOut(int param);
	void OnOwnerDrawPrintOut(int param);

	DECLARE_OBJECT(FrItemStorageAccessPanel)

	void SendPasswordToServer();

protected:
	bool InputPassword(unsigned char slot);
	bool DiffPassword();
	void SetButtonImage(FrButton* pButton, unsigned char slot);

	void OnInitNumberSlot0(int param);
	void OnInitNumberSlot1(int param);
	void OnInitNumberSlot2(int param);
	void OnInitNumberSlot3(int param);
	void OnInitNumberSlot4(int param);
	void OnInitNumberSlot5(int param);
	void OnInitNumberSlot6(int param);
	void OnInitNumberSlot7(int param);
	void OnInitNumberSlot8(int param);
	void OnInitNumberSlot9(int param);
	void OnLBDownNumberSlot0();
	void OnLBDownNumberSlot1();
	void OnLBDownNumberSlot2();
	void OnLBDownNumberSlot3();
	void OnLBDownNumberSlot4();
	void OnLBDownNumberSlot5();
	void OnLBDownNumberSlot6();
	void OnLBDownNumberSlot7();
	void OnLBDownNumberSlot8();
	void OnLBDownNumberSlot9();
	void OnInitConfirm(int param);
	void OnLBDownConfirm();
	void OnInitCancel(int param);
	void OnLBDownCancel();

	DECLARE_FRESH_MSGMAP()
};

class FrItemCounter : public FrForm
{
public:
	FrItemCounter();
	virtual ~FrItemCounter();

protected:
	void OnInitDrawArea(int param);
	void OnOwnerDrawDrawArea(int param);
	void OnInitInput(int param);
	void OnInitConfirm(int param);
	void OnLBDownConfirm();
	void OnInitCancel(int param);
	void OnLBDownCancel();

	FrArea* m_pDrawArea;
	FrEdit* m_pInput;
	FrButton* m_pConfirm;
	FrButton* m_pCancel;
	unsigned long m_type;
	sStoredItemInfo m_storedItemInfo;

	DECLARE_OBJECT(FrItemCounter)

	void SetStoredItemInfo(const sStoredItemInfo& info)
	{
		m_storedItemInfo = info;
	}
	const sStoredItemInfo& GetStoredItemInfo() const
	{
		return m_storedItemInfo;
	}

	void SetType(unsigned long type)
	{
		m_type = type;

		switch (type)
		{
		case 1:
		{
			SetCaption(
				"\xBE\xC6\xC0\xCC\xC5\xDB \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2");
			SetDesc(
				"\xB0\xA1\xC1\xAE\xBF\xC3 \xBE\xC6\xC0\xCC\xC5\xDB\xC0\xC7 \xBC\xF6\xB7\xAE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4.");
		}
		break;

		case 0:
		{
			SetCaption(
				"\xBE\xC6\xC0\xCC\xC5\xDB \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2");
			SetDesc(
				"\xBA\xB8\xB0\xFC\xC7\xD2 \xBE\xC6\xC0\xCC\xC5\xDB\xC0\xC7 \xBC\xF6\xB7\xAE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4.");
		}
		break;
		}
	}
	unsigned long GetType() const { return m_type; }

	DECLARE_FRESH_MSGMAP()
};

class FrItemConfirm : public FrForm
{
public:
	FrItemConfirm();
	virtual ~FrItemConfirm();

protected:
	void OnInitDrawArea(int param);
	void OnOwnerDrawDrawArea(int param);
	void OnInitConfirm(int param);
	void OnLBDownConfirm();
	void OnInitCancel(int param);
	void OnLBDownCancel();

	FrArea* m_pDrawArea;
	FrButton* m_pConfirm;
	FrButton* m_pCancel;
	unsigned long m_type;
	sStoredItemInfo m_storedItemInfo;

	DECLARE_OBJECT(FrItemConfirm)

	void SetStoredItemInfo(const sStoredItemInfo& info)
	{
		m_storedItemInfo = info;
	}
	const sStoredItemInfo& GetStoredItemInfo() const
	{
		return m_storedItemInfo;
	}
	void SetType(unsigned long type)
	{
		m_type = type;

		switch (type)
		{
		case 1:
		{
			SetCaption(
				"\xBE\xC6\xC0\xCC\xC5\xDB \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2");
			SetDesc(
				"\xBE\xC6\xC0\xCC\xC5\xDB\xC0\xBB \xC3\xA2\xB0\xED\xBF\xA1\xBC\xAD \xB0\xA1\xC1\xAE\xBF\xC9\xB4\xCF\xB4\xD9.");
		}
		break;

		case 0:
		{
			SetCaption(
				"\xBE\xC6\xC0\xCC\xC5\xDB \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2");
			SetDesc(
				"\xBE\xC6\xC0\xCC\xC5\xDB\xC0\xBB \xC3\xA2\xB0\xED\xBF\xA1 \xBA\xB8\xB0\xFC\xC7\xD5\xB4\xCF\xB4\xD9.");
		}
		break;
		}
	}
	unsigned long GetType() const { return m_type; }

	DECLARE_FRESH_MSGMAP()
};

class FrItemStoragePangBank : public FrForm
{
public:
	enum eType
	{
		eTYPE_STORE,
		eTYPE_TAKE
	};

	FrItemStoragePangBank();
	virtual ~FrItemStoragePangBank();

protected:
	void OnInitDrawArea(int param);
	void OnOwnerDrawDrawArea(int param);
	void OnInitInput(int param);
	bool OnInputEnterKey(int param);
	void OnInitConfirm(int param);
	void OnLBDownConfirm();
	void OnInitCancel(int param);
	void OnLBDownCancel();

	FrArea* m_pDrawArea;
	FrEdit* m_pInput;
	FrButton* m_pConfirm;
	FrButton* m_pCancel;
	unsigned long m_type;
	__int64 m_storedPang;
	__int64 m_myPang;

public:
	void SetStoredPang(__int64 pang) { m_storedPang = pang; }
	__int64 GetStoredPang() const { return m_storedPang; }
	void SetMyPang(__int64 pang) { m_myPang = pang; }
	__int64 GetMyPang() const { return m_myPang; }

	void SetType(unsigned long type)
	{
		m_type = type;

		switch (type)
		{
		case 1:
		{
			SetCaption("\xC6\xCE \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2");
			SetDesc(
				"\xB0\xA1\xC1\xAE\xBF\xC3 \xC6\xCE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4.");
		}
		break;

		case 0:
		{
			SetCaption("\xC6\xCE \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2");
			SetDesc(
				"\xBA\xB8\xB0\xFC\xC7\xD2 \xC6\xCE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4.");
		}
		break;
		}
	}
	unsigned long GetType() const { return m_type; }

	DECLARE_OBJECT(FrItemStoragePangBank)

	DECLARE_FRESH_MSGMAP()
};

struct sStoredItemDragDrop
{
	enum MODE
	{
		MODE_NONE,
		MODE_ITEM_LIST,
		MODE_STORAGE_LIST
	};

	MODE mode;
	WPoint mouse;
	unsigned long index;
	sItemInfo* pItemInfo;
	sStoredItemInfo storedItemInfo;
};

class CItemStorage : public WSingleton<CItemStorage>, public FrCmdTarget
{
public:
	CItemStorage();
	virtual ~CItemStorage();

	void Lock();
	void UnLock();

	bool IsVisible() const { return m_bVisible; }

	bool IsLock() const { return m_bLock; }

	void AddFrontUI(FrWnd* pWnd);
	void AddBackGroundUI(FrWnd* pWnd, bool bVisible);
	void SetVisibleFrontUI(bool bVisible);
	void SetVisibleBackGroundUI(bool bVisible);
	void SetEnableFrontUI(bool bEnable);
	void SetEnableBackGroundUI(bool bEnable);

	void Print(float x, float y, const char* text, float width, int align,
		float scale, unsigned long color);

	void ClearStoredItemInfo();
	void AddStoredItemInfo(const sStoredItemInfo& info);
	bool CheckEquiped(unsigned long id);
	bool CheckStoredItemInfo(sStoredItemInfo& storedItemInfo,
		const sItemInfo& itemInfo);
	void ReqPopStoredItemInfo(const FrListItem& item);
	void ReqPopStoredItemInfo(const sStoredItemInfo& info);
	void ReqPushStoredItemInfo(const FrListItem& item);
	void ReqPushStoredItemInfo(const sItemInfo& info);

	void DrawBackgroundImage();
	void MakeStoredItemInfo(FrListBox*& pListBox);
	void DrawStoredItemInfo(const FrListBox*& pListBox, const FrListItem& item);

	void SetTotalPage(unsigned long page) { m_totalPage = page; }
	unsigned long GetTotalPage() const { return m_totalPage; }
	void SetCurPage(unsigned long page) { m_curPage = page; }
	unsigned long GetCurPage() const { return m_curPage; }
	CIndexControl* GetIndexControl() { return m_pIndexControl; }
	void InitIndexControl(unsigned long totalIndex, unsigned long indexPerPage);
	void IndexControlClick();
	void IndexControlNext();
	void IndexControlPrev();
	void IndexControlDraw(WPoint& pos);
	bool NeedPageIndexer();

	void SetStoredPang(__int64 pang)
	{
		// NOFORMAT
		m_storedPang = pang;
	}
	__int64 GetStoredPang() const
	{
		// NOFORMAT
		return m_storedPang;
	}
	void OpenPangBank(FrItemStoragePangBank::eType type);
	bool OnResultPangBank(int result, FrForm* pForm);
	bool OnResultItemCounter(int result, FrForm* pForm);
	bool OnResultItemConfirm(int result, FrForm* pForm);

	void SetDragDropItem(sStoredItemDragDrop& item);
	void SetDrag(sStoredItemDragDrop::MODE mode);
	void DragDropItemDraw();
	unsigned long GetDragingItemIndex(sStoredItemDragDrop::MODE mode);

protected:
	bool CheckDrag();
	bool CheckDrop();

public:
	void SetItemStorageArea(WRect rect) { m_itemStorageArea = rect; }
	void SetItemListArea(WRect rect) { m_itemListArea = rect; }

protected:
	bool m_bVisible;
	bool m_bLock;
	std::list<FrWnd*> m_frontUI;
	std::list<FrWnd*> m_backEnableUI;
	std::list<FrWnd*> m_backVisibleUI;
	WTitleFont* m_pTitleFont;
	__int64 m_storedPang;
	unsigned long m_totalPage;
	unsigned long m_curPage;
	CIndexControl* m_pIndexControl;
	std::vector<sStoredItemInfo*> m_storedItemList;
	std::vector<sItemInfo*> m_uccItemList;
	FrItemStoragePangBank* m_pPangBank;
	FrItemCounter* m_pItemCounter;
	FrItemConfirm* m_pItemConfirm;
	WRect m_itemStorageArea;
	WRect m_itemListArea;
	sStoredItemDragDrop m_dragDrop;
};
