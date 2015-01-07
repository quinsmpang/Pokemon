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
        /**
         * @brief Encrypt content using AES.
         * Note: You have to delete the non-nil return value by yourself.  free(p);
         *
         * @param data Data to be enciphered.
         * @param key 128-bit encryption key.
         * @param outSize You can get the data size after the encryption from here.
         *
         * @return The content after encryption.
         */
		unsigned char *encipher(unsigned char *data, const std::string &key, int *outSize);

		/**
         * @brief Decrypt content using AES.
         * Note: You have to delete the non-nil return value by yourself.  free(p);
         *
         * @param data Data to be deciphered.
         * @param key 128-bit encryption key.
         * @param outSize You can get the data size after the decryption from here.
         *
         * @return The content after decryption.
         */
		unsigned char *decipher(unsigned char *data, const std::string &key, int *outSize);
	};
}

#endif