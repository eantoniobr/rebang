#pragma once

#include <vector>
#include <map>
#include "frform.h"

class FrEdit;
class FrArea;
class FrButton;
class FrListBox;

namespace _guild
{

	enum eFormStyle
	{
		FORM_NONE = 0,
		FORM_INFO = 1,
		FORM_MEMBER = 2,
		FORM_SEARCH = 4
	};
	enum eAuthority
	{
		AUTH_NONE = 1,
		AUTH_MASTER = 2,
		AUTH_SUBMASTER = 4,
		AUTH_MEMBER = 8,
		AUTH_WAIT = 16,
		AUTH_ALL = 0xffff
	};

	template <class T>
	enumGuiType GUIConverter(T* pWnd);

	template <>
	inline enumGuiType GUIConverter<FrEdit>(FrEdit* pWnd)
	{
		return GI_EDIT;
	}
	template <>
	inline enumGuiType GUIConverter<FrArea>(FrArea* pWnd)
	{
		return GI_AREA;
	}
	template <>
	inline enumGuiType GUIConverter<FrButton>(FrButton* pWnd)
	{
		return GI_BUTTON;
	}
	template <>
	inline enumGuiType GUIConverter<FrListBox>(FrListBox* pWnd)
	{
		return GI_LISTBOX;
	}

	class CGuildFormController
	{
	public:
		CGuildFormController();
		~CGuildFormController();

		struct sPostAction
		{
			enumGuiType type;
			int formStyle;
			int authority;
			FrWnd* pWnd;
			void (CGuildFormController::*pFn)(sPostAction*);

			void operator()(CGuildFormController* pController)
			{
				(pController->*pFn)(this);
			}
		};

		void ControllForm(eFormStyle style, eAuthority authority);
		void InsertControl(FrWnd* pWnd);

		void ReadOnlywindow(sPostAction* pAction);
		void WritableWindow(sPostAction* pAction);
		void EnableWindow(sPostAction* pAction);
		void DisableWindow(sPostAction* pAction);
		void MoveLeftSide(sPostAction* pAction);
		void MoveRightSide(sPostAction* pAction);
		void ClearEdit(sPostAction* pAction);
		void VisibleWindow(sPostAction* pAction);
		void InVisibleWindow(sPostAction* pAction);

		template <class T>
		void InsertPostAction(T* pWnd, int formStyle, int authority,
			void (CGuildFormController::*pFn)(sPostAction*))
		{
			sPostAction* pAction = new sPostAction;
			pAction->type = GUIConverter(pWnd);
			pAction->formStyle = formStyle;
			pAction->authority = authority;
			pAction->pWnd = pWnd;
			pAction->pFn = pFn;

			m_postActions.insert(std::make_pair(pAction, pAction));
		}

	private:
		std::vector<FrWnd*> m_controls;
		std::map<sPostAction*, sPostAction*> m_postActions;
		eFormStyle m_formStyle;
	};

	class CPageArrow
	{
	public:
		CPageArrow() { }
		~CPageArrow() { }

		void InitControl();
		void RefreshArrowButton(int page, int total);

		void SetLeftArrow(FrButton* pButton) { m_pLeftArrow = pButton; }
		void SetRightArrow(FrButton* pButton) { m_pRightArrow = pButton; }

	private:
		FrButton* m_pLeftArrow;
		FrButton* m_pRightArrow;
		WFlags m_state;
	};

}
