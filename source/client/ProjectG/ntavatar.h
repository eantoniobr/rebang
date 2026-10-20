#pragma once

#include "../../shared/globalgamedefine.h"

class ntAvatar
{
public:
	bool GetBoneScreenCoord(const char* bone, int* x, int* y) const;
	const sCharacterInfo& GetCharacterInfo() const { return m_charInfo; }

private:
	unsigned char m_unknown[0x3d9];
	sCharacterInfo m_charInfo;
};
