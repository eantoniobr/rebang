#include "stdafx.h"
#include "tradedlg.h"
#include "tradehandler.h"
#include "gatewayactor.h"
#include "chatmsg.h"
#include "messagemanager.h"
#include "ucclibrary.h"
#include "uccmanager.h"
#include "../../shared/localize.h"

extern Fresh* g_pFresh;

namespace _gateway
{
	CTradeHandler::CTradeHandler()
	{
	}

	CTradeHandler::~CTradeHandler()
	{
	}

	void CTradeHandler::OnSetEnablePackageSale()
	{
		CTradeDoc* doc = GetDocument<CTradeDoc*>();
		if (doc)
			doc->SetPackageSale(true);
	}

	void CTradeHandler::OnSetDisablePackageSale()
	{
		CTradeDoc* doc = GetDocument<CTradeDoc*>();
		if (doc)
			doc->SetPackageSale(false);
	}

	void CTradeHandler::OnGetPackageSale(int param)
	{
		CTradeDoc* doc = GetDocument<CTradeDoc*>();
		if (doc)
			*(bool*)((MsgObject*)param)->param2 = doc->GetPackageSale();
	}

	void SetTradeResult(int result, int packet, std::vector<sTradeItem>* items)
	{
		if (result == 1)
		{
			if (packet >= 470 && packet <= 471)
			{
				FrTradeResultDlg* dlg = CreateForm<FrTradeResultDlg>(
					g_pFresh->GetManager(), NULL, "traderesultdlg", NULL);
				if (dlg && items)
				{
					dlg->Open(NULL, FrESCAPE);
					dlg->SetFadeout(false);
					dlg->SetResultItemList(items);
				}
			}
			return;
		}
		switch (result)
		{
		case 15:
		{
			FrWnd* wnd =
				g_pFresh->GetDesktop()->FindChildByName("tradewarningdlg");
			if (wnd == NULL)
			{
				FrTradeWarningDlg* dlg = DYNAMIC_CAST(FrTradeWarningDlg, wnd);
				dlg = CreateForm<FrTradeWarningDlg>(g_pFresh->GetManager(),
					NULL, "tradewarningdlg", NULL);
				if (dlg)
				{
					dlg->Open(NULL, FrESCAPE);
					dlg->SetWarningMessageType(15, 0);
					dlg->SetFadeout(false);
				}
			}
		}
		break;
		case 23:
		{
			FrTradeLevelLimitDlg* dlg = CreateForm<FrTradeLevelLimitDlg>(
				g_pFresh->GetManager(), NULL, "tradelevellimitdlg", NULL);
			if (dlg)
				dlg->Open(NULL, FrRET_OK);
			return;
		}
		}
		FrWnd* resultWnd =
			g_pFresh->GetDesktop()->FindChildByName("traderesultdlg");
		if (resultWnd == NULL)
		{
			FrTradeResultDlg* resultDlg =
				DYNAMIC_CAST(FrTradeResultDlg, resultWnd);
			FrWnd* wnd =
				g_pFresh->GetDesktop()->FindChildByName("tradewarningdlg");
			if (wnd == NULL)
			{
				FrTradeWarningDlg* dlg = DYNAMIC_CAST(FrTradeWarningDlg, wnd);
				dlg = CreateForm<FrTradeWarningDlg>(g_pFresh->GetManager(),
					NULL, "tradewarningdlg", NULL);
				if (dlg)
				{
					dlg->Open(NULL, FrESCAPE);
					dlg->SetWarningMessageForPackage(result);
					dlg->SetFadeout(false);
				}
			}
		}
		else
		{
			switch (result)
			{
			case 3:
				CChatMsg::Instance()->AddChatMsg(
					"\xbb\xf3\xc1\xa1\xc0\xcc \xb4\xdd\xc7\xfb\xbd\xc0\xb4\xcf\xb4\xd9. \xb4\xd9\xc0\xbd \xb1\xe2\xc8\xb8\xbf\xa1 \xc0\xcc\xbf\xeb\xc7\xd8\xc1\xd6\xbc\xbc\xbf\xe4.",
					0xffff, false, false);
				break;
			case 4:
				CChatMsg::Instance()->AddChatMsg(
					"\xbb\xf3\xc1\xa1\xc0\xcc \xc6\xed\xc1\xfd\xc1\xdf\xc0\xd4\xb4\xcf\xb4\xd9. \xb0\xb3\xbc\xb3 \xc8\xc4 \xc0\xcc\xbf\xeb\xc7\xd8\xc1\xd6\xbc\xbc\xbf\xe4.",
					0xffff, false, false);
				break;
			}
		}
	}

