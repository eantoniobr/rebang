#pragma once

#include <string>
#include <vector>
#include "frform.h"
#include "titlefontex.h"
#include "wtemplate.h"

class FrEdit;
class FrListBox;
struct FrListItem;
class FrButton;
struct sItemInfo;
struct sCards;
struct _sPrivateTradeItem;
struct _sPrivateTradeItemSingle;
class FrMyWareHouse;
class FrTradeToolTip;
class FrPrivateTradeWnd;

struct sWarpItem
{
	sWarpItem(const sWarpItem* item);
	sWarpItem(const sItemInfo& item);
	sWarpItem(const sCards& card);

	void SetIcon(unsigned long typeId);

	unsigned long typeId;
	unsigned long id;
	const Bitmap* pIcon;
	std::string name;
	WRect iconRect;
	int count;
};

struct sTradeDropItem
{
	sTradeDropItem()
		: id(0), typeId(0), count(1)
	{
	}
	sTradeDropItem(unsigned long _id, unsigned long _typeId)
		: id(_id), typeId(_typeId), count(1)
	{
	}

	unsigned long id;
	unsigned long typeId;
	int count;
};

class CTradeDragDrop
{
	friend class FrPrivateTrade;

public:
	CTradeDragDrop();
	virtual ~CTradeDragDrop();

	static bool IsPoped();
	static void Cancel();
	static void Drop(CTradeDragDrop* target);

	virtual bool Pop();
	const sTradeDropItem* GetDropItem();

protected:
	virtual bool DropItemUp() = 0;
	virtual bool DropItemDown() = 0;
	virtual void DropItemMoved() = 0;
	virtual void SetPopItem(const sTradeDropItem& item);

private:
	static CTradeDragDrop* m_pCaller;
	static sTradeDropItem* m_pItem;
};

class FrNumEdit : public FrForm
{
	DECLARE_OBJECT(FrNumEdit)
	FrNumEdit();
	virtual ~FrNumEdit();

	void SetEditRange(unsigned long min, unsigned long max);
	void SetValue(unsigned long value);

	void OnViewDraw();
	void OnEditInit(int param);
	bool OnEditEnter(int param);

	unsigned long GetValue() const { return m_value; }

	void SetReturnParam(void* param) { m_pReturnParam = param; }
	void* GetReturnParam() { return m_pReturnParam; }

protected:
	virtual void OnProc(const float delta);

	FrEdit* m_pEdit;
	unsigned long m_value;
	void* m_pReturnParam;
	unsigned long m_min;
	unsigned long m_max;

private:
	DECLARE_FRESH_MSGMAP()
};

class FrPangEdit : public FrForm
{
	DECLARE_OBJECT(FrPangEdit)
	FrPangEdit();
	virtual ~FrPangEdit();

	void SetPangValue(__int64 pang);

	void OnViewDraw();
	void OnEditInit(int param);
	bool OnEditEnter(int param);

	void SetTexRate(unsigned char rate) { m_texRate = rate; }
	__int64 GetTex() { return m_pang * m_texRate / 100; }
	__int64 GetPangValue() const { return m_pang; }

protected:
	virtual void OnProc(const float delta);

	FrEdit* m_pEdit;
	__int64 m_pang;
	unsigned char m_texRate;

private:
	DECLARE_FRESH_MSGMAP()
};

class EncapsulatedPang : public CWindFont
{
public:
	enum eStyle
	{
		STYLE_BAR = 2,
		STYLE_ICON = 4,
		STYLE_HOVER = 8
	};

	EncapsulatedPang();
	virtual ~EncapsulatedPang();

	void SetRect(const WRect& rect);
	__int64 GetPang() const { return m_pang; }
	const WRect* GetRectPtr() const { return m_pRect; }
	int IsStyle(eStyle style);
	int SubPang(__int64 pang);
	void AddPangBarStyle(eStyle style);
	void SetPang(__int64 pang) { m_pang = pang; }

protected:
	void DrawPang();

	__int64 m_pang;
	WRect* m_pRect;
	int m_style;
};
enum eSetItemButton
{
	SIB_PART,
	SIB_CLUB,
	SIB_ITEM,
	SIB_CARD
};
enum eSetSortType
{
	SST_ALL
};

class FrMyWareHouse : public FrForm,
					  public CTradeDragDrop,
					  public EncapsulatedPang
{
	DECLARE_OBJECT(FrMyWareHouse)
	FrMyWareHouse();
	virtual ~FrMyWareHouse();

	virtual bool OnInit();
	virtual void OnProc(const float delta);

	bool AddListItem(unsigned long id, unsigned long typeId, int count);
	bool SetListItem(unsigned long id, unsigned long typeId, int count);
	bool SubListItemCount(unsigned long id, unsigned long typeId, int count);
	bool AddListItemCount(unsigned long id, unsigned long typeId, int count);
	int GetListItemCount(unsigned long id, unsigned long typeId);
	bool EraseListItem(unsigned long id, unsigned long typeId);

protected:
	virtual bool DropItemUp();
	virtual bool DropItemDown();
	virtual void DropItemMoved();

	void OnViewDraw();
	void OnSortInit(int param);
	void OnSortDraw(int param);
	void OnSortDown(int param);
	void OnListInit(int param);
	void OnListDraw(int param);
	void OnListDblClick();
	void OnPartBtnInit(int param);
	void OnClubBtnInit(int param);
	void OnItemBtnInit(int param);
	void OnCardBtnInit(int param);
	void OnPartBtnDown();
	void OnClubBtnDown();
	void OnItemBtnDown();
	void OnCardBtnDown();

private:
	FrListItem* FindListItem(unsigned long id, unsigned long typeId);
	void InitSortList(eSetItemButton button);
	void SetButtonStyle(int param, eSetItemButton button);
	void UnPushedButtonAll();
	void SetItemList(eSetItemButton button, eSetSortType sort);

	std::vector<sWarpItem*> m_items;
	std::vector<FrButton*> m_buttons;
	FrListBox* m_pList;
	FrListBox* m_pSortList;
	eSetItemButton m_curButton;

	DECLARE_FRESH_MSGMAP()
};

