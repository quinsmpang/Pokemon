/******************************
Description: Write or read info to file.
Author: M.Wan
Date: 5/19/2014
******************************/

#ifndef __UTILS_RECORDHELPER__
#define __UTILS_RECORDHELPER__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class RecordHelper : public cocos2d::Ref
	{
	public:
		static RecordHelper *getInstance();

		void setEncryptionKey(const int &key);

		bool writeRecord(const std::string &filePath, const std::string &content);

		const char *readRecord(const std::string &filePath);

	private:
		static RecordHelper *_instance;

		RecordHelper();
		
		// encrypt and decrypt content
		const char *enciphering(const char *content);
		const char *deciphering(const char *content);

		int _key;
	};
}

#endif