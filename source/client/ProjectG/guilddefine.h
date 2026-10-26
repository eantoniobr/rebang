#pragma once

#include "wlocalize.h"

static const char* s_guildJoinDateFormat =
	K2L_Compatibility(" - %d\xb3\xe2 %d\xbf\xf9 %d\xc0\xcf %s\n");

namespace _guild
{
	typedef std::list<GUILD_USER_LIST>::iterator MEMBER_LIST_IT;
	typedef std::list<GUILD_LIST>::iterator SEARCH_LIST_IT;

	int ConvertGuildHistory(GUILD_STATE_IDX state);
}
