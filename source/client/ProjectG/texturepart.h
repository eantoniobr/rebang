#pragma once

#include <string.h>
#include <list>

struct sTexturePart
{
	char name[64];
	char part[64];
	Bitmap* bitmap;
	RECT rect;

	sTexturePart()
	{
		memset(name, 0, sizeof(name));
		memset(part, 0, sizeof(part));
		memset(&rect, 0, sizeof(rect));
		bitmap = NULL;
	}

	~sTexturePart()
	{
		if (bitmap)
		{
			delete bitmap;
			bitmap = NULL;
		}
	}
};

struct sFindTexPart
{
	const char* m_part;

	sFindTexPart(const char* part)
		: m_part(part)
	{
	}

	bool operator()(const sTexturePart* p) const
	{
		return strcmpi(p->part, m_part) == 0;
	}
};

typedef std::list<sTexturePart*>::iterator TexPartIter;
