#include "stdafx.h"
#include "fxbox.h"
#include "fxbox.inl"
#include "fx.h"
#include "golfball.h"
#include "club.h"
#include "quadtree.h"
#include "contentsdoc.h"
#include "soundmanager.h"
#include "taskmanager.h"
#include "mathconsts.h"
extern WMatrix g_camera;
extern HWND g_hwnd;

class CFxControl
{
public:
	static unsigned long ms_serial;

	virtual ~CFxControl() { }
	virtual bool Process(float elapsed) = 0;

	unsigned long m_serial;
};

class CFxRunDust : public CFxControl
{
public:
	CFxRunDust(CPvsFxBox& fxBox, const WVector& pos, const WVector& vel);
	virtual ~CFxRunDust();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	const WVector& m_pos;
	const WVector& m_vel;
	CFxSequence* m_ground;
	CFxSequence* m_water;
	unsigned char m_unused[4];
};

class CFxCobra : public CFxControl
{
public:
	CFxCobra(CPvsFxBox& fxBox, const CGolfBall& ball);
	virtual ~CFxCobra();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	const CGolfBall& m_ball;
	CFxSequence* m_seq[4];
	bool m_bLaunched;
};

class CFxTomahawk : public CFxControl
{
public:
	CFxTomahawk(CPvsFxBox& fxBox, const CGolfBall& ball, bool bTrajectory);
	virtual ~CFxTomahawk();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	const CGolfBall& m_ball;
	CFxSequence* m_seq;
	bool m_bTrajectory;
	int m_step;
};

class CFxPowerSpin : public CFxControl
{
public:
	CFxPowerSpin(CPvsFxBox& fxBox, CGolfBall& ball);
	virtual ~CFxPowerSpin();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	CGolfBall& m_ball;
	CFxSequence* m_seq;
	bool m_bRotated;
};

class CFxShotImpact : public CFxControl
{
public:
	CFxShotImpact(CPvsFxBox& fxBox, CGolfBall& ball);
	virtual ~CFxShotImpact();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	CGolfBall& m_ball;
	CFxSequence* m_seq;
	bool m_bRotated;
};

class CFxClubImpact : public CFxControl
{
public:
	CFxClubImpact(CPvsFxBox& fxBox, CGolfBall& ball, unsigned long clubId);
	virtual ~CFxClubImpact();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	CGolfBall& m_ball;
};

class CFxSpike : public CFxControl
{
public:
	CFxSpike(CPvsFxBox& fxBox, const CGolfBall& ball, bool bTrajectory);
	virtual ~CFxSpike();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	const CGolfBall& m_ball;
	CFxSequence* m_seq[2];
	bool m_bTrajectory;
	int m_step;
};

class CFxPowerShot2 : public CFxControl
{
public:
	CFxPowerShot2(CPvsFxBox& fxBox, CGolfBall& ball);
	virtual ~CFxPowerShot2();
	virtual bool Process(float elapsed);

protected:
	bool m_bDone;
	CPvsFxBox& m_fxBox;
	CGolfBall& m_ball;
};

class CFxBoosterWarp : public CFxControl
{
public:
	CFxBoosterWarp(CPvsFxBox& fxBox, CGolfBall& ball, unsigned char type);
	virtual ~CFxBoosterWarp();
	virtual bool Process(float elapsed);

protected:
	CPvsFxBox& m_fxBox;
	CGolfBall& m_ball;
	CFxSequence* m_seq[2];
	bool m_bReady;
	float m_time;
	bool m_bSlide;
};

unsigned long CFxControl::ms_serial = 0;

Attacher::Attacher()
{
	x = g_HUGE;
	y = g_HUGE;
	for (int i = 0; i < 4; ++i)
	{
		mat[i] = NULL;
		pos[i] = NULL;
	}
}

bool Attacher::Get(WVector& out)
{
	out.Reset();
	int i;
	for (i = 0; i < sizeof(mat) / sizeof(mat[0]); ++i)
	{
		WMatrix* m = NULL;
		WVector* p = pos[i];
		m = mat[i];
		if (p)
		{
			WVector temp;
			if (m)
			{
				temp.x = ((p->y * m->xy) + p->z * m->xz) + p->x * m->xx + m->xm;
				temp.y = (p->x * m->yx + p->y * m->yy) + p->z * m->yz + m->ym;
				temp.z = (p->x * m->zx + p->y * m->zy) + p->z * m->zz + m->zm;
				p = &temp;
			}

			out += *p;
		}
		else
		{
			if (!m)
				break;
			float ilpad0 = out.x;
			float ilpad1 = out.x;
			out += m->pivot;
		}
	}

	if (i > 0)
	{
		out *= 1.0f / i;
		return true;
	}

	return false;
}

