#pragma once

#include "frform.h"
#include "frlistbox.h"
#include "tooltipmanager.h"
#include "tabmanager.h"
#include "overlaycursor.h"
#include "fadingtext.h"
#include "uccbrush.h"

struct sItemInfo;
class CUccClothes;
class FrNotifyForm;
class FrUccSetInfoDlg;
class FrUccPickColorDlg;

enum eDrawMode
{
	DRAW_CLOTHES,
	DRAW_AZTEC
};

enum eUccTab
{
	UCC_TAB_DRAW,
	UCC_TAB_PATTERN,
	UCC_TAB_EMOTICON,
	UCC_TAB_TEXT
};

class FrUccDrawDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrUccDrawDlg)

	FrUccDrawDlg();
	virtual ~FrUccDrawDlg();

	void Init();
	void Clear();

	virtual bool Open(bool (FrCmdTarget::*pFnResult)(int, FrForm*),
		const WPoint& pos, unsigned long flag);
	virtual bool Close(eFormRet ret, bool bFadeout);

	void SetName(const char* name);
	void Upload();
	void Notify(const char* msg);
	void SetCurrentColor(unsigned char r, unsigned char g, unsigned char b);
	void MoveCanvasToCenter();

	void SetUccDrawInfo(eDrawMode mode, sItemInfo* pItemInfo, bool bReset);

	bool IsInitialized() { return m_bInitialized; }

	void AfterZoom();
	void SetSaved(bool bSaved);
	void Finish();

	void BuildBrushList();
	void BuildPenList();
	void BuildEraserList();
	void BuildPatternList(int index, bool bFolded);
	void BuildColorList();
	void BuildCurrentPattern();
	void ChangeTab(eUccTab tab);

	bool IsSaved() { return m_bSaved; }
	void CloseWaitingForm();
	void SetToolbarStatus(FrButton* pButton);

protected:
	virtual void OnCancel();
	virtual void OnProc(const float delta);

	void OnUccCanvasInit(int param);
	void OnUndoBtnInit(int param);
	void OnUndoBtnUp();
	void OnRedoBtnInit(int param);
	void OnRedoBtnUp();
	void OnFlipBtnInit(int param);
	void OnFlipBtnOwnerDraw(int param);
	void OnFlipBtnUp();
	void OnResetBtnInit(int param);
	void OnResetBtnUp();
	void OnGridBtnInit(int param);
	void OnGridBtnUp();
	void OnDragBtnInit(int param);
	void OnDragBtnUp();
	void OnZoomInBtnInit(int param);
	void OnZoomInBtnUp();
	void OnZoomOutBtnInit(int param);
	void OnZoomOutBtnUp();
	void OnSide1AreaInit(int param);
	void OnSide2AreaInit(int param);
	void OnTempSaveBtnInit(int param);
	void OnTempSaveBtnUp();
	void OnTabDrawBtnInit(int param);
	void OnTabDrawBtnUp();
	void OnTabPatternBtnInit(int param);
	void OnTabPatternBtnUp();
	void OnTabEmoticonBtnInit(int param);
	void OnTabEmoticonBtnUp();
	void OnTabTextBtnInit(int param);
	void OnTabTextBtnUp();
	void OnFinishBtnInit(int param);
	void OnFinishBtnUp();
	bool OnAskCompleteDlgResult(int result, FrForm* form);
	bool OnAskCancelDlgResult(int result, FrForm* form);
	bool OnAskResetDlgResult(int result, FrForm* form);
	bool OnUccSetInfoDlgResult(int result, FrForm* form);
	void OnCloseBtnInit(int param);
	void OnCloseBtnUp();
	void OnPaintBtnInit(int param);
	void OnPaintBtnUp();
	void OnPickColorBtnInit(int param);
	void OnPickColorBtnUp();
	void OnCurrentColorBtnInit(int param);
	void OnCurrentColorBtnUp();
	bool OnUccPickColorDlgResult(int result, FrForm* form);
	void OnCurrentColorAreaInit(int param);
	void OnColorListInit(int param);
	void OnColorListOwnerDraw(int param);
	void OnColorListBtnDown();
	void OnEraserListInit(int param);
	void OnEraserListOwnerDraw(int param);
	void OnEraserListBtnDown();
	void OnToolInfoEraserAreaInit(int param);
	void OnBaseColorListInit(int param);
	void OnExtendedBasePatternListInit(int param);
	void OnBrushListInit(int param);
	void OnBrushListOwnerDraw(int param);
	void OnBrushListBtnDown();
	void OnPenListInit(int param);
	void OnPenListOwnerDraw(int param);
	void OnPenListBtnDown();
	void OnToolInfoPenAreaInit(int param);
	void OnToolInfoBrushAreaInit(int param);
	void OnColorListsAreaInit(int param);
	void OnArrowDownBtnInit(int param);
	void OnArrowDownBtnUp();
	void OnArrowRightBtnInit(int param);
	void OnArrowRightBtnUp();
	void OnArrowLeftBtnInit(int param);
	void OnArrowLeftBtnUp();
	void OnDeleteBtnInit(int param);
	void OnDeleteBtnUp();
	void OnModifyBtnInit(int param);
	void OnModifyBtnUp();
	void OnMakeBtnInit(int param);
	void OnMakeBtnUp();
	void OnRateListInit(int param);
	void OnRateListOwnerDraw(int param);
	void OnRateListBtnDown();
	void OnPatternListInit(int param);
	void OnPatternListOwnerDraw(int param);
	void OnPatternListBtnDown();
	void OnEtcInit(int param);
	void OnEtcOwnerDraw(int param);
	void OnToolTipInit(int param);
	void OnToolTipOnwerDraw(int param);

	void Reset();
	bool IsSavingTemporarily();

