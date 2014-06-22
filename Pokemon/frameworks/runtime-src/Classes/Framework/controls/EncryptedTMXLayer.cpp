#include "EncryptedTMXLayer.h"

using namespace cocos2d;

namespace framework
{
	const char *EncryptedTMXLayer::ENCRYPTION_KEY = "b77j19dK8ay2F5k90znsC31g";

	EncryptedTMXLayer *EncryptedTMXLayer::create(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo)
	{
		auto pLayer = new EncryptedTMXLayer();
		if (pLayer && pLayer->initWithInfo(tilesetInfo, layerInfo, mapInfo))
		{
			pLayer->autorelease();
			return pLayer;
		}
		CC_SAFE_RELEASE_NULL(pLayer);
		return nullptr;
	}

	EncryptedTMXLayer::EncryptedTMXLayer()
		: _encryptor(nullptr)
	{
	}

	EncryptedTMXLayer::~EncryptedTMXLayer()
	{
		CC_SAFE_RELEASE_NULL(_encryptor);
	}

	bool EncryptedTMXLayer::initWithInfo(cocos2d::TMXTilesetInfo *tilesetInfo, cocos2d::TMXLayerInfo *layerInfo, cocos2d::TMXMapInfo *mapInfo)
	{
		// XXX: is 35% a good estimate ?
		Size size = layerInfo->_layerSize;
		float totalNumberOfTiles = size.width * size.height;
		float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?

		this->_encryptor = FileEncryptor::create(EncryptedTMXLayer::ENCRYPTION_KEY);
		this->_encryptor->retain();

		Texture2D *texture = nullptr;
		if( tilesetInfo )
		{
			// decrypt first, compatible with Android
			const std::string &resourcePath = FileUtils::getInstance()->fullPathForFilename(tilesetInfo->_sourceImage);
			int outSize = 0;
			unsigned char *data = this->_encryptor->decrypt(resourcePath, &outSize);
			Image *pImage = new Image();
			bool bRet = pImage->initWithImageData(data, outSize);
			if (!bRet)
			{
				return false;
			}

			texture = Director::getInstance()->getTextureCache()->addImage(pImage, resourcePath);
		}

		if (SpriteBatchNode::initWithTexture(texture, static_cast<ssize_t>(capacity)))
		{
			// layerInfo
			_layerName = layerInfo->_name;
			_layerSize = size;
			_tiles = layerInfo->_tiles;
			_opacity = layerInfo->_opacity;
			setProperties(layerInfo->getProperties());
			_contentScaleFactor = Director::getInstance()->getContentScaleFactor(); 

			// tilesetInfo
			_tileSet = tilesetInfo;
			CC_SAFE_RETAIN(_tileSet);

			// mapInfo
			_mapTileSize = mapInfo->getTileSize();
			_layerOrientation = mapInfo->getOrientation();

			// offset (after layer orientation is set);
			Point offset = this->calculateLayerOffset(layerInfo->_offset);
			this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

			_atlasIndexArray = ccCArrayNew(totalNumberOfTiles);

			this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));

			_useAutomaticVertexZ = false;
			_vertexZvalue = 0;

			return true;
		}
		return false;
	}

	//CCTMXLayer - obtaining positions, offset
	Point EncryptedTMXLayer::calculateLayerOffset(const Point& pos)
	{
		Point ret = Point::ZERO;
		switch (_layerOrientation) 
		{
		case TMXOrientationOrtho:
			ret = Point( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
			break;
		case TMXOrientationIso:
			ret = Point((_mapTileSize.width /2) * (pos.x - pos.y),
				(_mapTileSize.height /2 ) * (-pos.x - pos.y));
			break;
		case TMXOrientationHex:
			CCASSERT(pos.equals(Point::ZERO), "offset for hexagonal map not implemented yet");
			break;
		}
		return ret;    
	}

	void EncryptedTMXLayer::addChild(Node * child, int zOrder, int tag)
	{
		CCASSERT( child != nullptr, "Argument must be non-nil");
		CCASSERT( child->getParent() == nullptr, "child already added. It can't be added again");

		if (_children.empty())
		{
			this->childrenAlloc();
		}

		this->insertChild(child, zOrder);

		child->setTag(tag);

		child->setParent(this);
		child->setOrderOfArrival(s_globalOrderOfArrival++);

		if( _running )
		{
			child->onEnter();
			// prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
			if (_isTransitionFinished) {
				child->onEnterTransitionDidFinish();
			}
		}

		if (_cascadeColorEnabled)
		{
			updateCascadeColor();
		}

		if (_cascadeOpacityEnabled)
		{
			updateCascadeOpacity();
		}
	}
}