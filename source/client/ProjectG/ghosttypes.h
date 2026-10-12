#pragma once

struct GHOST_GAME_BRIEF
{
	unsigned long owner;
	int course;
	unsigned long itemId;
	int score;
	int pang;
	unsigned long recordId;
	int recordCount;
	bool operator==(int value) const { return course == value; }
};
