#include "stdafx.h"
#include "winnernotice.h"
#include "tinyxml.h"
#include "binstr.h"
#include "chatmsg.h"
#include "gdeventnotice.h"
#include "capturedbg.h"
#include "onelineboard.h"
#include "soundmanager.h"

extern Fresh* g_pFresh;
extern WView* g_view;
extern WResourceManager* g_resrcmng;
extern CSoundManager* g_audio;

CWinnerNotice::CWinnerNotice()
{
	WinnerNotice_Init();
}

CWinnerNotice::~CWinnerNotice()
{
	WinnerNotice_Clear();
}

void CWinnerNotice::WinnerNotice_Init()
{
	m_pNoticeL = g_resrcmng->GetOverlay("notice_l.tga", 0);
	m_pNoticeM = g_resrcmng->GetOverlay("notice_m.tga", 0);
	m_pNoticeR = g_resrcmng->GetOverlay("notice_r.tga", 0);
	m_pFont = CChatMsg::Instance()->GetMaskedFont();
	m_itrCurrent = m_noticeList.end();
	m_fTextPosX = -5555.0f;
	m_fBgPosY = -50.0f;
	m_pEventNotice = NULL;
	m_reserved = 0;
}

void CWinnerNotice::WinnerNotice_Clear()
{
	m_itrCurrent = m_noticeList.end();
	sequence_delete(m_noticeList.begin(), m_noticeList.end());
	if (g_resrcmng && m_pNoticeL)
	{
		g_resrcmng->Release(m_pNoticeL);
		m_pNoticeL = NULL;
	}
	if (g_resrcmng && m_pNoticeM)
	{
		g_resrcmng->Release(m_pNoticeM);
		m_pNoticeM = NULL;
	}
	if (g_resrcmng && m_pNoticeR)
	{
		g_resrcmng->Release(m_pNoticeR);
		m_pNoticeR = NULL;
	}
}

void CWinnerNotice::Process(float elapsed)
{
	elapsed /= CProjectG::Instance()->GetGameSpeed();
	if (m_itrCurrent == m_noticeList.end())
	{
		m_itrCurrent = m_noticeList.begin();
		if (m_itrCurrent == m_noticeList.end())
		{
			if (m_fBgPosY > -50.0f)
			{
				m_fBgPosY -= elapsed * 30.0f;
				if (m_fBgPosY < -50.0f)
					m_fBgPosY = -50.0f;
			}
			if (IS_KINDOF(CGolfTask, AfxGetTask()))
				COneLineBoard::Instance()->FadeIn();
			return;
		}
	}
	if (CCapturedBg::Instance() && CCapturedBg::Instance()->IsCaptured())
	{
		FrEmoticon* emoticon = g_pFresh->GetManager()->GetEmoticon();
		if (emoticon)
			emoticon->SetAnim(false);
	}
	else
	{
		if (m_fBgPosY < -0.1f)
		{
			m_fBgPosY += elapsed * 30.0f;
			if (!(m_fBgPosY > 0.0f))
				return;
		}
		m_fBgPosY = 0.0f;
		sWinnerNotice* notice = *m_itrCurrent;
		if (m_fTextPosX < -5000.0f)
			m_fTextPosX = g_view->GetWidth() * 0.5f + 150.0f;
		m_fTextPosX -= elapsed * 30.0f;
		float center = g_view->GetWidth() * 0.5f;
		if (m_fTextPosX + notice->width < center - 150.0f)
		{
			m_fTextPosX = center + 150.0f;
			if (--notice->repeat < 1)
			{
				delete *m_itrCurrent;
				m_itrCurrent = m_noticeList.erase(m_itrCurrent);
			}
			else
				++m_itrCurrent;
		}
	}
}

