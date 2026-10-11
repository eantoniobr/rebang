#pragma once
#include <vector>

#include "encrypttypes.h"
class CFxSequence;
class CWind
{
public:
	CWind();
	virtual ~CWind() { }

	void Init(unsigned char intensity, unsigned char direction,
		unsigned char hole, unsigned char bAbsolute);
	void Process(float delta);
	void Display(WPuppet* pPuppet, float x, float y);
	void DrawWindArea(WView* pView);
	void MakeWindList();

	WVector GetWind(const WVector& pos);
	WVector GetGlobalWind();
	float GetGlobalIntensity();
	float GetGlobalDirection();
	void SetIntensity(float intensity);
	void SetDirection(float direction);
	void SetWind(const WVector& wind);
	void PlusWind(const WVector& wind);
	bool IsGlobalWind_Compare();
	bool IsInTurbulence(const WVector& pos);
	bool IsInTurbulence(const WVector& from, const WVector& to);

	void SetActive(bool bActive) { m_bActive = bActive; }

	void SetSpecialWind(bool bSpecial);
	void GenerateFx(bool bGenerate);
	void CheckSpecialWind();
	bool HasSpecialWind() { return m_spIntensity > 0.0f; }

	bool IsActiveSpecialWind() { return m_bSpecialWind; }
	void SetSpWindStartFrame(unsigned long frame)
	{
		m_spWindStartFrame = frame;
	}
	unsigned long GetSpWindStartFrame() { return m_spWindStartFrame; }

protected:
	struct sWind
	{
		int index;
		Waabb area;
		WVector wind;
		unsigned char type;
		float intensity;
		float pitch;
		float yaw;
		int link;
	};

	bool IsInclude(const Waabb& area, const WVector& pos);
	void AddWindArea(const Waabb& area, char* param);

	unsigned long m_spWindStartFrame;
	WVector m_wind;
	WCrypticValue<float> m_intensity;
	WCrypticValue<float> m_direction;
	float m_roll;
	WMatrix m_camera;
	LightSet m_light;
	float m_heading;
	float m_minIntensity;
	float m_maxIntensity;
	WCrypticValue<bool> m_bActive;
	std::vector<sWind> m_windList;
	WVector m_globalWindRef;
	WVector m_globalWind;
	WVector m_specialWind;
	WCrypticValue<float> m_spIntensity;
	WCrypticValue<float> m_spDirection;
	bool m_bSpecialWind;
	WMatrix m_fxMatrix;
	WVector m_fxPos;
	CFxSequence* m_pFx;
};

CWind& Wind();
