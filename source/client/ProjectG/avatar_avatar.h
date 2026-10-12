#pragma once

#include "singleton.h"

class ntAvatar;
class ntAvatarChatMain;
class CQuadTree;
class WVector;
struct sSlotInfo;
struct sCharacterInfo;

class ntAvatarManager : public WSingleton<ntAvatarManager>
{
public:
	ntAvatarManager();
	virtual ~ntAvatarManager();

	ntAvatar* CreateAvatar(const sSlotInfo& slot, const sCharacterInfo& info,
		ntAvatarChatMain* pMain);
	bool DeleteAvatar(const char* idName);
	void FreeAllAvatars();
	void Process(float delta);
	void Render();
	void RenderOverlay();
	void ResetAvatarPositionAngle();
	ntAvatar* FindAvatarByIDName(const char* idName) const;
	ntAvatar* FindAvatarByNickName(const char* nickName) const;
	ntAvatar* FindAvatarByGuid(int guid) const;
	ntAvatar* CheckClick(float x, float y) const;
	ntAvatar* AvatarByRayIntersect(const WVector& from,
		const WVector& to) const;

	void SetActive(bool bActive) { m_bActive = bActive; }

protected:
	CQuadTree& GetPVS();
	void SetLocalPVS(CQuadTree& pvs);

public:
	int m_avatarCount;
	ntAvatar* m_avatar[30];
	ntAvatar* m_pMyAvatar;
	ntAvatar* m_pPickedAvatar;
	ntAvatar* m_pClickedAvatar;
	bool m_bActive;
	bool m_bShowName;
	CQuadTree* m_pPVS;
};
