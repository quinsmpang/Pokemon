#include "FileEncryptor.h"
#include "DesUtils.h"
#include "../utils/IOUtils.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	FileEncryptor::FileEncryptor(const char *key)
		: _key(key)
	{
	}

	FileEncryptor *FileEncryptor::create(const char *key)
	{
		auto pEncryptor = new FileEncryptor(key);
		if (pEncryptor)
		{
			pEncryptor->autorelease();
			return pEncryptor;
		}
		CC_SAFE_RELEASE_NULL(pEncryptor);
		return nullptr;
	}

	void FileEncryptor::encrypt(const string &filePath)
	{
		if (_key.size() == 0)
		{
			return;
		}

		// Compatiable with Android
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
		
		Data fileData = FileUtils::getInstance()->getDataFromFile(fullPath);
		ssize_t size = fileData.getSize();
		unsigned char *data = fileData.getBytes();

		// encryption
		int outSize = 0;
		unsigned char *encryptData = DesUtils::getInstance()->encrypt(_key.c_str(), data, size, &outSize);

		IOUtils::getInstance()->writeDataToFile(encryptData, outSize, fullPath);

		// release data
		free(encryptData);
	}

	unsigned char *FileEncryptor::decrypt(const string &filePath, int *dataSize, bool writeToFile)
	{
		if (_key.size() == 0)
		{
			return nullptr;
		}

		// Compatiable with Android
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
		
		Data fileData = FileUtils::getInstance()->getDataFromFile(fullPath);
		ssize_t size = fileData.getSize();
		unsigned char *data = fileData.getBytes();

		// decryption
		int outSize = 0;
		// don't forget to release it.
		unsigned char *decryptData = DesUtils::getInstance()->decrypt(_key.c_str(), data, size, &outSize);
		*dataSize = outSize;

		if (writeToFile)
		{
			IOUtils::getInstance()->writeDataToFile(decryptData, outSize, fullPath);
		}

		return decryptData;
	}
}