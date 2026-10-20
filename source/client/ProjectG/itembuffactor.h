#pragma once

#include <list>
#include "actor.h"
#include "frcmdtarget.h"

struct sSCardAvilityPeriodInfo;
struct sItemInfo;
class FrSPCardBuffDlg;
class WReceivedPacket;
struct FrListItem;
class FrForm;
struct Bitmap;

class CItemBuff : public IActor, public FrCmdTarget
{
protected:
	CItemBuff();

public:
	DECLARE_OBJECT(CItemBuff)

	virtual void OnLoad();
	virtual void HandleMsg(const MsgObject& msg);

	static void ResetBuffList();
	static void ProcessPacket(WReceivedPacket& packet);
	static void AddBuffItem(sSCardAvilityPeriodInfo& info);
	static void RemoveBuffItem(unsigned long typeId);
	static void UpdateBuffDlg(FrSPCardBuffDlg* dlg);

protected:
	void HandleBuffItemSubMsg(const MsgObject& msg);
	void DrawMiniButton(FrListItem* item, const WPoint& pos);
	void ButtonDown(FrListItem* item, const WPoint& pos);
	void UseBuffItem(sItemInfo* item);
	void IsCompatibleBuff(unsigned long typeId,
		const std::list<sSCardAvilityPeriodInfo>& buffList, bool& compatible,
		unsigned long& conflictTypeId);
	bool OnUseBuffItemDlgResult(int result, FrForm* form);

	const Bitmap* m_pButtonNormal;
	const Bitmap* m_pButtonOver;
	WRect m_buttonRect;
	unsigned long m_useTypeId;

private:
	static std::list<sSCardAvilityPeriodInfo> ms_BuffItemInfoList;
};
