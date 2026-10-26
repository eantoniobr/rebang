#pragma once

template <class T>
class TRingQ
{
protected:
	T* m_pData;
	int m_head;
	int m_tail;
	int m_size;

public:
	TRingQ()
	{
		m_pData = NULL;
		m_head = m_tail = m_size = 0;
	}

	~TRingQ()
	{
		if (m_pData)
			delete[] m_pData;
	}

	int Init(int size)
	{
		if (size < 2)
			return 1;

		if (m_pData)
			delete[] m_pData;

		m_pData = new T[size];
		m_size = size;
		m_head = m_tail = 0;
		return 0;
	}

	int IsEmpty() const { return GetLen() < 1; }
	int IsFull() const { return IsOverflow(1); }

	int IsUndersink(unsigned int n) const { return (int)n > GetLen(); }

	int IsOverflow(unsigned int n) const
	{
		if (m_head > m_tail)
		{
			if ((int)n < m_head - m_tail)
				return 0;
		}
		else if (m_size > (int)(m_tail - m_head + n))
		{
			return 0;
		}

		return 1;
	}

	T* GetHead(unsigned int n) const { return &m_pData[(m_head + n) % m_size]; }

	T* GetTail(unsigned int n) const
	{
		if (m_tail - (int)n < 0)
			return &m_pData[m_size - n + m_tail];

		return &m_pData[m_tail - n];
	}

	int GetLen() const
	{
		if (m_tail < m_head)
			return m_size - m_head + m_tail;
		else
			return m_tail - m_head;
	}

	T* StepHead(unsigned int n)
	{
		if (IsUndersink(n))
			return NULL;

		m_head = (m_head + n) % m_size;
		return &m_pData[m_head];
	}

	T* StepTail(unsigned int n)
	{
		if (IsOverflow(n))
			return NULL;

		m_tail = (m_tail + n) % m_size;
		return &m_pData[m_tail];
	}
};
