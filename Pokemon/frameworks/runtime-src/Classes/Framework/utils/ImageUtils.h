/******************************
Description: Use FreeImage to analyze images' info
Author: M.Wan
Date: 8/2/2014
******************************/

#ifndef __IMAGEUTILS_H__
#define __IMAGEUTILS_H__

#include "base/CCRef.h"
#include "2d/platform/CCImage.h"
#include "2d/CCActionInterval.h"
#include "../containers/Vector.h"
#include "../base/BinaryData.h"

namespace framework
{
	class ImageUtils : public cocos2d::Ref
	{
	public:
		static ImageUtils *getInstance();

		Vector *getGifFrames(const std::string &imagePath);
		Vector *getGifFrames(BinaryData *imageData);
		cocos2d::Animate *createAnimationByGifImage(const std::string &imagePath, float timeline);
		cocos2d::Animate *createAnimationByFrames(Vector *frames, float timeline);

	private:
		static ImageUtils *_instance;
		ImageUtils();
		~ImageUtils();
	};
}

#endif