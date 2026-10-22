#pragma once

#include "actor.h"
#include "fxbox.h"
#include "scenemanager.h"

class CBall : public IActor, public CRenderFuncPtr, public CFxKeeper
{
public:
	virtual ~CBall() { }

	DECLARE_OBJECT(CBall)

	virtual void OnPreLoadInit();
	virtual void OnLoad();
	virtual void OnInit();
	virtual void OnReload();
	virtual void OnProcess(float delta);
	virtual void OnDisplay();
	virtual void OnDestroy();
	virtual void Display();
	virtual void EmptyFx(void* fx);

protected:
	CBall();

	virtual void HandleMsg(const MsgObject& msg);

	struct sBall
	{
		IFF_STRUCT::sBall* info;
		WPuppet* puppet;
		CFxSpray* spray[4];
		CFxSequence* sequence[4];

		sBall()
			: info(NULL), puppet(NULL)
		{
			memset(spray, 0, sizeof(spray));
			memset(sequence, 0, sizeof(sequence));
		}
	};

	struct sFindBall
	{
		unsigned long typeId;

		sFindBall(unsigned long id)
			: typeId(id)
		{
		}

		bool operator()(sBall* ball) { return ball->info->c.TypeId == typeId; }
	};

	sBall* FindBall(unsigned long typeId);
	sBall* AddBall(unsigned long typeId);
	void AttachFx(int type);
	void DetachFx(int type);
	float GetDownDelta();
	void TransformBall();
	std::list<sBall*> m_balls;
	WPuppet* m_pPuppet;
	int m_shadow;
	WMatrix m_matrix;
	WVector m_axis;
	bool m_bLightChanged;
	float m_down;
	int m_downStart;
	LightSet m_light;
	bool m_bVisible;
	int m_lastFrame;
	WTVertex* m_vtx[5];
	WTVertex m_vertices[4];
};