	void CTradeHandler::OnNotifyTradeErrorCode(int param)
	{
		SetTradeResult(((MsgObject*)param)->param2, 0, NULL);
	}

	void UpdateSellItem(const sTradeItem& item)
	{
		switch (item.dwTid >> 26)
		{
		case 2:
		{
			std::list<sItemInfo>::iterator it;
			if (IsLocalContent(S4_UCC) && IsUccClothes(item.dwTid))
			{
				for (it = Doc()->m_uccItemList.begin();
					it != Doc()->m_uccItemList.end(); ++it)
					if ((*it).guid == item.dwGuid && (*it).tid == item.dwTid &&
						strcmpi((*it).UccIndex, item.UccIndex) == 0 &&
						(*it).Seq == item.Seq)
					{
						Doc()->m_uccItemList.erase(it);
						if (IsLocalContent(S4_CARD_SYSTEM_CHANGE))
							Doc()->DeleteCardToPartsAttach(item.dwGuid);
						break;
					}
			}
			else
			{
				for (it = Doc()->m_partsList.begin();
					it != Doc()->m_partsList.end(); ++it)
					if ((*it).guid == item.dwGuid)
					{
						if ((*it).tid == item.dwTid)
						{
							Doc()->m_partsList.erase(it);
							if (IsLocalContent(S4_CARD_SYSTEM_CHANGE))
								Doc()->DeleteCardToPartsAttach(item.dwGuid);
						}
						break;
					}
			}
		}
		break;
		case 4:
			for (std::map<unsigned int, sItemInfo>::iterator it =
					 Doc()->m_clubSetMap.begin();
				it != Doc()->m_clubSetMap.end(); ++it)
				if ((*it).second.guid == item.dwGuid)
				{
					if ((*it).second.tid == item.dwTid)
						Doc()->m_clubSetMap.erase(it);
					break;
				}
			break;
		}
	}

	void UpdateBuyItem(const sTradeBuyBase& base)
	{
		switch (base.countingType)
		{
		case 2:
		case 3:
			switch (base.itemInfo.tid >> 26)
			{
			case 2:
				if (IsLocalContent(S4_UCC) && IsUccClothes(base.itemInfo.tid))
				{
					Doc()->m_uccItemList.push_back(base.itemInfo);
					UccManager()->AddClothes(1, base.itemInfo.guid,
						base.itemInfo.tid, base.itemInfo.UccIndex, false,
						false);
				}
				else
					Doc()->AddMyPartsList(base.itemInfo);
				break;
			case 4:
				Doc()->m_clubSetMap.insert(
					std::map<unsigned int, sItemInfo>::value_type(
						base.itemInfo.guid, base.itemInfo));
				break;
			}
			break;
		default:
			_systemmsg::CMessageManager::Instance()->NotifyNormalMessage(
				"Invalid Counting Type!");
			break;
		}
	}

	struct sTransformHelper
	{
		const sTradeItem operator()(const sTradeBuyBase& base)
		{
			return base.item;
		}
	};

	void CTradeHandler::OnUpdateTradeBuyItem(int param)
	{
		sTradeBuyParam* data = (sTradeBuyParam*)((MsgObject*)param)->param2;
		std::for_each(data->items.begin(), data->items.end(), UpdateBuyItem);
		Doc()->m_myInfo.stat.i64Pang = data->pang;
		FrTradeDlg* dlg =
			(FrTradeDlg*)g_pFresh->GetDesktop()->FindChildByName("tradedlg");
		if (!dlg)
			DYNAMIC_CAST(FrTradeDlg, dlg);
		else
			dlg->EnableSendingServer(false);
		std::vector<sTradeItem> items;
		std::transform(data->items.begin(), data->items.end(),
			std::back_inserter(items), sTransformHelper());
		SetTradeResult(data->result, 470, &items);
	}

	void CTradeHandler::OnUpdateTradeSellItem(int param)
	{
		sTradeSellParam* data = (sTradeSellParam*)((MsgObject*)param)->param2;
		std::for_each(data->items.begin(), data->items.end(), UpdateSellItem);
		Doc()->m_myInfo.stat.i64Pang += data->pang;
		Doc()->AddTradeIncome(data->pang);
		FrTradeDlg* dlg =
			(FrTradeDlg*)g_pFresh->GetDesktop()->FindChildByName("tradedlg");
		if (!dlg)
			DYNAMIC_CAST(FrTradeDlg, dlg);
		else
			dlg->EnableSendingServer(false);
		std::string message = MakeStr(
			"%d\xb0\xb3\xc0\xc7 \xbe\xc6\xc0\xcc\xc5\xdb\xc0\xcc \xb8\xf0\xb5\xce \xc6\xc7\xb8\xc5\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9.",
			data->items.size());
		CChatMsg::Instance()->AddChatMsg(message, 0xffff, true, false);
	}

