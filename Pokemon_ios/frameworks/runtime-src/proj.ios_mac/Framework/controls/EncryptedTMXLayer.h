/******************************
Description: To decrypt map resources before using TMXLayer
Author: M.Wan
Date: 6/22/2014
******************************/

#ifndef __CONTROLS_ENCRYPTEDTMXLAYER__
#define __CONTROLS_ENCRYPTEDTMXLAYER__

#include "cocos2d.h"
#include "../encryption/FileEncryptor.h"

namespace framework
{
	class EncryptedTMXLayer : public cocos2d::TMXLayer
	{
	public:
		static const char *ENCRYPTION_KEY;

		static EncryptedTMXLayer *create(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo);

		explicit EncryptedTMXLayer();
		~EncryptedTMXLayer();

		bool initWithInfo(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo);

		virtual void addChild(cocos2d::Node * child, int zOrder, int tag) override;
		
	protected:
		cocos2d::Point calculateLayerOffset(const cocos2d::Point &pos);

		FileEncryptor *_encryptor;
	};
}

#endif