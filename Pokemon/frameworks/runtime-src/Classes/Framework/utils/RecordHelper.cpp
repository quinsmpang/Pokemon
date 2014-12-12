#include "RecordHelper.h"
#include "cocos2d.h"
#include <iostream>
#include <fstream>

using namespace cocos2d;
using namespace std;

namespace framework
{
	RecordHelper::RecordHelper()
		: _key(0)
	{
	}

	void RecordHelper::setEncryptionKey(const int &key)
	{
		this->_key = key;
	}

	bool RecordHelper::writeRecord(const std::string &filePath, const std::string &content)
	{
		string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);

		fstream hFile;

		hFile.open(fullPath.c_str(), ios::out);

		if (!hFile)
		{
			return false;
		}

		hFile << this->enciphering(content.c_str()) << endl;
		hFile.flush();
		hFile.close();

		return true;
	}

	const char *RecordHelper::readRecord(const std::string &filePath)
	{
		string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);

		fstream hFile;

		hFile.open(fullPath.c_str(), ios::in);

		if (!hFile)
		{
			return nullptr;
		}

		char buffer[1000] = { 0 };
		char ch;
		int index = 0;

		while (hFile.get(ch))
		{
			buffer[index] = ch;
			++index;
		}

		auto content = this->deciphering(buffer);

		return content;
	}

	const char *RecordHelper::enciphering(const char *content)
	{
		char *code = new char[1000];
		memset(code, 0, 1000);
		int index = 0, ch;
		while (content[index])
		{
			if (content[index] >= 'a' && content[index] <= 'z')
			{
				ch = content[index] + index + this->_key + 1;
				while (true)
				{
					if (ch > 'z')
					{
						ch -= 26;
					}
					else
					{
						break;
					}
				}
				code[index] = ch;
			}
			else
			{
				code[index] = content[index] ^ this->_key;
			}
			++index;
		}

		return code;
	}

	const char *RecordHelper::deciphering(const char *content)
	{
		char *code = new char[1000];
		memset(code, 0, 1000);
		int index = 0, ch;
		while (content[index])
		{
			if (content[index] >= 'a' && content[index] <= 'z')
			{
				ch = content[index] - index - 1 - this->_key;
				while (true)
				{
					if (ch < 'a')
					{
						ch += 26;
					}
					else
					{
						break;
					}
				}
				code[index] = ch;
			}
			else
			{
				code[index] = content[index] ^ this->_key;
			}
			++index;
		}
		// the last character is the redundant one, so remove it
		code[index - 1] = 0;

		return code;
	}
}