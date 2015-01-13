/******************************
Description: DES algorithm to encrypt and decrypt files
Author: M.Wan
Date: 6/21/2014
******************************/

#ifndef __ENCRYPTION_DESUTILS__
#define __ENCRYPTION_DESUTILS__

#include "../base/Macros.h"

namespace framework
{
	class DesUtils
	{
		SINGLETON(DesUtils);
	public:
        /**
         * @brief Encrypt content using DES.
         * Note: You have to delete the non-nil return value by yourself.  free(p);
         *
         * @param key 24-bit encryption key.
         * @param data Data to be enciphered.
         * @param data The size of raw data.
         * @param outSize You can get the data size after the encryption from here.
         *
         * @return The content after encryption.
         */
		void *encrypt(const char *key, void *data, int inSize, int *outSize);

		/**
         * @brief Decrypt content using DES.
         * Note: You have to delete the non-nil return value by yourself.  free(p);
         *
         * @param key 24-bit encryption key.
         * @param data Data to be deciphered.
         * @param data The size of encrypted data.
         * @param outSize You can get the data size after the decryption from here.
         *
         * @return The content after decryption.
         */
		void *decrypt(const char *key, void *data, int inSize, int *outSize);

	private:
		static DesUtils *_instance;
	};
}

#endif