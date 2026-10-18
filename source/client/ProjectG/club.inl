#pragma once

inline bool CClub::Updated()
{
	return (m_flag & 1) != 0;
}

inline bool CClub::IsPowerPutter()
{
	return m_bPowerPutter;
}

inline bool CClub::Is(char* name, sClub* club)
{
	char* result;
	if (club)
		result = strstr(club->name, name);
	else
		result = strstr(m_pClub->name, name);
	return result != NULL;
}
