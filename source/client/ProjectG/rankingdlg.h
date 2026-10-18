#pragma once

#include "frform.h"
#include "fredit.h"
#include "anotherhand.h"
#include "../../shared/globalgamedefine.h"

class FrEmoticonDlg;
class FrRankingAboutDlg;
class CExhibition;
class CPartTidList;
class FrComboBox;
class FrTextButton;
class FrGaugeBar;
class FrListBox;
struct FrListItem;
class FrViewer;
struct sTypeName;

namespace ranktype
{
	struct sRankRecord
	{
		unsigned long rank;
		unsigned long preRank;
		int value;
	};

	struct sRankUserInfo
	{
		unsigned long uid;
		char id[22];
		char nickname[22];
		unsigned char level;
		unsigned char reserved;
		sCharacterInfo charInfo;
		sRankRecord record[5];
	};
}

class FrRankingDlg : public FrForm, public CHandOwner
{
	friend class CTask;

public:
	DECLARE_OBJECT(FrRankingDlg)

	FrRankingDlg();
	virtual ~FrRankingDlg();

protected:
	virtual bool OnInit();
	virtual void OnCancel();
	virtual void OnProc(const float);
	virtual void OnAnotherHand(int, void*);
	void ResetControl();
	void SetVisibleByRankType();
	void SetVisibleUserInfo(bool);

public:
	void UpdateRankList();
	void ClearRankList();
	void UpdateMyInfo();
	void UpdateUserInfo();

protected:
	void SetPetCharacter();
	void SetListItemInfo(FrListItem*);
	void ShowUserInfo();
	void DrawUserInfoLine(int, int, WPoint&);

public:
	void DisconnectRankServer();
	static void SetRankTypes(unsigned char, unsigned char, unsigned char,
		unsigned char, int, int);
	void SelectRankList(int);

protected:
	void SynchronizeButtons();
	void CloseAllComboBtns();
	void SetAllControlsEnable(bool);
	void HidePet(bool);
	void SendRequestRank(bool);
	void SendRequestUserInfo(unsigned long, const char*);
	void SendRequestSearchUser(const char*);
	void OnTermType_S5_BtnInit(int);
	void OnTermType_S5_BtnUp();
	void OnCourseAreaInit(int);
	void OnCourseAreaOwnerDraw(int);
	void OnRankList_Init(int);
	void OnRankList_OwnerDraw(int);
	void OnRankList_LBtnDown();
	void OnRankList_PrevPageInit(int);
	void OnRankList_PrevPageBtnUp();
	void OnRankList_NextPageInit(int);
	void OnRankList_NextPageBtnUp();
	void OnRankList_CurrentPageInit(int);
	void OnRankList_TotalPageInit(int);
	void OnRankList_MyInfo_Init(int);
	void OnRankList_MyInfo_LBtnDown();
	void OnRankList_MyInfo_OwnerDraw(int);
	void OnRankList_NoInRank_Init(int);
	void OnRankList_SearchUserInit(int);
	void OnRankList_SearchUserBtnUp();
	void OnRankList_UserIdEditInit(int);
	void OnRankList_UserIdEditDown();
	void OnEmoticonInit(int);
	void OnEmoticonBtnUp();
	void OnLanguageInit(int);
	void OnAboutBtnInit(int);
	void OnAboutBtnUp();
	void OnCloseBtnUp();
	void OnBottomMessageInit(int);
	void OnPetCharacterInit(int);
	void OnPetCharacterOwnerDraw();
	void OnPetLoadInit(int);
	void OnUpperMiniInfoInit(int);
	void OnUpperMiniInfoOwnerDraw();
	void OnClassType_ComboInit(int);
	void OnClassType_ComboDown(int);
	void OnRankTypeListInit(int);
	void OnRankTypeListLDown();
	void OnRankTypeListOwnerDraw(int);
	void OnRankTypeViewerInit(int);
	void OnRankTypeViewerDown();
	void OnRankTypeViewerOwnerDraw();
	void OnGeneralSubTypeListInit(int);
	void OnGeneralSubTypeListLDown();
	void OnGeneralSubTypeListOwnerDraw(int);
	void OnGeneralSubTypeViewerInit(int);
	void OnGeneralSubTypeViewerDown();
	void OnGeneralSubTypeViewerOwnerDraw();
	void OnCourseTypeListInit(int);
	void OnCourseTypeListLDown();
	void OnCourseTypeListOwnerDraw(int);
	void OnCourseTypeViewerInit(int);
	void OnCourseTypeViewerDown();
	void OnCourseTypeViewerOwnerDraw();
	void OnRecordTypeListInit(int);
	void OnRecordTypeListLDown();
	void OnRecordTypeListOwnerDraw(int);
	void OnRecordTypeViewerInit(int);
	void OnRecordTypeViewerDown();
	void OnRecordTypeViewerOwnerDraw();
	void OnSearchTypeListInit(int);
	void OnSearchTypeListLDown();
	void OnSearchTypeListOwnerDraw(int);
	void OnSearchTypeViewerInit(int);
	void OnSearchTypeViewerDown();
	void OnSearchTypeViewerOwnerDraw();
	void OnUserRankEditInit(int);

public:
	void OnNotify(const char*, unsigned long);
	void SetBottomMsg(const char*);
	void OnCustomProc(float);

protected:
	bool OnEmoticonResult(int, FrForm*);
	bool OnAboutDlgResult(int, FrForm*);
	void OnGhostBtnInit(int);
	void OnGhostBtnUp();