void CPvsFxBox::ProcessAttacher(float elapsed)
{
	WVector pos;
	for (std::map<CFxSequence*, CFxSequence*>::iterator it = m_sequence.begin();
		it != m_sequence.end(); ++it)
	{
		CFxSequence* seq = (*it).second;
		std::map<CFxSequence*, Attacher>::iterator at = m_seqAttacher.find(seq);
		if (at != m_seqAttacher.end() && (*at).second.Get(pos))
			seq->Pos() = pos;
	}

	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it)
	{
		CFxSpray* spray = (*it).second;
		std::map<CFxSpray*, Attacher>::iterator at =
			m_sprayAttacher.find(spray);
		if (at != m_sprayAttacher.end() && (*at).second.Get(pos))
			spray->Pos() = pos;
	}
}

bool CPvsFxBox::CheckGroundCollision(const WVector& from, const WVector& to,
	float& height, float radius)
{
	if (height > m_groundHeightMax || height < m_groundHeightMin)
		return false;
	float fromHeight = GetPVS().GetGroundPoint(from, true, NULL, true).y;
	float toHeight = GetPVS().GetGroundPoint(to, true, NULL, true).y;
	height = toHeight;
	if (IsEqual(to.y, toHeight))
		return true;
	if (to.y < toHeight)
	{
		if (IsEqual(from.y, fromHeight) || from.y < fromHeight)
			return IsEqual(to.y + radius, toHeight) || to.y + radius > toHeight;
	}
	else
	{
		if (IsEqual(from.y, fromHeight) || from.y > fromHeight)
			return IsEqual(to.y - radius, toHeight) || to.y - radius < toHeight;
	}

	return true;
}

void CPvsFxBox::OnSequenceCreated(CFxSequence* sequence)
{
	if (!sequence->m_attacher)
		return;
	m_seqAttacher.insert(std::pair<CFxSequence* const, Attacher>(sequence,
		*(Attacher*)sequence->m_attacher));
	sequence->m_attacher = &m_seqAttacher[sequence];
	memcpy(sequence->m_attachMat, m_seqAttacher[sequence].mat,
		sizeof(sequence->m_attachMat));
	memcpy(sequence->m_attachPos, m_seqAttacher[sequence].pos,
		sizeof(sequence->m_attachPos));
}

void CPvsFxBox::OnSequenceDeleted(CFxSequence* sequence)
{
	std::map<CFxSequence*, Attacher>::iterator it =
		m_seqAttacher.find(sequence);
	if (it != m_seqAttacher.end())
		m_seqAttacher.erase(it);
}

void CPvsFxBox::OnSprayCreated(CFxSpray* spray)
{
	if (!spray->m_attacher)
		return;
	m_sprayAttacher.insert(
		std::pair<CFxSpray* const, Attacher>(spray, *spray->m_attacher));
	spray->m_attacher = &m_sprayAttacher[spray];
	memcpy(spray->m_attachMat, m_sprayAttacher[spray].mat,
		sizeof(spray->m_attachMat));
	memcpy(spray->m_attachPos, m_sprayAttacher[spray].pos,
		sizeof(spray->m_attachPos));
}

void CPvsFxBox::OnSprayDeleted(CFxSpray* spray)
{
	std::map<CFxSpray*, Attacher>::iterator it = m_sprayAttacher.find(spray);
	if (it != m_sprayAttacher.end())
		m_sprayAttacher.erase(it);
}

void CPvsFxBox::UpdateLightSrc(const LightSet& light)
{
	for (std::map<CFxSequence*, CFxSequence*>::iterator it = m_sequence.begin();
		it != m_sequence.end(); ++it)
	{
		std::map<CFxSpray*, CFxSpray*>& list = (*it).second->GetSprayList();
		for (std::map<CFxSpray*, CFxSpray*>::iterator s = list.begin();
			s != list.end(); ++s)
			(*s).second->SetLight(light);
	}

	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it)
		(*it).second->SetLight(light);
}

CFx::CFx()
{
	m_pvsFxBox.Init(g_resrcmng);
	m_pvsFxBox.SetCamera(&g_camera);
	m_pvsFxBox.m_frameTime = 1000.f / 30.f;
	m_bActive = true;
}

CFx::~CFx()
{
	ClearControl();
}

