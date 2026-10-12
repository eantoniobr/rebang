#pragma once

#include <list>
#include <vector>
#include "singleton.h"
#include "frcmdtarget.h"
#include "../../shared/globalnetworkdefine.h"
#include "wtypes.h"

struct sItemInfo;
class FrWnd;
class WTitleFont;
class CIndexControl;
class FrItemStoragePangBank;
class FrItemCounter;
class FrItemConfirm;

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
	bool IsVisible() const { return m_bVisible; }
	bool IsLock() const { return m_bLock; }

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
