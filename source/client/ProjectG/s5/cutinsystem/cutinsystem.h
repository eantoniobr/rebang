#pragma once

#include <string>
#include "actor.h"
#include "../../../../shared/globalgamedefine.h"

#include "tweaker.h"

class tweaker_param;
class WOverlay;

namespace S5
{
	class CCutin : public IActor, public tweaker_cmd_target
	{
		DECLARE_OBJECT(CCutin)
	public:
		virtual ~CCutin() { }

		virtual void OnInit();
		virtual void OnProcess(float dt);
		virtual void OnDisplay();
		virtual void OnDestroy();
		virtual void HandleMsg(const MsgObject& msg);

	protected:
		CCutin();

		bool CheckGameState();
		bool PrepareCutIn();
		bool ProcessWorkIn(float dt);
		bool ProcessWorkInFinish(float dt);
		bool ProcessWorkOut(float dt);
		void OutDraw_Setting();
		void ClearAllData(bool bKeep);
		void SetOverlayInfo(WOverlay* pOverlay, eCUTINANISTLYE style,
			WRect& rect);
		bool ProcessOverlay(float dt, WOverlay* pOverlay, eCUTINANISTLYE style,
			WRect& rect);
		bool ProcessOverlay_Out(float dt, WOverlay* pOverlay,
			eCUTINANISTLYE style, WRect& rect);
		void DisplayOverlay(WOverlay* pOverlay, eCUTINANISTLYE style,
			WRect& rect);
		void RectScaling(WRect& rect, float scale);
		void ScreenRate(WRect& rect, WOverlay* pOverlay);

		void SetGameState(unsigned long state) { m_gameState |= state; }
		bool IsGameState(unsigned long state);

		void SetCondition(unsigned long condition) { m_condition |= condition; }
		int GetCondition() { return m_condition; }
		bool ISCondition(unsigned long condition);

		std::string TwAnimateTest(const tweaker_param& param);

		int m_step;
		CUTIN_ANI_STYPEINFO m_aniInfo;
		WOverlay* m_pCharacter;
		WOverlay* m_pBackground;
		WOverlay* m_pPattern;
		WOverlay* m_pText;
		float m_alpha;
		float m_rotate;
		float m_scale;
		WRect m_rect[4];
		float m_waitTime;
		unsigned long m_gameState;
		unsigned char m_unknown13c[4];
		unsigned long m_condition;
		CUTIN_ANI_STYPEINFO m_reservedAniInfo;
		std::string m_reservedImage;
		unsigned long m_reservedItemId;
		bool m_bReserved;
	};
}
