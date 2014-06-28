#include "IOUtils.h"
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <direct.h>
#include <vector>
#include <fstream>

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

	bool IOUtils::fileExists(const std::string &path)
	{
		fstream file;
		file.open(path, ios::in);
		bool exist = file;
		file.close();

		return exist;
	}

	bool IOUtils::directoryExists(const std::string &path)
	{
		return _access(path.c_str(), 0) != -1;
	}

	bool IOUtils::moveFile(const std::string &oldPath, const std::string &newPath)
	{
		return rename(oldPath.c_str(), newPath.c_str()) == 0;
	}

	bool IOUtils::copyFile(const std::string &oldPath, const std::string &newPath)
	{
		ifstream in;
		ofstream out;
		in.open(oldPath, ios::binary);		// open source file
		if (in.fail())
		{
			printf("Failed to open the source file.");
			in.close();
			out.close();
			return false;
		}
		out << in.rdbuf();
		out.close();
		in.close();
		return true;
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
		// split the directory path
		vector<string> dirPathArray;
		string subStr = directoryPath;
		do
		{
			auto pos = subStr.find_first_of('/');
			if (pos < subStr.size())
			{
				dirPathArray.push_back(directoryPath.substr(0, pos));
				subStr = subStr.substr(pos + 1, subStr.size() - 1);
				continue;
			}
			dirPathArray.push_back(directoryPath);
			break;
		} while (true);

		// create directory in a loop.
		bool result = true;
		auto iter = dirPathArray.begin();
		while (iter != dirPathArray.end())
		{
			auto dir = (*iter).c_str();
			if (_mkdir(dir))
			{
				result = false;
				break;
			}
			++iter;
		}

		return result;
	}
}