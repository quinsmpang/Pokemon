#pragma comment(lib, "FreeImage.lib")

#include "ImageUtils.h"
#include "FreeImage.h"
#include "2d/platform/CCFileUtils.h"
#include "base/CCVector.h"
#include <memory>

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

	framework::Vector *ImageUtils::getGifFrames(const std::string &imagePath)
	{
		Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(imagePath));

		BinaryData *pData = BinaryData::create(data.getBytes(), data.getSize());

		return this->getGifFrames(pData);
	}

	framework::Vector *ImageUtils::getGifFrames(BinaryData *imageData)
	{
		Vector *frames = Vector::create();

		FIMEMORY *pData = FreeImage_OpenMemory(imageData->getData(), imageData->getSize());

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//fif = FreeImage_GetFileType(imagePath.c_str());
		fif = FreeImage_GetFileTypeFromMemory(pData);

		if (fif == FIF_GIF)
		{
			FIMULTIBITMAP *fiBmps = FreeImage_LoadMultiBitmapFromMemory(fif, pData, GIF_PLAYBACK);
			if (fiBmps)
			{
				int frameCount = FreeImage_GetPageCount(fiBmps);
				for (int i = 0; i < frameCount; i++)
				{
					FIBITMAP *pBmp = FreeImage_LockPage(fiBmps, i);
					if (pBmp)
					{
						const int width = FreeImage_GetWidth(pBmp);
						const int height = FreeImage_GetHeight(pBmp);
						const int bpp = FreeImage_GetBPP(pBmp);
						char *data = (char*)FreeImage_GetBits(pBmp);
						// Í¼ÏñÊÇµßµ¹µÄ
						const int len = width * height * bpp / 8;
						const int bytes = bpp / 8;
						char *ptrBegin = data, *ptrEnd = data + (height - 1) * width * bytes;
						char *buffer = new char[width * bytes];
						memset(buffer, 0, width * bytes);
						for (int h = 0; h < height; h++)
						{
							if (ptrBegin >= ptrEnd)
							{
								break;
							}
							memcpy(buffer, ptrBegin, width * bytes);
							memcpy(ptrBegin, ptrEnd, width * bytes);
							memcpy(ptrEnd, buffer, width * bytes);

							ptrBegin += width * bytes;
							ptrEnd -= width * bytes;
						}

						Texture2D *pTexture = new Texture2D();
						pTexture->initWithData(data, len, Texture2D::PixelFormat::BGRA8888, width, height, Size(width, height));
						pTexture->autorelease();
						frames->addObject(pTexture);
						delete [] buffer;
						FreeImage_UnlockPage(fiBmps, pBmp, false); 
					}
					else
					{
						assert(false, "Invalid image data");
					}
				}
			}
			FreeImage_CloseMemory(pData);
			FreeImage_CloseMultiBitmap(fiBmps);
		}

		return frames;
	}

	Animate *ImageUtils::createAnimationByGifImage(const std::string &imagePath, float timeline)
	{
		Vector *frames = this->getGifFrames(imagePath);
		return this->createAnimationByFrames(frames, timeline);
	}

	Animate *ImageUtils::createAnimationByFrames(Vector *frames, float timeline)
	{
		cocos2d::Vector<SpriteFrame*> vFrames;
		
		Texture2D *pTexture = nullptr;
		for (int i = 0; i < frames->getLength(); i++)
		{
			pTexture = static_cast<Texture2D*>(frames->objectAt(i));
			vFrames.pushBack(SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height)));
		}

		auto pAnimation = Animation::createWithSpriteFrames(vFrames, timeline);
		auto pAnimate = Animate::create(pAnimation);

		return pAnimate;
	}

	Sprite *ImageUtils::createSpriteWithBinaryData(BinaryData *imageData)
	{
		Image *pImg = new Image();
		pImg->initWithImageData(imageData->getData(), imageData->getSize());
		Texture2D *pTexture = new Texture2D();
		pTexture->initWithImage(pImg);
		Sprite *pSprite = Sprite::createWithTexture(pTexture);

		return pSprite;
	}
}