#include "frticketexchangedlg.h"
#include "frviewer.h"

extern Fresh* g_pFresh;

namespace nsTicketHelper
{
	unsigned long Combine(unsigned long type, unsigned long index)
	{
		return type | index;
	}
	void Analyze(unsigned long& id, unsigned long& type, unsigned long& index)
	{
		type = id & 0xffff0000;
		index = id & 0xffff;
	}
}

IMPLEMENT_OBJECT(FrTicketExchangeDescDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrTicketExchangeDescDlg, FrForm)
ON_FRESH_VI("desc_view", FRCMD_INIT, FrTicketExchangeDescDlg::OnInitDescViewer)
END_FRESH_MSGMAP()

FrTicketExchangeDescDlg::FrTicketExchangeDescDlg()
{
	m_pDescViewer = NULL;
	memset(m_descImage, 0, sizeof(m_descImage));
}

FrTicketExchangeDescDlg::~FrTicketExchangeDescDlg()
{
}

void FrTicketExchangeDescDlg::SetDescImage(const char* image)
{
	if (m_pDescViewer)
	{
		memset(m_descImage, 0, sizeof(m_descImage));
		strcpy(m_descImage, image);
		m_pDescViewer->ShowScrollBar(true);
		m_pDescViewer->Open(m_descImage);
	}
}

void FrTicketExchangeDescDlg::OnInitDescViewer(int obj)
{
	m_pDescViewer = DYNAMIC_CAST(FrViewer, obj);
}

