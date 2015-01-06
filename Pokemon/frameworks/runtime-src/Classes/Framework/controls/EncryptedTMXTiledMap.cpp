#include "EncryptedTMXTiledMap.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	EncryptedTMXTiledMap::EncryptedTMXTiledMap()
		: _encryptor(nullptr)
        , _encryptionKey("")
	{
	}

	EncryptedTMXTiledMap::~EncryptedTMXTiledMap()
	{
		CC_SAFE_RELEASE_NULL(_encryptor);
	}

	EncryptedTMXTiledMap *EncryptedTMXTiledMap::create(const std::string &tmxFile, const std::string &encryptionKey)
	{
		auto pMap = new EncryptedTMXTiledMap();
		if (pMap && pMap->initWithEncryptedTMXFile(tmxFile, encryptionKey))
		{
			pMap->autorelease();
			return pMap;
		}
		CC_SAFE_RELEASE_NULL(pMap);
		return nullptr;
	}

	bool EncryptedTMXTiledMap::initWithEncryptedTMXFile(const std::string &tmxFile, const std::string &encryptionKey)
	{
		CCASSERT(tmxFile.size()>0, "EncryptedTMXTiledMap: tmx file should not be empty");

		this->setContentSize(Size::ZERO);

        this->_encryptionKey = encryptionKey;
		this->_encryptor = FileEncryptor::create(encryptionKey.c_str());
		this->_encryptor->retain();

		// compatible with Android
		const std::string &fullPath = FileUtils::getInstance()->fullPathForFilename(tmxFile);
		int outSize = 0;
		unsigned char *decryptData = this->_encryptor->decrypt(fullPath, &outSize);
		string xml((const char*)decryptData);

		auto mapInfo = TMXMapInfo::createWithXML(xml, "");
		free(decryptData);

		if (!mapInfo)
		{
			return false;
		}
		CCASSERT(!mapInfo->getTilesets().empty(), "TMXTiledMap: Map not found. Please check the filename.");
		this->initWithMapInfo(mapInfo);

		return true;
	}

	void EncryptedTMXTiledMap::initWithMapInfo(TMXMapInfo *mapInfo)
	{
		_mapSize = mapInfo->getMapSize();
		_tileSize = mapInfo->getTileSize();
		_mapOrientation = mapInfo->getOrientation();

		_objectGroups = mapInfo->getObjectGroups();

		_properties = mapInfo->getProperties();

		_tileProperties = mapInfo->getTileProperties();

		int idx=0;

		auto &layers = mapInfo->getLayers();
		for (const auto &layerInfo : layers) {
			if (layerInfo->_visible)
			{
				EncryptedTMXLayer *child = this->parseLayerByInfo(layerInfo, mapInfo);
				this->addChild(child, idx, idx);

				// update content size with the max size
				const Size& childSize = child->getContentSize();
				Size currentSize = this->getContentSize();
				currentSize.width = std::max( currentSize.width, childSize.width );
				currentSize.height = std::max( currentSize.height, childSize.height );
				this->setContentSize(currentSize);

				idx++;
			}
		}
	}

	EncryptedTMXLayer *EncryptedTMXTiledMap::parseLayerByInfo(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
	{
		TMXTilesetInfo *tileset = tilesetForLayer(layerInfo, mapInfo);
		EncryptedTMXLayer *layer = EncryptedTMXLayer::create(tileset, layerInfo, mapInfo, _encryptionKey);

		// tell the layerinfo to release the ownership of the tiles map.
		layerInfo->_ownTiles = false;
		layer->setupTiles();

		return layer;
	}
}