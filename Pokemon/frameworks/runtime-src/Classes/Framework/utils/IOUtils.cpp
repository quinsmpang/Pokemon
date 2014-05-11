#include "IOUtils.h"
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <direct.h>
#include <vector>

using namespace std;

namespace framework
{
	IOUtils *IOUtils::_instance = nullptr;

	IOUtils *IOUtils::getInstance()
	{
		if (!_instance)
		{
			_instance = new IOUtils();
		}

		return _instance;
	}

	IOUtils::IOUtils()
	{
	}

	bool IOUtils::fileOrDirectoryExist(const std::string &path)
	{
		return _access(path.c_str(), 0) != -1;
	}

	bool IOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
	{
		return rename(oldPath.c_str(), newPath.c_str()) == 0;
	}

	bool IOUtils::writeDataToFile(const unsigned char *content, unsigned long length, const std::string &filePath, bool isAppend)
	{
		const char *mode = isAppend ? "ab" : "wb";
		FILE *hFile = fopen(filePath.c_str(), mode);
		if (!hFile)
		{
			return false;
		}

		size_t writtenSize = fwrite(content, length, 1, hFile);
		fclose(hFile);

		return writtenSize == length;
	}

	bool IOUtils::removeFile(const std::string &filePath)
	{
		return remove(filePath.c_str()) == 0;
	}

	bool IOUtils::createDirectory(const std::string &directoryPath)
	{
		vector<string> dirPathArray;
		string fullPath = directoryPath.c_str();

		// find the last directory which doesn't exist.
		string dirSubPath;
		do
		{
			int pos = fullPath.find_last_of('/');
			dirSubPath = fullPath.substr(0, pos);
			if (!fileOrDirectoryExist(directoryPath))
			{
				dirPathArray.insert(dirPathArray.begin(), dirSubPath);
				fullPath = dirSubPath.c_str();
			}
			else
			{
				break;
			}
		} while (true);

		// create directory in a loop.
		bool result = true;
		auto iter = dirPathArray.begin();
		while (iter != dirPathArray.end())
		{
			auto dir = (*iter).c_str();
			if (!_mkdir(dir))
			{
				result = false;
				break;
			}
			++iter;
		}

		return result;
	}
}