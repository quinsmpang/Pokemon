#include "SaveData.h"
#include "../encryption/AesUtils.h"
#include <new>
#include <iostream>
#include <fstream>

using namespace std;

namespace framework
{
	SaveData::SaveData()
		: _prefix("SAVE")
		, _version(0.0f)
	{
	}

	SaveData *SaveData::createWithData(const string &data)
	{
		auto pSave = new (nothrow) SaveData();
		if (pSave && pSave->initWithData(data))
		{
			pSave->autorelease();
			return pSave;
		}
		CC_SAFE_RELEASE(pSave);
		return nullptr;
	}

	bool SaveData::initWithData(const string &data)
	{
		this->_data = data;

		return true;
	}

	bool SaveData::serializeToFile(const std::string &path, const std::string &cipherKey)
	{
		int size;
		unsigned char *encryptedData = AesUtils::getInstance()->encipher((unsigned char*)this->_data.c_str(), cipherKey, &size);

		ofstream ofs;
		ofs.open(path, ios::out | ios::binary);
		if (!ofs.good())
		{
			return false;
		}
		// write prefix, 4 bytes
		ofs.write(this->_prefix.c_str(), 4);
		char *pSize = (char*)&size;
		ofs.write(pSize, sizeof(int));
		char *pVersion = (char*)&_version;
		ofs.write(pVersion, sizeof(float));
		ofs.write((const char*)encryptedData, size);
		if (!ofs.good())
		{
			return false;
		}

		ofs.close();

		return true;
	}

	SaveData *SaveData::desearialzeFromFile(const std::string &path, const std::string &cipherKey)
	{
		ifstream ifs;
		ifs.open(path, ios::in | ios::binary);
		if (!ifs.good())
		{
			return false;
		}
		// get prefix
		char prefix[5] = { 0 };
		ifs.read(prefix, 4);
		char size[4];
		ifs.read(size, 4);
		int nSize = *((int*)size);
		char version[4];
		ifs.read(version, 4);
		float fVersion = *((float*)version);
		char *encryptedData = new char[nSize];
		ifs.read(encryptedData, nSize);
		if (!ifs.good())
		{
			return false;
		}

		ifs.close();

		int outSize;
		unsigned char *decryptedData = AesUtils::getInstance()->decipher((unsigned char*)encryptedData, cipherKey, &outSize);

		auto pSave = SaveData::createWithData(string((const char*)decryptedData));
		pSave->setPrefex(prefix);
		pSave->setVersion(fVersion);

		cout << pSave->getData() << endl;

		return pSave;
	}
}