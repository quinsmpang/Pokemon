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
        /**
         * Create a new SaveData object.
         *
         * @param data The source data.
         *
         * @return Return a new SaveData object.
         */
		static SaveData *createWithData(const std::string &data);

        /**
         * SaveData constructor.
         */
		explicit SaveData();

        /**
         * Source data getter.
         *
         * @return Source data.
         */
		inline const std::string &getData() const
		{
			return this->_data;
		}
        /**
         * Version info getter.
         *
         * @return Version info.
         */
		inline float getVersion() const
		{
			return this->_version;
		}
        /**
         * Version info setter.
         *
         * @param version Version info.
         */
		inline void setVersion(float version)
		{
			this->_version = version;
		}
        /**
         * Get the prefix.
         *
         * @return Prefix.
         */
		inline const std::string &getPrefix() const
		{
			return this->_prefix;
		}
        /**
         * Prefix setter.
         *
         * @param prefix Userdefined prefix.
         */
		inline void setPrefix(const std::string &prefix)
		{
			this->_prefix = prefix;
		}

        /**
         * Serialize binary data into the file.
         *
         * @param path The destination file path.
         * @param cipherKey The encryption key using AES.
         *
         * @return Whether the operation is successful.
         */
		bool serializeToFile(const std::string &path, const std::string &cipherKey);
        /**
         * Deserialize into SaveData object from the specified file.
         *
         * @param path The destination file path.
         * @param cipherKey The encryption key using AES.
         *
         * @return The SaveData object after deserialization.
         */
		static SaveData *deserializeFromFile(const std::string &path, const std::string &cipherKey);

	private:
		bool initWithData(const std::string &data);

		std::string _prefix;	// prefix
		float _version;		// version
		std::string _data;		// data
	};
}

#endif