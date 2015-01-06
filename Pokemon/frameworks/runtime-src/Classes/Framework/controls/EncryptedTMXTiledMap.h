/******************************
Description: Encrypted tmx-format tiled map
Author: M.Wan
Date: 6/22/2014
******************************/

#ifndef __CONTROLS_ENCRYPTEDTMXTILEDMAP__
#define __CONTROLS_ENCRYPTEDTMXTILEDMAP__

#include "cocos2d.h"
#include "../encryption/FileEncryptor.h"
#include "EncryptedTMXLayer.h"
#include <string>

namespace framework
{
	class EncryptedTMXLayer;

	class EncryptedTMXTiledMap : public cocos2d::TMXTiledMap
	{
	public:
        /**
         * Create an encrypted tmx map.
         *
         * @param tmxFile The path of the encrypted tmx file.
         * @param encryptionKey The encipher key of the tmx file.
         *
         * @return Return EncryptedTMXTiledMap object.
         */
		static EncryptedTMXTiledMap *create(const std::string &tmxFile, const std::string &encryptionKey);

        /**
         * EncryptedTMXTiledMap constructor.
         */
		explicit EncryptedTMXTiledMap();
        /**
         * EncryptedTMXTiledMap destructor.
         */
		~EncryptedTMXTiledMap();

	protected:
		bool initWithEncryptedTMXFile(const std::string &tmxFile, const std::string &encryptionKey);
		void initWithMapInfo(cocos2d::TMXMapInfo *mapInfo);
		EncryptedTMXLayer *parseLayerByInfo(cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo);

        std::string _encryptionKey;
		FileEncryptor *_encryptor;
	};
}

#endif