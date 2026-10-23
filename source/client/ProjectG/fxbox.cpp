#include "stdafx.h"
#include "binstr.h"
#include "fxbox.h"
#include "fxbox.inl"
#include "clientsetting.h"
#include "mathconsts.h"
#include <stdio.h>
#include <stdlib.h>
extern WResourceManager* g_resrcmng;

CFxBox::CFxBox()
{
	m_resrcMng = NULL;
	m_bPause = false;
	m_drawFlag = 0;
	m_frameTime = 1000.f / 30.f;
	m_bLimitFrame = true;
	m_timeScale = 1.f;
	m_name[0] = 0;
	m_particleNum = 0;
	m_tailNum = 0;
	m_bShowBound = false;
	m_camera = NULL;
	m_groundHeightMax = 99.f;
	m_groundHeightMin = -99.f;
	m_quad[0] = m_vtx;
	m_quad[1] = m_vtx + 1;
	m_quad[2] = m_vtx + 3;
	m_quad[3] = m_vtx + 2;
	m_quad[4] = NULL;
	for (int i = 0; i < 4; ++i)
	{
		m_vtx[i].tu = (i & 2) ? 1.f : 0.f;
		m_vtx[i].tv = (i & 1) ? 0.f : 1.f;
		m_vtx[i].diffuse = 0xffffffff;
	}
}

CFxBox::~CFxBox()
{
	ClearFxKeeper();
	Clear();
}

void CFxBox::Clear()
{
	ClearAll(true);
	ClearSprite();
	ClearOriginalSpray();
	ClearOriginalSequence();
}

void CFxBox::Init(WResourceManager* manager)
{
	m_resrcMng = manager;
}

void CFxBox::SetCamera(const WMatrix* camera)
{
	m_camera = camera;
}

void CFxBox::ClearSprite()
{
	for (FxSpriteIterator it = m_sprite.begin(); it != m_sprite.end(); ++it)
	{
		if (m_resrcMng && (*it).second)
		{
			m_resrcMng->Release((*it).second);
			(*it).second = NULL;
		}
	}
	m_sprite.clear();
}

void CFxBox::ClearOriginalSpray()
{
	for (FxSprayCacheIterator it = m_originalSpray.begin();
		it != m_originalSpray.end(); ++it)
	{
		CFxSpray* spray = (*it).second;
		if (g_resrcmng && spray->m_tailTexHandle)
		{
			g_resrcmng->Release(spray->m_tailTexHandle);
			spray->m_tailTexHandle = NULL;
		}
		delete spray;
	}
	m_originalSpray.clear();
}

void CFxBox::ClearOriginalSequence()
{
	for (FxSequenceCacheIterator it = m_sequenceCache.begin();
		it != m_sequenceCache.end(); ++it)
		delete (*it).second;
	m_sequenceCache.clear();
}

void CFxBox::ClearAll(bool markedOnly)
{
	ClearSequence(markedOnly);
	ClearSpray(markedOnly);
}

void CFxBox::ClearSpray(bool markedOnly)
{
	std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
	while (it != m_spray.end())
	{
		CFxSpray* spray = (*it).second;
		if (spray)
		{
			if (!markedOnly || spray->m_bMark)
				DeleteSpray(it);
			else
				++it;
		}
	}
}

void CFxBox::DeleteSpray(CFxSpray* spray)
{
	std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.find(spray);
	if (it != m_spray.end())
		DeleteSpray(it);
}

void CFxBox::DeleteSpray(std::map<CFxSpray*, CFxSpray*>::iterator& it)
{
	CFxSpray* spray = (*it).second;
	m_spray.erase(it++);
	OnSprayDeleted(spray);
	if (spray->m_parent)
		spray->m_parent->DeleteChildSpray(spray);
	CallFxKeeperCallBack(spray);
	delete spray;
}

void CFxBox::ClearSequence(bool markedOnly)
{
	std::map<CFxSequence*, CFxSequence*>::iterator it = m_sequence.begin();
	while (it != m_sequence.end())
	{
		CFxSequence* sequence = (*it).second;
		if (sequence)
		{
			if (!markedOnly || sequence->m_bMark)
				DeleteSequence(it, false);
			else
				++it;
		}
	}
}

void CFxBox::DeleteSequence(CFxSequence* sequence, bool deleteChild)
{
	std::map<CFxSequence*, CFxSequence*>::iterator it =
		m_sequence.find(sequence);
	if (it != m_sequence.end())
		DeleteSequence(it, deleteChild);
}

