/******************************
Description: AES algorithm to encrypt and decrypt files
Author: M.Wan
Date: 11/21/2014
******************************/

#ifndef __ENCRYPTION_AESUTILS__
#define __ENCRYPTION_AESUTILS__

#include "../base/Macros.h"
#include <string>

namespace framework
{
	class AesUtils
	{
		SINGLETON(AesUtils);
	public:
		// key: 128-bit encryption key;  data: data to be encrypted;  outSize: data size after the encryption.
		// Note: You have to delete the non-nil return value by yourself.  free(p);
		unsigned char *encipher(unsigned char *data, const std::string &key, int *outSize);

		// Note: You have to delete the non-nil return value by yourself.  free(p);
		unsigned char *decipher(unsigned char *data, const std::string &key, int *outSize);
	};
}

#endif