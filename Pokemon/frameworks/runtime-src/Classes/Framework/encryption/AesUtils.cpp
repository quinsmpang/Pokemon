#include "AesUtils.h"
#include "libaes/aes.h"
#include <stdlib.h>

using namespace std;

namespace framework
{
	AesUtils::AesUtils()
	{
	}

	void *AesUtils::encipher(void *data, const std::string &key, int *outSize)
	{
		AES aes((unsigned char*)key.c_str());
		char *encryptedData = (char*)malloc(1024 * 1024);
		aes.Cipher((char*)data, encryptedData);
		*outSize = string(encryptedData).size();
		/*for (int i = 0; i < 16; ++i)
		{
		encryptedData = aes.Cipher(encryptedData);
		}*/
		//printf("encipher: %s\n", encryptedData);

		return encryptedData;
	}

	void *AesUtils::decipher(void *data, const std::string &key, int *outSize)
	{
		AES aes((unsigned char*)key.c_str());
		char *decryptedData = (char*)malloc(1024 * 1024);
		aes.InvCipher((char*)data, decryptedData);
		*outSize = string(decryptedData).size();
		/*for (int i = 0; i < 16; ++i)
		{
		decryptedData = (unsigned char*)aes.InvCipher(decryptedData);
		}*/
		//printf("decipher: %s\n", decryptedData);

		return decryptedData;
	}
}