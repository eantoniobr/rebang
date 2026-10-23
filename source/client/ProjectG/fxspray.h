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
	friend class CFxBox;

public:
	struct sRevol
	{
		sRevol() { }
		WVector center;
		WVector axis;
		int start;
		float speed;
		int end;
		float acceleration;
	};

	struct sNozzleRot
	{
		sNozzleRot() { }
		WVector axis;
		int start;
		float speed;
		int end;
		float acceleration;
	};

	struct sSound
	{
		char name[260];
		float range;
	};

	struct sSpawn
	{
		int type;
		char name[260];
		bool attached;
		float time;
		int count;
	};

	CFxSpray(CFxBox& box);
	bool ParseFile(const char* name, bool useOriginal);

protected:
	bool Process(float elapsed);
	void Display(WView* view);

public:
	void SetDistLimit(float nearLimit, float farLimit);
	virtual ~CFxSpray();
	void SetActive(bool active);
	WVector& Pos();
	WVector& Vel();
	WVector& InitialMinVel() { return m_initialMinVel; }
	WVector& InitialMaxVel() { return m_initialMaxVel; }
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
	unsigned char m_unused115c[100];
	bool m_strongBond;
	unsigned char m_unused11c1[2];
	bool m_attachedToParent;
	unsigned long m_parentMask;
	unsigned char m_unused11c8[648];
	int m_tailTexHandle;
	unsigned char m_unused1454[8];
	WVector m_initialMinVel;
	WVector m_initialMaxVel;
	unsigned char m_unused1474[96];
	std::list<sNozzleRot> m_nozzleRotation;
	std::list<sNozzleRot> m_rotation;
	std::list<sRevol> m_revolution;
	std::list<sRevol> m_parentRevolution;
	unsigned char m_unused1504[116];
	std::list<sSpawn> m_spawn;

	std::list<sSound> m_sounds;
	bool m_evenSphere;
	unsigned char m_unused1594[4];
	float m_sphereAngle;
};

#include "fxspray.inl"
