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
					"\xc1\xa4\xbb\xf3\xc0\xfb\xc0\xb8\xb7\xce \xb1\xb8\xb8\xc5\xb0\xa1 \xbf\xcf\xb7\xe1\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9.\012\xba\xb8\xb3\xca\xbd\xba %s %d\xb0\xb3\xb8\xa6 \xb9\xde\xc0\xb8\xbc\xcc\xbd\xc0\xb4\xcf\xb4\xd9.",
					Doc()->m_itemManager.GetItemName(tid), result),
				0, 0, 0, 0);
		}
		break;
		case 0:
			Doc()->m_myInfo.stat.i64Pang = packet.Decode8();
			Doc()->m_bonusCash = packet.Decode8();
			Doc()->RefreshAllCookie();
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc1\xa4\xbb\xf3\xc0\xfb\xc0\xb8\xb7\xce \xb1\xb8\xb8\xc5\xb0\xa1 \xbf\xcf\xb7\xe1\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9.",
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
				(int)"\xba\xb8\xc0\xaf\xc7\xcf\xb0\xed \xc0\xd6\xb4\xc2 \xc6\xce\xc0\xcc \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xdf\xb8\xf8\xb5\xc8 \xbb\xf3\xc7\xb0 \xc4\xda\xb5\xe5\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xb1\xb8\xb8\xc5\xb0\xa1 \xbd\xc7\xc6\xd0\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 4:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xcc\xb9\xcc \xb1\xb8\xb8\xc5\xc7\xd1 \xb9\xb0\xb0\xc7\xc0\xd4\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x28:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xcc\xb9\xcc \xbf\xec\xc6\xed\xc7\xd4\xbf\xa1 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x29:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc1\xf6\xb1\xdd \xc6\xc7\xb8\xc5\xc1\xdf\xc0\xce \xbb\xf3\xc7\xb0\xc0\xd4\xb4\xcf\xb4\xd9. \xc6\xc7\xb8\xc5 \xbf\xcf\xb7\xe1\xb5\xc8 \xb5\xda\xbf\xa1 \xb1\xb8\xc0\xd4\xc7\xcf\xbd\xc7 \xbc\xf6 \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2B:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xcc\xb9\xcc \xb5\xb9\xc7\xc7\xb4\xcf\xc0\xc7 \xba\xf1\xb9\xd0\xb1\xdd\xb0\xed\xbf\xa1 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0xB:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc6\xc7\xb8\xc5\xb1\xe2\xb0\xa3\xc0\xbb \xc8\xae\xc0\xce\xc7\xd8 \xc1\xd6\xbc\xbc\xbf\xe4.",
				0, 0, 0, 0);
			break;
		}

		case 9:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xc6\xc0\xcc\xc5\xdb\xc0\xc7 \xb1\xe2\xb0\xa3\xc0\xbb \xc8\xae\xc0\xce\xc7\xd8 \xc1\xd6\xbc\xbc\xbf\xe4.",
				0, 0, 0, 0);
			break;
		}

		case 0x10:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xb1\xe2\xb0\xa3\xc1\xa6 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xbb\xe7\xbf\xeb\xc1\xdf\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x11:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xb0\xb9\xbc\xf6\xc1\xa6 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xbb\xe7\xbf\xeb\xc1\xdf\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x15:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xd1\xb9\xf8\xbf\xa1 \xb3\xca\xb9\xab \xb8\xb9\xc0\xba \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xb1\xb8\xc0\xd4\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x17:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xba\xb8\xc0\xaf\xc7\xcf\xb0\xed \xc0\xd6\xb4\xc2 \xc4\xed\xc5\xb0\xb0\xa1 \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x18:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc4\xed\xc5\xb0\xb8\xa6 \xbe\xf7\xb5\xa5\xc0\xcc\xc6\xae\xc7\xcf\xb4\xc2\xb5\xa5 \xbd\xc7\xc6\xd0\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x12:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xb4\xf5 \xc0\xcc\xbb\xf3 \xb1\xb8\xc0\xd4\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x23:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xc1\xa1\xc0\xcc \xc8\xa5\xc0\xe2\xc7\xcf\xbf\xa9 \xc1\xf6\xb1\xdd\xc0\xba \xb1\xb8\xc0\xd4\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9. \xc0\xe1\xbd\xc3 \xc8\xc4 \xc0\xcc\xbf\xeb\xc7\xd8\xc1\xd6\xbd\xc3\xb1\xe2 \xb9\xd9\xb6\xf8\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x13:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc6\xc7\xb8\xc5\xc7\xcf\xb4\xc2 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xcc \xbe\xc6\xb4\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc3\xa4\xb3\xce\xb8\xb5\xbc\xad\xba\xf1\xbd\xba\xb0\xa1 \xc1\xbe\xb7\xe1\xb5\xc7\xbe\xee \xb4\xf5\xc0\xcc\xbb\xf3 \xb1\xb8\xb8\xc5\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x22:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xcc \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xb4\xf5 \xc0\xcc\xbb\xf3 \xba\xb8\xc0\xaf\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2C:
		case 0x2D:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xf6\xc0\xe7 \xb7\xb9\xba\xa7\xb7\xce\xb4\xc2 \xb1\xb8\xc0\xd4\xc7\xd2 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x35:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xf6\xc0\xe7 \xb8\xf0\xb5\xe7 \xc4\xb3\xbd\xac\xbf\xa1 \xb4\xeb\xc7\xd1 \xc1\xb6\xc8\xb8 \xb9\xd7 \xbb\xe7\xbf\xeb\xc0\xcc \xc1\xa4\xc1\xf6\xb5\xc7\xbe\xee \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
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
				(int)"\xbc\xb1\xb9\xb0\xc7\xcf\xb1\xe2\xb0\xa1 \xbf\xcf\xb7\xe1\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9",
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
				(int)"\xb1\xdd\xbe\xd7\xc0\xcc \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xdf\xb8\xf8\xb5\xc8 \xbb\xf3\xc7\xb0 \xc4\xda\xb5\xe5\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc7\xcf\xb1\xe2\xb0\xa1 \xbd\xc7\xc6\xd0\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 4:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xcc \xc0\xcc\xb9\xcc \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x28:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xcc \xc0\xcc\xb9\xcc \xbf\xec\xc6\xed\xc7\xd4\xbf\xa1 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x29:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xcc \xc7\xf6\xc0\xe7 \xc6\xc7\xb8\xc5\xc1\xdf\xc0\xce \xbb\xf3\xc7\xb0\xc0\xd4\xb4\xcf\xb4\xd9. \xc6\xc7\xb8\xc5 \xbf\xcf\xb7\xe1\xb5\xc8 \xb5\xda\xbf\xa1 \xbc\xb1\xb9\xb0\xc7\xcf\xb1\xe2\xb0\xa1 \xb0\xa1\xb4\xc9\xc7\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2B:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xcc\xb9\xcc \xb5\xb9\xc7\xc7\xb4\xcf\xc0\xc7 \xba\xf1\xb9\xd0\xb1\xdd\xb0\xed\xbf\xa1 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 8:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc7\xcf\xb1\xe2\xb8\xa6 \xc7\xd2 \xbc\xf6 \xbe\xf8\xb4\xc2 \xb0\xe8\xc1\xa4\xc0\xd4\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 7:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc1\xd6\xb9\xce\xb9\xf8\xc8\xa3\xb0\xa1 \xc0\xdf\xb8\xf8 \xc0\xd4\xb7\xc2\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0xB:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc6\xc7\xb8\xc5\xb1\xe2\xb0\xa3\xc0\xbb \xc8\xae\xc0\xce\xc7\xd8 \xc1\xd6\xbc\xbc\xbf\xe4.",
				0, 0, 0, 0);
			break;
		}

		case 9:
		{
			SYSTEMTIME time;
			packet.DecodeBuffer(&time, sizeof(time));
			Doc()->SetServerTime(time);
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xc6\xc0\xcc\xc5\xdb\xc0\xc7 \xb1\xe2\xb0\xa3\xc0\xbb \xc8\xae\xc0\xce\xc7\xd8 \xc1\xd6\xbc\xbc\xbf\xe4.",
				0, 0, 0, 0);
			break;
		}

		case 0xC:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xbf\xa1\xb0\xd4 \xc7\xd8\xb4\xe7 \xc4\xb3\xb5\xf0\xb0\xa1 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0xE:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xbf\xa1\xb0\xd4 \xc7\xd8\xb4\xe7 \xc4\xb3\xb8\xaf\xc5\xcd\xb0\xa1 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x10:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xcc \xb1\xe2\xb0\xa3\xc1\xa6 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xbb\xe7\xbf\xeb\xc1\xdf\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x11:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xcc \xb0\xb9\xbc\xf6\xc1\xa6 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xbb\xe7\xbf\xeb\xc1\xdf\xc0\xd4\xb4\xcf\xb4\xd9",
				0, 0, 0, 0);
			break;

		case 0x12:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xc6\xc0\xcc\xc5\xdb \xba\xb8\xc0\xaf \xc7\xd1\xb5\xb5\xb8\xa6 \xc3\xca\xb0\xfa\xc7\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x15:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xd1\xb9\xf8\xbf\xa1 \xb3\xca\xb9\xab \xb8\xb9\xc0\xba \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xbb \xb1\xb8\xc0\xd4\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x17:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xba\xb8\xc0\xaf\xc7\xcf\xb0\xed \xc0\xd6\xb4\xc2 \xc4\xed\xc5\xb0\xb0\xa1 \xba\xce\xc1\xb7\xc7\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x18:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc4\xed\xc5\xb0\xc1\xa4\xba\xb8\xb8\xa6 \xbe\xf7\xb5\xa5\xc0\xcc\xc6\xae\xc7\xcf\xc1\xf6 \xb8\xf8\xc7\xdf\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x1C:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xb1\xb8\xc0\xd4\xc7\xcf\xbd\xc5 \xbc\xb1\xb9\xb0\xc0\xbb \xc0\xfa\xc0\xe5\xc7\xcf\xc1\xf6 \xb8\xf8\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x1E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xc7 \xc1\xa4\xba\xb8\xb8\xa6 \xc1\xb6\xc8\xb8\xc7\xcf\xb4\xc2\xb5\xa5 \xbd\xc7\xc6\xd0\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x1F:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xb1\xb8\xc0\xd4\xc7\xcf\xb7\xc1\xb0\xed \xc7\xcf\xb4\xc2 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xcc \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x20:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xc5\xc3\xc7\xcf\xbd\xc5 \xc4\xed\xc6\xf9\xc0\xbb \xbb\xe7\xbf\xeb\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9..",
				0, 0, 0, 0);
			break;

		case 0x21:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbb\xf3\xb4\xeb\xb9\xe6\xc0\xc7 \xbc\xb1\xb9\xb0\xc7\xd4\xc0\xcc \xb0\xa1\xb5\xe6 \xc2\xf7 \xb4\xf5 \xc0\xcc\xbb\xf3 \xbc\xb1\xb9\xb0\xc0\xbb \xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x13:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc6\xc7\xb8\xc5\xc7\xcf\xb4\xc2 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xcc \xbe\xc6\xb4\xd5\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x19:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc4\xed\xc5\xb0\xb8\xa6 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xb4\xd9\xb4\xc2 \xc1\xa4\xba\xb8\xb8\xa6 \xc3\xa3\xc0\xbb \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2E:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc3\xa4\xb3\xce\xb8\xb5\xbc\xad\xba\xf1\xbd\xba\xb0\xa1 \xc1\xbe\xb7\xe1\xb5\xc7\xbe\xee \xb4\xf5\xc0\xcc\xbb\xf3 \xb1\xb8\xb8\xc5\xc7\xcf\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9..",
				0, 0, 0, 0);
			break;

		case 0x22:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc0\xbb \xc7\xcf\xb7\xc1\xb4\xc2 \xc0\xaf\xc0\xfa\xb4\xc2 \xc0\xcc \xbc\xb1\xb9\xb0\xc0\xbb \xb9\xde\xc0\xb8\xbd\xc7 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2C:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc0\xbb \xb9\xde\xb4\xc2 \xc0\xaf\xc0\xfa\xc0\xc7 \xb7\xb9\xba\xa7\xc0\xcc \xb3\xb7\xbe\xc6 \xbc\xb1\xb9\xb0\xc7\xd2\xbc\xf6\xb0\xa1 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x2D:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc0\xbb \xb9\xde\xb4\xc2 \xc0\xaf\xc0\xfa\xc0\xc7 \xb7\xb9\xba\xa7\xc0\xcc \xb3\xf4\xbe\xc6 \xbc\xb1\xb9\xb0 \xc7\xd2 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x34:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc0\xda\xb1\xe2 \xc0\xda\xbd\xc5\xbf\xa1\xb0\xd4\xb4\xc2 \xbc\xb1\xb9\xb0\xc0\xbb \xba\xb8\xb3\xbe \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;

		case 0x33:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbc\xb1\xb9\xb0\xc7\xd2 \xc0\xaf\xc0\xfa\xc0\xc7 \xc1\xa4\xba\xb8\xb8\xa6 \xc3\xa3\xc1\xf6 \xb8\xf8\xc7\xdf\xbd\xc0\xb4\xcf\xb4\xd9. \xb4\xd9\xbd\xc3 \xbd\xc3\xb5\xb5\xc7\xd8 \xc1\xd6\xbc\xbc\xbf\xe4",
				0, 0, 0, 0);
			break;

		case 0x35:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xf6\xc0\xe7 \xb8\xf0\xb5\xe7 \xc4\xb3\xbd\xac\xbf\xa1 \xb4\xeb\xc7\xd1 \xc1\xb6\xc8\xb8 \xb9\xd7 \xbb\xe7\xbf\xeb\xc0\xcc \xc1\xa4\xc1\xf6\xb5\xc7\xbe\xee \xc0\xd6\xbd\xc0\xb4\xcf\xb4\xd9.",
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
				(int)"\xbe\xf7\xb1\xd7\xb7\xb9\xc0\xcc\xb5\xe5\xb8\xa6 \xbc\xba\xb0\xf8\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				caddie.tid, 0, 0, 0);
		}
		break;
		case 1:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xc7\xd8\xb4\xe7 \xc4\xb3\xb5\xf0\xb8\xa6 \xb0\xa1\xc1\xf6\xb0\xed \xc0\xd6\xc1\xf6 \xbe\xca\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;
		case 2:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xf7\xb1\xd7\xb7\xb9\xc0\xcc\xb5\xe5\xb8\xa6 \xbd\xc7\xc6\xd0\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;
		case 3:
			GetActor("Shop") << MsgObject(NULL, 35,
				(int)"\xbe\xcb\xbc\xf6\xbe\xf8\xb4\xc2 \xbf\xc0\xb7\xf9\xb0\xa1 \xb9\xdf\xbb\xfd\xc7\xcf\xbf\xb4\xbd\xc0\xb4\xcf\xb4\xd9.",
				0, 0, 0, 0);
			break;
		}
		break;
	}
	return OnPacketCommon(packet);
}
