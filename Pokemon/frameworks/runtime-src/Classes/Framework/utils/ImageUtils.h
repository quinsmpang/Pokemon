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
        /**
         * ImageUtils is a singleton.
         */
		SINGLETON(ImageUtils);
	public:
        /**
         * Slurf the gif image, get each frame texture collection.
         *
         * @param imagePath Gif image path.
         *
         * @return Frame textures collection.
         */
		Vector *getGifFrames(const std::string &imagePath);
        /**
         * Get each frame texture collection from raw data.
         *
         * @param imageData Gif raw data.
         *
         * @return Frame textures collection.
         */
		Vector *getGifFrames(BinaryData *imageData);
        /**
         * Create frame animation from a gif image.
         *
         * @param imagePath Gif image path.
         * @param timeline Animation timeline.
         *
         * @return Animation.
         */
		cocos2d::Animate *createAnimationByGifImage(const std::string &imagePath, float timeline);
        /**
         * Create frame animation from specified frames.
         *
         * @param frames Texture frames.
         * @param timeline Animation timeline.
         *
         * @return Animation.
         */
		cocos2d::Animate *createAnimationByFrames(Vector *frames, float timeline);

        /**
         * Create sprite from raw data.
         *
         * @param imageData Texture raw data.
         *
         * @return Sprite.
         */
		cocos2d::Sprite *createSpriteWithBinaryData(BinaryData *imageData);
        /**
         * Create SpriteFrame object from raw data.
         *
         * @param imageData Texture raw data.
         *
         * @return SpriteFrame.
         */
		cocos2d::SpriteFrame *createSpriteFrameWithBinaryData(BinaryData *imageData);
	};
}

#endif