#include "stdafx.h"
#include "shoptask.h"
#include "gatewayactor.h"
#include "taskmain.h"
#include "contentsdoc.h"
#include "mathconsts.h"

extern Fresh* g_pFresh;
extern int g_iRecvPacketType;

IMPLEMENT_OBJECT(CShopTask, CTask)

CShopTask::CShopTask()
{
	IActor::m_defaultSkipLayer = 0;
	IActor::m_pLayer = NULL;
}

CShopTask::~CShopTask()
{
}

void CShopTask::Init(const char* wallPaper)
{
	CTask::Init("shop_background.jpg");
	SetWhisper(false);
}

void CShopTask::Register()
{
	SetMainActor(AddActor("CShopMain", "Shop", false, ""));
	AddActor(s_gatewayActor[0], s_gatewayActor[1], false, GetRTTI()->GetName());
	CTask* task = AfxGetPreservedTask();
	if (task)
	{
		IActor* actor = task->GetActor("TutorialMain");
		if (actor)
		{
			const char* className = NULL;
			const char* name = NULL;
			actor << MsgObject(NULL, 334, (int)&className, (int)&name, 0, 0, 0);
			AddActor(className, name, false, "");
		}
	}
}

void CShopTask::Load()
{
	SetProgressBar(false);
	SetTip(false);
	if (IsLocalContent((localContentType_t)86) &&
		IsLocalContent((localContentType_t)97))
	{
		WSendPacket send((enumClientPacket)175);
		send.Encode4(MyUID());
		send.Encode1(0);
		send.Send(TO_GAME);
		if (IsLocalContent((localContentType_t)102))
		{
			WSendPacket send((enumClientPacket)196);
			send.Encode4(MyUID());
			send.Send(TO_GAME);
		}
	}
	CTask::Load();
}

void CShopTask::Process(float delta)
{
	g_pFresh->OnProcess(delta);
	CTask::Process(delta);
}

void CShopTask::Display()
{
	if (!Doc()->m_bBackgroundVideo)
		CTask::Display();
	g_pFresh->OnDisplay(Doc()->m_bBackgroundVideo != 0);
}

