#pragma once

#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include "singleton.h"

class WReceivedPacket;

enum ePaperTheme
{
	PT_CUPINHOLDING,
	PT_RECORD,
	PT_AWARD,
	PT_MAX
};

class CPaper : public WSingleton<CPaper>
{
public:
	class cMemo
	{
	public:
		cMemo(const char* time, unsigned int signature, const char* message)
			: m_time(time), m_signature(signature), m_message(message)
		{
		}
		std::string m_time;
		unsigned int m_signature;
		std::string m_message;
	};

	CPaper();
	virtual ~CPaper();

	void SetServerTime(const SYSTEMTIME& time);
	void PrepareNewPaper(const char* user);
	void Destroy();
	bool AddMemo(ePaperTheme theme, const char* signature, const char* message);
	const char* GetEnumStr(ePaperTheme theme) const;
	const char* GetFuncSigStr(unsigned int id) const;
	const char* GetServerTime() const;
	unsigned int GetMemoSize(ePaperTheme theme) const;
	void GetServerTime(SYSTEMTIME& time) const;
	bool PrintOut(ePaperTheme theme);
	void ReceivedPacket(WReceivedPacket* packet);
	void SendUpdatableQuery();
	void Send();
	const char* SystemTimeToString(const SYSTEMTIME& time) const;
	unsigned int GetFuncSigId(const char* signature);

private:
	SYSTEMTIME m_createTime;
	SYSTEMTIME m_sendTime;
	std::string m_user;
	std::multimap<ePaperTheme, cMemo> m_memos;
	std::vector<std::string> m_signatures;
	std::map<std::string, unsigned int> m_signatureIds;
	int m_updating;
};

class CPaperMemo
{
public:
	CPaperMemo(const char* signature);
	~CPaperMemo();
	void __cdecl Write(ePaperTheme theme, const char* format, ...);

private:
	std::string m_signature;
};
