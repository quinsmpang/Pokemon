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
		unsigned char *encryptedData = aes.Cipher(data);
		//printf("encipher: %s\n", encryptedData);
		*outSize = string((const char*)encryptedData).size();

		return encryptedData;
	}

	unsigned char *AesUtils::decipher(unsigned char *data, const std::string &key, int *outSize)
	{
		AES aes((unsigned char*)key.c_str());
		unsigned char *decryptedData = (unsigned char*)aes.InvCipher(data);
		//printf("decipher: %s\n", decryptedData);
		*outSize = string((const char*)decryptedData).size();

		return decryptedData;
	}
}