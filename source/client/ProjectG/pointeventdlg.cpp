#include "pointeventdlg.h"
#include "frviewer.h"

extern Fresh* g_pFresh;

static unsigned short previousSelection = 10;
FrPointEventDlg* g_pPointEventDlg;
CCommodityTable g_CommodityTable;
CCommodityStatusManager g_CommodityStatusManager;

CCommodityItem::CCommodityItem()
{
	m_dwTid = 0;
	m_dwValue = 0;
	m_ItemType = TYPE_NULL;
}

CCommodityItem::CCommodityItem(const CCommodityItem& item)
{
	m_dwTid = item.m_dwTid;
	m_dwValue = item.m_dwValue;
	m_ItemType = item.m_ItemType;
}

CCommodityItem::CCommodityItem(unsigned long id, unsigned long value,
	eItemType type)
{
	m_dwTid = id;
	m_dwValue = value;
	m_ItemType = type;
}

void CCommodityItem::SetTypeID(unsigned long id)
{
	m_dwTid = id;
}

void CCommodityItem::SetValue(unsigned long value)
{
	m_dwValue = value;
}

void CCommodityItem::SetItemType(eItemType type)
{
	m_ItemType = type;
}

unsigned long CCommodityItem::GetTypeID() const
{
	return m_dwTid;
}

unsigned long CCommodityItem::GetValue() const
{
	return m_dwValue;
}

CCommodityItem::eItemType CCommodityItem::GetItemType() const
{
	return m_ItemType;
}

const CCommodityItem& CCommodityItem::operator=(const CCommodityItem& item)
{
	m_dwTid = item.m_dwTid;
	m_dwValue = item.m_dwValue;
	m_ItemType = item.m_ItemType;
	return *this;
}

CCommodity::CCommodity()
{
	m_usCurItemCount = 0;
	m_usCost = 0;
}

CCommodity::CCommodity(const CCommodity& commodity)
{
	m_usCurItemCount = commodity.GetCommodityItemCount();
	for (int i = 0; i < m_usCurItemCount; ++i)
		m_Item[i] = commodity.GetCommodityItem(i);
	m_usCost = commodity.GetCommodityCost();
}

CCommodity::CCommodity(const CCommodityItem& item, unsigned short cost)
{
	m_usCurItemCount = 1;
	m_Item[0] = item;
	m_usCost = cost;
}

void CCommodity::SetCommodityCost(unsigned short cost)
{
	m_usCost = cost;
}

unsigned short CCommodity::GetCommodityItemCount() const
{
	return m_usCurItemCount;
}

unsigned short CCommodity::GetCommodityCost() const
{
	return m_usCost;
}

bool CCommodity::InsertCommodityItem(const CCommodityItem& item)
{
	if (m_usCurItemCount >= MAX_ITEM_COUNT)
		return false;
	m_Item[m_usCurItemCount] = item;
	++m_usCurItemCount;
	return true;
}

const CCommodityItem& CCommodity::GetCommodityItem(unsigned short idxItem) const
{
	return m_Item[idxItem];
}

const CCommodity& CCommodity::operator=(const CCommodity& commodity)
{
	m_usCurItemCount = commodity.GetCommodityItemCount();
	for (int i = 0; i < m_usCurItemCount; ++i)
		m_Item[i] = commodity.GetCommodityItem(i);
	m_usCost = commodity.GetCommodityCost();
	return *this;
}

CCommodityTable::CCommodityTable()
{
	InitializeTable();
}

bool CCommodityTable::InitializeTable()
{
	CCommodity commodity[MAX_COMMODITY_COUNT];
	commodity[0].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[0].SetCommodityCost(600);
	commodity[1].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[1].SetCommodityCost(600);
	commodity[2].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[2].SetCommodityCost(600);
	commodity[3].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[3].SetCommodityCost(600);
	commodity[4].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[4].SetCommodityCost(600);
	commodity[5].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[5].SetCommodityCost(600);
	commodity[6].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[6].SetCommodityCost(600);
	commodity[7].InsertCommodityItem(
		CCommodityItem(0, 0, CCommodityItem::TYPE_VOTE));
	commodity[7].SetCommodityCost(300);
	commodity[8].InsertCommodityItem(
		CCommodityItem(0x1a000010, 3000, CCommodityItem::TYPE_PANG));
	commodity[8].SetCommodityCost(150);
	commodity[9].InsertCommodityItem(
		CCommodityItem(0x1a00003f, 1, CCommodityItem::TYPE_CONTRIBUTION));
	commodity[9].SetCommodityCost(100);
	for (int i = 0; i < MAX_COMMODITY_COUNT; ++i)
		m_Commodity[i] = commodity[i];
	return true;
}

const CCommodity& CCommodityTable::GetCommodity(
	unsigned short idxCommodity) const
{
	if (idxCommodity > MAX_COMMODITY_COUNT)
		idxCommodity = 0;
	return m_Commodity[idxCommodity];
}

CCommodityStatusManager::CCommodityStatusManager()
{
	m_pStatus = NULL;
	InitializeStatus();
}

CCommodityStatusManager::~CCommodityStatusManager()
{
	if (m_pStatus)
	{
		delete[] m_pStatus;
		m_pStatus = NULL;
	}
}

