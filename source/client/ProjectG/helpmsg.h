#pragma once

struct sItemInfo;

class CHelpMsg : public WSingleton<CHelpMsg>
{
public:
	CHelpMsg();
	virtual ~CHelpMsg();

	void ResetUiPosition();
	void Process(float delta);
	void Display();
	void SetItemHelpMsg(unsigned long typeId);
	void SetHelpMsg(int id, char* param);
	void SetEmoticonHelpMsg(char** msg);
	void OnChangeTurn();
	void CheckReplayAvailable();

private:
	void CalcWindowSize(char* title, char* msg);
	int GetLine(int* pBegin, int* pEnd, unsigned long* pColor, char* str,
		bool bSkipSpace);

private:
	WOverlay* m_pOverlay;
	char* (*m_helpMsg)[3];
	int m_helpId;
	WFont* m_pFont;
	WRect m_srcRect[3];
	WRect m_dstRect[3];
	unsigned long m_itemTypeId;
	char m_title[32];
	char m_msg[256];
	char m_key[16];
	char m_param[64];
	float m_time;
	bool m_bItemChanged;
	sItemInfo* m_pReplayTape;
};
