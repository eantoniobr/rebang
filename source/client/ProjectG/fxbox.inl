inline std::map<CFxSequence*, CFxSequence*>& CFxBox::GetSequenceList()
{
	return m_sequence;
}

inline std::map<CFxSpray*, CFxSpray*>& CFxBox::GetSprayList()
{
	return m_spray;
}

inline CFxSpray* CFxBox::GetSpray(int index)
{
	if (index < 0)
		return NULL;

	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it, --index)
	{
		if (index == 0)
			return (*it).second;
	}

	return NULL;
}

inline bool CFxBox::FindSequence(CFxSequence* sequence)
{
	return m_sequence.find(sequence) != m_sequence.end();
}

inline bool CFxBox::FindSpray(CFxSpray* spray)
{
	return m_spray.find(spray) != m_spray.end();
}

inline bool CFxBox::GetOutput(WVector& quake, unsigned char& flash)
{
	for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_spray.begin();
		it != m_spray.end(); ++it)
	{
		CFxSpray* spray = (*it).second;

		float rate = 1.0f / ((quake - spray->m_quakePos).Magnitude() + 1.0f);
		quake += spray->m_quake * rate;
		int value = flash + spray->m_flash;
		flash = value > 255 ? 255 : value;
	}

	return m_spray.size() != 0;
}

inline float CFxBox::Random(float min, float max)
{
	return min + (max - min) * (rand() % 20001) * 0.00005f;
}

inline WVector CFxBox::Random(const WVector& min, const WVector& max)
{
	return WVector(Random(min.x, max.x), Random(min.y, max.y),
		Random(min.z, max.z));
}

inline WVector CFxBox::Random(const WVector& center, float minRadius,
	float maxRadius, float angle)
{
	float c = cosf(angle * 0.5f);
	WVector2D h;
	float y, len;

	do
	{
		h.x = Random(-1.0f, 1.0f);
		h.y = Random(-1.0f, 1.0f);
		y = Random(c, 1.0f);

		len = h.Magnitude();

	} while (Wabs(len) < 0.00001f);

	h = h * (sqrtf(1.0f - y * y) / len);

	float r = Random(minRadius, maxRadius);
	return center + WVector(h.x * r, y * r, h.y * r);
}

#define IS_EQUAL(a, b) ((a) - (b) < 0.00001f && (a) - (b) > -0.00001f)

inline bool IsEqual(float a, float b)
{
	float d = a - b;
	return d < 0.00001f && d > -0.00001f;
}

inline bool CFxBox::CheckGroundCollision(const WVector& from, const WVector& to,
	float& height, float radius)
{
	if (IS_EQUAL(to.y, height))
		return true;

	if (to.y < height)
	{
		if (IS_EQUAL(from.y, height) || from.y < height)
			return IS_EQUAL(to.y + radius, height) || to.y + radius > height;
	}
	else
	{
		if (IS_EQUAL(from.y, height) || from.y > height)
			return IS_EQUAL(to.y - radius, height) || to.y - radius < height;
	}

	return true;
}

inline void CFxBox::OnSequenceCreated(CFxSequence* sequence)
{
}

inline void CFxBox::OnSequenceDeleted(CFxSequence* sequence)
{
}

inline void CFxBox::OnSprayCreated(CFxSpray* spray)
{
}

inline void CFxBox::OnSprayDeleted(CFxSpray* spray)
{
}
