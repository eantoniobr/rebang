#pragma once

#include "frform.h"
#include <list>
#include <vector>
#include "noticeimage.h"
#include "../../shared/globalnetworkdefine.h"

class CExhibition;
class CSimpleUI;
class FrTextButton;

class FrBongdariShopDlg : public FrForm
{
	DECLARE_OBJECT(FrBongdariShopDlg)

	FrBongdariShopDlg();
	virtual ~FrBongdariShopDlg();

	struct sItemSilhouette
	{
		int ballIndex;
		const Bitmap* pBitmap;
		unsigned long typeId;
		unsigned char category;
		unsigned char state;
		float time;
	};

	struct sMovingData
	{
		WVector velocity;
		WVector bottom;
		WVector pos;
		float scale;
		int bounceCount;
		unsigned char state;
		float rotSpeed;
	};

	void InitBongdariShop();
	void InitCouponBongdariShop();
	void SetBongdariShop();
	void Clear();
	void SetBonusBall(int num, sBonusBall* balls);
	void SetDataFee(int fee);
	void OpenBonusBall(int index);
	void CreateBonusBall(WVector pos);
	void EnableExitButton(bool bEnable);
	void UpdateUsableTimes();
	void ShowDiscountUsableTimes();

protected:
	virtual bool OnInit();
	virtual void OnProc(const float dt);
	virtual void OnCancel();
	virtual bool OnLButtonDown(const WPoint& pt);
	virtual bool OnLButtonUp(const WPoint& pt);

	void OnBongdariShopInit(int param);
	void OnAboutShopBnInit(int param);
	void OnAboutShopBnUp();
	void OnTotalItemBnInit(int param);
	void OnTotalItemBnUp();
	void OnBongdarishopNoticeBnInit(int param);
	void OnBongdarishopNoticeBnUp();
	void OnCloseBnInit(int param);
	void OnCloseBnUp();
	void OnBongdariInit(int param);
	void OnBongdariOwnerDraw();
	void OnBonusBall01BnInit(int param);
	void OnBonusBall02BnInit(int param);
	void OnBonusBall03BnInit(int param);
	void OnBonusBall04BnInit(int param);
	void OnBonusBall05BnInit(int param);
	void OnBonusBall01OwnerDraw();
	void OnBonusBall02OwnerDraw();
	void OnBonusBall03OwnerDraw();
	void OnBonusBall04OwnerDraw();
	void OnBonusBall05OwnerDraw();

	void OpenAboutShopDlg();
	void OpenTotalItemDlg();
	void OpenBongdarishopNoticeDlg(bool bIn);
	void OpenBongdarishopRareItemDlg(int index);
	void OpenBongdarishopWarningDlg(int type, int price);
	void OpenClosedBonusBallResultDlg();
	bool OnAboutShopDlgResult(int ret, FrForm* pForm);
	bool OnTotalItemDlgResult(int ret, FrForm* pForm);
	bool OnBongdarishopNoticeDlgResult(int ret, FrForm* pForm);
	bool OnBongdarishopRareItemDlgResult(int ret, FrForm* pForm);
	bool OnBongdarishopWarningDlgResult(int ret, FrForm* pForm);
	void ControlNoticeDlg();

	void Processing(float dt);
	void SetPosMovingClickText(float dt);
	void SetStartAnimationBongdari();
	void DeletePetBonusBall();
	void ShowBongdari();
	void ShowBonusBall(int index);
	void DrawBonusBall(unsigned int index);
	void DrawShadow();
	void DrawTextBongdariClick();
	void DrawTextBonusBallClick();
	void DrawUserInfo();
	void SetOpeningBonusBallInfo(sBonusBall* ball);
	void AddListTotalItem(sBonusBall* ball);
	void UpdateListMyItem(sBonusBall* ball);

	void InitRandomDataItemSilhouette();
	void ShuffleRandomDataItemSilhouette();
	void SetRandomDataItemSilhouette();
	void DisplayItemSilhouette();
	unsigned long SelectDifferentTypeId(int category);

	void SendStateBongdariShop(bool bEnter);
	void SendReBuildMyInventory();
	void SendDataClosedBonusBall();