void CCommodityStatusManager::InitializeStatus()
{
	if (!m_pStatus)
	{
		m_pStatus = new sCommodityStatus[MAX_COMMODITY_COUNT];
		for (int i = 0; i < MAX_COMMODITY_COUNT; ++i)
		{
			m_pStatus[i].myCount = 0;
			m_pStatus[i].totalCount = 0;
			m_pStatus[i].status = 0;
		}
	}
	m_updateType[0] = UPDATE_MAX;
	m_updateType[1] = UPDATE_MAX;
	m_updateType[2] = UPDATE_MAX;
	m_updateType[3] = UPDATE_MAX;
	m_updateType[4] = UPDATE_MAX;
	m_updateType[5] = UPDATE_MAX;
	m_updateType[6] = UPDATE_MAX;
	m_updateType[7] = UPDATE_MAX;
	m_updateType[8] = UPDATE_NONE;
	m_updateType[9] = UPDATE_MAX;
}

unsigned long CCommodityStatusManager::GetStatus(unsigned short index) const
{
	return m_pStatus[index].status;
}

unsigned long CCommodityStatusManager::GetMyCount(unsigned short index) const
{
	return m_pStatus[index].myCount;
}

unsigned long CCommodityStatusManager::GetTotalCount(unsigned short index) const
{
	return m_pStatus[index].totalCount;
}

CCommodityStatusManager::eUpdateType CCommodityStatusManager::GetUpdateType(
	unsigned short index) const
{
	return m_updateType[index];
}

void CCommodityStatusManager::SetStatus(unsigned short index,
	unsigned long status)
{
	m_pStatus[index].status = status;
}

void CCommodityStatusManager::SetMyCount(unsigned short index,
	unsigned long count)
{
	m_pStatus[index].myCount = count;
}

void CCommodityStatusManager::SetTotalCount(unsigned short index,
	unsigned long count)
{
	m_pStatus[index].totalCount = count;
}

void CCommodityStatusManager::SetData(unsigned short index,
	unsigned long status, unsigned long myCount, unsigned long totalCount)
{
	m_pStatus[index].status = status;
	m_pStatus[index].myCount = myCount;
	m_pStatus[index].totalCount = totalCount;
}

void CCommodityStatusManager::UpdateTotalCount(unsigned short index,
	unsigned long count)
{
	switch (m_updateType[index])
	{
	case UPDATE_MAX:
		if (m_pStatus[index].totalCount <= count)
			m_pStatus[index].totalCount = count;
		break;
	case UPDATE_MIN:
		if (m_pStatus[index].totalCount >= count ||
			m_pStatus[index].totalCount == 0)
			m_pStatus[index].totalCount = count;
		break;
	case UPDATE_REPLACE:
		m_pStatus[index].totalCount = count;
		break;
	}
}

void CCommodityStatusManager::UpdateStatus(unsigned short index,
	unsigned long status)
{
	m_pStatus[index].status = status;
}

void CCommodityStatusManager::UpdateMyCount(unsigned short index,
	unsigned long count)
{
	m_pStatus[index].myCount = count;
}

CCommodityButton::CCommodityButton()
{
	m_buttonType = BUTTON_NONE;
	m_pButton = NULL;
	m_pCover = NULL;
	m_coverPos = WPoint(0.0f, 0.0f);
}

CCommodityButton::~CCommodityButton()
{
}

CCommodityButton::eCommodityButtonType CCommodityButton::GetButtonType() const
{
	return m_buttonType;
}

bool CCommodityButton::IsVisible() const
{
	return m_pButton->IsVisible();
}

bool CCommodityButton::BindButton(FrButton* pButton)
{
	if (!pButton)
		return false;
	m_pButton = pButton;
	pButton->SetPushDelay(0.1f);
	return true;
}

void CCommodityButton::SetCover(const char* name)
{
	if (m_pButton)
	{
		m_pCover = NULL;
		m_pCover = g_pFresh->GetBitmap(name);
		m_coverPos.x = m_pButton->GetRect().x;
		m_coverPos.y = m_pButton->GetRect().y;
	}
}

void CCommodityButton::ChangeButtonType(eCommodityButtonType type)
{
	if (!m_pButton)
		return;
	switch (type)
	{
	case BUTTON_GIFT1:
		m_pButton->SetButtonImg("btn_pointevent_gift1_n", FrButton::NORMAL);
		m_pButton->SetButtonImg("btn_pointevent_gift1_o", FrButton::OVER);
		m_pButton->SetButtonImg("btn_pointevent_gift1_d", FrButton::PRESSED);
		m_buttonType = BUTTON_GIFT1;
		break;
	case BUTTON_GIFT2:
		m_pButton->SetButtonImg("btn_pointevent_gift2_n", FrButton::NORMAL);
		m_pButton->SetButtonImg("btn_pointevent_gift2_o", FrButton::OVER);
		m_pButton->SetButtonImg("btn_pointevent_gift2_d", FrButton::PRESSED);
		m_buttonType = BUTTON_GIFT2;
		break;
	case BUTTON_CONTRIBUTION:
		m_buttonType = BUTTON_CONTRIBUTION;
		break;
	}
}

void CCommodityButton::ButtonSwitch(bool bEnable)
{
	if (m_pButton)
		m_pButton->SetVisible(bEnable);
}

void CCommodityButton::DrawCover()
{
	FrGraphicInterface* graphic = g_pFresh->GetManager()->GetGDI();
	if (graphic && IsVisible() && m_pCover)
	{
		m_coverPos.x = m_pButton->GetRect().x;
		m_coverPos.y = m_pButton->GetRect().y;
		int space = graphic->SetSpace(0);
		graphic->DrawTexture(m_pCover,
			WRect(m_coverPos.x, m_coverPos.y, (float)m_pCover->Width(),
				(float)m_pCover->Height()),
			0xffffffff, 0);
		graphic->SetSpace(space);
	}
}

