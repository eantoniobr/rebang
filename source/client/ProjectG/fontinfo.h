#pragma once

#include "wmath.h"

class WTitleFont;
class CFontInfo
{
public:
	struct sFontInfo;
	struct sFont
	{
		WTitleFont* pFont;
		sFontInfo* pInfo;
	};

	CFontInfo();
	virtual ~CFontInfo();
	void SetColor(unsigned long color) { m_color = color; }
	virtual void Process(float dt) { }
	virtual void Display() { }
	virtual void Init(char* name, sFont* font);
	virtual void GetScreenPos(float* x, float* y) { }
	virtual void Reset() { }

protected:
	sFont m_font;
	unsigned long m_color;
	int m_align;
	char* m_buffer;
};

class CClubRangeInfo : public CFontInfo
{
public:
	CClubRangeInfo();
	virtual void Display();
	void SetPos(const WVector& pos) { m_pos = pos; }

private:
	WVector m_pos;
};
