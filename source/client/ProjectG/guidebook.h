#pragma once

#include "frform.h"
#include "frtextbutton.h"
#include "actor.h"

class FrGuideBookDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrGuideBookDlg)

	FrGuideBookDlg();
	virtual ~FrGuideBookDlg();

protected:
	void OpenChapter(int chapter);

	void OnContentInit(int param);
	void OnContentOwnerDraw(int param);
	void OnPrevInit(int param);
	void OnNextInit(int param);
	void OnTip1Init(int param);
	void OnTip2Init(int param);
	void OnTip3Init(int param);
	void OnTip4Init(int param);
	void OnTip5Init(int param);
	void OnTip6Init(int param);
	void OnTip7Init(int param);
	void OnTip8Init(int param);
	void OnTip9Init(int param);

	void OnPrevBtnUp();
	void OnNextBtnUp();
	void OnTip1BtnUp();
	void OnTip2BtnUp();
	void OnTip3BtnUp();
	void OnTip4BtnUp();
	void OnTip5BtnUp();
	void OnTip6BtnUp();
	void OnTip7BtnUp();
	void OnTip8BtnUp();
	void OnTip9BtnUp();

	int m_chapter;
	int m_page;
	FrArea* m_pContent;
	FrButton* m_pPrev;
	FrButton* m_pNext;
	FrTextButton* m_pTip[9];
	WOverlay* m_pPage;

private:
	DECLARE_FRESH_MSGMAP()
};

class CGuideBook : public IActor, public FrCmdTarget
{
public:
	DECLARE_OBJECT(CGuideBook)
protected:
	CGuideBook();

public:
	virtual ~CGuideBook() { }

	virtual void HandleMsg(const MsgObject& msg);

protected:
	bool OnDlgResult(int result, FrForm* form);

	FrGuideBookDlg* m_pDlg;
};
