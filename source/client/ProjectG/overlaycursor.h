#pragma once

#include <map>
class FrWnd;
class WOverlay;

struct sOCItem
{
	int type;
	WOverlay* pOverlay;
	int x;
	int y;
	sOCItem()
	{
		type = 0;
		pOverlay = NULL;
		x = 0;
		y = 0;
	}
};

class COverlayCursor
{
public:
	enum eCursorType
	{
		CT_NORMAL,
		CT_DRAG,
		CT_ERASER,
		CT_EYEDROPPER,
		CT_PAINT,
		CT_SELECT_COLOR,
		CT_ZOOM_IN,
		CT_ZOOM_OUT
	};
	COverlayCursor();
	~COverlayCursor();

	void Add(eCursorType type, const char* filename, int x, int y);
	void Render();

	void SetRect(FrWnd** ppRect) { m_ppRect = ppRect; }

	void SetCursor(eCursorType type) { m_cursor = type; }

private:
	std::map<int, sOCItem> m_items;
	FrWnd** m_ppRect;
	eCursorType m_cursor;
};
