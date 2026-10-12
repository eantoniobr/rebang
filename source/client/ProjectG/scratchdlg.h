#pragma once

#include "frform.h"
#include "bongdarishopdlg.h"

class FrTextButton;

class FrScratchDlg : public FrForm
{
	DECLARE_OBJECT(FrScratchDlg)

	FrScratchDlg();
	virtual ~FrScratchDlg();

	void InitScratchCard();
	void SetScratchItem(int count, sBonusBall* pBalls);
	void ClearScratchItem();
	void UpdateListMyItem(sBonusBall* pBall);
	void RequestScratchItem();
	void SendScratchSerialNumber();
	void ResponseScratchSerialNumber(int result, unsigned long itemTypeId);
	void EnableScratchSerialNumber(bool bEnable);
	void EnableNextPageButton(bool bEnable);

	void SetBmpColsedScratchCover();
	void ResetBmpScratchCover(int index);
	void OpenScratchCover(const WPoint& pt);
	void SetBmpScratchItem();
	void SetRectScratchItem();
	void DrawScratchItem();

	void SetRectCheckScratchItemRect();
	void SetRectCheckScratchItemRectByIndex(int index, WPoint margin);
	void ClearDataCheckScratchItem();
	void CheckScratchItemRect(const WPoint& pt);
	void ProcessCheckScratchItemRect(float delta);

	void InitChangeScratchCardNumber(int type);
	void ProcessChangeScratchCardNumber(float delta);
	void DrawChangeScratchCardNumber();

	void SetBmpResultText(int result);
	void ProcessResultText(float delta);
	void OpenScratchResultDlg();
	bool OnConfirmResult(int result, FrForm* pForm);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);
	virtual void OnCancel();
	virtual void OnMouseMove(const WPoint& pt);
	virtual bool OnLButtonDown(const WPoint& pt);
	virtual bool OnLButtonUp(const WPoint& pt);

	void OnScratchDlgInit(int param);
	void OnScratchCardInit(int param);
	bool OnScratchCardEnterKey(int param);
	void OnSerialNumberInit(int param);
	bool OnSerialNumberEnterKey(int param);
	void OnSerialNumberBnInit(int param);
	void OnSerialNumberBnUp();
	void OnScratchCover01Init(int param);
	void OnScratchCover01OwnerDraw();
	void OnScratchCover02Init(int param);
	void OnScratchCover02OwnerDraw();
	void OnScratchBottomInit(int param);
	void OnScratchBottomOwnerDraw();
	void OnScratchNextPageBnInit(int param);
	void OnScratchNextPageBnUp();
	void OnAboutBnInit(int param);
	void OnAboutBnUp();
	void OnCloseBnInit(int param);
	void OnCloseBnUp();

protected:
	FrArea* m_pScratchCover[2];
	FrEdit* m_pScratchCard;
	FrButton* m_pNextPageBn;
	FrEdit* m_pSerialNumber;
	FrButton* m_pSerialNumberBn;
	WTitleFont* m_pFont;
	const Bitmap* m_pImgCover[2];
	const Bitmap* m_pImgClosedCover;
	Bitmap m_bmpCover[2];
	const Bitmap* m_pImgEraser;
	const Bitmap* m_pImgChangeNumber[2];
	const Bitmap* m_pImgItem[2];

public:
	void SetEnableRequestScratchItem(bool bEnable)
	{
		m_bEnableRequestScratchItem = bEnable;
	}

protected:
	WRect m_rtItem[3];
	WRect m_rtScratchArea;
	WPoint m_ptEraserOffset;
	bool m_bScratching;
	int m_scratchCardCount;
	sBonusBall m_scratchItem[11];
	int m_scratchItemCount;
	int m_result;
	bool m_bEnableRequestScratchItem;
	bool m_bScratchable;
	bool m_bEnableSerialNumber;
	bool m_bShowResult;
	int m_changeNumberType[2];
	float m_changeNumberPos[2];
	int m_changeNumberAlpha[2];
	float m_resultTime;
	bool m_bCheckedRect[2][4];
	WRect m_rtCheck[3][4];

	DECLARE_FRESH_MSGMAP()
};

class FrScratchResultDlg : public FrForm
{
	DECLARE_OBJECT(FrScratchResultDlg)

	FrScratchResultDlg();
	virtual ~FrScratchResultDlg();

	void SetResultItem(sBonusBall* pBalls, int count);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float delta);

	void OnScratchResultDlgInit(int param);
	void OnResultItemIconInit(int param);
	void OnResultItemIconOwnerDraw();
	void OnResultItemNameInit(int param);
	void OnResultItemAbilityInit(int param);

	FrArea* m_pResultItemIcon;
	FrEdit* m_pResultItemName;
	FrEdit* m_pResultItemAbility;
	WTitleFont* m_pFont;
	sBonusBall m_resultItem[2];
	int m_resultItemCount;
	bool m_bShowAbility;
	const Bitmap* m_pImgItem[2];

	DECLARE_FRESH_MSGMAP()
};

class FrScratchAboutDlg : public FrForm
{
	DECLARE_OBJECT(FrScratchAboutDlg)

	FrScratchAboutDlg();
	virtual ~FrScratchAboutDlg();

	void SetImgAboutIndex(int index);

protected:
	virtual bool OnInit();

	void OnAboutViewerInit(int param);
	void OnIndex01Init(int param);
	void OnIndex02Init(int param);
	void OnIndex03Init(int param);
	void OnIndex04Init(int param);
	void OnIndex05Init(int param);
	void OnIndex01BnUp();
	void OnIndex02BnUp();
	void OnIndex03BnUp();
	void OnIndex04BnUp();
	void OnIndex05BnUp();
	void OnBackwardBnInit(int param);
	void OnBackwardBnUp();
	void OnForwardBnInit(int param);
	void OnForwardBnUp();
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrTextButton* m_pIndexBn[5];
	int m_aboutIndex;
	FrButton* m_pBackwardBn;
	FrButton* m_pForwardBn;
	FrViewer* m_pAboutViewer;

	DECLARE_FRESH_MSGMAP()
};