void CWinnerNotice::Display()
{
	FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
	if (!m_pNoticeL || !m_pNoticeM || !m_pNoticeR)
		return;
	float alpha = (m_fBgPosY + 50.0f) * 0.02f;
	if (Wabs(alpha) < g_EPSILON)
		return;
	WRect uv(0, 0, 1, 1);
	WRect dest(g_view->GetWidth() * 0.5f - 150.0f - 20.0f, m_fBgPosY,
		(float)m_pNoticeL->GetWidth(), (float)m_pNoticeL->GetHeight());
	m_pNoticeL->Render(g_view, uv, dest, 0, 0xa0ffffff, 0, 0);
	dest.x += dest.w;
	dest.w = 300.0f - m_pNoticeR->GetWidth() + 20.0f;
	dest.h = (float)m_pNoticeM->GetHeight();
	m_pNoticeM->Render(g_view, uv, dest, 0, 0xa0ffffff, 0, 0);
	dest.x += dest.w;
	dest.w = (float)m_pNoticeR->GetWidth();
	dest.h = (float)m_pNoticeR->GetHeight();
	m_pNoticeR->Render(g_view, uv, dest, 0, 0xa0ffffff, 0, 0);
	if (IS_EXACTKINDOF(CGolfTask, AfxGetTask()))
	{
		gdi->SetTextStyle(0);
		gdi->SetTextColor(0xffffffff, 0);
	}
	else
		gdi->SetTextStyle(0);
	if (m_itrCurrent != m_noticeList.end())
	{
		sWinnerNotice* notice = *m_itrCurrent;
		FrEmoticon* emoticon = g_pFresh->GetManager()->GetEmoticon();
		WRect clip(g_view->GetWidth() * 0.5f - 150.0f, 0, 300, 40);
		emoticon->SetClippingArea(&clip);
		if (emoticon)
			emoticon->SetAnim(true);
		emoticon->SetAnimTime(notice->startTime);
		for (int i = 0; i < notice->msgCount; ++i)
		{
			gdi->SetTextColor(0xffffffff, notice->msg[i].color);
			gdi->SetTextStyle(notice->msg[i].style);
			int x = (int)m_fTextPosX;
			emoticon->PrintText(WPoint(GetTextTailPoint(i) + x, 7.0f), 0,
				notice->msg[i].msg.c_str(), 0xffffffff);
		}
		emoticon->SetAnim(false);
		emoticon->SetClippingArea(NULL);
	}
	gdi->SetTextColor(0xffffffff, 0xffffffff);
	gdi->SetTextStyle(0);
}

bool CWinnerNotice::GetColornText(const char* src, std::string& text,
	unsigned long& color)
{
	color = 0xffffffff;
	cTokenV parser;
	if (parser.Init(src, strlen(src)))
	{
		char* prefix;
		bool more = parser.GetTokenFullSep(&prefix, "\\c", 2);
		if ((prefix && *prefix) || more)
		{
			if (more)
			{
				char* token;
				parser.GetTokenFullSep(&token, "\\c", 2);
				unsigned long parsedColor = 0xffffffff;
				cTokenV colors;
				if (colors.Init(token, strlen(token)))
				{
					bool next;
					do
					{
						char* value;
						next = colors.GetToken(&value, ",", 1);
						if (value && *value && strlen(value) > 1)
							sscanf(value, "%x", &parsedColor);
					} while (next);
				}
				color = parsedColor;
				std::string message(src);
				text = message.substr(message.rfind("\\c") + 2);
			}
			else
				text = src;
			return true;
		}
	}
	return false;
}

float CWinnerNotice::GetTextTailPoint(int count)
{
	FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
	sWinnerNotice* notice = *m_itrCurrent;
	float width = 0;
	for (int i = 0; i < count; ++i)
		width += gdi->GetTextExtend(notice->msg[i].msg.c_str());
	return width;
}