int CShopTask::OnPacket(WReceivedPacket& packet)
{
	unsigned short type = packet.Decode2();
	g_iRecvPacketType = type;
	switch (type)
	{
	case 0xb6:
	{
		unsigned long items[128];
		packet.Decode4();
		unsigned char count = packet.Decode1();
		count = count < 128 ? count : 128;
		for (unsigned char i = 0; i < count; ++i)
			items[i] = packet.Decode4();
		GetActor("Shop") << MsgObject(NULL, 213, (int)items, count, 0, 0, 0);
		return 1;
	}
	case 0x66:
		GetActor("Shop") << MsgObject(NULL, 2, 0, 0, 0, 0, 0);
		GetActor("Shop") << MsgObject(NULL, 192, 1, 0, 0, 0, 0);
		switch (packet.Decode4())
		{
		case 0x2f:
		{
			unsigned long tid = packet.Decode4();
			unsigned long uid = packet.Decode4();
			int count = packet.Decode4();
			int result = packet.Decode4();
			std::list<sItemInfo>::iterator it;
			for (it = Doc()->m_myItemList.begin();
				it != Doc()->m_myItemList.end(); ++it)
			{
				if (it->guid == uid && it->tid == tid)
				{
					it->Common[0] = count;
					break;
				}
			}
			if (it == Doc()->m_myItemList.end())
			{
				sItemInfo item;
				memset(&item, 0, sizeof(item));
				item.IsValid = true;
				item.tid = tid;
				item.guid = uid;
				item.Common[0] = count;
				Doc()->m_myItemList.push_back(item);
			}
			GetActor("Shop") << MsgObject(NULL, 577,
				(int)MakeStr(
					"\301\244\273\363\300\373\300\270\267\316 \261\270\270\305\260\241 \277\317\267\341\265\307\276\372\275\300\264\317\264\331.\012\272\270\263\312\275\272 %s %d\260\263\270\246 \271\336\300\270\274\314\275\300\264\317\264\331.",
					Doc()->m_itemManager.GetItemName(tid), result),
				0, 0, 0, 0);
		}
		break;
		case 0:
			Doc()->m_myInfo.stat.i64Pang = packet.Decode8();
			Doc()->m_bonusCash = packet.Decode8();
			Doc()->RefreshAllCookie();
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\301\244\273\363\300\373\300\270\267\316 \261\270\270\305\260\241 \277\317\267\341\265\307\276\372\275\300\264\317\264\331.",
				0, 0, 0, 0);
			if (IS_KINDOF(CShopTask, AfxGetTask()))
			{
				CTaskMain* shop = (CTaskMain*)AfxGetTask()->GetActor("Shop");
				if (shop && !shop->IsActiveRecycleDlg())
					shop << MsgObject(NULL, 106, 0, 0, 0, 0, 0);
			}
			break;
		case 2:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\272\270\300\257\307\317\260\355 \300\326\264\302 \306\316\300\314 \272\316\301\267\307\325\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\337\270\370\265\310 \273\363\307\260 \304\332\265\345\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\261\270\270\305\260\241 \275\307\306\320\307\317\277\264\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 4:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\314\271\314 \261\270\270\305\307\321 \271\260\260\307\300\324\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x28:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\314\271\314 \277\354\306\355\307\324\277\241 \260\241\301\366\260\355 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x29:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\301\366\261\335 \306\307\270\305\301\337\300\316 \273\363\307\260\300\324\264\317\264\331. \306\307\270\305 \277\317\267\341\265\310 \265\332\277\241 \261\270\300\324\307\317\275\307 \274\366 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2B:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\314\271\314 \265\271\307\307\264\317\300\307 \272\361\271\320\261\335\260\355\277\241 \260\241\301\366\260\355 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0xB:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\306\307\270\305\261\342\260\243\300\273 \310\256\300\316\307\330 \301\326\274\274\277\344.",
				0, 0, 0, 0);
			break;
		}

		case 9:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\306\300\314\305\333\300\307 \261\342\260\243\300\273 \310\256\300\316\307\330 \301\326\274\274\277\344.",
				0, 0, 0, 0);
			break;
		}

		case 0x10:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\261\342\260\243\301\246 \276\306\300\314\305\333\300\273 \273\347\277\353\301\337\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x11:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\260\271\274\366\301\246 \276\306\300\314\305\333\300\273 \273\347\277\353\301\337\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x15:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\321\271\370\277\241 \263\312\271\253 \270\271\300\272 \276\306\300\314\305\333\300\273 \261\270\300\324\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x17:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\272\270\300\257\307\317\260\355 \300\326\264\302 \304\355\305\260\260\241 \272\316\301\267\307\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x18:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\304\355\305\260\270\246 \276\367\265\245\300\314\306\256\307\317\264\302\265\245 \275\307\306\320\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x12:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\306\300\314\305\333\300\273 \264\365 \300\314\273\363 \261\270\300\324\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x23:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\301\241\300\314 \310\245\300\342\307\317\277\251 \301\366\261\335\300\272 \261\270\300\324\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331. \300\341\275\303 \310\304 \300\314\277\353\307\330\301\326\275\303\261\342 \271\331\266\370\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x13:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\306\307\270\305\307\317\264\302 \276\306\300\314\305\333\300\314 \276\306\264\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\303\244\263\316\270\265\274\255\272\361\275\272\260\241 \301\276\267\341\265\307\276\356 \264\365\300\314\273\363 \261\270\270\305\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x22:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\314 \276\306\300\314\305\333\300\273 \264\365 \300\314\273\363 \272\270\300\257\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2C:
		case 0x2D:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\366\300\347 \267\271\272\247\267\316\264\302 \261\270\300\324\307\322 \274\366 \276\370\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x35:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\366\300\347 \270\360\265\347 \304\263\275\254\277\241 \264\353\307\321 \301\266\310\270 \271\327 \273\347\277\353\300\314 \301\244\301\366\265\307\276\356 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;
		}
		return 1;
	case 0x68:
		GetActor("Shop") << MsgObject(NULL, 2, 0, 0, 0, 0, 0);
		GetActor("Shop") << MsgObject(NULL, 192, 1, 0, 0, 0, 0);
		switch (packet.Decode4())
		{
		case 0:
			Doc()->m_myInfo.stat.i64Pang = packet.Decode8();
			Doc()->m_bonusCash = packet.Decode8();
			Doc()->RefreshAllCookie();
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\307\317\261\342\260\241 \277\317\267\341\265\307\276\372\275\300\264\317\264\331",
				0, 0, 0, 0);
			if (IsLocalContent((localContentType_t)96))
			{
				if (WNetworkSystem::Instance()->IsConnected(
						WNetworkSystem::NET_MSN))
				{
					WSendPacket send(39);
					send.Encode4(MyUID());
					send.Encode4(Doc()->m_giftIndex);
					send.Send(TO_MSN);
				}
			}
			else if (WNetworkSystem::Instance()->IsConnected(
						 WNetworkSystem::NET_MSN))
			{
				WSendPacket send(33);
				send.Encode4(MyUID());
				send.Encode4(Doc()->m_giftIndex);
				send.Send(TO_MSN);
				Doc()->m_giftName = "";
				Doc()->m_giftIndex = -1;
			}
			break;
		case 2:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\261\335\276\327\300\314 \272\316\301\267\307\325\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\337\270\370\265\310 \273\363\307\260 \304\332\265\345\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\307\317\261\342\260\241 \275\307\306\320\307\317\277\264\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 4:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\314 \300\314\271\314 \276\306\300\314\305\333\300\273 \260\241\301\366\260\355 \300\326\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x28:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\314 \300\314\271\314 \277\354\306\355\307\324\277\241 \260\241\301\366\260\355 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x29:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\314 \307\366\300\347 \306\307\270\305\301\337\300\316 \273\363\307\260\300\324\264\317\264\331. \306\307\270\305 \277\317\267\341\265\310 \265\332\277\241 \274\261\271\260\307\317\261\342\260\241 \260\241\264\311\307\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2B:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\314\271\314 \265\271\307\307\264\317\300\307 \272\361\271\320\261\335\260\355\277\241 \260\241\301\366\260\355 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 8:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\307\317\261\342\270\246 \307\322 \274\366 \276\370\264\302 \260\350\301\244\300\324\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 7:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\301\326\271\316\271\370\310\243\260\241 \300\337\270\370 \300\324\267\302\265\307\276\372\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0xB:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\306\307\270\305\261\342\260\243\300\273 \310\256\300\316\307\330 \301\326\274\274\277\344.",
				0, 0, 0, 0);
			break;
		}

		case 9:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\306\300\314\305\333\300\307 \261\342\260\243\300\273 \310\256\300\316\307\330 \301\326\274\274\277\344.",
				0, 0, 0, 0);
			break;
		}

		case 0xC:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\277\241\260\324 \307\330\264\347 \304\263\265\360\260\241 \276\370\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0xE:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\277\241\260\324 \307\330\264\347 \304\263\270\257\305\315\260\241 \276\370\275\300\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x10:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\314 \261\342\260\243\301\246 \276\306\300\314\305\333\300\273 \273\347\277\353\301\337\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x11:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\314 \260\271\274\366\301\246 \276\306\300\314\305\333\300\273 \273\347\277\353\301\337\300\324\264\317\264\331",
				0, 0, 0, 0);
			break;

		case 0x12:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\306\300\314\305\333 \272\270\300\257 \307\321\265\265\270\246 \303\312\260\372\307\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x15:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\321\271\370\277\241 \263\312\271\253 \270\271\300\272 \276\306\300\314\305\333\300\273 \261\270\300\324\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x17:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\272\270\300\257\307\317\260\355 \300\326\264\302 \304\355\305\260\260\241 \272\316\301\267\307\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x18:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\304\355\305\260\301\244\272\270\270\246 \276\367\265\245\300\314\306\256\307\317\301\366 \270\370\307\337\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x1C:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\261\270\300\324\307\317\275\305 \274\261\271\260\300\273 \300\372\300\345\307\317\301\366 \270\370\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x1E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\307 \301\244\272\270\270\246 \301\266\310\270\307\317\264\302\265\245 \275\307\306\320\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x1F:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\261\270\300\324\307\317\267\301\260\355 \307\317\264\302 \276\306\300\314\305\333\300\314 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x20:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\305\303\307\317\275\305 \304\355\306\371\300\273 \273\347\277\353\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331..",
				0, 0, 0, 0);
			break;

		case 0x21:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\273\363\264\353\271\346\300\307 \274\261\271\260\307\324\300\314 \260\241\265\346 \302\367 \264\365 \300\314\273\363 \274\261\271\260\300\273 \307\317\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x13:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\306\307\270\305\307\317\264\302 \276\306\300\314\305\333\300\314 \276\306\264\325\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x19:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\304\355\305\260\270\246 \260\241\301\366\260\355 \300\326\264\331\264\302 \301\244\272\270\270\246 \303\243\300\273 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\303\244\263\316\270\265\274\255\272\361\275\272\260\241 \301\276\267\341\265\307\276\356 \264\365\300\314\273\363 \261\270\270\305\307\317\275\307 \274\366 \276\370\275\300\264\317\264\331..",
				0, 0, 0, 0);
			break;

		case 0x22:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\300\273 \307\317\267\301\264\302 \300\257\300\372\264\302 \300\314 \274\261\271\260\300\273 \271\336\300\270\275\307 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2C:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\300\273 \271\336\264\302 \300\257\300\372\300\307 \267\271\272\247\300\314 \263\267\276\306 \274\261\271\260\307\322\274\366\260\241 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x2D:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\300\273 \271\336\264\302 \300\257\300\372\300\307 \267\271\272\247\300\314 \263\364\276\306 \274\261\271\260 \307\322 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x34:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\300\332\261\342 \300\332\275\305\277\241\260\324\264\302 \274\261\271\260\300\273 \272\270\263\276 \274\366 \276\370\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;

		case 0x33:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\274\261\271\260\307\322 \300\257\300\372\300\307 \301\244\272\270\270\246 \303\243\301\366 \270\370\307\337\275\300\264\317\264\331. \264\331\275\303 \275\303\265\265\307\330 \301\326\274\274\277\344",
				0, 0, 0, 0);
			break;

		case 0x35:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\366\300\347 \270\360\265\347 \304\263\275\254\277\241 \264\353\307\321 \301\266\310\270 \271\327 \273\347\277\353\300\314 \301\244\301\366\265\307\276\356 \300\326\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;
		}
		return 1;
	case 0xae:
		return 1;
	case 0xb4:
		GetActor("Shop") << MsgObject(NULL, 193, packet.Decode4(), 0, 0, 0, 0);
		return 1;
	case 0x105:
		if (!packet.Decode1())
			GetActor("Shop") << MsgObject(NULL, 511, 0, 0, 0, 0, 0);
		return 1;
	case 0x125:
		if (IsLocalContent((localContentType_t)86))
		{
			int result = packet.Decode4();
			if (result == 1)
			{
				int count = packet.Decode2();
				for (int i = 0; i < count; ++i)
				{
					sFurniture_List furniture;
					memset(&furniture, 0, sizeof(furniture));
					packet.DecodeBuffer(&furniture, sizeof(furniture));
					std::list<sFurniture_List>::iterator it;
					for (it = Doc()->m_furnitureList.begin();
						it != Doc()->m_furnitureList.end(); ++it)
						if ((*it).id == furniture.id)
							break;
					if (it == Doc()->m_furnitureList.end())
						Doc()->AddFurniture(furniture);
				}
			}
			else
				AfxGetTask()->GetActor("RealMyRoom")
					<< MsgObject(NULL, 552, 293, result, 0, 0, 0);
		}
		return 1;
	case 0x199:
		AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 2, 0, 0, 0, 0, 0));
		switch (packet.Decode4())
		{
		case 0:
		{
			unsigned long oldId = packet.Decode4();
			unsigned long newId = packet.Decode4();
			sCaddieInfo caddie;
			packet.DecodeBuffer(&caddie, sizeof(caddie));
			std::map<unsigned int, sCaddieInfo>::iterator it =
				Doc()->m_caddieMap.find(oldId);
			if (it != Doc()->m_caddieMap.end())
				Doc()->m_caddieMap.erase(it);
			Doc()->AddCaddie(&caddie);
			Doc()->m_myInfo.userEquip.guidCaddie = newId;
			AfxGetTask()->GetActor("Shop") << MsgObject(NULL, 591,
				(int)"\276\367\261\327\267\271\300\314\265\345\270\246 \274\272\260\370\307\317\277\264\275\300\264\317\264\331.",
				caddie.tid, 0, 0, 0);
		}
		break;
		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\307\330\264\347 \304\263\265\360\270\246 \260\241\301\366\260\355 \300\326\301\366 \276\312\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;
		case 2:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\367\261\327\267\271\300\314\265\345\270\246 \275\307\306\320\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;
		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\276\313\274\366\276\370\264\302 \277\300\267\371\260\241 \271\337\273\375\307\317\277\264\275\300\264\317\264\331.",
				0, 0, 0, 0);
			break;
		}
		break;
	}
	return OnPacketCommon(packet);
}