class FrTradeToolTip : public FrForm
{
	DECLARE_OBJECT(FrTradeToolTip)
	FrTradeToolTip();
	virtual ~FrTradeToolTip();

	void SetToolTip(_sPrivateTradeItemSingle* item);
	void SetDragItem(const sTradeDropItem* item);

	void SetDragDraw(int draw) { m_dragDraw = draw; }

protected:
	virtual void OnProc(const float delta);

	void OnViewDraw();
	void OnTextListInit(int param);
	void OnTextListDraw(int param);

private:
	void MakeFormatText(const std::string& text,
		std::vector<std::string>& lines, int width);

	float m_alpha;
	FrListBox* m_pTextList;
	const Bitmap* m_pIcon;
	std::vector<std::string> m_text;
	_sPrivateTradeItemSingle* m_pItem;
	int m_dragDraw;
	const sTradeDropItem* m_pDragItem;

	DECLARE_FRESH_MSGMAP()
};

class FrPrivateTradeWnd : public FrForm,
						  public CTradeDragDrop,
						  public EncapsulatedPang
{
	DECLARE_OBJECT(FrPrivateTradeWnd)
	FrPrivateTradeWnd();
	virtual ~FrPrivateTradeWnd();

	virtual bool OnInit();

	void SetAvatarIndex(int index);
	void GetTradeItems(_sPrivateTradeItem& items);
	void OnUpdateTradeItem(const _sPrivateTradeItem& items);
	void AddItem(const sTradeDropItem* item);
	void SubItem(const sTradeDropItem* item);
	void DoConfirm();
	void DoPermit();
	void DoTradeUnLock();
	bool OnResultEditPang(int result, FrForm* form);
	bool OnResultEditNum(int result, FrForm* form);

protected:
	virtual bool DropItemUp();
	virtual bool DropItemDown();
	virtual void DropItemMoved();
	virtual void OnProc(const float delta);

	void OnViewDraw();
	void OnListInit(int param);
	void OnListDraw(int param);
	void OnListDown();
	void OnListDblClick();
	void OnSendItemUpdate();
	void OpenPangEditWnd();
	void OpenNumEditWnd(int index);

public:
	void SetNick(const std::string& nick) { m_nick = nick; }

protected:
	void OnNumEditBtn01Init(int param);
	void OnNumEditBtn02Init(int param);
	void OnNumEditBtn03Init(int param);
	void OnNumEditBtn04Init(int param);
	void OnNumEditBtn01Down();
	void OnNumEditBtn02Down();
	void OnNumEditBtn03Down();
	void OnNumEditBtn04Down();

public:
	void EnableActiveControl(bool bEnable) { m_bActiveControl = bEnable; }

protected:
	std::string m_nick;
	int m_avatarIndex;
	FrListBox* m_pList;
	FrPangEdit* m_pPangEdit;
	std::vector<FrButton*> m_numEditBtn;
	FrNumEdit* m_pNumEdit;
	bool m_bActiveControl;
	unsigned char m_confirmState;
	_sPrivateTradeItem* m_pTradeItem;

private:
	DECLARE_FRESH_MSGMAP()
};

class FrPrivateTrade : public FrForm, public EncapsulatedPang
{
	DECLARE_OBJECT(FrPrivateTrade)
	FrPrivateTrade();
	virtual ~FrPrivateTrade();

	virtual bool OnInit();

	void SetCompanion(const std::string& nick, unsigned long guid,
		unsigned long typeId);
	void GetMyTradeItems(_sPrivateTradeItem& items);
	void MoveItem(const char* from, const void* item);
	void UpdateFrTradeItem(const _sPrivateTradeItem& items);
	void FinalFrWait(const _sPrivateTradeItem& items);
	void FinalFrOK(const _sPrivateTradeItem& items);
	void ButtonContolByConfirmCancel();
	void SetTradeUnLockAll();

protected:
	virtual void OnProc(const float delta);

	void OnViewDraw();
	void OnInitConfirmBtn(int param);
	void OnInitPermitBtn(int param);
	void OnInitCancelBtn(int param);
	void OnDownConfirmBtn();
	void OnDownPermitBtn();
	void OnDownCancelBtn();

	FrPrivateTradeWnd* m_pYourWnd;
	FrPrivateTradeWnd* m_pMyWnd;
	FrTradeToolTip* m_pToolTip;
	FrMyWareHouse* m_pWareHouse;
	const sTradeDropItem* m_pDropItem;
	FrButton* m_pConfirmBtn;
	FrButton* m_pPermitBtn;
	FrButton* m_pCancelBtn;
	std::string m_companionNick;
	unsigned long m_companionGuid;
	unsigned long m_companionTypeId;

private:
	DECLARE_FRESH_MSGMAP()
};

struct _sPrivateTradeItemSingle
{
	unsigned long id;
	unsigned long typeId;
	unsigned short count;
	struct
	{
		unsigned long typeId;
		unsigned long id;
		int ability;
		int abilityValue;
		int slotNum;
		int cardType;
	} card[8];
	short c[5];
};

struct _sPrivateTradeItem
{
	__int64 pang;
	_sPrivateTradeItemSingle item[4];
};
