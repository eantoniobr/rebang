#pragma once

#include <list>
#include "singleton.h"
#include "../../shared/globalnetworkdefine.h"
#include "mailboxpage.h"

class CTransferableItem : public WSingleton<CTransferableItem>
{
public:
	CTransferableItem();
	virtual ~CTransferableItem();

	void OnLoad();
	void OnDestory();
	void Process(float elapsed);
	void Render();
	void Reset();
	std::list<sTradeItem>* GetList_TransferableItem();
	void ClearTransferableItemList();
	void SetTransferableItemList();
	bool GetTransferableItem(sItemInfo& item, sTradeItem& trade, bool bCheck);
	void SetTransferableEtcItemList();
	void SetListEquipParts();
	bool IsEquipParts(unsigned long uid);
	bool IsUccEquipped(sItemInfo* pItem);
	int GetNumEquipItem(unsigned long typeId);
	void Set_RegistrationListSize(int size);
	bool SetRegistrationItem(unsigned long uid);
	bool SetRegistrationItem(unsigned long uid, int count);
	bool IsTransferableItem(unsigned long uid, sTradeItem& trade, int count);
	bool IsRegisterationItem(unsigned long uid, sTradeItem& trade);
	bool IsRegisterationItem(unsigned long uid);
	std::list<sTradeItem>* GetList_RegistrationItem();
	void ResetRegistrationItemList();
	int Get_RegistrationListSize();
	bool DelRegistrationItem(unsigned long uid);
	std::list<sTradeItem>::iterator DelRegistrationItem_itor_return(
		unsigned long uid);
	void SetMailInfoPage(sMailBoxListForPage& page);
	void SetMailInfo(sMailInfo& info);
	sMailBoxListForPage* GetMailBoxPageList();
	sMailInfo* GetMailInfo();
	int GetNumTradingItem(unsigned long typeId);
	bool IsEquipParts(unsigned long charTypeId, unsigned long uid);
	bool IsCheckCardParts(unsigned long charTypeId, unsigned long typeId);

	std::list<sTradeItem> m_transferableList;
	std::list<unsigned long> m_equipCharList;
	std::list<sTradeItem> m_registrationList;
	int m_registrationListSize;
	sMailBoxListForPage m_mailBoxPage;
	sMailInfo m_mailInfo;
};
