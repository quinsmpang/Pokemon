#include "ImageUtils.h"
#include "FreeImage.h"
#include "2d/platform/CCFileUtils.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	ImageUtils *ImageUtils::_instance = nullptr;

	ImageUtils *ImageUtils::getInstance()
	{
		if (!_instance)
		{
			_instance = new ImageUtils();
		}
		return _instance;
	}

	ImageUtils::ImageUtils()
	{
		//FreeImage_Initialise(false);
	}

	ImageUtils::~ImageUtils()
	{
		//FreeImage_DeInitialise();
	}

	Vector *ImageUtils::getGifFrames(std::string imagePath)
	{
		Vector *frames = Vector::create();

		Data data = FileUtils::getInstance()->getDataFromFile(imagePath);
		FIMEMORY *pData = FreeImage_OpenMemory(data.getBytes(), data.getSize());

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileTypeFromMemory(pData);

		if (fif == FIF_GIF)
		{
			FIMULTIBITMAP *fiBmps = FreeImage_LoadMultiBitmapFromMemory(fif, pData, GIF_DEFAULT);
			if (fiBmps)
			{
				int frameCount = FreeImage_GetPageCount(fiBmps);
				for (int i = 0; i < frameCount; i++)
				{
					FIBITMAP *pBmp = FreeImage_LockPage(fiBmps, i);
					if (pBmp)
					{
						int width = FreeImage_GetWidth(pBmp);
						int height = FreeImage_GetHeight(pBmp);
						Image *pImg = new Image();
						pImg->initWithImageData((const unsigned char*)pBmp->data, width * height);
						Texture2D *pTexture = new Texture2D();
						pTexture->initWithImage(pImg);
						pImg->release();
						frames->addObject(pTexture);
					}
					else
					{
						assert(false, "Invalid image data");
					}
				}
			}
		}

		return frames;
	}

	Vector *ImageUtils::getGifTimelines(std::string imagePath)
	{
		Vector *timelines = Vector::create();

		return timelines;
	}
}