public:
	sItemInfo* m_pItemInfo;
	CUccClothes* m_pClothes[2];
	bool m_bWaiting;
	FrForm* m_pWaitingForm;
	float m_waitingTime;
	Bitmap m_color[18];

protected:
	CToolTipManager m_toolTip;
	CTabManager m_tabManager;
	bool m_bSaved;
	bool m_bCloseAfterSave;
	FrArea* m_pCanvas;
	FrButton* m_pUndoBtn;
	FrButton* m_pRedoBtn;
	FrButton* m_pFlipBtn;
	FrButton* m_pResetBtn;
	FrArea* m_pSide1Area;
	FrArea* m_pSide2Area;
	FrButton* m_pTempSaveBtn;
	FrButton* m_pGridBtn;
	FrButton* m_pDragBtn;
	FrButton* m_pZoomInBtn;
	FrButton* m_pZoomOutBtn;
	FrButton* m_pTabDrawBtn;
	FrButton* m_pTabPatternBtn;
	FrButton* m_pTabEmoticonBtn;
	FrButton* m_pTabTextBtn;
	FrButton* m_pFinishBtn;
	FrButton* m_pCloseBtn;
	FrButton* m_pPickColorBtn;
	FrButton* m_pCurrentColorBtn;
	FrButton* m_pPaintBtn;
	FrArea* m_pCurrentColorArea;
	FrListBox* m_pColorList;
	FrListBox* m_pEraserList;
	FrArea* m_pToolInfoEraserArea;
	Bitmap m_currentColor;
	FrListBox* m_pBrushList;
	FrListBox* m_pPenList;
	FrArea* m_pToolInfoPenArea;
	FrArea* m_pToolInfoBrushArea;
	FrArea* m_pColorListsArea;
	FrButton* m_pArrowDownBtn;
	FrButton* m_pArrowRightBtn;
	FrButton* m_pArrowLeftBtn;
	FrButton* m_pDeleteBtn;
	FrButton* m_pModifyBtn;
	FrButton* m_pMakeBtn;
	FrListBox* m_pRateList;
	FrListBox* m_pPatternList;
	FrArea* m_pBaseColorList;
	FrArea* m_pExtendedBasePatternList;
	FrArea* m_pEtc;
	FrArea* m_pToolTip;
	int m_unknown384;
	FrUccSetInfoDlg* m_pSetInfoDlg;
	FrUccPickColorDlg* m_pPickColorDlg;
	FrNotifyForm* m_pAskCancelDlg;
	FrForm* m_pAskResetDlg;
	FrForm* m_pAskCompleteDlg;
	const Bitmap* m_pToolBox;
	const Bitmap* m_pSelectBox;
	const Bitmap* m_pSelectSBox2;
	const Bitmap* m_pBgText1[2];
	const Bitmap* m_pBgText2[2];
	const Bitmap* m_pToolChangeIcon;
	const Bitmap* m_pSelectBoxYellow;
	const Bitmap* m_pSelectBoxPink;
	const Bitmap* m_pSelectColor;
	unsigned char m_unknown3c8[4];
	int m_defaultEraser;
	eBrushType m_brushType;
	int m_side;
	eDrawMode m_drawMode;
	char m_name[64];
	WRect m_canvasRect;
	Bitmap m_pattern[24];
	eUccTab m_currentTab;
	Bitmap m_blankPattern;
	Bitmap m_emptyPattern;
	int m_patternIndex;
	int m_patternRate;
	bool m_bPatternFolded;
	bool m_bGrid;
	Bitmap m_unknown644;
	bool m_bInitialized;
	COverlayCursor m_cursor;
	CFadingText m_fadingText;

private:
	DECLARE_FRESH_MSGMAP()
};
