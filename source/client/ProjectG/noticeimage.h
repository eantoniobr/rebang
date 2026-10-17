#pragma once

#include <list>
#include <vector>

struct sNoticeImage
{
	struct sBn
	{
		sBn() { }

		int typeId;
		WRect rect;
	};

	sNoticeImage() { name[0] = 0; }

	char name[32];
	std::list<sBn> bnList;
};

void LoadNoticeImageFile(const char* filename,
	std::vector<sNoticeImage>& images, int maxNum, const char* lang);
