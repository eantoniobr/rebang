#pragma once

class CGolfDoc;

class CRival : public WSingleton<CRival>
{
public:
	CRival();
	virtual ~CRival();

	void SetVariable(CGolfDoc* pDoc);
	void Shot();
	void SetResult();
	WVector GetPos() { return m_pos; }

private:
	WVector GetGreenSlope();

	WVector m_pos;
	WVector m_resultPos;
	int m_unknown40;
	float m_angle;
	float m_power;
	int m_club;
	int m_result;
	float m_curve;
	float m_spin;
};