void CFx::Process(float elapsed)
{
	if (!m_bActive)
		return;
	m_pvsFxBox.ProcessAttacher(elapsed);
	for (std::map<int, CFxControl*>::iterator it = m_control.begin();
		it != m_control.end();)
	{
		CFxControl* control = (*it).second;
		if (!control->Process(elapsed))
		{
			m_control.erase(it++);
			delete control;
		}
		else
		{
			++it;
		}
	}

	m_pvsFxBox.Process(elapsed * 1000.f);
}

void CFx::Display()
{
	if (m_bActive)
		m_pvsFxBox.Display(g_view);
}

CFxSequence* CFx::OpenSequence(const char* filename, bool bDelete)
{
	CFxSequence* seq = m_pvsFxBox.LoadSequence(filename, bDelete, NULL);
	if (seq)
		m_pvsFxBox.AddSequence(seq);
	return seq;
}

void CFx::CloseSequence(CFxSequence* seq, bool bDeleteChild)
{
	m_pvsFxBox.DeleteSequence(seq, bDeleteChild);
}

CFxSpray* CFx::OpenSpray(const char* filename)
{
	CFxSpray* spray = m_pvsFxBox.LoadSpray(filename, NULL);
	if (spray)
		m_pvsFxBox.AddSpray(spray);
	return spray;
}

void CFx::CloseSpray(CFxSpray* spray)
{
	m_pvsFxBox.DeleteSpray(spray);
}

void CFx::ClearAll(bool bMarkedOnly)
{
	ClearControl();
	m_pvsFxBox.ClearAll(bMarkedOnly);
}

void CFx::AddFxKeeper(sFxKeeper& keeper)
{
	m_pvsFxBox.AddFxKeeper(keeper);
}

void CFx::EraseFxKeeper(CFxKeeper* keeper)
{
	m_pvsFxBox.EraseFxKeeper(keeper);
}

void CFx::ClearFxKeeper()
{
	m_pvsFxBox.ClearFxKeeper();
}

CFxSpray* CFx::GetSpray(int index)
{
	return m_pvsFxBox.GetSpray(index);
}

bool CFx::FindSequence(CFxSequence* seq)
{
	return m_pvsFxBox.FindSequence(seq);
}

bool CFx::FindSpray(CFxSpray* spray)
{
	return m_pvsFxBox.FindSpray(spray);
}

void* CFx::Attach(const Attacher& attacher, const char* filename, bool bMark,
	defines_t* defines)
{
	int length = strlen(filename);
	if (length < 5)
	{
		return NULL;
	}
	else
	{
		if (!strcmpi(filename + length - 3, "spr"))
		{
			CFxSpray* spray = m_pvsFxBox.LoadSpray(filename, defines);
			if (spray)
			{
				spray->m_bMark = bMark;
				spray->m_attacher = (Attacher*)&attacher;
				spray->m_centerX = attacher.x;
				spray->m_centerY = attacher.y;
				m_pvsFxBox.AddSpray(spray);
				return spray;
			}
			return NULL;
		}

		CFxSequence* seq = m_pvsFxBox.LoadSequence(filename, true, defines);
		if (!seq)
			return NULL;
		seq->m_bMark = bMark;
		seq->m_attacher = (Attacher*)&attacher;
		seq->m_centerX = attacher.x;
		seq->m_centerY = attacher.y;
		m_pvsFxBox.AddSequence(seq);
		return seq;
	}
}

bool CFx::GetOutput(WVector& out, unsigned char& value)
{
	return m_pvsFxBox.GetOutput(out, value);
}

CFxControl* CFx::FindControl(int handle)
{
	std::map<int, CFxControl*>::iterator it = m_control.find(handle);
	if (it != m_control.end())
		return (*it).second;
	return NULL;
}

int CFx::MakeRunDust(const WVector& pos, const WVector& vel)
{
	return AddFxControl(new CFxRunDust(m_pvsFxBox, pos, vel));
}

bool CFx::RemoveRunDust(int handle)
{
	std::map<int, CFxControl*>::iterator it = m_control.find(handle);
	if (it != m_control.end())
	{
		CFxControl* control = (*it).second;
		m_control.erase(it);
		delete control;
		return true;
	}

	return false;
}

int CFx::MakeCobra(const CGolfBall& ball)
{
	return AddFxControl(new CFxCobra(m_pvsFxBox, ball));
}

int CFx::MakeTomahawk(const CGolfBall& ball, bool bTrajectory)
{
	return AddFxControl(new CFxTomahawk(m_pvsFxBox, ball, bTrajectory));
}

int CFx::MakePowerSpin(CGolfBall& ball)
{
	return AddFxControl(new CFxPowerSpin(m_pvsFxBox, ball));
}

