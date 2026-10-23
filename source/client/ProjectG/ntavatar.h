#pragma once

#include <list>
#include "singleton.h"
#include "wbone.h"
#include "../../shared/globalgamedefine.h"
#include "parttidlist.h"
#include "fx.h"
#include "../../shared/s5/specialprize/specialprizeitem.h"

enum eSPAVILITYTYPE;
class CQuadTree;
class CPetFrame;
class ntAvatarChatMain;
class ntBalloonText;
struct sTexturePart;
struct Attacher;
struct defines_t;

struct trace_s
{
	WVector endpos;
	float fraction;
	WPlane plane;
	bool startsolid;
};

class ntAvatarBurden
{
public:
	ntAvatarBurden()
		: m_pPetFrame(NULL)
	{
	}
	ntAvatarBurden(unsigned long uid, unsigned long guid,
		const sCharacterInfo& info, CPetFrame* pPetFrame);
	~ntAvatarBurden();

	bool operator<(const ntAvatarBurden& rhs) { return m_guid < rhs.m_guid; }

	bool operator==(const ntAvatarBurden& rhs)
	{
		return m_guid == rhs.m_guid && m_pPetFrame != (CPetFrame*)-1 &&
			rhs.m_pPetFrame != (CPetFrame*)-1;
	}

	bool Load();

	unsigned long m_uid;
	unsigned long m_guid;
	sCharacterInfo m_charInfo;
	CPartTidList m_partTidList;
	CPetFrame* m_pPetFrame;
	unsigned long m_reserved;
};

class ntAvatar
{
	friend class ntAvatarManager;

protected:
	ntAvatar(CQuadTree& pvs, const sSlotInfo& slot, const sCharacterInfo& info,
		ntAvatarChatMain* pMain);

public:
	~ntAvatar();

	void Process(float delta);
	void Render();
	void RenderOverlay(bool bSelected);
	bool IsClickable(float x, float y) const;
	bool GetBoneScreenCoord(const char* bone, int* x, int* y) const;

	void SetCharactorInfo(const sCharacterInfo& info);
	void SetPosition(const WVector& pos);
	void SetTargetPosition(const WVector& pos);
	bool IsTargetPositionChanged(bool bReset);
	void SetAngle(float angle);
	void SetTargetAngle(float angle);
	void SetPendingTargetAngle(float angle);
	void SetState(unsigned long state);
	void SetAction(int action);
	void ChangeMotion(int motion, const char* name, float blendTime);
	void SetChatFacial(int facial);
	void Stop();
	void Follow(const char* nickName);
	ntAvatar* GetFollowingAvatar() const;
	void SetBalloonText(const char* text);
	void SetTradeTitle(const char* title);
	void RefreshUccClothes(unsigned long typeId, unsigned long uid);
	void UseSPItem(eSPAVILITYTYPE type);
	SpecialPrizeItem& GetMySpItem(eSPAVILITYTYPE type);

	const sCharacterInfo& GetCharacterInfo() const { return m_charInfo; }

	bool IsMoving() const
	{
		return (m_pos - m_targetPos).Magnitude() > 0.001f ? true : false;
	}
	bool IsFollowing() const { return m_followName[0] ? true : false; }

	bool IsHoldState() const { return (m_state & 0x7e) ? true : false; }

	unsigned long GetUID() const { return m_uid; }
	unsigned long GetGuid() const { return m_guid; }
	const char* GetIDName() const { return m_idName; }
	const char* GetNickName() const { return m_nickName; }

	const WVector& GetPosition() const { return m_pos; }
	const WVector& GetTargetPosition() const { return m_targetPos; }

	int GetMotion() const { return m_motion; }
	unsigned long GetState() const { return m_state; }
	unsigned long GetAction() const { return m_action; }

protected:
	CQuadTree& GetPVS();
	void SetLocalPVS(CQuadTree& pvs);

public:
	void AddState(unsigned long state) { SetState(m_state | state); }
	void SubState(unsigned long state) { SetState(m_state & ~state); }

	void SetHeadIcon(int icon) { m_headIcon = icon; }

private:
	void SendMove(const WVector& pos, bool bForce);
	void ProcessMotion(float delta);
	void ProcessChangeState();
	void ScriptProcess(const w_motion_data* data, float from, float to,
		bool bLoop);
	void ParsePuppetScript(const char* script);
	void ParseScript_ShowVis(bool bShow, const char* name);
	sTexturePart* FindTexturePart(const char* part, const char* tex);
	void SetPendingTexPart(const char* part, const char* tex);
	void* AttachFx(const Attacher& attacher, const char* name, bool bLoop,
		defines_t* defines);

public:
	CPartTidList& GetPartTidList() { return m_partTidList; }

public:
	CQuadTree* m_pPVS;
	char m_idName[22];
	char m_nickName[22];
	char m_targetName[22];
	char m_followName[22];
	bool m_bShowProviderId;
	char m_providerId[128];
	unsigned long m_uid;
	unsigned long m_guid;
	bool m_bGM;
	unsigned char m_mark;
	bool m_bGoodPlayer;
	bool m_bAngelWing;
	unsigned long m_charTypeId;
	unsigned long m_state;
	unsigned long m_prevState;
	unsigned long m_action;
	WVector m_pos;
	float m_angle;
	float m_targetAngle;
	bool m_bPendingTargetAngle;
	float m_pendingTargetAngle;
	WVector m_up;
	WVector m_targetPos;
	bool m_bTargetPosChanged;
	int m_headIcon;
	WVector m_moveDir;
	ntAvatarBurden m_burden;
	bool m_bBurdenLoaded;
	sCharacterInfo m_charInfo;
	CPartTidList m_partTidList;
	CPetFrame* m_pPetFrame;
	std::list<sTexturePart*> m_texPartList;
	float m_height;
	LightSet m_light;
	w_motion_data* m_pMotionData;
	int m_motion;
	WBoneSet m_bones;
	w_motion_data* m_pPrevMotionData;
	int m_prevMotion;
	WBoneSet m_prevBones;
	float m_blendTime;
	float m_blendElapsed;
	float m_motionTime;
	float m_facialTime;
	unsigned long m_lastMotionSendTime;
	ntBalloonText* m_pBalloon;
	float m_balloonColor[4];
	float m_balloonTime;
	char m_tradeTitle[64];
	const Bitmap* m_pEmblem;
	ntAvatarChatMain* m_pMain;
	CPvsFxBox m_fxBox;
	SpecialPrizeItem m_spItem[5];
};