CCommoditySlot::CCommoditySlot()
{
	m_slotIndex = 0;
	m_slotStatus = SLOT_ENABLE;
	m_pSoldOutMark = NULL;
	m_pGiftMark = NULL;
	m_myCount = 0;
	m_totalCount = 0;
	m_myCountPos = WPoint(0.0f, 0.0f);
	m_totalCountPos = WPoint(0.0f, 0.0f);
	m_markPos = WPoint(0.0f, 0.0f);
	m_linkCount = 0;
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
		m_pLink[i] = NULL;
}

CCommoditySlot::~CCommoditySlot()
{
}

void CCommoditySlot::InitSlot(sCommoditySlotData& data)
{
	m_slotIndex = data.slotIndex;
	m_slotStatus = SLOT_ENABLE;
	m_pSoldOutMark = g_pFresh->GetBitmap(data.soldOutMark);
	m_pGiftMark = g_pFresh->GetBitmap(data.giftMark);
	m_countFlag = data.countFlag;
	m_markFlag = data.markFlag;
	m_myCountPos = data.myCountPos;
	m_totalCountPos = data.totalCountPos;
	m_markPos = data.markPos;
	BindButton(data.pButton);
	SetCover(data.cover);
	ChangeButtonType(data.buttonType);
	m_linkCount = 0;
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
		m_pLink[i] = NULL;
}

void CCommoditySlot::SetMyCount(unsigned long count)
{
	m_myCount = count;
}

void CCommoditySlot::SetTotalCount(unsigned long count)
{
	m_totalCount = count;
}

void CCommoditySlot::SetSlotStatus(eSlotStatus status)
{
	m_slotStatus = status;
	switch (status)
	{
	case SLOT_ENABLE:
		ButtonSwitch(true);
		break;
	case SLOT_SOLDOUT:
		ButtonSwitch(false);
		break;
	case SLOT_RECEIVED:
		ButtonSwitch(false);
		break;
	case SLOT_DISABLE:
		ButtonSwitch(false);
		break;
	}
}

unsigned short CCommoditySlot::GetSlotIndex() const
{
	return m_slotIndex;
}

CCommoditySlot::eSlotStatus CCommoditySlot::GetSlotStatus() const
{
	return m_slotStatus;
}

WRect CCommoditySlot::GetButtonRect() const
{
	WRect rect = m_pButton->GetRect();
	return rect;
}

void CCommoditySlot::AddSlotLink(const CCommoditySlot* pSlot)
{
	if (pSlot && m_linkCount < MAX_COMMODITY_SLOT_COUNT)
		m_pLink[m_linkCount++] = pSlot;
}

void CCommoditySlot::Process()
{
	for (int i = 0; i < m_linkCount; ++i)
	{
		if (m_pLink[i] && m_pLink[i]->GetSlotStatus() == SLOT_RECEIVED)
			SetSlotStatus(SLOT_DISABLE);
	}
}

void CCommoditySlot::DrawSlot(WPoint pos)
{
	FrGraphicInterface* graphic = g_pFresh->GetManager()->GetGDI();
	if (!graphic)
		return;
	int space = graphic->SetSpace(0);
	graphic->SetTextStyle(1);
	switch (m_countFlag)
	{
	case 1:
		graphic->Print(pos + m_myCountPos, 2, "%d", m_myCount);
		break;
	case 2:
		graphic->Print(pos + m_totalCountPos, 2, "%d", m_totalCount);
		break;
	case 3:
		graphic->Print(pos + m_myCountPos, 2, "%d", m_myCount);
		graphic->Print(pos + m_totalCountPos, 2, "%d", m_totalCount);
		break;
	}
	graphic->SetTextStyle(0);
	switch (m_slotStatus)
	{
	case SLOT_SOLDOUT:
		if (m_pSoldOutMark && (m_markFlag & 1))
			graphic->DrawTexture(m_pSoldOutMark,
				WRect(pos.x + m_markPos.x, pos.y + m_markPos.y,
					(float)m_pSoldOutMark->Width(),
					(float)m_pSoldOutMark->Height()),
				0xffffffff, 0);
		break;
	case SLOT_RECEIVED:
		if (m_pGiftMark && (m_markFlag & 2))
			graphic->DrawTexture(m_pGiftMark,
				WRect(pos.x + m_markPos.x, pos.y + m_markPos.y,
					(float)m_pGiftMark->Width(), (float)m_pGiftMark->Height()),
				0xffffffff, 0);
	}
	graphic->SetSpace(space);
}

IMPLEMENT_OBJECT(FrPointEventNoticeDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrPointEventNoticeDlg, FrForm)
ON_FRESH_VI("yes_button", FRCMD_INIT, FrPointEventNoticeDlg::OnInitBtnYes)
ON_FRESH_VV("yes_button", FRCMD_LBUTTONUP,
	FrPointEventNoticeDlg::OnLBDownBtnYes)
ON_FRESH_VI("no_button", FRCMD_INIT, FrPointEventNoticeDlg::OnInitBtnNo)
ON_FRESH_VV("no_button", FRCMD_LBUTTONUP, FrPointEventNoticeDlg::OnLBDownBtnNo)
ON_FRESH_VI("draw_area", FRCMD_INIT, FrPointEventNoticeDlg::OnInitDrawArea)
ON_FRESH_VI("draw_area", FRCMD_OWNERDRAW,
	FrPointEventNoticeDlg::OnOwnerDrawDrawArea)
END_FRESH_MSGMAP()

