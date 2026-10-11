#pragma once

#include "encrypttypes.h"

class CClub
{
public:
	struct sClub
	{
		WCrypticValue<float> range;
		WCrypticValue<float> lie;
		unsigned char id;
		unsigned char index;
		unsigned char type;
		WCrypticValue<float> power;
		WCrypticValue<float> curve;
		WCrypticValue<float> spin;
		char name[4];
		float pointFactor;
		WCrypticValue<float> barSpeed;
	};

	void SetClub(const char* name);
	void SetClub(unsigned char index);
	void SelectBestClub(const WVector& target);
	void SelectBestClub();
	void AddCrypticValue();
	void Process(float dt);

	float GetRange(const char* name = NULL);
	float GetPower();
	float GetNarrowAccuracy();
	void SetAccuracy();
	float GetWideAccuracy();
	float GetBarSpeed() { return m_pClub->barSpeed; }
	unsigned char GetType() { return m_pClub->type; }
	char* GetName() { return m_pClub->name; }
	float GetLie(const char* name = NULL);
	void SetApproachMode();
	void SetPowerShot(int type) { m_powerShot = type; }
	int PowerShotType() { return m_powerShot; }
	unsigned char GetApproachMode() { return m_approachMode; }
	unsigned char GetIndex() { return m_pClub->index; }
	unsigned char GetID() { return m_pClub->id; }
	bool BarIs(int state) { return m_bar == state; }
	void SetRandomPower(float power) { m_randomPower = power; }
	float GetRandomPower() const { return m_randomPower; }
	void SetCalcRandomPower(bool bCalc) { m_bCalcRandomPower = bCalc; }

private:
	int m_reserved;
	sClub* m_pClub;
	WList<sClub*> m_clubList;
	unsigned char m_curIndex;
	unsigned char m_limitIndex;
	WCrypticValue<int> m_powerShot;
	unsigned char m_approachMode;
	unsigned char m_unused3d[0x17];
	int m_bar;
	bool m_bItemWindow;
	unsigned char m_prevIndex;
	float m_narrowAccuracy;
	float m_wideAccuracy;
	float m_randomPower;
	bool m_bCalcRandomPower;
	// TODO: incomplete
};

CClub& GolfClub();
