/******************************
Description: Use FreeImage to analyze images' info
Author: M.Wan
Date: 8/2/2014
******************************/

#ifndef __IMAGEUTILS_H__
#define __IMAGEUTILS_H__

#include "../base/Macros.h"
#include "base/CCRef.h"
#include "2d/platform/CCImage.h"
#include "2d/CCActionInterval.h"
#include "../containers/Vector.h"
#include "../base/BinaryData.h"

namespace framework
{
	class ImageUtils : public cocos2d::Ref
	{
		SINGLETON(ImageUtils);
	public:
		Vector *getGifFrames(const std::string &imagePath);
		Vector *getGifFrames(BinaryData *imageData);
		cocos2d::Animate *createAnimationByGifImage(const std::string &imagePath, float timeline);
		cocos2d::Animate *createAnimationByFrames(Vector *frames, float timeline);

		cocos2d::Sprite *createSpriteWithBinaryData(BinaryData *imageData);
		cocos2d::SpriteFrame *createSpriteFrameWithBinaryData(BinaryData *imageData);
	};
}

#endif