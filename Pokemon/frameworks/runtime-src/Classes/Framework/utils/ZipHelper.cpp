#include "ZipHelper.h"
#include "2d/platform/CCFileUtils.h"
#include "IOUtils.h"
#include "../base/RefString.h"
#ifdef _WIN32
#include "ziplib/zip.h"
#include "ziplib/unzip.h"
#else
#endif

#define INVALID_ZIP_HANDLE 0

using namespace cocos2d;

namespace framework
{
	ZipHelper::ZipHelper()
	{
	}

	BinaryData *ZipHelper::getFileDataInZip(const std::string &zipFile, const std::string &targetFile, const std::string &password)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		std::string zipFilePath = FileUtils::getInstance()->fullPathForFilename(zipFile);
		wchar_t zipFilename[MAX_PATH] = { 0 };
		STDSTRING_TO_WCHAR(zipFilePath, zipFilename);
		wchar_t targetFilename[MAX_PATH] = { 0 };
		STDSTRING_TO_WCHAR(targetFile, targetFilename);
		const char *pwd = password.c_str();

		HZIP hZip = OpenZip(zipFilename, pwd);
		if (hZip == INVALID_ZIP_HANDLE)
		{
			printf("ZipHelper: %s zip file not found", zipFile.c_str());
			return nullptr;
		}
		ZIPENTRY zEntry;
		int index;
		FindZipItem(hZip, targetFilename, true, &index, &zEntry);
		unsigned long dataSize = zEntry.unc_size;
		unsigned char *pData = (unsigned char*)malloc(dataSize);
		UnzipItem(hZip, index, pData, dataSize);
		CloseZip(hZip);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        unsigned long dataSize = 0;
        unsigned char *pData = (unsigned char*)malloc(dataSize);
#endif
		
		auto binaryData = BinaryData::create(pData, dataSize);
		//binaryData->retain();

		return binaryData;
	}

	bool ZipHelper::zipOneFile(const std::string &zipFile, const std::string &targetFile, unsigned char *data, unsigned long size, bool overwrite, const std::string &password)
	{
		bool ret = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		wchar_t zipFilename[MAX_PATH] = { 0 };
		STDSTRING_TO_WCHAR(zipFile, zipFilename);
		wchar_t targetFilename[MAX_PATH] = { 0 };
		STDSTRING_TO_WCHAR(targetFile, targetFilename);

		HZIP hZip = INVALID_ZIP_HANDLE;
		if (!overwrite && FileUtils::getInstance()->isFileExist(zipFile))
		{
			// No way to add file to existing directly, you have to copy all files from the old zip to the new zip.
			std::string backupFile = zipFile + "~";
			IOUtils::getInstance()->copyFile(zipFile, backupFile);
			wchar_t backupFilename[MAX_PATH] = { 0 };
			STDSTRING_TO_WCHAR(backupFile, backupFilename);

			HZIP hOldZip = OpenZip(backupFilename, password.c_str());
			hZip = CreateZip(zipFilename, password.size() > 0 ? password.c_str() : nullptr);
			// copy all old zip files to the new one.
			ZIPENTRY entry;
			GetZipItem(hOldZip, -1, &entry);
			int count = entry.index;
			for (int i = 0; i < count; i++)
			{
				GetZipItem(hOldZip, i, &entry);
				unsigned char *pData = (unsigned char*)malloc(entry.unc_size);
				UnzipItem(hOldZip, i, pData, entry.unc_size);
				ZipAdd(hZip, entry.name, pData, entry.unc_size);
				free(pData);
			}
			CloseZip(hOldZip);
			IOUtils::getInstance()->removeFile(backupFile);
		}
		else
		{
			hZip = CreateZip(zipFilename, password.c_str());
		}
		// add new file
		ZipAdd(hZip, targetFilename, data, size);
		CloseZip(hZip);
		ret = true;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        ret = true;
#endif

		return ret;
	}

	bool ZipHelper::zipMultipleFiles(const std::string &zipFile, Map *allFilesInfo, bool overwrite, const std::string &password)
	{
		bool ret = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		wchar_t zipFilename[MAX_PATH] = { 0 };
		STDSTRING_TO_WCHAR(zipFile, zipFilename);

		HZIP hZip = INVALID_ZIP_HANDLE;
		if (!overwrite && FileUtils::getInstance()->isFileExist(zipFile))
		{
			// No way to add file to existing directly, you have to copy all files from the old zip to the new zip.
			std::string backupFile = zipFile + "~";
			IOUtils::getInstance()->copyFile(zipFile, backupFile);
			wchar_t backupFilename[MAX_PATH] = { 0 };
			STDSTRING_TO_WCHAR(backupFile, backupFilename);

			HZIP hOldZip = OpenZip(backupFilename, password.size() > 0 ? password.c_str() : nullptr);
			hZip = CreateZip(zipFilename, password.c_str());
			// copy all old zip files to the new one.
			ZIPENTRY entry;
			GetZipItem(hOldZip, -1, &entry);
			int count = entry.index;
			for (int i = 0; i < count; i++)
			{
				GetZipItem(hOldZip, i, &entry);
				unsigned char *pData = (unsigned char*)malloc(entry.unc_size);
				UnzipItem(hOldZip, i, pData, entry.unc_size);
				ZipAdd(hZip, entry.name, pData, entry.unc_size);
				free(pData);
			}
			CloseZip(hOldZip);
			IOUtils::getInstance()->removeFile(backupFile);
		}
		else
		{
			hZip = CreateZip(zipFilename, password.c_str());
		}
		// add new files
		Vector *allKeys = allFilesInfo->allKeys();
		for (int i = 0; i < allKeys->getLength(); i++)
		{
			std::string key = std::string(static_cast<RefString*>(allKeys->objectAt(i))->getCString());
			wchar_t filename[MAX_PATH] = { 0 };
			STDSTRING_TO_WCHAR(key, filename);
			BinaryData *pData = static_cast<BinaryData*>(allFilesInfo->objectForKey(key));
			ZipAdd(hZip, filename, pData->getData(), pData->getSize());
		}
		CloseZip(hZip);
		ret = true;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        ret = true;
#endif

		return ret;
	}
}