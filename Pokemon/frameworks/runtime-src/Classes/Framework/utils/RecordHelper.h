/******************************
Description: Write or read info to file.
Author: M.Wan
Date: 5/19/2014
******************************/

#ifndef __UTILS_RECORDHELPER__
#define __UTILS_RECORDHELPER__

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <string>

namespace framework
{
	class RecordHelper : public cocos2d::Ref
	{
        /**
         * RecordHelper is a singleton.
         */
		SINGLETON(RecordHelper);
	public:
        /**
         * Set up encryption key using by the record.
         *
         * @param key Encipher key.
         */
		void setEncryptionKey(const int &key);

        /**
         * Encrypted the specified content to the specified path.
         *
         * @param filePath Destination file path.
         * @param content Content to write to file.
         *
         * @return Operation result.
         */
		bool writeRecord(const std::string &filePath, const std::string &content);
        /**
         * Read the encrypted content from the file and decipher it.
         *
         * @param filePath Destination file path.
         *
         * @return The deciphered content.
         */
		const char *readRecord(const std::string &filePath);

	private:
		// encrypt and decrypt content
		const char *enciphering(const char *content);
		const char *deciphering(const char *content);

		int _key;
	};
}

#endif