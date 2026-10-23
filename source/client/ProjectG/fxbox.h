#pragma once

#include <string>
#include <list>
#include <map>
#include "fxspray.h"
#include "fxsequence.h"

class CFxKeeper;
struct sFxKeeper;
typedef std::list<sFxKeeper>::iterator FxKeeperIterator;
typedef std::map<std::string, CFxSpray*>::iterator FxSprayCacheIterator;
typedef std::map<std::string, CFxSequence*>::iterator FxSequenceCacheIterator;
typedef std::map<std::string, W3dAniSpr*>::iterator FxSpriteIterator;

class CFxBox
{
	friend class CFxSpray;
	friend class CFxSequence;

public:
	CFxBox();
	virtual ~CFxBox();

	void Init(WResourceManager* resMng);
	void SetCamera(const WMatrix* camera);

	void Clear();
	void ClearAll(bool bMarkedOnly);
	void ClearSprite();
	void ClearOriginalSpray();
	void ClearOriginalSequence();
	void ClearSpray(bool bMarkedOnly);
	void DeleteSpray(CFxSpray* spray);
	void ClearSequence(bool bMarkedOnly);
	void DeleteSequence(CFxSequence* sequence, bool bDeleteChild);
	bool Finished();
	const CFxSequence::sLine& GetLastError();

	CFxSequence* LoadSequence(const char* filename, bool bDelete,
		defines_t* defines);
	void AddSequence(CFxSequence* sequence);
	CFxSpray* LoadSpray(const char* filename, defines_t* defines = NULL);
	void AddSpray(CFxSpray* spray);

	bool Process(float elapsed);
	void Display(WView* view);

	void ClearDefines(defines_t& defines, defines_t* src);
	bool PreprocessDefines(defines_t& defines, const char* line);
	void ProcessDefines(defines_t& defines, char* str);

	void AddFxKeeper(sFxKeeper& keeper);
	void CallFxKeeperCallBack(void* fx);
	void EraseFxKeeper(CFxKeeper* keeper);
	void ClearFxKeeper();

	void SetScreenCenter(float x, float y);

	std::map<CFxSequence*, CFxSequence*>& GetSequenceList();
	std::map<CFxSpray*, CFxSpray*>& GetSprayList();
	CFxSpray* GetSpray(int index);
	bool FindSequence(CFxSequence* sequence);
	bool FindSpray(CFxSpray* spray);
	bool GetOutput(WVector& quake, unsigned char& flash);

	virtual void ProcessAttacher(float elapsed) { }

	void SetGroundHeightArea(float maxHeight, float minHeight)
	{
		m_groundHeightMax = maxHeight;
		m_groundHeightMin = minHeight;
	}

protected:
	float ParseNumber(const char* str);
	W3dAniSpr* LoadSprite(const char* filename, int width, int height);
	float Random(float min, float max);
	WVector Random(const WVector& min, const WVector& max);
	WVector Random(const WVector& center, float minRadius, float maxRadius,
		float angle);

	virtual bool CheckGroundCollision(const WVector& from, const WVector& to,
		float& height, float radius);
	virtual void OnSequenceCreated(CFxSequence* sequence);
	virtual void OnSequenceDeleted(CFxSequence* sequence);
	virtual void OnSprayCreated(CFxSpray* spray);
	virtual void OnSprayDeleted(CFxSpray* spray);

private:
	void DeleteSpray(std::map<CFxSpray*, CFxSpray*>::iterator& it);
	void DeleteSequence(std::map<CFxSequence*, CFxSequence*>::iterator& it,
		bool bDeleteChild);

public:
	float m_frameTime;

protected:
	float m_timeScale;
	char m_name[260];
	bool m_bPause;
	unsigned long m_drawFlag;
	bool m_bLimitFrame;
	int m_particleNum;
	int m_tailNum;
	bool m_bShowBound;
	std::map<std::string, CFxSpray*> m_originalSpray;
	std::map<std::string, CFxSequence*> m_sequenceCache;
	WResourceManager* m_resrcMng;
	std::map<std::string, W3dAniSpr*> m_sprite;
	std::map<CFxSpray*, CFxSpray*> m_spray;
	std::map<CFxSequence*, CFxSequence*> m_sequence;
	const WMatrix* m_camera;
	WTVertex* m_quad[5];
	WTVertex m_vtx[4];
	CFxSequence::sLine m_lastError;
	unsigned char m_unused[4];
	std::list<sFxKeeper> m_fxKeeper;
	float m_groundHeightMax;
	float m_groundHeightMin;
};

class CFxKeeper
{
public:
	CFxKeeper()
		: m_pManager(NULL)
	{
	}
	virtual ~CFxKeeper()
	{
		if (m_pManager)
			m_pManager->EraseFxKeeper(this);
	}
	virtual void EmptyFx(void* fx) = 0;
	void SetFxManager(CFxBox* fxBox) { m_pManager = fxBox; }

protected:
	CFxBox* m_pManager;
};

struct sFxKeeper
{
	CFxKeeper* keeper;
	void (CFxKeeper::*notify)(void* fx);
};
