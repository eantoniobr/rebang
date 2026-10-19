#pragma once
#include "baseobject.h"
#include "singleton.h"
#include "commonutil.h"

class CCapturedBg : public CStackableSingleton<CCapturedBg>
{
public:
	CCapturedBg();

	void Render();
	void Capture();
	void Reset();
	bool IsCaptured() { return m_CaptureMode; }

	virtual ~CCapturedBg() { }

protected:
	void SetCapturedBgMode(bool mode);

	bool m_CaptureMode;
};
// HACK: CStackableSingleton<CCapturedBg>::m_InstanceStack instantiates a stack or list here
namespace ILNUM_CAPBG
{
	typedef int t0;
}
