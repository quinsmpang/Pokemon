/******************************
Description: Use FreeImage to analyze images' info
Author: M.Wan
Date: 8/2/2014
******************************/

#ifndef __IMAGEUTILS_H__
#define __IMAGEUTILS_H__

#include "base/CCRef.h"
#include "2d/platform/CCImage.h"
#include "../containers/Vector.h"

namespace framework
{
	class ImageUtils : public cocos2d::Ref
	{
	public:
		static ImageUtils *getInstance();

		Vector *getGifFrames(std::string imagePath);
		Vector *getGifTimelines(std::string imagePath);

	private:
		static ImageUtils *_instance;
		ImageUtils();
		~ImageUtils();
	};
}

#endif