#include "stdafx.h"
#include "gatewayactor.h"
#include "actor.h"

enum taskMsg_t;
enum localContentType_t;

namespace _gateway
{
	class CGatewayHandler;

	class CGatewayActor : public IActor
	{
		DECLARE_OBJECT(CGatewayActor)
	protected:
		CGatewayActor();

	public:
		virtual ~CGatewayActor();
		virtual void OnDestroy();
		virtual void HandleMsg(const MsgObject& msg);

	private:
		bool CreateHandler(int task);
		bool InsertHandler(taskMsg_t msg, CGatewayHandler* handler);
		void QueryHandler(localContentType_t type, taskMsg_t msg);
		void CreateLobbyHandler();
		void CreateAvatarChatHandler();
		void CreateMyRoomHandler();
		void CreateShopHandler();
		void CreateGolfHandler();

		std::map<taskMsg_t, CGatewayHandler*> m_handler;
		std::map<std::string, void (CGatewayActor::*)()> m_creator;
	};
}

#include "gatewaydoc.h"

static const char* s_taskNames[] = { "CLobbyTask", "CShopTask",
	"CRealMyRoomTask", "ntAvatarChatTask", "CGolfTask" };

namespace _gateway
{
	IMPLEMENT_ACTOR(CGatewayActor, IActor)

	CGatewayActor::CGatewayActor()
	{
		m_creator.insert(
			std::make_pair(s_taskNames[0], &CGatewayActor::CreateLobbyHandler));
		m_creator.insert(
			std::make_pair(s_taskNames[1], &CGatewayActor::CreateShopHandler));
		m_creator.insert(std::make_pair(s_taskNames[2],
			&CGatewayActor::CreateMyRoomHandler));
		m_creator.insert(std::make_pair(s_taskNames[3],
			&CGatewayActor::CreateAvatarChatHandler));
		m_creator.insert(
			std::make_pair(s_taskNames[4], &CGatewayActor::CreateGolfHandler));
	}
	CGatewayActor::~CGatewayActor()
	{
	}

	void CGatewayActor::OnDestroy()
	{
		m_creator.clear();
	}

	void CGatewayActor::HandleMsg(const MsgObject& msg)
	{
		taskMsg_t message = static_cast<taskMsg_t>(msg.message);
		switch (message)
		{
		case 10002:
			CreateHandler(msg.param1);
			break;
		default:
		{
			std::map<taskMsg_t, CGatewayHandler*>::const_iterator it =
				m_handler.end();
			it = m_handler.find(message);
			if (it == m_handler.end())
				return;
			(*it).second->Execute(msg);
		}
		}
	}

	bool CGatewayActor::CreateHandler(int task)
	{
		std::map<std::string, void (CGatewayActor::*)()>::const_iterator it =
			m_creator.find(std::string((const char*)task));
		if (it == m_creator.end())
			return false;
		(this->*(*it).second)();
		return true;
	}

	bool CGatewayActor::InsertHandler(taskMsg_t msg, CGatewayHandler* handler)
	{
		m_handler.insert(std::make_pair(msg, handler));
		return true;
	}

	void CGatewayActor::QueryHandler(localContentType_t type, taskMsg_t msg)
	{
		if (type < 157 || type > 160)
			throw WAppException("Passed Unknown doctype!!\nCode[0]");
		IContentsDataContainer* container = NULL;
		CContentsDoc::Instance()->GetContainer(type, container);
		CGatewayControlDoc* doc = static_cast<CGatewayControlDoc*>(container);
		if (!doc)
			throw WAppException("Need Doc Object!!\nCode[1]");
		CGatewayHandler* handler = doc->GetGatewayHandler();
		if (!handler)
			throw WAppException("Need Gateway Handler!!\nCode[2]");
		handler->SetDocument(doc);
		InsertHandler(msg, handler);
	}

	void CGatewayActor::CreateLobbyHandler()
	{
		QueryHandler((localContentType_t)157, (taskMsg_t)621);
		QueryHandler((localContentType_t)158, (taskMsg_t)623);
		QueryHandler((localContentType_t)160, (taskMsg_t)630);
	}
	void CGatewayActor::CreateAvatarChatHandler()
	{
		QueryHandler((localContentType_t)157, (taskMsg_t)621);
		QueryHandler((localContentType_t)159, (taskMsg_t)627);
	}
	void CGatewayActor::CreateMyRoomHandler()
	{
		QueryHandler((localContentType_t)157, (taskMsg_t)621);
		QueryHandler((localContentType_t)160, (taskMsg_t)630);
	}
	void CGatewayActor::CreateShopHandler()
	{
		QueryHandler((localContentType_t)157, (taskMsg_t)621);
	}
	void CGatewayActor::CreateGolfHandler()
	{
		QueryHandler((localContentType_t)158, (taskMsg_t)623);
	}
}