int CFx::MakeShotImpact(CGolfBall& ball)
{
	return AddFxControl(new CFxShotImpact(m_pvsFxBox, ball));
}

int CFx::MakeClubImpact(CGolfBall& ball, unsigned long clubId)
{
	return AddFxControl(new CFxClubImpact(m_pvsFxBox, ball, clubId));
}

int CFx::MakeSpike(const CGolfBall& ball, bool bTrajectory)
{
	return AddFxControl(new CFxSpike(m_pvsFxBox, ball, bTrajectory));
}

int CFx::MakePowerShot2(CGolfBall& ball)
{
	return AddFxControl(new CFxPowerShot2(m_pvsFxBox, ball));
}

int CFx::MakeBoosterWarp(CGolfBall& ball, unsigned char type)
{
	return AddFxControl(new CFxBoosterWarp(m_pvsFxBox, ball, type));
}

int CFx::AddFxControl(CFxControl* control)
{
	m_control.insert(
		std::pair<const int, CFxControl*>(control->m_serial, control));
	return control->m_serial;
}

void CFx::ClearControl()
{
	for (std::map<int, CFxControl*>::iterator it = m_control.begin();
		it != m_control.end(); ++it)
		delete (*it).second;
	m_control.clear();
}

void CFx::SetActive(bool bActive)
{
	m_bActive = bActive;
}

void CFx::UpdateExtWind(WVector wind)
{
	std::map<CFxSpray*, CFxSpray*>& sprays = m_pvsFxBox.GetSprayList();
	for (std::map<CFxSpray*, CFxSpray*>::iterator it = sprays.begin();
		it != sprays.end(); it++)
		(*it).second->SetWind(wind);
	std::map<CFxSequence*, CFxSequence*>& seq = m_pvsFxBox.GetSequenceList();
	for (std::map<CFxSequence*, CFxSequence*>::iterator it = seq.begin();
		it != seq.end(); ++it)
		(*it).second->m_wind = wind;
}

CFxRunDust::CFxRunDust(CPvsFxBox& box, const WVector& pos, const WVector& vel)
	: m_fxBox(box), m_pos(pos), m_vel(vel)
{
	m_ground = m_fxBox.LoadSequence("GroundRun.seq", false, NULL);
	m_water = m_fxBox.LoadSequence("WaterRun.seq", false, NULL);
	if (m_ground && m_water)
	{
		m_fxBox.AddSequence(m_ground);
		m_fxBox.AddSequence(m_water);
	}

	m_serial = ms_serial++;
}

CFxRunDust::~CFxRunDust()
{
	m_fxBox.DeleteSequence(m_ground, false);
	m_fxBox.DeleteSequence(m_water, false);
	delete m_ground;
	delete m_water;
}

bool CFxRunDust::Process(float elapsed)
{
	WVector pos = m_pos;
	pos.y = GetPVS().GetGroundPoint(m_pos, true, NULL, true).y;
	if (m_vel.Magnitude() < 0.5f || pos.y + 1.2f < m_pos.y)
	{
		m_ground->SetActive(false, false);
		m_water->SetActive(false, false);
	}
	else
	{
		CFxSequence* seq;
		if (GetPVS().IsOverWater(pos))
		{
			m_ground->SetActive(false, false);
			m_water->SetActive(true, false);
			seq = m_water;
		}
		else
		{
			m_ground->SetActive(true, false);
			m_water->SetActive(false, false);
			seq = m_ground;
		}

		seq->Pos() = pos;
	}

	return true;
}

CFxCobra::CFxCobra(CPvsFxBox& box, const CGolfBall& ball)
	: m_fxBox(box), m_ball(ball), m_bLaunched(false)
{
	m_seq[0] = m_fxBox.LoadSequence("Cobra_BG.seq", false, NULL);
	m_seq[1] = m_fxBox.LoadSequence("Cobra_BW.seq", false, NULL);
	m_seq[2] = m_fxBox.LoadSequence("Cobra_BR.seq", false, NULL);
	m_seq[3] = m_fxBox.LoadSequence("Cobra_C.seq", false, NULL);
	if (m_seq[0] && m_seq[1] && m_seq[2] && m_seq[3])
	{
		m_fxBox.AddSequence(m_seq[0]);
		m_fxBox.AddSequence(m_seq[1]);
		m_fxBox.AddSequence(m_seq[2]);
		m_fxBox.AddSequence(m_seq[3]);
	}

	m_serial = ms_serial++;
}