IMPLEMENT_OBJECT(FrTicketExchangeDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrTicketExchangeDlg, FrForm)
ON_FRESH_VI("num_0", FRCMD_INIT, FrTicketExchangeDlg::onInit_Number_0)
ON_FRESH_VI("num_1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Number_1)
ON_FRESH_VI("num_2", FRCMD_INIT, FrTicketExchangeDlg::onInit_Number_2)
ON_FRESH_VI("num_3", FRCMD_INIT, FrTicketExchangeDlg::onInit_Number_3)
ON_FRESH_VV("help", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_Help)
ON_FRESH_VI("icon_0", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_0)
ON_FRESH_VI("icon_1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_1)
ON_FRESH_VI("icon_2", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_2)
ON_FRESH_VI("icon_3", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_3)
ON_FRESH_VI("icon_4", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_4)
ON_FRESH_VI("icon_5", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_5)
ON_FRESH_VI("icon_6", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_6)
ON_FRESH_VI("icon_7", FRCMD_INIT, FrTicketExchangeDlg::onInit_Icon_7)
ON_FRESH_VI("ent_b0", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemE0)
ON_FRESH_VV("ent_b0", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemE0)
ON_FRESH_VI("ent_0e0", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0E0)
ON_FRESH_VI("ent_1e0", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit1E0)
ON_FRESH_VI("ent_b1", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemE1)
ON_FRESH_VV("ent_b1", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemE1)
ON_FRESH_VI("ent_0e1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0E1)
ON_FRESH_VI("ent_1e1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit1E1)
ON_FRESH_VI("grp_b0", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemG0)
ON_FRESH_VV("grp_b0", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemG0)
ON_FRESH_VI("grp_0e0", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0G0)
ON_FRESH_VI("grp_b1", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemG1)
ON_FRESH_VV("grp_b1", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemG1)
ON_FRESH_VI("grp_0e1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0G1)
ON_FRESH_VI("grp_b2", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemG2)
ON_FRESH_VV("grp_b2", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemG2)
ON_FRESH_VI("grp_0e2", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0G2)
ON_FRESH_VI("grp_b3", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemG3)
ON_FRESH_VV("grp_b3", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemG3)
ON_FRESH_VI("grp_0e3", FRCMD_INIT, FrTicketExchangeDlg::onInit_Edit0G3)
ON_FRESH_VI("imd_b0", FRCMD_INIT, FrTicketExchangeDlg::onInit_ItemI0)
ON_FRESH_VV("imd_b0", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemI0)
ON_FRESH_VI("imd_b1", FRCMD_INIT, FrTicketExchangeDlg::onInit_Item_I1)
ON_FRESH_VV("imd_b1", FRCMD_LBUTTONUP, FrTicketExchangeDlg::onLBtnUp_ItemI1)
ON_FRESH_VI("grp_view0", FRCMD_INIT, FrTicketExchangeDlg::onInit_View0)
ON_FRESH_VI("grp_view1", FRCMD_INIT, FrTicketExchangeDlg::onInit_View1)
ON_FRESH_VI("grp_view2", FRCMD_INIT, FrTicketExchangeDlg::onInit_View2)
ON_FRESH_VI("grp_view3", FRCMD_INIT, FrTicketExchangeDlg::onInit_View3)
END_FRESH_MSGMAP()

FrTicketExchangeDlg::FrTicketExchangeDlg()
{
	m_pDescDlg = NULL;
	memset(m_pNumber, 0, sizeof(m_pNumber));
	new TicketInfo;
}

FrTicketExchangeDlg::~FrTicketExchangeDlg()
{
	for (std::map<unsigned long, TicketItemObject*>::iterator it =
			 m_itemMap.begin();
		it != m_itemMap.end(); it++)
	{
		if (it->second)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_itemMap.clear();
	memset(m_pNumber, 0, sizeof(m_pNumber));
	delete TicketInfo::Instance();
}

bool FrTicketExchangeDlg::OnTicketExchangeDescResult(int result, FrForm* form)
{
	m_pDescDlg = NULL;
	return true;
}

TicketItemObject* FrTicketExchangeDlg::FindItem(unsigned long id)
{
	std::map<unsigned long, TicketItemObject*>::iterator it =
		m_itemMap.find(id);
	TicketItemObject* item = NULL;
	if (it != m_itemMap.end())
		item = it->second;
	if (!item)
	{
		item = new TicketItemObject;
		m_itemMap[id] = item;
	}
	return item;
}

bool FrTicketExchangeDlg::Request(unsigned int type, unsigned long tid,
	unsigned int quantity)
{
	WSendPacket packet(0xe1);
	packet.Encode4(type);
	if (type == 0x10000 || type == 0x100000 || type == 0x1000000)
	{
		packet.Encode4(tid);
		packet.Encode4(quantity);
	}
	packet.Send(TO_GAME);
	AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 1, 0, 0, 0, 0, 0);
	return true;
}

void FrTicketExchangeDlg::Reponse(unsigned long type, unsigned char result)
{
	char message[256] = "";
	bool bNotify = true;
	switch (result)
	{
	case 0:
		switch (type)
		{
		case 0x10000:
		{
			const char* text =
				"\xc0\xc0\xb8\xf0 \xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.\x0a\xc7\xe0\xbf\xee\xc0\xbb \xb1\xe2\xbf\xf8\xc7\xd5\xb4\xcf\xb4\xd9.";
			strcpy(message, text);
		}
		break;
		case 0x100000:
			TicketInfo::Instance()->m_state = 0;
		case 0x1000000:
		{
			const char* text =
				"\xc1\xf6\xb1\xde \xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.\x0a\xbf\xec\xc6\xed\xc7\xd4\xc0\xbb \xc8\xae\xc0\xce\xc7\xd8 \xba\xb8\xbd\xca\xbd\xc3\xbf\xc0.";
			strcpy(message, text);
		}
		break;
		case 0x11110000:
			bNotify = false;
			break;
		}
		break;
	case 2:
	{
		const char* text =
			"\xc7\xd8\xb4\xe7 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xc7 \xc0\xe7\xb0\xed\xb0\xa1 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.\x0a\xb4\xd9\xbd\xc3 \xb5\xe9\xbe\xee\xbf\xc3\xb6\xa7\xb1\xee\xc1\xf6 \xb1\xe2\xb4\xd9\xb7\xc1 \xc1\xd6\xbd\xca\xbd\xc3\xbf\xc0.";
		strcpy(message, text);
	}
	break;
	case 4:
	{
		const char* text =
			"\xb1\xb3\xc8\xaf \xb0\xa1\xb4\xc9\xc7\xd1 \xc6\xbc\xc4\xcf\xc0\xcc \xc0\xfb\xbd\xc0\xb4\xcf\xb4\xd9.\x0a\xc1\xb6\xb1\xdd \xb4\xf5 \xb8\xf0\xbe\xc6\xc1\xd6\xbd\xc3\xb1\xe2 \xb9\xd9\xb6\xf8\xb4\xcf\xb4\xd9.";
		strcpy(message, text);
	}
	break;
	}
	if (bNotify)
	{
		FrForm* dlg =
			CreateForm<FrForm>(g_pFresh->GetManager(), this, "notify", NULL);
		dlg->SetTimeLimit(3.0f);
		dlg->SetMessage(message, true);
		dlg->Open(NULL, 0);
		if (result)
			return;
	}
	ApplyInformation();
}

void FrTicketExchangeDlg::ApplyInformation()
{
	if (!TicketInfo::Instance())
		return;
	char text[9] = "";
	SetCountImage(TicketInfo::Instance()->m_ticketCount);
	for (std::list<sItemInfo>::iterator it = Doc()->m_myItemList.begin();
		it != Doc()->m_myItemList.end(); it++)
	{
		if (it->tid == 0x1a0000bd)
		{
			it->Common[0] = (short)TicketInfo::Instance()->m_ticketCount;
			if (it->Common[0] < 1)
				Doc()->m_myItemList.erase(it);
			break;
		}
	}
	for (std::map<unsigned long, TicketItemObject*>::iterator it =
			 m_itemMap.begin();
		it != m_itemMap.end(); it++)
	{
		unsigned long id = it->first, type, index;
		nsTicketHelper::Analyze(id, type, index);
		switch (type)
		{
		case 0x10000:
		{
			TicketInfo::sTicketItem info =
				TicketInfo::Instance()->FindCount(it->second->get_TID());
			FrEdit* count = it->second->get_Edit(0, 0);
			FrEdit* remain = it->second->get_Edit(1, 0);
			if (!count || !remain)
				continue;
			count->ClearLine();
			remain->ClearLine();
			sprintf(text, "%d", info.count);
			count->AddText(text, false, true);
			sprintf(text, "%d", info.remain);
			remain->AddText(text, false, true);
		}
		break;
		case 0x100000:
		{
			TicketInfo::sTicketItem info =
				TicketInfo::Instance()->FindCount(it->second->get_TID());
			FrEdit* remain = it->second->get_Edit(0, 0);
			if (!remain)
				continue;
			remain->ClearLine();
			sprintf(text, "%d", info.remain);
			remain->AddText(text, false, true);
			FrButton* button = it->second->get_Button(0);
			if (!button)
				continue;
			if (info.remain == 0 || TicketInfo::Instance()->m_state == 0)
			{
				button->Enable(false);
				ChangeItemState(it->second, info.remain == 0 ? 2 : 1);
			}
			else
			{
				button->Enable(true);
				ChangeItemState(it->second, -1);
			}
		}
		break;
		}
		if (TicketInfo::Instance()->m_ticketCount == 0)
		{
			FrButton* button = it->second->get_Button(0);
			FrViewer* frame = it->second->get_Viewer(0, true);
			if (button && frame)
			{
				button->Enable(false);
				frame->Enable(true);
				frame->SetVisible(true);
			}
		}
	}
}

void FrTicketExchangeDlg::ChangeItemState(TicketItemObject* item, int state)
{
	if (!item)
		return;
	FrViewer* viewer = item->get_Viewer(0, false);
	FrViewer* frame = item->get_Viewer(0, true);
	char image[64] = "";
	switch (state)
	{
	case -1:
		viewer->Enable(false);
		viewer->SetVisible(false);
		if (frame)
		{
			frame->Enable(false);
			frame->SetVisible(false);
		}
		break;
	case 2:
		if (strlen(image) == 0)
			strcpy(image, "soldout.tga");
	case 1:
		if (strlen(image) == 0)
			strcpy(image, "payment.tga");
		viewer->Enable(true);
		viewer->SetVisible(true);
		viewer->Open(image);
		if (frame)
		{
			frame->Enable(true);
			frame->SetVisible(true);
		}
		break;
	}
}

void FrTicketExchangeDlg::SetCountImage(unsigned int count)
{
	if (count > 9999)
		count = 9999;
	char text[5] = "";
	sprintf(text, "%d", count);
	unsigned int length = strlen(text);
	WPoint pos = GetRect().TopLeft();
	WRect rect;
	rect = WRect(457.0f, 69.0f, 14.0f, 19.0f);
	rect.x += rect.w * ((4 - (float)length) * 0.5f);
	rect.x += pos.x;
	rect.y += pos.y;
	unsigned int digit = 0;
	for (int i = 0; i < 4; ++i)
	{
		char image[16] = "";
		bool show = false;
		if (digit < length)
		{
			sprintf(image, "ticket_%c.tga", text[digit++]);
			show = true;
		}
		m_pNumber[i]->Enable(show);
		m_pNumber[i]->SetVisible(show);
		m_pNumber[i]->Open(image);
		m_pNumber[i]->SetRect(rect);
		rect.x += rect.w;
	}
}

void FrTicketExchangeDlg::Auto_Initialize(unsigned int kind, unsigned int index,
	int obj, unsigned long id)
{
	TicketItemObject* item = FindItem(id);
	if (!item)
		return;
	switch (kind)
	{
	case 0:
		item->get_Button(obj);
		break;
	case 1:
		item->get_Edit(index, obj)->AddText("12345678", false, true);
		break;
	case 2:
		item->get_Viewer(obj, false);
		ChangeItemState(item, -1);
		break;
	case 3:
	{
		char image[32] = "";
		sprintf(image, "ticket_frame%d.tga", index);
		FrViewer* frame = item->get_Viewer(obj, true);
		frame->Open(image);
		frame->Enable(false);
		frame->SetVisible(false);
	}
	break;
	}
}

bool FrTicketExchangeDlg::OnInit()
{
	unsigned long tids[8] = { 0 };
	tids[0] = 0x3b9ac9f7;
	tids[1] = 0x3b9ac9f8;
	tids[2] = 0x1a00000e;
	tids[3] = 0x18000006;
	tids[4] = 0x1a000011;
	tids[5] = 0x1a000040;
	tids[6] = 0x1a0000bc;
	tids[7] = 0x1a000030;
	unsigned long quantity[8] = { 0 };
	quantity[0] = 1;
	quantity[1] = 1;
	quantity[2] = 5;
	quantity[3] = 5;
	quantity[4] = 5;
	quantity[5] = 5;
	quantity[6] = 3;
	quantity[7] = 3;
	unsigned long ids[8] = { 0 };
	ids[0] = 0x10001;
	ids[1] = 0x10002;
	ids[2] = 0x100001;
	ids[3] = 0x100002;
	ids[4] = 0x100003;
	ids[5] = 0x100004;
	ids[6] = 0x1000001;
	ids[7] = 0x1000002;
	for (unsigned int i = 0; i < 8; ++i)
	{
		TicketItemObject* item = FindItem(ids[i]);
		if (item)
		{
			item->set_TID(tids[i]);
			item->set_Quantity(quantity[i]);
		}
	}
	for (int i = 0; i < 6; ++i)
	{
		std::map<unsigned long, TicketInfo::sTicketItem>::iterator it =
			TicketInfo::Instance()->m_itemMap.find(tids[i]);
		if (it == TicketInfo::Instance()->m_itemMap.end())
		{
			TicketInfo::sTicketItem info = { 0, 0 };
			TicketInfo::Instance()->m_itemMap[tids[i]] = info;
		}
	}
	Request(0x11110000, 0, 0);
	return true;
}

void FrTicketExchangeDlg::OnProc(const float dt)
{
}

void FrTicketExchangeDlg::onLBtnUp_Help()
{
	if (!m_pDescDlg)
		m_pDescDlg = CreateForm<FrTicketExchangeDescDlg>(g_pFresh->GetManager(),
			this, "ticketexchange_desc", NULL);
	if (!m_pDescDlg)
		return;
	m_pDescDlg->SetDescImage("tiketexchange_event_explanation.jpg");
	m_pDescDlg->SetIconRect(m_pDescDlg->GetRect());
	m_pDescDlg->Open(
		(FRESH_PFN_RESULT)&FrTicketExchangeDlg::OnTicketExchangeDescResult,
		0x11);
}

void FrTicketExchangeDlg::onInit_Icon_0(int obj)
{
	Auto_Initialize(3, 1, obj, 0x10001);
}

void FrTicketExchangeDlg::onInit_Icon_1(int obj)
{
	Auto_Initialize(3, 2, obj, 0x10002);
}

void FrTicketExchangeDlg::onInit_Icon_2(int obj)
{
	Auto_Initialize(3, 3, obj, 0x100001);
}

void FrTicketExchangeDlg::onInit_Icon_3(int obj)
{
	Auto_Initialize(3, 4, obj, 0x100002);
}

void FrTicketExchangeDlg::onInit_Icon_4(int obj)
{
	Auto_Initialize(3, 5, obj, 0x100003);
}

void FrTicketExchangeDlg::onInit_Icon_5(int obj)
{
	Auto_Initialize(3, 6, obj, 0x100004);
}

void FrTicketExchangeDlg::onInit_Icon_6(int obj)
{
	Auto_Initialize(3, 7, obj, 0x1000001);
}

void FrTicketExchangeDlg::onInit_Icon_7(int obj)
{
	Auto_Initialize(3, 8, obj, 0x1000002);
}

void FrTicketExchangeDlg::onInit_ItemE0(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x10000, 1));
}

void FrTicketExchangeDlg::onLBtnUp_ItemE0()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x10000, 1));
	if (item)
		Request(0x10000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0E0(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x10000, 1));
}

