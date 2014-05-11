/******************************
Description: Handle IO operations
Author: M.Wan
Date: 5/11/2014
******************************/

#ifndef __UTILS_IOUTILS__
#define __UTILS_IOUTILS__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class IOUtils : public cocos2d::Ref
	{
	public:
		static IOUtils *getInstance();

		// Judge whether the file or directory of specific name does exist.
		bool fileOrDirectoryExist(const std::string &path);

		// Move file from one path to another path, which can be also used to rename a file.
		bool moveFile(const std::string &oldPath, const std::string &newPath);

		// Write data to file
		bool writeDataToFile(const unsigned char *content, unsigned long length, const std::string &filePath, bool isAppend = false);

		// Delete file
		bool removeFile(const std::string &filePath);

		// Create directory
		bool createDirectory(const std::string &directoryPath);

	private:
		static IOUtils *_instance;
		IOUtils();
	};
}

#endif