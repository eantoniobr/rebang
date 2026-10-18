#pragma once

#include "work.h"
#include "eventthread.h"

class CWorkAliveCheck : public CWork
{
protected:
	unsigned long m_lastTick;
	unsigned long m_interval;
	unsigned long m_count;

public:
	CWorkAliveCheck(unsigned long interval)
		: m_lastTick(GetTickCount()), m_interval(interval), m_count(0)
	{
		CEventThread::Instance()->RegisterWork(this);
	}

	virtual ~CWorkAliveCheck()
	{
		CEventThread::Instance()->UnregisterWork(this);
	}

	virtual void Act()
	{
		if (m_interval < GetTickCount() - m_lastTick)
		{
			WSendPacket send((enumClientPacket)0xf6);
			send.Encode4(m_count++);
			send.Send(TO_GAME);

			m_lastTick = GetTickCount();
		}
	}
};