	void CTradeHandler::OnUpdateTradeMinusItem(int param)
	{
		sTradeMinusParam* data = (sTradeMinusParam*)((MsgObject*)param)->param2;
		if (data->uid == Doc()->GetTradeUID())
		{
			if (data->state == STATE_TRADE_OUTOFSTOCK)
				Doc()->SetStateTrade(STATE_TRADE_OUTOFSTOCK);
			std::for_each(data->items.begin(), data->items.end(),
				_util::MakeMemFun1(*Doc(), &CSharedDoc::MinusListTradeItem));
			FrTradeBuyDlg* buy =
				(FrTradeBuyDlg*)g_pFresh->GetDesktop()->FindChildByName(
					"tradebuydlg");
			if (!buy)
				DYNAMIC_CAST(FrTradeBuyDlg, buy);
			else
			{
				if (!buy->IsClosing())
				{
					buy->ClearTradeList();
					CChatMsg::Instance()->AddChatMsg(
						"\xb8\xf0\xb5\xe7 \xbb\xf3\xc7\xb0\xc0\xcc \xc6\xc7\xb8\xc5\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9.",
						0xffff, true, false);
					buy->Close(true);
					FrWnd* notify = g_pFresh->GetDesktop()->FindChildByName(
						"notify_okcancel");
					if (!notify)
						DYNAMIC_CAST(FrForm, notify);
					else
						notify->Close(true);
				}
			}
			FrTradeDlg* found =
				(FrTradeDlg*)g_pFresh->GetDesktop()->FindChildByName(
					"tradedlg");
			FrTradeDlg* trade = NULL;
			if (!found)
				DYNAMIC_CAST(FrTradeDlg, found);
			else
			{
				trade = found;
				trade->SetListTradeItem(true);
				trade->SetListTradeItem(false);
			}
			if (Doc()->GetStateTrade() == STATE_TRADE_OUTOFSTOCK)
			{
				if (strcmp(data->name.c_str(), MyNick()))
				{
					if (trade)
						trade->Close(true);
				}
				else
				{
					if (trade)
					{
						trade->ShowStaticOutOfStock(true);
						trade->EnableHideBn(false);
					}
					else
					{
						FrTradeDlg* dlg = CreateForm<FrTradeDlg>(
							g_pFresh->GetManager(), this, "tradedlg", NULL);
						if (dlg)
						{
							dlg->Open(NULL, FrRET_OK | FrRET_CANCEL);
							dlg->OpenTradeShop(Doc()->GetTradeUID());
							dlg->SetFadeout(false);
						}
					}
				}
				CChatMsg::Instance()->AddChatMsg(
					"\xb8\xf0\xb5\xe7 \xbb\xf3\xc7\xb0\xc0\xcc \xc6\xc7\xb8\xc5\xb5\xc7\xbe\xfa\xbd\xc0\xb4\xcf\xb4\xd9.",
					0xffff, true, false);
			}
		}
		if (Doc()->GetStateTrade() == STATE_TRADE_OUTOFSTOCK)
			AfxGetTask()->GetActor("AvatarChat")
				<< MsgObject(NULL, 232, (int)data->name.c_str(), 3, 0, 0, 0);
	}

	bool CTradeHandler::Execute(const MsgObject& msg)
	{
		SetFunctionType(msg.param1);
		return Exec(this, (int)&msg);
	}

	bool CTradeHandler::Initialize()
	{
		AddFunctionType(0, FUNCTIONTYPE_ARG,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnNotifyTradeErrorCode);
		AddFunctionType(1, FUNCTIONTYPE_ARG,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnUpdateTradeBuyItem);
		AddFunctionType(2, FUNCTIONTYPE_ARG,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnUpdateTradeSellItem);
		AddFunctionType(3, FUNCTIONTYPE_ARG,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnUpdateTradeMinusItem);
		AddFunctionType(4, FUNCTIONTYPE_VOID,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnSetEnablePackageSale);
		AddFunctionType(5, FUNCTIONTYPE_VOID,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnSetDisablePackageSale);
		AddFunctionType(6, FUNCTIONTYPE_ARG,
			(FUNCTION_PTR)(void (
				CTradeHandler::*)())&CTradeHandler::OnGetPackageSale);
		return true;
	}
}