void FrTicketExchangeDlg::onInit_Edit1E0(int obj)
{
	Auto_Initialize(1, 1, obj, nsTicketHelper::Combine(0x10000, 1));
}

void FrTicketExchangeDlg::onInit_ItemE1(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x10000, 2));
}

void FrTicketExchangeDlg::onLBtnUp_ItemE1()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x10000, 2));
	if (item)
		Request(0x10000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0E1(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x10000, 2));
}

void FrTicketExchangeDlg::onInit_Edit1E1(int obj)
{
	Auto_Initialize(1, 1, obj, nsTicketHelper::Combine(0x10000, 2));
}

void FrTicketExchangeDlg::onInit_ItemG0(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x100000, 1));
}

void FrTicketExchangeDlg::onLBtnUp_ItemG0()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x100000, 1));
	if (item)
		Request(0x100000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0G0(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x100000, 1));
}

void FrTicketExchangeDlg::onInit_ItemG1(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x100000, 2));
}

void FrTicketExchangeDlg::onLBtnUp_ItemG1()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x100000, 2));
	if (item)
		Request(0x100000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0G1(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x100000, 2));
}

void FrTicketExchangeDlg::onInit_ItemG2(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x100000, 3));
}

void FrTicketExchangeDlg::onLBtnUp_ItemG2()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x100000, 3));
	if (item)
		Request(0x100000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0G2(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x100000, 3));
}