void CFxBox::DeleteSequence(std::map<CFxSequence*, CFxSequence*>::iterator& it,
	bool deleteChild)
{
	CFxSequence* sequence = (*it).second;
	m_sequence.erase(it++);

	std::map<CFxSpray*, CFxSpray*>::iterator child =
		sequence->GetSprayList().begin();
	while (child != sequence->GetSprayList().end())
	{
		CFxSpray* spray = (*child).second;
		if (!spray)
		{
			sequence->GetSprayList().erase(child++);
			continue;
		}
		if (spray && deleteChild)
		{
			++child;
			DeleteSpray(spray);
			continue;
		}
		WVector& pos = spray->Pos();
		pos += sequence->Pos();
		spray->m_parent = NULL;
		if (spray->m_strongBond && sequence->m_attacher)
		{
			spray->m_attacher = (Attacher*)sequence->m_attacher;
			AddSpray(spray);
		}
		++child;
	}
	OnSequenceDeleted(sequence);
	if (sequence->m_bDelete)
	{
		CallFxKeeperCallBack(sequence);
		delete sequence;
	}
}

bool CFxBox::Finished()
{
	return m_sequence.size() == 0 && m_spray.size() == 0;
}

const CFxSequence::sLine& CFxBox::GetLastError()
{
	return m_lastError;
}

CFxSequence* CFxBox::LoadSequence(const char* name, bool temporary,
	defines_t* defines)
{
	CFxSequence* sequence = new CFxSequence(*this, temporary);
	ClearDefines(sequence->m_defines, defines);
	if (sequence->LoadFile(name))
	{
		sequence->m_filename = name;
		return sequence;
	}
	delete sequence;
	return NULL;
}

void CFxBox::AddSequence(CFxSequence* sequence)
{
	sequence->SetLineTime();
	m_sequence[sequence] = sequence;
	OnSequenceCreated(sequence);
}

CFxSpray* CFxBox::LoadSpray(const char* name, defines_t* defines)
{
	CFxSpray* spray = new CFxSpray(*this);
	ClearDefines(spray->m_defines, defines);
	if (spray->ParseFile(name, defines == NULL))
		return spray;
	delete spray;
	return NULL;
}

void CFxBox::AddSpray(CFxSpray* spray)
{
	m_spray[spray] = spray;
	OnSprayCreated(spray);
}

float CFxBox::ParseNumber(const char* text)
{
	int len = strlen(text);
	if (!len)
		return 0.f;
	if (text[len - 1] == 'd')
		return (float)atof(text) * g_DEGTORAD;
	if (text[len - 1] == 'f')
		return (float)atof(text) * m_frameTime;
	return (float)atof(text);
}

W3dAniSpr* CFxBox::LoadSprite(const char* name, int width, int height)
{
	char key[272];
	sprintf(key, "%s_%dx%d", name, width, height);
	FxSpriteIterator it = m_sprite.find(key);
	if (it != m_sprite.end())
		return (*it).second;
	if (!m_resrcMng)
		return NULL;
	W3dAniSpr* sprite = new W3dAniSpr;
	sprite->SetResourceManager(m_resrcMng);
	sprite->LoadSpritesInOneTexture(name, 0, (float)width, (float)height);
	m_sprite[key] = sprite;
	return sprite;
}

bool CFxBox::Process(float elapsed)
{
	if (m_bPause)
		return true;
	if (m_bLimitFrame && elapsed > m_frameTime * 1.5f)
		elapsed = m_frameTime * 1.5f;
	std::map<CFxSpray*, CFxSpray*>::iterator spray = m_spray.begin();
	while (spray != m_spray.end())
	{
		CFxSpray* p = (*spray).second;
		if (!p)
		{
			m_spray.erase(spray++);
			continue;
		}
		if (!p->Process(elapsed * m_timeScale))
			DeleteSpray(spray);
		else
			++spray;
	}
	std::map<CFxSequence*, CFxSequence*>::iterator it = m_sequence.begin();
	while (it != m_sequence.end())
	{
		CFxSequence* sequence = (*it).second;
		if (!sequence)
		{
			m_sequence.erase(it++);
			continue;
		}
		bool error;
		if (!sequence->Process(elapsed * m_timeScale, error))
			DeleteSequence(it, false);
		else
			++it;
		if (error)
		{
			m_lastError = sequence->GetLastError();
			return false;
		}
	}
	return true;
}