	static const int s_iListCountPerPage;
	static int s_iRankType;
	static int s_iSubType;
	static int s_iTermType;
	static int s_iClassType;
	static int s_iPageNum;
	static int s_iPageTotal;
	static int s_iSearchType;
	static const sTypeName s_aRankType[];
	static const sTypeName s_aClassType[];
	static const sTypeName s_aGenSubType[];
	static const sTypeName s_aCourseType[];
	static const sTypeName s_aRecordType[];
	static const sTypeName s_aTermType[];
	static const sTypeName s_aSearchType[];

	std::list<ranktype::sListInfo> m_rankInfoList;
	ranktype::sListInfo m_myRankInfo;
	ranktype::sRankUserInfo m_userInfo;
	FrLine m_courseTypeLine[17];
	FrLine m_searchTypeLine[2];
	FrLine m_recordTypeLine[5];
	FrLine m_rankTypeLine[3];
	FrLine m_genSubTypeLine[5];
	FrButton* m_pTermTypeS5;
	FrComboBox* m_pClassTypeCombo;
	FrListBox* m_pRankList;
	FrListBox* m_pMyInfo;
	FrArea* m_pCourseArea;
	FrStatic* m_pNoInRank;
	FrButton* m_pSearchUser;
	FrEdit* m_pUserIdEdit;
	FrButton* m_pEmoticon;
	FrArea* m_pLanguage;
	FrEdit* m_pCurrentPage;
	FrEdit* m_pTotalPage;
	FrEdit* m_pUserRankEdit;
	FrGaugeBar* m_pPetLoad;
	FrStatic* m_pBottomMessage;
	FrEmoticonDlg* m_pEmoticonDlg;
	FrRankingAboutDlg* m_pAboutDlg;
	FrListBox* m_pRankTypeList;
	FrViewer* m_pRankTypeViewer;
	const Bitmap* m_pRankTypeBtn[3];
	FrListBox* m_pGenSubTypeList;
	FrViewer* m_pGenSubTypeViewer;
	const Bitmap* m_pGenSubTypeBtn[3];
	FrListBox* m_pCourseTypeList;
	FrViewer* m_pCourseTypeViewer;
	const Bitmap* m_pCourseTypeBtn[3];
	FrListBox* m_pRecordTypeList;
	FrViewer* m_pRecordTypeViewer;
	const Bitmap* m_pRecordTypeBtn[3];
	FrListBox* m_pSearchTypeList;
	FrViewer* m_pSearchTypeViewer;
	const Bitmap* m_pSearchTypeBtn[3];
	FrArea* m_pPetCharacter;
	CExhibition* m_pExhibition;
	CPartTidList* m_pPartTidList;
	FrButton* m_pGhostBtn;
	FrArea* m_pUpperMiniInfo;
	CAnotherHand m_anotherHand;
	float m_requestDelay;

	DECLARE_FRESH_MSGMAP()
};

class FrRankingAboutDlg : public FrForm
{
public:
	DECLARE_OBJECT(FrRankingAboutDlg)

	FrRankingAboutDlg();
	virtual ~FrRankingAboutDlg();

	void SetImgAboutIndex(int index);

protected:
	virtual bool OnInit();

	void OnAboutViewerInit(int param);
	void OnIndex01Init(int param);
	void OnIndex01BnUp();
	void OnIndex02Init(int param);
	void OnIndex02BnUp();
	void OnIndex03Init(int param);
	void OnIndex03BnUp();
	void OnIndex04Init(int param);
	void OnIndex04BnUp();
	void OnBackwardBnInit(int param);
	void OnBackwardBnUp();
	void OnForwardBnInit(int param);
	void OnForwardBnUp();
	void OnOkBnInit(int param);
	void OnOkBnUp();

	FrTextButton* m_pIndex[4];
	int m_index;
	FrButton* m_pBackward;
	FrButton* m_pForward;
	FrViewer* m_pViewer;

	DECLARE_FRESH_MSGMAP()
};

struct sTypeName
{
	int type;
	const char* name;
};
