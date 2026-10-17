#pragma once

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

enum wUnitMode
{
	W_UNIT_XPOS = 0,
	W_UNIT_YPOS = 1,
	W_UNIT_WIDTH = 2,
	W_UNIT_HEIGHT = 3
};

struct _WPOINT
{
	float x, y;
};
struct _WSIZE
{
	float w, h;
};
struct _WRECT
{
	float x, y, w, h;
};

class WPoint : public _WPOINT
{
public:
	WPoint() { }
	WPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	WPoint(WPoint& p)
	{
		x = p.x;
		y = p.y;
	}
	WPoint(WPoint* p)
	{
		x = p->x;
		y = p->y;
	}
	void Offset(WPoint& p)
	{
		x += p.x;
		y += p.y;
	}
	void Offset(float dx, float dy)
	{
		x += dx;
		y += dy;
	}
	int operator==(WPoint& _p) const { return (x == _p.x && y == _p.y); }
	int operator!=(WPoint& _p) const { return !(x == _p.x && y == _p.y); }
	void operator+=(WPoint& p)
	{
		x += p.x;
		y += p.y;
	}
	void operator-=(WPoint& p)
	{
		x -= p.x;
		y -= p.y;
	}
	WPoint operator-() const { return WPoint(-x, -y); }
	WPoint operator+(WPoint& p) const { return WPoint(x + p.x, y + p.y); }
	WPoint operator-(WPoint& _p) const { return WPoint(x - _p.x, y - _p.y); }
};

class WSize : public _WSIZE
{
public:
	WSize() { }
	WSize(float w, float h)
	{
		this->w = w;
		this->h = h;
	}
	WSize(WSize& s)
	{
		w = s.w;
		h = s.h;
	}
	WSize(WSize* s)
	{
		w = s->w;
		h = s->h;
	}
	int operator==(WSize& s) const { return (w == s.w && h == s.h); }
	int operator!=(WSize& s) const { return !(w == s.w && h == s.h); }
	void operator+=(WSize& s)
	{
		w += s.w;
		h += s.h;
	}
	void operator-=(WSize& s)
	{
		w -= s.w;
		h -= s.h;
	}
	WSize operator+(WSize& _s) const { return WSize(w + _s.w, h + _s.h); }
	WSize operator-() const { return WSize(-w, -h); }
	WSize operator-(WSize& s) const { return WSize(w - s.w, h - s.h); }
};

class WRect : public _WRECT
{
public:
	__forceinline WRect() { }

	template <class Width, class Height>
	WRect(float x, float y, Width width, Height height)
	{
		this->x = x;
		this->y = y;
		this->w = width;
		this->h = height;
	}
	WRect(const WRect& rect)
	{
		x = rect.x;
		y = rect.y;
		w = rect.w;
		h = rect.h;
	}
	WRect(const _WRECT& rect)
	{
		x = rect.x;
		y = rect.y;
		w = rect.w;
		h = rect.h;
	}
	WRect operator+(WPoint& point) const;
	WRect operator-(WPoint& point) const;
	WRect operator+(WRect& rect) const;
	float Right() const { return w + x; }
	float Bottom() const { return h + y; }
	int operator!=(WRect& rect) const
	{
		return !(x == rect.x && y == rect.y && w == rect.w && h == rect.h);
	}
	bool IsInRect(const WPoint& point);
	bool IsInRect(float x, float y);
	WRect(const WPoint& pt, const WSize& size)
	{
		x = pt.x;
		y = pt.y;
		w = size.w;
		h = size.h;
	}
	template <class Width, class Height>
	WRect(const WPoint& pt, Width width, Height height);

	WPoint TopLeft() const { return WPoint(x, y); }
	WSize Size() const { return WSize(w, h); }
};

template <>
inline WRect::WRect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
}

inline WRect WRect::operator+(WPoint& point) const
{
	return WRect(x + point.x, y + point.y, w, h);
}

inline WRect WRect::operator-(WPoint& point) const
{
	return WRect(x - point.x, y - point.y, w, h);
}

template <>
inline WRect::WRect(const WPoint& pt, float width, float height)
{
	x = pt.x;
	y = pt.y;
	w = width;
	h = height;
}

inline WRect WRect::operator+(WRect& rect) const
{
	return WRect(x + rect.x, y + rect.y, w + rect.w, h + rect.h);
}

template <class Width, class Height>
inline WRect::WRect(const WPoint& pt, Width width, Height height)
{
	x = pt.x;
	y = pt.y;
	w = (float)width;
	h = (float)height;
}

inline bool WRect::IsInRect(float x, float y)
{
	if (x >= this->x && this->x + w >= x && y >= this->y && this->y + h >= y)
		return true;
	return false;
}

inline bool WRect::IsInRect(const WPoint& point)
{
	if (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h)
		return true;
	return false;
}
