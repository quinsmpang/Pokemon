/******************************
Description: Handle IO operations
Author: M.Wan
Date: 5/11/2014
******************************/

#ifndef __UTILS_IOUTILS__
#define __UTILS_IOUTILS__

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <string>

namespace framework
{
	class IOUtils : public cocos2d::Ref
	{
		SINGLETON(IOUtils);
	public:
		// Judge whether the file does exist.
		bool fileExists(const std::string &path);

		// Judge whether the directory does exist.
		bool directoryExists(const std::string &path);

		// Move file from one path to another path, which can be also used to rename a file.
		bool moveFile(const std::string &oldPath, const std::string &newPath);

		// Copy file from one path to another path
		bool copyFile(const std::string &oldPath, const std::string &newPath);

		// Write data to file
		bool writeDataToFile(const unsigned char *content, unsigned long length, const std::string &filePath, bool isAppend = false);

		// Delete file
		bool removeFile(const std::string &filePath);

		// Create directory
		bool createDirectory(const std::string &directoryPath);
	};
}

#endif