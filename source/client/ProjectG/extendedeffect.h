#pragma once

#include <map>
#include <list>
#include <string>

class CPetFrame;
class CFxSequence;

class CExtendedEffect
{
public:
	struct sEffectData
	{
		unsigned long tid;
		std::string bone;
		std::string filename;
		bool loop;
		CFxSequence* sequence;
	};
	struct sAvatarInfo
	{
		CPetFrame* pet;
		std::list<sEffectData> effects;
	};
	CExtendedEffect();
	virtual ~CExtendedEffect();
	int RegistExtenedEffect(CPetFrame* pet);
	void Update(CPetFrame* pet);

private:
	int AddEffect(unsigned long tid, const char* bone, const char* filename,
		bool loop);
	sEffectData* FindEffect(unsigned long tid);
	int RegistSequence(unsigned long tid, std::list<sEffectData>* list);

	std::map<unsigned long, sEffectData> m_effectMap;
	std::list<sAvatarInfo> m_avatarList;
};
