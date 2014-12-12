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
		SINGLETON(RecordHelper);
	public:
		void setEncryptionKey(const int &key);

		bool writeRecord(const std::string &filePath, const std::string &content);

		const char *readRecord(const std::string &filePath);

	private:
		// encrypt and decrypt content
		const char *enciphering(const char *content);
		const char *deciphering(const char *content);

		int _key;
	};
}

#endif