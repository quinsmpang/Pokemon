#include "AesUtils.h"
#include "libaes/aes.h"

using namespace std;

namespace framework
{
	AesUtils::AesUtils()
	{
	}

	unsigned char *AesUtils::encipher(unsigned char *data, const std::string &key, int *outSize)
	{
		AES aes((unsigned char*)key.c_str());
		char *encryptedData = new char[1024 * 1024];
		aes.Cipher((char*)data, encryptedData);
		*outSize = string(encryptedData).size();
		/*for (int i = 0; i < 16; ++i)
		{
		encryptedData = aes.Cipher(encryptedData);
		}*/
		//printf("encipher: %s\n", encryptedData);

		return (unsigned char*)encryptedData;
	}

	unsigned char *AesUtils::decipher(unsigned char *data, const std::string &key, int *outSize)
	{
		AES aes((unsigned char*)key.c_str());
		char *decryptedData = new char[1024 * 1024];
		aes.InvCipher((char*)data, decryptedData);
		*outSize = string(decryptedData).size();
		/*for (int i = 0; i < 16; ++i)
		{
		decryptedData = (unsigned char*)aes.InvCipher(decryptedData);
		}*/
		//printf("decipher: %s\n", decryptedData);

		return (unsigned char*)decryptedData;
	}
}