CFxCobra::~CFxCobra()
{
	for (int i = 0; i < 4; ++i)
	{
		m_fxBox.DeleteSequence(m_seq[i], false);
		delete m_seq[i];
		m_seq[i] = NULL;
	}
}

bool CFxCobra::Process(float elapsed)
{
	if (!(m_ball.m_special & 0x20) || !m_seq[0] || !m_seq[1] || !m_seq[2] ||
		!m_seq[3])
		return false;
	WVector pos = m_ball.m_pos;
	pos.y = GetPVS().GetGroundPoint(m_ball.m_pos, true, NULL, true).y;
	if (m_bLaunched)
	{
		if (m_ball.m_vel.y < 0.f)
			return false;
		m_seq[3]->Pos() = m_ball.m_pos;
		if (pos.y + 22.4f > m_ball.m_pos.y)
		{
			if (m_ball.m_vel.Magnitude() < 0.5f)
			{
				m_seq[0]->SetActive(false, false);
				m_seq[1]->SetActive(false, false);
				m_seq[2]->SetActive(false, false);
			}
			else
			{
				if (GetPVS().IsOverWater(pos))
				{
					m_seq[0]->SetActive(false, false);
					m_seq[1]->SetActive(true, false);
					m_seq[2]->SetActive(true, false);
					m_seq[1]->Pos() = pos;
					m_seq[2]->Pos() = pos;
				}
				else
				{
					m_seq[0]->SetActive(true, false);
					m_seq[1]->SetActive(false, false);
					m_seq[2]->SetActive(false, false);
					m_seq[0]->Pos() = pos;
				}
			}
		}
		else
		{
			m_seq[0]->SetActive(false, false);
			m_seq[1]->SetActive(false, false);
			m_seq[2]->SetActive(false, false);
		}
	}
	else
	{
		if (m_ball.m_vel.Magnitude() > 1.f)
		{
			m_bLaunched = true;
			CFxSequence* seq = m_fxBox.LoadSequence("Cobra_A.seq", true, NULL);
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
		}
	}

	return true;
}

CFxTomahawk::CFxTomahawk(CPvsFxBox& box, const CGolfBall& ball,
	bool bTrajectory)
	: m_fxBox(box), m_ball(ball)
{
	m_step = 0;
	m_seq = NULL;
	m_serial = ms_serial++;
	m_bTrajectory = bTrajectory;
}

CFxTomahawk::~CFxTomahawk()
{
	if (m_seq)
	{
		m_fxBox.DeleteSequence(m_seq, false);
		delete m_seq;
		m_seq = NULL;
	}
}

bool CFxTomahawk::Process(float elapsed)
{
	GetPVS().GetGroundPoint(m_ball.m_pos, true, NULL, true);
	if (m_ball.m_tomahawkFrame > 0 &&
		m_ball.m_playFrame >= m_ball.m_tomahawkFrame)
		m_step = 3;
	switch (m_step)
	{
	case 0:
		if (m_ball.m_vel.Magnitude() > 1.f)
		{
			m_step = 1;
			CFxSequence* seq =
				m_fxBox.LoadSequence("Tomahawk_A.seq", true, NULL);
			if (!seq)
				return false;
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
			m_seq = m_fxBox.LoadSequence("Tomahawk_B.seq", false, NULL);
			if (!m_seq)
				return false;
			m_fxBox.AddSequence(m_seq);
		}
		break;
	case 1:
		if (m_ball.m_vel.y < 0.6f)
		{
			m_step = 2;
			if (m_seq)
			{
				m_fxBox.DeleteSequence(m_seq, false);
				delete m_seq;
				m_seq = NULL;
			}

			m_seq = m_fxBox.LoadSequence("Tomahawk_C.seq", false, NULL);
			if (!m_seq)
				return false;
			m_fxBox.AddSequence(m_seq);
		}
		break;
	case 3:
		if (m_seq)
		{
			m_fxBox.DeleteSequence(m_seq, false);
			delete m_seq;
			m_seq = NULL;
		}

		CFxSequence* seq = m_fxBox.LoadSequence("Tomahawk_D.seq", true, NULL);
		if (seq)
		{
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
			g_audio->PlaySfx("\xb0\xf8_\xc5\xe4\xb8\xb6\xc8\xa3\xc5\xa9");
			if (m_bTrajectory)
				AfxGetTask()->GetActor("Trajectory")
					<< MsgObject(NULL, 351, 0, 0, 0, 0, 0);
		}
		return false;
	}

	if (m_seq)
		m_seq->Pos() = m_ball.m_pos;
	return true;
}

