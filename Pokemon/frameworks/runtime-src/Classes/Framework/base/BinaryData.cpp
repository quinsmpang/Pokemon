#include "BinaryData.h"
#include <malloc.h>
#include <string.h>

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
			free(_data);
		}
	}

	bool BinaryData::init(unsigned char *data, unsigned long size)
	{
		// copy the data
		this->_data = (unsigned char*)malloc(size);
		memcpy(this->_data, data, size);
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