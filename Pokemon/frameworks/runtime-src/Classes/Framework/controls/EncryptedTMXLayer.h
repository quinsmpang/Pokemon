/******************************
Description: To decrypt map resources before using TMXLayer
Author: M.Wan
Date: 6/22/2014
******************************/

#ifndef __CONTROLS_ENCRYPTEDTMXLAYER__
#define __CONTROLS_ENCRYPTEDTMXLAYER__

#include "cocos2d.h"
#include "../encryption/FileEncryptor.h"
#include <string>

namespace framework
{
	class EncryptedTMXLayer : public cocos2d::TMXLayer
	{
	public:
		static EncryptedTMXLayer *create(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo, const std::string &encryptionKey);

		explicit EncryptedTMXLayer();
		~EncryptedTMXLayer();

		virtual void addChild(cocos2d::Node * child, int zOrder, int tag) override;
		
	protected:
		bool initWithInfo(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo, const std::string &encryptionKey);
		cocos2d::Point calculateLayerOffset(const cocos2d::Point &pos);

        std::string _encryptionKey;
		FileEncryptor *_encryptor;
	};
}

#endif