CFxPowerSpin::CFxPowerSpin(CPvsFxBox& box, CGolfBall& ball)
	: m_fxBox(box), m_ball(ball), m_bRotated(false)
{
	char filename[32];
	switch (GetPVS().GetGroundType(ball.m_pos, true, NULL))
	{
	case 3:
	case 6:
		sprintf(filename, "PowerSpin_%s_S.seq", GetCurMapName());
		break;
	case 5:
		sprintf(filename, "PowerSpin_%s_P.seq", GetCurMapName());
		break;
	case 9:
		sprintf(filename, "PowerSpin_%s_W.seq", GetCurMapName());
		break;
	default:
		if (!stricmp(GetCurMapName(), "pola"))
			sprintf(filename, "PowerSpin_icee_G.seq");
		else
			sprintf(filename, "PowerSpin_%s_G.seq", GetCurMapName());
		break;
	}

	m_seq = m_fxBox.LoadSequence(filename, true, NULL);
	if (!m_seq)
		m_seq = m_fxBox.LoadSequence("PowerSpin_Blue_G.seq", true, NULL);
	if (m_seq)
		m_fxBox.AddSequence(m_seq);
	m_serial = ms_serial++;
}

CFxPowerSpin::~CFxPowerSpin()
{
}

bool CFxPowerSpin::Process(float elapsed)
{
	if (!m_fxBox.FindSequence(m_seq))
		return false;
	std::map<CFxSpray*, CFxSpray*>& sprays = m_seq->GetSprayList();
	std::map<CFxSpray*, CFxSpray*>::iterator it;
	if (!m_bRotated)
	{
		if (sprays.size() == 0)
			return true;
		WVector dir =
			m_ball.PreData(m_ball.m_playFrame)->pos - m_ball.PreData(0)->pos;
		dir.y = 0;
		dir = (m_ball.m_special & 1) ? dir.Normalize() * -1.f : dir.Normalize();
		float rad = acos(dir * WVector(0, 0, -1));
		float angle;
		if (dir.x < 0.f)
			angle = 2.f * g_PI - rad;
		else
			angle = rad;
		WMatrix rot = RotMat(WVector(0, 1, 0), angle);
		for (it = sprays.begin(); it != sprays.end(); it++)
		{
			CFxSpray* spray = (*it).second;
			spray->InitialMaxVel() = spray->InitialMaxVel() * rot;
			spray->InitialMinVel() = spray->InitialMinVel() * rot;
		}

		m_bRotated = true;
	}
	else
	{
		for (it = sprays.begin(); it != sprays.end(); it++)
			(*it).second->Pos() = m_ball.m_pos;
	}

	return true;
}

CFxShotImpact::CFxShotImpact(CPvsFxBox& box, CGolfBall& ball)
	: m_fxBox(box), m_ball(ball), m_bRotated(false)
{
	char filename[32];
	switch (GetPVS().GetGroundType(ball.m_pos, false, NULL))
	{
	case 3:
		sprintf(filename, "ShotImpact_%s_S.seq", GetCurMapName());
		m_seq = m_fxBox.LoadSequence(filename, true, NULL);
		break;
	case 5:
	case 7:
	case 8:
		m_seq = m_fxBox.LoadSequence("ShotImpact_P.seq", true, NULL);
		break;
	case 4:
		sprintf(filename, "ShotImpact_%s_G.seq", GetCurMapName());
		m_seq = m_fxBox.LoadSequence(filename, true, NULL);
		break;
	case 0:
		m_seq = m_fxBox.LoadSequence("ShotImpact_T.seq", true, NULL);
		break;
	case 9:
		m_seq = m_fxBox.LoadSequence("ShotImpact_W.seq", true, NULL);
		break;
	default:
		m_seq = NULL;
		break;
	}

	if (m_seq)
	{
		m_fxBox.AddSequence(m_seq);
		m_seq->Pos() = m_ball.PreData(0)->pos;
	}

	m_serial = ms_serial++;
}

CFxShotImpact::~CFxShotImpact()
{
}

bool CFxShotImpact::Process(float elapsed)
{
	if (!m_fxBox.FindSequence(m_seq))
		return false;
	std::map<CFxSpray*, CFxSpray*>& sprays = m_seq->GetSprayList();
	if (!m_bRotated && sprays.size() != 0)
	{
		WVector dir = m_ball.PreData(0)->vel;
		dir.y = 0;
		dir.Normalize();
		float rad = acos(dir * WVector(0, 0, -1));
		float angle;
		if (dir.x < 0.f)
			angle = 2.f * g_PI - rad;
		else
			angle = rad;
		WMatrix rot = RotMat(WVector(0, 1, 0), angle);
		for (std::map<CFxSpray*, CFxSpray*>::iterator it = sprays.begin();
			it != sprays.end(); it++)
		{
			CFxSpray* spray = (*it).second;
			spray->InitialMaxVel() = spray->InitialMaxVel() * rot;
			spray->InitialMinVel() = spray->InitialMinVel() * rot;
		}

		m_bRotated = true;
	}

	return true;
}

