#pragma once

#include "fxsequence.h"

class CFxKeeper;

// TODO: incomplete
class CFxBox
{
	friend class CFxSequence;

public:
	CFxSpray* LoadSpray(const char* filename, defines_t* defines = NULL);
	void AddSpray(CFxSpray* spray);
	bool PreprocessDefines(defines_t& defines, const char* text);
	void ProcessDefines(defines_t& defines, char* text);

protected:
	float ParseNumber(const char* text);

public:
	CFxBox();
	virtual ~CFxBox();
	void EraseFxKeeper(CFxKeeper* keeper);

	virtual void ProcessAttacher(float elapsed) { }

	void SetGroundHeightArea(float maxHeight, float minHeight)
	{
		m_groundHeightMax = maxHeight;
		m_groundHeightMin = minHeight;
	}

protected:
	virtual bool CheckGroundCollision(const WVector& from, const WVector& to,
		float& height, float radius);
	virtual void OnSequenceCreated(CFxSequence* sequence);
	virtual void OnSequenceDeleted(CFxSequence* sequence);
	virtual void OnSprayCreated(CFxSpray* spray);
	virtual void OnSprayDeleted(CFxSpray* spray);

public:
	float m_frameTime;
	unsigned char m_unused8[300];
	std::map<std::string, CFxSequence*> m_sequenceCache;
	WResourceManager* m_resrcMng;
	unsigned char m_unused144[512];

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
	void SetFxManager(CFxBox* manager);

protected:
	CFxBox* m_pManager;
};

struct sFxKeeper
{
	CFxKeeper* keeper;
	void (CFxKeeper::*notify)(void*);
};