void CFxBox::Display(WView* view)
{
	m_particleNum = 0;
	m_tailNum = 0;
	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it)
	{
		CFxSpray* spray = (*it).second;
		spray->Display(view);
		m_particleNum += spray->m_particleNum;
		m_tailNum += spray->m_tailNum;
	}
}

void CFxBox::ClearDefines(defines_t& defines, defines_t* src)
{
	for (int i = 0; i < 16; ++i)
		defines.name[i][0] = 0;
	strcpy(defines.name[0], "particle_level");
	if (COption::IsInstantiated())
		defines.value[0] =
			(float)max(1, 2 - COption::Instance()->vGetParticleLevel());
	else
		defines.value[0] = 0;
	if (src)
	{
		for (int i = 0; i < src->num; ++i)
		{
			strcpy(defines.name[i + 1], src->name[i]);
			defines.value[i + 1] = src->value[i];
		}
		defines.num = src->num + 1;
	}
	else
		defines.num = 1;
}

bool CFxBox::PreprocessDefines(defines_t& defines, const char* text)
{
	cTokenV parser;
	parser.Init(text, strlen(text));
	char token[260], name[260];
	parser.GetToken(token, " ", 1);
	if (!stricmp(token, "#define"))
	{
		parser.GetTokenWithoutFail(name, " \r\n\t", 4);
		int i;
		for (i = 0; i < defines.num; ++i)
			if (!stricmp(name, defines.name[i]))
				break;
		if (i >= defines.num)
		{
			int op = 0;
			float values[2];
			float* value = values;
			for (i = 0; i < 16; ++i)
			{
				parser.GetTokenWithoutFail(token, " \r\n\t", 4);
				if (token[0])
				{
					if (!stricmp(token, "*"))
						op = 3;
					else if (!stricmp(token, "/"))
						op = 4;
					else if (!stricmp(token, "+"))
						op = 1;
					else if (!stricmp(token, "-"))
						op = 2;
					else
					{
						int j;
						for (j = 0; j < defines.num; ++j)
							if (!stricmp(token, defines.name[j]))
							{
								*value++ = defines.value[j];
								break;
							}
						if (j == defines.num)
							*value++ = atof(token);
					}
				}
			}
			float result;
			switch (op)
			{
			case 1:
				result = values[0] + values[1];
				break;
			case 2:
				result = values[0] - values[1];
				break;
			case 3:
				result = values[0] * values[1];
				break;
			case 4:
				result = values[0] / values[1];
				break;
			default:
				result = values[0];
			}
			strcpy(defines.name[defines.num], name);
			defines.value[defines.num++] = result;
		}
		return true;
	}
	return false;
}

void CFxBox::ProcessDefines(defines_t& defines, char* text)
{
	for (int i = 0; i < defines.num; ++i)
		if (!stricmp(text, defines.name[i]))
			gcvt(defines.value[i], 10, text);
}

void CFxBox::AddFxKeeper(sFxKeeper& keeper)
{
	if (keeper.keeper)
		keeper.keeper->SetFxManager(this);
	m_fxKeeper.push_back(keeper);
}

void CFxBox::CallFxKeeperCallBack(void* fx)
{
	for (FxKeeperIterator it = m_fxKeeper.begin(); it != m_fxKeeper.end(); ++it)
		((*it).keeper->*((*it).notify))(fx);
}

void CFxBox::EraseFxKeeper(CFxKeeper* keeper)
{
	FxKeeperIterator it;
	if (!keeper)
		return;
	for (it = m_fxKeeper.begin(); it != m_fxKeeper.end(); ++it)
		if ((*it).keeper == keeper)
		{
			m_fxKeeper.erase(it);
			break;
		}
}

void CFxBox::ClearFxKeeper()
{
	m_fxKeeper.clear();
}

void CFxBox::SetScreenCenter(float x, float y)
{
	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it)
	{
		CFxSpray* spray = (*it).second;
		if (spray)
		{
			spray->m_centerX = x;
			spray->m_centerY = y;
		}
	}
	for (std::map<CFxSequence*, CFxSequence*>::iterator it = m_sequence.begin();
		it != m_sequence.end(); ++it)
	{
		CFxSequence* seq = (*it).second;
		if (seq)
		{
			seq->m_centerX = x;
			seq->m_centerY = y;
		}
	}
}
