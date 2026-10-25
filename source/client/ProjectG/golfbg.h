#pragma once
#include "actor.h"

class CGolfBg : public IActor
{
public:
	DECLARE_OBJECT(CGolfBg)
protected:
	CGolfBg();

public:
	virtual ~CGolfBg() { }
	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnDestroy();
	virtual void HandleMsg(const MsgObject& msg);

protected:
	void SetLowestPoint();
	void SetGridCenter(WVector& pos);
	void SetStartPoint(const WVector& pos);
	void SetHolePoint(const WVector& pos);
	void SetSkyColor(unsigned long color);
	const char* GetSkyBoxName();
	unsigned char GetRenderWeather() { return m_renderWeather; }
	void SetRenderWeather(unsigned char weather);
	void DoInitAfterLoad();
	void DoReLoad();
	unsigned char m_renderWeather;
};