CFxClubImpact::CFxClubImpact(CPvsFxBox& box, CGolfBall& ball,
	unsigned long clubId)
	: m_fxBox(box), m_ball(ball)
{
	const char* types[] = { "w", "i", "s", "p" };
	char filename[256];
	IFF_STRUCT::sClubSet* club = ItemManager()->FindClubSet(clubId);
	sprintf(filename, "%s_%s_impact.seq", club->c.Icon,
		types[GolfClub().GetType()]);
	CFxSequence* seq = m_fxBox.LoadSequence(filename, true, NULL);
	if (seq)
	{
		m_fxBox.AddSequence(seq);
		seq->Pos() = m_ball.PreData(0)->pos;
	}
	else
	{
		sprintf(filename, "%s_%s_impact.spr", club->c.Icon,
			types[GolfClub().GetType()]);
		CFxSpray* spray = m_fxBox.LoadSpray(filename, NULL);
		if (spray)
		{
			m_fxBox.AddSpray(spray);
			spray->Pos() = m_ball.PreData(0)->pos;
		}
	}
}

CFxClubImpact::~CFxClubImpact()
{
}

bool CFxClubImpact::Process(float elapsed)
{
	return false;
}

CFxSpike::CFxSpike(CPvsFxBox& box, const CGolfBall& ball, bool bTrajectory)
	: m_fxBox(box), m_ball(ball)
{
	m_seq[0] = m_fxBox.LoadSequence("Spike_C.seq", false, NULL);
	m_seq[1] = m_fxBox.LoadSequence("Spike_ball.seq", false, NULL);
	m_step = 0;
	m_serial = ms_serial++;
	m_bTrajectory = bTrajectory;
}

CFxSpike::~CFxSpike()
{
	for (int i = 0; i < 2; ++i)
		if (m_seq[i])
		{
			m_fxBox.DeleteSequence(m_seq[i], false);
			delete m_seq[i];
		}
}

bool CFxSpike::Process(float elapsed)
{
	GetPVS().GetGroundPoint(m_ball.m_pos, true, NULL, true);
	if (m_ball.m_spikeEndFrame > 0 &&
		m_ball.m_playFrame >= m_ball.m_spikeEndFrame)
		m_step = 4;
	switch (m_step)
	{
	case 0:
	{
		m_fxBox.AddSequence(m_seq[0]);
		m_seq[0]->Pos() = m_ball.m_pos;
		CFxSequence* seq = m_fxBox.LoadSequence("Spike_A.seq", true, NULL);
		if (!seq)
			return false;
		m_fxBox.AddSequence(seq);
		seq->Pos() = m_ball.m_pos;
		m_step = 1;
		break;
	}

	case 1:
		if (m_ball.m_topFrame < m_ball.m_playFrame)
		{
			CFxSequence* seq =
				m_fxBox.LoadSequence("spike_shot-01.seq", true, NULL);
			if (!seq)
				return false;
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
			g_audio->PlaySfx("spike_ball_duration");
			m_step = 2;
		}
		else
			m_seq[0]->Pos() = m_ball.m_pos;
		if (!(m_ball.m_special & 0x40))
			return false;
		break;
	case 2:
		if (m_ball.m_topFrame + 60 < m_ball.m_playFrame)
		{
			CFxSequence* seq =
				m_fxBox.LoadSequence("Spike_shot.seq", true, NULL);
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
			m_fxBox.AddSequence(m_seq[1]);
			m_seq[1]->Pos() = m_ball.m_pos;
			m_seq[0]->SetActive(false, false);
			g_audio->PlaySfx("spike_beam");
			m_step = 3;
		}
		break;
	case 3:
		m_seq[1]->Pos() = m_ball.m_pos;
		break;
	case 4:
	{
		CFxSequence* seq = m_fxBox.LoadSequence("Tomahawk_D.seq", true, NULL);
		if (seq)
		{
			m_fxBox.AddSequence(seq);
			seq->Pos() = m_ball.m_pos;
			m_seq[1]->SetActive(false, false);
			g_audio->PlaySfx("\xb0\xf8_\xc5\xe4\xb8\xb6\xc8\xa3\xc5\xa9");
			if (m_bTrajectory)
				AfxGetTask()->GetActor("Trajectory")
					<< MsgObject(NULL, 351, 0, 0, 0, 0, 0);
		}
		return false;
	}
	}

	return true;
}

