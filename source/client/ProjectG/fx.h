#pragma once

#include <map>
#include "scenemanager.h"
#include "fxbox.h"

class CGolfBall;
class CFxControl;
class CFxSequence;
class CFxSpray;
class CFxKeeper;
struct sFxKeeper;
struct defines_t;

struct Attacher
{
	float x;
	float y;
	WMatrix* mat[4];
	WVector* pos[4];

	Attacher();
	bool Get(WVector& out);
};

class CPvsFxBox : public CFxBox
{
public:
	virtual void ProcessAttacher(float elapsed);

protected:
	virtual bool CheckGroundCollision(const WVector& from, const WVector& to,
		float& height, float radius);
	virtual void OnSequenceCreated(CFxSequence* sequence);
	virtual void OnSequenceDeleted(CFxSequence* sequence);
	virtual void OnSprayCreated(CFxSpray* spray);
	virtual void OnSprayDeleted(CFxSpray* spray);
	void UpdateLightSrc(const LightSet& light);

	std::map<CFxSequence*, Attacher> m_seqAttacher;
	std::map<CFxSpray*, Attacher> m_sprayAttacher;
};

class CFx : public CRenderFuncPtr, public WSingleton<CFx>
{
public:
	CFx();
	virtual ~CFx();

	virtual void Process(float elapsed);
	virtual void Display();

	CFxSequence* OpenSequence(const char* filename, bool bDelete);
	void CloseSequence(CFxSequence* sequence, bool bDeleteChild);
	CFxSpray* OpenSpray(const char* filename);
	void CloseSpray(CFxSpray* spray);
	void ClearAll(bool bMarkedOnly);

	void AddFxKeeper(sFxKeeper& keeper);
	void EraseFxKeeper(CFxKeeper* keeper);
	void ClearFxKeeper();

	CFxSpray* GetSpray(int index);
	bool FindSequence(CFxSequence* sequence);
	bool FindSpray(CFxSpray* spray);
	void* Attach(const Attacher& attacher, const char* filename, bool bMark,
		defines_t* defines);
	bool GetOutput(WVector& out, unsigned char& value);

	CFxControl* FindControl(int handle);
	int MakeRunDust(const WVector& pos, const WVector& vel);
	bool RemoveRunDust(int handle);
	int MakeCobra(const CGolfBall& ball);
	int MakeTomahawk(const CGolfBall& ball, bool bTrajectory);
	int MakePowerSpin(CGolfBall& ball);
	int MakeShotImpact(CGolfBall& ball);
	int MakeClubImpact(CGolfBall& ball, unsigned long clubId);
	int MakeSpike(const CGolfBall& ball, bool bTrajectory);
	int MakePowerShot2(CGolfBall& ball);
	int MakeBoosterWarp(CGolfBall& ball, unsigned char type);

	void SetActive(bool bActive);
	void UpdateExtWind(WVector wind);

	void SetPvsFxBoxGroundHeight(float maxHeight, float minHeight)
	{
		m_pvsFxBox.SetGroundHeightArea(maxHeight, minHeight);
	}

protected:
	int AddFxControl(CFxControl* control);
	void ClearControl();

	CPvsFxBox m_pvsFxBox;
	std::map<int, CFxControl*> m_control;
	bool m_bActive;
};
