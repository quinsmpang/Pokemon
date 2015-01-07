/******************************
Description: For file encryption, use DES cipher
Author: M.Wan
Date: 6/21/2014
******************************/

#ifndef __ENCRYPTION_FILEENCRYPTOR__
#define __ENCRYPTION_FILEENCRYPTOR__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class FileEncryptor : public cocos2d::Ref
	{
	public:
        /**
         * FileEncryptor constructor.
         *
         * @param key Encryption key.
         */
		explicit FileEncryptor(const char *key);

        /**
         * Create a new FileEncryptor object.
         *
         * @param key Encryption key.
         *
         * @return Return a new FileEncryptor object.
         */
		static FileEncryptor *create(const char *key);

        /**
         * Simple encryption.
         *
         * @param filePath The file to be enciphered.
         */
		void encrypt(const std::string &filePath);

        /**
         * Simple decryption.
         *
         * @param filePath The file to be deciphered.
         * @param dataSize The data size after decryption.
         * @param writeToFile Whether to write into the origin file.
         *
         * @return The decrypted data.
         */
		unsigned char *decrypt(const std::string &filePath, int *dataSize, bool writeToFile = false);

	private:
		const std::string _key;
	};
}

#endif