CFxPowerShot2::CFxPowerShot2(CPvsFxBox& box, CGolfBall& ball)
	: m_fxBox(box), m_ball(ball)
{
	m_serial = ms_serial++;
	m_bDone = false;
}

CFxPowerShot2::~CFxPowerShot2()
{
}

bool CFxPowerShot2::Process(float elapsed)
{
	if (!m_bDone)
	{
		CFxSequence* seq = m_fxBox.LoadSequence("woodwave2.seq", true, NULL);
		if (seq)
		{
			m_fxBox.AddSequence(seq);
			WVector pos = m_ball.PreData(0)->pos;
			pos.y += 1.6f;
			seq->Pos() = pos;
		}
		else
			MessageBox(g_hwnd, "Couldn't load 'woodwave2.seq'.", "Error", 0);
		m_bDone = true;
	}

	return true;
}

CFxBoosterWarp::CFxBoosterWarp(CPvsFxBox& box, CGolfBall& ball,
	unsigned char type)
	: m_fxBox(box), m_ball(ball)
{
	m_time = 0;
	m_bSlide = false;
	m_bReady = false;
	m_serial = ms_serial++;
	std::string twist = "Twist.seq", wave = "Wave.seq";
	if (type == 6)
	{
		CGimmickContainer* gimmick = NULL;
		CContentsDoc::Instance()->GetContainer((localContentType_t)163,
			gimmick);
		wave = gimmick->m_carpetSeqName;
		m_bSlide = true;
		g_audio->SetBGMVolume(0.f);
		int a = rand() % 5 + 1;
		g_audio->PlaySfx(MakeStr("magic_melody%d", a));
		int b = rand() % 5 + 1;
		if (b != a)
		{
			g_audio->PlaySfx(MakeStr("magic_melody%d", b));
			int c = rand() % 5 + 1;
			if (c != a && c != b)
				g_audio->PlaySfx(MakeStr("magic_melody%d", c));
		}
		else
			g_audio->PlaySfx("magic_bounce");
		bool long1 = g_audio->IsPlaying("magicharp_goal_long1");
		bool short1 = g_audio->IsPlaying("magicharp_goal_short1");
		bool short2 = g_audio->IsPlaying("magicharp_goal_short2");
		if (!long1 && !short1 && !short2)
		{
			int sound = rand() % 50;
			if (sound == 1)
				g_audio->PlaySfx("magicharp_goal_long1");
			else if (sound == 2)
				g_audio->PlaySfx("magicharp_goal_short1");
			else if (sound == 3)
				g_audio->PlaySfx("magicharp_goal_short2");
		}
	}

	m_seq[0] = m_fxBox.LoadSequence(twist.c_str(), false, NULL);
	m_seq[1] = m_fxBox.LoadSequence(wave.c_str(), false, NULL);
	if (m_seq[0] && m_seq[1])
	{
		m_fxBox.AddSequence(m_seq[0]);
		m_fxBox.AddSequence(m_seq[1]);
		if (type == 6)
			m_seq[0]->SetActive(false, false);
		else
		{
			m_seq[0]->Pos() = m_ball.m_pos;
			m_seq[0]->SetActive(true, false);
		}

		m_seq[1]->Pos() = m_ball.m_pos;
		m_seq[1]->SetActive(true, false);
		m_bReady = true;
	}
}

CFxBoosterWarp::~CFxBoosterWarp()
{
	for (int i = 0; i < 2; ++i)
		if (m_seq[i])
		{
			m_fxBox.DeleteSequence(m_seq[i], false);
			delete m_seq[i];
			m_seq[i] = NULL;
		}
}

bool CFxBoosterWarp::Process(float elapsed)
{
	if (m_bSlide == true)
		m_time += elapsed;
	if (2.f < m_time)
	{
		m_seq[0]->SetActive(false, false);
		m_seq[1]->SetActive(false, false);
		return false;
	}

	if (m_bReady)
	{
		if (m_ball.m_vel.Magnitude() < 0.5f)
		{
			m_seq[0]->SetActive(false, false);
			m_seq[1]->SetActive(false, false);
		}
		else
		{
			m_seq[0]->Pos() = m_ball.m_pos;
		}
	}

	return true;
}