	int m_state;
	sItemSilhouette m_silhouette[9];
	sBonusBall m_bonusBall[5];
	int m_bonusBallNum;
	CExhibition* m_pPetBonusBall[5];
	CExhibition* m_pPetBongdari;
	FrButton* m_pCloseBn;
	FrArea* m_pBongdari;
	FrArea* m_pBonusBallBn[5];
	const Bitmap* m_pImgItemBase;
	const Bitmap* m_pImgShadow;
	const Bitmap* m_pImgTextBongdariClick;
	const Bitmap* m_pImgTextBonusBallClick;
	const Bitmap* m_pImgTextFee[2];
	float m_clickTextPos;
	bool m_bClickTextUp;
	bool m_bBongdariDown;
	bool m_bUsingBonusBall;
	bool m_bAnimating;
	WRect m_rtBongdari;
	int m_overBonusBall;
	int m_cursor;
	WTitleFont* m_pFontPang;
	WTitleFont* m_pFontCount;
	WTitleFont* m_pFontCoupon;
	CSimpleUI* m_pNumberUI;
	sMovingData m_movingData[5];
	bool m_bOpenSubDlg;
	std::list<sBonusBall> m_totalItem;
	int m_couponCount;
	short m_usableTimes;
	short m_usableBonusTimes;
	short m_remainedBonusTimes;
	int m_dataFee;
	float m_feeAniPos;
	int m_feeAniAlpha;
	bool m_bShowUsableTimes;
	bool m_bShowBonusTimes;
	float m_timesAniPos;
	int m_timesAniAlpha;
	float m_processTime;
	FrButton* m_pTotalItemBn;
	float m_exitTime;

	DECLARE_FRESH_MSGMAP()

public:
	void SetUsingBonusBall(bool bUsing) { m_bUsingBonusBall = bUsing; }
};

class FrAboutShopDlg : public FrForm
{
	DECLARE_OBJECT(FrAboutShopDlg)

	FrAboutShopDlg();
	virtual ~FrAboutShopDlg();

	void SetImgAboutIndex(int index);

protected:
	virtual bool OnInit();

	void OnAboutShopInit(int param);
	void OnAboutViewerInit(int param);
	void OnIndex01Init(int param);
	void OnIndex01BnUp();
	void OnIndex02Init(int param);
	void OnIndex02BnUp();
	void OnIndex03Init(int param);
	void OnIndex03BnUp();
	void OnIndex04Init(int param);
	void OnIndex04BnUp();
	void OnIndex05Init(int param);
	void OnIndex05BnUp();
	void OnIndex06Init(int param);
	void OnIndex06BnUp();
	void OnIndex07Init(int param);
	void OnIndex07BnUp();
	void OnIndex08Init(int param);
	void OnIndex08BnUp();
	void OnIndex09Init(int param);
	void OnIndex09BnUp();
	void OnIndex10Init(int param);
	void OnIndex10BnUp();
	void OnBackwardBnInit(int param);
	void OnBackwardBnUp();
	void OnForwardBnInit(int param);
	void OnForwardBnUp();
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrTextButton* m_pIndexBn[10];
	int m_index;
	FrButton* m_pBackwardBn;
	FrButton* m_pForwardBn;
	FrViewer* m_pAboutViewer;

	DECLARE_FRESH_MSGMAP()
};

class FrTotalItemDlg : public FrForm
{
	DECLARE_OBJECT(FrTotalItemDlg)

	FrTotalItemDlg();
	virtual ~FrTotalItemDlg();

	class MiniBtn
	{
	public:
		WRect m_rect;
		const Bitmap* m_pBitmap;
		unsigned long m_reserved;
	};

	void SetListItem(std::list<sBonusBall>* pList);

protected:
	virtual bool OnInit();

	void OnTotalItemInit(int param);
	void OnTotalItemListInit(int param);
	void OnTotalItemListOwnerDraw(int param);
	void OnTotalItemListRBnDown();
	void OnOkBnInit(int param);
	void OnOkBnUp();
	void OpenInformation(unsigned long typeId);

	FrListBox* m_pTotalItemList;
	const Bitmap* m_pImgIconBase;
	WTitleFont* m_pFont;
	MiniBtn m_miniBtn[8];
	std::list<sBonusBall> m_itemList;

	DECLARE_FRESH_MSGMAP()
};

