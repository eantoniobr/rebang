#pragma once

struct defines_t
{
	char name[16][260];
	float value[16];
	int num;
};

class CFxBox;
class CFxSequence;
struct CFxParticle;
struct Attacher;

// TODO: incomplete
class CFxSpray
{
public:
	virtual ~CFxSpray();
	void SetActive(bool active);
	WVector& Pos();
	WVector& Vel();
	void SetWind(const WVector& wind);
	void SetLight(const LightSet& light);

	bool m_bMark;
	Attacher* m_attacher;
	float m_centerX;
	float m_centerY;
	WMatrix* m_attachMat[4];
	WVector* m_attachPos[4];
	defines_t m_defines;
	char m_filename[64];
	CFxBox& m_fxBox;
	std::list<CFxParticle*> m_particle;
	CFxSequence* m_parent;
	bool m_bActive;
	float m_time;
	WVector m_quake;
	WVector m_quakePos;
	unsigned char m_flash;
	int m_particleNum;
	int m_tailNum;
	WVector m_pos;
	WVector m_bgPos;
	WVector m_vel;
};

#include "fxspray.inl"