void FrTicketExchangeDlg::onInit_ItemG3(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x100000, 4));
}

void FrTicketExchangeDlg::onLBtnUp_ItemG3()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x100000, 4));
	if (item)
		Request(0x100000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Edit0G3(int obj)
{
	Auto_Initialize(1, 0, obj, nsTicketHelper::Combine(0x100000, 4));
}

void FrTicketExchangeDlg::onInit_ItemI0(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x1000000, 1));
}

void FrTicketExchangeDlg::onLBtnUp_ItemI0()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x1000000, 1));
	if (item)
		Request(0x1000000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Item_I1(int obj)
{
	Auto_Initialize(0, 0, obj, nsTicketHelper::Combine(0x1000000, 2));
}

void FrTicketExchangeDlg::onLBtnUp_ItemI1()
{
	TicketItemObject* item = FindItem(nsTicketHelper::Combine(0x1000000, 2));
	if (item)
		Request(0x1000000, item->get_TID(), item->get_Quantity());
}

void FrTicketExchangeDlg::onInit_Number_0(int obj)
{
	if (!m_pNumber[0])
		m_pNumber[0] = DYNAMIC_CAST(FrViewer, obj);
}

void FrTicketExchangeDlg::onInit_Number_1(int obj)
{
	if (!m_pNumber[1])
		m_pNumber[1] = DYNAMIC_CAST(FrViewer, obj);
}

void FrTicketExchangeDlg::onInit_Number_2(int obj)
{
	if (!m_pNumber[2])
		m_pNumber[2] = DYNAMIC_CAST(FrViewer, obj);
}

void FrTicketExchangeDlg::onInit_Number_3(int obj)
{
	if (!m_pNumber[3])
		m_pNumber[3] = DYNAMIC_CAST(FrViewer, obj);
}

void FrTicketExchangeDlg::onInit_View0(int obj)
{
	Auto_Initialize(2, 0, obj, nsTicketHelper::Combine(0x100000, 1));
}

void FrTicketExchangeDlg::onInit_View1(int obj)
{
	Auto_Initialize(2, 0, obj, nsTicketHelper::Combine(0x100000, 2));
}

void FrTicketExchangeDlg::onInit_View2(int obj)
{
	Auto_Initialize(2, 0, obj, nsTicketHelper::Combine(0x100000, 3));
}

void FrTicketExchangeDlg::onInit_View3(int obj)
{
	Auto_Initialize(2, 0, obj, nsTicketHelper::Combine(0x100000, 4));
}
