#pragma once

class CPrivateTradeImpl;
class WReceivedPacket;

class CPrivateTrade : public IActor
{
	DECLARE_OBJECT(CPrivateTrade)

public:
	CPrivateTrade();
	virtual ~CPrivateTrade();

	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnReload();
	virtual void OnProcess(float delta);
	virtual void OnDisplay();
	virtual void OnDestroy();

	void OnPacket(WReceivedPacket* packet);

protected:
	virtual void HandleMsg(const MsgObject& msg);

private:
	CPrivateTradeImpl* m_pImpl;
};
