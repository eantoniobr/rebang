#pragma once

#include <map>
#include "frform.h"

class CWindFont;
class CExhibition;
class CParticle2D;
class WReceivedPacket;

class FrCardBoxDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrCardBoxDlg)

	FrCardBoxDlg();
	virtual ~FrCardBoxDlg();

	virtual void Init(unsigned long cardTypeId, unsigned long cardId,
		int count);
	void RecievedPacket(WReceivedPacket* packet);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);
	virtual void OnOK();
	virtual void OnCancel();

	void OnResultBtnInit(int param);
	void OnResultBtnUp();
	void OnCloseBtnInit(int param);
	void OnCloseBtnUp();
	void OnAreaBgInit(int param);
	void OnAreaBgOwnerDraw();
	void OnPackOpenBtnInit(int param);
	void OnPackOpenBtnUp();
	void OnOpenNextBtnInit(int param);
	void OnOpenNextBtnUp();

private:
	void SetAnimation(unsigned long cardTypeId);
	void LoadCardBoxPet(unsigned long cardTypeId, int count);
	void LoadCardPackPet(unsigned long cardTypeId);
	void SetPackVisibleInBox();
	void Display2DBg();

	CWindFont* m_pFont;
	CExhibition* m_pExhibition;
	WRect m_bgRect;
	int m_state;
	FrButton* m_pPackOpenBtn;
	FrButton* m_pOpenNextBtn;
	FrButton* m_pCloseBtn;
	FrButton* m_pResultBtn;
	unsigned long m_cardTypeId;
	unsigned long m_cardId;
	WRect m_packOpenRect;
	float m_packShake;
	std::map<unsigned long, unsigned int> m_resultCards;
	CParticle2D* m_pParticle;

	DECLARE_FRESH_MSGMAP()
};