FrPointEventNoticeDlg::FrPointEventNoticeDlg()
	: m_pBtnYes(NULL),
	  m_pBtnNo(NULL),
	  m_pDrawArea(NULL),
	  m_commodityIndex(0),
	  m_pItemImage(NULL),
	  m_type(0)
{
}

FrPointEventNoticeDlg::~FrPointEventNoticeDlg()
{
}

void FrPointEventNoticeDlg::OnInitBtnYes(int param)
{
	m_pBtnYes = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnYes->SetPushDelay(0.0f);
}

void FrPointEventNoticeDlg::OnLBDownBtnYes()
{
	Close(FrOK, true);
}

void FrPointEventNoticeDlg::OnInitBtnNo(int param)
{
	m_pBtnNo = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnNo->SetPushDelay(0.0f);
}

void FrPointEventNoticeDlg::OnLBDownBtnNo()
{
	Close(FrCANCEL, true);
}

void FrPointEventNoticeDlg::SetCommodity(int index, unsigned long type)
{
	m_commodityIndex = index;
	if (index + 1 < 10)
		m_pItemImage =
			g_pFresh->GetBitmap(MakeStr("pointevent_item_0%d", index + 1));
	else
		m_pItemImage =
			g_pFresh->GetBitmap(MakeStr("pointevent_item_%d", index + 1));
	m_type = type;
}

void FrPointEventNoticeDlg::OnInitDrawArea(int param)
{
	m_pDrawArea = DYNAMIC_CAST(FrArea, (FrWnd*)param);
}

void FrPointEventNoticeDlg::OnOwnerDrawDrawArea(int param)
{
	FrGraphicInterface* graphic = g_pFresh->GetManager()->GetGDI();
	if (!graphic)
		return;
	int space = graphic->SetSpace(0);
	WRect pos = m_rect;
	if (m_pItemImage)
		graphic->DrawTexture(m_pItemImage,
			WRect(pos.x + 48.0f, pos.y + 41.0f, m_pItemImage->Width(),
				m_pItemImage->Height()),
			0xffffffff, 0);
	graphic->SetTextStyle(1);
	switch (m_type)
	{
	case 0:
		graphic->Print(WPoint(pos.x + 69.0f, pos.y + 153.0f), 0,
			"\xc0\xbb \xc1\xf6\xb1\xde\xb9\xde\xc0\xb8\xbd\xc3\xb0\xda\xbd\xc0\xb4\xcf\xb1\xee?");
		break;
	case 1:
		graphic->Print(WPoint(pos.x + 69.0f, pos.y + 153.0f), 0,
			"\xc0\xbb \xc0\xc0\xb8\xf0\xc7\xcf\xbd\xc3\xb0\xda\xbd\xc0\xb4\xcf\xb1\xee?");
		break;
	case 2:
		graphic->Print(WPoint(pos.x + 53.0f, pos.y + 153.0f), 0,
			"\xc0\xbb \xc1\xf6\xb1\xde\xb9\xde\xb0\xed 100\xc6\xf7\xc0\xce\xc6\xae \xb1\xe2\xba\xce\xc7\xd5\xb4\xcf\xb4\xd9.");
		break;
	}
	graphic->SetTextStyle(0);
	graphic->SetSpace(space);
}

bool FrPointEventNoticeDlg::OnInit()
{
	return true;
}

IMPLEMENT_OBJECT(FrPointEventDescDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrPointEventDescDlg, FrForm)
ON_FRESH_VI("desc_view", FRCMD_INIT, FrPointEventDescDlg::OnInitDescViewer)
END_FRESH_MSGMAP()

FrPointEventDescDlg::FrPointEventDescDlg()
{
	m_pDescViewer = NULL;
	memset(m_szDescImage, 0, sizeof(m_szDescImage));
}

FrPointEventDescDlg::~FrPointEventDescDlg()
{
}

void FrPointEventDescDlg::SetDescImage(const char* filename)
{
	if (m_pDescViewer)
	{
		memset(m_szDescImage, 0, sizeof(m_szDescImage));
		strcpy(m_szDescImage, filename);
		m_pDescViewer->ShowScrollBar(true);
		m_pDescViewer->Open(m_szDescImage);
	}
}

void FrPointEventDescDlg::OnInitDescViewer(int param)
{
	m_pDescViewer = DYNAMIC_CAST(FrViewer, (FrWnd*)param);
}

IMPLEMENT_OBJECT(FrPointEventDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrPointEventDlg, FrForm)
ON_FRESH_VI("desc_button", FRCMD_INIT, FrPointEventDlg::OnInitDescButton)
ON_FRESH_VV("desc_button", FRCMD_LBUTTONUP, FrPointEventDlg::OnLBDownDescButton)
ON_FRESH_VI("cover_area", FRCMD_OWNERDRAW,
	FrPointEventDlg::OnOwnerDrawCoverArea)
ON_FRESH_VI("commodity_button01", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity01)
ON_FRESH_VV("commodity_button01", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity01)
ON_FRESH_VI("commodity_button02", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity02)
ON_FRESH_VV("commodity_button02", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity02)
ON_FRESH_VI("commodity_button03", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity03)
ON_FRESH_VV("commodity_button03", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity03)
ON_FRESH_VI("commodity_button04", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity04)
ON_FRESH_VV("commodity_button04", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity04)
ON_FRESH_VI("commodity_button05", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity05)
ON_FRESH_VV("commodity_button05", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity05)
ON_FRESH_VI("commodity_button06", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity06)
ON_FRESH_VV("commodity_button06", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity06)
ON_FRESH_VI("commodity_button07", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity07)
ON_FRESH_VV("commodity_button07", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity07)
ON_FRESH_VI("commodity_button08", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity08)
ON_FRESH_VV("commodity_button08", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity08)
ON_FRESH_VI("commodity_button09", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnCommodity09)
ON_FRESH_VV("commodity_button09", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnCommodity09)
ON_FRESH_VI("data_area", FRCMD_OWNERDRAW, FrPointEventDlg::OnOwnerDrawDataArea)
ON_FRESH_VI("contribution_area", FRCMD_OWNERDRAW,
	FrPointEventDlg::OnOwnerDrawContribution)
