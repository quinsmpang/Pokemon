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
        /**
         * ZipHelper is a singleton.
         */
		SINGLETON(ZipHelper);
	public:
        /**
         * Get decompressed item raw data from the specified zip file.
         *
         * @param zipFile Destination .zip file path.
         * @param targetFile Compressed item name.
         * @param password The password of the zip if there is one.
         *
         * @return Raw data of the seeking item.
         */
		BinaryData *getFileDataInZip(const std::string &zipFile, const std::string &targetFile, const std::string &password = "");

        /**
         * Compress one file into zip.
         *
         * @param zipFile Destination .zip file path.
         * @param targetFile The destination compressed file name.
         * @param data The raw data to compress.
         * @param size Data size.
         * @param overwrite Whether to overwrite the existing zip file.
         * @param password Whether to add a new password
         *
         * @return Operation result.
         */
		bool zipOneFile(const std::string &zipFile, const std::string &targetFile, unsigned char *data, unsigned long size, bool overwrite = false, const std::string &password = "");
        /**
         * Compress multiple files into zip.
         *
         * @param zipFile Destination .zip file path.
         * @param allFilesInfo Destination files map, key is target name, value is the raw data.
         * @param overwrite Whether to overwrite the existing zip file.
         * @param password Whether to add a new password
         *
         * @return Operation result.
         */
		bool zipMultipleFiles(const std::string &zipFile, Map *allFilesInfo, bool overwrite = false, const std::string &password = "");
	};
}

#endif