void CWinnerNotice::AddWinnerNotice(int repeat)
{
	sWinnerNotice* notice = new sWinnerNotice;
	notice->clear_data();
	notice->msgCount = m_winnerNotice.msgCount;
	notice->repeat = repeat;
	for (int i = 0; i < m_winnerNotice.msgCount; ++i)
	{
		notice->msg[i].color = m_winnerNotice.msg[i].color;
		notice->msg[i].style = m_winnerNotice.msg[i].style;
		notice->msg[i].msg = m_winnerNotice.msg[i].msg;
		notice->width +=
			m_pFont->GetTextWidth(g_view, m_winnerNotice.msg[i].msg.c_str());
	}
	notice->startTime = timeGetTime();
	unsigned int oldSize = m_noticeList.size();
	m_noticeList.push_back(notice);
	if ((!CCapturedBg::Instance() || !CCapturedBg::Instance()->IsCaptured()) &&
		oldSize == 0 && m_noticeList.size() == 1 && m_fBgPosY < -0.1f)
		g_audio->PlaySfx("goldentime_notice");
}

void CWinnerNotice::SetWinnerData(int type, std::string data)
{
	if (!m_pEventNotice)
		m_pEventNotice = (CGDEventNotice*)CGameDataDB::Instance()->GetGameData(
			GAMEDATA_EVENTNOTICE, "WinnerEventNotice");
	TiXmlDocument doc;
	ParseXmlData(doc, data.c_str());
	m_winnerNotice.clear_data();
	sNoticeMsg* messages = m_winnerNotice.msg;
	int count = 0;
	switch (type)
	{
	case 11:
		GetColornText(m_pEventNotice->GetText(1), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(2), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		messages[count].msg = GetItemNamefromXml(doc);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		GetItemCountfromXml(doc, messages[count].msg);
		++count;
		GetColornText(m_pEventNotice->GetText(3), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 12:
		GetColornText(m_pEventNotice->GetText(4), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(5), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		messages[count].msg = GetItemNamefromXml(doc);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		GetItemCountfromXml(doc, messages[count].msg);
		++count;
		GetColornText(m_pEventNotice->GetText(6), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 13:
		GetColornText(m_pEventNotice->GetText(7), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(8), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 14:
		GetColornText(m_pEventNotice->GetText(9), messages[count].msg,
			messages[count].color);
		++count;
		GetColornText(m_pEventNotice->GetText(10), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(11), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		messages[count].msg = GetItemNamefromXml(doc);
		++count;
		messages[count].color = 0xffff0000;
		messages[count].style = 2;
		GetItemCountfromXml(doc, messages[count].msg);
		++count;
		GetColornText(m_pEventNotice->GetText(12), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xffff9bcd;
		messages[count].style = 2;
		GetUserNamefromXml(doc, messages[count].msg);
		++count;
		GetColornText(m_pEventNotice->GetText(13), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 15:
		GetColornText(m_pEventNotice->GetText(14), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(15), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, true);
		++count;
		GetColornText(m_pEventNotice->GetText(16), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 16:
		GetColornText(m_pEventNotice->GetText(17), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_DAY, false);
		++count;
		GetColornText(m_pEventNotice->GetText(18), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_DAY, true);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, true);
		++count;
		GetColornText(m_pEventNotice->GetText(19), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 17:
		GetColornText(m_pEventNotice->GetText(20), messages[count].msg,
			messages[count].color);
		++count;
		break;
	case 18:
		GetColornText(m_pEventNotice->GetText(21), messages[count].msg,
			messages[count].color);
		++count;
		messages[count].color = 0xff050a9b;
		messages[count].style = 2;
		GetDaynTimefromXml(doc, messages[count].msg, EVENT_TIME, false);
		++count;
		GetColornText(m_pEventNotice->GetText(22), messages[count].msg,
			messages[count].color);
		++count;
		break;
	}
	m_winnerNotice.msgCount = count + 1;
	AddWinnerNotice(1);
}

void CWinnerNotice::ParseXmlData(TiXmlDocument& doc, const char* xml)
{
	doc.Clear();
	doc.Parse(xml);
}

void CWinnerNotice::GetEventNumfromXml(TiXmlDocument& doc, std::string& out,
	bool bNext)
{
	char buffer[50] = { 0 };
	TiXmlElement* element;
	if (bNext)
		element =
			doc.FirstChildElement("PARAMS")->FirstChildElement("NEXTTIMES");
	else
		element = doc.FirstChildElement("PARAMS")->FirstChildElement("TIMES");
	const char* number = element ? element->FirstChild()->Value() : NULL;
	sprintf(buffer, "%s \302\367\274\366 \300\314\272\245\306\256",
		number ? number : "0");
	out = buffer;
}

void CWinnerNotice::GetDaynTimefromXml(TiXmlDocument& doc, std::string& out,
	EventTimeFlag flag, bool bNext)
{
	char buffer[100] = { 0 };
	TiXmlElement* element;
	if (bNext)
		element =
			doc.FirstChildElement("PARAMS")->FirstChildElement("EVENTNEXTTIME");
	else
		element = doc.FirstChildElement("PARAMS")->FirstChildElement(
			"EVENTSTARTTIME");
	if (!element)
	{
		out = "0";
		return;
	}
	int year, month, day, hour, minute, unused;
	sscanf(element->FirstChild()->Value(), "%d-%d-%d %d:%d:%d.%d", &year,
		&month, &day, &hour, &minute, &unused, &unused);
	switch (flag)
	{
	case EVENT_DAY:
		sprintf(buffer, "%d \277\371 %d \300\317", month, day);
		break;
	case EVENT_TIME:
		sprintf(buffer, "%02d\275\303%02d\272\320", hour, minute);
		break;
	}
	out = buffer;
}

const char* CWinnerNotice::GetItemNamefromXml(TiXmlDocument& doc)
{
	TiXmlElement* item =
		doc.FirstChildElement("PARAMS")->FirstChildElement("TYPEID");
	if (!item)
		return "";
	unsigned long type = atoi(item->FirstChild()->Value());
	return ItemManager()->GetItemName(type);
}

void CWinnerNotice::GetItemCountfromXml(TiXmlDocument& doc, std::string& out)
{
	TiXmlElement* qty =
		doc.FirstChildElement("PARAMS")->FirstChildElement("QTY");
	TiXmlElement* type =
		doc.FirstChildElement("PARAMS")->FirstChildElement("TYPEID");
	if (!type)
	{
		out = "";
		return;
	}
	if (!qty)
	{
		out = "";
		return;
	}
	char buffer[100] = { 0 };
	if (atoi(type->FirstChild()->Value()) == 436207632)
	{
		sprintf(buffer, "(%d \306\316)", atoi(qty->FirstChild()->Value()));
		out = buffer;
	}
	else if (atoi(qty->FirstChild()->Value()) > 1)
	{
		sprintf(buffer, "(%d)", atoi(qty->FirstChild()->Value()));
		out = buffer;
	}
	else
		out = "";
}

void CWinnerNotice::GetUserNamefromXml(TiXmlDocument& doc, std::string& out)
{
	std::string nick;
	TiXmlElement* item =
		doc.FirstChildElement("PARAMS")->FirstChildElement("NICKNAME");
	if (!item)
		out = "";
	else
	{
		do
		{
			NickNameEdit((char*)item->FirstChild()->Value(), true, nick);
			out += "(" + nick + ")";
			item = item->NextSiblingElement();
		} while (item);
	}
}

void CWinnerNotice::NickNameEdit(char* name, bool bFirst, std::string& out)
{
	std::string nick;
	std::string mask("***");
	char buffer[50] = { 0 };
	nick = "";
	if (bFirst)
	{
		mbscut(buffer, name, strlen(name) - 2);
		nick = buffer;
		nick += mask;
		out = nick;
	}
	else
	{
		nick = name + 2;
		out = mask + nick;
	}
}
