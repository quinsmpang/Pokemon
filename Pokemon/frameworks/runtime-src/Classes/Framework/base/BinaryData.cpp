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

	BinaryData::~BinaryData()
	{
		if (_data)
		{
			delete _data;
		}
	}

	bool BinaryData::init(unsigned char *data, unsigned long size)
	{
		this->_data = data;
		this->_size = size;

		return true;
	}

	unsigned char *BinaryData::getData() const
	{
		return _data;
	}

	unsigned long BinaryData::getSize() const
	{
		return _size;
	}
}