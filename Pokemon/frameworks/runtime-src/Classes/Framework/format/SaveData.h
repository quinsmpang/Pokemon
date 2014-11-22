/******************************
Description: Userdefined format data, for saving
Author: M.Wan
Date: 11/21/2014
******************************/

#ifndef __FORMAT_SAVEDATA__
#define __FORMAT_SAVEDATA__

#include "cocos2d.h"
#include <string>

namespace framework
{
	class SaveData : public cocos2d::Ref
	{
	public:
		static SaveData *createWithData(const std::string &data);

		explicit SaveData();

		inline const std::string &getData() const
		{
			return this->_data;
		}
		inline float getVersion() const
		{
			return this->_version;
		}
		inline void setVersion(float version)
		{
			this->_version = version;
		}
		inline const std::string &getPrefix() const
		{
			return this->_prefix;
		}
		inline void setPrefix(const std::string &prefix)
		{
			this->_prefix = prefix;
		}

		bool serializeToFile(const std::string &path, const std::string &cipherKey);
		static SaveData *deserializeFromFile(const std::string &path, const std::string &cipherKey);

	private:
		bool initWithData(const std::string &data);

		std::string _prefix;	// prefix
		float _version;		// version
		std::string _data;		// data
	};
}

#endif