#pragma once

#include <list>
#include "../../shared/globalgamedefine.h"

struct sMailBoxListForPage
{
	std::list<sMailInfoBrief> mailList;
	int curPage;
	int totalPage;
	int mailCount;
};
