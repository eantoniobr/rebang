#pragma once
#include <map>
#include <list>
#include <string>
#include "fxspray.h"
class CFxSequence
{
public:
	struct sLine
	{
		int number;
		unsigned int start, end, time;
		char text[260];
	};
	CFxSequence(CFxBox& box, bool temporary);
	virtual ~CFxSequence();
	void Clear();
	void SetActive(bool bActive, bool bChild);
	WVector& Pos();
	std::map<CFxSpray*, CFxSpray*>& GetSprayList();
	void SetDelay(float delay);
	void GetBoneMatrix(WMatrix* mat);
	void SetWind(const WVector& wind);
	void SetLight(const LightSet& light);
	void SetDistLimit(float nearLimit, float farLimit);
	void AddLine(const char* text, int number);
	bool LoadFile(const char* filename);
	const sLine& GetLastError();

protected:
	void SetLineTime();
	bool ParseLine(const char* text, bool& error);
	bool Process(float elapsed, bool& error);

private:
	void DeleteChildSpray(CFxSpray* spray);

public:
	bool m_bMark;
	WVector m_wind;
	void* m_attacher;
	float m_centerX, m_centerY;
	std::map<CFxSpray*, CFxSpray*> m_spray;
	WMatrix* m_attachMat[4];
	WVector* m_attachPos[4];
	defines_t m_defines;
	WMatrix m_rot;
	CFxBox& m_fxBox;
	bool m_bActive;
	WVector m_pos;
	WVector m_vel;
	bool m_bDelete;
	float m_time;
	float m_delay;
	sLine m_lastError;
	CFxSpray* m_lastSpray;
	std::list<sLine> m_lines;
	std::list<sLine>::iterator m_current;
	std::string m_filename;
};
#include "fxsequence.inl"
