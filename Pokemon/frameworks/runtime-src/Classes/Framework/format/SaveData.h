/******************************
Description: Userdefined format data, for saving
Author: M.Wan
Date: 11/21/2014
******************************/

#ifndef __FORMAT_SAVEDATA__
#define __FORMAT_SAVEDATA__

#include "cocos2d.h"
#include <string>

class SaveData : public cocos2d::Ref
{
public:
	static SaveData *createWithData(const std::string &data);

	const std::string &getEncryptedData();
	inline unsigned int getEncryptedDataLength()
	{
		return this->_dataLength;
	}
	inline void setEncryptedDataLength(unsigned int length)
	{
		this->_dataLength = length;
	}
	inline float getVersion()
	{
		return this->_version;
	}
	inline void setVersion(float version)
	{
		this->_version = version;
	}

	bool saveToFile(const std::string &path);

private:
	bool initWithData(const std::string &data);

	std::string _prefix;	// prefix
	unsigned int _dataLength;	// encrypted data length
	float _version;		// version
};

#endif