ON_FRESH_VI("contribution_desc", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnDescContribution)
ON_FRESH_VV("contribution_desc", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnDescContribution)
ON_FRESH_VI("contribution_button", FRCMD_INIT,
	FrPointEventDlg::OnInitBtnContribution)
ON_FRESH_VV("contribution_button", FRCMD_LBUTTONUP,
	FrPointEventDlg::OnLBDownBtnContribution)
END_FRESH_MSGMAP()

FrPointEventDlg::FrPointEventDlg()
{
	m_elapsed = 0.0f;
	m_pDescButton = NULL;
	m_pDescDlg = NULL;
	m_pNoticeDlg = NULL;
	m_myPoint = 0;
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
		m_pBtnCommodity[i] = NULL;
	g_pPointEventDlg = this;
	m_contribution = 0.0f;
	m_pBtnDescContribution = NULL;
	m_pContributionGage = NULL;
	m_pContributionGageBg = NULL;
	memset(m_pContributionFrame, 0, sizeof(m_pContributionFrame));
	m_pIconSuccess = NULL;
}

FrPointEventDlg::~FrPointEventDlg()
{
	g_pPointEventDlg = NULL;
}

void FrPointEventDlg::OnInitDescButton(int param)
{
	if (!m_pDescButton)
		m_pDescButton = DYNAMIC_CAST(FrButton, (FrWnd*)param);
}

void FrPointEventDlg::OnLBDownDescButton()
{
	if (!m_pDescDlg)
		m_pDescDlg = CreateForm<FrPointEventDescDlg>(g_pFresh->GetManager(),
			this, "point_event_desc");
	if (!m_pDescDlg)
		return;
	m_pDescDlg->SetDescImage("point_event_explanation.jpg");
	m_pDescDlg->SetIconRect(m_pDescButton->GetRect());
	m_pDescDlg->Open(
		(FRESH_PFN_RESULT)&FrPointEventDlg::OnPointEventDescDlgResult, 0x11);
}

void FrPointEventDlg::OnOwnerDrawCoverArea(int param)
{
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
		m_commoditySlot[i].DrawCover();
}

