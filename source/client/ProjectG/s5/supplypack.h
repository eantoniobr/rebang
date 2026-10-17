#pragma once

#include <string>
#include <list>

#include "../../shared/globalgamedefine.h"

class CExhibition;
class WTitleFontEx;
class CWindFont;
class CBlueWindFontBig;
class CFontAnimation;

namespace S5
{
	class FrSupplyPackDlg : public FrForm
	{
		DECLARE_OBJECT(FrSupplyPackDlg)

		FrSupplyPackDlg();
		virtual ~FrSupplyPackDlg();

		void Initialize(unsigned long typeId);
		void UpdateData(unsigned int count);

	protected:
		virtual void OnProc(const float dt);
		virtual bool OnResultConfirm(int ret, FrForm* pForm);

		virtual void OnCancel() { }

		void OnItemListInit(int param);
		void OnItemListDraw(int param);
		void OnItemListUp();
		void OnOkayBtnInit(int param);
		void OnOkayBtnUp();
		void OnCancelBtnInit(int param);
		void OnCancelBtnUp();
		void OnBgAreaDraw();

		unsigned long m_typeId;
		FrListBox* m_pItemList;
		FrButton* m_pCancelBtn;
		FrButton* m_pOkayBtn;
		CExhibition* m_pExhibition;
		float m_alpha;
		FrListItem* m_pSelectedItem;
		CWindFont* m_pWindFont;
		CBlueWindFontBig* m_pBlueWindFont;
		float m_waitTime;
		int m_bStarted;
		unsigned int m_supplyCount;
		CFontAnimation* m_pFontAnimation;
		float m_elapsed;
		float m_arrowOffset;
		int m_bonus[10];
		std::list<sItemInfo> m_itemList;
		int m_baseQuantity;
		int m_quantity;
		int m_step;

		DECLARE_FRESH_MSGMAP()
	};
}
