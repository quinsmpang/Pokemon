#include "BinaryData.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	BinaryData *BinaryData::create(unsigned char *data, unsigned long size)
	{
		auto pData = new BinaryData();
		if (pData->init(data, size))
		{
			pData->autorelease();
			return pData;
		}
		CC_SAFE_RELEASE(pData);
		return nullptr;
	}

	bool BinaryData::init(unsigned char *data, unsigned long size)
	{
		this->_data = shared_ptr<unsigned char>(data);
		this->_size = size;

		return true;
	}

	unsigned char *BinaryData::getData() const
	{
		return _data.get();
	}

	unsigned long BinaryData::getSize() const
	{
		return _size;
	}
}