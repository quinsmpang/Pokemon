/******************************
Description: For file encryption
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
		explicit FileEncryptor(const char *key);

		static FileEncryptor *create(const char *key);

		void encrypt(const std::string &filePath);

		unsigned char *decrypt(const std::string &filePath, int *dataSize, bool writeToFile = false);

	private:
		const std::string _key;
	};
}

#endif