#pragma once

#include <list>
#include <vector>
#include <string>
#include "wtypes.h"
#include "wmath.h"

class Bitmap;

class CParticle2D
{
public:
	enum eSTYLE
	{
		STYLE_NORMAL = 0,
		STYLE_TWINKLE = 1,
	};

	struct sParticle
	{
		float x;
		float y;
		float dx;
		float dy;
		const Bitmap* bitmap;
		float alpha;
		int bFadeIn;
		float speed;
		int bLive;
		WRect src;
		WRect dest;
	};

	CParticle2D() { }
	~CParticle2D();

	int Initialize(const std::list<std::string>& bitmaps, const WRect& rect,
		unsigned int count, eSTYLE style, float minSpeed, float maxSpeed,
		const WVector2D& minDir, const WVector2D& maxDir);
	void Process(float dt);
	void Display();
	void Release();

private:
	void MakeDisplayRect(sParticle* p);

	WRect m_rect;
	eSTYLE m_style;
	unsigned int m_count;
	float m_minSpeed;
	float m_maxSpeed;
	WVector2D m_minDir;
	WVector2D m_maxDir;
	std::list<sParticle*> m_particle;
	std::vector<const Bitmap*> m_bitmap;
};