void FrPointEventDlg::OnInitBtnCommodity01(int param)
{
	m_pBtnCommodity[0] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[0]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity02(int param)
{
	m_pBtnCommodity[1] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[1]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity03(int param)
{
	m_pBtnCommodity[2] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[2]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity04(int param)
{
	m_pBtnCommodity[3] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[3]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity05(int param)
{
	m_pBtnCommodity[4] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[4]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity06(int param)
{
	m_pBtnCommodity[5] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[5]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity07(int param)
{
	m_pBtnCommodity[6] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[6]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity08(int param)
{
	m_pBtnCommodity[7] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[7]->SetVisible(false);
}

void FrPointEventDlg::OnInitBtnCommodity09(int param)
{
	m_pBtnCommodity[8] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	m_pBtnCommodity[8]->SetVisible(false);
}

void FrPointEventDlg::OnLBDownBtnCommodity01()
{
	Confirm(0);
}

void FrPointEventDlg::OnLBDownBtnCommodity02()
{
	Confirm(1);
}

void FrPointEventDlg::OnLBDownBtnCommodity03()
{
	Confirm(2);
}

void FrPointEventDlg::OnLBDownBtnCommodity04()
{
	Confirm(3);
}

void FrPointEventDlg::OnLBDownBtnCommodity05()
{
	Confirm(4);
}

void FrPointEventDlg::OnLBDownBtnCommodity06()
{
	Confirm(5);
}

void FrPointEventDlg::OnLBDownBtnCommodity07()
{
	Confirm(6);
}

void FrPointEventDlg::OnLBDownBtnCommodity08()
{
	Confirm(7);
}

void FrPointEventDlg::OnLBDownBtnCommodity09()
{
	Confirm(8);
}

void FrPointEventDlg::OnOwnerDrawDataArea(int param)
{
	FrGraphicInterface* graphic = g_pFresh->GetManager()->GetGDI();
	if (!graphic)
		return;
	WRect pos = m_rect;
	int space = graphic->SetSpace(0);
	graphic->SetTextStyle(1);
	graphic->Print(WPoint(pos.x + 507.0f, pos.y + 73.0f), 2, "%d", m_myPoint);
	graphic->SetTextStyle(0);
	graphic->SetSpace(space);
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
		m_commoditySlot[i].DrawSlot(pos.TopLeft());
}

bool FrPointEventDlg::OnPointEventDescDlgResult(int result, FrForm* pForm)
{
	m_pDescDlg = NULL;
	return true;
}

bool FrPointEventDlg::OnPointEventNoticeDlgResult(int result, FrForm* pForm)
{
	m_pNoticeDlg = NULL;
	if (result == FrOK)
	{
		WSendPacket packet((enumClientPacket)0x8a);
		packet.Encode4(m_selectCommodity);
		packet.Send(TO_GAME);
	}
	else
	{
		UnSelectCommodity();
	}
	return true;
}

bool FrPointEventDlg::OnInit()
{
	SendUpdateDataPacket();
	// clang-format off
	CCommoditySlot::sCommoditySlotData slotData[MAX_COMMODITY_SLOT_COUNT] = {
		{ 0, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(166.0f, 285.0f), WPoint(166.0f, 297.0f), WPoint(130.0f, 252.0f), m_pBtnCommodity[0], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 1, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(330.0f, 285.0f), WPoint(330.0f, 297.0f), WPoint(295.0f, 252.0f), m_pBtnCommodity[1], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 2, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(494.0f, 285.0f), WPoint(494.0f, 297.0f), WPoint(459.0f, 252.0f), m_pBtnCommodity[2], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 3, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(166.0f, 391.0f), WPoint(166.0f, 403.0f), WPoint(130.0f, 358.0f), m_pBtnCommodity[3], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 4, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(330.0f, 391.0f), WPoint(330.0f, 403.0f), WPoint(295.0f, 358.0f), m_pBtnCommodity[4], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 5, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(494.0f, 391.0f), WPoint(494.0f, 403.0f), WPoint(459.0f, 358.0f), m_pBtnCommodity[5], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 6, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(166.0f, 496.0f), WPoint(166.0f, 508.0f), WPoint(130.0f, 462.0f), m_pBtnCommodity[6], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 7, 3, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(330.0f, 496.0f), WPoint(330.0f, 508.0f), WPoint(295.0f, 462.0f), m_pBtnCommodity[7], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT2 },
		{ 8, 0, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(494.0f, 496.0f), WPoint(494.0f, 508.0f), WPoint(459.0f, 462.0f), m_pBtnCommodity[8], "btn_pointevent_white", CCommodityButton::BUTTON_GIFT1 },
		{ 9, 0, 0, "pointevent_soldout_mark", "pointevent_gift_mark", WPoint(494.0f, 496.0f), WPoint(494.0f, 508.0f), WPoint(459.0f, 462.0f), m_pBtnCommodity[9], "contribution_btn_white", CCommodityButton::BUTTON_CONTRIBUTION },
	};
	// clang-format on
	for (int i = 0; i < MAX_COMMODITY_SLOT_COUNT; ++i)
	{
		m_commoditySlot[i].InitSlot(slotData[i]);
	}
	m_selectCommodity = MAX_COMMODITY_SLOT_COUNT;
	if (IsLocalContent((localContentType_t)22))
	{
		WRect rect = m_rect;
		rect.x -= 50.0f;
		SetRect(rect);
		m_pContributionGage = g_pFresh->GetBitmap("contribution_gage");
		m_pContributionGageBg =
			g_pFresh->GetBitmap("contribution_gage_background");
		m_pContributionFrame[0] = g_pFresh->GetBitmap("contribution_frame_01");
		m_pContributionFrame[1] = g_pFresh->GetBitmap("contribution_frame_02");
		m_pIconSuccess = g_pFresh->GetBitmap("icon_success");
	}
	return true;
}

void FrPointEventDlg::OnProc(const float delta)
{
	m_elapsed += delta;
	if (m_elapsed > 10.0f)
	{
		SendUpdateDataPacket();
		m_elapsed = 0.0f;
	}
	SetMyPoint(Doc()->m_myInfo.info.dwPointPointEvent);
	int count = MAX_COMMODITY_SLOT_COUNT;
	if (!IsLocalContent((localContentType_t)22))
		count = 9;
	for (int i = 0; i < count; ++i)
	{
		CCommodity commodity = g_CommodityTable.GetCommodity(i);
		m_commoditySlot[i].SetMyCount(g_CommodityStatusManager.GetMyCount(i));
		m_commoditySlot[i].SetTotalCount(
			g_CommodityStatusManager.GetTotalCount(i));
		bool disabled = false;
		if (GetMyPoint() >= commodity.GetCommodityCost())
			m_commoditySlot[i].SetSlotStatus(CCommoditySlot::SLOT_ENABLE);
		else
		{
			m_commoditySlot[i].SetSlotStatus(CCommoditySlot::SLOT_DISABLE);
			disabled = true;
		}
		switch (g_CommodityStatusManager.GetStatus(i))
		{
		case 0:
			if (!disabled)
				m_commoditySlot[i].SetSlotStatus(CCommoditySlot::SLOT_ENABLE);
			break;
		case 1:
			m_commoditySlot[i].SetSlotStatus(CCommoditySlot::SLOT_RECEIVED);
			break;
		case 2:
			m_commoditySlot[i].SetSlotStatus(CCommoditySlot::SLOT_SOLDOUT);
			break;
		}
		m_commoditySlot[i].Process();
	}
}

void FrPointEventDlg::Confirm(unsigned long index)
{
	previousSelection = m_selectCommodity;
	if (previousSelection != MAX_COMMODITY_SLOT_COUNT)
	{
		FrForm* form =
			CreateForm<FrForm>(g_pFresh->GetManager(), this, "notify");
		form->SetTimeLimit(3.0f);
		form->SetMessage(
			" \xc0\xe1\xbd\xc3\xc8\xc4\xbf\xa1 \xb4\xd9\xbd\xc3 \xbd\xc3\xb5\xb5 \xc7\xd8\xc1\xd6\xbd\xca\xbd\xc3\xbf\xc0. ",
			false);
		form->Open(NULL, 0);
		return;
	}
	m_selectCommodity = index;
	if (!m_pNoticeDlg)
		m_pNoticeDlg = CreateForm<FrPointEventNoticeDlg>(g_pFresh->GetManager(),
			this, "point_event_notice");
	if (m_pNoticeDlg)
	{
		unsigned long type = 0;
		switch (m_commoditySlot[index].GetButtonType())
		{
		case CCommodityButton::BUTTON_GIFT2:
			type = 1;
			break;
		case CCommodityButton::BUTTON_CONTRIBUTION:
			type = 2;
			break;
		case CCommodityButton::BUTTON_GIFT1:
		case CCommodityButton::BUTTON_NONE:
			type = 0;
			break;
		}
		m_pNoticeDlg->SetCommodity(m_selectCommodity, type);
		m_pNoticeDlg->SetIconRect(
			m_commoditySlot[m_selectCommodity].GetButtonRect());
		m_pNoticeDlg->Open(
			(FRESH_PFN_RESULT)&FrPointEventDlg::OnPointEventNoticeDlgResult,
			0x11);
	}
}

void FrPointEventDlg::ResultMessage(unsigned long result)
{
	FrForm* form = CreateForm<FrForm>(g_pFresh->GetManager(), this, "notify");
	WRect rect = form->GetRect();
	form->SetRect(WRect(rect.x, rect.y, rect.w, rect.h));
	form->SetTimeLimit(12.0f);
	if (m_selectCommodity >= MAX_COMMODITY_SLOT_COUNT)
		return;
	switch (result)
	{
	case 0:
		switch (m_commoditySlot[m_selectCommodity].GetButtonType())
		{
		case CCommodityButton::BUTTON_GIFT1:
		{
			form->SetMessage(
				"\xbc\xba\xb0\xf8\xc0\xfb\xc0\xb8\xb7\xce \xbb\xf3\xc7\xb0\xc0\xbb \xc1\xf6\xb1\xde \xb9\xde\xbe\xd2\xbd\xc0\xb4\xcf\xb4\xd9.",
				false);
			WSendPacket packet(0x21);
			const char* nick = Doc()->m_myInfo.info.sNick;
			packet.EncodeStr(std::string(nick));
			unsigned long uid = Doc()->m_myInfo.info.dwUID;
			packet.Encode4(uid);
			packet.Send(TO_MSN);
			break;
		}
		case CCommodityButton::BUTTON_GIFT2:
		{
			form->SetMessage(
				"\xbc\xba\xb0\xf8\xc0\xfb\xc0\xb8\xb7\xce \xbb\xf3\xc7\xb0\xc0\xbb \xc0\xc0\xb8\xf0 \xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				false);
			break;
		}
		case CCommodityButton::BUTTON_CONTRIBUTION:
		{
			form->SetMessage(
				"\xbc\xba\xb0\xf8\xc0\xfb\xc0\xb8\xb7\xce \xb1\xe2\xba\xce \xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				false);
			WSendPacket packet(0x21);
			const char* nick = Doc()->m_myInfo.info.sNick;
			packet.EncodeStr(std::string(nick));
			unsigned long uid = Doc()->m_myInfo.info.dwUID;
			packet.Encode4(uid);
			packet.Send(TO_MSN);
			break;
		}
		}
		LocalDataUpdate(m_selectCommodity);
		break;
	case 1:
	case 4:
		switch (m_commoditySlot[m_selectCommodity].GetButtonType())
		{
		case CCommodityButton::BUTTON_GIFT1:
			form->SetMessage(
				"\xc6\xf7\xc0\xce\xc6\xae\xb0\xa1 \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9.",
				false);
			break;
		case CCommodityButton::BUTTON_GIFT2:
			form->SetMessage(
				"\xc6\xf7\xc0\xce\xc6\xae\xb0\xa1 \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9.",
				false);
			break;
		case CCommodityButton::BUTTON_CONTRIBUTION:
			form->SetMessage(
				"\xc6\xf7\xc0\xce\xc6\xae\xb0\xa1 \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9.",
				false);
			break;
		}
		break;
	case 2:
	case 3:
		switch (m_commoditySlot[m_selectCommodity].GetButtonType())
		{
		case CCommodityButton::BUTTON_GIFT1:
			form->SetMessage(
				"\xc0\xcc\xb9\xcc \xc1\xf6\xb1\xde\xb9\xde\xc0\xba \xbb\xf3\xc7\xb0\xc0\xd4\xb4\xcf\xb4\xd9.",
				false);
			break;
		case CCommodityButton::BUTTON_GIFT2:
			form->SetMessage(
				"\xc0\xcc\xb9\xcc \xc0\xc0\xb8\xf0\xc7\xd1 \xbb\xf3\xc7\xb0\xc0\xd4\xb4\xcf\xb4\xd9.",
				false);
			break;
		case CCommodityButton::BUTTON_CONTRIBUTION:
			form->SetMessage(
				"\xb1\xe2\xba\xce \xc7\xd2 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9. \xc0\xe1\xbd\xc3 \xc8\xc4 \xb4\xd9\xbd\xc3 \xbd\xc3\xb5\xb5 \xc7\xd8 \xc1\xd6\xbd\xca\xbd\xc3\xbf\xc0",
				false);
			break;
		}
		break;
	}
	form->Open(NULL, 0);
	UnSelectCommodity();
}

void FrPointEventDlg::UnSelectCommodity()
{
	m_selectCommodity = MAX_COMMODITY_SLOT_COUNT;
}

void FrPointEventDlg::SendUpdateDataPacket()
{
	WSendPacket packet((enumClientPacket)0x8b);
	packet.Send(TO_GAME);
}

void FrPointEventDlg::LocalDataUpdate(unsigned short index)
{
	unsigned long myCount = g_CommodityStatusManager.GetMyCount(index);
	unsigned long totalCount = g_CommodityStatusManager.GetTotalCount(index);
	switch (m_commoditySlot[index].GetButtonType())
	{
	case CCommodityButton::BUTTON_GIFT1:
		++myCount;
		if (totalCount > 0)
			--totalCount;
		g_CommodityStatusManager.SetMyCount(index, myCount);
		g_CommodityStatusManager.SetTotalCount(index, totalCount);
		break;
	case CCommodityButton::BUTTON_GIFT2:
		g_CommodityStatusManager.SetMyCount(index, myCount + 1);
		g_CommodityStatusManager.SetTotalCount(index, totalCount + 1);
		break;
	case CCommodityButton::BUTTON_CONTRIBUTION:
		g_CommodityStatusManager.SetMyCount(index, myCount + 1);
		g_CommodityStatusManager.SetTotalCount(index, totalCount + 100);
		break;
	}
	CCommodity commodity = g_CommodityTable.GetCommodity(index);
	m_myPoint -= commodity.GetCommodityCost();
}

void FrPointEventDlg::OnOwnerDrawContribution(int param)
{
	if (!IsLocalContent((localContentType_t)22))
		return;
	FrGraphicInterface* graphic = g_pFresh->GetManager()->GetGDI();
	if (!graphic)
		return;
	int space = graphic->SetSpace(0);
	unsigned long success = 0;
	WRect pos = m_rect;
	m_contribution = (float)g_CommodityStatusManager.GetTotalCount(9);
	unsigned long contribution = (int)(m_contribution * 0.01f);
	float height;
	if (contribution < m_iPangDouble1)
	{
		height = contribution * (36.5f / m_iPangDouble1);
	}
	else if (contribution < m_iExpDouble)
	{
		contribution -= m_iPangDouble1;
		height = contribution * (36.5f / m_iExpDouble) + 36.5f;
		if (contribution < 100)
			success = 2;
	}
	else if (contribution < m_iPangDouble2)
	{
		contribution -= m_iExpDouble;
		height = contribution * (36.5f / m_iPangDouble2) + 73.0f;
		if (contribution < 100)
			success = 3;
	}
	else if (contribution < m_iMaxContribution)
	{
		contribution -= m_iPangDouble2;
		height =
			contribution * (36.5f / (m_iMaxContribution - m_iPangDouble2)) +
			109.5f;
		if (contribution < 100)
			success = 4;
	}
	else
	{
		height = 146.0f;
		success = 5;
	}
	graphic->DrawTexture(m_pContributionGageBg,
		WRect(pos.x + 604.0f, pos.y + 372.0f - 146.0f,
			(float)m_pContributionGage->Width(), 146.0f),
		0xffffffff, 0);
	graphic->DrawTexture(m_pContributionGage,
		WRect(pos.x + 604.0f, (float)(pos.y + 373.0f - height),
			(float)m_pContributionGage->Width(), height + 1.0f),
		0xffffffff, 0);
	graphic->DrawTexture(m_pContributionFrame[0],
		WRect(pos.x + 522.0f, pos.y + 130.0f,
			(float)m_pContributionFrame[0]->Width(),
			(float)m_pContributionFrame[0]->Height()),
		0xffffffff, 0);
	graphic->DrawTexture(m_pContributionFrame[1],
		WRect(pos.x + 522.0f, pos.y + 386.0f,
			(float)m_pContributionFrame[1]->Width(),
			(float)m_pContributionFrame[1]->Height()),
		0xffffffff, 0);
	if (success)
		graphic->DrawTexture(m_pIconSuccess,
			WRect(pos.x + 617.0f, pos.y + 366.0f - success * 36.5f,
				(float)m_pIconSuccess->Width(),
				(float)m_pIconSuccess->Height()),
			0xffffffff, 0);
	graphic->SetSpace(space);
}

void FrPointEventDlg::OnInitBtnDescContribution(int param)
{
	m_pBtnDescContribution = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	if (!IsLocalContent((localContentType_t)22))
	{
		m_pBtnDescContribution->SetVisible(false);
		m_pBtnDescContribution->Enable(false);
		return;
	}
	m_pBtnDescContribution->SetPushDelay(0.0f);
}

void FrPointEventDlg::OnLBDownBtnDescContribution()
{
	if (!IsLocalContent((localContentType_t)22))
		return;
	if (!m_pDescDlg)
		m_pDescDlg = CreateForm<FrPointEventDescDlg>(g_pFresh->GetManager(),
			this, "point_event_desc");
	if (!m_pDescDlg)
		return;
	m_pDescDlg->SetDescImage("point_event_explanation_02.jpg");
	m_pDescDlg->SetIconRect(m_pBtnDescContribution->GetRect());
	m_pDescDlg->Open(
		(FRESH_PFN_RESULT)&FrPointEventDlg::OnPointEventDescDlgResult, 0x11);
}

void FrPointEventDlg::OnInitBtnContribution(int param)
{
	m_pBtnCommodity[9] = DYNAMIC_CAST(FrButton, (FrWnd*)param);
	if (!IsLocalContent((localContentType_t)22))
	{
		m_pBtnCommodity[9]->SetVisible(false);
		return;
	}
	m_pBtnCommodity[0]->SetVisible(false);
	m_pBtnCommodity[9]->SetPushDelay(0.0f);
}

void FrPointEventDlg::OnLBDownBtnContribution()
{
	if (IsLocalContent((localContentType_t)22))
		Confirm(9);
}
