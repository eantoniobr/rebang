#pragma once

// TODO: incomplete
class CShadowManager : public WSingleton<CShadowManager>
{
public:
	CShadowManager(WResourceManager* pResMgr, bool bEnable);
	virtual ~CShadowManager();

	void UpdateLight(const char* lightName, LightSet& light);
	void AddCastPet_New(const char* recvName, bool flag, WPuppet* pet);
	void Enable(bool bEnable);
	void SetActive(bool bActive);

protected:
	bool m_bEnable;
	unsigned char m_unused2c[0x30];
};
