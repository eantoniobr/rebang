#include "stdafx.h"
#include "topiconmanager.h"
#include "topicons.h"
#include "webicons.h"
#include "tinyxml.h"

CIconManager::CIconManager()
{
	RegisterInstances();
	m_outSideIconCount = 0;
	LoadGameData("TopIcons.xml");
}

CIconManager::~CIconManager()
{
	m_outSideIconCount = 0;
	Destory();
}

void CIconManager::LoadGameData(const char* filename)
{
	TiXmlDocument doc;
	if (!doc.LoadFileEx(filename))
		return;
	ParseTopIconData(doc);
}

void CIconManager::ParseTopIconData(TiXmlDocument& doc)
{
	TiXmlNode* root = doc.FirstChild("TopIcons");
	std::string type("");
	for (TiXmlNode* node = root->FirstChild("Icon"); node;
		node = node->NextSibling("Icon"))
	{
		type = node->ToElement()->Attribute("Type");
		if (type != "")
		{
			if (type == "EVENTICON")
				ParseEventIconData(node);
			else if (type == "WEBICON")
				ParseWebIconData(node);
		}
	}
}

void CIconManager::ParseEventIconData(TiXmlNode* node)
{
	std::string name("");
	name = node->ToElement()->Attribute("Name");
	if (name == "")
		return;
	if (m_instanceFunctions.find(name) != m_instanceFunctions.end())
		m_topIcons.push_back(
			new sTopIcon(name, m_instanceFunctions[name].pCreateInstance()));
}

void CIconManager::ParseWebIconData(TiXmlNode* node)
{
	std::string normal, over, selected, qaUrl, url;
	std::string name("");
	name = node->ToElement()->Attribute("Name");
	if (m_instanceFunctions.find(name) != m_instanceFunctions.end())
	{
		CIconInterface* icon = m_instanceFunctions[name].pCreateInstance();
		normal = node->ToElement()->Attribute("Normal");
		over = node->ToElement()->Attribute("Over");
		selected = node->ToElement()->Attribute("Selected");
		qaUrl = node->ToElement()->Attribute("QAUrl");
		url = node->ToElement()->Attribute("Url");
		icon->SetInformation(normal, over, selected, qaUrl, url);
		m_topIcons.push_back(new sTopIcon(name, icon));
	}
}

void CIconManager::RegisterInstances()
{
	CWizcityOpenEvent::RegisterToTopIconDB();
	CWebIcons_WebEvent1::RegisterToTopIconDB();
	CWebIcons_WebEvent2::RegisterToTopIconDB();
}

void CIconManager::RegisterInstanceFunction(std::string name,
	CreateTopIconInstanceFunc create, DestoryTopIconInstanceFunc destroy)
{
	m_instanceFunctions.insert(
		std::map<std::string, sInstanceFunctions>::value_type(name,
			sInstanceFunctions(create, destroy)));
}

void CIconManager::Destory()
{
	for (TopIconIterator it = m_topIcons.begin(); it != m_topIcons.end(); ++it)
	{
		if (it != NULL)
		{
			if ((*it)->pInstance)
				m_instanceFunctions[(*it)->name].pDestoryInstance(
					(*it)->pInstance);
			delete *it;
		}
	}
	m_topIcons.clear();
}

void CIconManager::InitalizeTopIcon(unsigned long index, int wnd)
{
	FrButton* button = DYNAMIC_CAST(FrButton, (FrWnd*)wnd);
	if (button)
	{
		if (index >= m_topIcons.size())
		{
			button->SetVisible(false);
			button->Enable(false);
			return;
		}
		CIconInterface* icon = m_topIcons[index]->pInstance;
		if (!icon)
		{
			button->SetVisible(false);
			button->Enable(false);
			return;
		}
		WRect rect;
		button->GetClientRect(rect);
		rect.x = (float)(80 * (index + m_outSideIconCount));
		button->SetClientRect(rect);
		icon->SetIconImage(*button);
		icon->OnInit(*button);
	}
}

void CIconManager::OnButtonDown(unsigned long index)
{
	m_topIcons[index]->pInstance->OnButtonDown();
}

bool CIconManager::IsIncludedIcon(std::string name)
{
	for (TopIconIterator it = m_topIcons.begin(); it != m_topIcons.end(); ++it)
		if (it != NULL && strcmp((*it)->name.c_str(), name.c_str()) == 0)
			return true;
	return false;
}
