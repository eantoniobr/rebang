#pragma once

#include <string>
#include <list>
#include "singleton.h"

class ntBalloonText
{
public:
	ntBalloonText(unsigned long uid, const char* text, const float* const color,
		float lifeTime);
	~ntBalloonText();

	void SetText(const char* text);
	bool Process(float delta);
	void Render(WView* view);

	bool IsVisible() const { return m_elapsed < m_lifeTime ? true : false; }

	void SetTransparency(float alpha) { m_color[3] = alpha; }

private:
	const char* StripSpecialText(const char* text) const;

	unsigned long m_uid;
	std::string m_text;
	bool m_bUpdated;
	int m_x;
	bool m_bThink;
	float m_color[4];
	float m_lifeTime;
	float m_elapsed;

	friend class ntBalloonTextManager;
};

class ntBalloonTextManager : public WSingleton<ntBalloonTextManager>
{
public:
	void Init();
	void Shutdown();
	void DeleteAll();
	void Process(float delta);
	void Render();
	ntBalloonText* CreateBalloonText(unsigned long uid, const char* text,
		const float* const color, float lifeTime);
	void DeleteBalloonText(ntBalloonText* balloon);

	std::list<ntBalloonText*> m_list;
	WFont* m_pFont;
	WOverlay* m_pFrame[9];
	WOverlay* m_pTail;
	WOverlay* m_pThinkFrame;
	WOverlay* m_pThinkTail;
	int m_leftWidth;
	int m_topHeight;
	int m_rightWidth;
	int m_bottomHeight;
};
