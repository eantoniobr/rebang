#include "stdafx.h"
#include "eventactor.h"
#include "gatewayactor.h"
#include "gatewayinterface.h"

namespace _event
{
	IMPLEMENT_ACTOR(CEventActor, IActor)

	CEventActor::CEventActor()
	{
		m_creator.insert(std::make_pair(s_taskNames[0],
			_util::MakeMemFun(*this, &CEventActor::CreateLobbyHandler)));
		m_creator.insert(std::make_pair(s_taskNames[1],
			_util::MakeMemFun(*this, &CEventActor::CreateShopHandler)));
		m_creator.insert(std::make_pair(s_taskNames[2],
			_util::MakeMemFun(*this, &CEventActor::CreateMyRoomHandler)));
		m_creator.insert(std::make_pair(s_taskNames[3],
			_util::MakeMemFun(*this, &CEventActor::CreateAvatarChatHandler)));
		m_creator.insert(std::make_pair(s_taskNames[4],
			_util::MakeMemFun(*this, &CEventActor::CreateGolfHandler)));
	}

	CEventActor::~CEventActor()
	{
	}

	void CEventActor::CreateLobbyHandler()
	{
	}
	void CEventActor::CreateAvatarChatHandler()
	{
	}
	void CEventActor::CreateMyRoomHandler()
	{
	}
	void CEventActor::CreateShopHandler()
	{
	}
	void CEventActor::CreateGolfHandler()
	{
	}

	void CEventActor::OnPreLoadInit()
	{
		m_eventList.push_back(static_cast<eEventIdentifier>(0));
	}

	void CEventActor::HandleMsg(const MsgObject& msg)
	{
		taskMsg_t message = static_cast<taskMsg_t>(msg.message);
		switch (message)
		{
		case 628:
		case 10002:
			break;
		default:
			std::map<taskMsg_t, _gateway::CGatewayHandler*>::const_iterator it =
				m_handler.end();
			it = m_handler.find(message);
			if (it != m_handler.end())
				(*it).second->Execute(msg);
			break;
		}
	}
}
