/******************************
Description: Zip and Unzip utils, which supports zip encryption.
Author: M.Wan
Date: 8/3/2014
******************************/

#ifndef __ZIPHELPER_H__
#define __ZIPHELPER_H__

#include "../base/Macros.h"
#include "base/CCRef.h"
#include "../containers/Map.h"
#include "../base/BinaryData.h"
#include <string>

namespace framework
{
	class ZipHelper : public cocos2d::Ref
	{
		SINGLETON(ZipHelper);
	public:
		BinaryData *getFileDataInZip(const std::string &zipFile, const std::string &targetFile, const std::string &password = "");

		bool zipOneFile(const std::string &zipFile, const std::string &targetFile, unsigned char *data, unsigned long size, bool overwrite = false, const std::string &password = "");
		bool zipMultipleFiles(const std::string &zipFile, Map *allFilesInfo, bool overwrite = false, const std::string &password = "");
	};
}

#endif