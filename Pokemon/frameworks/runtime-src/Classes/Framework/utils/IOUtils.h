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
        /**
         * IOUtils is a singleton.
         */
		SINGLETON(IOUtils);
	public:
        /**
         * Check whether the specified file does exist.
         *
         * @param path File path to check.
         *
         * @return A boolean value.
         */
		bool fileExists(const std::string &path);

        /**
         * Check whether the directory does exist.
         *
         * @param path Directory path to check.
         *
         * @return A boolean value.
         */
		bool directoryExists(const std::string &path);

        /**
         * Move file from old path to new path.
         *
         * @param oldPath Source file path.
         * @param newPath New file path.
         *
         * @return Operation result.
         */
		bool moveFile(const std::string &oldPath, const std::string &newPath);

		/**
         * Copy file from old path to new path.
         *
         * @param oldPath Source file path.
         * @param newPath New file path.
         *
         * @return Operation result.
         */
		bool copyFile(const std::string &oldPath, const std::string &newPath);

		/**
         * Write content to the specified file.
         *
         * @param content File content to write.
         * @param length Content size.
         * @param filePath Destination file path.
         * @param isAppend Whether to append the content at the end of the file.
         *
         * @return Operation result.
         */
		bool writeDataToFile(const unsigned char *content, unsigned long length, const std::string &filePath, bool isAppend = false);

		/**
         * Remove file from the specified path.
         *
         * @param filePath Destination file path.
         *
         * @return Operation result.
         */
		bool removeFile(const std::string &filePath);

		/**
         * Create a new directory.
         *
         * @param directoryPath The new directory path.
         *
         * @return Operation result.
         */
		bool createDirectory(const std::string &directoryPath);
	};
}

#endif