#pragma once

#include <string.h>
#include "ghosttypes.h"

struct GHOST_DATA_HEADER
{
	unsigned int version;
	unsigned int userDataSize;
	unsigned int gameDataSize;
	unsigned int shotDataSize;
	unsigned int shotCount;
	unsigned int cardDataSize;
	unsigned int cardCount;
	unsigned int GetDataBodySize()
	{
		return userDataSize + gameDataSize + shotDataSize * shotCount +
			cardDataSize * cardCount;
	}
};

template <int N>
void py_strcpy(char (&dst)[N], const char* src)
{
	memset(dst, 0, N);
	memcpy(dst, src, N - 1);
}

struct GHOST_SHOT_PROTOCOL
{
	float maxClick;
	float minClick;
	float curve;
	float spin;
	unsigned char accuracy;
	int special;
	int frame;
	float shotAngle;
	int shotTime;
	float center;
	unsigned char clubIndex;
	float randomPower;
	float randomAngle;
};

struct GHOST_USER_DATA
{
	unsigned long charTypeId;
	unsigned char hairColor;
	unsigned char shirtsColor;
	unsigned long partTypeId[24];
	unsigned long auxPartTypeId[5];
	unsigned char charPcl[5];
	unsigned char charReserved[0xd8];
	unsigned long clubTypeId;
	short clubPcl[5];
	unsigned long ballTypeId;
	unsigned long caddieTypeId;
	unsigned long caddiePartsTypeId;
	unsigned char caddieLevel;
	unsigned long mascotTypeId;
	char mascotMsg[32];
	unsigned long itemSlot[10];
	char nickname[32];
	char id[32];
	char guildName[32];
	unsigned long capability;
	char guildMark[32];
	unsigned char female;
	unsigned char angelWing;
	unsigned char angelEffect;
	unsigned char devilWing;
	unsigned char level;
	unsigned long uid;
};

inline const char* MakeGhostGameFileName(const GHOST_GAME_BRIEF* brief)
{
	return MakeStr("%d_%d_%d_%d_%d_%d.GST", brief->owner, brief->course,
		brief->itemId, brief->score, brief->pang, brief->recordId);
}

inline unsigned long GetGhostGameBriefFromFileName(GHOST_GAME_BRIEF* brief,
	const char* fileName)
{
	sscanf(fileName, "%d_%d_%d_%d_%d_%d.GST", &brief->owner, &brief->course,
		&brief->itemId, &brief->score, &brief->pang, &brief->recordId);
	return brief->owner;
}
