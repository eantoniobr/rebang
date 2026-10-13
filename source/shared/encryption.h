#pragma once

#define ENCRYPTION_KEY "{782AE110-2EEF-4c61-B030-A53F17634F7D}"
#define ENCRYPTION_KEY_LEN (sizeof(ENCRYPTION_KEY) - 1)

template <typename T>
static unsigned int __stdcall Decrypt(T* src, unsigned int srclen)
{
	unsigned char* data = (unsigned char*)src;

	unsigned int i = 0;
	if (srclen < ENCRYPTION_KEY_LEN)
	{
		for (unsigned int j = 0; j < ENCRYPTION_KEY_LEN; j++)
		{
			data[i++] ^= ENCRYPTION_KEY[j];
			if (i >= srclen)
				i = 0;
		}
		return ENCRYPTION_KEY_LEN;
	}

	for (unsigned int j = 0; j < srclen; j++)
	{
		data[j] ^= ENCRYPTION_KEY[i++];
		if (i >= ENCRYPTION_KEY_LEN)
			i = 0;
	}
	return srclen;
}

class CEncryption
{
private:
	CEncryption() { }
	~CEncryption() { }

public:
	static CEncryption* Instance()
	{
		static CEncryption _Instance;
		return &_Instance;
	}

	template <class T>
	void Encrypt(T* pData, EncryptKey& key)
	{
		T data;
		memcpy(&data, pData, sizeof(T));

		unsigned char* p = (unsigned char*)&data;
		int k = 0;
		for (int i = 0; i < (int)sizeof(T); i++)
		{
			p[i] ^= key.GetKey(k++);

			if (k >= 16)
				k = 0;
		}

		memcpy(pData, &data, sizeof(T));
	}
};
