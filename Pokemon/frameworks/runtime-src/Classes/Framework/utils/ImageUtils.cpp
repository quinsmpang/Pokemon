#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#pragma comment(lib, "FreeImage.lib")
#endif

#include "ImageUtils.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "lib/FreeImage.h"
#else
#include "giflib/gif_lib.h"
#endif
#include "2d/platform/CCFileUtils.h"
#include "base/CCVector.h"
#include <memory>

using namespace cocos2d;
using namespace std;

namespace framework
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    /* Read raw data of 'len' bytes from gif and copy them to the buffer */
    static int copyGifData(GifFileType *hGif, GifByteType *buffer, int len)
    {
        // UserData is the raw data you passed to giflib.
        char *pRawData = (char*)hGif->UserData;
        memcpy(buffer, pRawData, len);
        // don't forget to shift the ptr, cuz giflib doesn't read all data at once, you have to memory the offset you have read.
        pRawData += len;
        hGif->UserData = (void*)pRawData;
        
        return len;
    }
#endif
    
	ImageUtils::ImageUtils()
	{
		//FreeImage_Initialise(false);
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
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
						// The image is reversed.
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
						delete[] buffer;
						FreeImage_UnlockPage(fiBmps, pBmp, false);
					}
					else
					{
						CCASSERT(false, "Invalid image data");
					}
				}
			}
			FreeImage_CloseMemory(pData);
			FreeImage_CloseMultiBitmap(fiBmps);
		}
#else
        int err = 0;
        GifFileType *hGif = DGifOpen(imageData->getData(), copyGifData, &err);
        if (err)
        {
            CCLOG("Read gif error.");
            throw "invalid binary data.";
        }
        DGifSlurp(hGif);
        CCLOG("Gif frame count: %d", hGif->ImageCount);
        if (hGif->ImageCount > 0) {
            // gif width and height
            int bgWidth = hGif->SWidth;
            int bgHeight = hGif->SHeight;
            // gif color depth
            int cr = hGif->SColorResolution;
            // check bg color, if the global color map is nonexistent, then the bg color is no use.
            GifColorType *bgColor = hGif->SColorMap ? hGif->SColorMap[hGif->SBackGroundColor].Colors : nullptr;
            
            // read image data one by one
            unsigned char *pImgData = nullptr;
            for (int i = 0; i < hGif->ImageCount; ++i) {
                pImgData = hGif->SavedImages[i].RasterBits;
            }
        }
#endif

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

	SpriteFrame *ImageUtils::createSpriteFrameWithBinaryData(BinaryData *imageData)
	{
		auto pImg = new Image();
		pImg->initWithImageData(imageData->getData(), imageData->getSize());
		auto pTexture = new Texture2D();
		pTexture->initWithImage(pImg);
		auto pFrame = SpriteFrame::createWithTexture(pTexture, Rect(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));

		return pFrame;
	}
}