class FrBongdarishopNoticeDlg : public FrForm
{
	DECLARE_OBJECT(FrBongdarishopNoticeDlg)

	FrBongdarishopNoticeDlg();
	virtual ~FrBongdarishopNoticeDlg();

	void LoadInitFile(const char* filename);
	void SetImgNotice(int index);
	void SetButtonType(bool bIn);
	void PrevIndex();
	void NextIndex();

protected:
	virtual bool OnInit();

	void OnBongdarishopNoticeInit(int param);
	void OnNoticeViewerInit(int param);
	void OnNoticeViewerBnUp();
	void OnListIndexInit(int param);
	void OnListIndexOwnerDraw(int param);
	void OnListIndexLBnUp();
	void OnBackwardBnInit(int param);
	void OnBackwardBnUp();
	void OnForwardBnInit(int param);
	void OnForwardBnUp();
	void OnInBnInit(int param);
	void OnInBnUp();
	void OnOutBnInit(int param);
	void OnOutBnUp();
	void OnOkBnInit(int param);
	void OnOkBnUp();

	std::vector<sNoticeImage> m_notice;
	FrListBox* m_pListIndex;
	int m_index;
	unsigned long m_moveLayoutTid;
	FrButton* m_pBackwardBn;
	FrButton* m_pForwardBn;
	FrViewer* m_pNoticeViewer;
	FrButton* m_pInBn;
	FrButton* m_pOutBn;
	FrButton* m_pOkBn;

	DECLARE_FRESH_MSGMAP()

public:
	unsigned long GetMoveLayoutTid() { return m_moveLayoutTid; }
};

class FrBongdarishopRareItemDlg : public FrForm
{
	DECLARE_OBJECT(FrBongdarishopRareItemDlg)

	FrBongdarishopRareItemDlg();
	virtual ~FrBongdarishopRareItemDlg();

	void SetRareItem(sBonusBall* ball);

protected:
	virtual bool OnInit();

	void OnBongdarishopRareItemInit(int param);
	void OnRareItemIconInit(int param);
	void OnRareItemNameInit(int param);
	void OnRareItemAbilityInit(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrArea* m_pRareItemIcon;
	FrEdit* m_pRareItemName;
	FrEdit* m_pRareItemAbility;

	DECLARE_FRESH_MSGMAP()
};

class FrBongdarishopWarningDlg : public FrForm
{
	DECLARE_OBJECT(FrBongdarishopWarningDlg)

	FrBongdarishopWarningDlg();
	virtual ~FrBongdarishopWarningDlg();

	void SetImgWarningBack(int type, int price);

protected:
	virtual bool OnInit();

	void OnBongdarishopWarningInit(int param);
	void OnWarningBackInit(int param);
	void OnWarningBackOwnerDraw(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrArea* m_pWarningBack;
	WTitleFont* m_pFont;
	unsigned long m_price;
	int m_type;

	DECLARE_FRESH_MSGMAP()
};

class FrClosedBonusBallResultDlg : public FrForm
{
	DECLARE_OBJECT(FrClosedBonusBallResultDlg)

	FrClosedBonusBallResultDlg();
	virtual ~FrClosedBonusBallResultDlg();

	class MiniBtn
	{
	public:
		WRect m_rect;
		const Bitmap* m_pBitmap;
		unsigned long m_reserved;
	};

	void SetClosedBonusBall(sBonusBall* balls);
	void SetEditDataClosedBonusBall(int line, int index);

protected:
	virtual bool OnInit();
	virtual void OnProc(const float dt);

	void OnClosedBonusBallResultInit(int param);
	void OnClosedBonusBallListInit(int param);
	void OnClosedBonusBallListOwnerDraw(int param);
	void OnClosedBonusBallName01Init(int param);
	void OnClosedBonusBallAbility01Init(int param);
	void OnClosedBonusBallName02Init(int param);
	void OnClosedBonusBallAbility02Init(int param);
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrListBox* m_pClosedBonusBallList;
	FrEdit* m_pName[2];
	FrEdit* m_pAbility[2];
	int m_topRow;
	MiniBtn m_miniBtn[8];
	sBonusBall m_closedBonusBall[5];

	DECLARE_FRESH_MSGMAP()
};
