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
            // check bg color, if the global color map is nonexistent, then the bg color is no use.
            GifColorType defaultColor = { 0x0, 0x0, 0x0 };
            GifColorType bgColor = hGif->SColorMap ? hGif->SColorMap->Colors[hGif->SBackGroundColor] : defaultColor;
            CCLOG("Background color: R: %d, G: %d, B: %d", bgColor.Red, bgColor.Green, bgColor.Blue);
            // alloc the data for the bg at first, use RGBA8888 here
            unsigned int len = bgWidth * bgHeight * sizeof(unsigned int);
            unsigned int *pBgBuffer = (unsigned int*)malloc(len);
            // fill the bg color to the bg buffer
            // the first row
            unsigned int r, g, b, a;
            r = bgColor.Red;
            g = bgColor.Green;
            b = bgColor.Blue;
            a = 0x0;       // alpha, 0 indicates transparency
            unsigned int bgRgba = (a << 24) | (b << 16) | (g << 8) | r;
            for (int i = 0; i < bgWidth; ++i) {
                pBgBuffer[i] = bgRgba;
            }
            // copy the first row to the rest rows.
            for (int i = 1; i < bgHeight; ++i) {
                memcpy(pBgBuffer + i * bgWidth, pBgBuffer, bgWidth);
            }
            
            // save the sub image one by one
            unsigned int *pImgBuffer = nullptr;
            for (int i = 0; i < hGif->ImageCount; ++i) {
                pImgBuffer = (unsigned int*)malloc(len);
                memcpy(pImgBuffer, pBgBuffer, len);
                
                int top = hGif->SavedImages[i].ImageDesc.Top;
                int left = hGif->SavedImages[i].ImageDesc.Left;
                int width = hGif->SavedImages[i].ImageDesc.Width;
                int height = hGif->SavedImages[i].ImageDesc.Height;
                // check transparency from extension blocks
                GraphicsControlBlock gcb;
                DGifSavedExtensionToGCB(hGif, i, &gcb);
//                CCLOG("delay ts: %d", gcb.DelayTime);
                // image raw data: RGBRGB...(all color index) read them one by one
                unsigned char *pRawData = hGif->SavedImages[i].RasterBits;
                // check local color map, if nonexistence, use global color map
                // any possibility that neither of color maps exists?
                GifColorType *pColorMap = hGif->SavedImages[i].ImageDesc.ColorMap ? hGif->SavedImages[i].ImageDesc.ColorMap->Colors : hGif->SColorMap->Colors;
                // calculate the offset, retrieve data from raw data
                unsigned int *pImgPtr = pImgBuffer + top * bgWidth + left;
                unsigned char *pRawPtr = pRawData;
                int rawIndex;
                GifColorType color;
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        rawIndex = pRawPtr[x];
                        // check whether it is the transparent pixel
                        if (gcb.TransparentColor != -1 && gcb.TransparentColor == rawIndex) {
                            // skip the current pixel.
                            continue;
                        }
                        color = pColorMap[rawIndex];
                        r = color.Red;
                        g = color.Green;
                        b = color.Blue;
                        a = 0xff;       // alpha, default as 100% opacity
                        pImgPtr[x] = (a << 24) | (b << 16) | (g << 8) | r;
                    }
                    // shift the pointer
                    pImgPtr += width + left;
                    pRawPtr += width;
                }
                
                // create texture
                auto pTexture = new Texture2D();
                pTexture->initWithData((void*)pImgBuffer, len, Texture2D::PixelFormat::RGBA8888, bgWidth, bgHeight, Size(bgWidth, bgHeight));
                pTexture->autorelease();
                frames->addObject(pTexture);
                free(pImgBuffer);
            }
            
            // clean the buffer
            free(pBgBuffer);
            // close gif
            DGifCloseFile(hGif, &err);
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