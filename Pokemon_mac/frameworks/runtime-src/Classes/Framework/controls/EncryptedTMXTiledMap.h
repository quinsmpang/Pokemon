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
		static const char *ENCRYPTION_KEY;

		static EncryptedTMXTiledMap *create(const std::string &tmxFile);

		explicit EncryptedTMXTiledMap();
		~EncryptedTMXTiledMap();

		bool initWithEncryptedTMXFile(const std::string &tmxFile);

	protected:
		void initWithMapInfo(cocos2d::TMXMapInfo *mapInfo);
		EncryptedTMXLayer *parseLayerByInfo(cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo);

		FileEncryptor *_encryptor;
	};
}

#endif