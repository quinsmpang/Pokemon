/******************************
Description: Binary data, to save raw data and data size
Author: M.Wan
Date: 8/4/2014
******************************/

#ifndef __BINARYDATA_H__
#define __BINARYDATA_H__

#include "base/CCRef.h"
#include <memory>

namespace framework
{
	class BinaryData : public cocos2d::Ref
	{
	public:
		static BinaryData *create(unsigned char *data, unsigned long size);

		bool init(unsigned char *data, unsigned long size);

		unsigned char *getData() const;
		unsigned long getSize() const;

	private:
		std::shared_ptr<unsigned char> _data;
		unsigned long _size;
	};
}

#endif