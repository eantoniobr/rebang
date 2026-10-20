#pragma once

#include "actor.h"
#include "wtemplate.h"
#include <list>

enum taskMsg_t;
namespace _gateway
{
	class CGatewayHandler;
}

namespace _event
{
	enum eEventIdentifier;

	class CEventActor : public IActor
	{
		DECLARE_OBJECT(CEventActor)
	protected:
		CEventActor();

	public:
		virtual ~CEventActor();
		virtual void OnPreLoadInit();
		virtual void HandleMsg(const MsgObject& msg);

	private:
		void CreateLobbyHandler();
		void CreateAvatarChatHandler();
		void CreateMyRoomHandler();
		void CreateShopHandler();
		void CreateGolfHandler();

		std::map<taskMsg_t, _gateway::CGatewayHandler*> m_handler;
		std::list<eEventIdentifier> m_eventList;
		std::map<std::string, _util::WMemFun<CEventActor, void> > m_creator;
	};
}
